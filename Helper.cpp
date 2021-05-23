#include <string>
#include <math.h>

class Helper{
public:
    std::string static formatTime(int hours, int minutes, int seconds){
        std::string hoursString = ((hours < 10)?"0":"") + std::to_string(hours);
        std::string minutesString = ((minutes < 10)?"0":"") + std::to_string(minutes);
        std::string secondsString = ((seconds < 10)?"0":"") + std::to_string(seconds);

        std::string result = hoursString + ":"
                            + minutesString + ":"
                            + secondsString;
        return result;
    }

    float static formatFloat(float f, int numberOfDecimals){
        if(numberOfDecimals < 1)
            return f;

        int t = pow(10,numberOfDecimals);
        int floatAsInt = (int)(f * t + .5);

        float result = (float)floatAsInt / t;

        return result;
    }
};
