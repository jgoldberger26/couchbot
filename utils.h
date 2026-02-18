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

int write_fast_mode(uint8_t handle, uint16_t bytes) {
    // Zero power down bits and cc bits
    bytes &= 0x0fff;
    // Duplicate the payload as per the datasheet
    uint32_t doubled_bytes = (bytes << 16) | bytes;
    // TODO actually handle errors
    return wiringPiI2CRawWrite(handle, &doubled_bytes, 4);
}

int write_percent_to_i2c(uint8_t handle, float percent) {
    uint16_t input_code = percent * 4096; // 12 bits
    return write_fast_mode(handle, input_code);
}