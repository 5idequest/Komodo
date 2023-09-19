#pragma once

#ifdef KOMODO_BUILD_DEBUG

  #include <volk.h>
  #include <vulkan/vk_enum_string_helper.h>

  #include "komodo/backend/vulkan/debug/vulkan_exception.hpp"
  #include "komodo/utils/concat.hpp"

  #define VK_CALL(x) do { \
    VkResult KM_CONCAT(result, __LINE__) = x; \
    if (KM_CONCAT(result, __LINE__) != VK_SUCCESS) { \
      throw VulkanException(string_VkResult(KM_CONCAT(result, __LINE__))); \
    } \
  } while(0)

#endif // KOMODO_BUILD_DEBUG

#ifdef KOMODO_BUILD_RELEASE
  #define VK_CALL(x) x
#endif // KOMODO_BUILD_RELEASE
