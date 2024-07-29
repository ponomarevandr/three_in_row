#pragma once

#include <string>


namespace Interface {

std::pair<size_t, size_t> turnToUser(size_t index);
size_t turnToProgram(size_t whole, size_t third);

std::wstring turnToString(size_t index);

}