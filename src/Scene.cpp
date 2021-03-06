// Copyright (C) 2022 saccharineboi

#include "Scene.hpp"
#include "Random.hpp"

#include <glm/gtc/random.hpp>

#include <cstdint>
#include <cassert>

namespace CursedRay
{
    ////////////////////////////////////////
    void Scene::Render(const Camera& camera,
                       Framebuffer& framebuffer,
                       int numSamples,
                       const NCDevice& device,
                       const glm::vec3& clearColor,
                       int depth,
                       float tMin,
                       float tMax) const
    {
        int viewportWidth   = static_cast<int>(device.mEffectiveWidth);
        int viewportHeight  = static_cast<int>(device.mEffectiveHeight);

        for (int row = 0; row < viewportHeight; ++row)
        {
            for (int col = 0; col < viewportWidth; ++col)
            {
                glm::vec3 color(0.0f);
                for (int sample = 0; sample < numSamples; ++sample)
                {
                    float u = ((float)col + RandomRange(0.0f, 1.0f)) /
                               (float)(viewportWidth - 1);
                    float v = ((float)row + RandomRange(0.0f, 1.0f)) /
                               (float)(viewportHeight - 1);

                    Ray ray = camera.GetRay(u, v);
                    color += IntersectSpheres(ray, clearColor, tMin, tMax, depth);
                }
                float scale = 1.0f / (float)numSamples;
                color = glm::sqrt(scale * color); // gamma correction
                framebuffer.SetPixel(row, col, color);
            }
            float percentage = (float)(row * viewportWidth) /
                               (float)(viewportWidth * viewportHeight) * 100.0f;
            device.ProgressCallback(percentage);
        }
    }

    ////////////////////////////////////////
    glm::vec3 Scene::IntersectSpheres(const Ray& ray,
                                      const glm::vec3& clearColor,
                                      float tMin,
                                      float tMax,
                                      int depth) const
    {
        if (depth < 0)
        {
            return clearColor;
        }

        bool hitAnything = false;
        glm::vec3 scatterColor;
        Ray scatteredRay;
        float closestDistance;
        for (const Sphere& sphere : mSpheres)
        {
            Hit hit;
            if (sphere.Intersect(ray, tMin, tMax, hit))
            {
                float currentDistance = glm::distance(hit.mPoint, ray.mOrigin);
                if (!hitAnything)
                {
                    hitAnything = true;
                    closestDistance = currentDistance;
                    const Material& material = sphere.mMaterial;
                    scatterColor = material.Scatter(ray, hit, scatteredRay);
                }
                else if (currentDistance < closestDistance)
                {
                    closestDistance = currentDistance;
                    const Material& material = sphere.mMaterial;
                    scatterColor = material.Scatter(ray, hit, scatteredRay);
                }
            }
        }
        if (hitAnything)
        {
            return scatterColor * IntersectSpheres(scatteredRay,
                                                   clearColor,
                                                   tMin, tMax,
                                                   depth - 1);
        }
        return clearColor;
    }
}
