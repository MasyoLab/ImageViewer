//==========================================================================
// enum operator [enum_operator.hpp]
// author: MasyoLab
//==========================================================================
#pragma once
#include <type_traits>
#include "mdx.h"

_MDX_COMMON_BEGIN

//==========================================================================
// enum�@�\�g��
//==========================================================================
namespace enum_operator {
    // ���Z
    template<typename T>
    struct calculation : std::false_type {};
    // Bit���Z
    template<typename T>
    struct has_bitwise_operators : std::false_type {};
    // AND/OR���Z
    template<typename T>
    struct has_and_or_operators : has_bitwise_operators<T> {};
}

//==========================================================================
// ���^�擾
//==========================================================================
namespace type_traits {
    template<bool con> using concept_t = typename std::enable_if<con, std::nullptr_t>::type;
    template<typename T> using underlying_type_t = typename std::underlying_type<T>::type;//C++11�ɂ͂Ȃ�
}

//==========================================================================
// ���^�擾
//==========================================================================
namespace detail {
    using namespace type_traits;
    template<typename T, concept_t<std::is_enum<T>::value> = nullptr>
    constexpr underlying_type_t<T> underlying_cast(T e) { return static_cast<underlying_type_t<T>>(e); }
}

_MDX_COMMON_END

//==========================================================================
// AND/OR���Z ��������
//==========================================================================
template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::has_and_or_operators<T>::value> = nullptr>
constexpr T operator&(T l, S r) {
    return static_cast<T>(mdx::common::detail::underlying_cast((T)l) & mdx::common::detail::underlying_cast((T)r));
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::has_and_or_operators<T>::value> = nullptr>
T& operator&=(T& l, S r) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) & mdx::common::detail::underlying_cast((T)r));
    return l;
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::has_and_or_operators<T>::value> = nullptr>
constexpr T operator|(T l, S r) {
    return static_cast<T>(mdx::common::detail::underlying_cast((T)l) | mdx::common::detail::underlying_cast((T)r));
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::has_and_or_operators<T>::value> = nullptr>
T& operator|=(T& l, S r) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) | mdx::common::detail::underlying_cast((T)r));
    return l;
}

//==========================================================================
// AND/OR���Z �����܂�
//==========================================================================

//==========================================================================
// Bit���Z ��������
//==========================================================================
template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::has_bitwise_operators<T>::value> = nullptr>
constexpr T operator^(T l, S r) {
    return static_cast<T>(mdx::common::detail::underlying_cast((T)l) ^ mdx::common::detail::underlying_cast((T)r));
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::has_bitwise_operators<T>::value> = nullptr>
T& operator^=(T& l, S r) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) ^ mdx::common::detail::underlying_cast((T)r));
    return l;
}

template<typename T, mdx::common::type_traits::concept_t<mdx::common::enum_operator::has_bitwise_operators<T>::value> = nullptr>
constexpr T operator~(T op) {
    return static_cast<T>(~mdx::common::detail::underlying_cast(op));
}

//==========================================================================
// Bit���Z �����܂�
//==========================================================================

//==========================================================================
// ���Z ��������
//==========================================================================
template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator+(T l, S r) {
    return static_cast<T>(mdx::common::detail::underlying_cast((T)l) + mdx::common::detail::underlying_cast((T)r));
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator-(T l, S r) {
    return static_cast<T>(mdx::common::detail::underlying_cast((T)l) - mdx::common::detail::underlying_cast((T)r));
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator/(T l, S r) {
    return static_cast<T>(mdx::common::detail::underlying_cast((T)l) / mdx::common::detail::underlying_cast((T)r));
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator*(T l, S r) {
    return static_cast<T>(mdx::common::detail::underlying_cast((T)l) * mdx::common::detail::underlying_cast((T)r));
}

template<typename T, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator++(T & l) {
    l = static_cast<T>(mdx::common::detail::underlying_cast(l) + mdx::common::detail::underlying_cast((T)1));
    return l;
}

template<typename T, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator--(T & l) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) - mdx::common::detail::underlying_cast((T)1));
    return l;
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator+=(T &l, S r) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) + mdx::common::detail::underlying_cast((T)r));
    return l;
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator-=(T &l, S r) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) - mdx::common::detail::underlying_cast((T)r));
    return l;
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator*=(T &l, S r) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) * mdx::common::detail::underlying_cast((T)r));
    return l;
}

template<typename T, typename S, mdx::common::type_traits::concept_t<mdx::common::enum_operator::calculation<T>::value> = nullptr>
constexpr T operator/=(T &l, S r) {
    l = static_cast<T>(mdx::common::detail::underlying_cast((T)l) / mdx::common::detail::underlying_cast((T)r));
    return l;
}

//==========================================================================
// ���Z �����܂�
//==========================================================================

#if 0
/*

enum�Aenum class �̌^����<T>�ɓ����Ƃ��ɂ�萔�w�I�������\�ɂ���class�ł�

template<> struct enum_operator::calculation<T> : std::true_type {};
template<> struct enum_operator::has_and_or_operators<T> : std::true_type {};
template<> struct enum_operator::has_bitwise_operators<T> : std::true_type {};

*/
#endif