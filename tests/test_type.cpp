#include <catch2/catch.hpp>
#include <ph_type/type.hpp>

//using namespace boost::hof;

using namespace std;


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





struct A {};
struct B : A {
//    using value_type = int;
};
struct C : B {};

struct D {};

struct BASE
{
    friend ostream& operator << (ostream& os, BASE const&)
    {
        return os;
    }
};





template <char c>
struct __e {
    friend ostream& operator << (ostream& os, __e const& aa)
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
    friend ostream& operator << (ostream& os, __operator const& aa)
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


//template <template <typename...> typename A, template <typename...> typename B, typename... C, typename... D>
//auto operator|(A <C...> a, B <D...> b)
//{
//    return PIPE <A <C...>, B <D...>> {};
//}
//template <template <typename...> typename A, template <typename...> typename B, typename... C, typename... D>
//auto operator and (A <C...> a, B <D...> b)
//{
//    return AND <A <C...>, B <D...>> {};
//}
//
//template <template <typename...> typename A, template <typename...> typename B, typename... C, typename... D>
//auto operator or (A <C...> a, B <D...> b)
//{
//    return OR <A <C...>, B <D...>> {};
//}


TEST_CASE ("")
{
//    constexpr auto a = type <int>;
    auto a = types <type <int>>;
    
//    auto dd = common_type_t<A, B> {};
//    int dsd = 3 <common> 4;
    
    transformations <_types <A, B, C>, transformer <common_s <>>> _vv = types_t <A, B, C> | common;
    
    auto vv = types_t <A, B, C> | common ;
    
//    AA {} and BB {} and CC {} or DD {} and CC {};
    
    cout << (_e <'0'> and _e <'1'> and _e <'2'> or _e <'3'> and _e <'4'> | _e <'5'> | _e <'6'>) << endl;
    cout << (_e <'0'> or _e <'1'> | _e <'x'> and _e <'2'> or _e <'3'> and _e <'4'> | _e <'5'> | _e <'6'>) << endl;

//    AA {} and BB {} | CC {};
    
//    AA {} and BB {} | CC {} and DD {};
    
//    AA {} and BB {} | CC {} | DD {};
    
//    transformations <_types <A, B, C>, transformer <common_s <>>> vv = types_t <A, B, C> | common;

    
    
//    common_s <B, C>
    
//    auto n = type <B> <common> type <C> | 4;
    
    
//    auto n = type <B> <common> type <C> | value_type;
    
//    int n2 = B{} <common> C{} | value_type;
    
    
//    cout << sds (3) << endl;
    

//    cout << i << endl;
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
