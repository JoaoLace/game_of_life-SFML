#include "mylib.h"

class game{
public:
    void run();
    void test();
private:
    sf::RenderWindow *window;
    bool gameRunning;

    void init();
    void initVariables();
    void initWindow();

    void update();
    void updateEvent();
    
    void render();

    char gride[10][10];
    // '*' -> alive
    // ' ' -> dead
    void renderGride();
    void initGride();
    void updateGride();

    bool underpopulation(int x, int y);
    bool survival(int x, int y);
    bool overcrowding(int x, int y);
    bool reproduction(int x, int y);
    bool cell_isAlive(int x, int y);

    int neighbors_alive(int x, int y);
};