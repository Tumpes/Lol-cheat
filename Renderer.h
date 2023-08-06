#pragma once
#include <Windows.h>
#include "Vector.h"
#include <iostream>
#include "Offsets.h"
#include "Globals.h"

class GameRenderer {

public:

	int      width, height;

	float    viewMatrix[16];
	float    projMatrix[16];
    float    viewProjMatrix[16];

    void     LoadFromMem();

	Vector2 WorldToScreen(const Vector3 pos);

private:
	void     MultiplyMatrices(float* out, float* a, int row1, int col1, float* b, int row2, int col2);

};

extern GameRenderer renderer;