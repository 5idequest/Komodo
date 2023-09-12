#include <komodo/komodo.hpp>

int main() {
  Komodo::OpenGlWindow window;
  
  while (window.IsOpen()) {
    Komodo::PollWindowEvents();
  }
}
