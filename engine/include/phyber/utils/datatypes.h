#ifndef PHYBER_ENGINE_DATATYPES_H
#define PHYBER_ENGINE_DATATYPES_H

// requires c++11 for templates

#include <new>
#include <stdexcept>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <type_traits>

template <typename T>
class DynamicArray {
    static_assert(std::is_trivially_copyable<T>::value,
                      "DynamicArray requires trivially copyable types");
private:
    T *_array = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

protected:
    bool free_slots() const {
        return _size < _capacity;
    }

public:
    explicit DynamicArray(size_t capacity=0) {
        // If ptr is NULL, realloc() is identical to a call to malloc() for capacity bytes
        reserve(capacity);
    }

    ~DynamicArray() {
        free(_array);
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

    void reserve(size_t new_capacity) {
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
    void resize(size_t new_size) {
        reserve(new_size);

        if (new_size > _size) {
            memset(_array + _size, 0, (new_size - _size) * sizeof(T));
        }

        _size = new_size;
    }

    void shrink_to_fit() {
        if (free_slots()) {
            resize(_size);
        }
    }

    void clear() {
        _size = 0;
    }

    void pop_back() {
        if (_size > 0) { --_size; }
    }

    T *erase(size_t pos) {
        if (pos >= _size) {
            throw std::out_of_range("Out of bounds");
        }
        else if (pos == _size-1) {
            return _array + (--_size);
        } else {
            // can't use memcpy here because we could overwrite memory before it's moved to final destination
            memmove(_array + pos, _array + (pos + 1), (_size - pos - 1) * sizeof(T));
            --_size;
            return _array + pos;
        }
    }

    void insert(size_t pos, const T &v) {
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

    void push_back(const T &v) {
        insert(_size, v);
    }
};

#endif /* PHYBER_ENGINE_DATATYPES_H */
