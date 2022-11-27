#ifndef YAML_CONFIGURATION_H
#define YAML_CONFIGURATION_H

#include "../src/configuration/attributes/server_configuration_attributes.h"
#include "../src/configuration/attributes/client_configuration_attributes.h"

class YamlConfiguration {
public:
    YamlConfiguration();
    ServerConfigurationAttributes ReadServerConfiguration();
    ClientConfigurationAttributes ReadClientConfiguration();
};


#endif // YAML_CONFIGURATION_H
