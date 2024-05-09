#include "Expression.h"

namespace customFuncs {
    static float sinWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return sinf(expr_eval(&vec_nth(args, 0)));
    }

    static float cosWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return cosf(expr_eval(&vec_nth(args, 0)));
    }

    static float tanWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return tanf(expr_eval(&vec_nth(args, 0)));
    }

    static float asinWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return asinf(expr_eval(&vec_nth(args, 0)));
    }

    static float acosWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return acosf(expr_eval(&vec_nth(args, 0)));
    }

    static float atanWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return atanf(expr_eval(&vec_nth(args, 0)));
    }

    static float sinhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return sinhf(expr_eval(&vec_nth(args, 0)));
    }

    static float coshWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return coshf(expr_eval(&vec_nth(args, 0)));
    }

    static float tanhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return tanhf(expr_eval(&vec_nth(args, 0)));
    }

    static float asinhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return asinhf(expr_eval(&vec_nth(args, 0)));
    }

    static float acoshWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return acoshf(expr_eval(&vec_nth(args, 0)));
    }

    static float atanhWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return atanhf(expr_eval(&vec_nth(args, 0)));
    }

    static float gammaWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return tgammaf(expr_eval(&vec_nth(args, 0)));
    }

    static float logWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return logf(expr_eval(&vec_nth(args, 0)));
    }

    static float expWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return expf(expr_eval(&vec_nth(args, 0)));
    }

    static float absWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return fabsf(expr_eval(&vec_nth(args, 0)));
    }

    static float sqrtWrapper(struct expr_func*, vec_expr_t* args, void*) {
        return sqrtf(expr_eval(&vec_nth(args, 0)));
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
