#pragma once

//setup SDL
#include <SDL.h>
#include "Texture.h"
#include "Animation.h"

struct CharacterAnimations {
	Animation* idle;
	Animation* attack;
	Animation* run;
	Animation* die;
	Animation* jump;
};

class Game
{
public:
	//constructor
	Game();
	//deconstructor
	~Game();

private:
	//window for rendering
	SDL_Window* sdlWindow;
	//2D Renderer
	SDL_Renderer* sdlRenderer;
	//flag for the game loop
	bool bIsGameOver;
	
	//player texture
	Texture* playerTexture;
	CharacterAnimations playerAnims;

	//how long since last update
	unsigned int lastUpdatedTime;

public:

	//create the renderer
	//allocate any objects we want

	bool Start();

	//handle inputs from player
	void ProcessInput();


	//run on every tick
	void Update();
	
	//draw the game images to screen
	void Draw();


	//Create game window and run
	//@ param 1 - title for the window
	//@ param 2 - width for the window
	//@ param 3 - height for the window
	//@ param 4 - if we are fullscreen or not
	void Run(const char* title, int width, int height, bool fullscreen);

	//dealocate objects from memory
	void Shutdown();

	//Shutdown SDL framework & delete renderer from memory
	void Destroy();
};

