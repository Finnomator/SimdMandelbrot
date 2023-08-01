#pragma once
#include "Renderer.h"

class SimdRenderer :
	public Renderer {

public:
	SimdRenderer(const int width, const int height, const bool double_precision);
protected:
	virtual void GenerateFractalDoublePrecision() = 0;
	virtual	void GenerateFractalSinglePrecision() = 0;
private:
	void GenerateFractal() override;
	bool double_precision;
};

