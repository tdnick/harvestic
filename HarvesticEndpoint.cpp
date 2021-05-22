#include "HarvesticEndpoint.hpp"
#include "ParserJson.hpp"
using namespace std;
using namespace Pistache;

// General advice: pay attention to the namespaces that you use in various contexts. Could prevent headaches.

HarvesticEndpoint::HarvesticEndpoint(Address addr)
    : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
    {}

void HarvesticEndpoint::init(size_t thr){
    auto opts = Http::Endpoint::options()
            .threads(static_cast<int>(thr));
        httpEndpoint->init(opts);
        setupRoutes();
}

void HarvesticEndpoint::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serveThreaded();
}

void HarvesticEndpoint::stop(){
    httpEndpoint->shutdown();
}

void HarvesticEndpoint::setupRoutes() {
    using namespace Rest;
    Routes::Get(router, "/map/:index/", Routes::bind(&HarvesticEndpoint::getHoseState, this));
    Routes::Put(router, "/map/:index/:boolValue", Routes::bind(&HarvesticEndpoint::setHoseState, this));
    Routes::Put(router, "/meteo/conditions/", Routes::bind(&HarvesticEndpoint::setMeteoConditions, this));
    Routes::Get(router, "/waterTemp/", Routes::bind(&HarvesticEndpoint::getWaterTemp, this));
    Routes::Put(router, "/waterTemp/:celsius", Routes::bind(&HarvesticEndpoint::setWaterTemp, this));
}

void HarvesticEndpoint::setMeteoConditions(const Rest::Request& request, Http::ResponseWriter response){
    ParserJson json;
    Json::Value root = json.parse(request.body());

    hvs.setAirTemperature(root["air_temperature"].asFloat());
    hvs.setAirHumidity(root["air_humidity"].asFloat());
    hvs.setTimeOfDay(root["time_of_day"].asString());
    response.send(Http::Code::Ok, "Meteo conditions set.");
}

///TODO:
void HarvesticEndpoint::getMeteoConditions(const Rest::Request& request, Http::ResponseWriter response){
    
}

void HarvesticEndpoint::getHoseState(const Rest::Request& request, Http::ResponseWriter response){
    auto index = request.param(":index").as<int>();
    
    Guard guard(HarvesticLock);
    if(index >= hvs.hosesCount()){
        response.send(Http::Code::Not_Found, "Hose " + to_string(index) + " was not found");
    }
    else{
        bool state = hvs.getHoseState(index);

        using namespace Http;
        response.headers()
                        .add<Header::Server>("pistache/0.1")
                        .add<Header::ContentType>(MIME(Text, Plain));
        std::string turnedOnStatement = (state) ? "turned on" : "turned off";
        response.send(Http::Code::Ok, "Hose " + to_string(index) + " is " + turnedOnStatement);
    }
}

void HarvesticEndpoint::setHoseState(const Rest::Request& request, Http::ResponseWriter response){
    auto index = request.param(":index").as<int>();
    auto value = request.param(":boolValue").as<std::string>();
    bool boolValue = value.compare("true") == 0;

    Guard guard(HarvesticLock);

    if(index >= hvs.hosesCount()){
        response.send(Http::Code::Not_Found, "Hose " + to_string(index) + " was not found");
    }
    else{ 
        hvs.setHoseState(index,boolValue);
        response.send(Http::Code::Ok, "Hose " + to_string(index) + " has been " + ((boolValue)?"turned on":"turned off"));
    }
}

void HarvesticEndpoint::getWaterTemp(const Rest::Request& request, Http::ResponseWriter response){
    (void)request;

    Guard guard(HarvesticLock);
    
    int celsius = hvs.getWaterTemp();
    
    using namespace Http;
    response.headers()
                    .add<Header::Server>("pistache/0.1")
                    .add<Header::ContentType>(MIME(Text, Plain));
    response.send(Http::Code::Ok, "Temperature is set to " + to_string(celsius));

}

void HarvesticEndpoint::setWaterTemp(const Rest::Request& request, Http::ResponseWriter response){
    auto celsius = request.param(":celsius").as<int>();

    Guard guard(HarvesticLock);

    if(celsius < 15){
        response.send(Http::Code::Not_Found, "Temperature is too low.");
    }
    else if(celsius > 30) { 
        response.send(Http::Code::Not_Found, "Temperature is too high.");
    }
    else {
        hvs.setWaterTemp(celsius);
        response.send(Http::Code::Ok, "Temperature was set to " + to_string(celsius));
    }
}