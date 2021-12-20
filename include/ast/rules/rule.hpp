#pragma once

#include <type_traits>

#include <ast/atom.hpp>
#include <ast/binop.hpp>

namespace ast::rules
{
    template <typename Lhs>
    struct rule {
        consteval auto operator()() const noexcept -> Lhs
        {}
    };

    
    // binop<binop<atom<T1, ATag1>, atom<T2, ATag2>, Tag1, Reducer1>, atom<T1, ATag1>, Tag2, Reducer2>
} // namespace ast::rules
