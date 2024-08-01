#include<iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib> // For system()

using namespace std;

class HOTEL
{
    private:
        int room_no;
        char name[30];
        char address[50];
        char phone[15];
        long days;
        long cost;
        char rtype[30];
        long pay;
        void breakfast(int);        // to assign price of breakfast
        void lunch(int);            // to assign price of lunch
        void dinner(int);           // to assign price of dinner

    public:
        void main_menu();           // to display the main menu
        void add();                 // to book a room
        void display();             // to display the specific customer information
        void rooms();               // to display alloted rooms
        void edit();                // to edit the customer by calling modify or delete
        int check(int);             // to check room status
        void modify();              // to modify the customer information
        void delete_rec();          // to check out the customer
        void restaurant();          // to order food from restaurant
        void modify_name(int);      // to modify name of guest
        void modify_address(int);   // to modify address of guest
        void modify_phone(int);     // to modify phone number of guest
        void modify_days(int);      // to modify days of stay of guest
} h;

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void HOTEL::main_menu()
{
    int choice;
    do
    {
        clear_screen();
        cout << "\n\t\t\t\t *************";
        cout << "\n\t\t\t\t **THE HOTEL**";
        cout << "\n\t\t\t\t *************";
        cout << "\n\t\t\t\t * MAIN MENU *";
        cout << "\n\t\t\t\t *************";
        cout << "\n\n\n\t\t\t\t1. Book A Room";
        cout << "\n\t\t\t\t2. Customer Information";
        cout << "\n\t\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t\t4. Edit Customer Details";
        cout << "\n\t\t\t\t5. Order Food from Restaurant";
        cout << "\n\t\t\t\t6. Exit";
        cout << "\n\n\t\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: add();
                break;
            case 2: display();
                break;
            case 3: rooms();
                break;
            case 4: edit();
                break;
            case 5: restaurant();
                break;
            case 6: return;
            default:
                {
                    cout << "\n\n\t\t\tWrong choice.";
                    cout << "\n\t\t\tPress any key to continue.";
                    getchar();
                    getchar();
                }
        }
    } while (choice != 6);
}

void HOTEL::add()
{
    clear_screen();
    int r, flag;
    ofstream fout("Record.DAT", ios::app | ios::binary);
    cout << "\n\t\t\t +-----------------------+";
    cout << "\n\t\t\t | Rooms  |   Room Type  |";
    cout << "\n\t\t\t +-----------------------+";
    cout << "\n\t\t\t |   1-50 |    Deluxe    |";
    cout << "\n\t\t\t |  51-80 |   Executive  |";
    cout << "\n\t\t\t | 81-100 | Presidential |";
    cout << "\n\t\t\t +-----------------------+";
    cout << "\n\n ENTER CUSTOMER DETAILS";
    cout << "\n ----------------------";
    cout << "\n\n Room Number: ";
    cin >> r;
    flag = check(r);
    if (flag == 1)
        cout << "\n Sorry, Room is already booked.\n";
    else if (flag == 2)
        cout << "\n Sorry, Room does not exist.\n";
    else
    {
        room_no = r;
        cout << " Name: ";
        cin.ignore();
        cin.getline(name, 30);
        cout << " Address: ";
        cin.getline(address, 50);
        cout << " Phone Number: ";
        cin.getline(phone, 15);
        cout << " Number of Days: ";
        cin >> days;
        if (room_no >= 1 && room_no <= 50)
        {
            strcpy(rtype, "Deluxe");
            cost = days * 10000;
        }
        else if (room_no >= 51 && room_no <= 80)
        {
            strcpy(rtype, "Executive");
            cost = days * 12500;
        }
        else if (room_no >= 81 && room_no <= 100)
        {
            strcpy(rtype, "Presidential");
            cost = days * 15000;
        }
        fout.write((char *)this, sizeof(HOTEL));
        cout << "\n Room has been booked.";
    }
    cout << "\n Press any key to continue.";
    getchar();
    getchar();
    fout.close();
}

void HOTEL::display()
{
    clear_screen();
    ifstream fin("Record.DAT", ios::in | ios::binary);
    int r, flag = 0;
    cout << "\n Enter Room Number: ";
    cin >> r;
    while (fin.read((char *)this, sizeof(HOTEL)))
    {
        if (room_no == r)
        {
            clear_screen();
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room Number: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone Number: " << phone;
            cout << "\n Staying for " << days << " days.";
            cout << "\n Room Type: " << rtype;
            cout << "\n Total cost of stay: " << cost;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Room is Vacant.";
    cout << "\n\n Press any key to continue.";
    getchar();
    getchar();
    fin.close();
}

void HOTEL::rooms()
{
    clear_screen();
    const char separator = ' ';
    const int NoWidth = 8;
    const int GuestWidth = 17;
    const int AddressWidth = 16;
    const int RoomWidth = 13;
    const int ContactNoWidth = 13;
    ifstream fin("Record.DAT", ios::in | ios::binary);
    cout << "\n\t\t\t    LIST OF ROOMS ALLOTED";
    cout << "\n\t\t\t   -----------------------";
    cout << "\n\n +---------+------------------+-----------------+--------------+--------------+";
    cout << "\n | Room No.|    Guest Name    |      Address    |   Room Type  |  Contact No. |";
    cout << "\n +---------+------------------+-----------------+--------------+--------------+";
    while (fin.read((char *)this, sizeof(HOTEL)))
    {
        cout << "\n |" << setw(NoWidth) << setfill(separator) << room_no << " |";
        cout << setw(GuestWidth) << setfill(separator) << name << " |";
        cout << setw(AddressWidth) << setfill(separator) << address << " |";
        cout << setw(RoomWidth) << setfill(separator) << rtype << " |";
        cout << setw(ContactNoWidth) << setfill(separator) << phone << " |";
    }
    cout << "\n +---------+------------------+-----------------+--------------+--------------+";
    cout << "\n\n\n\t\t\tPress any key to continue.";
    getchar();
    getchar();
    fin.close();
}

void HOTEL::edit()
{
    clear_screen();
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1. Modify Customer Information.";
    cout << "\n 2. Customer Check Out.";
    cout << "\n Enter your choice: ";
    cin >> choice;
    clear_screen();
    switch (choice)
    {
        case 1: modify();
            break;
        case 2: delete_rec();
            break;
        default: cout << "\n Wrong Choice.";
            break;
    }
    cout << "\n Press any key to continue.";
    getchar();
    getchar();
}

int HOTEL::check(int r)
{
    int flag = 0;
    ifstream fin("Record.DAT", ios::in | ios::binary);
    while (fin.read((char *)this, sizeof(HOTEL)))
    {
        if (room_no == r)
        {
            flag = 1;
            break;
        }
        else if (r > 100)
        {
            flag = 2;
            break;
        }
    }
    fin.close();
    return (flag);
}

void HOTEL::modify()
{
    clear_screen();
    int ch, r;
    cout << "\n MODIFY MENU";
    cout << "\n -----------";
    cout << "\n\n\n 1. Modify Name";
    cout << "\n 2. Modify Address";
    cout << "\n 3. Modify Phone Number";
    cout << "\n 4. Modify Number of Days";
    cout << "\n Enter your choice: ";
    cin >> ch;
    cout << "\n Enter room no: ";
    cin >> r;
    switch (ch)
    {
        case 1: modify_name(r);
            break;
        case 2: modify_address(r);
            break;
        case 3: modify_phone(r);
            break;
        case 4: modify_days(r);
            break;
        default: cout << "\n Wrong Choice.";
            break;
    }
    cout << "\n Press any key to continue.";
    getchar();
    getchar();
}

void HOTEL::modify_name(int r)
{
    clear_screen();
    long pos;
    fstream file("Record.DAT", ios::in | ios::out | ios::binary);
    while (file.read((char *)this, sizeof(HOTEL)))
    {
        pos = file.tellg();
        if (room_no == r)
        {
            cout << "\n Enter New Name: ";
            cin.ignore();
            cin.getline(name, 30);
            file.seekg(pos - sizeof(HOTEL));
            file.write((char *)this, sizeof(HOTEL));
            cout << "\n Name has been modified.";
            break;
        }
    }
    file.close();
}

void HOTEL::modify_address(int r)
{
    clear_screen();
    long pos;
    fstream file("Record.DAT", ios::in | ios::out | ios::binary);
    while (file.read((char *)this, sizeof(HOTEL)))
    {
        pos = file.tellg();
        if (room_no == r)
        {
            cout << "\n Enter New Address: ";
            cin.ignore();
            cin.getline(address, 50);
            file.seekg(pos - sizeof(HOTEL));
            file.write((char *)this, sizeof(HOTEL));
            cout << "\n Address has been modified.";
            break;
        }
    }
    file.close();
}

void HOTEL::modify_phone(int r)
{
    clear_screen();
    long pos;
    fstream file("Record.DAT", ios::in | ios::out | ios::binary);
    while (file.read((char *)this, sizeof(HOTEL)))
    {
        pos = file.tellg();
        if (room_no == r)
        {
            cout << "\n Enter New Phone Number: ";
            cin.ignore();
            cin.getline(phone, 15);
            file.seekg(pos - sizeof(HOTEL));
            file.write((char *)this, sizeof(HOTEL));
            cout << "\n Phone Number has been modified.";
            break;
        }
    }
    file.close();
}

void HOTEL::modify_days(int r)
{
    clear_screen();
    long pos;
    fstream file("Record.DAT", ios::in | ios::out | ios::binary);
    while (file.read((char *)this, sizeof(HOTEL)))
    {
        pos = file.tellg();
        if (room_no == r)
        {
            cout << "\n Enter New Number of Days: ";
            cin >> days;
            file.seekg(pos - sizeof(HOTEL));
            file.write((char *)this, sizeof(HOTEL));
            cout << "\n Number of Days has been modified.";
            break;
        }
    }
    file.close();
}

void HOTEL::delete_rec()
{
    clear_screen();
    int r;
    char ch;
    ifstream fin("Record.DAT", ios::in | ios::binary);
    ofstream fout("temp.DAT", ios::out | ios::binary);
    cout << "\n Enter Room Number: ";
    cin >> r;
    while (fin.read((char *)this, sizeof(HOTEL)))
    {
        if (room_no != r)
            fout.write((char *)this, sizeof(HOTEL));
        else
        {
            clear_screen();
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone Number: " << phone;
            cout << "\n Staying for " << days << " days.";
            cout << "\n Room Type: " << rtype;
            cout << "\n Total cost of stay: " << cost;
            cout << "\n\n Do you want to checkout this customer(y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write((char *)this, sizeof(HOTEL));
        }
    }
    fin.close();
    fout.close();
    remove("Record.DAT");
    rename("temp.DAT", "Record.DAT");
}

void HOTEL::breakfast(int option)
{
    switch (option)
    {
        case 1: cout << " Cost: Rs. 300"; pay = 300; break;
        case 2: cout << " Cost: Rs. 250"; pay = 250; break;
        case 3: cout << " Cost: Rs. 200"; pay = 200; break;
        case 4: cout << " Cost: Rs. 100"; pay = 100; break;
        default: cout << " Invalid Option"; pay = 0; break;
    }
}

void HOTEL::lunch(int option)
{
    switch (option)
    {
        case 1: cout << " Cost: Rs. 500"; pay = 500; break;
        case 2: cout << " Cost: Rs. 400"; pay = 400; break;
        case 3: cout << " Cost: Rs. 300"; pay = 300; break;
        case 4: cout << " Cost: Rs. 200"; pay = 200; break;
        default: cout << " Invalid Option"; pay = 0; break;
    }
}

void HOTEL::dinner(int option)
{
    switch (option)
    {
        case 1: cout << " Cost: Rs. 600"; pay = 600; break;
        case 2: cout << " Cost: Rs. 500"; pay = 500; break;
        case 3: cout << " Cost: Rs. 400"; pay = 400; break;
        case 4: cout << " Cost: Rs. 300"; pay = 300; break;
        default: cout << " Invalid Option"; pay = 0; break;
    }
}

void HOTEL::restaurant()
{
    clear_screen();
    int choice;
    cout << "\n ************";
    cout << "\n * MAIN MENU*";
    cout << "\n ************";
    cout << "\n\n 1. Breakfast";
    cout << "\n 2. Lunch";
    cout << "\n 3. Dinner";
    cout << "\n 4. Exit";
    cout << "\n\n Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
        case 1:
            clear_screen();
            cout << "\n ************";
            cout << "\n *BREAKFAST*";
            cout << "\n ************";
            cout << "\n\n 1. Idly";
            cout << "\n 2. Dosa";
            cout << "\n 3. Poori";
            cout << "\n 4. Exit";
            cout << "\n\n Enter your choice: ";
            cin >> choice;
            breakfast(choice);
            break;
        case 2:
            clear_screen();
            cout << "\n ********";
            cout << "\n *LUNCH*";
            cout << "\n ********";
            cout << "\n\n 1. Full Meals";
            cout << "\n 2. Mini Meals";
            cout << "\n 3. Fried Rice";
            cout << "\n 4. Noodles";
            cout << "\n\n Enter your choice: ";
            cin >> choice;
            lunch(choice);
            break;
        case 3:
            clear_screen();
            cout << "\n *********";
            cout << "\n *DINNER*";
            cout << "\n *********";
            cout << "\n\n 1. Paneer Butter Masala";
            cout << "\n 2. Chapathi";
            cout << "\n 3. Parotta";
            cout << "\n 4. Naan";
            cout << "\n\n Enter your choice: ";
            cin >> choice;
            dinner(choice);
            break;
        case 4:
            return;
        default:
            cout << "\n Wrong Choice.";
    }
    cout << "\n\n Press any key to continue.";
    getchar();
    getchar();
}

int main()
{
    h.main_menu();
    return 0;
}

