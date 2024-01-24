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

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <random>

namespace CursedRay
{
    ////////////////////////////////////////
    inline float RandomRange(float min, float max)
    {
        static std::mt19937 mersenneTwister{ std::random_device{}() };
        std::uniform_real_distribution dist{ min, max };
        return dist(mersenneTwister);
    }
}
