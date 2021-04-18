#ifndef TYPE_HPP
#define TYPE_HPP
#include <ph_concepts/concepts.hpp>
#include <boost/hof.hpp>
using namespace std;

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

struct value_type_s {};
constexpr auto value_type = value_type_s {};



template <typename T>
struct type_t
{

};
template <typename T>
constexpr type_t <T> type;

//template <auto... t>
//struct types_t;

template <typename... T>
struct _types {};

template <typename T>
struct _types <type_t <T>>
{};



//template <auto a, auto, b, auto... u>
//struct types_t <u..., t>
//{
//
//};
template <auto const&... t>
constexpr _types <decay_t <decltype (t)>...> types;

template <typename... T>
constexpr _types <T...> types_t;




//template <typename... T>
//requires requires {
//    requires sizeof... (T) > 0;
//    requires (is_base_of_v <type_base, T> and ...);
//}
//struct type_t : T...
//{
//
//};

template <typename... typifiers>
struct typify_t
{
    
};








template <typename T>
concept is_type_transf = requires {
    typename T::transform_types;
};






template <typename Derived>
requires requires {
    true;
    /**
     Derived.transform()
     
     because then we can ch
     */
    
}
struct transformer
{
    template <template <typename...> typename T, typename... U>
    using type = typename Derived::template type <T, U...>::type;
};

template <typename... T>
struct transformations;

template <typename Derived, typename... T>
struct transformations <_types <T...>, transformer <Derived>>
{
    
};










template <ph::concepts::value_type T>
auto operator | (type_t <T> const&, value_type_s const&) -> auto
{
    return typename T::value_type {};
}

template <typename T, typename U>
constexpr auto operator!= (type_t <T> const& t, U const& u) -> bool
{
    return not (t == u);
}

template <typename T>
constexpr auto operator== (type_t <T> const&, type_t <T> const&) -> bool
{
    return true;
}

template <typename T>
constexpr auto operator!= (type_t <T> const&, type_t <T> const&) -> bool
{
    return false;
}


template <typename...>
struct has_s
{
    
};



template <typename... T>
struct common_s
{
//    using type = common_type_t <T...>;
};

template <>
struct common_s <>
{
    template <template <typename...> typename T, typename... U>
    using type = T <common_type_t <U...>>;
};




constexpr transformer <common_s <>> common;


//template <typename... T, typename... U>
//constexpr auto typify (typify_t <T...> const&, )
//{
//
//}


template <typename U>
constexpr auto operator > (common_s <> const& n, U&& rhs) -> auto
{
    return ;
}

template <typename T>
constexpr auto operator < (type_t <T> const&, common_s <> const&) -> auto
{
    return common_s <T> {};
}

//static_assert (is_same_v <decltype (types <int, char> | common), common_s <int, char>>, "");

template <typename... T, typename U>
constexpr auto operator > (common_s <T...> const& n, U&& rhs) -> auto
{
    return common_s <T..., decay_t <U>> {};
}



//template <typename... direktiv, typename T>
//constexpr auto operator < (T&&, common_s <direktiv...> const&) -> auto
//{
//    return common_s <decay_t <T>> {};
//}






template <typename T, typename Derived1>
constexpr auto operator | (type_t <type_t <T>> const&, transformer <Derived1> const& t) -> auto
{
    return type <T> | t;
}



template <typename T, typename Derived1>
constexpr auto operator | (type_t <T> const&, transformer <Derived1> const& t) -> auto
{
    return types_t <T> | t;
}

template <typename... T, typename Derived1>
constexpr auto operator | (_types <T...> const&, transformer <Derived1> const& t) -> auto
{
    return transformations <_types <T...>, transformer <Derived1>> {};
}


template <typename T, typename Derived1>
constexpr auto operator | (T&&, transformer <Derived1> const&) -> auto
{
    return transformations <transformer <Derived1>, decay_t <T>> {};
}

static_assert (is_same_v <transformations <_types <int, char, double>, transformer <common_s <>>>, decltype (types_t <int, char, double> | common)>, "");

template <typename T>
constexpr auto operator or (T&& t, common_s <> const&) -> auto
{ //cout<<"or"<<endl;
    return forward <T> (t);
}


//template <typename... T>
//constexpr auto operator | (bajs_t b, int)
//{
//    return b;
//}


template <typename... T, typename... U>
constexpr auto operator and (type_t <T...> const&, type_t <U...> const&)
{cout<<"and"<<endl;
    return type_t <T..., U...> {};
}

































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

#endif
