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
#include "Framebuffer.hpp"

#include <glm/common.hpp>

#include <random>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>

////////////////////////////////////////
// static std::vector<std::uint8_t> GenerateTestPixels(std::uint32_t width, std::uint32_t height)
// {
//     std::vector<std::uint8_t> pixels;
//     pixels.reserve(width * height * 4);
// 
//     std::random_device rd;
//     std::uniform_int_distribution<std::uint8_t> dist(0, 255);
// 
//     for (std::uint32_t row{}; row < height; ++row) {
//         for (std::uint32_t col{}; col < width; ++col) {
//             for (std::uint32_t pix{}; pix < 4; ++pix) {
//                 if (pix == 3) {
//                     pixels.push_back(255);
//                 }
//                 else if (pix == 0) {
//                     pixels.push_back(static_cast<std::uint8_t>(255.0f * (static_cast<float>(row) / static_cast<float>(height))));
//                 }
//                 else if (pix == 1) {
//                     pixels.push_back(static_cast<std::uint8_t>(255.0f * (static_cast<float>(height - row) / static_cast<float>(height))));
//                 }
//                 else {
//                     pixels.push_back(255);
//                 }
//             }
//         }
//     }
//     return pixels;
// }

////////////////////////////////////////
int main(int argc, char** argv)
{
    CursedRay::NCDeviceOptions deviceOptions(argc, argv);
    CursedRay::NCDevice device(deviceOptions);

    CursedRay::FramebufferOptions framebufferOptions(device.GetRenderWidth(),
                                                            device.GetRenderHeight(),
                                                            device.GetClearColor());

    CursedRay::Framebuffer framebuffer(framebufferOptions);

    // std::vector<std::uint8_t> testPixels{ GenerateTestPixels(device.GetRenderWidth(), device.GetRenderHeight()) };
    // device.Log("CursedRay: generated %lu bytes of pixel data", testPixels.size());

    device.Blit(framebuffer);
    device.Block();
}
