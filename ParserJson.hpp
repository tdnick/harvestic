#include <string>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

class ParserJson {
    public:
        ParserJson();
        Json::Value parse(std::string);
    private:
        Json::Value value;
        Json::Reader reader;
};