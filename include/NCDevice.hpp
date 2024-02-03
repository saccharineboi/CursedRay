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

#pragma once

#include "Constants.hpp"
#include "HWDeviceOptions.hpp"

#include <glm/vec4.hpp>

#include <cstdlib>
#include <notcurses/notcurses.h>
#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <cstring>
#include <fstream>

namespace CursedRay
{
    ////////////////////////////////////////
    struct Framebuffer;

    ////////////////////////////////////////
    struct NCDeviceOptions
    {
    private:
        /* notcurses options */
        bool mNoAlternateScreen{ DEFAULT_NO_ALTERNATE_SCREEN };
        bool mSuppressBanners{ DEFAULT_SUPPRESS_BANNERS };
        ncblitter_e mBlitter{ DEFAULT_BLITTER };
        ncloglevel_e mLogLevel{ DEFAULT_LOGLEVEL };

        /* logging */
        std::string mLogFileName{ DEFAULT_LOGFILE_NAME };
        bool mDumpLogs{ DEFAULT_DUMP_LOGS };

        /* framebuffer options */
        glm::vec4 mClearColor{ DEFAULT_CLEAR_COLOR };

        /* hardware device options */
        HWDeviceOptions mHWOptions;

        const char* GetBlitterName() const;
        const char* GetLogLevelName() const;
        const char* GetClearColorValues() const;
        const char* GetDeviceTypeName() const;

        [[noreturn]] void PrintHelp(char** argv) const;

    public:
        NCDeviceOptions(int argc, char** argv);

        bool NoAlternateScreen() const { return mNoAlternateScreen; }
        bool SuppressBanners() const { return mSuppressBanners; }
        ncblitter_e Blitter() const { return mBlitter; }

        ncloglevel_e LogLevel() const { return mLogLevel; }
        bool DumpLogs() const { return mDumpLogs; }

        glm::vec4 ClearColor() const { return mClearColor; }
        HWDeviceOptions GetHWDeviceOptions() const { return mHWOptions; }
    };

    ////////////////////////////////////////
    struct NCDevice
    {
    private:
        notcurses* mContext;
        ncplane* mPlane;
        ncvisual_options mOptions;
        notcurses_options mContextOptions;

        std::uint32_t mWidth, mHeight;
        std::uint32_t mPixelsWidth, mPixelsHeight;
        std::uint32_t mCellWidth, mCellHeight;

        bool mDumpLogs;

    public:
        explicit NCDevice(const NCDeviceOptions& options);

        NCDevice(const NCDevice&) = delete;
        NCDevice& operator=(const NCDevice&) = delete;
        NCDevice(NCDevice&&) = delete;
        NCDevice& operator=(NCDevice&&) = delete;

        ~NCDevice();

        void Blit(const std::vector<std::uint8_t>& pixels, std::int32_t width, std::int32_t height);
        void Blit(const Framebuffer& framebuffer);
        void Block() const;

        std::uint32_t GetWidth() const { return mWidth; }
        std::uint32_t GetHeight() const { return mHeight; }

        std::int32_t GetWidthSigned() const { return static_cast<std::int32_t>(mWidth); }
        std::int32_t GetHeightSigned() const { return static_cast<std::int32_t>(mHeight); }

        std::uint32_t GetPixelsWidth() const { return mPixelsWidth; }
        std::uint32_t GetPixelsHeight() const { return mPixelsHeight; }

        std::int32_t GetPixelsWidthSigned() const { return static_cast<std::int32_t>(mPixelsWidth); }
        std::int32_t GetPixelsHeightSigned() const { return static_cast<std::int32_t>(mPixelsHeight); }

        std::uint32_t GetCellWidth() const { return mCellWidth; }
        std::uint32_t GetCellHeight() const { return mCellHeight; }

        std::int32_t GetCellWidthSigned() const { return static_cast<std::int32_t>(mCellWidth); }
        std::int32_t GetCellHeightSigned() const { return static_cast<std::int32_t>(mCellHeight); }

        std::uint32_t GetRenderWidth() const { return mOptions.lenx; }
        std::uint32_t GetRenderHeight() const { return mOptions.leny; }

        std::int32_t GetRenderWidthSigned() const { return static_cast<std::int32_t>(mOptions.lenx); }
        std::int32_t GetRenderHeightSigned() const { return static_cast<std::int32_t>(mOptions.leny); }

        float GetRenderOutputRatio() const { return static_cast<float>(mOptions.lenx) / static_cast<float>(mOptions.leny); }
    };
}
