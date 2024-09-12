#include "Terrain.h"
#include <cmath>
#include <random>



Terrain::Terrain()
{
	const int NUM_POINTS = GREEN_PIXELS_WIDTH;
	float* heights = new float[NUM_POINTS];
	float newTerrain = tools::frand(0.01, 0.08);
	for (int i = 0; i < 1200; i++) {
		heights[i] = tools::perlin(i * newTerrain) * 0.5f + 0.5f;
	}
	//x represents the horizontal coordinate of the pixel, ranging from 0 to 1199 (1200 pixels in total), 
	//and y represents the vertical coordinate of the pixel, ranging from 399 to 798 (400 pixels in total).
	//Multiplying y by 1200 represents the number of pixels in each row before the row containing the desired pixel, 
	//and adding x to it gives the total number of pixels before the desired pixel in that row. 
	//Multiplying this by 4 gives the number of bytes before the desired pixel
	for (int x = 0; x < 1200; x++) {
		for (int y = 199; y < 799; y++) {
			int index = (x + y * 1200) * 4;
			pixels[index] = 0;
			pixels[index + 1] = 255;
			pixels[index + 2] = 0;
			pixels[index + 3] = 255;

			if (y < (800 - heights[x] * 800)) {
				pixels[index] = 0;
				pixels[index + 1] = 255;
				pixels[index + 2] = 255;
				//pixels[index + 3] = 255;
			}
		}
		for (int y = 0; y < 199; y++) {
			int index = (x + y * 1200) * 4;
			pixels[index] = 0;
			pixels[index + 1] = 255;
			pixels[index + 2] = 255;
			pixels[index + 3] = 255;
		}
	}

	texture.create(1200, 800);
	texture.update(pixels);
	terrainS.setTexture(texture);
}

void Terrain::CreateTerrain()
{

}

void Terrain::UpdateTerrain()
{

}

void Terrain::DrawTerrain(sf::RenderWindow& _window)
{
	_window.draw(terrainS);
}
