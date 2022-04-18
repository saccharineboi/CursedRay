// Copyright (C) 2022 saccharineboi

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
