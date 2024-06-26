#include "../include/game.h"
// MAIN FUNC
void game::run(){
    init();
    while (gameRunning){
         if (gameStarted){
                runGameStarted();
        }else{
                runGameNotStarted();
        }}
}
void game::runGameStarted(){
        text1.setString("Press 'p' to pause - Press 'c' to clear ");
        sf::sleep(sf::seconds(0.3));
        update();
        render();
    }
void game::runGameNotStarted(){
    text1.setString("Press 'p' to start - Press 'c' to clear ");
        updateEvent();
        updateCells();
        render();
}
// INIT FUNCS
game::~game() {
    if (cells != nullptr) {
        for (auto& cell : *cells) {
            delete cell.sprite;
        }
        delete cells;
    }
    if (window != nullptr) {
        delete window;
    }
}
void game::init(){
    initVariables();
    initText();
    initWindow();
    initGride();
    initCells();
}
void game::initVariables(){
    gameRunning = true;
    gameStarted = false;
    cells = new std::vector<cell>();
}
void game::initWindow(){
    window = new sf::RenderWindow(window_WH,"Game of Life - SFML", sf::Style::Close);
}
void game::initCells(){
    for (size_t i = 0; i < get_WindowSize().x/cell_width; i++)
        {
                for (size_t l = 0; l < 600/cell_height;l++)
                {
                    cell temp_cell;
                    temp_cell.sprite = new sf::RectangleShape (sf::Vector2f(cell_width, cell_height));
                    temp_cell.sprite->setPosition(sf::Vector2f(cell_width*i, cell_height*l));
                    temp_cell.sprite->setOutlineThickness(1);
                    temp_cell.sprite->setOutlineColor(BLACK);
                    if (gride[i][l] == cell_dead){
                            temp_cell.sprite->setFillColor(WHITE);
                            temp_cell.state = dead;
                        }else{
                            temp_cell.sprite->setFillColor(BLACK);
                            temp_cell.state = alive;
                        }
                    temp_cell.x = i;
                    temp_cell.y = l;
                    cells->push_back(temp_cell);
                }
        }
}
void game::initFont(){
    if (font.loadFromFile("/home/joao/Dev/cpp/TICTACTOE/fonts/JetBrainsMono-Bold-Italic.ttf")){
        std::cout << "Failed to load from file";
    }
}
void game::initText(){
    initFont();
    text1.setFont(font);
    text1.setPosition(textPos);
    text1.setCharacterSize(24);
    text1.setFillColor(WHITE);
}
// UPDATE FUNCS
void game::update(){
    updateEvent();
    updateGride();
    updateCells();
}
void game::updateEvent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            gameRunning = false;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                gameStarted = !gameStarted; 
                text1.setString(gameStarted ? "Press 'p' to resume" : "Press 'p' to pause");
            }
            if (event.key.code == sf::Keyboard::C)
                clearGrid();
        }
        if (!gameStarted) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x / cell_width;
                    int y = event.mouseButton.y / cell_height;
                    updateClick(x, y);
                }
            }
        } else {

        }
    }
}

void game::updateCells() {
    for (size_t i = 0; i < gride_width; i++) {
        for (size_t j = 0; j < gride_height; j++) {
            if (gride[i][j] == cell_dead) {
                int index = returnIndex(i, j);
                if (index != -1) {
                    cells->at(index).sprite->setFillColor(WHITE);
                    cells->at(index).sprite->setOutlineColor(BLACK);
                    cells->at(index).state = cell_dead;
                }
            } else if (gride[i][j] == cell_alive) {
                int index = returnIndex(i, j);
                if (index != -1) {
                    cells->at(index).sprite->setFillColor(BLACK);
                    cells->at(index).sprite->setOutlineColor(WHITE);
                    cells->at(index).state = cell_alive;
                }
            }
        }
    }
}


void game::updateClick(int x, int y){
 if (x >= 0 && x < gride_width && y >= 0 && y < gride_height) {
    // DEBUGING
        if (!cell_isAlive(x,y)){
            // std::cout << "Changing cell at position " << x << ", " << y << " from dead to alive\n";
            // std::cout << "\nCell at position " << x << ", " << y << "has " << neighbors_alive(x,y) << "\n";

            //     if (neighbors_alive(x,y) == 3){
            //         std::cout << "\nReprodution()";
            //     }
            gride[x][y] = cell_alive;
        } else if (cell_isAlive(x,y)){
            // std::cout << "Changing cell at position " << x << ", " << y << " from alive to dead\n";
            // std::cout << "\nCell at position " << x << ", " << y << " has " << neighbors_alive(x,y) << "\n";

            gride[x][y] = cell_dead;
        }
    } else {
        // std::cerr << "Error: Clicked position (" << x << ", " << y << ") is out of bounds!" << std::endl;
    }
    // std::cout << "\nGride at position " << x << ", " << y << " is " << gride[x][y] << "\n";
    // renderGride();
}
// RENDER FUNCS
void game::render(){
    window->clear();
    // renderGride();
    renderGrid();
    renderText();
    window->display();
}
void game::renderGrid() {
    for (size_t i = 0; i < gride_width; ++i) {
        for (size_t j = 0; j < gride_height; ++j) {
            int index = returnIndex(i,j); 
            if (index != -1) { 
                cells->at(index).sprite->setPosition(sf::Vector2f(i * cell_width, j * cell_height));
                window->draw(*cells->at(index).sprite); 
            }
        }
    }
}
void game::renderText(){
    window->draw(text1);
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
void game::renderGride() {
    system("clear");
    for (size_t j = 0; j < gride_height; ++j) {
        for (size_t i = 0; i < gride_width; ++i) {
            std::cout << gride[i][j];
        }
        std::cout << "\n";
    }
}

void game::initGride(){
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    for (size_t i = 0; i < gride_width; ++i){
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
    // gride[0][0] = cell_alive;
}
void game::updateGride() {
    char newGride[gride_width][gride_height]; 

    for (size_t i = 0; i < gride_width; i++) {
        for (size_t j = 0; j < gride_height; j++) {
            int aliveNeighbors = neighbors_alive(i, j);

            if (cell_isAlive(i, j)) {
                if (underpopulation(aliveNeighbors))
                    newGride[i][j] = cell_dead;
                else if (overcrowding(aliveNeighbors))
                    newGride[i][j] = cell_dead;
                else
                    newGride[i][j] = cell_alive;
            } else {
                if (reproduction(aliveNeighbors))
                    newGride[i][j] = cell_alive;
                else
                    newGride[i][j] = cell_dead;
            }
        }
    }

    for (size_t i = 0; i < gride_width; i++) {
        for (size_t j = 0; j < gride_height; j++) {
            gride[i][j] = newGride[i][j];
        }
    }
}

   
bool game::underpopulation(int aliveNeighbors) {
    return aliveNeighbors < 2;
}

bool game::overcrowding(int aliveNeighbors) {
    return aliveNeighbors > 3;
}

bool game::reproduction(int aliveNeighbors) {
    return aliveNeighbors == 3;
}

bool game::cell_isAlive(int x, int y){
    if (gride[x][y] == cell_alive){
        return true;
    }
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
            if (nx >= 0 && nx < gride_width && ny >= 0 && ny < gride_height) {
                if (cell_isAlive(nx, ny)) {
                    temp++;
                }
            }
        }
    }
    return temp;
}
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
    return -1;
}
void game::clearGrid(){
        for (size_t i = 0; i < gride_width; i++){
             for (size_t l = 0; l < gride_height; l++){
                gride[i][l] = cell_dead;

             }}
}