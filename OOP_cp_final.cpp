#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<conio.h>
using namespace std;

class patient{
    private:
        int app_no;
        string name, symptoms, dob, blood_group, address, adhar_no, mobile_no, disease;
    public:
        void menu(char type);
        void get_data();
        void insert(char type);
        void get_record();
        void display_records(char type);
        void particular_record(char type);
        void discharge_patient(char type);
        void Main_menu();

        int get_appointno(){
            return app_no;
        }

        string get_name(){
            return name;
        }
        string get_symptoms(){
            return symptoms;
        }
        string get_dob(){
            return dob;
        }
        string get_blood_group(){
            return blood_group;
        }
        string get_address(){
            return address;
        }
        string get_adhar_no(){
            return adhar_no;
        }
        string get_mobile_no(){
            return mobile_no;
        }
        string get_disease(){
            return disease;
        }
};

class covid : public patient{
    private:
        int oxy;
        char vent, oxy_required;
    public:
        void get_oxy(){
            char ch;
            cout<<"\n\t\t\tEnter oxygen level: ";
            cin>>oxy;
            if(oxy < 94){
                oxy_required='Y';
                cout<<"\t\t\tVentilator required..."<<endl;
                cin>>ch;
                if(ch=='Y'){
                    vent='Y';
                }
                else{
                    vent='N';
                }
            }
            else{
                oxy_required='N';
                vent='N';
                cout<<"\t\t\tOxygen and Ventilator not needed..."<<endl;
            }
        }

        void get_cov();
};

covid project;
patient pat;
fstream file;
char x;

void patient::menu(char type){
    int choice,ch;

    do{
        //system("cls");
        cout<<endl;
        cout<<"\t\t\t 1. Add new Patient"<<endl;
        cout<<"\t\t\t 2. Display all Patients"<<endl;
        cout<<"\t\t\t 3. Display particular Patient"<<endl;
        cout<<"\t\t\t 4. Discharge Patient"<<endl;
        cout<<"\t\t\t 5. Back to Main Menu"<<endl;
        cout<<"\t\t\t 6. Exit"<<endl<<endl;

        cout<<"\t\t\t-----------------"<<endl;
        cout<<"\t\t\tChoose[1/2/3/4/5/6]"<<endl;
        cout<<"\t\t\t-----------------"<<endl<<endl;

        cout<<"\t\t\tEnter your choice: ";
        cin>>choice;

        switch(choice){
        case 1:
            insert(type);
            break;

        case 2:
            display_records(type);
            break;

        case 3:
            particular_record(type);
            break;

        case 4:
            discharge_patient(type);
            break;

        case 5:
            Main_menu();

        case 6:
            exit(0);

        default:
            cout<<"\n\t\t\tInvalid choice... Please try again..";
            break;
        }
        cout<<"\n\t\t\tPress 1 for Menu or 0 to exit : ";
        cin>>ch;
        system("cls");
    }while(ch==1);
}

void patient::get_data(){
    system("cls");
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"----------------------------------------------------------------------------------------------------------ADD NEW RECORD------------";
    cout<<"--------------------------------------------------------------"<<endl;
    cout<<"\t\t\tAppointment number.............................";
    cin>>app_no;
    cin.ignore();
    cout<<"\t\t\tPatient name...................................";
    getline(cin,name);
    cout<<"\t\t\tSymptoms.......................................";
    getline(cin,symptoms);
    cout<<"\t\t\tDisease........................................";
    getline(cin,disease);
    cout<<"\t\t\tDate of birth..................................";
    getline(cin,dob);
    cout<<"\t\t\tBlood Group....................................";
    getline(cin,blood_group);
    cout<<"\t\t\tPatient address................................";
    getline(cin,address);
    cout<<"\t\t\tAadhar number(xxxx yyyy zzzz)..................";
    getline(cin,adhar_no);
    while(1){
        if(adhar_no.length() != 14){
            cout<<"\t\t\tAadhar number(xxxx yyyy zzzz)..................";
            getline(cin,adhar_no);
        }
        else
            break;
    }
    cout<<"\t\t\tMobile number..................................";
    getline(cin,mobile_no);
    while(1){
        if(mobile_no.length() != 10){
            cout<<"\t\t\tMobile number..................................";
            getline(cin,mobile_no);
        }
        else
            break;
    }
}

void patient::insert(char type){
    do{
            if(type=='N'){
                file.open("normalpat.dat",ios::app | ios::binary);
                pat.get_data();
                file.write((char*)&pat,sizeof(pat));
                file.close();
                cout<<"\n\t\t\tRecord added successfully";
                cout<<"\n\t\t\tAdd Another Patient record (Y,N)";
                cin>>x;
                system("cls");
            }
            else{
                file.open("covidpat.dat",ios::app | ios::binary);
                project.get_data();
                project.get_oxy();
                file.write((char*)&project,sizeof(project));
                file.close();
                cout<<"\n\t\t\tRecord added successfully";
                cout<<"\n\t\t\tAdd Another Patient record (Y,N)";
                cin>>x;
                system("cls");
            }

    }while(x == 'y' || x == 'Y');
}

void patient::get_record(){
    //system("cls");
    cout<<setw(6)<<app_no<<setw(15)<<name<<setw(15)<<symptoms<<setw(15)<<disease<<setw(15)<<dob<<setw(6)<<blood_group<<setw(6)<<address<<setw(15)<<adhar_no
    <<setw(15)<<mobile_no<<endl;
}

void covid::get_cov(){
    //system("cls");
    cout<<setw(6)<<project.get_appointno()<<setw(8)<<project.get_name()<<setw(8)<<project.get_symptoms()<<setw(10)<<project.get_disease()<<setw(11)<<project.get_dob()
    <<setw(6)<<project.get_blood_group()<<setw(15)<<project.get_address()<<setw(25)<<project.get_adhar_no()<<setw(15)<<project.get_mobile_no()<<setw(10)<<oxy<<setw(15)
    <<oxy_required<<setw(15)<<vent<<endl;
}

void patient::display_records(char type){
    system("cls");
    if(type=='C'){
            file.open("covidpat.dat",ios::in | ios::binary);
            //project.get_record();
            if(! file)
            {
                cout<<"\t\t\tFile not found";
            }
            else
            {
                cout<<"app_no     "<<"name  "<<"symptoms  "<<"disease  "<<"dob  "<<"blood_group     "
                <<"address         "<<"adhar_no         "<<"mobile_no         "<<"oxy           "<<"oxy_required    "
                <<"vent"<<endl<<endl;
                file.read((char*)&project,sizeof(project));
                while (!file.eof())
                {
                    project.get_cov();
                    file.read((char*)&project,sizeof(project));
                }
                file.close();
            }
    }
    else{
            file.open("normalpat.dat",ios::in | ios::binary);
            //project.get_record();
            if(!file)
            {
                cout<<"\t\t\tFile not found";
            }
            else
            {
                //cout<<"app_no"<<"name"<<"symptoms"<<"disease"<<"dob"<<"blood_group"
                //<<"address"<<"adhar_no"<<"mobile_no"<<endl;
                file.read((char*)&pat,sizeof(pat));
                while (!file.eof())
                {
                    pat.get_record();
                    file.read((char*)&pat,sizeof(pat));
                }
                file.close();
            }
    }
}

void patient::particular_record(char type){
    system("cls");

    if(type=='C'){
            cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"---------------------------------------------------------------------------------------------------------PARTICULAR RECORD--------------------------------------------------------------"<<endl;

    int no, flag=0, c;
    file.open("covidpat.dat",ios::in | ios::binary);
    if(!file){   //if file open fails
        cout<<"\nFile not found";
    }
    else{
        do{
            cout<<"\nEnter the appointment number: ";
            cin>>no;
            file.read((char*)&project, sizeof(project));
            while(!file.eof()){
                if(no==project.get_appointno()){
                    flag=1;
                    cout<<"\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                    cout<<setw(6)<<"app_no"<<setw(15)<<"name"<<setw(15)<<"symptoms"<<setw(15)<<"disease"<<setw(10)<<"dob"<<setw(6)<<"blood_group"<<setw(6)<<"address"<<setw(15)
                    <<"adhar_no"<<setw(15)<<"mobile_no"<<setw(15)<<"oxy"<<setw(15)<<"oxy_required"<<setw(15)<<"vent"<<endl;
                    cout<<"\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                    project.get_cov();
                    cout<<"\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                    break;
                }
                file.read((char*)&project, sizeof(project));
            }

            if(flag==0){
                cout<<"\nItem not found...";
            }

            cout<<"\nIf you want to search another one record press 1 to continue and 0 to menu.....";
            cin>>c;
        }while(c==1);
    }
    system("cls");
    file.close();
    project.menu(type);
    }

    else{
            cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"---------------------------------------------------------------------------------------------------------PARTICULAR RECORD--------------------------------------------------------------"<<endl;
    int no, flag=0, c;
    file.open("normalpat.dat",ios::in | ios::binary);
    if(!file){   //if file open fails
        cout<<"\nFile not found";
        exit(0);
    }
    else{
        do{
            cout<<"\nEnter the appointment number: ";
            cin>>no;
            file.read((char*)&pat, sizeof(pat));
            while(!file.eof()){
                if(no==pat.get_appointno()){
                    flag=1;
                    cout<<"\n-------------------------------------------------------------------------------------------------------------------------------\n";
                    cout<<setw(6)<<"app_no"<<setw(15)<<"name"<<setw(15)<<"symptoms"<<setw(15)<<"disease"<<setw(15)<<"dob"<<setw(6)<<"blood_group"<<setw(6)<<"address"<<setw(15)
                    <<"adhar_no"<<setw(15)<<"mobile_no"<<endl;
                    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n";
                    pat.get_record();
                    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n";
                    break;
                }
                file.read((char*)&pat, sizeof(pat));
            }

            if(flag==0){
                cout<<"\nItem not found...";
            }

            cout<<"\nIf you want to search another one record press 1 to continue and 0 to menu.....";
            cin>>c;
        }while(c==1);
    }
    system("cls");
    file.close();
    pat.menu(type);
    }
}

void patient::discharge_patient(char type){

    if(type=='C'){
        int no;
        cout<<"\nEnter the appointment number: ";
        cin>>no;
        fstream file2;
        file2.open("discharged.dat", ios::out | ios::binary);
        file.open("covidpat.dat", ios::in | ios::binary);
        if(!file){
            cout<<"\nFile not found";
            //exit(0);
        }
        else{
            file.read((char*)&project, sizeof(project));
            while(!file.eof()){
                if(no != project.get_appointno()){
                    file2.write((char*)&project, sizeof(project));
                }
                file.read((char*)&project,sizeof(project));
            }
        }
        file2.close();
        file.close();
        remove("covidpat.dat");
        rename("discharged.dat","covidpat.dat");
    }

    else{
        int no;
        cout<<"\nEnter the appointment number: ";
        cin>>no;
        fstream file2;
        file2.open("discharged_nor.dat", ios::out | ios::binary);
        file.open("normalpat.dat", ios::in | ios::binary);
        if(!file){
            cout<<"\nFile not found";
            //exit(0);
        }
        else{
            file.read((char*)&pat, sizeof(pat));
            while(!file.eof()){
                if(no != pat.get_appointno()){
                    file2.write((char*)&pat, sizeof(pat));
                }
                file.read((char*)&pat,sizeof(pat));
            }
        }
        file2.close();
        file.close();
        remove("normalpat.dat");
        rename("discharged_nor.dat","normalpat.dat");
    }
}

void patient::Main_menu(){
    system("cls");
    int ch;
    cout<<"\t\t\t-----------------------"<<endl;
    cout<<"\t\t\t|  Sancheti Hospital  |"<<endl;
    cout<<"\t\t\t-----------------------"<<endl<<endl;
    cout<<"\t\t\t1. Normal Patient"<<endl;
    cout<<"\t\t\t2. Covid Patient"<<endl;
    cout<<"\t\t\t3. Exit"<<endl;
    cout<<"\t\t\tEnter your choice: ";
    cin>>ch;

    switch(ch){
    case 1:
        system("cls");
        //char nor='N';
        cout<<"\n\t\t\t******** Normal patient records ********"<<endl<<endl;
        pat.menu('N');
        break;
    case 2:
        system("cls");
        //char cov='C';
        cout<<"\n\t\t\t******** Covid Patient records ********"<<endl<<endl;
        project.menu('C');
        break;
    case 3:
        exit(0);
    }
}

int main(){
    pat.Main_menu();
    return 0;
}


