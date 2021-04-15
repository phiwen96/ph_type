#include <catch2/catch.hpp>
#include <ph_type/type.hpp>

using namespace std;



TEST_CASE ("standard types")
{
    int i;
    REQUIRE (type <int> == i);
    REQUIRE (i == type <int>);
    
    REQUIRE (type <char> != i);
    REQUIRE (i != type <char>);
}

struct inverted
{
    template <typename T>
    constexpr auto same_type () const -> bool
    {
        cout << "overload!" << endl;
        return false;
    }
};

TEST_CASE ("custom types")
{
    
    inverted t;
    REQUIRE (t != type <inverted>);
    REQUIRE (not (t == type <inverted>));
}
