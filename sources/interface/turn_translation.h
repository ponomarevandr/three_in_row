#pragma once

#include <cstdint>
#include <string>


namespace Interface {

std::pair<size_t, uint8_t> turnToUser(size_t index);
size_t turnToProgram(size_t index_whole, uint8_t player);

std::wstring turnToString(size_t index);

}