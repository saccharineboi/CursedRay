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
