#include "App.h"
#include "common.h"

#include <iostream>

App::App()
: leszek({ 784,128,10 })
, canvas(GRID_SIZE, GRID_SIZE)
, running(false)
, isMouseClicked(false)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
    }

	window = SDL_CreateWindow("Leszek", WINDOW_SIZE, WINDOW_SIZE, 0);

    if (!window)
    {
        std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    leszek.loadFromFile("../weights.txt");
}

App::~App()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::run()
{
    running = true;

    while (running)
    {
        handleEvents();
        update();
        draw();
    }
}

void App::handleEvents()
{
    SDL_Event event;

    isResetClicked = false;
    isGuessClicked = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            running = false;
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            isMouseClicked = true;
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            isMouseClicked = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_R || event.key.key == SDLK_DELETE || event.key.key == SDLK_BACKSPACE)
            {
                isResetClicked = true;
            }
            else if (event.key.key == SDLK_RETURN)
            {
                isGuessClicked = true;
            }
        }
    }
}

void App::update()
{
    if (isMouseClicked)
    {
        float mouseX, mouseY;
        int cellCol, cellRow;
        SDL_GetMouseState(&mouseX, &mouseY);
        
        cellCol = mouseX / CELL_SIZE;
        cellRow = mouseY / CELL_SIZE;
        

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int targetRow = cellRow + i;
                int targetCol = cellCol + j;

                if(targetRow < 0 || targetCol < 0 || targetRow >= GRID_SIZE || targetCol >= GRID_SIZE) continue;
                    
                if (i == 0 && j == 0)
                {
                    canvas.at(targetRow, targetCol) = std::max(canvas.at(targetRow, targetCol), 1.0);
                }
                else if (i == 0 && j != 0)
                {
                    canvas.at(targetRow, targetCol) = std::max(canvas.at(targetRow, targetCol), 0.5);
                }
                else if (j == 0 && i != 0)
                {
                    canvas.at(targetRow, targetCol) = std::max(canvas.at(targetRow, targetCol), 0.5);
                }
                else if (i != 0 && j != 0)
                {
                    canvas.at(targetRow, targetCol) = std::max(canvas.at(targetRow, targetCol), 0.3);
                }
            }
        }
    }

    if (isGuessClicked)
    {
        Matrix input(784, 1);
        for (int i = 0; i < canvas.data.size(); i++)
        {
            input.at(i, 0) = canvas.data[i];
        }

        Matrix output = leszek.forward(input);
        
        for (int i = 0; i < output.data.size(); i++)
        {
            std::cout << i << ": " << output.data[i] * 100 << "%\n";
        }
        std::cout << "\n";
    }

    if (isResetClicked)
    {
        canvas.zero();
    }

    


}

void App::draw()
{
    SDL_RenderClear(renderer);

    SDL_FRect rect;
    rect.w = CELL_SIZE;
    rect.h = CELL_SIZE;

    for (int i = 0; i < canvas.rows; i++)
    {
        for (int j = 0; j < canvas.cols; j++)
        {
            rect.x = CELL_SIZE * j;
            rect.y = CELL_SIZE * i;

            Uint8 colorValue = static_cast<Uint8>(canvas.at(i, j) * 255);
            SDL_SetRenderDrawColor(renderer, colorValue, colorValue, colorValue, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    
    SDL_RenderPresent(renderer);
}