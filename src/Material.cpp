// Copyright (C) 2022 saccharineboi

#include "Material.hpp"

namespace CursedRay
{
    ////////////////////////////////////////
    static float SchlickReflectance(float cosine, float refractionRatio)
    {
        float r0 = (1.0f - refractionRatio) / (1.0f + refractionRatio);
        r0 *= r0;
        return r0 * (1.0f - r0) * glm::pow(1.0f - cosine, 5.0f);
    }

    ////////////////////////////////////////
    glm::vec3 Material::Scatter(const Ray& intersectedRay,
                                const Hit& hit,
                                Ray& scatteredRay) const
    {
        glm::vec3 rayDirection = glm::normalize(intersectedRay.mDirection);

        if (mIsDielectric)
        {
            float cos_theta = glm::min(glm::dot(-rayDirection, hit.mNormal), 1.0f);
            float sin_theta = glm::sqrt(1.0f - cos_theta * cos_theta);

            float refractionRatio = hit.mSurface == SurfaceType::Front
                                                 ? (1.0f / mRefractionIndex)
                                                 : mRefractionIndex;
            if (refractionRatio * sin_theta > 1.0f ||
                SchlickReflectance(cos_theta, refractionRatio) > RandomRange(0.0f, 1.0f))
            {
                glm::vec3 scatterDirection = glm::reflect(rayDirection, hit.mNormal);
                scatteredRay = Ray(hit.mPoint, scatterDirection +
                                               mRoughness * glm::sphericalRand(1.0f));
            }
            else
            {
                glm::vec3 scatterDirection = glm::refract(rayDirection,
                                                          hit.mNormal,
                                                          refractionRatio);
                if (glm::all(glm::equal(scatterDirection, glm::vec3(0.0f))))
                {
                    scatterDirection = hit.mNormal;
                }
                scatteredRay = Ray(hit.mPoint, scatterDirection +
                                               mRoughness * glm::sphericalRand(1.0f));
            }
        }
        else
        {
            glm::vec3 scatterDirection = glm::reflect(rayDirection, hit.mNormal);
            if (glm::all(glm::equal(scatterDirection, glm::vec3(0.0f))))
            {
                scatterDirection = hit.mNormal;
            }
            scatterDirection = glm::normalize(scatterDirection +
                                              mRoughness * glm::sphericalRand(1.0f));
            scatteredRay = Ray(hit.mPoint, scatterDirection);
            if (glm::dot(scatteredRay.mDirection, hit.mNormal) <= 0.0f)
            {
                return glm::vec3(0.0f);
            }
        }
        return mAlbedo;
    }
}
