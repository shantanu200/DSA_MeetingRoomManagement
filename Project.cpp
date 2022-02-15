#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

using namespace std;

class MeetingHotel
{
public:
    int room_no;
    string Hostname;
    string meetpurpose;
    string meetdate;
    string meetduration;
    string meetstarttime;
    void homescreen();
    int check(int);
    void book();
    void records();
    void edit();
    void cancel();
    void adddata(int);
};
int MeetingHotel::check(int r)
{
    int flag = 0;

    ifstream fin("db.dat", ios::in);

    while (!fin.eof())
    {

        fin.read((char *)this, sizeof(MeetingHotel));
        if (room_no == r)
        {

            flag = 1;
            break;
        }
    }
    fin.close();
    return (flag);
}
void MeetingHotel::adddata(int choice)
{
    system("CLS");
    ofstream fout("db.dat", ios::app);
    int user_room;
    cout << "\t\t\t\t\t\tInsert Data \n";
    cout << "\t\t\t\t------------------------------------------------\n\n";
    cout << "\t\t\t\t\tEnter Hostname: ";
    cin >> Hostname;

    if (choice == 1)
    {
        meetpurpose = "Buisness";
    }
    else if (choice == 2)
    {
        meetpurpose = "Non-Buisness";
    }
    cout << "\n\t\t\t\t\tMeet Purpose: " << meetpurpose << endl;
    cout << "\n\t\t\t\t\tEnter Meet Date: ";
    cin >> meetdate;
    cout << "\n\t\t\t\t\tEnter Meet Duration: ";
    cin >> meetduration;
    cout << "\n\t\t\t\t\tEnter Start-Time of Meet: ";
    cin >> meetstarttime;
    cout << "\n\t\t\t\t\tEnter Room Number: ";
    cin >> user_room;

    if (check(user_room))
    {
        cout << "\n\t\t\t\t\tSorry!!!,Room No. is already booked.";
    }
    else
    {
        room_no = user_room;
        fout.write((char *)this, sizeof(MeetingHotel));
        cout << "\t\t\t\t-------------------Room Booked!!!!------------------------";
    }
    cout<<"\n\n\t\t\t\t\tPress any key to continue";
    getch();
    fout.close();
}

void MeetingHotel::book()
{
    system("cls");
    int choice;
    cout << "\t\t\t\t\tRegister and access free meeting place \n\n";
    cout << "\t\t\t\t------------------------------------------------\n";
    cout << "\t\t\t\t\t\t1.Buisness Meeting" << endl;
    cout << "\t\t\t\t\t\t2.Non-Buisness Meeting" << endl;
    cout << "\n\n\t\t\t\t\t\tEnter your choice: ";
    cin >> choice;

    if (choice == 1 || choice == 2)
    {
        adddata(choice);
    }
    else
    {
        cout << "\n\t\t\t\t\tInvalid Choice";
    }
    cout<<"\n\n\t\t\t\t\tPress any key to continue";
}
void MeetingHotel::records()
{
    system("CLS");
    bool flag = false;

    ifstream fin("db.dat", ios::in);

    string room;
    cout << "\t\t\t\t\tEnter the booked room number/Hostname here: ";
    cin >> room;

    while (!fin.eof())
    {
        fin.read((char *)this, sizeof(MeetingHotel));
        if (room == to_string(room_no) || Hostname == room)
        {
            cout << "\n\t\t\t\t\t----------Details----------" << endl;
            cout << "\n\n\t\t\t\t\tHostname: " << Hostname << endl;
            cout << "\n\t\t\t\t\tMeeting-Purpose: " << meetpurpose << endl;
            cout << "\n\t\t\t\t\tMeet Date: " << meetdate << endl;
            cout << "\n\t\t\t\t\tMeet Duration: " << meetduration << endl;
            cout << "\n\t\t\t\t\tRoom No.: " << room_no << endl;
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        cout << "\t\t\t\t\t\t----------Details----------" << endl;
        cout << "\n\t\t\t\t\t\tNo Such user is found!!!!" << endl;
    }
    cout<<"\n\n\t\t\t\t\tPress any key to continue";
    getch();
    fin.close();
}
void MeetingHotel::edit()
{
    system("CLS");

    long file_pos;

    int room;

    bool find = false;
    cout << "\t\t\t\t\tEnter Meet-Room number: ";
    cin >> room;
    fstream file("db.dat", ios::in | ios::out | ios::binary);

    while (!file.eof())
    {
        file_pos = file.tellg();
        file.read((char *)this, sizeof(MeetingHotel));

        if (room == room_no)
        {
            cout << "\t\t\t\t\tEnter New Details: " << endl;
            cout << "\t\t\t\t\t--------------------------------" << endl;
            cout << "\t\t\t\t\tHostname: ";
            cin >> Hostname;
            cout << "\n\t\t\t\t\tMeet Purpose: ";
            cin >> meetpurpose;
            cout << "\n\t\t\t\t\tMeet Date: ";
            cin >> meetdate;
            cout << "\n\t\t\t\t\tMeet Duration: ";
            cin >> meetduration;
            file.seekg(file_pos);
            file.write((char *)this, sizeof(MeetingHotel));
            cout << "\n\t\t\t\t\tRecord is updated for room no. " << room_no << endl;
            find = true;
            break;
        }
    }
    if (!find)
    {
        cout << "\t\t\t\t\tNo entry for these room_no" << endl;
    }
    cout<<"\n\n\t\t\t\t\tPress any key to continue";
    getch();
}
void MeetingHotel::cancel()
{
    system("CLS");
    bool flag = false;
    int room;
    char ans;

    ifstream fin("db.dat", ios::in);
    ofstream fout("temp.dat", ios::out);

    cout << "\t\t\t\t\t-----------Cancel Meetings-----------" << endl;
    cout << "\n\t\t\t\t\tEnter room Number Here: ";
    cin >> room;
    while (!fin.eof())
    {
        fin.read((char *)this, sizeof(MeetingHotel));
        if (room_no == room)
        {
            cout << "\n\t\t\t\t\tHostname: " << Hostname << endl;
            cout << "\t\t\t\t\tDo You Really want to delete the room: Y/N -> ";
            cin >> ans;

            if (ans == 'N')
            {
                fout.write((char *)this, sizeof(MeetingHotel));
            }
            flag = true;
        }
        else
        {
            fout.write((char *)this, sizeof(MeetingHotel));
        }
    }

    fin.close();
    fout.close();

    if (flag == false)
    {
        cout << "\n\t\t\t\tNo Such User find in database with meet room no. " << room << endl;
    }

    else
    {
        remove("db.dat");
        rename("temp.dat", "db.dat");
    }
    getch();

}
void MeetingHotel::homescreen()
{
hs:
    system("CLS");
    int key;
    cout << "\n\t\t\t\t*************************";
    cout << "\n\t\t\t\t MEETING MANGEMENT SYSTEM ";
    cout << "\n\t\t\t\t      * MAIN MENU *";
    cout << "\n\t\t\t\t*************************";
    cout << "\n\n\n\t\t\t1.Book A Meeting Room";
    cout << "\n\t\t\t2.Meeting Records";
    cout << "\n\t\t\t3.Edit Meeting Record";
    cout << "\n\t\t\t4.Cancel Meeting";
    cout << "\n\t\t\t5.Exit";
    cout << "\n\n\t\t\tEnter Your Choice: ";
    cin >> key;

    switch (key)
    {
    case 1:
        book();
        break;

    case 2:
        records();
        break;

    case 3:
        edit();
        break;
    case 4:
        cancel();
        break;

    default:
        cout << "\t\t\t\t-----------Invalid Choice-----------" << endl;
        goto hs;
        break;
    }
}

int main()
{
    MeetingHotel object;
    object.homescreen();
    return 0;
}