#ifndef environment_hpp
#define environment_hpp

#include <cstdlib>
#include <string>
#include <fstream>

namespace EnvUtil {

    // Load .env file and populate environment variables
    inline void load_env(const std::string& path = ".env") {
        std::ifstream file(path);
        if (!file.is_open()) {
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            const auto pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            if (!key.empty()) {
                setenv(key.c_str(), value.c_str(), 1);
            }
        }
    }

    // Function to get environment variable value
    inline std::string get_env_var(const std::string& var_name) {
        const char* val = std::getenv(var_name.c_str());
        if (val == nullptr) {
            return "";
        }
        return std::string(val);
    }

} // namespace EnvUtil

#endif // environment_hpp