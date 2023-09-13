#include <komodo/komodo.hpp>

int main() {
  Komodo::VulkanInstance komodo;
  Komodo::VulkanWindow window;
  
  while (window.IsOpen()) {
    Komodo::PollWindowEvents();
  }
}
