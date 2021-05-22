#include <string>
#include <vector>

// Defining the class of the Harvestic. It should model the entire configuration of the Harvestic
class Harvestic {
public:
    explicit Harvestic();
    std::string get(std::string name); //get
    int set(std::string name, std::string value); //set
    void setHoseState(int index, bool value); // get
    bool getHoseState(int index); // set
    int hosesCount();
private:
    struct boolSetting{
        std::string name;
        bool value;
    }defrost;
    
    std::vector<bool> stateOfHose;

};