#pragma once
#include "concepts.hpp"



template <typename Parent, typename Child>
struct __parent
{
    using me = __parent <Parent, Child>;
    
    template <typename NewTransformer>
    requires requires {
        can_add_transformer <Child, NewTransformer>;
    }
    using add_transformer = __parent <Parent, typename Child::template add_transformer <NewTransformer>>;

    template <typename... Types>
    using transform = typename Child::template transform <typename Parent::template transform <Types...>>;
};
