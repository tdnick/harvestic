#include <iostream>
#include <fstream>
#include "ParserJson.hpp"

ParserJson::ParserJson(){}

Json::Value ParserJson::parse(std::string jsonString){
    if(!reader.parse(jsonString.c_str(), value)){
        std::cout<<"Parse failed!\n"<< reader.getFormattedErrorMessages();
    }
    return value;
}