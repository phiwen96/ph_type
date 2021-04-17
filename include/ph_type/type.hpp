#ifndef TYPE_HPP
#define TYPE_HPP
#include <ph_concepts/concepts.hpp>
using namespace std;

template <typename T>
concept bool_func =

template <typename... T>
requires requires {

}
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

template <typename T>
struct type_t
{
    //    template <typename Q>
    //    friend constexpr auto operator== (type_t const&, Q const&) -> bool
    //    {
    //        return is_same_v <T, Q>;
    //    }
};

template <typename T, typename U>
concept __same = is_same_v <T, U>;

template <typename T, typename U>
concept has_overloaded_same_type = requires (T const& t)
{
    {t.template same_type <U> ()} -> __same <bool>;
    
    //    {U::template same_type <U> (declval <U const&> ())} -> __same <bool>;
};





template <typename T, typename U>
constexpr auto operator== (type_t <T> const&, U const& u) -> bool
requires (has_overloaded_same_type <U, T>)
{
    return u.template same_type <T> ();
}

template <typename T, typename U>
constexpr auto operator== (type_t <T> const&, U const&) -> bool
requires (not has_overloaded_same_type <U, T>)
{
    return is_same_v <T, U>;
}


template <typename T, typename U>
constexpr auto operator!= (type_t <T> const& t, U const& u) -> bool
{
    return not (t == u);
}




//template <typename T, typename U>
//constexpr auto operator== (U const&, type_t <T> const&) -> bool
//{
//    return is_same_v <T, U>;
//}

template <typename T>
constexpr auto type = type_t <T> {};


#endif
