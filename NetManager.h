#ifndef NETMANAGER_H_
#define NETMANAGER_H_

#include <SDL/SDL_net.h>

class NetManager
{
public:
    NetManager();
    ~NetManager();
    void init();

    void startServer();
    void stopServer();
    bool acceptClient();

    void connectToServer(char* host);
    
private:
    TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
    IPaddress ip, *remoteIP;
    int quit, quit2;
    char buffer[512];

    bool initialized;
};


#endif /* NETMANAGER_H_ */
