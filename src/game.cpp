#include "../include/game.h"
// MAIN FUNC
void game::run(){
    init();
    while (gameRunning){
        update();
        render();
    }
}
// INIT FUNCS
void game::init(){
    initVariables();
    initWindow();
}
void game::initVariables(){
    gameRunning = true;
}
void game::initWindow(){
    window = new sf::RenderWindow(window_WH,"Game of Life - SFML");
}
// UPDATE FUNCS
void game::update(){
    updateEvent();
}
void game::updateEvent(){
    sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                {
                     window->close();
                     gameRunning = false;
                }
               
        }
}
// RENDER FUNCS
void game::render(){
    window->clear();
    window->display();
}
void game::test(){
    initGride();
    while (true)
    {
        updateGride();
        renderGride();
    }
}

void game::renderGride(){
    sf::sleep(sf::seconds(0.5));
    system("clear");
    for (size_t i = 0; i < gride_height; ++i){
            for (size_t l = 0; l < gride_width; ++l){
                    std::cout << gride[i][l];
                }
            std::cout << "\n";
        }
}
void game::initGride(){
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    for (size_t i = 0; i < gride_height; ++i){
            for (size_t l = 0; l < gride_height; ++l){
                    int temp = rand () % 2;
                        if (temp == 0){
                                gride[i][l] = cell_dead;
                            }else if (temp == 1){
                                gride[i][l] = cell_alive;
                            }

                }
            std::cout << "\n";
        }
}
void game::updateGride(){
    for (size_t i = 0; i < gride_height; i++){
        for (size_t l = 0; l < gride_width; l++){
            if (cell_isAlive(i,l)){
                if (underpopulation(i,l))
                    gride[i][l] = cell_dead;
                else if (survival(i,l))
                    gride[i][l] = cell_alive;
                else if (overcrowding(i,l))
                    gride[i][l] = cell_dead;
            }else if (!cell_isAlive(i,l)){
                if (reproduction(i,l)){
                    gride[i][l] = cell_alive;
                }
            }
        }
    }
}
   
bool game::underpopulation(int x, int y){

    if (neighbors_alive(x,y) < 2)
        return true;

    return false;
}
bool game::survival(int x, int y){
    if (neighbors_alive(x,y) == 2 or neighbors_alive(x,y) == 3)
        return true;

    return false;
}
bool game::overcrowding(int x, int y){
    if (neighbors_alive(x,y) > 3)
        return true;

    return false;
}
bool game::reproduction(int x, int y){
    if (neighbors_alive(x,y) == 3)
        return true;

    return false;
}
bool game::cell_isAlive(int x, int y){
    if (gride[x][y] == cell_alive)
        return true;

    return false;
}
int game::neighbors_alive(int x, int y) {
    int temp = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < gride_height && ny >= 0 && ny < gride_width) {
                if (cell_isAlive(nx, ny)) {
                    temp++;
                }
            }
        }
    }
    return temp;
}
