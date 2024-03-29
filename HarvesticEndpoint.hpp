#include <algorithm>
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <signal.h>
#include "Harvestic.hpp"



class HarvesticEndpoint {
public:
    explicit HarvesticEndpoint(Pistache::Address addr);
    void init(size_t thr = 2); // Initialization of the server. Additional options can be provided here
    void start(); // Server is started threaded.  
    void stop(); // When signaled server shuts down
private:
    void setupRoutes();
    void getHoseState(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void setHoseState(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void getHosesCount(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void setHosesCount(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void getAllHoses(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void setAllHoses(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void getErrors(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void setError(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void getMeteoConditions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void setMeteoConditions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void getWaterTemp(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void setWaterTemp(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void getSoilConditions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void setSoilConditions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    using Lock = std::mutex; // Create the lock which prevents concurrent editing of the same variable
    using Guard = std::lock_guard<Lock>;
    Lock HarvesticLock;
    Harvestic hvs; // Instance of the Harvestic model
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint; // Defining the httpEndpoint and a router.
    Pistache::Rest::Router router;
};