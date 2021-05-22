#include "Harvestic.hpp"

Harvestic::Harvestic() : stateOfHose(20,false){ }

void Harvestic::setHoseState(int index, bool value){
    stateOfHose[index] = value;
}

bool Harvestic::getHoseState(int index){
    return stateOfHose[index];
}

int Harvestic::hosesCount(){
    return stateOfHose.size();
}