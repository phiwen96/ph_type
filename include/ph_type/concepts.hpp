#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP




template <typename Transformer, template <typename...> typename TypesContainer, typename... Types>
concept can_transform = requires {
    typename Transformer::template transform <TypesContainer, Types...>;
};



template <typename CurrentTransformer, typename NewTransformer>
concept can_add_transformer = requires {
    typename CurrentTransformer::template add_transformer <NewTransformer>;
};







#endif
