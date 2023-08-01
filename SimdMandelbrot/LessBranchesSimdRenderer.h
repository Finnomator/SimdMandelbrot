#pragma once
#include "SimdRenderer.h"

class LessBranchesSimdRenderer :
    public SimdRenderer {
public:
    LessBranchesSimdRenderer(int width, int height, bool double_precision);
protected:
    void GenerateFractalDoublePrecision() override;
    void GenerateFractalSinglePrecision() override;
};

