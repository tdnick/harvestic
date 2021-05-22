#include <string>
#include <vector>

// Defining the class of the Harvestic. It should model the entire configuration of the Harvestic
class Harvestic {
public:
    explicit Harvestic();
    void setHoseState(int index, bool value); // get
    bool getHoseState(int index); // set
    int hosesCount();
private:
    std::vector<bool> stateOfHose;
};