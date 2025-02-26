#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

int main() {
    // Create a YAML node and write data
    YAML::Node config;
    config["name"] = "John Doe";
    config["age"] = 25;

    // Save to a file
    std::ofstream fout("config.yaml");
    fout << config;
    fout.close();

    // Read from the YAML file
    YAML::Node loaded = YAML::LoadFile("config.yaml");
    std::cout << "Name: " << loaded["name"].as<std::string>() << std::endl;
    std::cout << "Age: " << loaded["age"].as<int>() << std::endl;

    return 0;
}
