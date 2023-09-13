#pragma once

#include <string>

namespace Komodo {
namespace OpenGl {

/* If a title is supplied, returns that title. Otherwise, returns the default title with build information.
 */
std::string GenerateWindowTitle(const std::string& initial_title);

}
}
