#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string>
using namespace std;
// sign up / in function variables
string usernames[100];
string passwords[100];
string roles[100];
int usercount = 0;
string name;
string password;
string role;
string role1;
// sign in sign up functions
int menu();
void add(string name, string password, string role);
bool signin(string name, string password);
void store(string name, string password, string role);
void viewall();
bool isValidName(string name);
void loaddatafromfile();
void header();
void adminheader();
void sign_up_menu();
void sign_in_menu();
// validation for email , password, user
bool check_email(string name);
bool check_password(string password);
bool check_user_type(string role);
// admin functions
// for employees:  variables
string employees[100];
string types[100];
int no_of_emp;
int staff_count = 0;
int staff_count1 = 0;
string search_employee;
// for employees: function
void add_employees();
void store_employees();
void store_all_employees();
void load_employees_from_file();
void delete_employees();
void search_employee_name();
void view_employees();
void viewall_signups();
bool isFound(string search_employee);
void view_sales();
void view_income();
// for bus: variables
string buses[100];
string timings[100];
string routes[100];
string dates[100];
int return_index = 0;
int num_of_bus = 0;
int bus_count = 0;
string search_serial;
// for bus: functions
void add_bus_with_timing();
void store_buses();
void load_buses_from_file();
void delete_buses();
void search_bus_serial();
bool isFound_bus(string search_serial);
void view_buses();
void admin_menu();
void admin_Header();

// user functions
// user variables
string search_route;
string search_bus_serial_u;
int num_of_seats = 0;
string user_details_arrays[100];
string user_genders[100];
string contacts[100];
string user_data;
string user_gender;
string contact;

int user_count = 0;
int total_users = 0;
float payments = 0;
string cancelled_seats;
float pay = 0;
string buyer_names[100];
int buyer_count = 0;
int num_of_seats_resererved[100];
string seat_number[100];
int paid[100];
// user functions
void search_bus_route();
bool route_found(string search_route);
void user_details();
void reserve_seat();
void update_seat();
void payment_seat();
void cancel_seat();
bool serial_found(string search_bus_serial_u);
void refund();
void view_tickets();
void load_users_from_file();
void store_user_details();
void select_bus();
void user_menu();
void store_customer_data();
void load_customer_data();
bool change_seat_found(string change_seat);
bool new_seat_found(string new_seat);
void store_payments(int pay);
void load_payments();
void add_user_to_array();

main()
{
    //load_users_from_file();
	load_users_from_file();
    loaddatafromfile();
    load_payments();
    load_buses_from_file();
    load_employees_from_file();
    
    load_customer_data();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 6;
    SetConsoleTextAttribute(hConsole, k);
    int number = menu();
    while (number != 0)
    {
        if (number == 1)
        {
            sign_up_menu();
            getch();
            number = menu();
        }
        else if (number == 2)
        {
            cout << number;
            sign_in_menu();
            cout << "Press any key to continue " << endl;
            getch();
            menu();
        }
        else
        {
            cout << "invalid option";
            cout << "Press any key to continue " << endl;
            getch();
            menu();
        }
    }
    // load_users_from_file();
    // registration_function_call();
}
void sign_up_menu()
{
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Enter your email: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;
    cout << "Enter your role: ";
    cin >> role;
    bool email_check = check_email(name);
    bool password_check = check_password(password);
    bool role_check = check_user_type(role);
    if ((email_check == true) && (password_check == true) && (role_check == true))
    {
        bool decision = isValidName(name);
        if (decision == true)
        {
            add(name, password, role);
            store(name, password, role);
            cout << "Account created successfully" << endl;
        }
        else
        {
            cout << " Name Not available " << endl;
        }
    }
    else
    {
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "Something went wrong!!" << endl;
        cout << "Please make sure the following things:" << endl;
        cout << "1. your email must have @ " << endl;
        cout << "Like : test@gmail.com" << endl;
        cout << "2. Your password must be 8 digits or more." << endl;
        cout << "Your role must be admin/ADMIN or customer/ CUSTOMER" << endl;
    }
}

void sign_in_menu()
{

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;
    bool decision = signin(name, password);

    if (decision == true)
    {
        for (int index = 0; index < usercount; index++)
        {
            if (usernames[index] == name && passwords[index] == password)
            {
                role1 = roles[index];
                cout << "You are " << role1 << endl;
                cout << "LogIn successful" << endl;
                if (role1 == "ADMIN" || role1 == "admin")
                {
                    system("cls");
                    admin_Header();
                    admin_menu();
                }
                if (role1 == "CUSTOMER" || role1 == "customer")
                {
                    system("cls");
                    admin_Header();
                    user_menu();
                }
            }
        }
    }
    else
    {
        cout << "Invalid Credentials" << endl;
    }
}
bool check_email(string name)
{
    if (name.find("@") != string::npos)
    {
        return true;
    }
    else
    {
        return false;
        cout << "Email is Invalid.\n";
    }
}
bool check_password(string password)
{
    if (password.size() >= 8)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool check_user_type(string role)
{
    if (role == "ADMIN" || role == "admin")
    {
        return true;
    }
    else if (role == "Customer" || role == "customer")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void add(string name, string password, string role)
{
    usernames[usercount] = name;
    passwords[usercount] = password;
    roles[usercount] = role;
    usercount++;
}
void store(string name, string password, string role)
{
    fstream file;
    file.open("bus.txt", ios::app);
    file << name << endl;
    file << password << endl;
    file << role << endl;
    file.close();
}
bool signin(string name, string password)
{
    bool flag = false;
    for (int index = 0; index < usercount; index++)
    {
        if (usernames[index] == name && passwords[index] == password)
        {

            flag = true;
            break;
        }
    }
    return flag;
}
bool isValidName(string name)
{
    bool flag = true;
    for (int index = 0; index < usercount; index++)
    {
        if (usernames[index] == name)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
int menu()
{
    system("cls");
    admin_Header();

    int choice = 0;
    cout << endl;
    cout << "1. SignUp" << endl;
    cout << "2. SignIn" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: " << endl;
    cin >> choice;
    return choice;
}

void loaddatafromfile()
{
    string name;
    string password;
    string role;
    fstream file;
    file.open("bus.txt", ios::in);
    while (getline(file, name) && getline(file, password) && getline(file, role))
    {

        usernames[usercount] = name;
        passwords[usercount] = password;
        roles[usercount] = role;

        usercount++;
    }
    file.close();
}

////////// admin functionalities

void admin_menu()
{
    int adm = 1;

    while (adm != 0)
    {
        admin_Header();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int k = 6;
        SetConsoleTextAttribute(hConsole, k);
        cout << "You can do these tasks ." << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Press 1 to add employee ." << endl;
        cout << "Press 2 to delete employee ." << endl;
        cout << "Press 3 to search employee ." << endl;
        cout << "Press 4 to view all employees ." << endl;
        cout << "Press 5 to add bus with timing and route ." << endl;
        cout << "Press 6 to delete bus ." << endl;
        cout << "Press 7 to search bus ." << endl;
        cout << "Press 8 to view all buses ." << endl;
        cout << "Press 9 to view sales ." << endl;
        cout << "Press 10 to view income ." << endl;
        cout << "Press 11 to view all sign ups" << endl;
        cout << "Press 0 to exist." << endl;
        cout << "----------------------------------------" << endl;
        cout << "Your choice : ";
        cin >> adm;
        cout << endl;
        cout << endl;
        if (adm == 1)
        {
            add_employees();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 2)
        {
            delete_employees();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 3)
        {
            search_employee_name();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 4)
        {
            view_employees();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 5)
        {
            add_bus_with_timing();
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 6)
        {
            delete_buses();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 7)
        {
            search_bus_serial();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 8)
        {
            view_buses();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 9)
        {
            view_sales();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 10)
        {
            view_income();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (adm == 11)
        {
            viewall_signups();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else
        {
            adm = 0;
            menu();
        }
    }
}

void admin_Header()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 14;
    SetConsoleTextAttribute(hConsole, k);
    cout << "#####################################################################################################################" << endl;
    cout << "#     #     ##                  #####            #                        #   #          #                          #" << endl;
    cout << "#    # #     #                  #                                         #   #          #                          #  " << endl;
    cout << "#   #   #    #                  #       ###     ##    ###   # ##          ## ##   ###   ####    ###   # ##    ###   #" << endl;
    cout << "#   #   #    #    #####         ####       #     #       #  ##  #         # # #  #   #   #     #   #  ##  #  #      #" << endl;
    cout << "#   #####    #                  #       ####     #    ####  #             #   #  #   #   #     #   #  #       ###   #" << endl;
    cout << "#   #   #    #                  #      #   #     #   #   #  #             #   #  #   #   #  #  #   #  #          #  # " << endl;
    cout << "#   #   #   ###                 #       ####  #  #    ####  #             #   #   ###     ##    ###   #      ####   #       " << endl;
    cout << "#                                             #  #                                                                  # " << endl;
    cout << "#                                              ##                                                                   # " << endl;
    cout << "##################################################################################################################### " << endl;
}
void add_employees()
{
    // add employee

    string employee, type;
    int numbers;
    cout << "Enter the number of employees : ";
    cin >> numbers;

    for (int i = 0; i < numbers; i++)
    {

        cout << "Enter the name of employee: ";
        cin >> employees[no_of_emp];

        cout << "Enter the type of employee: ";
        cin >> types[no_of_emp];
        no_of_emp++;
    }
    store_employees();
}
void store_employees()
{
    fstream file;
    file.open("employees.txt", ios::app);
    for (int i = 0; i < no_of_emp; i++)
    {
        file << employees[i] << endl;
        file << types[i] << endl;
    }
    file.close();
}
void store_all_employees()
{
    fstream file;
    file.open("employees.txt", ios::out);
    for (int i = 0; i < no_of_emp; i++)
    {
        file << employees[i] << endl;
        file << types[i] << endl;
    }
    file.close();
}
void load_employees_from_file()
{
    string staff_name;
    string staff_type;
    fstream file;
    file.open("employees.txt", ios::in);
    while ((getline(file, staff_name) && (getline(file, staff_type))))
    {
        employees[staff_count] = staff_name;
        types[staff_count] = staff_type;
        staff_count++;
        no_of_emp++;
    }
    file.close();
}
void delete_employees()
{
    string delete_name;
    int index;

    cout << "Enter the name of employee to delete: ";
    cin >> delete_name;

    for (int i = 0; i < no_of_emp; i++)
    {
        if (delete_name == employees[i])
        {
            index = i;
        }
    }
    for (int j = index; j < no_of_emp; j++)
    {

        employees[j] = employees[j + 1];
        types[j] = types[j + 1];
    }

    no_of_emp--;
    store_all_employees();
}
void search_employee_name()
{

    cout << "Enter the name of employee to search: ";
    cin >> search_employee;
    for (int i = 0; i < no_of_emp; i++)
    {
        if (isFound(search_employee) == true)
        {
            cout << "Present";
            break;
        }
    }
}
bool isFound(string search_employee)
{
    for (int i = 0; i < no_of_emp; i++)
    {
        if (search_employee == employees[i])
        {
            return true;
        }
    }
    return false;
}

void view_employees()
{
    cout << "Here is the list of all employees " << endl;
    cout << endl;
    cout << "Total no of Employees are : " << no_of_emp << endl;
    cout << endl;
    cout << "Name\t\t Type" << endl;
    for (int i = 0; i < no_of_emp; i++)
    {
        cout << employees[i] << "\t\t" << types[i] << endl;
    }
}

// bus functionalities
void add_bus_with_timing()
{

    int numbers;
    cout << "Enter the number of buses : ";
    cin >> numbers;

    for (int i = 0; i < numbers; i++)
    {
        cout << "Enter the serial number of bus: " << i + 1 << "  ";
        cin >> buses[num_of_bus];
        cout << "Enter the timing of bus: " << i + 1 << "  ";
        cin >> timings[num_of_bus];
        cout << "Enter the route of bus: " << i + 1 << "  ";
        cin.ignore();
        getline(cin, routes[num_of_bus]);
        cout << "Enter the date of  departure of bus: " << i + 1 << "  ";
        // cin.ignore();              changes
        getline(cin, dates[num_of_bus]);

        num_of_bus++;
    }

    store_buses();
}
void store_buses()
{
    fstream file;
    file.open("buses1.txt", ios::app);
    for (int i = 0; i < num_of_bus; i++)
    {
        file << buses[i] << endl;
        file << timings[i] << endl;
        file << dates[i] << endl;
        file << routes[i] << endl;
    }
    file.close();
}
void store_all_buses()
{
    fstream file;
    file.open("buses1.txt", ios::out);
    for (int i = 0; i < num_of_bus; i++)
    {
        file << buses[i] << endl;
        file << timings[i] << endl;
        file << dates[i] << endl;
        file << routes[i] << endl;
    }
    file.close();
}
void load_buses_from_file()
{
    string bus_serial;
    string bus_timing;
    string bus_route;
    string bus_date;
    fstream file;
    file.open("buses1.txt", ios::in);
    while ((getline(file, bus_serial) && (getline(file, bus_timing)) && (getline(file, bus_date)) && (getline(file, bus_route))))
    {
        buses[bus_count] = bus_serial;
        timings[bus_count] = bus_timing;
        dates[bus_count] = bus_date;
        routes[bus_count] = bus_route;
        bus_count++;
        num_of_bus++;
    }
    file.close();
}
void delete_buses()
{
    string delete_serial;
    int index;

    cout << "Enter the serial of bus to delete: ";
    cin >> delete_serial;

    for (int i = 0; i < num_of_bus; i++)
    {
        if (delete_serial == buses[i])
        {
            index = i;
        }
    }
    for (int j = index; j < num_of_bus; j++)
    {

        buses[j] = buses[j + 1];
        timings[j] = timings[j + 1];
        routes[j] = routes[j + 1];
        dates[j] = dates[j + 1];
    }

    num_of_bus--;
    store_all_buses();
}
void search_bus_serial()
{
    cout << "Enter the serial of bus to search: ";
    cin >> search_serial;
    for (int i = 0; i < num_of_bus; i++)
    {
        if (isFound_bus(search_serial) == true)
        {
            cout << "Present" << endl;
            cout << "The bus you are looking for has timing : " << timings[return_index] << endl;
            cout << "The bus you are looking for has route : " << routes[return_index] << endl;
            cout << "The bus you are looking for has date : " << dates[return_index] << endl;
            break;
        }
    }
}
bool isFound_bus(string search_serial)
{
    for (int i = 0; i < num_of_bus; i++)
    {
        if (search_serial == buses[i])
        {
            return_index = i;
            return true;
        }
    }
    return false;
}
void view_buses()
{
    cout << "Here is the list of all buses " << endl;
    cout << endl;
    cout << endl;
    cout << "Serial\tTiming\tDate\t\tRoute" << endl;
    for (int i = 0; i < num_of_bus; i++)
    {

        cout << buses[i] << "\t" << timings[i] << "\t" << dates[i] << "\t\t" << routes[i] << endl;
    }
}

void viewall_signups()
{

    cout << "Names\t\t\t\tPassword\t\t\tRole" << endl;
    for (int index = 0; index < usercount; index++)
    {
        cout << usernames[index] << "\t\t\t" << passwords[index] << "\t\t\t" << roles[index] << "\n";
    }
}
// admin functions
void view_sales()
{ //////////////////////////////////////////////

    cout << "The following customers bought tickets " << endl;
    cout << "Names \t\t\t Gender \t\t Contact-Number ";
    for (int i = 0; i < user_count; i++)
    {
        cout << user_details_arrays[i] << "\t\t" << user_genders[i] << "\t\t" << contacts[i] << endl;
    }
    cout << endl;
    cout << endl;
}
void view_income()
{
    int petrol = 5000;
    int petrol_all_buses = petrol * bus_count;
    int total = payments - petrol_all_buses;
    cout << "Total number of tickets sold: " << num_of_seats << endl;
    cout << "Total petrol price is " << petrol << "For one bus " << endl;
    cout << "Total petrol cost : " << petrol_all_buses << endl;
    cout << "Total income after subtraction of cost:  " << total << endl;
    if (total > 0)
    {
        cout << "You are not in loss" << endl;
        cout << "Keep going on " << endl;
    }
    else
    {
        cout << "ALAS!!!!! You are in loss " << endl;
    }
}

/// user functions

void search_bus_route()
{

    cout << "Enter your route to search the bus:";
    cin.ignore();
    getline(cin, search_route);

    bool search = route_found(search_route);
    if (search == true)
    {
        cout << "The route  :  " << search_route << " is present" << endl;
    }
    else
    {
        cout << "Route Not present" << endl;
    }
}
bool route_found(string search_route)
{
    bool flag;
    for (int i = 0; i < num_of_bus; i++)
    {
        if (routes[i] == search_route)
        {
            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
        return flag;
    }
}

void select_bus()
{
    string serial;
    cout << "\nEnter the serial number of the bus you want to select. ";
    cin >> search_bus_serial_u;
    bool flag = serial_found(search_bus_serial_u);
    if (flag == true)
    {
        cout << "Your bus is selected " << endl;
    }
    else
    {
        cout << "You can't select this bus" << endl;
        select_bus();
    }
}
bool serial_found(string search_bus_serial_u)
{
    bool flag = true;
    for (int i = 0; i < num_of_bus; i++)
    {
        if (buses[i] == search_bus_serial_u)
        {
            flag = true;
            break;
        }
    }
    return flag;
}
void reserve_seat()
{
    cout << "Enter your name  : ";
    cin.ignore();
    getline(cin, buyer_names[buyer_count]);
    cout << "Enter seat number: ";
    cin >> seat_number[buyer_count];
    buyer_count++;
}
void update_seat()
{
    string change_seat, new_seat;

    cout << "Enter seat number to change : ";
    cin >> change_seat;
    if (change_seat_found(change_seat) == true)
    {
        cout << "Enter new seat number: ";
        cin >> new_seat;
        if (new_seat_found(new_seat) == false)
        {
            cout << "This seat is already reserved .";
            cout << "Enter new seat number: ";
            cin >> new_seat;
        }
    }
    else
    {
        cout << "You have not selected this seat " << endl;
    }
    store_customer_data();
}
bool change_seat_found(string change_seat)
{
    for (int i = 0; i < buyer_count; i++)
    {
        if (change_seat == seat_number[i])
        {
            return true;
            break;
        }
        else
        {
            return false;
        }
    }
}
bool new_seat_found(string new_seat)
{
    for (int i = 0; i < buyer_count; i++)
    {
        if (new_seat != seat_number[i])
        {
            return true;
            break;
        }
        else
        {
            return false;
        }
    }
}
void store_customer_data()
{
    fstream file;
    file.open("customers.txt", ios::app);
    for (int i = 0; i < user_count; i++)
    {
        file << buyer_names[i] << endl;
        file << seat_number[i] << endl;

       // buyer_count++;
    }
    file.close();
}

void load_customer_data()
{
    string buyers;
    string tickets;
    fstream file;
    file.open("customers.txt", ios::in);
    while (getline(file, buyers) && (getline(file, tickets)))
    {
        buyer_names[buyer_count] = buyers;
        seat_number[buyer_count] = tickets;

        buyer_count++;
    }
}

void user_details()
{
    cout << "Enter your name: ";
    cin >> user_data;
    cout << "Enter your gender: ";
    cin >> user_gender;
    cout << "Enter your Contact number: ";
    cin >> contact;
    cout << "Here: ";
    getch();
    add_user_to_array();
}
void add_user_to_array()
{
    user_details_arrays[user_count] = user_data;
    user_genders[user_count] = user_gender;
    contacts[user_count] = contact;
    user_count++;
    store_user_details();
}
void store_user_details()
{	
    fstream file;
    file.open("arrays.txt", ios::app);
    for (int i = 0; i < user_count; i++)
    {
        file << user_details_arrays[i] << endl;
        file << user_genders[i] << endl;
        file << contacts[i] << endl;
        //user_count++;
    }
    file.close();
}

void load_users_from_file()
{

    string user_names;
    string user_gender;
    string user_contact;
    fstream file;
    file.open("arrays.txt", ios::in);
    while ((getline(file, user_names) && (getline(file, user_gender)) && (getline(file, user_contact))))
    {
        user_details_arrays[user_count] = user_names;
        user_genders[user_count] = user_gender;
        contacts[user_count] = user_contact;
        user_count++;
    }
    file.close();
}
void payment_seat()
{
    string method;
    float standard = 1500;

    cout << "General fare in rupees to every route " << standard << endl;
    cout << "If you are paying through card then you will avail 5% discount." << endl;
    cout << "Enter your Payment Method (card or cash ) : ";
    cin >> method;
    if (method == "cash")
    {
        pay = standard;
        cout << "Payment Has been Done:  " << pay << endl;
        payments = payments + pay;
    }
    else if (method == "card")
    {
        pay = standard - (standard * 0.05);
        cout << "Payment Has been Done:  " << pay << endl;
        payments = payments + pay;
    }
    else
    {
        cout << "Invalid Method of Payment" << endl;
    }
    
    store_payments(payments);
}
void cancel_seat()
{
    int idx;
    cout << "Enter number of seat to cancel : ";
    cin >> cancelled_seats;
    for (int i = 0; i < no_of_emp; i++)
    {
        if (cancelled_seats == seat_number[i])
        {
            idx = i;
        }
    }
    for (int j = idx; j < no_of_emp; j++)
    {

        buyer_names[j] = buyer_names[j + 1];
        seat_number[j] = seat_number[j + 1];
    }
}
bool cancel_seat_found(string cancelled_seats)
{
    for (int i = 0; i < buyer_count; i++)
    {
        if (cancelled_seats == seat_number[i])
        {
            return true;
            break;
        }
        else
        {
            return false;
        }
    }
}
void refund()
{

    cout << "You can only get 50% refund after departure of bus " << endl;
    int return_money = 1500 - (1500 * 0.5);
    cout << " Amount " << return_money << "  is refunded successfully! " << endl;
    payments = payments - return_money;
}

void view_tickets()
{
    cout << "Name  \t  Seat_Number " << endl;
    for (int i = 0; i < buyer_count; i++)
    {

        cout << buyer_names[i] << "\t\t" << seat_number[i] << " \t  " << endl;
    }
}
void store_payments(int payments)
{
    fstream file;
    file.open("payment.txt" , ios:: out);
    file << payments;
    file.close();
}
void load_payments()
{
    fstream file;
    file.open("payment.txt", ios:: in);
    file >> payments;
}
void user_menu()
{
    int customer = 1;

    while (customer != 0)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int k = 6;
        SetConsoleTextAttribute(hConsole, k);
        cout << endl;
        cout << endl;
        system("cls");
        admin_Header();
        cout << "You are allowed to perform following tasks " << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Press 1 to search bus by route. " << endl;
        cout << "Press 2 to view all buses ." << endl;
        cout << "Press 3 to select bus ." << endl;
        cout << "Press 4 to enter personal details ." << endl;
        cout << "Press 5 to reserve seat ." << endl;
        cout << "Press 6 to update seat. " << endl;
        cout << "Press 7 to pay for your seats." << endl;
        cout << "Press 8 to cancel seat. " << endl;
        cout << "Press 9 to get refund. " << endl;
        cout << "Press 10 to view tickets. " << endl;
        cout << "Press 0 to Exist. " << endl;
        cout << "----------------------------------------------------------------\n\n"
             << endl;
        cout << "Your option : ";
        cin >> customer;

        int l = 2;
        SetConsoleTextAttribute(hConsole, l);
        if (customer == 1)
        {

            search_bus_route();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }

        else if (customer == 2)
        {

            view_buses();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }

        else if (customer == 3)
        {
            select_bus();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (customer == 4)
        {
            user_details();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (customer == 5)
        {
            reserve_seat();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
            user_menu();
        }
        else if (customer == 6)
        {
            update_seat();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (customer == 7)
        {
            payment_seat();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (customer == 8)
        {
            cancel_seat();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (customer == 9)
        {
            refund();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (customer == 10)
        {
            view_tickets();
            cout << endl;
            cout << "Press any key to continue: ";
            getch();
        }
        else if (customer == 0)
        {
            menu();
    	}
    }
}
