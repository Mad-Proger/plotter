#pragma once

#include "expr.h"
#include <string>
#include <stdexcept>

class Expression {
public:
    explicit Expression(const std::string& expr);
    ~Expression();

    float operator()(float x, float y) const;

private:
    expr_var_list m_variables;
    expr* m_expression;
};
