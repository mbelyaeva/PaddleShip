#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NetManager.h"

NetManager::NetManager(){
    initialized = true;
}

NetManager::~NetManager(){
    SDLNet_Quit();
}

void NetManager::init(){
    if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

//------------------------------------------------------------

void NetManager::startServer(){
    if (SDLNet_ResolveHost(&ip, NULL, 49152) < 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
    {
        fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
}

void NetManager::stopServer(){
    SDLNet_TCP_Close(sd);
}

bool NetManager::acceptClient(){
    csd = SDLNet_TCP_Accept(sd);
    if (csd){
        printf("TCP client accepted\n");
        return true;
    }
    return false;
}

//------------------------------------------------------------

void NetManager::connectToServer(char* host){
    /* Resolve the host we are connecting to */
    if (SDLNet_ResolveHost(&ip, host, 49152) < 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
    }

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
    {
	fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    	exit(EXIT_FAILURE);
    }
}
