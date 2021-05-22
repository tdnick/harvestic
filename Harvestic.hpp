#include <string>
#include <vector>

// Defining the class of the Harvestic. It should model the entire configuration of the Harvestic
class Harvestic {
private:
    std::vector<bool> stateOfHose;
    int waterTemp;
public:
    explicit Harvestic();
    void setHoseState(int index, bool value); // get
    bool getHoseState(int index); // set
    int hosesCount();
    void setWaterTemp(int value); // get
    int getWaterTemp(); // set
};