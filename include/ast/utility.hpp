#pragma once

namespace ast::detail
{
    template<auto Tag>
    struct unique_value
    {
       static constexpr int value = 0;
    };
} // namespace ast::detail


namespace ast
{
    template<auto Tag = []{}>
    constexpr auto unique_return()
    {
       return &detail::unique_value<Tag>::value;
    }
} // namespace ast
