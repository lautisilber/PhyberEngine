#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <cstdint>

#include "phyber/utils/datatypes.h"

TEST_CASE("DynamicArray trivially-copiable type", "[DynamicArray]") {
    SECTION("DynamicArray default construction") {
        Phyber::DynamicArray<int> arr;

        CHECK(arr.size() == 0);
        CHECK(arr.capacity() == 0);
    }

    SECTION("DynamicArray custom capacity") {
        Phyber::DynamicArray<int> arr(10);

        CHECK(arr.size() == 0);
        CHECK(arr.capacity() == 10);
    }

    SECTION("push_back increases size") {
        Phyber::DynamicArray<int> arr(2);

        arr.push_back(1);
        arr.push_back(2);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 2);
    }

    SECTION("push_back triggers growth") {
        Phyber::DynamicArray<int> arr(1);

        arr.push_back(10);
        size_t old_capacity = arr.capacity();
        CHECK(old_capacity == 1);

        arr.push_back(20);

        CHECK(arr.size() == 2);
        CHECK(arr.capacity() > old_capacity);
    }

    SECTION("insert at beginning") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(2);
        arr.push_back(3);

        arr.insert(0, 1);

        CHECK(arr.size() == 3);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 2);
        CHECK(arr.begin()[2] == 3);
    }

    SECTION("insert in middle") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(3);

        arr.insert(1, 2);

        CHECK(arr.size() == 3);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 2);
        CHECK(arr.begin()[2] == 3);
    }

    SECTION("insert at end") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.insert(1, 2);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[1] == 2);
    }

    SECTION("erase middle element") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);
        arr.push_back(3);

        arr.erase(1);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 3);
    }

    SECTION("erase last element") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr.erase(1);

        CHECK(arr.size() == 1);
        CHECK(arr.begin()[0] == 1);
    }

    SECTION("resize larger") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.resize(5);

        CHECK(arr.size() == 5);
        CHECK(arr.begin()[0] == 1);

        for (size_t i = 1; i < 5; ++i) {
            CHECK(arr.begin()[i] == 0);
        }
    }

    SECTION("resize smaller") {
        Phyber::DynamicArray<int> arr;

        for (int i = 0; i < 5; ++i)
            arr.push_back(i);

        arr.resize(2);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[0] == 0);
        CHECK(arr.begin()[1] == 1);
    }

    SECTION("clear resets size") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr.clear();

        CHECK(arr.size() == 0);
        CHECK(arr.capacity() >= 2);
    }

    SECTION("shrink_to_fit reduces capacity") {
        Phyber::DynamicArray<int> arr(10);

        arr.push_back(1);
        arr.push_back(2);

        arr.shrink_to_fit();

        CHECK(arr.capacity() == arr.size());
    }

    SECTION("out of bounds insert throws") {
        Phyber::DynamicArray<int> arr;

        CHECK_THROWS(arr.insert(1, 5));
    }

    SECTION("out of bounds erase throws") {
        Phyber::DynamicArray<int> arr;

        CHECK_THROWS(arr.erase(0));
    }

    SECTION("operator[] read access") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(10);
        arr.push_back(20);
        arr.push_back(30);

        CHECK(arr[0] == 10);
        CHECK(arr[1] == 20);
        CHECK(arr[2] == 30);
    }

    SECTION("operator[] write access") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr[0] = 42;
        arr[1] = 99;

        CHECK(arr[0] == 42);
        CHECK(arr[1] == 99);
    }

    SECTION("operator[] const access") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(5);
        arr.push_back(6);

        const Phyber::DynamicArray<int>& cref = arr;

        CHECK(cref[0] == 5);
        CHECK(cref[1] == 6);
    }

    SECTION("at() write access") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr.at(0) = 11;
        arr.at(1) = 22;

        CHECK(arr[0] == 11);
        CHECK(arr[1] == 22);
    }

    SECTION("at() const access") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(3);
        arr.push_back(4);

        const Phyber::DynamicArray<int>& cref = arr;

        CHECK(cref.at(0) == 3);
        CHECK(cref.at(1) == 4);
    }

    SECTION("at() throws on out-of-bounds read") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);

        CHECK_THROWS_AS(arr.at(1), std::out_of_range);
        CHECK_THROWS_AS(arr.at(100), std::out_of_range);
    }

    SECTION("at() throws on out-of-bounds write") {
        Phyber::DynamicArray<int> arr;

        arr.push_back(1);

        CHECK_THROWS_AS(arr.at(2) = 5, std::out_of_range);
    }
}

struct Track {
    static int constructions;
    static int destructions;
    static int copies;
    static int moves;

    int value;

    Track(int v = 0) : value(v) { ++constructions; }
    Track(const Track &other) : value(other.value) { ++constructions; ++copies; }
    Track(Track &&other) noexcept : value(other.value) { ++constructions; ++moves; other.value = 0; }
    ~Track() { ++destructions; }

    Track &operator=(const Track &other) { value = other.value; ++copies; return *this; }
    Track &operator=(Track &&other) noexcept { value = other.value; other.value = 0; ++moves; return *this; }

    bool operator==(const Track &other) const { return value == other.value; }

    static void reset_counters() {
        constructions = 0;
        destructions = 0;
        copies = 0;
        moves = 0;
    }
};
// initialize static counters
int Track::constructions = 0;
int Track::destructions = 0;
int Track::copies = 0;
int Track::moves = 0;

TEST_CASE("DynamicArray non-trivially copyable", "[DynamicArray]") {
    SECTION("push_back and move semantics") {
        Track::reset_counters();
        {
            Phyber::DynamicArray<Track> arr;
            arr.push_back(Track(1));
            arr.push_back(Track(2));

            CHECK(arr.size() == 2);
            CHECK(arr[0].value == 1);
            CHECK(arr[1].value == 2);

            // Cannot check constructions == destructions yet, temporaries still exist
        }

        // Array is destroyed here, temporaries too
        CHECK(Track::constructions == Track::destructions);
    }

    SECTION("insert at middle with rvalue") {
        Track::reset_counters();
        {
            Phyber::DynamicArray<Track> arr;

            arr.push_back(Track(1));
            arr.push_back(Track(3));

            arr.insert(1, Track(2));

            CHECK(arr.size() == 3);
            CHECK(arr[0].value == 1);
            CHECK(arr[1].value == 2);
            CHECK(arr[2].value == 3);
        }

        CHECK(Track::destructions == Track::constructions);
    }

    SECTION("erase middle element") {
        Track::reset_counters();
        {
            Phyber::DynamicArray<Track> arr;
            arr.push_back(Track(1));
            arr.push_back(Track(2));
            arr.push_back(Track(3));

            arr.erase(1);

            CHECK(arr.size() == 2);
            CHECK(arr[0].value == 1);
            CHECK(arr[1].value == 3);
        }

        CHECK(Track::destructions == Track::constructions);
    }

    SECTION("resize larger and smaller") {
        Track::reset_counters();
        {
            Phyber::DynamicArray<Track> arr;
            arr.push_back(Track(1));
            arr.resize(5);

            CHECK(arr.size() == 5);
            CHECK(arr[0].value == 1);

            arr.resize(2);
            CHECK(arr.size() == 2);
            CHECK(arr[0].value == 1);
            CHECK(arr[1].value == 0);
        }

        CHECK(Track::destructions == Track::constructions);
    }

    SECTION("clear destroys elements") {
        Track::reset_counters();
        {
            Phyber::DynamicArray<Track> arr;
            arr.push_back(Track(1));
            arr.push_back(Track(2));

            arr.clear();
            CHECK(arr.size() == 0);
        }
        CHECK(Track::destructions == Track::constructions);
    }

    SECTION("pop_back destroys last element") {
        Track::reset_counters();
        {
            Phyber::DynamicArray<Track> arr;
            arr.push_back(Track(1));
            arr.push_back(Track(2));

            arr.pop_back();
            CHECK(arr.size() == 1);
            CHECK(arr[0].value == 1);
        }
        CHECK(Track::destructions == Track::constructions);
    }
}
