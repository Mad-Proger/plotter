#pragma once

#include "expr.h"
#include <cmath>
#include <string>
#include <stdexcept>

class Expression {
public:
    explicit Expression(const std::string& expr);
    ~Expression();

    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;

    Expression(Expression&& other) noexcept;
    Expression& operator=(Expression&& other) noexcept;

    float operator()(float x, float y) const;

private:
    expr_var_list m_variables;
    expr* m_expression;
};
