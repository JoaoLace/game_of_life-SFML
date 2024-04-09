#include "mylib.h"
typedef struct{
    sf::RectangleShape *sprite;
    bool state;
}cell;
class game{
public:
    void run();
    void test();
    ~game();
private:
    sf::RenderWindow *window;
    bool gameRunning;

    void init();
    void initVariables();
    void initWindow();
    void initCells();
    

    void update();
    void updateEvent();
    void updateCells();
    
    void render();
    void renderGrid();

    char gride[10][10];

    void renderGride();
    void initGride();
    void updateGride();

    bool underpopulation(int x, int y);
    bool survival(int x, int y);
    bool overcrowding(int x, int y);
    bool reproduction(int x, int y);
    bool cell_isAlive(int x, int y);

    int neighbors_alive(int x, int y);
    int neighbors_aliveCell(int x, int y);

    std::vector<cell> *cells;

    sf::Vector2u get_WindowSize();
};


