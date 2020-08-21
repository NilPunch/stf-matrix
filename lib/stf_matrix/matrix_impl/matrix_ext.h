
#pragma once
#include <cmath>

namespace stf
{
	Mat3 RotationMat(float AngleX, float AngleY, float AngleZ)
	{
		float cosX = cosf(AngleX), sinX = sinf(AngleX),
			cosY = cosf(AngleY), sinY = sinf(AngleY),
			cosZ = cosf(AngleZ), sinZ = sinf(AngleZ);

		Mat3 RotationX = {
			1.0f,   0.0f,   0.0f,
			0.0f,   cosX,  -sinX,
			0.0f,   sinX,   cosX
		};

		Mat3 RotationY = {
			cosY,   0.0f,  -sinY,
			0.0f,   1.0f,   0.0f,
			sinY,   0.0f,   cosY
		};

		Mat3 RotationZ = {
			cosZ,  -sinZ,   0.0f,
			sinZ,   cosZ,   0.0f,
			0.0f,   0.0f,   1.0f
		};

		return RotationX * RotationY * RotationZ;
	}

	/*Mat3 OrthoProjection()
	{

	}
	Mat3 PerspectiveProjection()
	{

	}*/
}