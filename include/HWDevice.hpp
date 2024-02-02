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

#include "Framebuffer.hpp"

#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/opencl.hpp>

#include <vector>

namespace CursedRay
{
    ////////////////////////////////////////
    struct HWDevice
    {
    private:
        cl::Context mCtx;
        cl::CommandQueue mCmdQueue;
        std::vector<cl::Device> mDevices;

        cl::Program mClearColorProgram;
        cl::Kernel mClearColorKernel;

        cl::Buffer mHWFramebuffer;

    public:
        explicit HWDevice(const Framebuffer& framebuffer);

        HWDevice(const HWDevice&) = delete;
        HWDevice& operator=(const HWDevice&) = delete;

        HWDevice(HWDevice&&) = delete;
        HWDevice& operator=(HWDevice&&) = delete;
    };
};
