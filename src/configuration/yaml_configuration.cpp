#include <yaml-cpp/yaml.h>
#include "yaml_configuration.h"
#include "../src/constants/configuration_paths.h"

YamlConfiguration::YamlConfiguration() {}

ServerConfigurationAttributes YamlConfiguration::ReadServerConfiguration() {
    YAML::Node config = YAML::LoadFile(DATA_PATH + ConfigurationPaths().SERVER_CONFIG);
    return {config["carWidth"].as<float>(), config["carHeight"].as<float>(), config["carDensity"].as<float>(),
            config["carFriction"].as<float>(), config["carRestitution"].as<float>(), config["ballDensity"].as<float>(),
            config["ballFriction"].as<float>(), config["ballRestitution"].as<float>(), config["ballRadious"].as<float>(),
            config["mapGravity"].as<float>(), config["movementForceModule"].as<float>(), config["jumpImpulse"].as<float>(),
            config["replayTimeInSec"].as<int>(), config["responsesPerSec"].as<int>()};
}

ClientConfigurationAttributes YamlConfiguration::ReadClientConfiguration() {
    YAML::Node config = YAML::LoadFile(DATA_PATH + ConfigurationPaths().CLIENT_CONFIG);
    return {config["width"].as<int>(), config["height"].as<int>()};
}
