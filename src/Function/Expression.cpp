#include "Expression.h"

namespace customFuncs {
    static float sinWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::sin(expr_eval(&vec_nth(args, 0)));
    }

    static float cosWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::cos(expr_eval(&vec_nth(args, 0)));
    }

    static float tanWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::tan(expr_eval(&vec_nth(args, 0)));
    }

    static float asinWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::asin(expr_eval(&vec_nth(args, 0)));
    }

    static float acosWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::acos(expr_eval(&vec_nth(args, 0)));
    }

    static float atanWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::atan(expr_eval(&vec_nth(args, 0)));
    }

    static float sinhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::sinh(expr_eval(&vec_nth(args, 0)));
    }

    static float coshWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::cosh(expr_eval(&vec_nth(args, 0)));
    }

    static float tanhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::tanh(expr_eval(&vec_nth(args, 0)));
    }

    static float asinhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::asinh(expr_eval(&vec_nth(args, 0)));
    }

    static float acoshWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::acosh(expr_eval(&vec_nth(args, 0)));
    }

    static float atanhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::atanh(expr_eval(&vec_nth(args, 0)));
    }

    static float gammaWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::tgamma(expr_eval(&vec_nth(args, 0)));
    }

    static float logWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::log(expr_eval(&vec_nth(args, 0)));
    }

    static float expWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::exp(expr_eval(&vec_nth(args, 0)));
    }

    static float absWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::abs(expr_eval(&vec_nth(args, 0)));
    }

    static float sqrtWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return std::sqrt(expr_eval(&vec_nth(args, 0)));
    }

    static struct expr_func funcList[] = {
            { "sin",   sinWrapper,   nullptr, 0 },
            { "cos",   cosWrapper,   nullptr, 0 },
            { "tan",   tanWrapper,   nullptr, 0 },
            { "asin",  asinWrapper,  nullptr, 0 },
            { "acos",  acosWrapper,  nullptr, 0 },
            { "atan",  atanWrapper,  nullptr, 0 },
            { "sinh",  sinhWrapper,  nullptr, 0 },
            { "cosh",  coshWrapper,  nullptr, 0 },
            { "tanh",  tanhWrapper,  nullptr, 0 },
            { "asinh", asinhWrapper, nullptr, 0 },
            { "acosh", acoshWrapper, nullptr, 0 },
            { "atanh", atanhWrapper, nullptr, 0 },
            { "gamma", gammaWrapper, nullptr, 0 },
            { "log",   logWrapper,   nullptr, 0 },
            { "exp",   expWrapper,   nullptr, 0 },
            { "abs",   absWrapper,   nullptr, 0 },
            { "sqrt",  sqrtWrapper,  nullptr, 0 }
    };
}

Expression::Expression(const std::string& expr)
        : m_variables{}
        , m_expression(expr_create(expr.c_str(), expr.length(),
                                   &m_variables, customFuncs::funcList)) {
    if (m_expression == nullptr) throw std::runtime_error("Could not parse expression");
}

Expression::~Expression() {
    expr_destroy(m_expression, &m_variables);
}

Expression::Expression(Expression&& other) noexcept
        : m_variables(other.m_variables), m_expression(other.m_expression) {
    other.m_expression = nullptr;
    other.m_variables.head = nullptr;
}

Expression& Expression::operator=(Expression&& other) noexcept {
    Expression moved = std::move(other);
    std::swap(m_variables, moved.m_variables);
    std::swap(m_expression, moved.m_expression);
    return *this;
}

float Expression::operator()(float x, float y) const {
    for (struct expr_var* var = m_variables.head; var != nullptr; var = var->next) {
        if (strcmp(var->name, "x") == 0) var->value = x;
        if (strcmp(var->name, "y") == 0) var->value = y;
    }
    return expr_eval(m_expression);
}
