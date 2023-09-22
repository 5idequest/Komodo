#pragma once

#include "komodo/shader/shader_create_info.hpp"

namespace Komodo {

struct VulkanInstanceData;

class VulkanShader {
public:
  VulkanShader(VulkanInstanceData* instance, const ShaderCreateInfo& shader_info);

public:
  void Bind();
};

}
