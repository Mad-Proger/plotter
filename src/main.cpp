#include "Window.h"
#include "Expression.h"
#include "RenderPlot.h"

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
    PlotParameters plotParameters({ -8, -4.5, 16, 9 },
                                  320, 180);
    auto plot = std::unique_ptr<InteractiveDrawable>{
            new RenderPlot(plotParameters, getExpression())
    };

    Window window(1280, 720, std::move(plot));
    window.eventLoop();
    return 0;
}
