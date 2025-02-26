#include <iostream>
#include <yaml-cpp/yaml.h>
#include <cassert>

int main() {
    YAML::Node node = YAML::Load("[1, 2, 3]");

    assert(node.Type() == YAML::NodeType::Sequence);  // Ensure it's a sequence
    assert(node.IsSequence());  // Shortcut, should also be true

    std::cout << "Assertions passed! YAML is a sequence." << std::endl;
    return 0;
}
