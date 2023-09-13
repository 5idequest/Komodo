#include <komodo/komodo.hpp>

int main() {
  Komodo::VulkanWindow window;
  
  while (window.IsOpen()) {
    Komodo::PollWindowEvents();
  }
}
