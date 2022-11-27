#include <yaml-cpp/yaml.h>
#include "yaml_configuration.h"
#include "../src/constants/configuration_paths.h"

YamlConfiguration::YamlConfiguration() {}

ServerConfigurationAttributes YamlConfiguration::ReadServerConfiguration() {
    YAML::Node config = YAML::LoadFile(DATA_PATH + ConfigurationPaths().SERVER_CONFIG);

}

ClientConfigurationAttributes YamlConfiguration::ReadClientConfiguration() {
    YAML::Node config = YAML::LoadFile(DATA_PATH + ConfigurationPaths().CLIENT_CONFIG);
    return {config["width"].as<int>(), config["height"].as<int>()};
}
