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

#include "Sphere.hpp"
#include "Camera.hpp"
#include "Framebuffer.hpp"
#include "NCDevice.hpp"
#include "Ray.hpp"

#include <vector>
#include <initializer_list>

namespace CursedRay
{
    ////////////////////////////////////////
    struct Scene
    {
        ////////////////////////////////////////
        void AddSphere(const Sphere& sphere)
        {
            mSpheres.push_back(sphere);
        }

        ////////////////////////////////////////
        void AddSpheres(const std::initializer_list<Sphere>& spheres)
        {
            for (const Sphere& sphere : spheres)
            {
                mSpheres.push_back(sphere);
            }
        }

        ////////////////////////////////////////
        glm::vec3 IntersectSpheres(const Ray& ray,
                                   const glm::vec3& clearColor,
                                   float tMin,
                                   float tMax,
                                   int depth) const;

        ////////////////////////////////////////
        void Render(const Camera& camera,
                    Framebuffer& framebuffer,
                    int numSamples,
                    const NCDevice& device,
                    const glm::vec3& clearColor,
                    int depth,
                    float tMin,
                    float tMax) const;

        ////////////////////////////////////////
        std::vector<Sphere> mSpheres;
    };
}
