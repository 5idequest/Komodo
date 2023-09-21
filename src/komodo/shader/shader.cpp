#include "shader.hpp"

#include <filesystem>

// shaderc is also included with the Vulkan SDK.
// Make sure not to #include <shaderc/shaderc.hpp> as this will cause
// mismatched header and cpp/lib files and you will end up with linker errors
#include <shaderc.hpp>

#include "komodo/debug/assert.hpp"
#include "komodo/utils/file_reader.hpp"

namespace Komodo {

std::shared_ptr<std::vector<uint32_t>> LoadGlslShaderModule(const std::string& path) {
  std::string glsl_code = ReadTextFile(path);

  shaderc::Compiler compiler;
  auto result = compiler.CompileGlslToSpv(glsl_code, shaderc_shader_kind::shaderc_glsl_vertex_shader, path.c_str());

  auto spv = std::make_shared<std::vector<uint32_t>>();
  for (uint32_t b : result) {
    spv->push_back(b);
  }

  return spv;
}

std::shared_ptr<std::vector<uint32_t>> LoadSpvShaderModule(const std::string& path) {
  auto spv = std::make_shared<std::vector<uint32_t>>();
  *spv = ReadSpvBinaryFile(path);
  return spv;
}

std::shared_ptr<std::vector<uint32_t>> LoadShaderModule(const std::string& path) {
  std::string extension = std::filesystem::path(path).extension().string();

  if (extension == ".spv") {
    return LoadSpvShaderModule(path);
  }
  if (extension == ".glsl") {
    return LoadGlslShaderModule(path);
  }

  KM_ASSERT(false, "Shader file extension not recognised!");
  return nullptr;
}

std::shared_ptr<SpvModules> LoadShaderModules(const ShaderCreateInfo& shader_info) {
  auto spv = std::make_shared<SpvModules>();

  if (!shader_info.vert_path.empty()) {
    spv->vert = LoadShaderModule(shader_info.vert_path);
  }
  if (!shader_info.frag_path.empty()) {
    spv->frag = LoadShaderModule(shader_info.frag_path);
  }

  return spv;
}

}
