// Copyright (C) 2022 saccharineboi

#pragma once

#include "Ray.hpp"

#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/random.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    struct CameraInfo
    {
        glm::vec3 mPosition;
        glm::vec3 mUp;
        glm::vec3 mTarget;
        float mAspectRatio;
        float mFovy;
        float mAspectMultiplier;
        float mAperture;
        float mFocusDistance;
    };

    ////////////////////////////////////////
    struct Camera
    {
        ////////////////////////////////////////
        explicit Camera(const CameraInfo& info);

        ////////////////////////////////////////
        Ray GetRay(float u, float v) const
        {
            glm::vec3 randomPoint = mLensRadius * glm::sphericalRand(1.0f);
            glm::vec3 offset = mU * randomPoint.x + mV * randomPoint.y;

            return Ray(mPosition + offset, mLowerLeftCorner     +
                                           u * mHorizontalDelta +
                                           v * mVerticalDelta   -
                                           mPosition            - offset);
        }

        ////////////////////////////////////////
        void ComputeViewportDims();
        void ComputeLowerLeftCorner();

        ////////////////////////////////////////
        float mAspectRatio;
        float mFovy;
        float mAspectMultiplier;
        float mViewportWidth;
        float mViewportHeight;
        float mLensRadius;
        float mFocusDistance;
        float mAperture;

        glm::vec3 mPosition;
        glm::vec3 mTarget;
        glm::vec3 mUp;
        glm::vec3 mDirection;

        glm::vec3 mHorizontalDelta;
        glm::vec3 mVerticalDelta;
        glm::vec3 mLowerLeftCorner;

        glm::vec3 mU, mV, mW;
    };
}
