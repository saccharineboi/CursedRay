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

////////////////////////////////////////////////////////////////////////////////////////////////////
__kernel void clear_color(__global float* out, float4 clearColor, uint colSizeInBytes)
{
    uint row     = get_global_id(0);
    uint col     = get_global_id(1);
    uint channel = get_global_id(2);

blah

    out[row * colSizeInBytes + col + channel] = clearColor[channel];
}
