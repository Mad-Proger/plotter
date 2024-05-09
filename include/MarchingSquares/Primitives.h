#pragma once

#include <type_traits>
#include <concepts>

struct Point {
    float x;
    float y;
};

struct Rect {
    float x;
    float y;
    float width;
    float height;
};

template <typename Func>
concept ImplicitFunction = std::is_invocable_r_v<float, Func, float, float>;

template <typename Func>
concept SegmentReturnCallback = std::invocable<Func, Point, Point>;
