#pragma once
#include "SimdRenderer.h"
class SimdRendererO1 :
    public SimdRenderer
{
public:
    SimdRendererO1(int width, int height, bool double_precision);
protected:
    void GenerateFractalDoublePrecision() override;
    void GenerateFractalSinglePrecision() override;
};

