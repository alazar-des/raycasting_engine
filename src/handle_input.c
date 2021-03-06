#include "handle_input.h"

/**
 * keyUp - set 0 when key up event occured
 * @event: SDL struct that holds event information
 */
void keyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

/**
 * keyDown - set 1 when key down event occured
 * @event: SDL struct that holds event information
 */
void keyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
}

/**
 * handleInput - handle input.
 */
void handleInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			keyDown(&event.key);
			break;
		case SDL_KEYUP:
			keyUp(&event.key);
			break;
		default:
			break;
		}
	}
}

/**
 * playerPos - handle keyboard event. set player position depending on keyboard
 * event.
 */
void playerPos(void)
{
	double dx = 0, dy = 0;

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player.dir -= PLAYER_ROT_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player.dir += PLAYER_ROT_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_UP])
	{
		dx = PLAYER_SPEED * cos(player.dir);
		dy = PLAYER_SPEED * sin(player.dir);
		if (Map.map[(int) (player.y + dy)][(int) (player.x + dx)] == 0
		|| Map.map[(int) (player.y + dy)][(int) (player.x + dx)] >= 10)
	{
		player.x += dx;
		player.y += dy;
	}
	}

	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		dx = -PLAYER_SPEED * cos(player.dir);
		dy = -PLAYER_SPEED * sin(player.dir);
		if (Map.map[(int) (player.y + dy)][(int) (player.x + dx)] == 0
		|| Map.map[(int) (player.y + dy)][(int) (player.x + dx)] >= 10)
	{
		player.x += dx;
		player.y += dy;
	}
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL])
	{
		if (player.gunTime <= 0)
		{
			++player.numGun;
			player.numGun = player.numGun % 3;
			player.gunTime = 10;
		}
	}

	if (app.keyboard[SDL_SCANCODE_RCTRL])
	{
		if (Map.mapTime <= 0)
		{
			Map.disp = !Map.disp;
			Map.mapTime = 10;
		}
	}
}

/**
 * input - handles keyboard event.
 */
void input(void)
{
	handleInput();
	playerPos();
}
