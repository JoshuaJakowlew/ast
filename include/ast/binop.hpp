#pragma once

namespace ast
{
    template <typename Op1, typename Op2, typename Tag, auto Reducer>
    struct binop
    {
        Op1 const & op1;
        Op2 const & op2;

        constexpr auto operator()() const
        {
            return Reducer(op1, op2);
        }
    };

    template <typename Tag, auto Reducer, typename Op1, typename Op2>
    constexpr auto make_binop(Op1 const & op1, Op2 const & op2)
    {
        return binop<Op1, Op2, Tag, Reducer>{op1, op2};
    }

} // namespace ast
