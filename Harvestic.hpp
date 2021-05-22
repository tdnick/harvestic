#include <string>


// Defining the class of the Harvestic. It should model the entire configuration of the Harvestic
class Harvestic {
public:
    explicit Harvestic();

    // Setting the value for one of the settings. Hardcoded for the defrosting option
    int set(std::string name, std::string value);

    // Getter
    std::string get(std::string name);

private:
    // Defining and instantiating settings.
    struct boolSetting{
        std::string name;
        bool value;
    }defrost;
};