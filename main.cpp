#include <iostream>

#include <ast/atom.hpp>
#include <ast/binop.hpp>
#include <ast/reducers/add.hpp>
#include <ast/reducers/sub.hpp>
#include <ast/rules/rule.hpp>

using namespace ast;

int main()
{   
    atom<int> x{1};
    atom<float> y{42};

    auto sum_xy = binop<decltype(x), decltype(y), reducers::add_tag, reducers::add{}>{x, y};

    auto sum_x_xy = binop<decltype(x), decltype(sum_xy), reducers::add_tag, reducers::add{}>{x, sum_xy};

    auto sum_xy_xy = binop<decltype(sum_xy), decltype(sum_xy), reducers::add_tag, reducers::add{}>{sum_xy, sum_xy};

    auto sum_xy_xy__x_xy = binop<decltype(sum_xy_xy), decltype(sum_x_xy), reducers::add_tag, reducers::add{}>{sum_xy_xy, sum_x_xy};

    std::cout << "x: " << x() << "\n"
              << "y: " << y() << "\n"
              << "x + y: " << sum_xy() << "\n"
              << "x + (x + y): " << sum_x_xy() << "\n"
              << "(x + y) + (x + y): " << sum_xy_xy() << "\n"
              << "((x + y) + (x + y)) + (x + (x + y)): " << sum_xy_xy__x_xy() << "\n";

    auto sub_xy = binop<decltype(x), decltype(y), reducers::sub_tag, reducers::sub{}>{x, y};

    auto sum_x_sub_xy = binop<decltype(x), decltype(sub_xy), reducers::sub_tag, reducers::add{}>{x, sub_xy};

    std::cout << "x - y: " << sub_xy() << "\n"
              << "x + (x - y): " << sum_x_sub_xy() << "\n";

    auto rule = rules::rule<int>{};
    static_assert(std::same_as<int, decltype(rule())>);
}
