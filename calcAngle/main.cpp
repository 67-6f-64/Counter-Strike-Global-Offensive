//////////////////////////////////////////////
// CONSOLE APP TO CALC ANGLE BETWEEN VECTORS//
// br dmThread/dm0000 ////////////////////////
//////////////////////////////////////////////

#include <iostream>
#define PI 3.14159265

typedef struct
{
	float   x;
	float   y;
	float   z;
}Vector, *PVector;

float AngleBetween(Vector &angleA, Vector &angleB, bool angle);
Vector a;
Vector b;

int main()
{
	std::cout << "Let's calculate angle between two vectors:" << std::endl;
	std::cout << "Vector A:" << std::endl;
	std::cout << "a.x: ";
	std::cin >> a.x;
	std::cout << "a.y: ";
	std::cin >> a.y;
	std::cout << "a.z: ";
	std::cin >> a.z;

	std::cout << "Vector B:" << std::endl;
	std::cout << "b.x: ";
	std::cin >> b.x;
	std::cout << "b.y: ";
	std::cin >> b.y;
	std::cout << "b.z: ";
	std::cin >> b.z;

	std::cout << "Vector a:" << a.x << "," << a.y << "," << a.z << std::endl;
	std::cout << "Vector b:" << b.x << "," << b.y << "," << b.z << std::endl;
	std::cout << "Cos: " << AngleBetween(a, b, false) << " Angle: " << AngleBetween(a, b, true) << std::endl << std::endl;

	system("pause");

	return 0;
}

float AngleBetween(Vector &angleA, Vector &angleB, bool angle)
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
