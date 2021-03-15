#include <gb/gb.h>
#include <string.h>
#include <stdbool.h>
#include "graphics/player_sprite.c"
#include "player.c"

void main();
void init();
void setPlayerTile();
void checkInput();
void updatePlayerDirection(enum PlayerDirection direction);
void updateSwitches();
void drawSprites();
void flipPlayer();

struct Player player;
bool wasColorPushed;

void main() 
{
	init();

	while (1) 
	{
		checkInput();
		drawSprites();
		updateSwitches();
		wait_vbl_done();
	}
}

void init() 
{
	DISPLAY_ON;

	set_sprite_data(0, 32, player_sprite_sheet);

	player.direction = Down;
	player.color = White;
	player.position[0] = 80;
	player.position[1] = 72;
	player.lastPosition[0] = 0;
	player.lastPosition[1] = 0;

	wasColorPushed = false;

	setPlayerTile();
}

void setPlayerTile()
{
	if (player.color == White)
	{
		switch (player.direction)
		{
			case Up:
				memcpy(player.playerTile, player_white_up_tile, sizeof player.playerTile);
				break;
			case Right:
				memcpy(player.playerTile, player_white_right_tile, sizeof player.playerTile);
				break;
			case Down:
				memcpy(player.playerTile, player_white_down_tile, sizeof player.playerTile);
				break;
			case Left:
				memcpy(player.playerTile, player_white_left_tile, sizeof player.playerTile);
				break;
		}
	}
	else
	{
		switch (player.direction)
		{
			case Up:
				memcpy(player.playerTile, player_black_up_tile, sizeof player.playerTile);
				break;
			case Right:
				memcpy(player.playerTile, player_black_right_tile, sizeof player.playerTile);
				break;
			case Down:
				memcpy(player.playerTile, player_black_down_tile, sizeof player.playerTile);
				break;
			case Left:
				memcpy(player.playerTile, player_black_left_tile, sizeof player.playerTile);
				break;
		}
	}

	set_sprite_tile(0, player.playerTile[0]);
	set_sprite_tile(1, player.playerTile[1]);
	set_sprite_tile(2, player.playerTile[2]);
	set_sprite_tile(3, player.playerTile[3]);
}

void checkInput() 
{
	if (joypad() & J_A )
	{
		if (wasColorPushed == false)
		{
			flipPlayer();
			wasColorPushed = true;
		}
	}
	else
	{
		wasColorPushed = false;
	}

	if (joypad() & J_UP && player.position[1] > 16) 
	{
		player.position[1]--;
		updatePlayerDirection(Up);
	}

	if (joypad() & J_DOWN && player.position[1] < 136) 
	{
		player.position[1]++;
		updatePlayerDirection(Down);
	}

	if (joypad() & J_LEFT && player.position[0] > 8) 
	{
		player.position[0]--;
		updatePlayerDirection(Left);
	}	
	
	if (joypad() & J_RIGHT && player.position[0] < 152) 
	{
		player.position[0]++;
		updatePlayerDirection(Right);
	}
}

void updatePlayerDirection(enum PlayerDirection direction)
{
	if (player.direction != direction)
	{
		player.direction = direction;
		setPlayerTile();
	}
}

void drawSprites()
{
	if (player.position[0] != player.lastPosition[0] || player.position[1] != player.lastPosition[1])
	{
		move_sprite(0, player.position[0], player.position[1]);
		move_sprite(1, player.position[0] + 8, player.position[1]);
		move_sprite(2, player.position[0], player.position[1] + 8);
		move_sprite(3, player.position[0] + 8, player.position[1] + 8);

		player.lastPosition[0] = player.position[0];
		player.lastPosition[1] = player.position[1];
	}
}

void flipPlayer()
{
	if (player.color == Black)
	{
		player.color = White;
	}
	else
	{
		player.color = Black;
	}

	setPlayerTile();
}

void updateSwitches() 
{
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

