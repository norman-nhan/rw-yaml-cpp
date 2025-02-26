#include <yaml-cpp/yaml.h>
#include <string>
#include <vector>

using std::vector;
typedef vector<vector<double>> dlist_t; // list of double list
using std::string;

struct Furniture {
    string frame; // tf frame
    dlist_t plane; // position (only x and y)
    string belong; // area in which it is belong to
    vector<dlist_t> access; // face in which robot can approach
};

namespace YAML {

    // Convert dlist_t (std::vector<std::vector<double>>)
    template<>
    struct convert<dlist_t> {
        static Node encode(const dlist_t& rhs) {
            Node node;
            for (const auto& point : rhs) {
                Node subnode;
                for (double value : point) {
                    subnode.push_back(value);
                }
                node.push_back(subnode);
            }
            return node;
        }
    
        static bool decode(const Node& node, dlist_t& rhs) {
            if (!node.IsSequence()) return false;
            for (const auto& subnode : node) {
                vector<double> point;
                if (!subnode.IsSequence()) return false;
                for (const auto& value : subnode) {
                    point.push_back(value.as<double>());
                }
                rhs.push_back(point);
            }
            return true;
        }
    };
    
    // Convert Furniture struct
    template<>
    struct convert<Furniture> {
        static Node encode(const Furniture& rhs) {
            Node node;
            node["frame"] = rhs.frame;
            node["plane"] = rhs.plane;
            node["belong"] = rhs.belong;
            node["access"] = rhs.access;
            return node;
        }
    
        static bool decode(const Node& node, Furniture& rhs) {
            if (!node.IsMap()) return false;
    
            rhs.frame = node["frame"].as<std::string>();
            rhs.plane = node["plane"].as<dlist_t>();
            rhs.belong = node["belong"].as<std::string>();
    
            for (const auto& subnode : node["access"]) {
                rhs.access.push_back(subnode.as<dlist_t>());
            }
    
            return true;
        }
    };
    
} // namespace YAML    