#define CATCH_CONFIG_MAIN

#include "../catch.hpp"

#include "symcpp.h"


TEST_CASE("Basic math capabilities of symcpp library", "[symcpp]") {
    using namespace symcpp;

    SECTION("Construction of symbols, numbers, and expressions") {
        Symbol x('x'), y('y');
        Number num = 17;

        Expression exp("x + ln(y^2)", {x, y});
        REQUIRE(exp.GetInfix() == "x + ln(y^2)");

        exp = Pow(x, 2) * 13 + Sin(pi * y);
        REQUIRE(exp.GetInfix() == "x^2 * 13 + sin(pi * y)");
    }

    SECTION("Evaluation of expressions with variable assignment") {
        Symbol x('x'), y('y');
        Number num = 17;

        Expression exp = Pow(x, 2) * 13 + Sin(pi * y);
        x = 3;
        // REQUIRE(exp.Evaluate({}). == Approx(117.0).epsilon(0.01));

        y = num / 2;
        // REQUIRE(exp.Evaluate({}) == Approx(117.0).epsilon(0.01));
    }

    SECTION("Reset functionality") {
        Symbol x('x'), y('y');

        Expression exp = Pow(x, 2) * 13 + Sin(pi * y);
        x = 3;
        y = 2;

        x.Reset();
        REQUIRE(exp.GetInfix() == "x^2 * 13 + sin(pi * 2)");

        y.Reset();
        REQUIRE(exp.GetInfix() == "x^2 * 13 + sin(pi * y)");
    }

    SECTION("Differentiation") {
        Symbol x('x'), y('y');

        Expression exp = 13*  Pow(x, 2)  + Sin(pi * y);

        auto derivative_of_func_x = Diff(exp, x);
        REQUIRE(derivative_of_func_x.GetInfix() == "26 * x");

        auto derivative_of_func_y = Diff(exp, y);
        REQUIRE(derivative_of_func_y.GetInfix() == "pi*cos(pi*y)");
    }

    SECTION("Evaluation and representation") {
        Symbol x('x'), y('y');

        Expression exp = Pow(x, 2) * 13 + Sin(pi * y);
        
        Number result_2 = Evaluate(Log(exp), {{x, 14}, {y, 17}});
        REQUIRE(result_2 > 0);

        REQUIRE(RPN(exp + Log(Pow(x, y))).empty() == false);
        REQUIRE(Latex(exp + Log(Pow(x, y))).empty() == false);
    }
}