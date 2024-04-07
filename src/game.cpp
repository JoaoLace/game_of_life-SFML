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
