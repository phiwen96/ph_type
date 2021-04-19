#pragma once


const char* s1 = R"foo(
Hello
  World
)foo";




template <typename T>
concept bool_func = requires (T t) {
    {t ()} -> ph::concepts::convertible <bool>;
};

template <bool_func... T>

constexpr auto type_watcher (T&&... t) -> auto
{
    return [...t = forward <T> (t)] <typename... U> () constexpr -> auto
    {
        constexpr auto me = [] <typename A, typename... B> (auto&& me, auto&& fun) constexpr -> auto
        {
            if constexpr (requires {fun.template operator () <A> ();})
            {
                if constexpr (not fun.template operator () <A> ())
                {
                    if constexpr (sizeof... (B) > 0)
                    {
                        me.template operator () <B...> (move (me), forward <decltype (fun)> (fun));
                    }
                }
            } else if constexpr (sizeof... (B) > 0)
            {
                me.template operator () <B...> (move (me), forward <decltype (fun)> (fun));
            }
        };
        
        (..., me.template operator () <U...> (move (me), t));
    };
}
