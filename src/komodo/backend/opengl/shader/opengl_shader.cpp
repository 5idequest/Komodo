#include "opengl_shader.hpp"

// spirv-cross is also included with the Vulkan SDK.
// Make sure not to #include <spirv-cross/spirv_xxx> as this will cause
// mismatched header and cpp/lib files and you will end up with linker errors
#include <spirv_glsl.hpp>
#include <glad/gl.h>

#include "komodo/debug/assert.hpp"
#include "komodo/shader/shader.hpp"

namespace Komodo {

static void ApplyOpenGLCompileOptions(spirv_cross::CompilerGLSL* compiler, GLenum shader_type) {
	spirv_cross::CompilerGLSL::Options options;

  // macOS only supports OpenGL versions up to 4.1 due to OpenGL being deprecated on the platform.
  // Unfortunately, explicit binding points are a 4.2 feature. Therefore we have to tell SPIRV-Cross
  // not to generate binding points for uniform buffers on macOS and other platforms that don't support OpenGL
	// versions 4.2 and later.
	if (options.version < 420) {
		options.enable_420pack_extension = false;
	}

	// Komodo uses Vulkan coordinate system for all backends
	// Tell SPIRV-Cross to insert an additional gl_Position.y = -gl_Position.y at the end of the vertex shader
	if (shader_type == GL_VERTEX_SHADER) {
		options.vertex.flip_vert_y = true;
	}

	compiler->set_common_options(options);
}

static GLuint CreateShaderModule(std::shared_ptr<std::vector<uint32_t>> spv, GLenum shader_type) {

  spirv_cross::CompilerGLSL* compiler = new spirv_cross::CompilerGLSL(*spv);
  ApplyOpenGLCompileOptions(compiler, shader_type);
  std::string glsl_code = compiler->compile();
  delete compiler;

  GLuint shader = glCreateShader(shader_type);
	const GLchar* source_ptr = (const GLchar*)glsl_code.c_str();

  glShaderSource(shader, 1, &source_ptr, 0);
  glCompileShader(shader);

#ifdef KOMODO_BUILD_DEBUG
  GLint is_compiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
  if (!is_compiled) {
    GLint max_length = 0;
	  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

	  // max_length includes the null character
	  std::vector<GLchar> info_log(max_length);
	  glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);
	  glDeleteShader(shader);

		KM_ASSERT(false, info_log.data());
	  return -1;
  }
#endif

  return shader;
}


OpenGlShader::OpenGlShader(const ShaderCreateInfo& shader_info) {
  shader_program = glCreateProgram();

  auto spv = LoadShaderModules(shader_info);

  std::vector<unsigned int> shader_modules;

  if (spv->vert) {
    int shader = CreateShaderModule(spv->vert, GL_VERTEX_SHADER);
    glAttachShader(shader_program, shader);
    shader_modules.push_back(shader);
  }
  if (spv->frag) {
    int shader = CreateShaderModule(spv->frag, GL_FRAGMENT_SHADER);
    glAttachShader(shader_program, shader);
    shader_modules.push_back(shader);
  }

  glLinkProgram(shader_program);

#ifdef KOMODO_BUILD_DEBUG
	GLint is_linked = 0;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &is_linked);
	if (!is_linked) {
		GLint max_length = 0;
		glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &max_length);
		std::vector<GLchar> info_log(max_length);
		glGetProgramInfoLog(shader_program, max_length, &max_length, &info_log[0]);
	
		glDeleteProgram(shader_program);
		for (auto shader : shader_modules) {
			glDeleteShader(shader);
		}

		KM_ASSERT(false, info_log.data());
		return;
	}
#endif

	for (auto shader : shader_modules) {
    glDetachShader(shader_program, shader);
    glDeleteShader(shader);
	}
}

void OpenGlShader::Bind() {
	glUseProgram(shader_program);
}

}
