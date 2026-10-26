#include "game/position.h"

#include <iostream>


using namespace ThreeInRow;

int main() {
	Position position;
	position.fromStream(std::cin);
	position.toStream(std::cout);
	return 0;
}