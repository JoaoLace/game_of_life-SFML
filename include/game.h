#include "mylib.h"
typedef struct{
    sf::RectangleShape *sprite;
    bool state;
    int x;
    int y;
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

    char gride[gride_width][gride_height];

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

    int returnIndex(int x, int y);

    sf::Vector2u get_WindowSize();
};


