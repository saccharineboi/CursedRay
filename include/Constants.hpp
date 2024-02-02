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

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <notcurses/notcurses.h>

namespace CursedRay
{
    ////////////////////////////////////////
    constexpr int CURSEDRAY_VERSION_MAJOR           { 0 };
    constexpr int CURSEDRAY_VERSION_MINOR           { 1 };
    constexpr int CURSEDRAY_VERSION_PATCH           { 0 };

    ////////////////////////////////////////
    constexpr int DEFAULT_ARG_STR_LEN               { 20 };

    ////////////////////////////////////////
    constexpr bool DEFAULT_NO_ALTERNATE_SCREEN      { true };
    constexpr bool DEFAULT_SUPPRESS_BANNERS         { true };
    constexpr ncblitter_e DEFAULT_BLITTER           { NCBLIT_1x1 };
    constexpr ncloglevel_e DEFAULT_LOGLEVEL         { NCLOGLEVEL_SILENT };
    constexpr const char DEFAULT_LOGFILE_NAME[]     { "cray.log" };
    constexpr glm::vec4 DEFAULT_CLEAR_COLOR         { glm::vec4(0.2f, 0.2f, 0.3f, 1.0f) };
    constexpr glm::vec3 DEFAULT_CAMERA_POSITION     { glm::vec3(0.0f, 0.0f, 0.0f) };
    constexpr float DEFAULT_CAMERA_FOCAL_LENGTH     { 1.0f };

    ////////////////////////////////////////
    constexpr const char KERNEL_CLEAR_COLOR_PATH[]  { "../kernels/clear_color.cl" };

    ////////////////////////////////////////
    constexpr const char KERNEL_CLEAR_COLOR_NAME[]  { "clear_color" };
}
