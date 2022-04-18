// Copyright (C) 2022 saccharineboi

#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/epsilon.hpp>

#include <cstdint>
#include <string>

namespace CursedRay
{
    ////////////////////////////////////////
    struct Framebuffer
    {
        ////////////////////////////////////////
        Framebuffer(int width, int height);

        ////////////////////////////////////////
        ~Framebuffer();

        ////////////////////////////////////////
        Framebuffer(const Framebuffer&);
        Framebuffer& operator=(const Framebuffer&);

        ////////////////////////////////////////
        Framebuffer(Framebuffer&&);
        Framebuffer& operator=(Framebuffer&&);

        ////////////////////////////////////////
        void SetPixel(int row, int col, const glm::vec3& color)
        {
            uint32_t red        = (uint32_t)(color[0] * 255.0f);
            uint32_t green      = (uint32_t)(color[1] * 255.0f);
            uint32_t blue       = (uint32_t)(color[2] * 255.0f);
            uint32_t alpha      = 255;

            int index = row * mWidth + col;
            mColorBuffer[index] = ((alpha << 24) |
                                   (blue  << 16) |
                                   (green << 8)  |
                                   (red   << 0));
        }

        ////////////////////////////////////////
        int mWidth;
        int mHeight;
        
        uint32_t* mColorBuffer  = nullptr;

        bool mIsInitialized       = false;
        std::string mErrorMessage;
    };
}
