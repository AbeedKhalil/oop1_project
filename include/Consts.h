#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <conio.h>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

// Constants for game settings
constexpr int MAX_LEVELS = 4;
constexpr int TILE_SIZE = 60;

// Game characters and elements
constexpr char WALL = '#';
constexpr char CHEESE = '*';
constexpr char GIFT = '$';
constexpr char DOOR = 'D';
constexpr char KEY = 'F';
constexpr char MOUSE = '%';
constexpr char CAT = '^';
constexpr char PASS = ' ';

//GameState enum to manage different game states
enum class GameState {
    MainMenu,
    InGame,
    Help,
    Paused,
    Exiting
};