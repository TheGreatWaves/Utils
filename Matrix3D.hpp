#pragma once

struct Matrix3D
{
public:
	Matrix3D() = default;

	Matrix3D(
		float n00, float n01, float n02,
		float n03, float n04, float n05,
		float n06, float n07, float n08
	)
	{
		n[0][0] = n00, n[0][1] = n01, n[0][2] = n02,
			n[0][3] = n03, n[0][4] = n04, n[0][5] = n05,
			n[0][6] = n06, n[0][7] = n07, n[0][8] = n08;
	}

private:
	float n[3][3]{};
};