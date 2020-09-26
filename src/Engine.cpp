#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Engine.h"
#include "EventSystem.h"
#include "PhysicsEngine.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "SceneSystem.h"

SDL_Window *Engine::window = nullptr;

void Engine::Init(const EngineConfig &config)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.window_width, config.window_height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    RenderSystem::background = SDL_GetWindowSurface(window);
    std::srand(std::time(nullptr));

    if (config.icon_path != "") {
        auto *icon = SDL_LoadBMP(config.icon_path.c_str());
        SDL_SetWindowIcon(Engine::window, icon);
    }
}

void Engine::Start()
{
    while (!EventSystem::exit) {
        EventSystem::Process();
        PhysicsEngine::Tick();
        SceneSystem::Tick();
        RenderSystem::Draw();
    }

    End();
}

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
