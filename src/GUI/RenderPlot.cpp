#include "RenderPlot.h"

RenderPlot::RenderPlot(PlotParameters plotParameters)
        : m_vertices(sf::PrimitiveType::Lines, sf::VertexBuffer::Usage::Dynamic)
        , m_parameters(plotParameters) {}

void RenderPlot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View oldView = target.getView();
    Rect region = m_parameters.getPlotRegion();
    target.setView(sf::View({
        region.x, region.y,
        region.width, region.height
    }));
    target.draw(m_vertices, states);
    target.setView(oldView);
}
