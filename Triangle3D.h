#pragma once

#include "Quaternion.h"
#include "Vector3D.h"

class Triangle3D {
public:
	Vector3D* p1;
	Vector3D* p2;
	Vector3D* p3;
 
  Vector3D edge1;
  Vector3D edge2;
	Vector3D normal = Vector3D();

	Triangle3D(){
		p1 = new Vector3D();
		p2 = new Vector3D();
		p3 = new Vector3D();
	}

	Triangle3D(Vector3D* p1, Vector3D* p2, Vector3D* p3) {
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;

		this->Normal();
	}

	Vector3D Normal() {
    edge1 = *p2 - *p1;
    edge2 = *p3 - *p1;
		normal = edge1.CrossProduct(edge2).UnitSphere();
		
		return normal;
	}

	void Translate(Quaternion q, Vector3D p) {
		*p1 = q.RotateVector(*p1) + p;
		*p2 = q.RotateVector(*p2) + p;
		*p3 = q.RotateVector(*p3) + p;

		Normal();
	}

	bool DidIntersect(Vector3D ray, Vector3D direction, Vector3D* intersect, Vector3D* color) {
		Vector3D pvec = direction.CrossProduct(edge2);
		double det = edge1.DotProduct(pvec);
		double invDet = 1.0 / det;

		//if (det < FLT_EPSILON) return false;//non culling
		//if (-det < FLT_EPSILON) return false;//culling
		if (fabs(det) < 0.000001) return false;//ray/triangle parallel if close to 0

		Vector3D tvec = ray - *p1;
		double u = tvec.DotProduct(pvec) * invDet;
		if (u < 0.0 || u > 1.0) return false;

		Vector3D qvec = tvec.CrossProduct(edge1);
		double v = direction.DotProduct(qvec) * invDet;
		if (v < 0.0 || u + v > 1.0) return false;

		double t = edge2.DotProduct(qvec) * invDet;//

		if (t > 0.000001) {//ray intersection
			Vector3D tempInt = *p1 + (edge2 * u) + (edge1 * v);

			tempInt = ray + direction.Multiply(t);

			intersect->X = tempInt.X;
			intersect->Y = tempInt.Y;
			intersect->Z = tempInt.Z;

			color->X = u;
			color->Y = v;
			color->Z = (1.0 - u - v);

			return true;
		}
		else {
			return false;
		}
	}

	string ToString() {
		return p1->ToString() + " " + p2->ToString() + " " + p3->ToString();
	}
};
