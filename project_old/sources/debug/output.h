#pragma once

#include <fstream>


namespace Debug {

class FlushingStream {
private:
	std::ofstream& fout;

public:
	explicit FlushingStream(std::ofstream& fout);

	template<typename T>
	FlushingStream& operator<<(const T& value) {
		fout << value;
		fout.flush();
		return *this;
	}
};

class Output {
private:
	std::ofstream fout;

public:
	Output() = default;
	~Output();
	FlushingStream getStream();
};

extern Output output;

}