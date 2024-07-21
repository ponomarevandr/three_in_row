#include "output.h"


namespace Debug {

Output::~Output() {
	if (fout.is_open()) {
		fout << "\n=============== End";
		fout.close();
	}
}

std::ofstream& Output::getStream() {
	if (!fout.is_open()) {
		fout.open("debug.txt");
		fout << "=============== Debug output\n\n";
	}
	return fout;
}

Output output;

}