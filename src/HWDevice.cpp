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
#include "HWDeviceOptions.hpp"
#include "IO.hpp"
#include "Log.hpp"
#include "Constants.hpp"
#include "Framebuffer.hpp"

#include <glm/gtc/type_ptr.hpp>

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
                        std::string message{ "CursedRay: " };
                        message.append(deviceName);
                        message.append(":");
                        message.append(buildLog);
                        Log(message.c_str());
                    }
                }
            }
        }
    }

    ////////////////////////////////////////
    HWDevice::HWDevice(Framebuffer& framebuffer, const HWDeviceOptions& options)
        : mFramebuffer{ framebuffer }
    {
        try {
            mCtx = cl::Context(options.mDeviceType);
            mCmdQueue = cl::CommandQueue(mCtx, CL_QUEUE_PROFILING_ENABLE);
            mDevices.push_back(cl::Device::getDefault());

            mClearColorProgram = cl::Program(mCtx, ReadTextFile(KERNEL_CLEAR_COLOR_PATH));
            BuildProgram(mDevices, mClearColorProgram);

            mHWFramebuffer = cl::Buffer(mCtx, CL_MEM_WRITE_ONLY, mFramebuffer.GetWidth() *
                                                                                       mFramebuffer.GetHeight() *
                                                                                       mFramebuffer.GetNumChannels());
            cl::copy(mCmdQueue, framebuffer.cbegin(), framebuffer.cend(), mHWFramebuffer);
        }
        catch (const cl::Error& err) {
            Log("CursedRay: OpenCL Error: %s", err.what());
        }
    }

    ////////////////////////////////////////
    std::vector<cl::Event> HWDevice::EnqueueClearColor(const glm::vec4& clearColor,
                                                       const std::vector<cl::Event>& events)
    {
        try {
            cl::Kernel kernel(mClearColorProgram, KERNEL_CLEAR_COLOR_NAME);
            kernel.setArg(0, mHWFramebuffer);
            kernel.setArg(1, mFramebuffer.GetWidth());
            kernel.setArg(2, mFramebuffer.GetHeight());
            kernel.setArg(3, clearColor.r);
            kernel.setArg(4, clearColor.g);
            kernel.setArg(5, clearColor.b);
            kernel.setArg(6, clearColor.a);

            cl::Event event;
            mCmdQueue.enqueueNDRangeKernel(kernel,
                                           cl::NullRange,
                                           cl::NDRange(mFramebuffer.GetWidth(), mFramebuffer.GetHeight()),
                                           cl::NullRange,
                                           &events,
                                           &event);
            return { event };
        }
        catch (const cl::Error& err) {
            Log("CursedRay: OpenCL Error: %s", err.what());
        }
        return {};
    }

    ////////////////////////////////////////
    double HWDevice::Profile(const cl::Event& event) const
    {
        ulong hwBegin{ event.getProfilingInfo<CL_PROFILING_COMMAND_START>() };
        ulong hwEnd{ event.getProfilingInfo<CL_PROFILING_COMMAND_END>() };
        return static_cast<double>(hwEnd - hwBegin);
    }

    ////////////////////////////////////////
    void HWDevice::LogProfile(const cl::Event& event) const
    {
        ulong hwBegin{ event.getProfilingInfo<CL_PROFILING_COMMAND_START>() };
        ulong hwEnd{ event.getProfilingInfo<CL_PROFILING_COMMAND_END>() };
        double timePassed{ static_cast<double>(hwEnd - hwBegin) };
        Log("CursedRay: kernel runtime was %f milliseconds", timePassed * 1e-6);
    }

    ////////////////////////////////////////
    void HWDevice::LogProfile(const std::vector<cl::Event>& events) const
    {
        for (const cl::Event& event : events) {
            ulong hwBegin{ event.getProfilingInfo<CL_PROFILING_COMMAND_START>() };
            ulong hwEnd{ event.getProfilingInfo<CL_PROFILING_COMMAND_END>() };
            double timePassed{ static_cast<double>(hwEnd - hwBegin) };
            Log("CursedRay: kernel runtime was %f milliseconds", timePassed * 1e-6);
        }
    }

    ////////////////////////////////////////
    void HWDevice::Finish()
    {
        try {
            mCmdQueue.finish();
            cl::copy(mCmdQueue, mHWFramebuffer, mFramebuffer.begin(), mFramebuffer.end());
        }
        catch (const cl::Error& err) {
            Log("CursedRay: OpenCL Error: %s", err.what());
        }
    }
}
