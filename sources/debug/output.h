#pragma once

#include <fstream>


namespace Debug {

class Output {
private:
	std::ofstream fout;

public:
	Output() = default;
	~Output();
	std::ofstream& getStream();
};

extern Output output;

}