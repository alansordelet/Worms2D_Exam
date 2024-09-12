#include "tools.h"

sf::Clock sfclock;
sf::Time sfTime;

namespace tools
{
	int iRand(int _min, int _max)
	{ 
		return rand() % (_max - _min) + _min;
	}

	double frand(float _min, float _max)
	{
		return ((rand() / (double)RAND_MAX) * ((double)_max - (double)_min) + (double)_min);
	}

	void restartClock()
	{
		sfTime = sfclock.restart();
	}

	float GetTimeDelta()
	{
		return sfTime.asSeconds();
	}

	float noise(int x)
	{
		x = (x << 13) ^ x;
		return (1.0f - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
	}

	float distanceToPoint(sf::Vector2f point1, sf::Vector2f point2) {
		float dx = point1.x - point2.x;
		float dy = point1.y - point2.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	float lerp(float a, float b, float t)
	{
		return (1.0f - t) * a + t * b;
	}

	float smoothstep(float x)
	{
		return 6 * pow(x, 5) - 15 * pow(x, 4) + 10 * pow(x, 3);
	}

	float noise(float x)
	{
		int ix = (int)x;
		float fx = x - ix;
		float a = noise(ix);
		float b = noise(ix + 1);
		return lerp(a, b, smoothstep(fx));
	}

	float perlin(float x)
	{

		float total = 0.0f;
		float persistence = PERSISTENCE;
		float frequency = SCALE_FACTOR;
		float amplitude = 1.0f;

		for (int i = 0; i < OCTAVES; i++) {
			total += noise(x * frequency) * amplitude;
			amplitude *= persistence;
			frequency *= 2;
		}

		return total;
	}


	Vector2f vec2f_lerp(Vector2f v0, Vector2f v1, float t)
	{
		Vector2f tmp;
		tmp.x = (1 - t) * v0.x + t * v1.x;
		tmp.y = (1 - t) * v0.y + t * v1.y;
		return tmp;
	}


	Vector3f vec3f_lerp(Vector3f v0, Vector3f v1, float t)
	{
		Vector3f tmp;
		tmp.x = (1 - t) * v0.x + t * v1.x;
		tmp.y = (1 - t) * v0.y + t * v1.y;
		tmp.z = (1 - t) * v0.z + t * v1.z;
		return tmp;
	}


	Color color_lerp(Color v0, Color v1, float t)
	{
		Color tmp;
		tmp.r = (1 - t) * v0.r + t * v1.r;
		tmp.g = (1 - t) * v0.g + t * v1.g;
		tmp.b = (1 - t) * v0.b + t * v1.b;
		tmp.a = (1 - t) * v0.a + t * v1.a;
		return tmp;
	}

	bool Circle_Collision(Vector2f _pos1, Vector2f _pos2, float _rayon1, float _rayon2)
	{
		// if (sqrt(pow(_pos1.x - _pos2.x, 2) + pow(_pos1.y - _pos2.y, 2)) < _rayon1 + _rayon2) // Version non optimisé
		// Version Optimisé
		if ((_pos1.x - _pos2.x) * (_pos1.x - _pos2.x) + (_pos1.y - _pos2.y) * (_pos1.y - _pos2.y) < (_rayon1 + _rayon2) * (_rayon1 + _rayon2))
		{
			return true;
		}
		else return false;
	}

	bool Rectangle_Collision(FloatRect _box1, FloatRect _box2)
	{
		if ((_box2.left >= _box1.left + _box1.width)      // trop à droite
			|| (_box2.left + _box2.width <= _box1.left) // trop à gauche
			|| (_box2.top >= _box1.top + _box1.height) // trop en bas
			|| (_box2.top + _box2.height <= _box1.top))  // trop en haut
			return false;
		else
			return true;
	}
};