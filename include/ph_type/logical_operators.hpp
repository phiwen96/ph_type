#pragma once
#include "operands.hpp"


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


struct __same
{
//    template <typename ChildTransformer>
//    using add_transformer = __parent <__same, ChildTransformer>;
    
//    template <template <typename...> typename T, typename... U>
//    using transform = std::conditional_t <(std::is_same_v <A, U> and ...), std::string, std::false_type>;
};
constexpr __same _same {};

struct __as {};
constexpr __as _as {};






