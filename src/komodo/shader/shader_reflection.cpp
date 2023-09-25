#include "shader_reflection.hpp"

#include <cstdint>
#include <vector>

// spirv-cross is also included with the Vulkan SDK. Make sure not to #include <spirv-cross/spirv_xxx> as this will
// cause mismatched header and cpp files and you will end up with linker errors
#include <spirv_glsl.hpp>

#include "komodo/shader/shader_data_type.hpp"
#include "komodo/shader/spv_modules.hpp"

namespace Komodo {

ShaderDataType FindInputVectorSize(uint32_t size) {
  switch (size) {
    case 1:  return ShaderDataType::kFloat;
    case 2:  return ShaderDataType::kFloat2;
    case 3:  return ShaderDataType::kFloat3;
    case 4:  return ShaderDataType::kFloat4;
    default: return ShaderDataType::kUndefined;
  }
}

ShaderReflectionDetails::ShaderReflectionDetails(std::shared_ptr<SpvModules> spv) {
  std::unordered_map<size_t, ShaderDataType> vertex_input_map;
  
  auto reflect_vertex_module = [&](std::shared_ptr<std::vector<uint32_t>> spv){
    spirv_cross::CompilerGLSL* glsl = new spirv_cross::CompilerGLSL(*spv);
    spirv_cross::ShaderResources* resources = new spirv_cross::ShaderResources(glsl->get_shader_resources());

    for (auto& stage_input : resources->stage_inputs) {
      uint32_t location = glsl->get_decoration(stage_input.id, spv::DecorationLocation);
      spirv_cross::SPIRType type = glsl->get_type(stage_input.type_id);
      ShaderDataType data_type = FindInputVectorSize(type.vecsize);
      if (data_type != ShaderDataType::kUndefined) {
        vertex_input_map.emplace(location, data_type);
      }
    }
    
    delete resources;
    delete glsl;
  };
  
  if (spv->vert) {
    reflect_vertex_module(spv->vert);
  }
  
  std::vector<BufferElement> buffer_elements;
  for (int i = 0; i < vertex_input_map.size(); ++i) {
    buffer_elements.push_back(vertex_input_map.at(i));
  }
  vertex_input_layout = buffer_elements;
}

}
