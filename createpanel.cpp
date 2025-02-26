#include "createpanel.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <cassert>
#include <map>

using std::map;
using std::cout;
using std::endl;
using std::setw;

int indent(int x) {
    return x*4;
}

int main(){
    // load file
    vector<std::pair<string, Furniture>> obj_list;
    YAML::Node config = YAML::LoadFile("./yaml/furniture.yaml");
    YAML::Node furniture = config["furniture"];

    for(YAML::const_iterator obj_it=furniture.begin();obj_it!=furniture.end();++obj_it){
        string obj_name = obj_it->first.as<string>();
        Furniture obj_info = obj_it->second.as<Furniture>();
        obj_list.push_back({obj_name, obj_info});
    }

    // write file
    std::ofstream fout("config.yaml");
    fout << std::fixed << std::setprecision(1); // round up to 1 digit after decimal point
    fout << "furniture:" << endl;
    for (const auto& obj : obj_list) {
        int lv=1;
        string name = obj.first;
        Furniture info = obj.second;
        fout << string(indent(lv), ' ') << name << ":" << endl;
        lv=2;
        fout << string(indent(lv), ' ') << "frame: " << info.frame << endl;
        fout << string(indent(lv), ' ') << "belong: " << info.belong << endl;

        fout << string(indent(lv), ' ') << "plane: [" << endl;
        lv=3;
        for (const auto& point : info.plane) {
            fout << string(indent(lv), ' ') << "[" << point[0] << ", " << point[1] << "]," << endl;
        }
        lv=2;
        fout << string(indent(lv), ' ') << "]" << endl;

        fout << string(indent(lv), ' ') << "access: [" << endl;
        lv=3;
        for (const auto& set : info.access) {
            fout << string(indent(lv), ' ') << "[";
            for (const auto& point : set) {
                fout << "[" << point[0] << ", " << point[1] << "], ";
            }
            fout << "]," << endl;
        }
        fout << string(indent(lv), ' ') <<  "]" << endl;
        fout << endl;
    }

    return 0;
}