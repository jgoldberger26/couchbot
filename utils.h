#include <map>
#include <string>
#include <yaml-cpp/yaml.h>

enum Speed {
    LOW_SPEED,
    MEDIUM_SPEED,
    HIGH_SPEED
};


// Config for constructing a motor controller
struct Motor_Config {
    std::map<std::string, int> handles;
    std::map<std::string, int> pins;
};

namespace YAML {
template<>
struct convert<Motor_Config> {
  static Node encode(const Motor_Config& m) {
    Node node;
    node.push_back(m.handles);
    return node;
  }

  static bool decode(const Node& node, Motor_Config& m) {
    if(!node.IsMap()) {
      return false;
    }

    if (node["Handles"]) m.handles = node["Handles"].as<std::map<std::string, int>>();
    if (node["Pins"]) m.pins =  node["Pins"].as<std::map<std::string, int>>();

    return true;
  }
};

}

