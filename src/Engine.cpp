#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Engine.h"
#include "EventSystem.h"
#include "RenderSystem.h"
#include "SceneSystem.h"

SDL_Window *Engine::window = nullptr;

// Initializes the engine and begins the game loop.
void Engine::Start(const std::string &title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    RenderSystem::background = SDL_GetWindowSurface(window);
    std::srand(std::time(nullptr));

    while (!EventSystem::exit) {
        EventSystem::Process();
        SceneSystem::Tick();
        RenderSystem::Draw();
    }

    End();
}

// Cleans up any engine allocated memory and exits the engine.
void Engine::End()
{
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_FreeSurface(surface);
    
    SDL_DestroyWindow(window);

    surface = nullptr;
    window = nullptr;
    RenderSystem::background = nullptr;

    SDL_Quit();
}
