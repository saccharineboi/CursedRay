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

#include <glm/vec3.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    struct Camera
    {
    private:
        glm::vec3 mPosition;
        float mFocalLength;

    public:
        Camera(const glm::vec3& position, float focalLength)
            : mPosition{position}, mFocalLength{focalLength} {}

        glm::vec3 GetPosition() const { return mPosition; }
        float GetFocalLength() const { return mFocalLength; }
    };
}
