#include "Renderer.h"

Renderer::Renderer(const int width, const int height)
{
	this->width = width;
	this->height = height;
	ratio = static_cast<double>(width) / height;

	pixels = new sf::Uint8[width * height * 4];
	texture.create(width, height);
	sprite = sf::Sprite(texture);

	for (int i = 0; i < width * height * 4; i += 4) {
		pixels[i + 3] = 255;
	}
}

sf::Sprite* Renderer::Render()
{
	GenerateFractal();
	texture.update(pixels);
	return &sprite;
}

void Renderer::SetPixel(int x, int y, char r, char g, char b)
{
	SetPixel(y * width + x, r, g, b);
}

void Renderer::SetPixel(int i, char r, char g, char b)
{
	i <<= 2;
	pixels[i] = r;
	pixels[i + 1] = g;
	pixels[i + 2] = b;
}

void Renderer::SetPixel(int x, int y, char all_channels) {
	const int i = (y * width + x) << 2;
	pixels[i] = all_channels;
	pixels[i + 1] = all_channels;
	pixels[i + 2] = all_channels;
}

