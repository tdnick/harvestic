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
    mineralsPercentage.N = mp.N;
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

    if (soilHumidity < 20){
        s = "URGENT! Water the plants for 60 minutes!";
    }
    else if (soilHumidity >= 20 && soilHumidity <= 60){
        if ((timeOfDay.hours >= 6 && timeOfDay.hours <= 10)||(timeOfDay.hours >= 18 && timeOfDay.hours <= 21)){
            if (airTemperature <= 25){
                if (airHumidity < 60){
                    s = "Water the plants for 45 minutes!";
                }
                else if (airHumidity >= 60 && airHumidity <= 80){
                    s = "Water the plants for 30 minutes!";
                }
                else {
                    s = "Water the plants for 15 minutes!";
                }
            }
            else {
                s = "The plants can't be watered. Air temperature too high!";
            }
        }
        else {
            s = "The plants can't be watered. Improper moment of the day!";
        }
    }
    else {
        s = "The plants don't need to be watered!";
    }
    return s;
}

std::vector<std::string> Harvestic::getSoilRecommendations(){
    std::vector<std::string> s;

    if (pH < 5.5){
        s.push_back("The pH value is too low!");
    }
    else if (pH > 7.5) {
        s.push_back("The pH value is too high!");
    }

    if (mineralsPercentage.Ca < 2){
        s.push_back("The Ca concentration is too low! Concentration difference: " + std::to_string(2 - mineralsPercentage.Ca));
    }
    else if (mineralsPercentage.Ca > 3) {
        s.push_back("The Ca concentration is too high!");
    }

    if (mineralsPercentage.Mg < 0.6){
        s.push_back("The Mg concentration is too low! Concentration difference: " + std::to_string(0.6 - mineralsPercentage.Mg));
    }
    else if (mineralsPercentage.Mg > 1.5) {
        s.push_back("The Mg concentration is too high!");
    }

    if (mineralsPercentage.N < 3.5){
        s.push_back("The N concentration is too low! Concentration difference: " + std::to_string(3.5 - mineralsPercentage.N));
    }
    else if (mineralsPercentage.N > 5.5) {
        s.push_back("The N concentration is too high!");
    }

    if (mineralsPercentage.P < 0.3){
        s.push_back("The P concentration is too low! Concentration difference: " + std::to_string(0.3 - mineralsPercentage.P));
    }
    else if (mineralsPercentage.P > 0.7) {
        s.push_back("The P concentration is too high!");
    }

    if (mineralsPercentage.K < 3){
        s.push_back("The K concentration is too low! Concentration difference: " + std::to_string(3 - mineralsPercentage.K));
    }
    else if (mineralsPercentage.K > 4) {
        s.push_back("The K concentration is too high!");
    }

    if (mineralsPercentage.S < 0.3){
        s.push_back("The S concentration is too low! Concentration difference: " + std::to_string(0.3 - mineralsPercentage.S));
    }
    else if (mineralsPercentage.S > 1) {
        s.push_back("The S concentration is too high!");
    }

    return s;
}