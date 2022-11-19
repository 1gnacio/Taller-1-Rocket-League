#ifndef CONNECTED_CLIENTS_H
#define CONNECTED_CLIENTS_H

#include <vector>

class ConnectedClients {
private:
    std::vector<int> clients;
public:
    ConnectedClients();
    explicit ConnectedClients(std::vector<unsigned char> serialized);
    void addClient(int id);
    std::vector<unsigned char> serialize();
    static int size(int count) { return count * sizeof(int); };
};


#endif // CONNECTED_CLIENTS_H
