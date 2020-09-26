#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include "Engine.h"
#include "EventSystem.h"
#include "PhysicsEngine.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "SceneSystem.h"

SDL_Window *Engine::window = nullptr;
EngineConfig *Engine::config;

bool paused = false;

void Engine::Init(EngineConfig *config)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(config->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config->window_width, config->window_height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    RenderSystem::background = SDL_GetWindowSurface(window);
    std::srand(std::time(nullptr));

    if (config->icon_path != "") {
        auto *icon = SDL_LoadBMP(config->icon_path.c_str());
        SDL_SetWindowIcon(Engine::window, icon);
    }

    Engine::config = config;
}

void DebugLoop()
{
    std::string command;

    while (!EventSystem::exit) {
        std::cout << ">>> ";
        std::cin >> command;

        if (command == "pause") {
            if (paused) {
                std::cout << "Error: Engine already paused!" << std::endl;
                continue;
            }
            paused = true;
            std::cout << "Engine Paused!" << std::endl;
        } 
        else if (command == "play") {
            if (!paused) {
                std::cout << "Error: Engine is not currently paused!" << std::endl;
                continue;
            }
            SceneSystem::Synchronize();
            paused = false;
            std::cout << "Engine Resumed!" << std::endl;
        } 
        else if (command == "exit") {
            EventSystem::exit = true;
            paused = false;
        }
        else {
            std::cout << "Error: command '" << command << "' not recognized!" << std::endl;
        }
    }
}

void Engine::Start()
{
    std::thread *thread;

    if (config->debug) {
        thread = new std::thread(DebugLoop);
    }

    while (!EventSystem::exit) {
        EventSystem::Process();
        PhysicsEngine::Tick();
        SceneSystem::Tick();
        RenderSystem::Draw();
        while (paused);
    }

    Engine::End();

    if (thread != nullptr) {
        thread->join();
    }
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
