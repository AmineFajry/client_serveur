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
           cout << "valeur : 0 " << endl ; 
           cout << " cette manche est annulee est mise en attente" <<endl<<endl; 

           break;

        case 1 : 
            cout << "Princesse"<<endl; 
            cout << "valeur : 1 " <<endl ; 
            cout << "Si votre adversaire a joue son Prince, vous remportez la partie" <<endl<<endl;
            break;

        case 2 : 
            cout << "Espion"<<endl; 
            cout << "valeur : 2 " << endl ; 
            cout << " A la prochaine manche.Votre adversaire revele sa carte avant que vous chosissez la votre"<<endl<<endl;
            break;

        case 3 : 
            cout << "Assassin"<<endl;
            cout << "valeur : 3 " << endl ; 
            cout << "La valeur la plus faiible l'emporte" <<endl<<endl;
            break;

        case 4 : 
            cout << "Ambassadeur"<<endl; 
            cout << "valeur : 4 " << endl; 
            cout << "Si vous gagnez avec cette carte,cela compte pour 2 manches" <<endl<<endl;
            break;

        case 5 : 
            cout << "Magicien"<<endl; 
            cout <<"valeur : 5 " << endl ; 
            cout << "Annule la capacite speciale de la carte jouee par l'adversaire" <<endl<<endl;
            break;

        case 6 : 
            cout << "General"<< endl; 
            cout << "valeur : 6 " << endl ; 
            cout << "Votre carte de la prochaine manche voit sa valeur augmentee de +2"<<endl<<endl;
            break;

        case 7 : 
            cout << "Prince"<<endl;
            cout << "valeur : 7" <<endl; 
            cout << "Vous gagnez la manche,sauf contre le musicien et la pricesse" <<endl<<endl;
            break; 
        default:
            cout << "Oups ta carte pas trouvée" <<endl<<endl;
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

    string msg,helo,welcome,menuStart,cardStart,card,menu,quit,start,help,clear;


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
    cardStart = msg.substr(31,27);
    card = msg.substr(58,4);
    quit = msg.substr(62,4);
    menu = msg.substr(66,4);
    start = msg.substr(70,5);
    help = msg.substr(75,4);
    clear = msg.substr(79,5);




    if(nb < 0){
            printf("[-]Error in receiving data.\n");
    }else{
            cout << "Server: \t"<< helo<< " " << name <<  endl;
            cout << "Server: \t"<< menuStart<<  endl;
            cout << "Server: \t"<< cardStart<<  endl;
            cout << "Server: \t"<< clear<<  endl;

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

            cout <<endl<< card << " " << cardChoice << endl ; 

            cout << "You chose " << " :  " ; 

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
        }else if (protocole == clear)
        {
            system("clear");
        }
        

    }

    





    //delete sock


    return 0;
}
