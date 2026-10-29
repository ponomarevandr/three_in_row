#pragma once

#include "game/position.h"


namespace ThreeInRow {

uint8_t playerNext(uint8_t player);

uint8_t whoseTurn(const Position&);

}