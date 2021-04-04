#include <iostream>
#include <thread>

#include <sys/time.h>
#include "socket.h"

using namespace std;
using namespace stdsock;

void worker(StreamSocket* client) {
    std::cout << "Got a client!" << std::endl;

    std::cout << client->getIP() << ":" << client->getPort() << std::endl;

    char* dateString; // Chaine de caractere contenant la date
    struct timeval time_value;
    gettimeofday(&time_value, NULL);
    dateString = ctime(&(time_value.tv_sec));

    client->send(dateString,strlen(dateString),0);
    cout << "Server: \t"<< dateString << endl;

    sleep(5);
    string veryLongString="dskhgjkdshgsdlgsdhjghsdglshkgsdlhgsdhjkgsdlgdhhdshjgsdhjdsssssshghjdgjdhgjdghdjghdjghjdghdjghdjghdjghjdhgjdghdjghdjghdjhgjdhgjdghjhdjghdjhgjdghdjghdjghdjghdjgdhjgdhgjdhgjdhgdjghjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";
    client->send(veryLongString);
    cout << "Server: \t"<< veryLongString << endl;

//    while (true) {
//        std::string msg;
//        if (client->read(msg) <= 0) {
//            break;
//        }

//        std::cout << msg;
//    }

    delete client;
    std::cout << "Client disconnected" << std::endl;
}


int main()
{
    ConnectionPoint *server=new ConnectionPoint(3490);

    int err= server->init();
    std::cout << server->getIP() << ":" << server->getPort() << std::endl;
    if (err != 0) {
        std::cout << strerror(err) << std::endl;
        exit(err);
    }

    while (true) {
        StreamSocket* client = server->accept();

        if (!client->valid()) {
            delete client;
            continue;
        }

        std::thread (worker, client).detach();
    }



    delete server;
    return 0;
}
