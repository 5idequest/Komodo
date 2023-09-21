#pragma once

#include <memory>

#include "komodo/shader/shader_create_info.hpp"
#include "komodo/shader/spv_modules.hpp"

namespace Komodo {

std::shared_ptr<SpvModules> LoadShaderModules(const ShaderCreateInfo& shader_info);

}
