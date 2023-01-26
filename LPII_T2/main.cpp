/*
 * main.cpp
 *
 *  Created on: 16 de jun de 2016
 *      Author: johannes
 */

#include "LogMonitor.h"
#include "Request.h"

using namespace std;

#define PORT 22222


void ClientProcess(int client, string ip, LogMonitor* Log);


int main(int argc, char *argv[])
{
    LogMonitor *Log = new LogMonitor("log.txt");

	int socketfd;
    struct sockaddr_in serv_addr, cli_addr;
    cout << "[SERVER] Using port " << PORT << ".\n";

    // Creating server socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0){
        cerr << "[ERROR] Could not create server socket.\n";
        Log->writeLog("[ERROR] Could not create server socket: Server was not initialized!\n");
        exit(1);
    }

    // Setting up TCP Socket
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    //
    if(bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        cerr << "[ERROR] Could not configure bind.\n";
        Log->writeLog("[ERROR] Could not configure bind: Server was not initialized!\n");
        exit(1);
    }

    //Log->writeLog("Servidor iniciado com sucesso! Porta: " + PORT + "\n");

    listen(socketfd, 0);

    for(;;){
        cout << "[SERVER] Waiting for clients.\n";
        socklen_t clilen = sizeof(cli_addr);
        int client = accept(socketfd, (struct sockaddr *) &cli_addr, &clilen);

        char str[1048];
        inet_ntop(AF_INET, &(cli_addr.sin_addr), str, INET_ADDRSTRLEN);
        string ip = str;

        Log->writeLog("New client connected. [IP: " + ip + "]\n");
        cout << "[SERVER] Client " << ip << " connected!\n";

        thread clientThread(ClientProcess, client, ip, Log);
        clientThread.detach();
    }

    delete Log;
    return 0;
}


void ClientProcess(int client, string ip, LogMonitor* Log)
{
    char rBuffer[2048];
    recv(client, rBuffer, sizeof(rBuffer),0);
    string req = rBuffer;
    Request myReq(req);

    printf("[CLIENT %s] Requesting:\n%s\n", ip.c_str(), req.c_str());

    Log->writeLog("[CLIENT " + ip + "] Requesting:\n" + req + "\n");

    string answer = myReq.GetAnswer();

    const char *output = answer.c_str();
    send(client, output, answer.size(), 0);

    printf("[CLIENT %s] Received answer:\n%s\n", ip.c_str(), answer.c_str());
    Log->writeLog("Client " + ip + " received:\n" + answer + "\n");

    printf("[CLIENT %s] Disconnecting.\n", ip.c_str());
    Log->writeLog("Client " + ip + " disconnected.\n");

    close(client);
}



