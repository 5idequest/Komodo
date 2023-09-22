#include <komodo/komodo.hpp>

int main() {
  Komodo::VulkanInstance komodo;
  auto window = komodo.CreateWindow();

  Komodo::ShaderCreateInfo shader_info;
  shader_info.vert_path = "res/shaders/test.vert.glsl";
  shader_info.frag_path = "res/shaders/test.frag.glsl";
  auto shader = komodo.CreateShader(shader_info);
  
  while (window->IsOpen()) {
    Komodo::PollWindowEvents();
    komodo.BeginFrame();
    shader->Bind();
    komodo.EndFrame();
  }
}
