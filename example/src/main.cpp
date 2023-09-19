#include <komodo/komodo.hpp>

int main() {
  Komodo::VulkanInstance komodo;
  auto window = komodo.CreateWindow();
  
  while (window->IsOpen()) {
    Komodo::PollWindowEvents();
  }
}
