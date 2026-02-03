#include "Utilities/ffmpegwrapping.hpp"
#include "Utilities/console.hpp"
#include <filesystem>
#include <cstdlib>
#include <stdio.h>
using namespace FFmpegWrap;
namespace fs = std::filesystem;
using namespace RichOut;

/*
    WARNING WARNING WARNING
    READ ME READ ME READ ME!!

    A FPUtil class was declared at the END of
    ffmpegwrapping.hpp to allow global access to
    the FPutility object.

    you should use FPutility to access the methods
    and members of the FPUtil class.

    DEFINING FUNCTIONS DON'T FOLLOW THIS RULE!!
    YOU NEED TO USE THE CLASS NAME AS USUAL!!

    FPUtil::<function_name>(<*inputs>);

    when accessing a predefined method or member variable.

    FPutility.<function_name OR member_variable>.<()>;

    READ ME READ ME READ ME!!
    WARNING WARNING WARNING
*/

void FPUtil::convert(const fs::path& inputPath, const std::unordered_set<std::uint16_t>& bitrate, const std::unordered_set<std::string_view>& codec) {
    // File checking.
    
    if (FPutility.ValidateAudioFile(inputPath)) {
        rc::info("Input file validated: " + inputPath.string());
    } else {
        rc::error("Input file validation failed: " + inputPath.string());
        return;
    }

    // Preset command
    // Output dir $HOME/Documents/KeroTheCPPBot/MusicCache
    fs::path outputDir = fs::path(getenv("HOME")) / "Documents" / "KeroTheCPPBot" / "MusicCache";
    if (!fs::exists(outputDir)) {
        try {
            fs::create_directories(outputDir);
            rc::info("a directory was made under ./KeroTheCPPBot/MusicCache for audio conversions.");
        }
        catch (const std::exception& e) {
            rc::error("Failed to create directory: " + std::string(e.what()));
            rc::info("The bot has also shut down due to the error.");
            throw _GLIBCXX_SYSTEM_ERROR;
        }
    } else {
        rc::info("Out dir found and exists: " + outputDir.string());
    }

    // Determining correct library based off codec
    // libopus for .opus
    // libmp3lame for .mp3

    std::string_view lib;
    std::string_view ext = inputPath.extension().string();
    if (!ext.empty() && ext.front() == '.') {
        ext.remove_prefix(1);
    };
    if (ext == "opus") {
        lib = "libopus";
    } else if (ext == "mp3") {
        lib = "libmp3lame";
    } else {
        lib = "unknown";
        rc::warn("Codec library for extension ." + std::string(ext) + " is not preset. You may need to modify the command manually.");
    }



    // Command
    std::string_view cmd = "ffmpeg -i \"" + inputPath.string() + "c:a" + std::string(lib) + " -b:a " + std::to_string(*bitrate.begin()) + "k \"" + (outputDir / inputPath.filename()).string() + "\" -y";

    rc::info("Executing command: " + std::string(cmd));
    FILE* pipe = popen(std::string(cmd).c_str(), "r");
    if (!pipe) {
        rc::error("Failed to open pipe for ffmpeg command.");
        rc::error("Command was: " + std::string(cmd));
        rc::error("Aborting conversion. Check if you have ffmpeg installed and in your PATH + libraries.");
        return;
    } else {
        rc::success("Pipe opened successfully for ffmpeg command.");
        char buffer[64];
        printf("ffmpeg output:\n");
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            printf("%s", buffer);
        }
        pclose(pipe);
    }

    



    return;

}
