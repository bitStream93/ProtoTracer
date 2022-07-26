#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

class Vector2D {
public:
	float X = 0.0f;
	float Y = 0.0f;

	Vector2D() {
		this->X = 0.0;
		this->Y = 0.0;
	}

	Vector2D(const Vector2D& vector) {
		this->X = vector.X;
		this->Y = vector.Y;
	}

	Vector2D(float X, float Y) {
		this->X = X;
		this->Y = Y;
	}

	Vector2D(const Vector3D& vector) {
		this->X = vector.X;
		this->Y = vector.Y;
	}

	Vector2D Absolute() {
		return Vector2D{
			fabsf(X),
			fabsf(Y)
		};
	}

	Vector2D Normal() {
		float magn = Magnitude();
		
		if (Mathematics::IsClose(magn, 1.0f, Mathematics::EPSILON)){
			return (*this);
		}
		else if (Mathematics::IsClose(magn, 0.0f, Mathematics::EPSILON)){
			return Multiply(3.40282e+038f);
		}
		else{
			return Multiply(1.0f / magn);
		}
	}

	Vector2D Add(Vector2D vector) {
		return Vector2D{
			X + vector.X,
			Y + vector.Y
		};
	}

	Vector2D Subtract(Vector2D vector) {
		return Vector2D{
			X - vector.X,
			Y - vector.Y
		};
	}

	Vector2D Multiply(Vector2D vector) {
		return Vector2D{
			X * vector.X,
			Y * vector.Y
		};
	}

	Vector2D Divide(Vector2D vector) {
		return Vector2D{
			X / vector.X,
			Y / vector.Y
		};
	}

	Vector2D Multiply(float scalar) {
		if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return (*this);
		if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector3D();

		return Vector2D{
			X * scalar,
			Y * scalar
		};
	}

	Vector2D Divide(float scalar) {
		if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return (*this);
		if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector3D();
		
		return Vector2D{
			X / scalar,
			Y / scalar
		};

	}

	Vector3D CrossProduct(Vector2D vector) {
		return Vector3D{
			0.0f,
			0.0f,
			(X * vector.Y) - (Y * vector.X)
		};
	}

	Vector2D UnitCircle() {
		float length = Magnitude();

		if (Mathematics::IsClose(length, 1.0f, Mathematics::EPSILON)) return Vector2D(this->X, this->Y);
		if (length == 0) return Vector2D(0, 1);

		return Vector2D{
			X / length,
			Y / length
		};
	}

	Vector2D Constrain(float minimum, float maximum) {
		return Vector2D{
			Mathematics::Constrain(X, minimum, maximum),
			Mathematics::Constrain(Y, minimum, maximum)
		};
	}

	Vector2D Constrain(Vector2D minimum, Vector2D maximum) {
		return Vector2D{
			Mathematics::Constrain(X, minimum.X, maximum.X),
			Mathematics::Constrain(Y, minimum.Y, maximum.Y)
		};
	}

	Vector2D Minimum(Vector2D v) {
		return Vector2D{
			X < v.X ? X : v.X,
			Y < v.Y ? Y : v.Y
		};
	}

	Vector2D Maximum(Vector2D v) {
		return Vector2D{
			X > v.X ? X : v.X,
			Y > v.Y ? Y : v.Y
		};
	}

	Vector2D Rotate(float angle, Vector2D offset){
		Vector2D v = Vector2D(X, Y).Subtract(offset);

		angle = angle * Mathematics::MPID180;

		float cs = cosf(angle);
		float sn = sinf(angle);

		return Vector2D{
			v.X * cs - v.Y * sn + offset.X,
			v.X * sn + v.Y * cs + offset.Y
		};
	}

	bool CheckBounds(Vector2D minimum, Vector2D maximum) {
		return X > minimum.X && X < maximum.X && Y > minimum.Y && Y < maximum.Y;
	}

	float Magnitude() {
		return Mathematics::Sqrt(X * X + Y * Y);
	}

	float DotProduct(Vector2D vector) {
		return (X * vector.X) + (Y * vector.Y);
	}

	float CalculateEuclideanDistance(Vector2D vector) {
		vector = Subtract(vector);

		return vector.Magnitude();
	}

	bool IsEqual(Vector2D vector) {
		return (X == vector.X) && (Y == vector.Y);
	}

	string ToString() {
		string x = Mathematics::DoubleToCleanString(X);
		string y = Mathematics::DoubleToCleanString(Y);

		return "[" + x + ", " + y + "]";
	}

	
	static Vector2D Minimum(Vector2D v1, Vector2D v2){
		return Vector2D{
			v1.X < v2.X ? v1.X : v2.X,
			v1.Y < v2.Y ? v1.Y : v2.Y
		};
	}

	static Vector2D Maximum(Vector2D v1, Vector2D v2){
		return Vector2D{
			v1.X > v2.X ? v1.X : v2.X,
			v1.Y > v2.Y ? v1.Y : v2.Y
		};
	}

  
	static Vector2D LERP(Vector2D start, Vector2D finish, float ratio) {
		return finish * ratio + start * (1.0f - ratio);
	}
  
	static Vector2D DegreesToRadians(Vector2D degrees) {
		return degrees / (180.0f / Mathematics::MPI);
	}

	static Vector2D RadiansToDegrees(Vector2D radians) {
		return radians * (180.0f / Mathematics::MPI);
	}

	//Static function declaractions
	static Vector2D Normal(Vector2D vector) {
		return vector.Normal();
	}

	static Vector2D Add(Vector2D v1, Vector2D v2) {
		return v1.Add(v2);
	}

	static Vector2D Subtract(Vector2D v1, Vector2D v2) {
		return v1.Subtract(v2);
	}

	static Vector2D Multiply(Vector2D v1, Vector2D v2) {
		return v1.Multiply(v2);
	}

	static Vector2D Divide(Vector2D v1, Vector2D v2) {
		return v1.Divide(v2);
	}

	static Vector2D Multiply(Vector2D vector, float scalar) {
		return vector.Multiply(scalar);
	}

	static Vector2D Multiply(float scalar, Vector2D vector) {
		return vector.Multiply(scalar);
	}

	static Vector2D Divide(Vector2D vector, float scalar) {
		return vector.Divide(scalar);
	}

	static Vector3D CrossProduct(Vector2D v1, Vector2D v2) {
		return v1.CrossProduct(v2);
	}

	static float DotProduct(Vector2D v1, Vector2D v2) {
		return v1.DotProduct(v2);
	}

	static float CalculateEuclideanDistance(Vector2D v1, Vector2D v2) {
		return v1.CalculateEuclideanDistance(v2);
	}

	static bool IsEqual(Vector2D v1, Vector2D v2) {
		return v1.IsEqual(v2);
	}

	//Operator overloads
	bool operator ==(Vector2D vector) {
		return this->IsEqual(vector);
	}

	bool operator !=(Vector2D vector) {
		return !(this->IsEqual(vector));
	}

	Vector2D operator  =(Vector2D vector) {
		this->X = vector.X;
		this->Y = vector.Y;

		return *this;
	}

	Vector2D operator  =(Vector3D vector) {
		this->X = vector.X;
		this->Y = vector.Y;

		return *this;
	}

	Vector2D operator  +(Vector2D vector) {
		return Add(vector);
	}

	Vector2D operator  -(Vector2D vector) {
		return Subtract(vector);
	}

	Vector2D operator  *(Vector2D vector) {
		return Multiply(vector);
	}

	Vector2D operator  /(Vector2D vector) {
		return Divide(vector);
	}

	Vector2D operator  *(float value) {
		return Multiply(value);
	}

	Vector2D operator  /(float value) {
		return Divide(value);
	}
};
