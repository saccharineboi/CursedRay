// Copyright (C) 2022 saccharineboi

#include "Sphere.hpp"
#include "Camera.hpp"
#include "Random.hpp"
#include "Scene.hpp"
#include "Framebuffer.hpp"
#include "NCDevice.hpp"

#include <glm/common.hpp>

#include <string>
#include <iostream>
#include <random>
#include <ctime>

////////////////////////////////////////
#define ERR_INIT            1
#define ERR_FB              2

////////////////////////////////////////
#define NUM_SAMPLES         32
#define CLEAR_COLOR         glm::vec3(0.7f, 0.9f, 1.0f)
#define ASPECT_MULTIPLIER   0.75f
#define MAX_DEPTH           32

////////////////////////////////////////
static int StartRayTracer(std::string& errorMessage)
{
    std::srand((unsigned)std::time(0));

    CursedRay::NCDevice device;
    if (!device.mIsInitialized)
    {
        errorMessage = device.mErrorMessage;
        return ERR_INIT;
    }

    CursedRay::Framebuffer framebuffer(device.mEffectiveWidth,
                                       device.mEffectiveHeight);
    if (!framebuffer.mIsInitialized)
    {
        errorMessage = framebuffer.mErrorMessage;
        return ERR_FB;
    }

    CursedRay::CameraInfo cameraInfo {
        .mPosition          = glm::vec3(-3.0f, 1.0f, 3.0f),
        .mUp                = glm::vec3(0.0f, 1.0f, 0.0f),
        .mTarget            = glm::vec3(0.0f, 1.0f, 0.0f),
        .mAspectRatio       = (float)device.mEffectiveWidth /
                              (float)device.mEffectiveHeight,
        .mFovy              = glm::radians(65.0f),
        .mAspectMultiplier  = ASPECT_MULTIPLIER,
        .mAperture          = 0.1f,
        .mFocusDistance     = 2.5f
    };
    CursedRay::Camera camera(cameraInfo);

    CursedRay::Sphere mediumSphere0(glm::vec3(-2.1f, 1.0f, 0.0f), 1.0f);
    mediumSphere0.mMaterial.mAlbedo = glm::vec3(0.5f, 0.5f, 1.0f);
    mediumSphere0.mMaterial.mRoughness = 0.0f;
    mediumSphere0.mMaterial.mIsDielectric = true;
    mediumSphere0.mMaterial.mRefractionIndex = 1.5f;

    CursedRay::Sphere mediumSphere1(glm::vec3(0.0f, 1.0f, 0.5f), 1.0f);
    mediumSphere1.mMaterial.mAlbedo = glm::vec3(1.0f, 0.5f, 0.5f);
    mediumSphere1.mMaterial.mRoughness = 0.1f;

    CursedRay::Sphere mediumSphere2(glm::vec3(2.1f, 1.0f, 1.5f), 1.0f);
    mediumSphere2.mMaterial.mAlbedo = glm::vec3(0.5f, 1.0f, 0.5f);
    mediumSphere2.mMaterial.mRoughness = 0.5f;

    CursedRay::Sphere smallSphere0(glm::vec3(0.5f, 0.5f, 3.0f), 0.5f);
    smallSphere0.mMaterial.mAlbedo = glm::vec3(1.0f, 0.8f, 0.6f);
    smallSphere0.mMaterial.mRoughness = 0.1f;

    CursedRay::Sphere smallSphere1(glm::vec3(-0.75f, 0.4f, 2.2f), 0.4f);
    smallSphere1.mMaterial.mAlbedo = glm::vec3(0.0f, 1.0f, 1.0f);
    smallSphere1.mMaterial.mRoughness = 1.0f;

    CursedRay::Sphere smallSphere2(glm::vec3(-1.75f, 0.3f, 1.6f), 0.3f);
    smallSphere2.mMaterial.mAlbedo = glm::vec3(1.0f, 0.0f, 1.0f);
    smallSphere2.mMaterial.mRoughness = 1.0f;

    CursedRay::Sphere bigSphere(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f);
    bigSphere.mMaterial.mAlbedo = glm::vec3(0.5f);
    bigSphere.mMaterial.mRoughness = 0.25f;

    CursedRay::Scene scene;
    scene.AddSpheres({ bigSphere,
                       mediumSphere0,
                       mediumSphere1,
                       mediumSphere2,
                       smallSphere0,
                       smallSphere1,
                       smallSphere2 });

    scene.Render(camera,
                 framebuffer,
                 NUM_SAMPLES,
                 device,
                 CLEAR_COLOR,
                 MAX_DEPTH,
                 0.001f, 1000.0f);
    device.Blit(framebuffer);

    device.WaitForKeyPress();
    return 0;
}

////////////////////////////////////////
int main()
{
    std::string errorMessage;
    int status = StartRayTracer(errorMessage);
    if (status)
    {
        std::cerr << "ERROR: " << errorMessage << '\n';
        return status;
    }

    return 0;
}
