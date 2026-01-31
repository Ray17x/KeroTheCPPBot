#ifndef console_hpp
#define console_hpp

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>

namespace RichOut {

    // This function returns the current time as a string in HH:MM:SS format
    // It should only be used for this file internally
    // If you want a current time string, its best to use your own implementation
    // Or the DPP (D++) library discord bot library's time functions
    inline std::string current_time_string() {
        using namespace std::chrono;
        auto now = system_clock::now();
        std::time_t tt = system_clock::to_time_t(now);
        std::tm tm{};
        localtime_r(&tt, &tm);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        return oss.str();
        // Example usage:
        // std::string time_str = current_time_string();
    }

    // This Class can be called globally to access color codes for console output
    // Or just text in general that supports ANSI escape codes.
    class Colors {
        public:

            // Reset
            static constexpr const char* RESET       = "\033[0m";

            // Regular Colors
            static constexpr const char* RED         = "\033[31m";
            static constexpr const char* GREEN       = "\033[32m";
            static constexpr const char* YELLOW      = "\033[33m";
            static constexpr const char* BLUE        = "\033[34m";
            static constexpr const char* MAGENTA     = "\033[35m";
            static constexpr const char* CYAN        = "\033[36m";
            static constexpr const char* WHITE       = "\033[37m";
            static constexpr const char* BOLD        = "\033[1m";
            static constexpr const char* UNDERLINE   = "\033[4m";

            // Bold

            static constexpr const char* BOLD_RED     = "\033[1;31m";
            static constexpr const char* BOLD_GREEN   = "\033[1;32m";
            static constexpr const char* BOLD_YELLOW  = "\033[1;33m";
            static constexpr const char* BOLD_BLUE    = "\033[1;34m";
            static constexpr const char* BOLD_MAGENTA = "\033[1;35m";
            static constexpr const char* BOLD_CYAN    = "\033[1;36m";
            static constexpr const char* BOLD_WHITE   = "\033[1;37m";
    };
    // rc for Rich Cout.
    // Functions still use printf() instead of std::cout for easier formatting with colors.
    class rc {
        public:

        static void info(const std::string& msg = "") {
        // If the message was not provided, prevent it from printing anything by returning early
        // This is just to save some space in the terminal if no message is given
        // This is applied to all other functions in this class as well
            if (msg.empty()) {
                return;
            }
            const std::string now = current_time_string();
            printf("%s[%s]%s %s[i]%s %s\n", Colors::BOLD_CYAN, now.c_str(), Colors::RESET, Colors::BOLD_CYAN, Colors::RESET, msg.c_str());
            /*
            Example usage:
            RichOut::info("This is an informational message.");
            If namespace RichOut is being used, you can call info() directly:
            rc::info("This is an informational message.");
            */
            return;
        } // void info()

        static void error(const std::string& msg = "") {
            // For Error messages, we can simply state an error has occured if there is no message
            std::string message = msg;
            if (message.empty()) {
                message = "An error has occurred.";
            }
            const std::string now = current_time_string();
            printf("%s[%s]%s %s[!]%s %s\n", Colors::BOLD_RED, now.c_str(), Colors::RESET, Colors::BOLD_RED, Colors::RESET, message.c_str());
            /*
            Example usage:
            RichOut::error("This is an error message.");
            If namespace RichOut is being used, you can call error() directly:
            rc::error("This is an error message.");
            */
            return;
        } // void error()

        static void success(const std::string& msg = "") {
            // This also applies to success messages
            // A non-const str is used here to modify the message if empty
            std::string message = msg;
            if (message.empty()) {
                message = "Operation completed successfully.";
            }
            const std::string now = current_time_string();
            printf("%s[%s]%s %s[+]%s %s\n", Colors::BOLD_GREEN, now.c_str(), Colors::RESET, Colors::BOLD_GREEN, Colors::RESET, message.c_str());
            /*
            Example usage:
            RichOut::success("This is a success message.");
            If namespace RichOut is being used, you can call success() directly:
            rc::success("This is a success message.");
            */
            return;
        } // void success()

        static void warn(const std::string& msg = "") {
            if (msg.empty()) {
                return;
            }
            const std::string now = current_time_string();
            printf("%s[%s]%s %s[?]%s %s\n", Colors::BOLD_YELLOW, now.c_str(), Colors::RESET, Colors::BOLD_YELLOW, Colors::RESET, msg.c_str());
            /*
            Example usage:
            RichOut::warn("This is a warning message.");
            If namespace RichOut is being used, you can call warn() directly:
            rc::warn("This is a warning message.");
            */
            return;
        } // void warn()
    };
}


#endif // console_hpp #ifndef end