// Copyright (C) 2022 saccharineboi

#include "NCDevice.hpp"

namespace CursedRay
{
    ////////////////////////////////////////
    ncblitter_e NCDevice::ChooseBlitter()
    {
        ncblitter_e blitter;
        if (notcurses_cansextant(mCtx))
        {
            mEffectiveWidth     = mRealWidth * 2;
            mEffectiveHeight    = mRealHeight * 3;
            blitter             = NCBLIT_3x2;
        }
        else if (notcurses_canquadrant(mCtx))
        {
            mEffectiveWidth     = mRealWidth * 2;
            mEffectiveHeight    = mRealHeight * 2;
            blitter             = NCBLIT_2x2;
        }
        else if (notcurses_canhalfblock(mCtx))
        {
            mEffectiveWidth     = mRealWidth;
            mEffectiveHeight    = mRealHeight * 2;
            blitter             = NCBLIT_2x1;
        }
        else
        {
            mEffectiveWidth     = mRealWidth;
            mEffectiveHeight    = mRealHeight;
            blitter             = NCBLIT_1x1;
        }
        return blitter;
    }

    ////////////////////////////////////////
    void NCDevice::SetOptions(ncblitter_e blitter)
    {
        mOptions.n          = mPlane;
        mOptions.scaling    = NCSCALE_NONE;
        mOptions.leny       = (unsigned)mEffectiveHeight;
        mOptions.lenx       = (unsigned)mEffectiveWidth;
        mOptions.blitter    = blitter;
        mOptions.flags      = NCVISUAL_OPTION_NOINTERPOLATE;
    }

    ////////////////////////////////////////
    void NCDevice::ProgressCallback(float percentage) const
    {
        ncplane_printf_aligned(mPlane,
                               mRealHeight / 2,
                               NCALIGN_CENTER,
                               "NCDevice::ProgressCallback(): %.2f%% rendered", percentage);
        notcurses_render(mCtx);
    }

    ////////////////////////////////////////
    void NCDevice::Blit(const Framebuffer& framebuffer)
    {
        ncblit_rgba(framebuffer.mColorBuffer,
                    mEffectiveWidth * sizeof(uint32_t),
                    &mOptions);
        notcurses_render(mCtx);
    }

    ////////////////////////////////////////
    void NCDevice::WaitForKeyPress()
    {
        struct ncinput input;
        while (notcurses_get_nblock(mCtx, &input) != 'q')
        {
            usleep(10'000);
        }
    }

    ////////////////////////////////////////
    NCDevice::NCDevice()
    {
        if (!setlocale(LC_ALL, ""))
        {
            mErrorMessage = "NCDevice::NCDevice(): coudn't set locale";
            return;
        }

        mCtx = notcurses_init(nullptr, nullptr);
        if (!mCtx)
        {
            mErrorMessage = "NCDevice::NCDevice(): couldn't initialize notcurses";
            return;
        }

        mPlane = notcurses_stdplane(mCtx);
        ncplane_dim_yx(mPlane, (unsigned*)&mRealHeight, (unsigned*)&mRealWidth);

        ncblitter_e blitter = ChooseBlitter();
        SetOptions(blitter);

        ncplane_set_fg_rgb8(mPlane, 0, 0, 0);
        ncplane_set_bg_rgb8(mPlane, 255, 255, 255);

        mIsInitialized = true;
    }
}
