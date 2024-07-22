#include "output.h"


namespace Debug {

Output::~Output() {
	if (fout.is_open()) {
		fout << "\n=============== End";
		fout.close();
	}
}

FlushingStream::FlushingStream(std::ofstream& fout): fout(fout) {}

FlushingStream Output::getStream() {
	if (!fout.is_open()) {
		fout.open("debug.txt");
		fout << "=============== Debug output\n\n";
		fout.flush();
	}
	return FlushingStream(fout);
}

Output output;

}