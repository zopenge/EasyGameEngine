/// @file auto_index_MACROS.h
/// 
/// Provides a construct to auto-increment an index at compile-time.
///
/// @author         Paul Watt
/// @date           5/19/2014
/// @copyright 2014 Paul Watt
//  ****************************************************************************
#ifndef AUTO_INDEX_H_INCLUDED
#define AUTO_INDEX_H_INCLUDED

#ifdef _PLATFORM_IOS_
    #include <ciso646>  // detect std::lib

	#ifdef _LIBCPP_VERSION
		// using libc++
		#include <type_traits>
		#define STD_INTEGRAL_CONSTANT   std::integral_constant
		#define STD_TRUE_TYPE           std::true_type
	#else
		// using libstdc++
		#include <tr1/type_traits>
		#define STD_INTEGRAL_CONSTANT   std::tr1::integral_constant
		#define STD_TRUE_TYPE           std::tr1::true_type
	#endif
#else
	// using libc++
	#include <type_traits>
	#define STD_INTEGRAL_CONSTANT   std::integral_constant
	#define STD_TRUE_TYPE           std::true_type
#endif


//  ***************************************************************************
/// This construct provides the compile-time equivalent of 
/// the ternary operator ?: for value selection.
///
template <bool predicate, typename T, T trueValue, T falseValue>
struct value_if
: STD_INTEGRAL_CONSTANT<T, trueValue>
{ };

//  ***************************************************************************
/// Specialization for the false condition of the value selector.
///
template <typename T, T trueValue, T falseValue>
struct value_if<false, T, trueValue, falseValue>
  : STD_INTEGRAL_CONSTANT<T, falseValue>
{ };

//  Forward Declarations *******************************************************
#define FORWARD_DECLARE_AUTO_INDEX                                              \
  template <int L>                                                              \
  struct decrement_until_match;

//  ****************************************************************************
#define ENUM_ENTRY_INVALID                                                      \
  template<int N, bool IsValidT = false>                                        \
  struct enum_entry                                                             \
    : STD_INTEGRAL_CONSTANT<bool, IsValidT>                                    \
  { };

//  ****************************************************************************
#define ENUM_ENTRY_VALID                                                        \
  template<int N>                                                               \
  struct enum_entry<N, true>                                                    \
    : STD_TRUE_TYPE                                                            \
  { };

//  ****************************************************************************
#define ENUM_ENTRY_ZERO                                                         \
  template<>                                                                    \
  struct enum_entry<0, true>                                                    \
    : STD_TRUE_TYPE                                                            \
  { };

//  ****************************************************************************
#define AUTO_INDEX_BEFORE                                                       \
  template <int L>                                                              \
  struct index_before                                                           \
    : STD_INTEGRAL_CONSTANT< int,                                              \
                              decrement_until_match<L - 1>::value               \
                            >                                                   \
  { };

//  ****************************************************************************
#define AUTO_INDEX_NEXT                                                         \
  template <int L>                                                              \
  struct auto_index                                                             \
    : STD_INTEGRAL_CONSTANT< int, index_before<L>::value + 1 >                 \
  { };

//  ****************************************************************************
#define AUTO_INDEX_ZERO                                                         \
  template <>                                                                   \
  struct auto_index<0>                                                          \
    : STD_INTEGRAL_CONSTANT< int, -1>                                          \
  { };

//  ****************************************************************************
#define DECREMENT_UNTIL_MATCH                                                   \
  template <int L>                                                              \
  struct decrement_until_match                                                  \
    : STD_INTEGRAL_CONSTANT< int,                                              \
                              value_if< enum_entry<L>::value,                   \
                                        int,                                    \
                                        auto_index<L>::value,                   \
                                        decrement_until_match<L - 1>::value     \
                                      >::value                                  \
                            >                                                   \
  { };

//  ****************************************************************************
#define DECREMENT_UNTIL_ZERO                                                    \
  template <>                                                                   \
  struct decrement_until_match<0>                                               \
    : STD_INTEGRAL_CONSTANT <int, -1>                                          \
  { };

//  ****************************************************************************
#define DECLARE_COUNTER                                                         \
  FORWARD_DECLARE_AUTO_INDEX                                                    \
  ENUM_ENTRY_INVALID                                                            \
  ENUM_ENTRY_VALID                                                              \
  ENUM_ENTRY_ZERO                                                               \
  AUTO_INDEX_BEFORE                                                             \
  AUTO_INDEX_NEXT                                                               \
  AUTO_INDEX_ZERO                                                               \
  DECREMENT_UNTIL_MATCH                                                         \
  DECREMENT_UNTIL_ZERO                                                          \
  static const size_t k_enum_base = __LINE__;

//  ****************************************************************************
#define INC_COUNTER_H(ID)                                                       \
  template<>                                                                    \
  struct enum_entry<(ID)>                                                       \
    : STD_TRUE_TYPE                                                            \
  { };

//  ****************************************************************************
#define INC_COUNTER                     INC_COUNTER_H(__LINE__ - k_enum_base)

#endif

