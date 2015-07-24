#include "main.h"

double Memory::Distance(Vector a, Vector b, bool metters)
{
	double dist = std::sqrt(
		std::pow(b.x - a.x, 2.0f) +
		std::pow(b.y - a.y, 2.0f) +
		std::pow(b.z - a.z, 2.0f)
		);

	if (metters)
		dist *= 0.0245f;

	return dist;
}

Vector Memory::BonePos(DWORD target, DWORD address, int boneId)
{	
	DWORD boneBase = RPM<DWORD>(proc, (target + address), sizeof(DWORD));
	Vector vBone;	
	vBone.x = RPM<float>(proc, (boneBase + 0x30 * boneId + 0x0C), sizeof(float));
	vBone.y = RPM<float>(proc, (boneBase + 0x30 * boneId + 0x1C), sizeof(float));
	vBone.z = RPM<float>(proc, (boneBase + 0x30 * boneId + 0x2C), sizeof(float));
	return vBone;
}

Vector Memory::CalcAngle(Vector& src, Vector& dst)
{
	Vector vAngle;
	Vector delta;
	delta.x = src.x - dst.x;
	delta.y = src.y - dst.y;
	delta.z = src.z - dst.z;
	double hyp = sqrt(delta.x*delta.x + delta.y*delta.y);

	vAngle.x = (float)(atan((delta.z + 64.06f) / hyp) * 57.295779513082f);
	vAngle.y = (float)(atan(delta.y / delta.x) * 57.295779513082f);
	vAngle.z = 0.0f;

	if (delta.x >= 0.0)
		vAngle.y += 180.0f;

	return vAngle;
}

void Memory::ClampAngle(Vector &angles)
{
	if (angles.x > 89.f)
		angles.x -= 360.f;
	else if (angles.x < -89.f)
		angles.x += 360.f;
	if (angles.y > 180.f)
		angles.y -= 360.f;
	else if (angles.y < -180.f)
		angles.y += 360.f;

	angles.z = 0;
}
