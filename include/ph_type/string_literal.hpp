#ifndef STRING_LITERAL_HPP
#define STRING_LITERAL_HPP
#include <compare>

// Raw literal operator
void operator "" _y(const char* lit)
{
    printf("operator \"\" _dump_raw(const char*)        : ===>%s<===\n",   lit);
};

void operator "" _y (char const*, size_t);

template <typename T, T... t>
auto operator "" _ () -> T const (&) [sizeof... (t)]
{
    return {t...};
}

template <char...>
auto operator "" _ () -> void//T const (&) [sizeof... (t)]
{
//    return {t...};
}

#endif
