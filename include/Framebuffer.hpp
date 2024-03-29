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

#pragma once

#include <glm/vec4.hpp>
#include <glm/gtc/epsilon.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace CursedRay
{
    ////////////////////////////////////////
    struct FramebufferOptions
    {
    private:
        std::uint32_t mWidth;
        std::uint32_t mHeight;
        glm::vec4 mClearColor;

    public:
        FramebufferOptions(std::uint32_t width,
                           std::uint32_t height,
                           const glm::vec4& clearColor)
            : mWidth{width}, mHeight{height}, mClearColor{clearColor} {}

        std::uint32_t GetWidth() const { return mWidth; }
        std::uint32_t GetHeight() const { return mHeight; }
        glm::vec4 GetClearColor() const { return mClearColor; }
    };

    ////////////////////////////////////////
    struct Framebuffer
    {
    private: 
        std::vector<std::uint8_t> mData;
        std::uint32_t mWidth;
        std::uint32_t mHeight;

    public:
        explicit Framebuffer(const FramebufferOptions& options);

        std::uint32_t GetWidth() const { return mWidth; }
        std::uint32_t GetHeight() const { return mHeight; }
        std::uint32_t GetSizeInBytes() const { return mWidth * mHeight * GetNumChannels(); }
        std::uint32_t GetNumChannels() const { return 4; }

        std::int32_t GetWidthSigned() const { return static_cast<std::int32_t>(mWidth); }
        std::int32_t GetHeightSigned() const { return static_cast<std::int32_t>(mHeight); }
        std::int32_t GetNumChannelsSigned() const { return static_cast<std::int32_t>(GetNumChannels()); }

        const std::uint8_t* GetData() const { return mData.data(); }
        void Clear() { mData.clear(); }
        void PushPixel(std::uint8_t pixel) { mData.push_back(pixel); }

        std::vector<std::uint8_t>::iterator begin() { return mData.begin(); }
        std::vector<std::uint8_t>::const_iterator cbegin() const { return mData.cbegin(); }

        std::vector<std::uint8_t>::iterator end() { return mData.end(); }
        std::vector<std::uint8_t>::const_iterator cend() const { return mData.cend(); }
    };
}
