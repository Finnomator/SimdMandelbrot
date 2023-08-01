#pragma once
#include "Renderer.h"
class LessBranchesRenderer :
    public Renderer {
public:
    LessBranchesRenderer(int widht, int height);
protected:
    void GenerateFractal() override;
};

