#pragma once

#include <ast/atom.hpp>
#include <ast/binop.hpp>

namespace ast::reducers
{
    struct add
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
} // namespace ast::reducers
