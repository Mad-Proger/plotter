#pragma once

#include "Primitives.h"

#include <cstddef>
#include <utility>

class PlotParameters {
public:
    PlotParameters(Rect plotRegion, size_t xParts, size_t yParts);

    Rect getPlotRegion() const;
    std::pair<size_t, size_t> getParts() const;

    void setPlotRegion(Rect plotRegion);
    void setParts(size_t xParts, size_t yParts);

    Point getNodeCoords(size_t i, size_t j) const;
    void getCellCorners(Point corners[2][2], size_t i, size_t j) const;

private:
    Rect m_plotRegion;
    size_t m_xParts;
    size_t m_yParts;
    float m_xStep;
    float m_yStep;

    void evalSteps();
};