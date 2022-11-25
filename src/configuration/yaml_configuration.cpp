#include "yaml_configuration.h"
#include "../src/constants/configuration_paths.h"

YamlConfiguration::YamlConfiguration() {}

ServerConfigurationAttributes YamlConfiguration::ReadServerConfiguration() {
    //TODO
    throw std::logic_error("Not implemented");
}

ClientConfigurationAttributes YamlConfiguration::ReadClientConfiguration() {
    YAML::Node config = YAML::LoadFile(DATA_PATH + ConfigurationPaths().CLIENT_CONFIG);
    return {config["width"].as<int>(), config["height"].as<int>()};
}
