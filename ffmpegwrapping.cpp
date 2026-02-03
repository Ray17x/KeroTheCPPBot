#include "Utilities/ffmpegwrapping.hpp"
#include "Utilities/console.hpp"
#include <filesystem>
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

    // Conversion logic to be implemented here
    // im lazy ok? ok... :C
    rc::warn("Conversion function not yet implemented.");
    return;
}