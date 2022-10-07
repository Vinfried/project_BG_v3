#include "Game.h"
#include <iostream>

using namespace std;

//constructor
Game::Game()
{
	//set the SDL Window and Renderer to null in case it has memory
	sdlWindow = nullptr;
	sdlRenderer = nullptr;

	//Initialise the subsystem in the SDL2 Framework
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {

		bIsGameOver = true;
		//if failed to initialise the subsystem, tell us on console
		cout << "Initialise SDL - failed" << endl;
	}
	else {
		//enable game loop
		bIsGameOver = false;
		//if the subsystem succesfully initialises
		cout << "initialise SDL - success" << endl;
	}

}

//deconstructor
Game::~Game()
{

}

bool Game::Start()
{
	// create the SDL renderer and define it
	sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, -1);

	lastUpdatedTime = SDL_GetTicks();
	
	//make sure the renderer worked
	if (sdlRenderer != nullptr) {
		cout << "Create Renderer - success" << endl;

		//initialise texture
		playerTexture = new Texture();
		//load the texture
		if (playerTexture->loadImageFromFile("Assets/hero_spritesheet_50x37_109.png", sdlRenderer)) {
			cout << " Player Texture - success" << endl;

			//player animations
			playerAnims.attack = new Animation(playerTexture, 109, 40.0f, 0, 12);
			playerAnims.idle = new Animation(playerTexture, 109, 40.0f, 65, 68);
			playerAnims.run = new Animation(playerTexture, 109, 40.0f, 84, 89);
			playerAnims.die = new Animation(playerTexture, 109, 40.0f, 53, 59);
			playerAnims.jump = new Animation(playerTexture, 109, 40.0f, 76, 79);
		}
		else {
			cout << "Player Texture - failed" << endl;
			return false;
		}

		return true;
	}
	
	cout << "Create Renderer - failed" << endl;

	return false;
}

void Game::ProcessInput()
{
	//Process player input
}

void Game::Update()
{
	//Process any changes to the game
	//int seconds = SDL_GetTicks() / 1000;

	//how long has it been since the last frame updated in milliseconds
	unsigned int tick = SDL_GetTicks() - lastUpdatedTime;

	//change the tick to seconds
	float deltaTime = tick / 1000.0f;

	//Refresh the last update time
	lastUpdatedTime + SDL_GetTicks();

	//add anything that needs deltaTime
	playerAnims.attack->update(deltaTime);
	playerAnims.idle->update(deltaTime);
	playerAnims.run->update(deltaTime);
	playerAnims.die->update(deltaTime);
	playerAnims.jump->update(deltaTime);
}

void Game::Draw()
{
	//set the draw color
	SDL_SetRenderDrawColor(sdlRenderer, 15, 15, 15, 255);

	//clear the renderer
	SDL_RenderClear(sdlRenderer);

	//Draw player texture here
	playerAnims.attack->draw(sdlRenderer, 50, 50, 4);
	playerAnims.idle->draw(sdlRenderer, 400, 50, 4, true);
	playerAnims.run->draw(sdlRenderer, 50, 200, 2);
	playerAnims.die->draw(sdlRenderer, 450, 200,1, true);
	playerAnims.jump->draw(sdlRenderer, 600, 200, 5, true);

	SDL_RenderPresent(sdlRenderer);
}

void Game::Run(const char* title, int width, int height, bool fullscreen)
{
	//define the creation flag
	int creationFlag = 0;

	//if fullscreen is set to false then set to window mode
	if (!fullscreen) {
		creationFlag = SDL_WINDOW_SHOWN;

	}

	else {
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}

	sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, creationFlag);

	//check if the SDL window work
	////create the renderer and start game loop
	if (sdlWindow != nullptr && Start()) {
		cout << "Create window - success" << endl;

		//run the loop
		while (!bIsGameOver) {
			//check for the player input
			ProcessInput();

			//process any changes that were made either by input or game code
			Update();

			//draw everything to screen
			Draw();

		}
	}

	//debug or was exited
	cout << "Create Window - failed or was exited" << endl;

	Shutdown();
	Destroy();


}

void Game::Shutdown()
{
}

void Game::Destroy()
{
	//dealocate the window
	SDL_DestroyWindow(sdlWindow);

	//dealocate the renderer
	SDL_DestroyRenderer(sdlRenderer);

	//shutdown the SDL framework
	SDL_Quit();

}
