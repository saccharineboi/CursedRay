// Copyright (C) 2022 saccharineboi

#pragma once

#include "Ray.hpp"
#include "Hit.hpp"
#include "Random.hpp"

#include <glm/vec3.hpp>
#include <glm/gtc/random.hpp>
#include <glm/ext/vector_relational.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    struct Material
    {
        ////////////////////////////////////////
        glm::vec3 Scatter(const Ray& intersectedRay,
                          const Hit& hit,
                          Ray& scatteredRay) const;

        ////////////////////////////////////////
        glm::vec3 mAlbedo           = glm::vec3(1.0f);
        float mRoughness            = 1.0f;
        float mRefractionIndex      = 0.0f;
        bool mIsDielectric          = false;
    };
}
