#pragma once
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

enum CameraMode {
    CAMERA_FREE = 0,
    CAMERA_COCKPIT,
    CAMERA_FOLLOWING
};

int cameraMode = CAMERA_FREE;

bool COCKPIT = false;
bool FOLLOW = false;
bool MENU = false;

float fogDensity = 0.0f;