#include <catch2/catch.hpp>
#include <ph_type/type.hpp>
#include <ph_type/string_literal.hpp>

//using namespace boost::hof;

//using namespace std;


struct same_f
{
    auto operator () (auto a, auto b) const -> bool
    {
        return a == b;
    }
};

auto inc = [] (auto a)
{
    return a + 1;
};

auto mult = [] (auto a)
{
    return a * 2;
};




struct E {};
struct A : E {};
struct B : E {
//    using value_type = int;
};
struct C : E {};

struct D {};

struct BASE
{
    friend std::ostream& operator << (std::ostream& os, BASE const&)
    {
        return os;
    }
};





template <char c>
struct __e {
    friend std::ostream& operator << (std::ostream& os, __e const& aa)
    {
        os << c;
        return os;
    }
};


template <char c>
constexpr auto _e = __e <c> {};


template <char... c>
struct __operator
{
    friend std::ostream& operator << (std::ostream& os, __operator const& aa)
    {
        ((os << c), ...);
        return os;
    }
};

template <template <char...> typename A, template <char...> typename B, char... C, char... D>
auto operator|(A <C...> a, B <D...> b)
{
    return __operator <'(', C..., ' ', '|', ' ', D..., ')'> {};
}
template <template <char...> typename A, template <char...> typename B, char... C, char... D>
auto operator and (A <C...> a, B <D...> b)
{
    return __operator <'(', C..., ' ', 'a', 'n', 'd', ' ', D..., ')'> {};
}

template <template <char...> typename A, template <char...> typename B, char... C, char... D>
auto operator or (A <C...> a, B <D...> b)
{
    return __operator <'(', C..., ' ', 'o', 'r', ' ', D..., ')'> {};
}

template <template <char...> typename A, template <char...> typename B, char... C, char... D>
auto operator + (A <C...> a, B <D...> b)
{
    return __operator <'(', C..., ' ', '+', ' ', D..., ')'> {};
}

struct A1 {};
struct A2 {};
struct A3 {};
struct A4 : A3 {};
struct A5 : A3 {};
struct A6 : A3 {};
struct A7 : A3 {};

template <typename...>
struct HEM;

template <typename A, typename B, typename... C>
concept has_common = requires(A a, B b) {
    true ? a : b;
};

template <typename A>
struct HEM <A>
{
    using type = std::true_type;
};

template <typename A, typename B>
requires (not has_common <A, B>)
struct HEM <A, B> : std::false_type {

};

template <typename A, typename B>
requires (has_common <A, B>)
struct HEM <A, B> : std::true_type {

};

//template <typename A, typename B, typename... C>
//struct HEM <A, B, C...> {
//    using type = conditional_t <has_common <A, B>, typename HEM <decltype (true?declval<A>():declval<B>()), C...>::type, false_type>;
//};

template <typename A, typename B, typename C, typename... D>
requires (has_common <A, B>)
struct HEM <A, B, C, D...> : std::true_type {
    using type = std::conditional_t <has_common <B, C>, typename HEM <C, D...>::type, std::false_type>;

};


template <typename Derived>
struct _AA {using type = Derived;};
struct _BB : _AA <_BB> {};
TEST_CASE ("")
{
    
    
//    auto a = types <type <int>>;
    transformer <common_s <>> tr = common;
    
//    transformations <_types <A, B, C>, transformer <common_s <>>> _vv = types_t <A, B, C> | common;
    
    auto vv = types_t <int, double, char> | common;
    
    

    auto as = [] <typename T, typename U> () -> decltype (true ? declval <T> () : declval <U> ()) {};
    
//    auto d = as.operator ()<A1, A2>();
    HEM <A3, A4> h;
    
    transformations <_types <int, double, char>, transformer <common_s <>>> vv2 = types_t <int, double, char> | common;
//    std::string ss = types_t <int, double, char> | same <as> ;
    
    
    
    std::cout << (_e <'0'> and _e <'1'> and _e <'2'> and _e <'3'> and _e <'4'> | _e <'5'> + _e <'6'> or _e <'7'>) << std::endl;
    std::cout << (_e <'0'> or _e <'1'> | _e <'x'> and _e <'2'> or _e <'3'> and _e <'4'> | _e <'5'> | _e <'6'>) << std::endl;

//    "ew"_y;
    230_y;
    std::cout << L"x = " << std::endl;
    std::cout << L"y = " << std::endl;
    3_;
    "ds"_;
    common;
}



TEST_CASE ("standard types")
{
//    int i;
//    REQUIRE (type <int> == i);
//    REQUIRE (i == type <int>);
//
//    REQUIRE (type <char> != i);
//    REQUIRE (i != type <char>);
}

struct inverted
{
    template <typename T>
    constexpr auto same_type () const -> bool
    {
//        cout << "overload!" << endl;
        return false;
    }
};

TEST_CASE ("custom types")
{
    
//    inverted t;
//    REQUIRE (t != type <inverted>);
//    REQUIRE (not (t == type <inverted>));
}
