#include <string>
#include <vector>
#include <sstream>

struct timer {
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
};

struct err {
    bool fail = false;
    std::string name = "";
};

struct MineralsPercentage{
    float Ca = 0.0;
    float Mg = 0.0;
    float N = 0.0;
    float P = 0.0;
    float K = 0.0;
    float S = 0.0;
};

// Defining the class of the Harvestic. It should model the entire configuration of the Harvestic
class Harvestic {
public:
    explicit Harvestic();
    bool getHoseState(int index);
    void setHoseState(int index, bool value);
    int getHosesCount();
    void setHosesCount(int nr);
    std::vector<err> getErrors();
    void setError(int index, bool value);
    float getAirTemperature();
    void setAirTemperature(float temp);
    float getAirHumidity();
    void setAirHumidity(float hum);
    timer getTimeOfDay();
    void setTimeOfDay(timer t);
    void setTimeOfDay(std::string s);
    int getWaterTemp();
    void setWaterTemp(int value);
    MineralsPercentage getMineralsPercentage();
    void setMineralsPercentage(MineralsPercentage mp);
    float getSoilHumidity();
    void setSoilHumidity(float s);
    float getPh();
    void setPh(float p);
    std::string getMeteoRecommendations();
    std::vector<std::string> getSoilRecommendations();
private:
    std::vector<bool> stateOfHose;
    std::vector<err> hasError;
    float airTemperature = 0.0;
    float airHumidity = 0.0;
    timer timeOfDay;
    int waterTemp = 0;
    MineralsPercentage mineralsPercentage;
    float soilHumidity = 0;
    float pH = 0;
};