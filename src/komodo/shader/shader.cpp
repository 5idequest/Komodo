#include "shader.hpp"

#include <filesystem>

#include <shaderc/shaderc.hpp>

#include "komodo/debug/assert.hpp"
#include "komodo/utils/file_reader.hpp"

namespace Komodo {

std::shared_ptr<std::vector<uint32_t>> LoadGlslShaderModule(const std::string& path) {
  std::string glsl_code = ReadFile(path);

  return nullptr;
}

std::shared_ptr<std::vector<uint32_t>> LoadShaderModule(const std::string& path) {
  std::string extension = std::filesystem::path(path).extension().string();

  if (extension == ".glsl") {
    return LoadGlslShaderModule(path);
  }
  else {
    KM_ASSERT(false, "Shader file extension not recognised!");
    return nullptr;
  }
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
