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

#include "NCDevice.hpp"
#include <glm/common.hpp>

#include <random>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>

////////////////////////////////////////
int main(int argc, char** argv)
{
    CursedRay::NCDeviceOptions options(argc, argv);
    CursedRay::NCDevice device(options);

    std::vector<std::uint8_t> pixels;
    pixels.reserve(device.GetRenderWidth() * device.GetRenderHeight() * 4);

    std::random_device rd;
    std::uniform_int_distribution<std::uint8_t> dist(0, 255);

    for (std::uint32_t row{}; row < device.GetRenderHeight(); ++row) {
        for (std::uint32_t col{}; col < device.GetRenderWidth(); ++col) {
            for (std::uint32_t pix{}; pix < 4; ++pix) {
                if (pix == 3) {
                    pixels.push_back(255);
                }
                else if (pix == 0) {
                    pixels.push_back(static_cast<std::uint8_t>(255.0f * (static_cast<float>(row) / static_cast<float>(device.GetRenderHeight()))));
                }
                else if (pix == 1) {
                    pixels.push_back(static_cast<std::uint8_t>(255.0f * (static_cast<float>(device.GetRenderHeight() - row) / static_cast<float>(device.GetRenderHeight()))));
                }
                else {
                    pixels.push_back(255);
                }
            }
        }
    }

    device.Log("[DEBUG] initialized the buffer");

    device.Blit(pixels, device.GetRenderWidthSigned(), device.GetRenderHeightSigned());
    device.Block();
}
