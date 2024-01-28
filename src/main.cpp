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

////////////////////////////////////////
int main()
{
    CursedRay::NCDevice device;

    std::vector<float> pixels(device.GetPixelsWidth() * device.GetPixelsHeight());

    std::random_device rd;
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    std::ranges::for_each(pixels, [&](float& x){ x = dist(rd); });

    device.Blit(pixels);
}
