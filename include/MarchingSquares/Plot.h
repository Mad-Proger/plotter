#pragma once

#include "PlotParameters.h"

#include <cmath>
#include <cstddef>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

namespace marchingSquares {

float findRoot(float x1, float x2, float val1, float val2) {
    float t = val1 / (val1 - val2);
    return std::lerp(x1, x2, t);
}

template <std::invocable<Point, Point> Func>
void computeAngle(Point pts[2][2], float values[2][2], Func&& f, size_t i, size_t j) {
    Point p1{ findRoot(pts[i][j].x, pts[i ^ 1][j].x, values[i][j], values[i ^ 1][j]),
              pts[i][j].y };
    Point p2{ pts[i][j].x,
              findRoot(pts[i][j].y, pts[i][j ^ 1].y, values[i][j], values[i][j ^ 1])};
    std::invoke(std::forward<Func>(f), p1, p2);
}

template <std::invocable<Point, Point> Func>
void computePositiveAngle(Point pts[2][2], float values[2][2], Func&& f) {
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            if (values[i][j] > 0) {
                computeAngle(pts, values, std::forward<Func>(f), i, j);
                return;
            }
        }
    }
}

template <std::invocable<Point, Point> Func>
void computeNegativeAngle(Point pts[2][2], float values[2][2], Func&& f) {
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            if (values[i][j] <= 0) {
                computeAngle(pts, values, std::forward<Func>(f), i, j);
                return;
            }
        }
    }
}

template <std::invocable<Point, Point> Func>
void computeVertical(Point pts[2][2], float values[2][2], Func&& f) {
    Point p1{ findRoot(pts[0][0].x, pts[1][0].x, values[0][0], values[1][0]), pts[0][0].y };
    Point p2{ findRoot(pts[0][1].x, pts[1][1].x, values[0][1], values[1][1]), pts[0][1].y };
    std::invoke(std::forward<Func>(f), p1, p2);
}

template <std::invocable<Point, Point> Func>
void computeHorizontal(Point pts[2][2], float values[2][2], Func&& f) {
    Point p1{ pts[0][0].x, findRoot(pts[0][0].y, pts[0][1].y, values[0][0], values[0][1]) };
    Point p2{ pts[1][0].x, findRoot(pts[1][0].y, pts[1][1].y, values[1][0], values[1][1]) };
    std::invoke(std::forward<Func>(f), p1, p2);
}

template <std::invocable<Point, Point> Func>
void computeCell(Point pts[2][2], float values[2][2], Func&& f) {
    int cntPositive = 0;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            if (!std::isnormal(values[i][j])) return;
            cntPositive += values[i][j] > 0;
        }
    }

    if (cntPositive == 1) computePositiveAngle(pts, values, std::forward<Func>(f));
    if (cntPositive == 3) computeNegativeAngle(pts, values, std::forward<Func>(f));
    if (cntPositive == 2) {
        if (((values[0][0] > 0) ^ (values[0][1] > 0)) &&
                ((values[0][0] > 0) ^ (values[1][0] > 0))) {
            computeAngle(pts, values, f, 0, 0);
            computeAngle(pts, values, f, 1, 1);
        } else if ((values[0][0] > 0) ^ (values[0][1] > 0)) {
            computeHorizontal(pts, values, std::forward<Func>(f));
        } else {
            computeVertical(pts, values, std::forward<Func>(f));
        }
    }
}

template <typename F, std::invocable<Point, Point> R>
void computePlot(const PlotParameters& plotParam, F&& func, R&& callback) requires
std::is_invocable_r_v<F, float, float, float> {
    auto [xParts, yParts] = plotParam.getParts();
    std::vector<float> lastRow(xParts + 1);
    for (size_t i = 0; i <= xParts; ++i) {
        lastRow[i] = func(i, i == 0);
    }
    float corner = func(0, 0);

    size_t i = 0, j = 0;
    while (j < yParts) {
        Point pts[2][2] = {};
        plotParam.getCellCorners(pts, i, j);
        float values[2][2] = {
                { corner,     lastRow[i + 1] },
                { lastRow[i], std::invoke(func, pts[1][1].x, pts[1][1].y) }
        };
        computeCell(pts, values, callback);

        if (++i == xParts) {
            i = 0;
            ++j;
            corner = lastRow[0];
            auto [x, y] = plotParam.getNodeCoords(0, j + 1);
            lastRow[0] = std::invoke(func, x, y);
        }
    }
}

}
