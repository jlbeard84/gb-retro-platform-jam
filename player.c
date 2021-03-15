#include <gb/gb.h>
#include "enums/player_direction.c"
#include "enums/player_color.c"

struct Player
{
    enum PlayerDirection direction;
    enum PlayerColor color;
    UINT8 playerTile[4];
    UINT8 position[2];
    UINT8 lastPosition[2];
};