#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <cstdint>

#include "phyber/utils/datatypes.h"

TEST_CASE("DynamicArray", "[DynamicArray]") {
    SECTION("DynamicArray default construction") {
        DynamicArray<int> arr;

        CHECK(arr.size() == 0);
        CHECK(arr.capacity() == 0);
    }

    SECTION("DynamicArray custom capacity") {
        DynamicArray<int> arr(10);

        CHECK(arr.size() == 0);
        CHECK(arr.capacity() == 10);
    }

    SECTION("push_back increases size") {
        DynamicArray<int> arr(2);

        arr.push_back(1);
        arr.push_back(2);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 2);
    }

    SECTION("push_back triggers growth") {
        DynamicArray<int> arr(1);

        arr.push_back(10);
        size_t old_capacity = arr.capacity();
        CHECK(old_capacity == 1);

        arr.push_back(20);

        CHECK(arr.size() == 2);
        CHECK(arr.capacity() > old_capacity);
    }

    SECTION("insert at beginning") {
        DynamicArray<int> arr;

        arr.push_back(2);
        arr.push_back(3);

        arr.insert(0, 1);

        CHECK(arr.size() == 3);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 2);
        CHECK(arr.begin()[2] == 3);
    }

    SECTION("insert in middle") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(3);

        arr.insert(1, 2);

        CHECK(arr.size() == 3);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 2);
        CHECK(arr.begin()[2] == 3);
    }

    SECTION("insert at end") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.insert(1, 2);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[1] == 2);
    }

    SECTION("erase middle element") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);
        arr.push_back(3);

        arr.erase(1);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[0] == 1);
        CHECK(arr.begin()[1] == 3);
    }

    SECTION("erase last element") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr.erase(1);

        CHECK(arr.size() == 1);
        CHECK(arr.begin()[0] == 1);
    }

    SECTION("resize larger") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.resize(5);

        CHECK(arr.size() == 5);
        CHECK(arr.begin()[0] == 1);

        for (size_t i = 1; i < 5; ++i) {
            CHECK(arr.begin()[i] == 0);
        }
    }

    SECTION("resize smaller") {
        DynamicArray<int> arr;

        for (int i = 0; i < 5; ++i)
            arr.push_back(i);

        arr.resize(2);

        CHECK(arr.size() == 2);
        CHECK(arr.begin()[0] == 0);
        CHECK(arr.begin()[1] == 1);
    }

    SECTION("clear resets size") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr.clear();

        CHECK(arr.size() == 0);
        CHECK(arr.capacity() >= 2);
    }

    SECTION("shrink_to_fit reduces capacity") {
        DynamicArray<int> arr(10);

        arr.push_back(1);
        arr.push_back(2);

        arr.shrink_to_fit();

        CHECK(arr.capacity() == arr.size());
    }

    SECTION("out of bounds insert throws") {
        DynamicArray<int> arr;

        CHECK_THROWS(arr.insert(1, 5));
    }

    SECTION("out of bounds erase throws") {
        DynamicArray<int> arr;

        CHECK_THROWS(arr.erase(0));
    }

    SECTION("operator[] read access") {
        DynamicArray<int> arr;

        arr.push_back(10);
        arr.push_back(20);
        arr.push_back(30);

        CHECK(arr[0] == 10);
        CHECK(arr[1] == 20);
        CHECK(arr[2] == 30);
    }

    SECTION("operator[] write access") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr[0] = 42;
        arr[1] = 99;

        CHECK(arr[0] == 42);
        CHECK(arr[1] == 99);
    }

    SECTION("operator[] const access") {
        DynamicArray<int> arr;

        arr.push_back(5);
        arr.push_back(6);

        const DynamicArray<int>& cref = arr;

        CHECK(cref[0] == 5);
        CHECK(cref[1] == 6);
    }

    SECTION("at() write access") {
        DynamicArray<int> arr;

        arr.push_back(1);
        arr.push_back(2);

        arr.at(0) = 11;
        arr.at(1) = 22;

        CHECK(arr[0] == 11);
        CHECK(arr[1] == 22);
    }

    SECTION("at() const access") {
        DynamicArray<int> arr;

        arr.push_back(3);
        arr.push_back(4);

        const DynamicArray<int>& cref = arr;

        CHECK(cref.at(0) == 3);
        CHECK(cref.at(1) == 4);
    }

    SECTION("at() throws on out-of-bounds read") {
        DynamicArray<int> arr;

        arr.push_back(1);

        CHECK_THROWS_AS(arr.at(1), std::out_of_range);
        CHECK_THROWS_AS(arr.at(100), std::out_of_range);
    }

    SECTION("at() throws on out-of-bounds write") {
        DynamicArray<int> arr;

        arr.push_back(1);

        CHECK_THROWS_AS(arr.at(2) = 5, std::out_of_range);
    }
}
