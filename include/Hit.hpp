// Copyright (C) 2022 saccharineboi

#pragma once

#include <glm/vec3.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    enum class SurfaceType { Front, Back };

    ////////////////////////////////////////
    struct Hit
    {
        glm::vec3 mPoint;
        glm::vec3 mNormal;
        float mT;
        SurfaceType mSurface;
    };
}
