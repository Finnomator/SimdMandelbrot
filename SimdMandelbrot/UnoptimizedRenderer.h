#pragma once
#include "Renderer.h"
class UnoptimizedRenderer :
    public Renderer
{
public:
    UnoptimizedRenderer(int widht, int height);
protected:
    void GenerateFractal() override;
};
