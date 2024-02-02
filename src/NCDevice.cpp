// CursedRay: Hardware-accelerated path tracer
// Copyright (C) 2024 Omar Huseynov
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "NCDevice.hpp"
#include "Constants.hpp"
#include "Framebuffer.hpp"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <ios>
#include <notcurses/nckeys.h>
#include <notcurses/notcurses.h>

namespace CursedRay
{
    ////////////////////////////////////////
    const char* NCDeviceOptions::GetBlitterName() const
    {
        switch (mBlitter) {
            case NCBLIT_1x1:
                return "1x1";
            case NCBLIT_2x1:
                return "2x1";
            case NCBLIT_2x2:
                return "2x2";
            case NCBLIT_3x2:
                return "3x2";
            case NCBLIT_PIXEL:
                return "pixel";
            case NCBLIT_4x1:
                return "4x1";
            case NCBLIT_8x1:
                return "8x1";
            case NCBLIT_BRAILLE:
                return "braille";
            case NCBLIT_DEFAULT:
                return "default";
        }
        return "unknown";
    }

    ////////////////////////////////////////
    const char* NCDeviceOptions::GetLogLevelName() const
    {
        switch (mLogLevel) {
            case NCLOGLEVEL_ERROR:
                return "error";
            case NCLOGLEVEL_SILENT:
                return "silent";
            case NCLOGLEVEL_DEBUG:
                return "debug";
            case NCLOGLEVEL_FATAL:
                return "fatal";
            case NCLOGLEVEL_INFO:
                return "info";
            case NCLOGLEVEL_PANIC:
                return "panic";
            case NCLOGLEVEL_TRACE:
                return "trace";
            case NCLOGLEVEL_VERBOSE:
                return "verbose";
            case NCLOGLEVEL_WARNING:
                return "warning";
        }
        return "unknown";
    }

    ////////////////////////////////////////
    const char* NCDeviceOptions::GetClearColorValues() const
    {
        static std::string colorInStr;

        std::string redValueStr{ std::to_string(mClearColor.r) };
        std::string greenValueStr{ std::to_string(mClearColor.g) };
        std::string blueValueStr{ std::to_string(mClearColor.b) };
        std::string alphaValueStr{ std::to_string(mClearColor.a) };

        colorInStr.clear();
        colorInStr.append("(");
        colorInStr.append(redValueStr);
        colorInStr.append(", ");
        colorInStr.append(greenValueStr);
        colorInStr.append(", ");
        colorInStr.append(blueValueStr);
        colorInStr.append(", ");
        colorInStr.append(alphaValueStr);
        colorInStr.append(")");
        return colorInStr.c_str();
    }

    ////////////////////////////////////////
    void NCDeviceOptions::PrintHelp(char** argv) const
    {
        std::printf("Usage: %s [OPTIONS...]\n\n", argv[0]);
        std::printf("\t--help:\t\t\t Print this help message\n");
        std::printf("\t--version:\t\t Print the version number\n");
        std::printf("\t--license:\t\t Print the license\n");
        std::printf("\t--clear-on-exit:\t Clear the terminal on exit\n\t\t\t\t Default is '%d'\n", !DEFAULT_NO_ALTERNATE_SCREEN);
        std::printf("\t--dont-suppress-banners: Don't suppress notcurses' banners\n\t\t\t\t Default is '%d'\n", DEFAULT_SUPPRESS_BANNERS);
        std::printf("\t--blitter:\t\t Blitter to use\n\t\t\t\t Valid values are '1x1', '2x1', '2x2', '3x2',\n\t\t\t\t and 'pixel'\n\t\t\t\t Default is '%s'\n", GetBlitterName());
        std::printf("\t--log-level:\t\t Log level to use\n\t\t\t\t Valid values are 'fatal', 'error', 'panic',\n\t\t\t\t 'debug', 'info', 'warning', 'silent',\n\t\t\t\t 'trace', and 'verbose'\n\t\t\t\t Default is '%s'\n", GetLogLevelName());
        std::printf("\t--log-file:\t\t Log file to write logs to\n\t\t\t\t Default is '%s'\n", DEFAULT_LOGFILE_NAME);
        std::printf("\t--clear-color:\t\t Set background color\n\t\t\t\t Default is '%s'\n", GetClearColorValues());
        std::exit(EXIT_SUCCESS);
    }

    ////////////////////////////////////////
    NCDeviceOptions::NCDeviceOptions(int argc, char** argv)
    {
        assert(nullptr != argv);
        for (int i{1}; i < argc; ++i) {
            assert(nullptr != argv[i]);
            if (!std::strncmp(argv[i], "--version", DEFAULT_ARG_STR_LEN)) {
                std::printf("Version: %d.%d.%d\n", CURSEDRAY_VERSION_MAJOR, CURSEDRAY_VERSION_MINOR, CURSEDRAY_VERSION_PATCH);
                std::exit(EXIT_SUCCESS);
            }
            else if (!std::strncmp(argv[i], "--license", DEFAULT_ARG_STR_LEN)) {
#define LICENSE_STR "Copyright (C) 2024 Omar Huseynov\n\n" \
                "This program is free software: you can redistribute it and/or modify\n" \
                "it under the terms of the GNU General Public License as published by\n" \
                "the Free Software Foundation, either version 3 of the License, or\n" \
                "(at your option) any later version.\n\n" \
                "This program is distributed in the hope that it will be useful,\n" \
                "but WITHOUT ANY WARRANTY; without even the implied warranty of\n" \
                "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n" \
                "GNU General Public License for more details.\n\n" \
                "You should have received a copy of the GNU General Public License\n" \
                "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n"
                std::printf("CursedRay: Hardware-accelerated path tracer\n" LICENSE_STR);
                std::exit(EXIT_SUCCESS);
            }
            else if (!std::strncmp(argv[i], "--help", DEFAULT_ARG_STR_LEN)) {
                PrintHelp(argv);
            }
            else if (!std::strncmp(argv[i], "--clear-on-exit", DEFAULT_ARG_STR_LEN)) {
                mNoAlternateScreen = false;
            }
            else if (!std::strncmp(argv[i], "--dont-suppress-banners", DEFAULT_ARG_STR_LEN)) {
                mSuppressBanners = false;
            }
            else if (!std::strncmp(argv[i], "--blitter", DEFAULT_ARG_STR_LEN)) {
                if (i == argc - 1) {
                    std::fprintf(stderr, "%s: --blitter requires 1 argument\n", argv[0]);
                    std::exit(EXIT_FAILURE);
                }
                if (!std::strncmp(argv[i + 1], "1x1", DEFAULT_ARG_STR_LEN)) {
                    mBlitter = NCBLIT_1x1;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "2x1", DEFAULT_ARG_STR_LEN)) {
                    mBlitter = NCBLIT_2x1;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "2x2", DEFAULT_ARG_STR_LEN)) {
                    mBlitter = NCBLIT_2x2;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "3x2", DEFAULT_ARG_STR_LEN)) {
                    mBlitter = NCBLIT_3x2;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "pixel", DEFAULT_ARG_STR_LEN)) {
                    mBlitter = NCBLIT_PIXEL;
                    ++i;
                }
                else {
                    std::fprintf(stderr, "%s: %s is an invalid blitter name\n", argv[0], argv[i + 1]);
                    std::exit(EXIT_FAILURE);
                }
            }
            else if (!std::strncmp(argv[i], "--log-level", DEFAULT_ARG_STR_LEN)) {
                if (i == argc - 1) {
                    std::fprintf(stderr, "%s: --log-level requires 1 argument\n", argv[0]);
                    std::exit(EXIT_FAILURE);
                }
                if (!std::strncmp(argv[i + 1], "fatal", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_FATAL;
                    ++i;
                }
                else if(!std::strncmp(argv[i + 1], "error", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_ERROR;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "panic", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_PANIC;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "debug", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_DEBUG;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "info", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_INFO;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "warning", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_WARNING;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "silent", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_SILENT;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "trace", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_TRACE;
                    ++i;
                }
                else if (!std::strncmp(argv[i + 1], "verbose", DEFAULT_ARG_STR_LEN)) {
                    mLogLevel = NCLOGLEVEL_VERBOSE;
                    ++i;
                }
                else {
                    std::fprintf(stderr, "%s: %s is an invalid log level\n", argv[0], argv[i + 1]);
                    std::exit(EXIT_FAILURE);
                }
            }
            else if (!std::strncmp("--log-file", argv[i], DEFAULT_ARG_STR_LEN)) {
                if (i == argc - 1) {
                    std::fprintf(stderr, "%s: --log-file requires 1 argument\n", argv[0]);
                    std::exit(EXIT_FAILURE);
                }
                mLogFileName = std::string{ argv[i + 1] };
                ++i;
            }
            else if (!std::strncmp("--clear-color", argv[i], DEFAULT_ARG_STR_LEN)) {
                if (i >= argc - 4) {
                    std::fprintf(stderr, "%s: --clear-color requires 4 arguments\n", argv[0]);
                    std::exit(EXIT_FAILURE);
                }
                float redChannel{ static_cast<float>(std::atof(argv[i + 1])) };
                float greenChannel{ static_cast<float>(std::atof(argv[i + 2])) };
                float blueChannel{ static_cast<float>(std::atof(argv[i + 3])) };
                float alphaChannel{ static_cast<float>(std::atof(argv[i + 4])) };

                mClearColor.r = std::clamp(redChannel, 0.0f, 1.0f);
                mClearColor.g = std::clamp(greenChannel, 0.0f, 1.0f);
                mClearColor.b = std::clamp(blueChannel, 0.0f, 1.0f);
                mClearColor.a = std::clamp(alphaChannel, 0.0f, 1.0f);
                i += 4;
            }
            else {
                std::fprintf(stderr, "%s: %s is an invalid option\n", argv[0], argv[i]);
                PrintHelp(argv);
                std::exit(EXIT_FAILURE);
            }
        }
    }

    ////////////////////////////////////////
    void NCDevice::Blit(const std::vector<std::uint8_t>& pixels, std::int32_t width, std::int32_t height)
    {
        if (ncblit_rgba(pixels.data(), width * 4, &mOptions) < 0) {
            Log("CursedRay: error in ncblit_rgba");
            notcurses_stop(mContext);
            std::exit(EXIT_FAILURE);
        }
        if (notcurses_render(mContext) == -1) {
            Log("CursedRay: error in notcurses_render");
            notcurses_stop(mContext);
            std::exit(EXIT_FAILURE);
        }
    }

    ////////////////////////////////////////
    void NCDevice::Blit(const Framebuffer& framebuffer)
    {
        if (ncblit_rgba(framebuffer.GetData(), framebuffer.GetWidthSigned() * 4, &mOptions) < 0) {
            Log("CursedRay: error in ncblit_rgba, framebuffer %p", &framebuffer);
            notcurses_stop(mContext);
            std::exit(EXIT_FAILURE);
        }
        if (notcurses_render(mContext) == -1) {
            Log("CursedRay: error in notcurses_render, framebuffer %p", &framebuffer);
            notcurses_stop(mContext);
            std::exit(EXIT_FAILURE);
        }
    }

    ////////////////////////////////////////
    void NCDevice::Log(const char* args, ...)
    {
        std::time_t timer;
        std::time(&timer);
        std::tm timeInfo{};

#ifdef __unix__
        localtime_r(&timer, &timeInfo);
#elif defined(_MSC_VER)
        localtime_s(&timeInfo, &timer);
#else
#error "CursedRay is not supported on this platform"
#endif

        std::va_list ap;
        va_start(ap, args);
        char processedOutput[250], finalOutput[500];
        std::vsnprintf(processedOutput, 250, args, ap);
        int charsWritten{ std::snprintf(finalOutput, 500, "[%02d:%02d:%02d %02d:%02d:%02d] %s\n", timeInfo.tm_mon, timeInfo.tm_mday, timeInfo.tm_year + 1900, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, processedOutput) };
        mLogFile.write(finalOutput, charsWritten);
        va_end(ap);
    }

    ////////////////////////////////////////
    void NCDevice::Block() const
    {
        ncinput input;
        while (notcurses_get_blocking(mContext, &input) != NCKEY_ESC && input.evtype != NCTYPE_PRESS)
            ;
    }

    ////////////////////////////////////////
    NCDevice::NCDevice(const NCDeviceOptions& options)
        : mContext{}, mPlane{}, mOptions{}, mContextOptions{},
          mWidth{}, mHeight{},
          mPixelsWidth{}, mPixelsHeight{},
          mCellWidth{}, mCellHeight{},
          mLogFile{options.LogFileName(), std::ios_base::out | std::ios_base::ate},
          mClearColor{ options.ClearColor() }
    {
        if (!setlocale(LC_ALL, "")) {
            std::fprintf(stderr, "CursedRay: coudn't set locale");
            std::exit(EXIT_FAILURE);
        }

        if (options.NoAlternateScreen()) {
            mContextOptions.flags |= NCOPTION_NO_ALTERNATE_SCREEN;
        }
        if (options.SuppressBanners()) {
            mContextOptions.flags |= NCOPTION_SUPPRESS_BANNERS;
        }
        mContextOptions.loglevel = options.LogLevel();

        mContext = notcurses_init(&mContextOptions, nullptr);
        if (!mContext) {
            std::fprintf(stderr, "CursedRay: couldn't initialize notcurses");
            std::exit(EXIT_FAILURE);
        }

        mPlane = notcurses_stdplane(mContext);
        ncplane_dim_yx(mPlane, &mHeight, &mWidth);
        Log("CursedRay: number of cells: %u:%u", mWidth, mHeight);

        ncplane_pixel_geom(mPlane, &mPixelsHeight, &mPixelsWidth, &mCellHeight, &mCellWidth, nullptr, nullptr);
        Log("CursedRay: dimensions of the terminal in pixels: %u:%u", mPixelsWidth, mPixelsHeight);
        Log("CursedRay: dimensions of each cell: %u:%u", mCellWidth, mCellHeight);

        ncblitter_e blitter{};
        if (options.Blitter() == NCBLIT_PIXEL && notcurses_canpixel(mContext)) {
            blitter = NCBLIT_PIXEL;
            mOptions.leny = mPixelsHeight;
            mOptions.lenx = mPixelsWidth;
            Log("CursedRay: can blit in pixels");
        }
        else if (options.Blitter() == NCBLIT_3x2 && notcurses_cansextant(mContext)) {
            blitter = NCBLIT_3x2;
            mOptions.leny = mHeight * 3;
            mOptions.lenx = mWidth * 2;
            Log("CursedRay: can blit in sextants");
        }
        else if (options.Blitter() == NCBLIT_2x2 && notcurses_canquadrant(mContext)) {
            blitter = NCBLIT_2x2;
            mOptions.leny = mHeight * 2;
            mOptions.lenx = mWidth * 2;
            Log("CursedRay: can blit in quadrants");
        }
        else if (options.Blitter() == NCBLIT_2x1 && notcurses_canhalfblock(mContext)) {
            blitter = NCBLIT_2x1;
            mOptions.leny = mHeight * 2;
            mOptions.lenx = mWidth;
            Log("CursedRay: can blit in halves");
        }
        else if (options.Blitter() == NCBLIT_1x1) {
            blitter = NCBLIT_1x1;
            mOptions.leny = mHeight;
            mOptions.lenx = mWidth;
            Log("CursedRay: can blit in cells");
        }

        Log("CursedRay: render output: %u:%u", mOptions.lenx, mOptions.leny);

        mOptions.n = mPlane;
        mOptions.scaling = NCSCALE_NONE;
        mOptions.blitter = blitter;
        mOptions.flags = NCVISUAL_OPTION_NOINTERPOLATE | NCVISUAL_OPTION_CHILDPLANE;

        ncplane_set_fg_rgb8(mPlane, 255, 255, 255);
        ncplane_set_bg_rgb8(mPlane, 0, 0, 0);
    }

    ////////////////////////////////////////
    NCDevice::~NCDevice()
    {
        notcurses_stop(mContext);
        mLogFile.close();
    }
}
