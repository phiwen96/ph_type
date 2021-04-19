#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP


template <typename Transformer, template <typename...> typename TypesContainer, typename... Types>
concept can_transform_types = requires {
    typename Transformer::template transform <TypesContainer, Types...>;
};

template <typename Transformer, template <typename...> typename NextTransformer>
concept can_add_transformer = requires {
    typename Transformer::template add_transformer <NextTransformer>;
};







#endif
