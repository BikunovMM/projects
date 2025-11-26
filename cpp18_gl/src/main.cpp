#include "main.hpp"

int main(int argc, char *argv[])
{
	Game game(640, 480);
	int res = 0;

	res = game.init();
	if (res < 0) {
		fprintf(stderr, "Failed to Game::init.\n");
		return -1;
	}

	res = game.run_render_loop();
	if (res < 0) {
		fprintf(stderr, "Failed to Game::run_render_loop.\n");
		return -1;
	}

	//game.end(); --Deleted method ( by myself :) )

	return 0;
}