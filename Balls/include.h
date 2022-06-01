#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace sf;

#define GAME_SPEED 800
#define BALL_RADIUS 20
#define FRICTION 0.0001
#define MAX_CUE_POWER 2
#define LINE std::pair<Vector2f,Vector2f>


const double PI = 3.141592653589793;

enum PACKET_TYPES {
 SERVER_CONNECT = 0, SERVER_PREPARE, SERVER_HIT, SERVER_RESETMAINBALL, SERVER_END
};

enum GameStates
{
	START = 0, CONNECT, PREPARE, HIT_PHASE, MAINBALL_RESET, END
};

enum Hit {
	MY_HIT = 0, OPPONENT_HIT
};

enum Direction {
	CLOCKWISE = 0, COUNTERCLOCKWISE
};



