#include "main.h"

#include <math.h>


//bool Memory::isInFov(D3DXVECTOR3 forward, D3DXVECTOR3 EnemyPos, D3DXVECTOR3 LocalPos, float fov)
//{
//	D3DXVECTOR3 vec1, vec2;
//	D3DXVec3Normalize(&vec1, &forward);
//	D3DXVec3Normalize(&vec2, &(EnemyPos - LocalPos));
//	float angle = acos(D3DXVec3Dot(&vec1, &vec2));
//	angle = D3DXToDegree(angle);
//
//
//	if (angle > (fov / 2))
//		return false;
//
//	return true;
//}

bool Memory::isInFov(D3DXVECTOR3 forward, D3DXVECTOR3 EnemyPos, D3DXVECTOR3 LocalPos, float fov)
{
	D3DXVECTOR3 vec1, vec2;
	D3DXVec3Normalize(&vec1, &forward);
	D3DXVec3Normalize(&vec2, &(EnemyPos - LocalPos));
	float angle = acos(D3DXVec3Dot(&vec1, &vec2));
	angle = D3DXToDegree(angle);


	if (angle > (fov / 2))
		return false;

	return true;
}

float Memory::AngleBetween(Vector &angleA, Vector &angleB, bool angle)
{

	//angleA = myViewAngle
	//angleB = enemyPos

	Vector firstAngle;
	Vector SecondAngle;

	//mag a
	firstAngle = { std::pow(angleA.x, 2), std::pow(angleA.y, 2), std::pow(angleA.z, 2) };
	float firstAngleTotal = firstAngle.x + firstAngle.y + firstAngle.z;
	//mag b
	SecondAngle = { std::pow(angleB.x, 2), std::pow(angleB.y, 2), std::pow(angleB.z, 2) };
	float secondAngleTotal = SecondAngle.x + SecondAngle.y + SecondAngle.z;
	
	//product 2 vector angleA x angleB
	float x = angleA.x * angleB.x;
	float y = angleA.y * angleB.y;
	float z = angleA.z * angleB.z;
	float resultProduct = x + y + z;

	//angle is or fov
	float cos = std::cos((resultProduct / (std::sqrt(firstAngleTotal) * std::sqrt(secondAngleTotal)))); // gerar coseno
	
	if (angle) // give angle based in cos
	{
		cos = (float)(std::acos(cos) * 180.0 / PI);
	}
	//this will return cos like 0,9998 0,5433
	return cos;
}

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
