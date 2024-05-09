#pragma once

#include "Plot.h"
#include "PlotParameters.h"
#include "Primitives.h"
#include <SFML/Graphics.hpp>

class RenderPlot: public sf::Drawable {
public:
    explicit RenderPlot(PlotParameters plotParameters);
    ~RenderPlot() override = default;

    template <ImplicitFunction Func>
    void renderFunc(Func&& func);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexBuffer m_vertices;
    PlotParameters m_parameters;
};

template <ImplicitFunction Func>
void RenderPlot::renderFunc(Func&& func) {
    std::vector<sf::Vertex> newVertices;
    marchingSquares::computePlot(m_parameters, std::forward<Func>(func),
            [&newVertices](Point p1, Point p2) {
        newVertices.emplace_back(sf::Vector2f{ p1.x, p1.y }, sf::Color::White);
        newVertices.emplace_back(sf::Vector2f{ p2.x, p2.y }, sf::Color::White);
    });
    m_vertices.update(newVertices.data(), newVertices.size(), 0);
}
