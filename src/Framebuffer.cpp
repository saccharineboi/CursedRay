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

#include "Framebuffer.hpp"

#include <cstring>
#include <algorithm>

namespace CursedRay
{
    ////////////////////////////////////////
    Framebuffer::~Framebuffer()
    {
        delete[] mColorBuffer;
    }

    ////////////////////////////////////////
    Framebuffer::Framebuffer(int width, int height)
        : mWidth{width}, mHeight{height}
    {
        mColorBuffer = new uint32_t[mWidth * mHeight];
        if (!mColorBuffer)
        {
            mErrorMessage = "Framebuffer::Framebuffer(): insufficient memory for mColorBuffer";
            return;
        }
        std::fill_n(mColorBuffer, mWidth * mHeight, 0);
        mIsInitialized = true;
    }

    ////////////////////////////////////////
    Framebuffer::Framebuffer(const Framebuffer& other)
        : mWidth{other.mWidth}, mHeight{other.mHeight}
    {
        mColorBuffer = new uint32_t[mWidth * mHeight];
        if (!mColorBuffer)
        {
            mErrorMessage = "Framebuffer::Framebuffer(): insufficient memory for mColorBuffer";
            return;
        }
        std::copy(other.mColorBuffer, other.mColorBuffer + mWidth * mHeight, mColorBuffer);
        mIsInitialized = true;
    }

    ////////////////////////////////////////
    Framebuffer& Framebuffer::operator=(const Framebuffer& other)
    {
        mWidth  = other.mWidth;
        mHeight = other.mHeight;

        delete[] mColorBuffer;
        mColorBuffer = new uint32_t[mWidth * mHeight];
        if (!mColorBuffer)
        {
            mErrorMessage = "Framebuffer::operator=(): insufficient memory for mColorBuffer";
            return *this;
        }
        std::copy(other.mColorBuffer, other.mColorBuffer + mWidth * mHeight, mColorBuffer);
        mIsInitialized = true;
        return *this;
    }

    ////////////////////////////////////////
    Framebuffer::Framebuffer(Framebuffer&& other)
        : mWidth            {other.mWidth},
          mHeight           {other.mHeight},
          mColorBuffer      {other.mColorBuffer},
          mIsInitialized    {other.mIsInitialized}
    {
        other.mColorBuffer = nullptr;
    }

    ////////////////////////////////////////
    Framebuffer& Framebuffer::operator=(Framebuffer&& other)
    {
        mWidth              = other.mWidth;
        mHeight             = other.mHeight;
        mIsInitialized      = other.mIsInitialized;

        delete[] mColorBuffer;
        mColorBuffer        = other.mColorBuffer;
        other.mColorBuffer  = nullptr;

        return *this;
    }
}
