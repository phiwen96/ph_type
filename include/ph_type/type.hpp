#ifndef TYPE_HPP
#define TYPE_HPP
#include <ph_concepts/concepts.hpp>
//#include <boost/hof.hpp>
//using namespace std;

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


template <typename Transformer, typename... Args>
concept can_transform = requires {
    typename Transformer::template transform <_types, Args...>;
};


template <typename... T>
struct __as
{
    
};

template <>
struct __as <>
{
    
};

constexpr __as as {};

struct __if {};
constexpr __if _if {};

struct __then {};
constexpr __then _then {};

struct __else {};
constexpr __else _else {};

struct __while {};
constexpr __while _while {};

struct __and {};
constexpr __and _and {};

struct __or {};
constexpr __or _or {};

template <typename Parent, typename Child>
struct __parent
{
    using me = __parent <Parent, Child>;
    
    template <typename Transformer>
    using add_transformer = __parent <Parent, typename Child::template add_transformer <Transformer>>;

    template <typename... Types>
    using transform = typename Child::template transform <typename Parent::template transform <Types...>>;
};

struct __same
{
    template <typename ChildTransformer>
    using add_transformer = __parent <__same, ChildTransformer>;
    
//    template <template <typename...> typename T, typename... U>
//    using transform = std::conditional_t <(std::is_same_v <A, U> and ...), std::string, std::false_type>;
};



constexpr auto same = __same {};

struct value_type_s {};
constexpr auto value_type = value_type_s {};



template <typename T>
struct type_t
{
    
    using type = T;
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

template <typename T>
struct _types <T>
{
    using type = T;
};



//template <auto a, auto, b, auto... u>
//struct types_t <u..., t>
//{
//
//};
template <auto const&... t>
constexpr _types <std::decay_t <decltype (t)>...> types;

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
struct transformer
{
//    template <typename Derived2>
//    using add_transformer = transformer <typename Derived::template add_transformer <Derived2>>;
    
    template <template <typename...> typename T, typename... U>
    requires requires {
        typename Derived::template transform <T, U...>;
    }
    using transform = typename Derived::template transform <T, U...>;
};



template <typename... T>
struct transformations;

template <typename Transformer, typename... T>
requires (can_transform <Transformer, T...>)
struct transformations <_types <T...>, Transformer>
{
    using type = typename Transformer::template transform <_types, T...>;
    
    operator auto () {
        return type {};
    }
};










//template <ph::concepts::value_type T>
//auto operator | (type_t <T> const&, value_type_s const&) -> auto
//{
//    return typename T::value_type {};
//}

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

template <typename...>
struct common_s;

template <typename Derived>
struct common_s <Derived>
{
//    template <template <typename...> typename T, typename... U>
//    using transform = typename T <common_type_t <U...>>::type;
    template <typename Derived2>
    using add_transformer = common_s <typename Derived::template add_transformer <Derived2>>;
    
    template <template <typename...> typename T, typename... U>
    using transform = typename Derived::template transform <T, std::common_type_t <U...>>;
};

template <>
struct common_s <>
{
    template <typename Derived>
    using add_transformer = common_s <Derived>;
    
    template <template <typename...> typename T, typename... U>
    using transform = typename T <std::common_type_t <U...>>::type;
};




constexpr transformer <common_s <>> common;


//template <typename... T, typename... U>
//constexpr auto typify (typify_t <T...> const&, )
//{
//
//}


//template <typename U>
//constexpr auto operator > (common_s <> const& n, U&& rhs) -> auto
//{
//    return ;
//}

//template <typename T>
//constexpr auto operator < (type_t <T> const&, common_s <> const&) -> auto
//{
//    return common_s <T> {};
//}

//static_assert (is_same_v <decltype (types <int, char> | common), common_s <int, char>>, "");

//template <typename... T, typename U>
//constexpr auto operator > (common_s <T...> const& n, U&& rhs) -> auto
//{
//    return common_s <T..., decay_t <U>> {};
//}



//template <typename... direktiv, typename T>
//constexpr auto operator < (T&&, common_s <direktiv...> const&) -> auto
//{
//    return common_s <decay_t <T>> {};
//}



template <typename Derived1, typename Derived2>
constexpr auto operator + (transformer <Derived1> const& a, transformer <Derived2> const&)
{
    return transformer <typename Derived1::template add_transformer <Derived2>> {};
}

template <typename Types, typename Derived1, typename Derived2>
constexpr auto operator and (transformations <Types, transformer <Derived1>> const& a, transformer <Derived2> const&)
{
    return transformations <Types, transformer <typename Derived1::template add_transformer <Derived2>>> {};
}


template <typename T, typename Derived1>
constexpr auto operator | (type_t <type_t <T>> const&, transformer <Derived1> const& t) -> auto
{
    return type_t <T> {} | t;
}



template <typename T, typename Derived1>
constexpr auto operator | (type_t <T> const&, transformer <Derived1> const& t) -> auto
{
    return _types <T> {} | t;
}

template <typename... T, typename Derived1>
constexpr auto operator | (_types <T...> const&, transformer <Derived1> const& t) -> auto
{
    return transformations <_types <T...>, transformer <Derived1>> {};
}

template <typename... T, typename Transformer>
requires (can_transform <Transformer, T...>)
constexpr auto operator | (_types <T...> const&, Transformer const& t) -> auto
{
    return transformations <_types <T...>, Transformer> {};
}

template <typename T, typename Derived1, typename Derived2>
constexpr auto operator | (transformations <T, transformer <Derived1>> const&, Derived2 const& t) -> auto
{
    return transformations <T, transformer <typename Derived1::template add_transformer <Derived2>>> {};
}

template <typename T, typename Derived1, typename Derived2>
constexpr auto operator and (transformations <T, transformer <Derived1>> const&, Derived2 const& t) -> auto
{
    return transformations <T, transformer <typename Derived1::template add_transformer <Derived2>>> {};
}




template <typename T, typename Derived1>
constexpr auto operator | (T&&, transformer <Derived1> const&) -> auto
{
    return transformations <std::decay_t <T>, transformer <Derived1>> {};
}

static_assert (std::is_same_v <transformations <_types <int, char, double>, transformer <common_s <>>>, decltype (types_t <int, char, double> | common)>, "");

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
{std::cout<<"and"<<std::endl;
    return type_t <T..., U...> {};
}



































//template <typename T, typename U>
//concept has_overloaded_same_type = requires (T const& t)
//{
//    {t.template same_type <U> ()} -> __same <bool>;
//
//    //    {U::template same_type <U> (declval <U const&> ())} -> __same <bool>;
//};
//
//
//
//
//
//template <typename T, typename U>
//constexpr auto operator== (type_t <T> const&, U const& u) -> bool
//requires (has_overloaded_same_type <U, T>)
//{
//    return u.template same_type <T> ();
//}
//
//template <typename T, typename U>
//constexpr auto operator== (type_t <T> const&, U const&) -> bool
//requires (not has_overloaded_same_type <U, T>)
//{
//    return is_same_v <T, U>;
//}

#endif
