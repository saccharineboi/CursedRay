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

#include "Sphere.hpp"

#include <glm/geometric.hpp>
#include <glm/common.hpp>
#include <glm/gtx/norm.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    bool Sphere::Intersect(const Ray& ray, float tMin, float tMax, Hit& hit) const
    {
        glm::vec3 dir   = ray.mOrigin - mPosition;
        float a         = glm::length2(ray.mDirection);
        float half_b    = glm::dot(dir, ray.mDirection);
        float c         = glm::length2(dir) - mRadius * mRadius;

        float discriminant = half_b * half_b - a * c;
        if (discriminant < 0.0f)
        {
            return false;
        }

        float sqrt_disc = glm::sqrt(discriminant);

        // Compute the nearest root in a given range ( tMin < t < tMax )
        float root = (-half_b - sqrt_disc) / a;
        if (root < tMin || root > tMax)
        {
            // Check the other root
            root = (-half_b + sqrt_disc) / a;
            if (root < tMin || root > tMax)
            {
                return false;
            }
        }

        hit.mPoint = ray.At(root);
        hit.mNormal = glm::normalize(hit.mPoint - mPosition);
        hit.mT = root;

        if (glm::dot(ray.mDirection, hit.mNormal) > 0.0f)
        {
            hit.mNormal = -hit.mNormal;
            hit.mSurface = SurfaceType::Back;
        }
        else
        {
            hit.mSurface = SurfaceType::Front;
        }

        return true;
    }
}
