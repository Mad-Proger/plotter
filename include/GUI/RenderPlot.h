#pragma once

#include "Plot.h"
#include "PlotParameters.h"
#include "Primitives.h"
#include <SFML/Graphics.hpp>

enum class ShiftDirection {
    Left,
    Right,
    Up,
    Down
};

template <ImplicitFunction Func>
class RenderPlot: public sf::Drawable {
public:
    RenderPlot(PlotParameters plotParameters, Func&& plotFunc);
    ~RenderPlot() override = default;

    void shift(ShiftDirection direction);
    void zoomIn();
    void zoomOut();
    void increaseAccuracy();
    void decreaseAccuracy();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexArray m_vertices;
    PlotParameters m_parameters;
    Func m_func;

    void updateVertices();
    void zoom(float coefficient);
    void updateAccuracy(float coefficient);

    static constexpr float SHIFT_COEFFICIENT = 0.1f;
    static constexpr float ZOOM_IN_COEFFICIENT = 0.9f;
    static constexpr float ZOOM_OUT_COEFFICIENT = 1.1f;
};

template <ImplicitFunction Func>
inline RenderPlot<Func>::RenderPlot(PlotParameters plotParameters, Func&& plotFunc)
        : m_vertices(sf::PrimitiveType::Lines)
        , m_parameters(plotParameters), m_func(std::move(plotFunc)) {
    updateVertices();
}

template <ImplicitFunction Func>
inline void RenderPlot<Func>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View oldView = target.getView();
    Rect region = m_parameters.getPlotRegion();
    target.setView(sf::View({
                                    region.x, region.y,
                                    region.width, region.height
                            }));
    target.draw(m_vertices, states);
    target.setView(oldView);
}

template <ImplicitFunction Func>
void RenderPlot<Func>::updateVertices() {
    m_vertices.clear();
    marchingSquares::computePlot(
            m_parameters, m_func,
            [this](Point p1, Point p2) {
                m_vertices.append(sf::Vertex({ p1.x, p1.y }, sf::Color::White));
                m_vertices.append(sf::Vertex({ p2.x, p2.y }, sf::Color::White));
            }
    );
}

template <ImplicitFunction Func>
void RenderPlot<Func>::shift(ShiftDirection direction) {
    Rect region = m_parameters.getPlotRegion();
    switch (direction) {
    case ShiftDirection::Left:
        region.x -= region.width * SHIFT_COEFFICIENT;
        break;
    case ShiftDirection::Right:
        region.x += region.width * SHIFT_COEFFICIENT;
        break;
    case ShiftDirection::Up:
        region.y += region.height * SHIFT_COEFFICIENT;
        break;
    case ShiftDirection::Down:
        region.y -= region.height * SHIFT_COEFFICIENT;
        break;
    }
    m_parameters.setPlotRegion(region);
    updateVertices();
}

template <ImplicitFunction Func>
void RenderPlot<Func>::zoomIn() {
    zoom(ZOOM_IN_COEFFICIENT);
}

template <ImplicitFunction Func>
void RenderPlot<Func>::zoomOut() {
    zoom(ZOOM_OUT_COEFFICIENT);
}

template <ImplicitFunction Func>
void RenderPlot<Func>::increaseAccuracy() {
    updateAccuracy(ZOOM_OUT_COEFFICIENT);
}

template <ImplicitFunction Func>
void RenderPlot<Func>::decreaseAccuracy() {
    updateAccuracy(ZOOM_IN_COEFFICIENT);
}

template <ImplicitFunction Func>
void RenderPlot<Func>::zoom(float coefficient) {
    Rect region = m_parameters.getPlotRegion();
    float dw = region.width * (coefficient - 1);
    float dh = region.height * (coefficient - 1);
    region.width *= coefficient;
    region.height *= coefficient;
    region.x -= dw / 2;
    region.y -= dh / 2;
    m_parameters.setPlotRegion(region);
    updateVertices();
}

template <ImplicitFunction Func>
void RenderPlot<Func>::updateAccuracy(float coefficient) {
    auto [xParts, yParts] = m_parameters.getParts();
    xParts = static_cast<size_t>(static_cast<float>(xParts) * coefficient);
    yParts = static_cast<size_t>(static_cast<float>(yParts) * coefficient);
    m_parameters.setParts(xParts, yParts);
    updateVertices();
}
