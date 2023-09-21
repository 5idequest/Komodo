#include "shader.hpp"

#include <filesystem>

#ifdef KOMODO_COMPONENT_SHADERC
  #include <shaderc/shaderc.hpp>
#endif

#include "komodo/debug/assert.hpp"
#include "komodo/utils/file_reader.hpp"

namespace Komodo {

#ifdef KOMODO_COMPONENT_SHADERC

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

#endif // KOMODO_COMPONENT_SHADERC

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

#ifdef KOMODO_COMPONENT_SHADERC
  if (extension == ".glsl") {
    return LoadGlslShaderModule(path);
  }
#endif // KOMODO_COMPONENT_SHADERC

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
