#include <string>

namespace Helper{
    std::string static formatTime(int hours, int minutes, int seconds){
        std::string hoursString = ((hours < 10)?"0":"") + std::to_string(hours);
        std::string minutesString = ((minutes < 10)?"0":"") + std::to_string(minutes);
        std::string secondsString = ((seconds < 10)?"0":"") + std::to_string(seconds);

        std::string result = hoursString + ":"
                            + minutesString + ":"
                            + secondsString;
        return result;
    }
}

