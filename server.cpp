#include <iostream>
#include <thread>

#include <sys/time.h>
#include "socket.h"
#include "table.h"
#include <vector>
using namespace std;
using namespace stdsock;

int manchGagneOrdi(int client , int client2)
{

    int manche = 0 ; 

    if(client >= 0 && client <= 7 && client2 >= 0 && client2 <= 7)
    {

        if( (client != 6 && client2 != 6) || (client == 6 && client2 == 6) )
        {
            if(table[0][client][client2] == 2)
            {
                manche++;
            }
        }

        else if(client == 6 && client2 != 6)
        {
            if(table[1][client][client2] == 2)
            {
                manche++;
            }
        }
        
        else if(client != 6 && client2 == 6)
        {
            if(table[2][client][client2] == 2)
            {
                manche++;
            }
        }
            
    }

    return manche ;

}

int searchinVector(vector<int>v,int value)
{
    for(unsigned int i = 0 ; i < v.size() ;++i)
    {
        
        if(v[i] == value)
        {
            return v[i];
        }


    }

    return -1 ;

}

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
  
    string Hello = "HELO";
    string welcome = "WELCOME"; 
    string menuStart = "TAP MENU TO SEE MENU";
    string cardStart = "TAP START TO START THE GAME";
    string card = "CARD" ;
    string quit = "QUIT";
    string menu = "MENU";
    string start = "START";
    string help = "HELP";
    string clear = "CLEAR"; 


    client->send(Hello);
    client->send(welcome);
    client->send(menuStart);
    client->send(cardStart);
    client->send(card);
    client->send(quit);
    client->send(menu);
    client->send(start);
    client->send(help);
    client->send(clear);


    string msg ; 
    
    int nb=client->read(msg);



    if(nb < 0){
            printf("[-]Error in receiving data.\n");
    }else{
            cout << "Server: \t"<< Hello << " " << msg <<  endl;
    }


    string number,carte ; 
    


    int mancheOrdi = 0 ; 
    vector<int> result ;
    while(mancheOrdi <= 3){

        cout << "CHOOSE CARD BETWEEN 0...8 : "; 
        cin >> carte ; 
        int x = stoi(carte);

        if(x != searchinVector(result,x)){

            int num =client->read(number);
            char dernierElement = number.back();

            if(num < 0){
                    printf("[-]Error in receiving data.\n");
            }else{
                    cout << "Client: \t"<< dernierElement <<  endl;
            }
            
            client->send(carte);

            result.push_back(x) ; 
            int y = dernierElement - '0';

            if(result[result.size() -1] == 6 )
            {
                mancheOrdi++;
            }
            mancheOrdi += manchGagneOrdi(y,x);

            cout << "MancheGagne : " << mancheOrdi << endl ; 

            for(unsigned int i = 0 ;i < result.size() ; i++ )
            {
                cout << result[i] << ' '  ;
            }
            
            cout << endl ;
        }
    }


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