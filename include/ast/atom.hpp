#pragma once

#include <ast/utility.hpp>

namespace ast
{
    template <typename T, auto Tag = unique_return()>
    struct atom
    {
        T const & value;

        constexpr auto operator()() const
        {
            return value;
        }
    };
} // namespace ast
