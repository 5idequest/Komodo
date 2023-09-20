#pragma once

#ifdef KOMODO_BUILD_DEBUG

  #include "komodo/debug/exception.hpp"

  #define KM_ASSERT_WITH_MSG(x, what) do { \
    if (!(x)) { \
      throw Exception(what); \
    } \
  } while(0)

#endif // KOMODO_BUILD_DEBUG

#ifdef KOMODO_BUILD_RELEASE

  #define KM_ASSERT_WITH_MSG(x, what) x

#endif

#define KM_ASSERT_WITHOUT_MSG(x, what) KM_ASSERT_WITH_MSG(x, "Assert failed!")

#define GET_3RD_ARG(arg1, arg2, arg3, arg4, ...) arg4
#define KM_ASSERT_MACRO_CHOOSER(...) \
    GET_3RD_ARG(__VA_ARGS__, \
    KM_ASSERT_WITH_MSG, KM_ASSERT_WITHOUT_MSG, )

#define KM_ASSERT(...) KM_ASSERT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
