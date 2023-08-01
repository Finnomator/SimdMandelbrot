#include "SimdRenderer.h"

SimdRenderer::SimdRenderer(const int width, const int height, const bool double_precision) : Renderer(width, height) {
	this->double_precision = double_precision;
}

void SimdRenderer::GenerateFractalDoublePrecision() {
}

void SimdRenderer::GenerateFractalSinglePrecision() {
}

void SimdRenderer::GenerateFractal() {
	if (double_precision)
		GenerateFractalDoublePrecision();
	else
		GenerateFractalSinglePrecision();
}
