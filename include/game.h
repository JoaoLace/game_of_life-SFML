#include "mylib.h"

class game{
public:
    void run();
private:
    sf::RenderWindow *window;
    bool gameRunning;

    void init();
    void initVariables();
    void initWindow();

    void update();
    void updateEvent();

    
    void render();
};