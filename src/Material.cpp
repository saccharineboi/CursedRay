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
