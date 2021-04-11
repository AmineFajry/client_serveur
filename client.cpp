#include <iostream>
#include <thread>

#include <sys/time.h>
#include "socket.h"

using namespace std;
using namespace stdsock;


void cardName(int number)
{
    switch(number)
    {
        case 0 : 
           cout << "Musicien"<<endl; 
           break;

        case 1 : 
            cout << "Princesse"<<endl; 
            break;

        case 2 : 
            cout << "Espion"<<endl; 
            break;

        case 3 : 
            cout << "Assassin"<<endl; 
            break;

        case 4 : 
            cout << "Ambassadeur"<<endl; 
            break;

        case 5 : 
            cout << "Magicien"<<endl; 
            break;

        case 6 : 
            cout << "General"<<endl; 
            break;

        case 7 : 
            cout << "Princesse"<<endl; 
            break; 
        default:
            cout << "Oups ta carte pas trouvée" << endl ;
            break;
            
    }
}

void menuSwitch(int input)
{

    switch (input)
    {
    case 1:
        cout << "See you later" <<endl ; 
        break;
    case 2 : 
        cout << " Braverats est un jeu ... " << endl ; 
        break;
    default:
        break;
    }



}

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
            cout << "Server: \t"<< menuStart<<  endl;
            cout << "Server: \t"<< cardStart<<  endl;
    }
    

    string protocole  ;
    int cardChoice ; 

    while(true)
    {
        cout << "YOUR TURN : "; 
        cin >> protocole ;

        if(protocole == start)
        {
            cout <<endl<< "Server: \t"<< welcome<<endl<<endl;

            cout << "CHOOSE YOUR CARD BETWEEN 0 ... 8" <<endl ; 
            cin >> cardChoice ; 

            cout << card << " " << cardChoice << endl ; 

            cout << "You chose musicien " << " :  " ; 

            cardName(cardChoice) ;


        }else if(protocole == menu)
        {
            cout<<endl<<" ----------------------- MENU -----------------------"<<endl<<endl;
            cout<<"1. HELP"<<endl;
            cout<<"2. Quitter"<<endl<<endl;

            int input ; 
            cin >> input ; 
            menuSwitch(input);
        }
        else if (protocole == quit)
        {
            exit(0);
        }
        

    }

    





    //delete sock


    return 0;
}
