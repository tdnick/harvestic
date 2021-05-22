#include "Harvestic.hpp"

Harvestic::Harvestic(){ }

int Harvestic::set(std::string name, std::string value){
    if(name == "defrost"){
        defrost.name = name;
        if(value == "true"){
            defrost.value = true;
            return 1;
        }
        if(value == "false"){
            defrost.value = false;
            return 1;
        }
    }
    return 0;
}

std::string Harvestic::get(std::string name){
    if (name == "defrost"){
        return std::to_string(defrost.value);
    }
    else{
        return "";
    }
}