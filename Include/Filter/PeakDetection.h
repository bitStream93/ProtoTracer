#pragma once


#include "../Math/Mathematics.h"

template <size_t sampleSize>
class PeakDetection{
private:
    uint8_t lag;

    float threshold;
    float influence;
    float filData[sampleSize];
    float avg[sampleSize];
    float std[sampleSize];

    void GetStdDev(uint8_t start, uint8_t length, float* data, float& avgRet, float& stdRet){
        float average = 0.0f;
        float stdDev = 0.0f;

        for (uint8_t i = 0; i < length; i++){
            average += data[start + i];
        }
        

        average /= (float)length;

        for (uint8_t i = 0; i < length; i++){
            stdDev += powf(data[start + i] - average, 2.0f);
        }

        avgRet = average;
        stdRet = sqrtf(stdDev / (float)length);
    }

public:
    PeakDetection(uint8_t lag = 12, float threshold = 0.75f, float influence = 0.5f) {
        this->lag = lag;
        this->threshold = threshold;
        this->influence = influence;
    }

    void Calculate(float* data, float* peaks){
        float average = 0.0f;
        float stdDev = 0.0f;

        for (uint8_t i = 0; i < sampleSize; i++){
            filData[i] = 0.0f;
            avg[i] = 0.0f;
            std[i] = 0.0f;
        }

        GetStdDev(0, lag, data, average, stdDev);

        avg[lag - 1] = average;
        std[lag - 1] = stdDev;

        for(uint8_t i = lag; i < sampleSize - lag; i++){
            if(fabs(data[i] - avg[i - 1]) > threshold * std[i - 1]){
                if(data[i] > avg[i - 1]) peaks[i] = 1.0f;
                //else peaks[i] = -1.0f;

                filData[i] = influence * data[i] + (1.0f - influence) * filData[i - 1];
            }
            else{
                peaks[i] = 0;
                filData[i] = data[i];
            }

            GetStdDev(i - lag + 1, i, data, avg[i], std[i]);
            
            avg[i] = average;
            std[i] = stdDev;
        }
    }
};
