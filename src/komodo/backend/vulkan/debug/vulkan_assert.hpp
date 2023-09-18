#pragma once

#ifdef KOMODO_BUILD_DEBUG

  #include <vulkan/vulkan.h>
  #include <vulkan/vk_enum_string_helper.h>

  #include "komodo/backend/vulkan/debug/vulkan_exception.hpp"

  #define KOMODO_CONCAT1(x, y) x##y
  #define KOMODO_CONCAT(x, y) KOMODO_CONCAT1(x, y)

  #define VK_CALL(x) do { \
    VkResult KOMODO_CONCAT(result, __LINE__) = x; \
    if (KOMODO_CONCAT(result, __LINE__) != VK_SUCCESS) { \
      throw VulkanException(string_VkResult(KOMODO_CONCAT(result, __LINE__))); \
    } \
  } while(0)

#endif // KOMODO_BUILD_DEBUG

#ifdef KOMODO_BUILD_RELEASE
  #define VK_CALL(x) x
#endif // KOMODO_BUILD_RELEASE
