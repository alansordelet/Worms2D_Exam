#pragma once
#include"tools.h"
class Terrain
{
public:
	Terrain();
	~Terrain() {};

	void CreateTerrain();
	void UpdateTerrain();
	void DrawTerrain(sf::RenderWindow& _window);

	inline void PerlinNoise1D(int nCount, float* fSeed, int nOctaves, float fBias, float* fOutput)
	{
		// Used 1D Perlin Noise
		for (int x = 0; x < nCount; x++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = nCount >> o;
				int nSample1 = (x / nPitch) * nPitch;
				int nSample2 = (nSample1 + nPitch) % nCount;

				float fBlend = (float)(x - nSample1) / (float)nPitch;

				float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];

				fScaleAcc += fScale;
				fNoise += fSample * fScale;
				fScale = fScale / fBias;
			}

			// Scale to seed range
			fOutput[x] = fNoise / fScaleAcc;
		}
	}

	float getTopOfGreenPixels(float x, float y)
	{
		// round the x and y coordinates to the nearest integers
		int xCoord = static_cast<int>(x + 0.1f);
		int yCoord = static_cast<int>(y + 0.1f);
		//range of pixels above and below the player's position as valid for movement
		int validRange = 5;
		for (int y = yCoord - validRange; y <= yCoord + validRange; y++)
		{
			int index = (xCoord + y * SCREEN_WIDTH) * 4;
			if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)// so the game doesnt crash when collison out of screen
			{
				if (pixels[index] == 0 && pixels[index + 1] == 255 && pixels[index + 2] == 0 && pixels[index + 3] == 255)
				{
					if (yCoord <= y)
					{
						return y;
					}
					else
					{
						return yCoord;
					}
				}
			}
		}
		return SCREEN_HEIGHT - 1;
	}
	sf::Uint8* pixels = new sf::Uint8[1200 * 800 * 4];
	sf::Texture texture;
	sf::Sprite terrainS;
private:
	float randomiseterrain = 0;

	const int GREEN_PIXELS_WIDTH = SCREEN_WIDTH;
};

