#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <time.h>
#include <vector>

// Consts
#define WIDTH 800
#define HEIGHT 600
#define BLACK sf::Color::Black
#define WHITE sf::Color::White
#define DEAD 0
#define ALIVE 1
#define window_WH sf::VideoMode(WIDTH,HEIGHT)
#define cell_alive '*'
#define cell_dead ' '
#define gride_width 800/40
#define gride_height 600/40
#define cell_width 40
#define cell_height 40
#define alive true
#define dead false
