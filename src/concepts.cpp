#include "concepts.hpp"



struct operand {};





struct operator_add
{
    template <typename new_transformer>
    using add_transformer = std::true_type;
};


static_assert (can_add_transformer <operator_add, operand> == true, "");







struct operator_transform
{
    template <template <typename...> typename >
    using transform = std::true_type;
};
