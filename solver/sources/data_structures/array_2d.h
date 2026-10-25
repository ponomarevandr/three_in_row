#pragma once

#include <cstdint>
#include <vector>


namespace ThreeInRow {

template<typename Type>
class Array2D {
private:
	std::vector<Type> buffer;
	size_t m;
	size_t n;
	uint32_t power_m;

public:
	Array2D() = default;
	void resize(size_t m, size_t n);
	std::pair<size_t, size_t> size() const;
	void set(size_t i, size_t j, Type value);
	Type get(size_t i, size_t j) const;

private:
	static uint32_t log2Ceil(size_t);
};


template<typename Type>
void Array2D<Type>::resize(size_t m, size_t n) {
	this->m = m;
	this->n = n;
	power_m = log2Ceil(m);
	buffer.resize(n * (static_cast<size_t>(1) << power_m));
}

template<typename Type>
std::pair<size_t, size_t> Array2D<Type>::size() const {
	return std::make_pair(m, n);
}

template<typename Type>
void Array2D<Type>::set(size_t i, size_t j, Type value) {
	buffer[i + (j << power_m)] = value;
}

template<typename Type>
Type Array2D<Type>::get(size_t i, size_t j) const {
	return buffer[i + (j << power_m)];
}


template<typename Type>
uint32_t Array2D<Type>::log2Ceil(size_t value) {
	uint32_t result = 0;
	while (static_cast<size_t>(1) << result < value) {
		++result;
	}
	return result;
}

}