#ifndef ffmpegwrapping_hpp
#define ffmpegwrapping_hpp

#include <cstdio>
#include <filesystem>
#include <unordered_set>
#include <string>
#include <string_view>
#include <stdexcept>
#include <cctype>
#include <algorithm>
namespace fs = std::filesystem;

// const enum class MP3LAMEbitrate {
//         // All qualities for MP3 LAME codec VBR -c:a libmp3lame -q <quality>
//         BITRATE_32KBPS   = 45, // -V 9
//         BITRATE_64KBPS   = 64, // -V 9
//         BITRATE_96KBPS   = 96, // -V 8
//         BITRATE_128KBPS  = 128, // -V 5
//         BITRATE_192KBPS  = 192, // -V 1
//         BITRATE_256KBPS  = 256, // -V 0
//         BITRATE_320KBPS  = 320 // CBR 
// };

// const enum class OPUSBitrates {
//     // All common qualities for OPUS codec VBR -c:a libopus -b:a <bitrate>k
//     BITRATE_48KBPS   = 48, // -b:a 48k
//     BITRATE_64KBPS   = 64, // -b:a 64k
//     BITRATE_96KBPS   = 96, // -b:a 96k
//     BITRATE_128KBPS  = 128, // -b:a 128k
//     BITRATE_192KBPS  = 192, // -b:a 192k
//     BITRATE_256KBPS  = 256, // -b:a 256k
//     BITRATE_320KBPS  = 320, // -b:a 320k
//     BITRATE_510KBPS  = 510 // -b:a 510k
// };

// ignore above im a moron :C
namespace FFmpegWrap {
    class FPUtil {
        public:

        static const std::unordered_set<std::uint16_t> bitrate_set;

        static const std::unordered_set<std::string_view> codec_set;

        static void convert(const fs::path& inputPath, const std::unordered_set<std::uint16_t>& bitrate, const std::unordered_set<std::string_view>& codec);

        inline void ValidateAudioFile(const fs::path& filePath) {
            if (!fs::exists(filePath)) {
                throw std::invalid_argument("File does not exist: " + filePath.string());
            }
            if (!fs::is_regular_file(filePath)) {
                throw std::invalid_argument("Path is not a regular file: " + filePath.string());
            }

            std::string ext = filePath.extension().string(); // includes leading '.'
            if (!ext.empty() && ext.front() == '.') {
                ext.erase(0, 1);
            }
            if (ext.empty()) {
                throw std::invalid_argument("File has no extension: " + filePath.string());
            }

            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

            if (codec_set.find(ext) == codec_set.end()) {
                throw std::invalid_argument("Unsupported audio extension: " + ext);
            }
        }
    };

    const std::unordered_set<std::uint16_t> FPUtil::bitrate_set = {
        // common bit rates in kbps, commands will need 'k' suffix when used in ffmpeg commands
        // also includes 510 for opus max bitrate
        // command example: ffmpeg -i input.[perferabbly flac/wav] -c:a [lib] -b:a [bitrate]k output.[extension]
        // output should be held in ./MusicCache then sent to discord THEN deleted immeidately after to not waste space on
        // server disk
        // mp3 uses libmp3lame 
        // opus uses libopus
        // other ones figure it out yourself fucking losers
        32,
        48,
        64,
        96,
        128,
        192,
        256,
        320,
        510
    };

    const std::unordered_set<std::string_view> FPUtil::codec_set = {
        "mp3",
        "ogg",
        "m4a",
        "wav",
        "flac",
        "aac",
        "wma",
        "opus",
        "aiff",
        "au",
        "ra",
        "3ga",
        "amr",
        "awb",
        "dss",
        "dvf",
        "m4b",
        "m4p",
        "mmf",
        "mpc",
        "msv",
        "nmf",
        "oga",
        "raw",
        "rf64",
        "sln",
        "tta",
        "voc",
        "vox",
        "wv",
        "webm",
        "8svx",
        "cda",
    };
}


#endif // ffmpegwrapping_hpp #ifndef end