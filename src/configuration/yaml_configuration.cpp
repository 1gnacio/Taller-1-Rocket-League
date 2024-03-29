#include <yaml-cpp/yaml.h>
#include "yaml_configuration.h"
#include "../src/constants/configuration_paths.h"

YamlConfiguration::YamlConfiguration() {}

ServerConfigurationAttributes YamlConfiguration::ReadServerConfiguration() {
    YAML::Node config = YAML::LoadFile(ConfigurationPaths().SERVER_CONFIG_INSTALLED);

    return {config["car_width"].as<float>(), config["car_height"].as<float>(), config["car_density"].as<float>(),
            config["car_friction"].as<float>(), config["car_restitution"].as<float>(), config["ball_density"].as<float>(),
            config["ball_friction"].as<float>(), config["ball_restitution"].as<float>(), config["ball_radius"].as<float>(),
            config["gravity"].as<float>(), config["directional_force_module"].as<float>(), config["jump_impulse"].as<float>(),
            config["replay_time_in_sec"].as<int>(), config["responses_per_sec"].as<int>(), config["game_time"].as<int>(),
            config["force_flip_shot"].as<float>(), config["force_red_shot"].as<float>(), config["force_purple_shot"].as<float>(),
            config["force_gold_shot"].as<float>(), config["turbo_force"].as<float>(), config["torque_force"].as<float>() };
}

ClientConfigurationAttributes YamlConfiguration::ReadClientConfiguration() {
    YAML::Node configServer = YAML::LoadFile(ConfigurationPaths().SERVER_CONFIG_INSTALLED);
    YAML::Node configClient = YAML::LoadFile(ConfigurationPaths().CLIENT_CONFIG_INSTALLED);
    return {configClient["width"].as<int>(), configClient["height"].as<int>(),
            configServer["car_width"].as<float>(), configServer["car_height"].as<float>(),
            configServer["ball_radius"].as<float>(), configServer["game_time"].as<int>(),
            configClient["sound_on"].as<bool>(), configClient["update_time"].as<unsigned int>() };
}
