#include "player_user.h"


namespace Game {

void PlayerUser::setTurnColumn(size_t turn_column) {
	this->turn_column = turn_column;
	is_ready = true;
}

}