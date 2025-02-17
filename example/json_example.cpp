#include <fstream>
#include <json.hpp>
#include <iostream>
using json = nlohmann::json;

// ...

int main()
{
    // std::ifstream f("example.json");
    std::string jsonString = "{ \"id\": \"string\", \"category\": 1, \"date\": \"2025-02-13\", \"start\": \"13:55\", \"end\": \"14:00\", \"duration\": 60, \"metrics\": [ { \"metric\": 0, \"value\": 0 } ] }";

    json data = json::parse(jsonString);
    std::cout << data << std::endl;

    // Using initializer lists
    json ex3 = {
        {"happy", true},
        {"pi", 3.141},
    };
    std::cout << ex3 << std::endl;
}