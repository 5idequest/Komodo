#include "glfw_window_position.hpp"

#include <algorithm>

#include <GLFW/glfw3.h>

namespace Komodo {
namespace Glfw {

/* Finds the monitor that a GLFW window mostly lies on
   The window can then be positioned relative to that monitor
 */
static GLFWmonitor* FindBestMonitor(GLFWwindow* glfw_window) {
  int monitor_count;
  GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

  int window_x, window_y, window_width, window_height;
  glfwGetWindowSize(glfw_window, &window_width, &window_height);
  glfwGetWindowPos(glfw_window, &window_x, &window_y);

  GLFWmonitor* best_monitor = nullptr;
  int best_area = 0;

  for (int i = 0; i < monitor_count; ++i) {
    GLFWmonitor* monitor = monitors[i];

    int monitor_x, monitor_y;
    glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) continue;

    int area_min_x = std::max(window_x, monitor_x);
    int area_min_y = std::max(window_x, monitor_y);

    int area_max_x = std::min(window_x + window_width, monitor_x + mode->width);
    int area_max_y = std::min(window_x + window_height, monitor_x + mode->height);

    int area = (area_max_x - area_min_x) * (area_max_y - area_min_y);

    if (area > best_area) {
      best_area = area;
      best_monitor = monitor;
    }
  }

  return best_monitor;
}

/* Finds a monitor by its number (0, 1, 2...)
   If the monitor doesn't exist, returns the primary monitor
 */
static GLFWmonitor* GetMonitor(int monitor) {
  int monitor_count;
  GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
  if (monitor > monitor_count) {
    return 0;
  }
  else {
    return monitors[monitor];
  }
}

void PositionWindow(GLFWwindow* glfw_window, const WindowPositionInfo& position) {
  GLFWmonitor* monitor;
  if (position.monitor == -1) {
    monitor = FindBestMonitor(glfw_window);
  }
  else {
    monitor = GetMonitor(position.monitor);
  }
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  if (!mode) return;

  int monitor_x, monitor_y;
  glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

  int window_width, window_height;
  glfwGetWindowSize(glfw_window, &window_width, &window_height);

  if (position.alignment == WindowAlignment::kCenter) {
    int window_x = monitor_x + (mode->width - window_width) / 2 + position.x;
    int window_y = monitor_y + (mode->height - window_height) / 2 + position.y;
    glfwSetWindowPos(glfw_window, window_x, window_y);
  }
  else {
    int window_x = monitor_x + position.x;
    int window_y = monitor_y + position.y;
    glfwSetWindowPos(glfw_window, window_x, window_y);
  }
}


}
}
