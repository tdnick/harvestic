#include "Harvestic.hpp"

Harvestic::Harvestic() : stateOfHose(20, false), waterTemp(25){ }

void Harvestic::setHoseState(int index, bool value){
    stateOfHose[index] = value;
}

bool Harvestic::getHoseState(int index){
    return stateOfHose[index];
}

float Harvestic::getAirTemperature(){
    return airTemperature;
}

void Harvestic::setAirTemperature(float temp){
    airTemperature = temp;
}

float Harvestic::getAirHumidity(){
    return airHumidity;
}

void Harvestic::setAirHumidity(float hum){
    airHumidity = hum;
}

timer Harvestic::getTimeOfDay(){
    return timeOfDay;
}

void Harvestic::setTimeOfDay(timer t){
    timeOfDay = t;
}

void Harvestic::setTimeOfDay(std::string s){
    std::vector<std::string> tokenized;
    std::stringstream sstream(s);
    std::string a;
    char del = ':';
    while (std::getline(sstream, a, del))
       tokenized.push_back(a);

    timeOfDay.hours = std::stoi(tokenized[0]);
    timeOfDay.minutes = std::stoi(tokenized[1]);
    timeOfDay.seconds = std::stoi(tokenized[2]);
}

int Harvestic::hosesCount(){
    return stateOfHose.size();
}

void Harvestic::setWaterTemp(int value){
    waterTemp = value;
}

int Harvestic::getWaterTemp(){
    return waterTemp;
}

std::string Harvestic::getMeteoRecommendations(){
    std::string s = "";

    if((6 <= timeOfDay.hours && timeOfDay.hours <= 10)
     || (18 <= timeOfDay.hours && timeOfDay.hours <= 21)
     || (airHumidity < 60)
     || (airTemperature < 28)){
        s = "Plants should be watered!";
     }
    else{
        s = "Everything is ok! :)";
    }
    return s;
}