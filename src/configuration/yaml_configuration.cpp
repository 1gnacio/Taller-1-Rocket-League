#include <yaml-cpp/yaml.h>
#include "yaml_configuration.h"
#include "../src/constants/configuration_paths.h"

YamlConfiguration::YamlConfiguration() {}

ServerConfigurationAttributes YamlConfiguration::ReadServerConfiguration() {
    YAML::Node config = YAML::LoadFile(DATA_PATH + ConfigurationPaths().SERVER_CONFIG);
    return {config["car_width"].as<float>(), config["car_height"].as<float>(), config["car_density"].as<float>(),
            config["car_friction"].as<float>(), config["car_restitution"].as<float>(), config["ball_density"].as<float>(),
            config["ball_friction"].as<float>(), config["ball_restitution"].as<float>(), config["ball_radius"].as<float>(),
            config["gravity"].as<float>(), config["directional_force_module"].as<float>(), config["jump_impulse"].as<float>(),
            config["replay_time_in_sec"].as<int>(), config["responses_per_sec"].as<int>()};
}

ClientConfigurationAttributes YamlConfiguration::ReadClientConfiguration() {
    YAML::Node config = YAML::LoadFile(DATA_PATH + ConfigurationPaths().CLIENT_CONFIG);
    return {config["width"].as<int>(), config["height"].as<int>()};
}
