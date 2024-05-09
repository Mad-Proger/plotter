#pragma once

#include "Interfaces.h"
#include "Plot.h"
#include "PlotParameters.h"
#include "Primitives.h"

template <ImplicitFunction Func>
class RenderPlot: public InteractiveDrawable {
public:
    RenderPlot(PlotParameters plotParameters, Func&& plotFunc);
    ~RenderPlot() override = default;

    void processEvent(sf::Event event) override;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexArray m_vertices;
    PlotParameters m_parameters;
    Func m_func;

    void updateVertices();
    void moveRegion(sf::Keyboard::Key keyCode);
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
inline void RenderPlot<Func>::processEvent(sf::Event event) {
    if (event.type != sf::Event::KeyPressed) return;
    if (event.key.code == sf::Keyboard::Dash) {
        if (event.key.shift) {
            updateAccuracy(ZOOM_IN_COEFFICIENT);
        } else {
            zoom(ZOOM_OUT_COEFFICIENT);
        }
    }
    if (event.key.code == sf::Keyboard::Equal) {
        if (event.key.shift) {
            updateAccuracy(ZOOM_OUT_COEFFICIENT);
        } else {
            zoom(ZOOM_IN_COEFFICIENT);
        }
    }
    moveRegion(event.key.code);
}

template <ImplicitFunction Func>
inline void RenderPlot<Func>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View oldView = target.getView();
    Rect region = m_parameters.getPlotRegion();
    target.setView(sf::View({
                                    region.x, region.y + region.height,
                                    region.width, -region.height
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
void RenderPlot<Func>::moveRegion(sf::Keyboard::Key keyCode) {
    Rect region = m_parameters.getPlotRegion();
    switch (keyCode) {
    case sf::Keyboard::Left:
        region.x -= region.width * SHIFT_COEFFICIENT;
        break;
    case sf::Keyboard::Right:
        region.x += region.width * SHIFT_COEFFICIENT;
        break;
    case sf::Keyboard::Up:
        region.y += region.height * SHIFT_COEFFICIENT;
        break;
    case sf::Keyboard::Down:
        region.y -= region.height * SHIFT_COEFFICIENT;
        break;
    default:
        return;
    }
    m_parameters.setPlotRegion(region);
    updateVertices();
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
