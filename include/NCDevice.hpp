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

#include "Framebuffer.hpp"

#include <notcurses/notcurses.h>
#include <string>

namespace CursedRay
{
    ////////////////////////////////////////
    struct NCDevice
    {
        ////////////////////////////////////////
        NCDevice();

        ////////////////////////////////////////
        ~NCDevice() { notcurses_stop(mCtx); }

        ////////////////////////////////////////
        NCDevice(const NCDevice&)               = delete;
        NCDevice& operator=(const NCDevice&)    = delete;
        NCDevice(NCDevice&&)                    = delete;
        NCDevice& operator=(NCDevice&&)         = delete;

        ////////////////////////////////////////
        ncblitter_e ChooseBlitter();
        void SetOptions(ncblitter_e blitter);
        void Blit(const Framebuffer& framebuffer) const;
        void WaitForKeyPress() const;

        ////////////////////////////////////////
        void ProgressCallback(float percentage) const;

        ////////////////////////////////////////
        int mRealWidth, mRealHeight;
        int mEffectiveWidth, mEffectiveHeight;

        bool mIsInitialized    = false;
        std::string mErrorMessage;

        struct notcurses* mCtx = nullptr;
        struct ncplane* mPlane = nullptr;
        struct ncvisual_options mOptions{};
    };
}
