#pragma once

#ifdef KOMODO_BUILD_DEBUG

  #include "komodo/debug/exception.hpp"

  #define KM_ASSERT(x) do { \
    if (!(x)) { \
      throw Exception("Assert failed!"); \
    } \
  } while(0)

#endif // KOMODO_BUILD_DEBUG

#ifdef KOMODO_BUILD_RELEASE

  #define KM_ASSERT(x)

#endif
