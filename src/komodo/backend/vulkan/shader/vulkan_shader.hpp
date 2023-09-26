#pragma once

#include "komodo/shader/shader_create_info.hpp"

namespace Komodo {

struct VulkanShaderData;
struct VulkanInstanceData;

class VulkanShader {
public:
  VulkanShader(VulkanInstanceData* instance, const ShaderCreateInfo& shader_info);
  ~VulkanShader();

public:
  void Bind();

private:
  VulkanShaderData* shader;
  VulkanInstanceData* instance;
};

}
