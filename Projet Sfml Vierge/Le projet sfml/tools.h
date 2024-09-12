#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "SFML/Graphics.hpp"
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define SCALE_FACTOR 0.05f
#define OCTAVES 4
#define PERSISTENCE  0.5f
#define M_PI 3.14159265358979323846f
#define PIXEL_SIZE  1
#define SNAP_THRESHOLD  1

using namespace sf;
using namespace std;

namespace tools
{
	float distanceToPoint(sf::Vector2f point1, sf::Vector2f point2);

	float noise(int x);
	
	float lerp(float a, float b, float t);
	
	float smoothstep(float x);
	
	float noise(float x);

	float perlin(float x);
	
	int iRand(int _min, int _max);

	double frand(float _min, float _max);

	void restartClock();

	float GetTimeDelta();

	Vector2f vec2f_lerp(Vector2f v0, Vector2f v1, float t);

	Vector3f vec3f_lerp(Vector3f v0, Vector3f v1, float t);

	Color color_lerp(Color v0, Color v1, float t);

	bool Circle_Collision(Vector2f _pos1, Vector2f _pos2, float _rayon1, float _rayon2);

	bool Rectangle_Collision(FloatRect _box1, FloatRect _box2);

};





