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

#include "Framebuffer.hpp"

#include <cstring>
#include <algorithm>

namespace CursedRay
{
    ////////////////////////////////////////
    Framebuffer::Framebuffer(const FramebufferOptions& options)
        : mWidth{options.GetWidth()}, mHeight{options.GetHeight()}
    {
        glm::vec4 clearColor{ options.GetClearColor() };
        mData.reserve(mWidth * mHeight * GetNumChannels());
        for (std::uint32_t row{}; row < mHeight; ++row) {
            for (std::uint32_t col{}; col < mWidth; ++col) {
                std::uint8_t redChannel{ static_cast<std::uint8_t>(clearColor.r * 255.0f) };
                std::uint8_t greenChannel{ static_cast<std::uint8_t>(clearColor.g * 255.0f) };
                std::uint8_t blueChannel{ static_cast<std::uint8_t>(clearColor.b * 255.0f) };
                std::uint8_t alphaChannel{ static_cast<std::uint8_t>(clearColor.a * 255.0f) };

                mData.push_back(redChannel);
                mData.push_back(greenChannel);
                mData.push_back(blueChannel);
                mData.push_back(alphaChannel);
            }
        }
    }
}
