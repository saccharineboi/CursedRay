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

#include "NCDevice.hpp"

#include <cstdlib>
#include <notcurses/notcurses.h>

namespace CursedRay
{
    ////////////////////////////////////////
    void NCDevice::Blit(const std::vector<float>& pixels) const
    {
        std::int32_t rows{ static_cast<std::int32_t>(mPixelsHeight) };
        std::int32_t cols{ static_cast<std::int32_t>(mPixelsWidth) };
        ncvisual* ncv{ ncvisual_from_rgb_packed(pixels.data(), rows, rows * 3, cols, NCALPHA_OPAQUE) };
        ncvisual_blit(mContext, ncv, &mOptions);
        notcurses_render(mContext);
        ncvisual_destroy(ncv);
    }

    ////////////////////////////////////////
    NCDevice::NCDevice()
    {
        if (!setlocale(LC_ALL, ""))
        {
            std::fprintf(stderr, "CursedRay: coudn't set locale");
            std::exit(EXIT_FAILURE);
        }

        notcurses_options options{};
        options.flags = NCOPTION_NO_ALTERNATE_SCREEN | NCOPTION_SUPPRESS_BANNERS;

        mContext = notcurses_init(&options, nullptr);
        if (!mContext)
        {
            std::fprintf(stderr, "CursedRay: couldn't initialize notcurses");
            std::exit(EXIT_FAILURE);
        }

        mPlane = notcurses_stdplane(mContext);
        ncplane_dim_yx(mPlane, &mHeight, &mWidth);
#ifdef _DEBUG
        std::printf("CursedRay: number of cells: %u:%u\n", mWidth, mHeight);
#endif

        ncplane_pixel_geom(mPlane, &mPixelsHeight, &mPixelsWidth, &mCellHeight, &mCellWidth, nullptr, nullptr);
#ifdef _DEBUG
        std::printf("CursedRay: dimensions of the terminal in pixels: %u:%u\n", mPixelsWidth, mPixelsHeight);
        std::printf("CursedRay: dimensions of each cell: %u:%u\n", mCellWidth, mCellHeight);
#endif

        ncblitter_e blitter{};
        if (notcurses_canpixel(mContext))
        {
            blitter = NCBLIT_PIXEL;
#ifdef _DEBUG
            std::printf("CursedRay: can blit in pixels\n");
#endif
        }
        else if (notcurses_cansextant(mContext))
        {
            blitter = NCBLIT_3x2;
#ifdef _DEBUG
            std::printf("CursedRay: can blit in sextants\n");
#endif
        }
        else if (notcurses_canquadrant(mContext))
        {
            blitter = NCBLIT_2x2;
#ifdef _DEBUG
            std::printf("CursedRay: can blit in quadrants\n");
#endif
        }
        else if (notcurses_canhalfblock(mContext))
        {
            blitter = NCBLIT_2x1;
#ifdef _DEBUG
            std::printf("CursedRay: can blit in halves\n");
#endif
        }
        else
        {
            blitter = NCBLIT_1x1;
#ifdef _DEBUG
            std::printf("CursedRay: can blit in cells\n");
#endif
        }

        mOptions.n = mPlane;
        mOptions.scaling = NCSCALE_NONE;
        mOptions.leny = mHeight;
        mOptions.lenx = mWidth;
        mOptions.blitter = blitter;
        mOptions.flags = NCVISUAL_OPTION_NOINTERPOLATE;

        ncplane_set_fg_rgb8(mPlane, 0, 0, 0);
        ncplane_set_bg_rgb8(mPlane, 255, 255, 255);
    }
}
