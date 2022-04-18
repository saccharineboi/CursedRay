// Copyright (C) 2022 saccharineboi

#include "Camera.hpp"

#include <glm/trigonometric.hpp>

namespace CursedRay
{
    ////////////////////////////////////////
    Camera::Camera(const CameraInfo& info)
        : mAspectRatio      {info.mAspectRatio},
          mFovy             {info.mFovy},
          mAspectMultiplier {info.mAspectMultiplier},
          mFocusDistance    {info.mFocusDistance},
          mAperture         {info.mAperture},
          mPosition         {info.mPosition},
          mTarget           {info.mTarget},
          mUp               {info.mUp}
    {
        mLensRadius     = mAperture * 0.5f;

        ComputeViewportDims();
        ComputeLowerLeftCorner();
    }

    ////////////////////////////////////////
    void Camera::ComputeViewportDims()
    {
        float height    = glm::tan(mFovy * 0.5f);
        mViewportHeight = -2.0f * height;
        mViewportWidth  = -mAspectRatio * mAspectMultiplier * mViewportHeight;
    }

    ////////////////////////////////////////
    void Camera::ComputeLowerLeftCorner()
    {
        mW = glm::normalize(mPosition - mTarget);
        mU = glm::normalize(glm::cross(mUp, mW));
        mV = glm::cross(mW, mU);

        mHorizontalDelta    = mFocusDistance * mViewportWidth   * mU;
        mVerticalDelta      = mFocusDistance * mViewportHeight  * mV;
        mLowerLeftCorner    = mPosition      - mHorizontalDelta * 0.5f
                                             - mVerticalDelta   * 0.5f
                                             - mFocusDistance   * mW;
    }
}
