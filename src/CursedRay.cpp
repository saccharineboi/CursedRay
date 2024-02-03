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
#include "HWDevice.hpp"
#include "Framebuffer.hpp"
#include "Log.hpp"

#include <glm/common.hpp>

#include <random>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>

////////////////////////////////////////
int main(int argc, char** argv)
{
    CursedRay::NCDeviceOptions ncDeviceOptions(argc, argv);
    CursedRay::NCDevice ncDevice(ncDeviceOptions);

    CursedRay::FramebufferOptions framebufferOptions(ncDevice.GetRenderWidth(),
                                                     ncDevice.GetRenderHeight(),
                                                     ncDeviceOptions.ClearColor());
    CursedRay::Framebuffer framebuffer(framebufferOptions);

    CursedRay::HWDevice hwDevice(framebuffer);
    auto events{ hwDevice.EnqueueClearColor(glm::vec4(0.5f, 0.0f, 0.5f, 1.0f)) };
    hwDevice.Finish();

    hwDevice.LogProfile(events);

    ncDevice.Blit(framebuffer);
    ncDevice.Block();
}
