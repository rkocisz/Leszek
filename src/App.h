#include "Matrix.h"
#include "NeuralNetwork.h"

#include <SDL3/SDL.h>

class App
{
public:
    App();                    
    ~App();                   
    void run();                

private:
    void handleEvents();      
    void update();            
    void draw();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Matrix canvas;
    NeuralNetwork leszek;

    bool isMouseClicked;
    bool isResetClicked;
    bool isGuessClicked;

};