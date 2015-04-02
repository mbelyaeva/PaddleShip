#ifndef NETMANAGER_H_
#define NETMANAGER_H_

#include <SDL/SDL_net.h>

#define NETMANAGER_BUFFER_SIZE 512

class NetManager
{
public:
    NetManager();
    ~NetManager();
    void init();

    void startServer();
    void stopServer();
    bool acceptClient();
    void sendMessageToClient(void * message, int len);
    bool receiveMessageFromServer(void * buff);

    void connectToServer(char* host);
    void sendMessageToServer(void * message, int len);
    bool receiveMessageFromClient(void * buff);

    

    
    
private:
    TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
    IPaddress ip;
    //char buffer[NETMANAGER_BUFFER_SIZE];

    bool serverRunning;
};


#endif /* NETMANAGER_H_ */
