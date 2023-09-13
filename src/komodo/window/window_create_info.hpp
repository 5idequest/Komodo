#pragma once

#include <string>

namespace Komodo {

enum class WindowAlignment {
  kCenter,
  kTopLeft,
};

struct WindowPositionInfo {
  WindowAlignment alignment = WindowAlignment::kCenter;
  int x = 0;
  int y = 0;
  int monitor = -1;
};

struct WindowCreateInfo {
  std::string title = "Komodo";
  int width = 1280;
  int height = 720;
  WindowPositionInfo position;
};

}
