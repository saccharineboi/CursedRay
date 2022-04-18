// Copyright (C) 2022 saccharineboi

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
