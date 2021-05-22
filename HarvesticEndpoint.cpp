#include "HarvesticEndpoint.hpp"

using namespace std;
using namespace Pistache;

// General advice: pay atetntion to the namespaces that you use in various contexts. Could prevent headaches.

// This is just a helper function to preety-print the Cookies that one of the enpoints shall receive.
void printCookies(const Http::Request& req) {
    auto cookies = req.cookies();
    std::cout << "Cookies: [" << std::endl;
    const std::string indent(4, ' ');
    for (const auto& c: cookies) {
        std::cout << indent << c.name << " = " << c.value << std::endl;
    }
    std::cout << "]" << std::endl;
}

void handleReady(const Rest::Request&, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "1");
}

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
    Routes::Get(router, "/ready", Routes::bind(&handleReady));
    Routes::Get(router, "/auth", Routes::bind(&HarvesticEndpoint::doAuth, this));
    Routes::Post(router, "/settings/:settingName/:value", Routes::bind(&HarvesticEndpoint::setSetting, this));
    Routes::Get(router, "/settings/:settingName/", Routes::bind(&HarvesticEndpoint::getSetting, this));
}

void HarvesticEndpoint::doAuth(const Rest::Request& request, Http::ResponseWriter response) {
    printCookies(request);
    // In the response object, it adds a cookie regarding the communications language.
    response.cookies()
        .add(Http::Cookie("lang", "en-US"));
    response.send(Http::Code::Ok);
}

// Endpoint to configure one of the Harvestic's settings.
void HarvesticEndpoint::setSetting(const Rest::Request& request, Http::ResponseWriter response){
    // You don't know what the parameter content that you receive is, but you should
    // try to cast it to some data structure. Here, I cast the settingName to string.
    auto settingName = request.param(":settingName").as<std::string>();

    // This is a guard that prevents editing the same value by two concurent threads. 
    Guard guard(HarvesticLock);

    string val = "";
    if (request.hasParam(":value")) {
        auto value = request.param(":value");
        val = value.as<string>();
    }

    // Setting the Harvestic's setting to value
    int setResponse = mwv.set(settingName, val);

    // Sending some confirmation or error response.
    if (setResponse == 1) {
        response.send(Http::Code::Ok, settingName + " was set to " + val);
    }
    else {
        response.send(Http::Code::Not_Found, settingName + " was not found and or '" + val + "' was not a valid value ");
    }

}

// Setting to get the settings value of one of the configurations of the Harvestic
void HarvesticEndpoint::getSetting(const Rest::Request& request, Http::ResponseWriter response){
    auto settingName = request.param(":settingName").as<std::string>();

    Guard guard(HarvesticLock);

    string valueSetting = mwv.get(settingName);

    if (valueSetting != "") {

        // In this response I also add a couple of headers, describing the server that sent this response, and the way the content is formatted.
        using namespace Http;
        response.headers()
                    .add<Header::Server>("pistache/0.1")
                    .add<Header::ContentType>(MIME(Text, Plain));

        response.send(Http::Code::Ok, settingName + " is " + valueSetting);
    }
    else {
        response.send(Http::Code::Not_Found, settingName + " was not found");
    }
}