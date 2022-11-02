#ifndef SOCKETCLOSED_H
#define SOCKETCLOSED_H

#include "../sockets/liberror.h"

class SocketClosedException : public std::exception {
private:
    LibError error;
public:
    explicit SocketClosedException(const LibError& error) : error(error) {}

    const char * what() {
        return this->error.what();
    }
};



#endif // SOCKETCLOSED_H
