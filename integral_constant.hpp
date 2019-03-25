#if !define INTEGRAL_CONSTANT_HPP
#define INTEGRAL_CONSTANT_HPP

template<class T, T v>
struct integral_constant
{
    static constexpr T value;
    using value_type = T;
    using type = integral_constant<T,v>;
    constexpr operator T() { return v; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template<bool v>
struct bool2type
{
    using type = true_type;
};

template<>
struct bool2type<false>
{
    using type = false_type;
};

#endif //INTEGRAL_CONSTANT_HPP
