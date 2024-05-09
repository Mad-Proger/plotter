#include "Window.h"
#include "Expression.h"

#include <iostream>
#include <string>

Expression getExpression() {
    std::cout << "Enter implicit function to plot: ";
    std::cout.flush();
    std::string expr;
    std::getline(std::cin, expr);
    return Expression{ expr };
}

int main() {
    Window window(1280, 720, nullptr);
    window.eventLoop();
    return 0;
}
