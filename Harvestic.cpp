#include "Harvestic.hpp"

Harvestic::Harvestic() : stateOfHose(20, false), hasError(8), waterTemp(25){
    std::vector<std::string> aux = {
        "No issues.",
        "Water pressure too low.",
        "Water pressure too high.",
        "Weather sensor malfunction.",
        "Soil sensor malfunction.",
        "Pump malfunction.",
        "Power issues.",
        "Other issues."
    };

    for(int i = 0; i <= 7; i++){
        hasError[i].fail = false;
        hasError[i].name = aux[i];
    }
}

void Harvestic::setHoseState(int index, bool value){
    stateOfHose[index] = value;
}

bool Harvestic::getHoseState(int index){
    return stateOfHose[index];
}

void Harvestic::setError(int index, bool value){
    hasError[index].fail = value;
}

std::vector<err> Harvestic::getErrors(){
    return hasError;
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

MineralsPercentage Harvestic::getMineralsPercentage(){
    return mineralsPercentage;
}

void Harvestic::setMineralsPercentage(MineralsPercentage mp){
    mineralsPercentage.Ca = mp.Ca;
    mineralsPercentage.K = mp.K;
    mineralsPercentage.Mg = mp.Mg;
    mineralsPercentage.N = mp.P;
    mineralsPercentage.P = mp.P;
    mineralsPercentage.S = mp.S;
}

float Harvestic::getSoilHumidity(){
    return soilHumidity;
}

void Harvestic::setSoilHumidity(float s){
    soilHumidity = s;
}

float Harvestic::getPh(){
    return pH;
}

void Harvestic::setPh(float p){
    pH = p;
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

std::string Harvestic::getSoilRecommendations(){
    std::string s="";
    return s;
}