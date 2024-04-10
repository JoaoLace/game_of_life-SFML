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
game::~game(){
    if (!cells->empty())
        {
             delete cells;
        }
}
void game::init(){
    initVariables();
    initWindow();
    initGride();
    initCells();
}
void game::initVariables(){
    gameRunning = true;
    cells = new std::vector<cell>();
}
void game::initWindow(){
    window = new sf::RenderWindow(window_WH,"Game of Life - SFML");
}
void game::initCells(){
    for (size_t i = 0; i < get_WindowSize().x/cell_width; i++)
        {
                for (size_t l = 0; l < get_WindowSize().y/cell_height;l++)
                {
                    cell temp_cell;
                    temp_cell.sprite = new sf::RectangleShape (sf::Vector2f(cell_width, cell_height));
                    temp_cell.sprite->setPosition(sf::Vector2f(cell_width*i, cell_height*l));
                    if (rand() % 2 == DEAD){
                            temp_cell.sprite->setFillColor(BLACK);
                            temp_cell.state = dead;
                        }else{
                            temp_cell.sprite->setFillColor(WHITE);
                            temp_cell.state = alive;
                        }
                    temp_cell.x = i;
                    temp_cell.y = l;
                    cells->push_back(temp_cell);
                }
        }
}
// UPDATE FUNCS
void game::update(){
    updateEvent();
    updateGride();
    updateCells();
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
void game::updateCells() {
    // for (size_t i = 0; i < cells->size(); i++) {
    //     cell &currentCell = cells->at(i);
    //     int x = i % (get_WindowSize().x / cell_width); 
    //     int y = i / (get_WindowSize().y / cell_height);

    //     int aliveNeighbors = neighbors_aliveCell(x, y);

    //     if (currentCell.state == alive) {
    //         if (aliveNeighbors < 2){
    //             currentCell.state = dead;
    //             currentCell.sprite->setFillColor(BLACK);
    //         }
    //         else if (aliveNeighbors == 2 or aliveNeighbors == 3){
    //             currentCell.state = alive;
    //             currentCell.sprite->setFillColor(WHITE);
    //         }
    //         else if (aliveNeighbors > 3){
    //             currentCell.state = dead;
    //             currentCell.sprite->setFillColor(BLACK);
    //         }
    //     } else {
    //         if (aliveNeighbors == 3){
    //             currentCell.state = alive;
    //             currentCell.sprite->setFillColor(WHITE);
    //         }
    //     }
    // }
    int index = 0;
    for (size_t i = 0; i < gride_height; i++){
        for (size_t l = 0; l < gride_width; l++){
            if (gride[i][l] == ' '){
                cells->at(index).sprite->setFillColor(BLACK);
                cells->at(index).state = cell_dead;
            }else if (gride[i][l] == '*'){
                cells->at(index).sprite->setFillColor(WHITE);
                cells->at(index).state = cell_alive;
            }
            index++;
        }
    }
}

// RENDER FUNCS
void game::render(){
    window->clear();
    renderGride();
    renderGrid();
    window->display();
}
void game::renderGrid(){
    for (auto &x : *cells)
        {
            window->draw(*x.sprite);
        }
}
// LOGIC FUNCS
void game::test(){
    initGride();
    while (true)
    {
        updateGride();
        renderGride();
    }
}
void game::renderGride(){
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
            for (size_t l = 0; l < gride_width; ++l){
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
// int game::neighbors_aliveCell(int x, int y) {
//     int temp = 0;
//     for (int dx = -1; dx <= 1; ++dx) {
//         for (int dy = -1; dy <= 1; ++dy) {
//             if (dx == 0 && dy == 0) {
//                 continue;
//             }
//             int nx = x + dx;
//             int ny = y + dy;
//             if (nx >= 0 && nx < x && ny >= 0 && ny < y) {
//                 if (cells->at(nx * (get_WindowSize().x / cell_width) + ny).state == alive) {
//                     temp++;
//                 }
//             }
//         }
//     }
//     return temp;
// }


// OTHERS  FUNCS
sf::Vector2u game::get_WindowSize(){
    return window->getSize();
}

int game::returnIndex(int x, int y){
    int count = 0;
    for (auto &temp : *cells){
        if (temp.x == x and temp.y == y)
            return count;
        
        count++;
    }
    return NULL;
}