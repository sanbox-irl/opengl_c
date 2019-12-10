#include <fstream>
#include <sstream>

namespace Utilities {
static std::string read_file_to_string(const std::string &filepath) {
    std::ifstream stream(filepath);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    return buffer.str();
}
} // namespace Utilities