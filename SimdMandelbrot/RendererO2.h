#pragma once
#include "Renderer.h"
class RendererO2 :
    public Renderer
{
public:
    RendererO2(int width, int height, bool double_precision);
protected:
    void GenerateFractal() override;
private:
    bool double_precision;
    void GenerateFractalDoublePrecision();
    void GenerateFractalSinglePrecision();
};

