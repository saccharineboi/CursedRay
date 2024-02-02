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

#include "HWDevice.hpp"
#include "IO.hpp"
#include "Log.hpp"

namespace CursedRay
{
    ////////////////////////////////////////
    static void BuildProgram(const std::vector<cl::Device>& devices, cl::Program& program)
    {
        try {
            program.build();
        }
        catch (const cl::Error& err) {
            if (err.err() == CL_BUILD_PROGRAM_FAILURE) {
                for (const cl::Device& device : devices) {
                    cl_build_status status{ program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device) };
                    if (status == CL_BUILD_ERROR) {
                        std::string deviceName{ device.getInfo<CL_DEVICE_NAME>() };
                        std::string buildLog{ program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) };
                        std::string message{ deviceName + ':' + buildLog };
                        Log(message.c_str());
                    }
                }
            }
        }
    }

    ////////////////////////////////////////
    HWDevice::HWDevice()
    {
        mCtx = cl::Context(CL_DEVICE_TYPE_DEFAULT);
        mCmdQueue = cl::CommandQueue(mCtx, CL_QUEUE_PROFILING_ENABLE);
        mDevices.push_back(cl::Device::getDefault());

        mClearColorProgram = cl::Program(mCtx, ReadTextFile("../kernels/clear_color.cl"));
        BuildProgram(mDevices, mClearColorProgram);
    }
}
