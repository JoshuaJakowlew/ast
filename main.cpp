#include <iostream>

#include <ast/atom.hpp>
#include <ast/binop.hpp>

using namespace ast;

struct add_tag {};
struct sub_tag {};

struct add_reducer
{
    template <
        typename Op1, auto Tag1,
        typename Op2, auto Tag2
    >
    constexpr auto operator()(
        atom<Op1, Tag1> const & op1,
        atom<Op2, Tag2> const & op2
    ) const
    {
        return op1.value + op2.value;
    }

    template <
        typename Op1, typename Op2,
        typename Tag1, auto Reducer,
        
        typename Op3, auto Tag2
    >
    constexpr auto operator()(
        binop<Op1, Op2, Tag1, Reducer> const & op1,
        atom<Op3, Tag2> const & op2
    ) const
    {
        return op1() + op2.value;
    }

    template <
        typename Op1, auto Tag1,
        
        typename Op2, typename Op3,
        typename Tag2, auto Reducer
    >
    constexpr auto operator()(
        atom<Op1, Tag1> const & op1,
        binop<Op2, Op3, Tag2, Reducer> const & op2
    ) const
    {
        return op1.value + op2();
    }

    template <
        typename Op1, typename Op2,
        typename Tag1, auto Reducer1,
        
        typename Op3, typename Op4,
        typename Tag2, auto Reducer2
    >
    constexpr auto operator()(
        binop<Op1, Op2, Tag1, Reducer1> const & op1,
        binop<Op3, Op4, Tag2, Reducer2> const & op2
    ) const
    {
        return op1() + op2();
    }
};

int main()
{   
    atom<int> x{1};
    atom<float> y{42};

    auto sum_xy = binop<decltype(x), decltype(y), add_tag, add_reducer{}>{x, y};

    auto sum_x_xy = binop<decltype(x), decltype(sum_xy), add_tag, add_reducer{}>{x, sum_xy};

    auto sum_xy_xy = binop<decltype(sum_xy), decltype(sum_xy), add_tag, add_reducer{}>{sum_xy, sum_xy};

    auto sum_xy_xy__x_xy = binop<decltype(sum_xy_xy), decltype(sum_x_xy), add_tag, add_reducer{}>{sum_xy_xy, sum_x_xy};

    std::cout << "x: " << x() << "\n"
              << "y: " << y() << "\n"
              << "x + y: " << sum_xy() << "\n"
              << "x + (x + y): " << sum_x_xy() << "\n"
              << "(x + y) + (x + y): " << sum_xy_xy() << "\n"
              << "((x + y) + (x + y)) + (x + (x + y)): " << sum_xy_xy__x_xy() << "\n";
}
