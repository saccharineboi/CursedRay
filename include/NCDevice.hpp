// CursedRay: GPU-accelerated path tracer
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

#include <notcurses/notcurses.h>
#include <string>
#include <vector>
#include <cstdint>

namespace CursedRay
{
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

    public:
        NCDevice();

        NCDevice(const NCDevice&) = delete;
        NCDevice& operator=(const NCDevice&) = delete;
        NCDevice(NCDevice&&) = delete;
        NCDevice& operator=(NCDevice&&) = delete;

        ~NCDevice();

        void Blit(const std::vector<std::uint8_t>& pixels, std::int32_t width, std::int32_t height) const;
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
    };
}
