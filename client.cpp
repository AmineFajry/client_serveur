#include <iostream>
#include <thread>

#include <sys/time.h>
#include "socket.h"

using namespace std;
using namespace stdsock;

int main(int argc, char* argv[])
{
    int port;

    if(argc!=3)
    {
        printf("usage: %s server_address port\n", argv[0]);
        return 0;
    }

    if(sscanf(argv[2], "%d", &port)!=1)
    {
        printf("usage: %s server_address port\n", argv[0]);
        return 1;
    }

    
    StreamSocket *sock=new StreamSocket(argv[1],port);

    int err= sock->connect();
    if (err!=0) {
        delete sock;
        perror("[-]Error in connection: ");
        return(err);
    }
    cout << "[+]Connected to Server " << sock->getIP() <<":" << sock->getPort() << endl;

    string msg,helo,welcome,menuStart,cardStart,card,menu,quit,start,help;


    int nb = sock->read(msg);


    string name ; 
    cout << "Saisir votre nom : " ;
    cin >> name; 

    sock->send(name);


    if(nb < 0){
            printf("[-]Error in receiving data.\n");
    }else{
            cout << "Server: \t"<< msg << endl;
    }
    msg.clear();

    nb=sock->read(msg);

    helo = msg.substr(0,4);
    welcome = msg.substr(4,7);
    menuStart = msg.substr(11,20);
    cardStart = msg.substr(31,21);
    card = msg.substr(52,4);
    quit = msg.substr(56,4);
    menu = msg.substr(60,4);
    start = msg.substr(64,5);
    help = msg.substr(69,4);




    if(nb < 0){
            printf("[-]Error in receiving data.\n");
    }else{
            cout << "Server: \t"<< helo<< " " << name <<  endl;
            cout << "Server: \t"<< welcome<<  endl;
            cout << "Server: \t"<< menuStart<<  endl;
            cout << "Server: \t"<< cardStart<<  endl;
            cout << "Server: \t"<< start <<  endl;
            cout << "Server: \t"<< help <<  endl;
    }
    
    
    /*string protocole ; 
    cout << "YOUR TURN : "; 
    cin >> protocole ;*/





  




    //delete sock


    return 0;
}
