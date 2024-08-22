#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Hostel{
    private:
     string Name;
     int Rent,Bed;
    public:
     Hostel(string name,int rent,int bed){
        Name = name;
        Rent = rent;
        Bed = bed;
     } 

     string getName(){
        return Name;
     }

     int getRent(){
        return Rent;
     }

     int getBed(){
        return Bed;
     }

     void reserve(){
        ifstream in("./Hostel.txt");
        ofstream out("./temp.txt");

        string line;
        while(getline(in,line)){
            int pos = line.find("Chanakya");
            if(pos != string::npos){
                int bed = Bed-1;
                Bed = bed;

                stringstream ss;
                ss<<bed;
                string strBed = ss.str();

                int bedPos = line.find_last_of(':');
                line.replace(bedPos+1,string::npos,strBed);
            }
            out<<line<<endl;
        }
        out.close();
        in.close();
        remove("./Hostel.txt");
        rename("./temp.txt","./Hostel.txt");
        cout<<"Bed reserved successfully"<<endl;
     }
};

class Student{
    private:
     string Name,RollNo,Address;
    public:
     Student():Name(""),RollNo(""),Address(""){}

     void setName(string name){
        Name = name;
     } 

     void setRollNo(string rollNo){
        RollNo = rollNo;
     }

     void setAddress(string address){
        Address = address;
     }

     string getName(){
        return Name;
     }

     string getRollNo(){
        return RollNo;
     }

     string getAddress(){
        return  Address;
     }
};


int main(){
    Hostel h("Chanakya",5000,3);
    ofstream out("./Hostel.txt");
    out<<h.getName()<<" : "<<h.getRent()<<" : "<<h.getBed()<<endl;
    cout<<"Hostel data saved"<<endl;
    out.close();

    Student s;
    bool exit = false;
    while(!exit){
        int choice;
        cout<<"Welcome to Hostel Accomodation System"<<endl;
        cout<<"*************************************"<<endl;
        cout<<"1.Reserve a bed"<<endl;
        cout<<"2.Exit"<<endl;
        cout<<"Enter choice"<<endl;
        cin>>choice;

        if(choice==1){
            string name,rollNo,address;
            cout<<"Enter the name of student"<<endl;
            cin>>name;
            s.setName(name);

            cout<<"Enter the rollno of student"<<endl;
            cin>>rollNo;
            s.setRollNo(rollNo);

            cout<<"Enter the address of the student"<<endl;
            cin>>address;
            s.setAddress(address);

            if(h.getBed() > 0){
                h.reserve();
            }else if(h.getBed()==0){
                cout<<"Sorry we don't have any beds available"<<endl;
            }
            ofstream outFile("./Student.txt",ios::app);
            outFile<<s.getName()<<" : "<<s.getRollNo()<<" : "<<s.getAddress()<<endl;
        }else if(choice==2){
            exit = true;
            cout<<"Thank You"<<endl;
        }
    }
    return 0;
}