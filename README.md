# System
    Ubuntu Linux x64
# Compile
    sudo make
# Dependencies
    SFML 
    gcc
    make
# Description
    The Game of Life, created by mathematician John Conway in 1970, is a cellular automaton, which is a mathematical model that consists of a grid of cells that evolve over discrete time steps based on a set of rules. Despite its name, it's not a game in the traditional sense with players and objectives, but rather a simulation governed by simple rules.

    In the Game of Life, each cell can be in one of two possible states: alive or dead. The game is played on a two-dimensional grid, where each cell interacts with its adjacent neighbors. The rules for the evolution of the grid from one generation to the next are as follows:
# Underpopulation: 
    If a live cell has fewer than two live neighbors, it dies due to loneliness.
# Survival: 
    If a live cell has two or three live neighbors, it survives to the next generation.
# Overcrowding: 
    If a live cell has more than three live neighbors, it dies due to overcrowding.
# Reproduction: 
    If a dead cell has exactly three live neighbors, it becomes alive in the next generation, simulating reproduction.
# Result
    These rules are applied simultaneously to all cells in the grid, creating successive generations of cells. This leads to various interesting patterns and behaviors, including stable patterns, oscillators, gliders, and even complex structures like spaceships.

    The Game of Life is not only of interest for its simplicity and unpredictability but also because it demonstrates emergent complexity. Even though the rules are straightforward, they can give rise to intricate and fascinating patterns that seem to exhibit life-like behavior, hence the name "Game of Life." It has applications in various fields, including computer science, biology, and artificial life research, serving as a rich source of study for complex systems and emergent phenomena.

    This project tries to apply the game of life idea with cpp and SFML.
# Observations
    You gonna have to change this to any font that you have (the location of it): 
        void game::initFont(){
             if (font.loadFromFile("/home/joao/Dev/cpp/TICTACTOE/fonts/JetBrainsMono-Bold-Italic.ttf"));
            }
        game.cpp line 53

    I have no idea of why the program gives segmentation fault when its closed