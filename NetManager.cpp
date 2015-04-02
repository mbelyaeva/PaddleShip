#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include "NetManager.h"

NetManager::NetManager(){
    serverRunning = false;
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
// Server fuctions
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

    serverRunning = true;
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
// Client fuctions
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

//------------------------------------------------------------
// Shared fuctions
//------------------------------------------------------------

bool NetManager::receiveMessage(char * buff){
    if (SDLNet_TCP_Recv(csd, buffer, NETMANAGER_BUFFER_SIZE) > 0){
        printf("Received message: %s\n", buffer);
        strncpy(buff, buffer, NETMANAGER_BUFFER_SIZE);
        return true;
    }
    return false;
}

void NetManager::sendMessage(char const * message){
    strncpy(buffer, message, NETMANAGER_BUFFER_SIZE);
    int len = strlen(buffer) + 1;
    if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len){
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    printf("Sent message: %s\n", buffer);
}