// Copyright (C) 2022 saccharineboi

#pragma once

#include <glm/vec3.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    struct Ray
    {
        ////////////////////////////////////////
        Ray() {}

        ////////////////////////////////////////
        Ray(const glm::vec3& origin, const glm::vec3& direction)
            : mOrigin{origin}, mDirection{direction} {}

        ////////////////////////////////////////
        glm::vec3 At(float t) const
        {
            return mOrigin + t * mDirection;
        }

        ////////////////////////////////////////
        glm::vec3 mOrigin;
        glm::vec3 mDirection;
    };
}
