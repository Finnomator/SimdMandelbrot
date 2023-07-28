#pragma once
#include "Renderer.h"

// Microoptimizations

class RendererO1 :
    public Renderer
{
public:
    RendererO1(int widht, int height);
protected:
    void GenerateFractal() override;
};

