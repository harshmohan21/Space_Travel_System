#include <iostream>
#include <vector>
#include<cmath>
#include <string.h>
using namespace std;
int count=0;

class Planet;

class Traveller;
class Astronaut;
class Commander;
class Ticket;
class Passenger;
float TicketPrice(int a , int b);
vector <Planet> planets;
vector <Passenger> passengers;
vector <Astronaut> astronauts;
vector <Commander> commands;
vector <Ticket> ticket;
int searchTicket(int ID);
class coordinates{
    public:
        int x,y,z;

};

class Planet{
    public: 
        float Position_X , Position_Y , Position_Z;
        string name;
        coordinates getCoordinates(){
            coordinates c;
            c.x = Position_X;
            c.y = Position_Y;
            c.z = Position_Z;
            return c;
        }    
        Planet(float x,float y,float z , string Name)
        {
            name = Name;
            Position_X = x;
            Position_Y = y;
            Position_Z = z;
            planets.push_back(*this);
        }   
};


class Traveller {
    private:
        int traveller_id;
    public:
        int ID;
        string Name;
        bool travelling_status=0;
        //traveller_id = ID;
        int get_traveller_id()
        {
            return traveller_id;
        }

};
class Astronaut:public Traveller{
    private: 
        int Experience;
    public:
        Astronaut(int ex , string name , int id ){
            Name = name;
            ID= id;
            Experience = ex;
            astronauts.push_back(*this);
        }
        int get_experience()
        {
            return Experience;
        }

};
class Commander:public Traveller{
    private:
        int Authority;
    public:
        int Experience;
        int LicenseID;
        Commander(int id , string name , int experience , int license)
        {
            ID = id;
            Name = name;
            Experience= experience;
            LicenseID = license;
            commands.push_back(*this);
        }
        
};
class Passenger:public Traveller{
    public: 
        int validity ;
        // Passenger(int id , string name , int Validity ){
        //     ID = id;
        //     Name = name;
        //     validity = Validity;
        //     passengers.push_back(*this);

        // }
};
int search_ID(int id){
    int s = passengers.size();
    for (int i = 0 ; i < s ; i++)
    {
        if(passengers[i].ID == id)
        return i;
    }
    return -1;
}
int search_Name(string name){
    int s = passengers.size();
    for (int i = 0 ; i < s ; i++)
    {
        if(passengers[i].Name == name)
        return i;
    }
    return -1;
}
int searchAstronaut(){
    int s = astronauts.size();
    for(int i = 0 ; i < s ; i++)
    {
        if(astronauts[i].travelling_status == 0)
            return i;
    }
    return -1;
}
int searchCommander(){
    int s = commands.size();
    for(int i = 0 ; i < s ; i++)
    {
        if(commands[i].travelling_status == 0)
            return i;
    }
    return -1;
}
void addPassenger() {
 Passenger p;
    cout<<"Fill form to create passenger"<<endl; 
    cout<<"Enter name:"<<endl;
    //cin>>p.Name; 
    cin.ignore();
    getline(cin,p.Name);       
    cout<<"Enter ID:"<<endl;
    id:
        cin>>p.ID;
        if(p.ID < 99999)
        {
            cout<<"Enter a valid 6 digit ID:"<<endl;
            goto id;
        }
        p.validity = 0;
        cout<<"Passenger created successfully"<<endl;
        passengers.push_back(p);
}
class Ticket{
    private:
        int price;
    public:
        int source_station, destination_station;
        string date ;
        string traveller_name;
        int traveller_ID;
        int Astronaut_ID;
        int Commander_ID;
        // Ticket()
        void book_ticket()
        {
            cout <<"************************Fill form to book ticket************************" << endl;
            Name:
                cout<<"Enter your Name:"<<endl;
                string name;
                cin.ignore();
                getline(cin, name);
                //cin >> name;
                if(search_Name(name) == -1)
                {
                    cout<<"Invalid User"<<endl;
                    goto Name;
                }
                else if(passengers[search_Name(name)].travelling_status == 1){
                    cout<<"you are already travelling"<<endl;
                    cout<<"Create a new Passenger user and then fill the form"<<endl;
                    addPassenger();
                    goto Name;
                }
                traveller_name = name;
            Identity:
                    cout<<"Enter your ID:"<<endl;
                    int id;
                    cin >> id;
                    if (search_ID(id) == -1)
                    {
                        cout<<"Invalid ID"<<endl;
                        goto Identity;
                    }
                    traveller_ID = id;
            source:  
                cout <<"Enter source station No. from the following list:"<<endl;
                cout<<" 1: Moon \n 2: Mars \n 3: Jupiter"<<endl;
                int a;
                cin>> a;
                source_station = a;
                if (a > 3 || a<1){
                    cout<<"invalid number"<<endl;
                    goto source;
                }
            destination:
               // cout <<"Enter 1 to get source Planet details:"<<endl;
                cout <<"Enter destination station No. from the following list:"<<endl;
                cout<<" 1: Moon \n 2: Mars \n 3: Jupiter"<<endl;
                int b;
                cin>> b;
                destination_station = b;
                if (b > 3 || b<1 || b==a){
                    cout<<"invalid number"<<endl;
                    goto destination;
                }
            price =  TicketPrice(a,b);
            cout<<"Enter Travel Date in DD/MM/YY: "<<endl;
            cin.ignore();
            getline(cin,date);
            //cin>>date;
            int q = searchAstronaut();
            int q1 = searchCommander();
            if(q==-1)
            {
                cout<<"Sorry no astronaut available for you travel."<<endl;
            }
            else astronauts[q].travelling_status = 1;
            if(q1==-1)
            {
                cout<<"Sorry no Commander available for you travel."<<endl;
            }
            else commands[q].travelling_status =1;
            if (q!= -1 && q1!= -1){
            passengers[search_Name(traveller_name)].travelling_status = 1;
            cout<<"********************Your ticket has been confirmed**********\nPlease check your ticket\n"<<endl;
            cout <<"Traveller Name: "<<traveller_name<<endl;
            cout<<"Source Station: "<<planets[source_station-1].name<<endl;
            cout<<"Destination Station: "<<planets[destination_station-1].name<<endl;
            cout<<"Travel date: "<<date<<endl;
            cout<<"Astronaut with you: " << astronauts[q].Name<<endl;
            cout<<"Astronaut experience: "<< astronauts[q].get_experience()<<" years"<<endl;
            cout<<"Commander with you: " << commands[q1].Name<<endl;
            cout<<"Commander experience: "<< commands[q1].Experience<<" years"<<endl;
            cout<<"Total Amount: "<<price<<"\n**********************************************\n\n\n"<<endl;
            ticket.push_back(*this);
            cout<<"Enter 1 to update a ticket:\nEnter 2 to delete a ticket"<<endl;
            int as1;
            cin >> as1;
            if(as1==1)
            {
                update_ticket();
            }
            else
            {
                delete_ticket();
            }
            }
// 
        }
        void update_ticket()
        {
            update:
                cout <<"Enter traveller_ID with which you booked ticket"<<endl;
                int id;
                cin >> id;
                int i = searchTicket(id);
                if(i==-1){
                    cout<<"No user with the given ID booked ticket\n renter the ID"<<endl;
                    goto update;
                }
                else {
                    update1:
                        cout<<"Enter number corresponding to the attribute you want to update"<<endl;
                        cout<<"1. Destination_station\n2. Date \n 3. Finish Update"<<endl;
                        int x;
                        cin >> x;
                        if(x==1)
                        {
                            cout<<"Enter new destination station";
                            int x1;
                            cin >> x1;
                            ticket[i].destination_station =x1;
                            cout<<"Your new destination station is "<<planets[x1].name<<endl;
                            goto update1;
                        }
                        else if(x==2){
                            cout <<"Enter new Date"<<endl;
                            string new_date;
                            cin>>new_date;
                            ticket[i].date = new_date;
                            cout<<"Your new travel date is "<<new_date<<endl;
                            goto update1;
                        }
                        else{

                        }
                }

        }
        void delete_ticket()
        {
            // delete_label:
            //     cout <<"Enter traveller_ID with which you booked ticket"<<endl;
            //     int id;
            //     cin >> id;
            //     int i = searchTicket(id);
            //     if(i==-1){
            //         cout<<"No user with the given ID booked ticket\n renter the ID"<<endl;
            //         goto delete_label;
            //     }
            //     else {
            //         ticket.erase(ticket.begin()+i);
            //     }
            //     cout<<"Your ticket has been deleted"<<endl;
            while (true) {
                cout <<"Enter traveller_ID with which you booked ticket"<<endl;
                int id;
                cin >> id;
                int i = searchTicket(id);
                if(i==-1){
                    cout<<"No user with the given ID booked ticket\n renter the ID"<<endl;
                }
                else {
                    ticket.erase(ticket.begin() + i);
                    cout<<"Your ticket has been deleted"<<endl;
                    break;
                }
            }


        }

};
int searchTicket(int ID){
    int s =ticket.size();
    for(int i = 0 ; i < s ; i++)
    {
        if(ticket[i].traveller_ID == ID)
        return i;
    }
    return -1;

}
float calculateDistance(float x1, float y1, float z1, float x2, float y2, float z2) {
    float xDistance = x2 - x1;
    float yDistance = y2 - y1;
    float zDistance = z2 - z1;
    float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2) + pow(zDistance, 2));
    return distance;
}
float TicketPrice(int a , int b){
    float x1 = planets[1].Position_X;
    float y1 = planets[a-1].Position_Y;
    float z1 = planets[a-1].Position_Z;
    float x2 = planets[b-1].Position_X;
    float y2 = planets[b-1].Position_Y;
    float z2 = planets[b-1].Position_Z;
    return 10000*calculateDistance(x1,y1,z1,x2,y2,z2);

}


int main() {
    Planet planet1(2.1 , 2.5 , 1.2 , "Moon");
    Planet planet2(2.5 , 2.7 , 1.1 , "Mars");
    Planet planet3(2.15 , 2.4 , 1.7 , "Jupiter");
    Astronaut A1(10 , "Mohan" , 1234);
    Astronaut A2(14 , "jjjhhaall" , 1214);
    Astronaut A3(10 , "Hanmo" , 1254);
    Commander C1(100, "Gourv" , 50 , 1111 );
    Commander C2(101, "Gouri" , 20 , 1112 );
    Commander C3(102, "Raathi" , 40 , 1113 );
   // Passenger P1(210543,"Harsh Mohan", 10);
    cout<<"***************************Welcome To Space Travel System!**************************"<<endl;
    addPassenger();
    Ticket T1;
    T1.book_ticket();
    cout<<ticket[0].traveller_name<<endl;
    // for(int i= 0 ; i<5 ; i++){
    //     int a;
    //     cout<<"Enter 1 to Create Passenger:"<<endl;
    //     cout<<"Enter 2 to Book Ticket:"<<endl;
    //     cin>>a;
    //     if (a==1)
    //     {
    //         addPassenger();
    //     }
    //     else{
    //         if(passengers.size() == 0 ){
    //             cout<<" No Passenger created yet. Please create a passenger"<<endl;
    //             addPassenger();
    //         }
    //         Ticket t;
    //         t.book_ticket();
    //     }

    // }
    

    return 0;
}