#include "PlotParameters.h"

PlotParameters::PlotParameters(Rect plotRegion, size_t xParts, size_t yParts)
        : m_plotRegion(plotRegion), m_xParts(xParts), m_yParts(yParts)
        , m_xStep{}, m_yStep{} {
    evalSteps();
}

Rect PlotParameters::getPlotRegion() const {
    return m_plotRegion;
}

std::pair<size_t, size_t> PlotParameters::getParts() const {
    return { m_xParts, m_yParts };
}

void PlotParameters::setPlotRegion(Rect plotRegion) {
    m_plotRegion = plotRegion;
    evalSteps();
}

void PlotParameters::setParts(size_t xParts, size_t yParts) {
    m_xParts = xParts;
    m_yParts = yParts;
    evalSteps();
}

Point PlotParameters::getNodeCoords(size_t i, size_t j) const {
    return {
        m_plotRegion.x + m_xStep * static_cast<float>(i),
        m_plotRegion.y + m_yStep * static_cast<float>(j)
    };
}

void PlotParameters::getCellCorners(Point corners[2][2], size_t i, size_t j) const {
    for (size_t ii = 0; ii < 2; ++ii) {
        for (size_t jj = 0; jj < 2; ++jj) {
            corners[ii][jj] = getNodeCoords(i + ii, j + jj);
        }
    }
}

void PlotParameters::evalSteps() {
    m_xStep = m_plotRegion.width / static_cast<float>(m_xParts);
    m_yStep = m_plotRegion.height / static_cast<float>(m_yParts);
}
