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

    void runGameNotStarted();
    void runGameStarted();

    void init();
    void initVariables();
    void initWindow();
    void initCells();
    void initText();
    void initFont();
    

    void update();
    void updateEvent();
    void updateCells();
    
    void render();
    void renderGrid();
    void renderText();

    char gride[20][15];

    void renderGride();
    void initGride();
    void updateGride();
    void updateClick(int x, int y);

    bool underpopulation(int x, int y);
    bool survival(int x, int y);
    bool overcrowding(int x, int y);
    bool reproduction(int x, int y);
    bool cell_isAlive(int x, int y);
    bool gameStarted;

    int neighbors_alive(int x, int y);
    int neighbors_aliveCell(int x, int y);

    std::vector<cell> *cells;

    int returnIndex(int x, int y);

    sf::Vector2u get_WindowSize();

    sf::Font font;
    sf::Text text1;
    sf::Text text2;

    void clearGrid();
};


