// Copyright (C) 2022 saccharineboi

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
        if (!other.mIsInitialized)
        {
            mIsInitialized = false;
            return;
        }

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
        if (!other.mIsInitialized)
        {
            mIsInitialized = false;
            return *this;
        }

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
