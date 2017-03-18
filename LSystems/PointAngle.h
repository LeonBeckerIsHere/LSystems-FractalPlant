#pragma once

struct PointAngle {
	float x;
	float y;
	float angle;
	PointAngle(float xx, float yy, float ang) { x = xx; y = yy; angle = ang; }
	PointAngle() { x = 0.0f, y = 0.0f, angle = 0.0f; }
};