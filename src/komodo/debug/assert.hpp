#pragma once

#ifdef KOMODO_BUILD_DEBUG

  #include "komodo/debug/exception.hpp"

  #define KM_ASSERT(x, what) do { \
    if (!(x)) { \
      throw Exception(what); \
    } \
  } while(0)

#endif // KOMODO_BUILD_DEBUG

#ifdef KOMODO_BUILD_RELEASE

  #define KM_ASSERT(x, what)

#endif
