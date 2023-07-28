#pragma once
#include "Renderer.h"
class RendererO2 :
    public Renderer
{
public:
    RendererO2(int width, int height);
protected:
    void GenerateFractal() override;
};

