#include "data_structures/array_2d.h"

#include <gtest/gtest.h>

#include <tuple>


using namespace ThreeInRow;

TEST(Array2D, Resize) {
	Array2D<uint8_t> array;
	array.resize(17, 31);
	size_t m, n;
	std::tie(m, n) = array.size();
	ASSERT_EQ(m, 17);
	ASSERT_EQ(n, 31);
	array.resize(1, 1);
	std::tie(m, n) = array.size();
	ASSERT_EQ(m, 1);
	ASSERT_EQ(n, 1);
}

TEST(Array2D, Resize0) {
	Array2D<uint8_t> array;
	array.resize(0, 0);
	size_t m, n;
	std::tie(m, n) = array.size();
	ASSERT_EQ(m, 0);
	ASSERT_EQ(n, 0);
	array.resize(5, 0);
	std::tie(m, n) = array.size();
	ASSERT_EQ(m, 5);
	ASSERT_EQ(n, 0);
	array.resize(0, 5);
	std::tie(m, n) = array.size();
	ASSERT_EQ(m, 0);
	ASSERT_EQ(n, 5);
}

TEST(Array2D, Assign) {
	Array2D<int32_t> array;
	array.resize(19, 7);
	for (size_t i = 0; i < 19; ++i) {
		for (size_t j = 0; j < 7; ++j) {
			array.set(i, j, i * j * j);
		}
	}
	for (size_t i = 0; i < 19; ++i) {
		for (size_t j = 0; j < 7; ++j) {
			ASSERT_EQ(array.get(i, j), i * j * j);
		}
	}
}

TEST(Array2D, AssignPower2) {
	Array2D<int32_t> array;
	array.resize(16, 32);
	for (size_t i = 0; i < 16; ++i) {
		for (size_t j = 0; j < 32; ++j) {
			array.set(i, j, i * j * j);
		}
	}
	for (size_t i = 0; i < 16; ++i) {
		for (size_t j = 0; j < 32; ++j) {
			ASSERT_EQ(array.get(i, j), i * j * j);
		}
	}
}