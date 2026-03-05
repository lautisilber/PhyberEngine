#ifndef PHYBER_ENGINE_DATATYPES_H
#define PHYBER_ENGINE_DATATYPES_H

// requires c++11 for templates

#include <new>
#include <stdexcept>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <type_traits>

namespace Phyber {

#define ENABLE_TRIVIALLY_SIMPLE(ReturnType) \
    template <typename U = T, typename std::enable_if< \
        std::is_trivially_copyable<U>::value && std::is_trivially_destructible<U>::value, int>::type = 0> \
    ReturnType

#define ENABLE_NON_TRIVIALLY_SIMPLE(ReturnType) \
    template <typename U = T, typename std::enable_if< \
        !(std::is_trivially_copyable<U>::value && std::is_trivially_destructible<U>::value), int>::type = 0> \
    ReturnType

// implementation for trivially copiable types
template <typename T>
class DynamicArray {
    static_assert(std::is_default_constructible<T>::value,
                      "T must be default constructible");
    static_assert(std::is_move_constructible<T>::value || std::is_trivially_copyable<T>::value,
                  "T must be move constructible or trivially copyable");
private:
    T *_array = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

protected:
    bool free_slots() const {
        return _size < _capacity;
    }

private:
    inline void _destructor(std::true_type) {
        free(_array);
    }

    inline void _destructor(std::false_type) {
        for (size_t i = 0; i < _size; ++i) {
            _array[i].~T();
        }
        ::operator delete(_array, std::align_val_t(alignof(T)));
    }

public:
    explicit DynamicArray(size_t capacity=0) {
        // If ptr is NULL, realloc() is identical to a call to malloc() for capacity bytes
        reserve(capacity);
    }

    ~DynamicArray() {
        _destructor(std::is_trivially_copyable<T>{});
    }

    size_t capacity() const { return _capacity; }
    size_t size() const { return _size; }

    T *begin() { return _array; }
    T *end() { return _array + _size; }
    const T &operator[](size_t index) const {
        return _array[index];
    }
    T &operator[](size_t index) {
        return _array[index];
    }
    const T &at(size_t index) const {
        if (index >= _size) {
            throw std::runtime_error("Out of bounds");
        }
        return _array[index];
    }
    T &at(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Out of bounds");
        }
        return _array[index];
    }

    ENABLE_TRIVIALLY_SIMPLE(void)
    reserve(size_t new_capacity) {
        if (new_capacity == _capacity) { return; }

        // we want a new_ptr because if the allocation fails, we lose track
        // of the pointer to the existing allocated memory, and it will cause
        // a memory leak. By first checking if the allocation is successful, we
        // can gracefully destroy DynamicArray and free the allocated memory
        void* new_ptr = realloc(_array, new_capacity * sizeof(T));
        if (!new_ptr) {
            throw std::bad_alloc();
        }

        _array = static_cast<T*>(new_ptr);
        _capacity = new_capacity;

        if (_size > _capacity)
            _size = _capacity;
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    reserve(size_t new_capacity) {
        if (new_capacity == _capacity) { return; }

        T* new_array = static_cast<T*>(::operator new(sizeof(T) * new_capacity, std::align_val_t(alignof(T))));

        // Move existing objects (need to construct new objects at destination because non exist beforehand)
        for (size_t i = 0; i < _size; ++i) {
            new (new_array + i) T(std::move(_array[i]));
            _array[i].~T();
        }

        ::operator delete(_array);
        _array = new_array;
        _capacity = new_capacity;
    }

    ENABLE_TRIVIALLY_SIMPLE(void)
    resize(size_t new_size) {
        reserve(new_size);

        if (new_size > _size) {
            memset(_array + _size, 0, (new_size - _size) * sizeof(T));
        }

        _size = new_size;
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    resize(size_t new_size) {
        reserve(new_size);

        // runs if new_size > _size
        for (size_t i = _size; i < new_size; ++i) {
            new (_array + i) T(); // default-construct new object
        }
        // runs if new_size < _size
        for (size_t i = new_size; i < _size; ++i) {
            _array[i].~T(); // destroy objects being removed
        }

        _size = new_size;
    }

    void shrink_to_fit() {
        if (free_slots()) {
            resize(_size);
        }
    }

    ENABLE_TRIVIALLY_SIMPLE(void)
    clear() {
        _size = 0;
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    clear() {
        // destroy all objects before forgetting them
        for (size_t i = 0; i < _size; ++i) {
            _array[i].~T();
        }
        _size = 0;
    }

    ENABLE_TRIVIALLY_SIMPLE(void)
    pop_back() {
        if (_size > 0) {
            --_size;
        }
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    pop_back() {
        if (_size > 0) {
            _array[(_size--) - 1].~T();
        }
    }

    ENABLE_TRIVIALLY_SIMPLE(T *)
    erase(size_t pos) {
        if (pos >= _size) {
            throw std::out_of_range("Out of bounds");
        } else if (pos == _size-1) {
            return _array + (--_size);
        } else {
            // can't use memcpy here because we could overwrite memory before it's moved to final destination
            memmove(_array + pos, _array + (pos + 1), (_size - pos - 1) * sizeof(T));
            --_size;
            return _array + pos;
        }
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(T *)
    erase(size_t pos) {
        if (pos >= _size) {
            throw std::out_of_range("Out of bounds");
        }
        _array[pos].~T();
        for (size_t i = pos; i < _size - 1; ++i) {
            new (_array + i) T(std::move(_array[i+1]));
            _array[i+1].~T();
        }
        --_size;
        return _array + pos;
    }

    ENABLE_TRIVIALLY_SIMPLE(void)
    insert(size_t pos, const T &v) {
        if (pos > _size) {
            throw std::out_of_range("Out of bounds");
        }

        if (!free_slots()) {
            reserve(_capacity > 1 ? (_capacity * 3) / 2 : 2);
        }

        if (pos == _size) {
            memcpy(_array + (_size++), &v, sizeof(T));
        } else {
            // can't use memcpy here because we could overwrite memory before it's moved to final destination
            memmove(_array + (pos + 1), _array + pos, (_size - pos) * sizeof(T));
            memcpy(_array + pos, &v, sizeof(T));
            ++_size;
        }
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    insert(size_t pos, const T &v) {
        if (pos > _size) {
            throw std::out_of_range("Out of bounds");
        }

        if (!free_slots()) {
            reserve(_capacity > 1 ? (_capacity * 3) / 2 : 2);
        }

        for (size_t i = _size; i > pos; --i) {
            new (_array + i) T(std::move(_array[i - 1]));
            _array[i - 1].~T(); // destroy old
        }
        new (_array + pos) T(v);

        ++_size;
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    insert(size_t pos, T &&v) {
        if (pos > _size) {
            throw std::out_of_range("Out of bounds");
        }

        if (!free_slots()) {
            reserve(_capacity > 1 ? (_capacity * 3) / 2 : 2);
        }

        for (size_t i = _size; i > pos; --i) {
            new (_array + i) T(std::move(_array[i - 1]));
            _array[i - 1].~T(); // destroy old
        }
        new (_array + pos) T(std::move(v));

        ++_size;
    }

    ENABLE_TRIVIALLY_SIMPLE(void)
    push_back(const T &v) {
        insert(_size, v);
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    push_back(const T &v) {
        insert(_size, v);
    }
    ENABLE_NON_TRIVIALLY_SIMPLE(void)
    push_back(T &&v) {
        insert(_size, std::move(v));
    }
};

#undef ENABLE_TRIVIALLY_SIMPLE
#undef ENABLE_NON_TRIVIALLY_SIMPLE

}

#endif /* PHYBER_ENGINE_DATATYPES_H */
