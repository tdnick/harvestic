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

// Defining the class of the Harvestic. It should model the entire configuration of the Harvestic
class Harvestic {
public:
    explicit Harvestic();
    bool getHoseState(int index); // get
    void setHoseState(int index, bool value); //set
    std::vector<err> getErrors(); // get
    void setError(int index, bool value); //set
    float getAirTemperature();
    void setAirTemperature(float temp);
    float getAirHumidity();
    void setAirHumidity(float hum);
    timer getTimeOfDay();
    void setTimeOfDay(timer t);
    void setTimeOfDay(std::string s);
    int hosesCount();
    void setWaterTemp(int value); // get
    int getWaterTemp(); // set
    std::string getMeteoRecommendations();
private:
    std::vector<bool> stateOfHose;
    std::vector<err> hasError;
    float airTemperature = 0.0;
    float airHumidity = 0.0;
    timer timeOfDay;
    int waterTemp;
    
};