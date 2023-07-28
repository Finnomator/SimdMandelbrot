#include "UnoptimizedRenderer.h"

UnoptimizedRenderer::UnoptimizedRenderer(int widht, int height) : Renderer(widht, height)
{
}

void UnoptimizedRenderer::GenerateFractal()
{

	for (int py = 0; py < height; ++py) {

		for (int px = 0; px < width; ++px) {

			double x0 = (2.0 * px / width - 1.0) * ratio;
			double y0 = 2.0 * py / height - 1.0;
			double x = 0;
			double y = 0;
			int iteration = 0;

			for (; x * x + y * y <= 4 && iteration < max_iteration; ++iteration) {
				double xtemp = x * x - y * y + x0;
				y = 2.0 * x * y + y0;
				x = xtemp;
			}

			SetPixel(px, py, iteration, iteration, iteration);
		}
	}
}
