// Copyright (C) 2022 saccharineboi

#pragma once

#include "Framebuffer.hpp"

#include <notcurses/notcurses.h>
#include <string>

namespace CursedRay
{
    ////////////////////////////////////////
    struct NCDevice
    {
        ////////////////////////////////////////
        NCDevice();

        ////////////////////////////////////////
        ~NCDevice() { notcurses_stop(mCtx); }

        ////////////////////////////////////////
        NCDevice(const NCDevice&)               = delete;
        NCDevice& operator=(const NCDevice&)    = delete;
        NCDevice(NCDevice&&)                    = delete;
        NCDevice& operator=(NCDevice&&)         = delete;

        ////////////////////////////////////////
        ncblitter_e ChooseBlitter();
        void SetOptions(ncblitter_e blitter);
        void Blit(const Framebuffer& framebuffer) const;
        void WaitForKeyPress() const;

        ////////////////////////////////////////
        void ProgressCallback(float percentage) const;

        ////////////////////////////////////////
        int mRealWidth, mRealHeight;
        int mEffectiveWidth, mEffectiveHeight;

        bool mIsInitialized    = false;
        std::string mErrorMessage;

        struct notcurses* mCtx = nullptr;
        struct ncplane* mPlane = nullptr;
        struct ncvisual_options mOptions{};
    };
}
