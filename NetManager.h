#ifndef NETMANAGER_H_
#define NETMANAGER_H_

#include <SDL/SDL_net.h>

#define NETMANAGER_BUFFER_SIZE 7084

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
    bool receiveMessageFromClient(void * buff);
    bool messageWaitingFromClient();

    void connectToServer(char* host);
    void sendMessageToServer(void * message, int len);
    bool receiveMessageFromServer(void * buff);

    

    

    
    
private:
    TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
    SDLNet_SocketSet set; //a set of sockets. Used here only to check existing packets
    IPaddress ip;

    bool serverRunning;
};


#endif /* NETMANAGER_H_ */
