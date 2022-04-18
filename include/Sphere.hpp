// Copyright (C) 2022 saccharineboi

#pragma once

#include "Hit.hpp"
#include "Ray.hpp"
#include "Material.hpp"

#include <glm/vec3.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    struct Sphere
    {
        ////////////////////////////////////////
        Sphere(const glm::vec3& position, float radius)
            : mPosition{position}, mRadius{radius} {}

        ////////////////////////////////////////
        bool Intersect(const Ray& ray, float tMin, float tMax, Hit& hit) const;

        ////////////////////////////////////////
        glm::vec3 mPosition;
        float mRadius;
        Material mMaterial;        
    };
}
