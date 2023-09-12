#pragma once

#include "komodo/window/window.hpp"

namespace Komodo {

class GlfwWindow : public Window {
public:
  virtual bool IsOpen() const override;
};

}
