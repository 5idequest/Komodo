#include "vulkan_shader.hpp"

#include <volk.h>

#include "komodo/shader/shader.hpp"
#include "komodo/shader/shader_reflection.hpp"
#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "komodo/backend/vulkan/shader/vulkan_shader_data.hpp"

namespace Komodo {

static VkShaderModule CreateShaderModule(VulkanInstanceData* instance, const std::vector<uint32_t>& spv) {
  VkShaderModuleCreateInfo shader_info { };
  shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  shader_info.codeSize = spv.size() * sizeof(uint32_t);
  shader_info.pCode = spv.data();
  VkShaderModule shader_module;
  VK_CALL(vkCreateShaderModule(instance->device, &shader_info, instance->allocator, &shader_module));
  return shader_module;
}

static VkPipelineShaderStageCreateInfo CreateShaderStageCreateInfo(VkShaderModule module, VkShaderStageFlagBits stage) {
  VkPipelineShaderStageCreateInfo shader_stage_info { };
  shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stage_info.stage = stage;
  shader_stage_info.module = module;
  shader_stage_info.pName = "main";
  return shader_stage_info;
}

VulkanShader::VulkanShader(VulkanInstanceData* instance, const ShaderCreateInfo& shader_info) : instance(instance) {
  shader = new VulkanShaderData();

  auto spv = LoadShaderModules(shader_info);
  auto reflection = ShaderReflectionDetails(spv);
  
  std::vector<VkShaderModule> shader_modules;
  std::vector<VkPipelineShaderStageCreateInfo> shader_stages;
  if (spv->vert) {
    VkShaderModule module = CreateShaderModule(instance, *spv->vert);
    shader_modules.push_back(module);
    shader_stages.push_back(std::move(CreateShaderStageCreateInfo(module, VK_SHADER_STAGE_VERTEX_BIT)));
  }
  if (spv->frag) {
    VkShaderModule module = CreateShaderModule(instance, *spv->frag);
    shader_modules.push_back(module);
    shader_stages.push_back(std::move(CreateShaderStageCreateInfo(module, VK_SHADER_STAGE_FRAGMENT_BIT)));
  }

  VkPipelineVertexInputStateCreateInfo vertex_input_info { };
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

  VkPipelineInputAssemblyStateCreateInfo input_assembly { };
  input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  std::vector<VkDynamicState> dynamic_states = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };

  VkPipelineDynamicStateCreateInfo dynamic_state_info { };
  dynamic_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state_info.dynamicStateCount = dynamic_states.size();
  dynamic_state_info.pDynamicStates = dynamic_states.data();
  
  VkPipelineRasterizationStateCreateInfo rasterizer_info { };
  rasterizer_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer_info.depthClampEnable = VK_FALSE;
  rasterizer_info.rasterizerDiscardEnable = VK_FALSE;
  rasterizer_info.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer_info.lineWidth = 1.0f;
  rasterizer_info.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer_info.depthBiasEnable = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling_info { };
  multisampling_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling_info.sampleShadingEnable = VK_FALSE;
  multisampling_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineColorBlendAttachmentState color_blend_attachment { };
  color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_FALSE;
  color_blend_attachment.blendEnable = VK_TRUE;
  color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
  color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

  VkPipelineColorBlendStateCreateInfo color_blend_info { };
  color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blend_info.logicOpEnable = VK_FALSE;
  color_blend_info.logicOp = VK_LOGIC_OP_COPY;
  color_blend_info.attachmentCount = 1;
  color_blend_info.pAttachments = &color_blend_attachment;

  VkPipelineLayoutCreateInfo pipeline_layout_info { };
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 0;
  pipeline_layout_info.pSetLayouts = nullptr;
  pipeline_layout_info.pushConstantRangeCount = 0;
  pipeline_layout_info.pPushConstantRanges = nullptr;
  VK_CALL(vkCreatePipelineLayout(instance->device, &pipeline_layout_info, instance->allocator, &shader->pipeline_layout));

  for (auto shader_module : shader_modules) {
    vkDestroyShaderModule(instance->device, shader_module, instance->allocator);
  }
}

VulkanShader::~VulkanShader() {
  vkDestroyPipelineLayout(instance->device, shader->pipeline_layout, instance->allocator);

  delete shader;
}

void VulkanShader::Bind() {

}

}
