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

        std::uint32_t mWidth, mHeight;
        std::uint32_t mPixelsWidth, mPixelsHeight;
        std::uint32_t mCellWidth, mCellHeight;

    public:
        NCDevice();

        NCDevice(const NCDevice&) = delete;
        NCDevice& operator=(const NCDevice&) = delete;
        NCDevice(NCDevice&&) = delete;
        NCDevice& operator=(NCDevice&&) = delete;

        ~NCDevice() { notcurses_stop(mContext); }

        void Blit(const std::vector<float>& pixels) const;

        std::uint32_t GetWidth() const { return mWidth; }
        std::uint32_t GetHeight() const { return mHeight; }

        std::uint32_t GetPixelsWidth() const { return mPixelsWidth; }
        std::uint32_t GetPixelsHeight() const { return mPixelsHeight; }

        std::uint32_t GetCellWidth() const { return mCellWidth; }
        std::uint32_t GetCellHeight() const { return mCellHeight; }
    };
}
