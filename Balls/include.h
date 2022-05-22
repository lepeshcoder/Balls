#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include<vector>
#include<stack>
#include<fstream>
#include<iostream>
#include<cmath>

using namespace sf;

#define GAME_SPEED 800
#define BALL_RADIUS 20
#define FRICTION 0.0002
#define MAX_CUE_POWER 2


const double PI = 3.141592653589793;

enum GameStates
{
	
	START = 0
};



