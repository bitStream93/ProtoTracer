#pragma once
#include "../Math/Mathematics.h"
#include "../Math/Quaternion.h"
#include "../Math/Vector3D.h"

class RGBColor {
public:
	uint8_t R = 0;
	uint8_t G = 0;
	uint8_t B = 0;

	RGBColor() {}

	RGBColor(uint8_t R, uint8_t G, uint8_t B) {
		this->R = R;
		this->G = G;
		this->B = B;
	}
    
	RGBColor(const RGBColor& rgbColor) {
		this->R = rgbColor.R;
		this->G = rgbColor.G;
		this->B = rgbColor.B;
	}

	RGBColor(Vector3D color) {
		this->R = color.X;
		this->G = color.Y;
		this->B = color.Z;
	}

	RGBColor Scale(uint8_t maxBrightness) {
		int sR, sG, sB;
        
		sR = (int)R * (int)maxBrightness / 255;
		sG = (int)G * (int)maxBrightness / 255;
		sB = (int)B * (int)maxBrightness / 255;
        
		sR = sR > 255 ? 255 : sR;
		sG = sG > 255 ? 255 : sG;
		sB = sB > 255 ? 255 : sB;
        
		sR = sR < 0 ? 0 : sR;
		sG = sG < 0 ? 0 : sG;
		sB = sB < 0 ? 0 : sB;
        
		return RGBColor(sR, sG, sB);
	}

	RGBColor Add(uint8_t value) {
		int sR, sG, sB;
        
		sR = (int)R + (int)value;
		sG = (int)G + (int)value;
		sB = (int)B + (int)value;
        
		sR = sR > 255 ? 255 : sR;
		sG = sG > 255 ? 255 : sG;
		sB = sB > 255 ? 255 : sB;
        
		sR = sR < 0 ? 0 : sR;
		sG = sG < 0 ? 0 : sG;
		sB = sB < 0 ? 0 : sB;
        
		return RGBColor(sR, sG, sB);
	}

	RGBColor HueShift(float hueDeg) {
		//hueDeg = (int)hueDeg % 360;
		//shift color space by rotating rgb vector about diagonal vector (1, 1, 1)
		float hueRad = hueDeg * Mathematics::MPI / 180.0f;
		float hueRat = 0.5f * sinf(hueRad / 2.0f);//2.0f for quaternion creation
		Vector3D rgbVec = Vector3D(R, G, B);
		Quaternion q = Quaternion(cosf(hueRad / 2.0f), hueRat, hueRat, hueRat);

		rgbVec = q.RotateVector(rgbVec).Constrain(0.0f, 255.0f);
        
		return RGBColor(rgbVec.X, rgbVec.Y, rgbVec.Z);
	}

	static RGBColor InterpolateColors(RGBColor a, RGBColor b, float ratio) {
		RGBColor c;

		c.R = a.R * (1.0f - ratio) + b.R * ratio;
		c.G = a.G * (1.0f - ratio) + b.G * ratio;
		c.B = a.B * (1.0f - ratio) + b.B * ratio;

		return c;
	}
    
	string ToString() {
		string r = to_string(this->R);
		string g = to_string(this->G);
		string b = to_string(this->B);
        
		return "[" + r + ", " + g + ", " + b + "]";
	}
};