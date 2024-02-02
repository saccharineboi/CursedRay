// CursedRay: Hardware-accelerated path tracer
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
