#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <math.H>
#include <cstring>


using namespace std;


// I use this function to separate pages in command line

void clearScreen(){


    for(int i = 0; i < 100; i++)
        cout << endl;

}


// this get the time from PC
// used for treat an exception (date of flight is in past)

time_t t = time(NULL);
tm* timePtr = localtime(&t);

// a function which says if a number is prime
// necessary for RSA encryption

int isPrime(long int number){

    for(int i = 2; i <= sqrt(number); i++){

        if(number % i == 0)
            return 0;

    }

    return 1;

}

// function for get a string from char array
// necessary to export results after RSA encryption

string convertToString(char* a, int size)
{
    string s(a);
    return s;
}


// class for RSA encryption

class RSA{

private:
    // two prime numbers after which the encryption algorithm will be made.
    int primeNumber1;
    int primeNumber2;
    // n - the modulus of private and public key
    int n;
    // totient function
    int totient;
    // e will storage each public key exponent of each char
    long int e[100] = {0};
    // d will storage each private key exponent of each char
    long int d[100] = {0};
    // temporar storage of ecnrypted chars
    long int temp[100] = {0};
    // message which we want to encrypt
    string message;
    // converse message from string to char array
    char copyMessage[100];
    // result we want to use after using RSA encryption
    string encryptedMessage;
    string decryptedMessage;
    // a vector with prime numbers
    int primeNumbers[13] = {7, 13, 83, 89, 173, 97, 101, 149, 103, 167, 107, 199, 109};
    // generate a random value to choose from prime numbers vector
    int randValue;
    // Encrypted Message & Decrypted Message in char arrays
    char em[100];
    char dm[100];

    long int j;


public:
    RSA(string message){

        this->message = message;
        this->copyMessage[this->message.length()];

        for(int i = 0; i < sizeof(this->message); i++){

            this->copyMessage[i] = this->message[i];

        }

        randValue = rand()%12;
        this->primeNumber1 = primeNumbers[randValue];
        randValue = rand()%12;
        this->primeNumber2 = primeNumbers[randValue];
        if(primeNumber1 == primeNumber2)
            primeNumber2 = primeNumbers[randValue + 1];

        this->n = this->primeNumber1 * this->primeNumber2;
        this->totient = (this->primeNumber1 - 1) * (this->primeNumber2 - 1);


    }

    // function which calculate greatestCommonDivisor beetween a number and totient

    long int greatestCommonDivisor(long int x){

        long int k = 1;
        while(1){

            k = k + this->totient;
            if(k % x == 0)
                return(k / x);

        }

    }

    // get keys for encrypt & decrypt
    // storage to e[] & d[].

    void rsa_key(){

        long int k = 0;
        long int aux;
        long int i;

        for(i = 2; i < this->totient; i++){

            if(this->totient % i == 0)
                continue;

            aux = isPrime(i);

            if(aux == 1 && i != this->primeNumber1 && i != this->primeNumber2){

                this->e[k] = i;
                aux = greatestCommonDivisor(this->e[k]);

                if(aux > 0){
                    this->d[k] = aux;
                    k++;
                }

                if(k == 99)
                    break;

            }
        }

    }

    void encrypt(){

        // The character in the message
        // we will process its ASCII code
        long int charFromM;
        // char - we will put its ASCII code in Encrypted Message
        long int charToEM;
        long int key = e[0];
        long int k;
        long int i = 0;


        long int length = strlen(this->copyMessage);

        while(i != length){

            charFromM = this->copyMessage[i];
            charFromM = charFromM - 50;
            k = 1;

            for(j = 0; j < key; j++){

                k = k * charFromM;
                k = k % this->n;

            }

            this->temp[i] = k;
            charToEM = k + 50;
            this->em[i] = charToEM;
            i++;
        }
        this->em[i] = -1;
        this->encryptedMessage = convertToString(em, i-1);

    }


    void decrypt(){

        long int charToDM;
        long int charFromEM;
        long int key = this->d[0];
        long int k;
        long int i = 0;


        while(this->em[i] != -1){

            charFromEM = temp[i];
            k = 1;

            for(j = 0; j < key; j++){

                k = k * charFromEM;
                k = k % this->n;

            }

            charToDM = k + 50;
            this->dm[i] = charToDM;
            i++;
        }

        this->decryptedMessage = convertToString(dm, i - 1);
    }

    // getters

    void getPrime1(){

        cout << this->primeNumber1;

    }

    void getPrime2(){

        cout << this->primeNumber2;

    }

    string getEncryptedMessage(){

        return this->encryptedMessage;

    }

    string getDecryptedMessage(){

        return this->decryptedMessage;

    }

    void getEm(){

        for(int i = 0; em[i] != -1; i++){

            cout << em[i] << " ";

        }

    }

    void getDm(){

        for(int i = 0; dm[i] != -1; i++){

            cout << dm[i] << " ";

        }

    }

};

// Application Interface

class Application{


public:

    void appOpen(){

        cout << "Welecome to our Flights Application!" << endl;

    }

    void appExit(){

        exit(1);

    }

    void appMenu();

};

// Flights

class Flights{

private:

    int flightID;

// For departure information
    string countryOfDeparture;
    int departureYear;
    int departureMonth;
    int departureDay;
    int departureHour;
    int departureMinute;

// For arrival information
    string countryOfArrival;
    int arrivalYear;
    int arrivalMonth;
    int arrivalDay;
    int arrivalHour;
    int arrivalMinute;

// Flight info
    int numberOfSeats;
    int numberOfReservedSeats;

public:

    static int counterID;

// constructors

    Flights(){

        flightID = counterID++;

        this->countryOfDeparture = "Unknown";
        this->departureYear = 0;
        this->departureMonth = 0;
        this->departureDay = 0;
        this->departureHour = 0;
        this->departureMinute = 0;

        this->countryOfArrival = "Unknown";
        this->arrivalYear = 0;
        this->arrivalMonth = 0;
        this->arrivalDay = 0;
        this->arrivalHour = 0;
        this->arrivalMinute = 0;

        this->numberOfSeats = 0;
        this->numberOfReservedSeats = 0;

    }

    Flights(string countryOfDeparture, int departureYear, int departureMonth, int departureDay, int departureHour, int departureMinute,
            string countryOfArrival, int arrivalYear, int arrivalMonth, int arrivalDay, int arrivalHour, int arrivalMinute,
            int numberOfSeats, int numberOfReservedSeats){

        flightID = counterID++;

        this->countryOfDeparture = countryOfDeparture;
        this->departureYear = departureYear;
        this->departureMonth = departureMonth;
        this->departureDay = departureDay;
        this->departureHour = departureHour;
        this->departureMinute = departureMinute;

        this->countryOfArrival = countryOfArrival;
        this->arrivalYear = arrivalYear;
        this->arrivalMonth = arrivalMonth;
        this->arrivalDay = arrivalDay;
        this->arrivalHour = arrivalHour;
        this->arrivalMinute = arrivalMinute;

        this->numberOfSeats = numberOfSeats;
        this->numberOfReservedSeats = numberOfReservedSeats;

    }

// setters


    void setCountryOfDeparture(string countryOfDeparture){

        this->countryOfDeparture = countryOfDeparture;

    }

    void setDepartureYear(int departureYear){

        this->departureYear = departureYear;

    }

    void setDepartureMonth(int departureMonth){

        this->departureMonth = departureMonth;

    }

    void setDepartureDay(int departureDay){

        this->departureDay = departureDay;

    }

    void setDepartureHour(int departureHour){

        this->departureHour = departureHour;

    }

    void setDepartureMinute(int departureMinute){

        this->departureMinute = departureMinute;

    }

    void setCountryOfArrival(string countryOfArrival){

        this->countryOfArrival = countryOfArrival;

    }

    void setArrivalYear(int arrivalYear){

        this->arrivalYear = arrivalYear;

    }

    void setArrivalMonth(int arrivalMonth){

        this->arrivalMonth = arrivalMonth;

    }

    void setArrivalDay(int arrivalDay){

        this->arrivalDay = arrivalDay;

    }

    void setArrivalHour(int arrivalHour){

        this->arrivalHour = arrivalHour;

    }

    void setArrivalMinute(int arrivalMinute){

        this->arrivalMinute = arrivalMinute;

    }

    void setNumberOfSeats(int numberOfSeats){

        this->numberOfSeats = numberOfSeats;

    }

    void setNumberOfReservedSeats(int numberOfReservedSeats){

        this->numberOfReservedSeats = numberOfReservedSeats;

    }

// getters

    int getFlightID(){

        return this->flightID;

    }

    string getCountryOfDeparture(){

        return this->countryOfDeparture;

    }

    int getDepartureYear(){

        return this->departureYear;

    }

    int getDepartureMonth(){

        return this->departureMonth;

    }

    int getDepartureDay(){

        return this->departureDay;

    }

    int getDepartureHour(){

        return this->departureHour;

    }

    int getDepartureMinute(){

        return this->departureMinute;

    }

    string getCountryOfArrival(){

        return this->countryOfArrival;

    }

    int getArrivalYear(){

        return this->arrivalYear;

    }

    int getArrivalMonth(){

        return this->arrivalMonth;

    }

    int getArrivalDay(){

        return this->arrivalDay;

    }

    int getArrivalHour(){

        return this->arrivalHour;

    }

    int getArrivalMinute(){

        return this->arrivalMinute;

    }

    int getNumberOfSeats(){

        return this->numberOfSeats;

    }

    int getNumberOfReservedSeats(){

        return this->numberOfReservedSeats;

    }

// methods

    void getAllFlightInfo(){

        cout << "[ " << getFlightID() << " Depart of: " << getCountryOfDeparture() << ", Arrive in: " << getCountryOfArrival();
        cout << ", depart at " << getDepartureYear() << "-" << getDepartureMonth() << "-" << getDepartureDay() << " ";
        cout << getDepartureHour() << ":" << getDepartureMinute();

        cout << ", arrive at " << getArrivalYear() << "-" << getArrivalMonth() << "-" << getArrivalDay() << " ";
        cout << getArrivalHour() << ":" << getArrivalMinute();

        cout << ", number of seats: " << getNumberOfSeats() << ", of which reserved " << getNumberOfReservedSeats() << " ]";
        cout << endl;

    }

    friend class Operator;
};

int Flights::counterID = 0;
vector<Flights> listOfFlights;


// Interface for methods which we will use for Operators & Users

class ManageFlights{

public:

    void addFlight();
    void removeFlight();
    void searchFlight();
    void reserveFlight();
    void cancelReservation();
    void showAllFlights();

};



class Operator : public ManageFlights{

private:
    string username;
    string password;

public:

    friend class FirstMenu;
    //friend class OperatorSpace;

    Operator(){

        this->username = "admin";
        this->password = "admin";

    }


    int operatorLogin(){

        string usernameInput;
        string passwordInput;
        int authorizeStatus = 0;

        cout << "Enter your username: "; cin >> usernameInput;
        cout << "Enter your password: "; cin >> passwordInput;

        if(this->username == usernameInput && this->password == passwordInput){
            authorizeStatus = 1;
        }

        return authorizeStatus;

    }

    void operatorAcces(){


        try{

            int validateLogin = operatorLogin();

            if(validateLogin){

                cout << "You Have Successfully Logged in your Operator Account.";
                cout << endl;
                cout << "Type any button to continue.";
                cin.get();
                clearScreen();
                operatorProfile();

            }
            else
                throw validateLogin;
        }

        catch(int e){

            cout << "Username or password is incorrect." << endl;
            cout << "Retry." << endl;
            operatorAcces();

        }

        catch(...){

            cout << "Error!" << endl;
            operatorAcces();

        }


    }

    void addFlight(){

        Flights flight;

        int aux_int;
        string aux_st;
        int ok = 1;


        cout << "Enter Flight Details: " << endl;
        try {
            cout << "Departure Country: ";
            cin >> aux_st;

            char upperL;

            for(int i = 0; i < aux_st.size(); i++){

                upperL = toupper(aux_st[i]);
                if(upperL < 'A' || upperL > 'Z'){
                    ok = 0;
                    break;
                }


            }

            if(ok)
                flight.setCountryOfDeparture(aux_st);
            else
                throw upperL;
        }
        catch(char e){
            cout << "Error! The name of Country must contains only letters!" << endl;
            cout << "Re-enter data!" << endl;
            addFlight();
        }
        catch(...){
                cout << "Error! The name of Country must contains only letters!" << endl;
        }
        try{
            cout << "Arrival Country: "; cin >> aux_st;

            char upperL;

            for(int i = 0; i < aux_st.size(); i++){

                upperL = toupper(aux_st[i]);
                if(upperL < 'A' || upperL > 'Z'){
                    ok = 0;
                    break;
                }


            }

            if(ok)
                flight.setCountryOfArrival(aux_st);
            else
                throw upperL;
        }
        catch(char e){
            cout << "Error! The name of Country must contains only letters!" << endl;
            cout << "Re-enter data!" << endl;
            addFlight();
        }
        catch(...){
            cout << "Error!" << endl;
        }


        try{
            cout << "Departure Year: "; cin >> aux_int;

            if(timePtr->tm_year + 1899 > aux_int)
                throw aux_int;
            else
                flight.setDepartureYear(aux_int);
        }
        catch(int e){

            cout << "Error! This year was in past!" << endl;
            cout << "Re-enter data!" << endl;
            addFlight();

        }
        catch(...){
            cout << "Error!" << endl;
        }

        cout << "Departure Month: "; cin >> aux_int; flight.setDepartureMonth(aux_int);
        cout << "Departure Day: "; cin >> aux_int; flight.setDepartureDay(aux_int);
        cout << "Departure Hour: "; cin >> aux_int; flight.setDepartureHour(aux_int);
        cout << "Departure Minute: "; cin >> aux_int; flight.setDepartureMinute(aux_int);
        cout << "Arrival Year: "; cin >> aux_int; flight.setArrivalYear(aux_int);
        cout << "Arrival Month: "; cin >> aux_int; flight.setArrivalMonth(aux_int);
        cout << "Arrival Day: "; cin >> aux_int; flight.setArrivalDay(aux_int);
        cout << "Arrival Hour: "; cin >> aux_int; flight.setArrivalHour(aux_int);
        cout << "Arrival Minute: "; cin >> aux_int; flight.setArrivalMinute(aux_int);
        cout << "Number of seats: "; cin >> aux_int; flight.setNumberOfSeats(aux_int);
        cout << "Reserved seats: "; cin >> aux_int; flight.setNumberOfReservedSeats(aux_int);

        listOfFlights.push_back(flight);

    }

    void searchFlight(){

        int choise;
        int input_int;
        basic_string<char> input_str;

        cout << "Search by: " << endl;
        cout << "[ 1 ] Flight ID" << endl;
        cout << "[ 2 ] Departure Country" << endl;
        cout << "[ 3 ] Arrival Country" << endl;
        cout << "Your choise: "; cin >> choise;

        switch(choise){

            case 1:
                cout << "Enter Flight ID: ";
                cin >> input_int;
                for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i){
                    if(i->getFlightID() == input_int){
                        i->getAllFlightInfo();
                    }
                }
                break;

            case 2:
                cout << "Enter Country of Departure: ";
                cin >> input_str;
                for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i){
                    if(i->getCountryOfDeparture() == input_str){
                        i->getAllFlightInfo();
                    }
                }
                break;

            case 3:
                cout << "Enter Country of Arrival: ";
                cin >> input_str;
                for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i){
                    if(i->getCountryOfArrival() == input_str){
                        i->getAllFlightInfo();
                    }
                }
                break;

            default:
                cout << "Invalid option.";


        }

    }

    void showAllFlights() {

        for (auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i) {
            i->getAllFlightInfo();

        }
    }


    void removeFlight(){

        int input_int;
        int ok = 0;

        cout << "Enter the Flight ID of the flight you want to remove: ";
        cin >> input_int;

        auto pos = listOfFlights.begin();
        for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i){
            if(i->getFlightID() == input_int){
                pos = i;
                ok = 1;
            }
        }

        if(ok)
            listOfFlights.erase(pos);

    }



    void operatorProfile(){

        cout << endl << "Welcome to your profile!" << endl;
        cout << "You are an operator!" << endl;
        cout << endl;
        cout << "[ 1 ] Show all Flights" << endl;
        cout << "[ 2 ] Add a flight" << endl;
        cout << "[ 3 ] Search a flight" << endl;
        cout << "[ 4 ] Remove a flight" << endl;
        cout << "[ 5 ] Exit" << endl;



        int choise;

        cout << "Choose your operation: "; cin >> choise;

        switch(choise){

            case 1:
                showAllFlights();
                cout << "Type any button to return ";
                cin.get();
                cin.get();
                operatorProfile();

            case 2:
                addFlight();
                cout << "Flight added! Type any button to return ";
                cin.get();
                cin.get();
                operatorProfile();

            case 3:
                searchFlight();
                cout << "Type any button to return ";
                cin.get();
                cin.get();
                operatorProfile();

            case 4:
                removeFlight();
                cout << "Flight removed! Type any button to return ";
                cin.get();
                cin.get();
                operatorProfile();

            case 5:
                exit(5);

            default:
                cout << "Invalid choise. Try again!" << endl;
                operatorProfile();
        }

    }

};


class User : public ManageFlights{

private:
    int userID;
    string username;
    string mail;
    int yearOfBirth;
    string password;
    string decryptedPassword;

public:

    static int counterUserID;

    User(){

        userID = counterUserID++;
        this->username = "0";
        this->mail = "0";
        this->yearOfBirth = 0;
        this->password = "0";
        this->decryptedPassword = "0";

    }

    User(string username, string mail, int yearOfBirth, string password, string decryptedPassword){

        userID = counterUserID++;
        this->username = username;
        this->mail = mail;
        this->yearOfBirth = yearOfBirth;
        this->password = password;
        this->decryptedPassword = decryptedPassword;

    }

// setters

    void setUsername(string username){

        this->username = username;

    }

    void setMail(string mail){

        this->mail = mail;

    }

    void setYearOfBirth(int yearOfBirth){

        this->yearOfBirth = yearOfBirth;

    }

    void setPassword(string password){

        this->password = password;

    }

// getters

    int getUserID(){

        return this->userID;

    }

    string getUsername(){

        return this->username;

    }

    string getMail(){

        return this->mail;

    }

    int getYearOfBirth(){

        return this->yearOfBirth;

    }

    string getPassword(){

        return this->password;

    }

    string getDecryptedPassword(){

        return this->decryptedPassword;

    }

    void getAllUserInfo(){

        cout << "[ UserID [ " << getUserID() << " ], username: " << getUsername() << ", mail: " << getMail()
        << ", born in " << getYearOfBirth() << ", password: " << getPassword() << ", decrypted password: " << getDecryptedPassword() << " ]" << endl;

    }

// methods

    void userProfile(int userLoggedID);
    void userLogin();
    void showAllFlights();
    void searchFlight();
    void reserveFlight();
    void cancelReservation();
    void myTickets();

    friend class Application;

};
int User::counterUserID = 0;
vector<User> listOfUsers;

void User::showAllFlights() {

    for (auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i) {
        i->getAllFlightInfo();

    }
}

void User::searchFlight() {

    int choise;
    int input_int;
    basic_string<char> input_str;

    cout << "Search by: " << endl;
    cout << "[ 1 ] Flight ID" << endl;
    cout << "[ 2 ] Departure Country" << endl;
    cout << "[ 3 ] Arrival Country" << endl;
    cout << "Your choise: "; cin >> choise;

    switch(choise){

        case 1:
            cout << "Enter Flight ID: ";
            cin >> input_int;
            for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i){
                if(i->getFlightID() == input_int){
                    i->getAllFlightInfo();
                }
            }
            break;

        case 2:
            cout << "Enter Country of Departure: ";
            cin >> input_str;
            for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i){
                if(i->getCountryOfDeparture() == input_str){
                    i->getAllFlightInfo();
                }
            }
            break;

        case 3:
            cout << "Enter Country of Arrival: ";
            cin >> input_str;
            for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i){
                if(i->getCountryOfArrival() == input_str){
                    i->getAllFlightInfo();
                }
            }
            break;

        default:
            cout << "Invalid option.";

    }


}

class Ticket : public Flights{

private:
    int ticketID;
    int userTicketID;
    int flightTicketID;
    string userTicketName;
    string ticketCountryOfDeparture;
    string ticketCountryOfArrival;
    int ticketSeat;

public:
    static int counterTicketID;

    Ticket(int userTicketID, int flightTicketID, string userTicketName, string ticketCountryOfDeparture, string ticketCountryOfArrival, int ticketSeat){

        this->ticketID = counterTicketID++;
        this->userTicketID = userTicketID;
        this->flightTicketID = flightTicketID;
        this->userTicketName = userTicketName;
        this->ticketCountryOfDeparture = ticketCountryOfDeparture;
        this->ticketCountryOfArrival = ticketCountryOfArrival;
        this->ticketSeat = ticketSeat;

    }

    int getTicketID(){

        return this->ticketID;

    }

    int getUserTicketID(){

        return this->userTicketID;

    }

    int getFlightTicketID(){

        return this->flightTicketID;

    }

    string getUserTicketName(){

        return this->userTicketName;

    }

    string getTicketCountryOfDeparture() {

        return this->ticketCountryOfDeparture;

    }

    string getTicketCountryOfArrival() {

        return this->ticketCountryOfArrival;

    }

    int getTicketSeat(){

        return this->ticketSeat;

    }

    void getAllTicketInfo(){

        cout << "[ Ticket ID: [ " << getTicketID() << " ] for user: [ " << getUserTicketID() << " ] " << getUserTicketName();
        cout << ", fly from " << getTicketCountryOfDeparture() << " to " << getTicketCountryOfArrival() << ", seat: " << getTicketSeat() << " ]" << endl;

    }

};


int Ticket::counterTicketID = 0;
vector<Ticket> tickets;

void User::reserveFlight() {

    int input_ID;
    int validate = 0;

    try{
        cout << "Warning! ID must be a number!" << endl;
        cout << "Enter ID of flight you want to reserve: ";
        cin >> input_ID;
        for (auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i) {
            if (i->getFlightID() == input_ID) {
                validate = 1;
                if (i->getNumberOfReservedSeats() != i->getNumberOfSeats()) {
                    i->setNumberOfReservedSeats(i->getNumberOfReservedSeats() + 1);
                    Ticket ticket(getUserID(), i->getFlightID(), getUsername(), i->getCountryOfDeparture(),
                                  i->getCountryOfArrival(), i->getNumberOfSeats() - i->getNumberOfReservedSeats());
                    tickets.push_back(ticket);
                    cout << "Flight reserved! You can see your ticket on section My Tickets" << endl;
                } else
                    cout << "All seats are taken" << endl;
            }
        }
        if(validate == 0){
            throw validate;
        }
    }
    catch(int e){

        cout << "This flight doesnt exists! Try again." << endl;
        reserveFlight();

    }
    catch(...){
        cout << "Error!" << endl;
        reserveFlight();
    }

}

void User::cancelReservation() {

    int input_ID;
    int ok = 0;

    auto pos = tickets.begin();
    cout << "Enter ID of flight you want to cancel reservation: "; cin >> input_ID;
    for(auto i = tickets.begin(); i != tickets.end(); ++i){

        if(i->getTicketID() == input_ID){

            pos = i;
            ok = 1;

        }

    }

    if(ok){
        tickets.erase(pos);
    }


}

void User::myTickets() {

    for(auto i = tickets.begin(); i != tickets.end(); ++i){

        if(i->getUserTicketID() == getUserID())
            i->getAllTicketInfo();

    }

}

void User::userProfile(int userLoggedID) {

    auto currentUser = listOfUsers.begin();
    for(auto i = listOfUsers.begin(); i != listOfUsers.end(); ++i){

        if(userLoggedID == i->getUserID())
            currentUser = i;

    }
    cout << "Welcome, " << currentUser->getUsername() << "!" << endl;
    cout << "You are an user!" << endl << endl;
    cout << "[ 1 ] Show All Flights" << endl;
    cout << "[ 2 ] Search a flight" << endl;
    cout << "[ 3 ] Reserve a flight" << endl;
    cout << "[ 4 ] Cancel a reservation" << endl;
    cout << "[ 5 ] Show my Tickets" << endl;
    cout << "[ 6 ] Exit" << endl;

    int choise;
    cout << "Choose your operation: "; cin >> choise;

    switch(choise){

        case 1:
            currentUser->showAllFlights();
            cout << "Press any button to continue ";
            cin.get();
            cin.get();
            userProfile(userLoggedID);

        case 2:
            currentUser->searchFlight();
            cout << "Press any button to continue ";
            cin.get();
            cin.get();
            userProfile(userLoggedID);

        case 3:
            currentUser->reserveFlight();
            cout << "Press any button to continue ";
            cin.get();
            cin.get();
            userProfile(userLoggedID);

        case 4:
            currentUser->cancelReservation();
            cout << "Press any button to continue ";
            cin.get();
            cin.get();
            userProfile(userLoggedID);

        case 5:
            currentUser->myTickets();
            cout << "Press any button to continue ";
            cin.get();
            cin.get();
            userProfile(userLoggedID);

        case 6:
            exit(6);

        default:
            cout << "Invalid input. Try again." << endl;
            userProfile(userLoggedID);
    }


}

void User::userLogin() {

    Application a;
    string usernameInput;
    string passwordInput;
    int validateLogin = 0;
    int userLoggedID;

    cout << "Username: "; cin >> usernameInput;
    cout << "Password: "; cin >> passwordInput;

    try {

        for (auto i = listOfUsers.begin(); i != listOfUsers.end(); ++i) {
            if (i->getUsername() == usernameInput && i->getDecryptedPassword() == passwordInput) {
                validateLogin = 1;
                userLoggedID = i->getUserID();
            }
            if (validateLogin)
                break;
        }

        if(validateLogin){
            clearScreen();
            userProfile(userLoggedID);
        }
        else
            throw validateLogin;

    }
    catch(int e){

        cout << "Username or password is incorrect.";
        cout << endl << "Retry." << endl;
        userLogin();

    }
    catch(...){

        cout << "Error!" << endl;
        userLogin();

    }
}

class Registration : public User{

private:
    string usernameInput;
    string mailInput;
    int yearOfBirthInput;
    string passwordInput;

public:
    void createAccount(){


        string aux_st;
        int validatePassword = 0;
        int validateMail_arrond = 0;
        int validateMail_dot = 0;
        int validatePasswordUpperL = 0;
        int validatePasswordSymbol = 0;
        string encryptedPassword;
        string decryptedPassword;

        cout << "To register, complete the following information: " << endl;
        cout << "Username: "; cin >> usernameInput;
        try {
            cout << "Mail adress: ";
            cin >> mailInput;

            for(int i = 0; i < mailInput.length(); i++){

                if(mailInput[i] == '@')
                    validateMail_arrond = 1;
                if(mailInput[i] == '.')
                    validateMail_dot = 1;

                if(validateMail_arrond == 1 && validateMail_dot == 1)
                    break;
            }

            if(validateMail_arrond != 1 || validateMail_dot != 1)
                throw validateMail_dot;
        }
        catch (int e){

            cout << "Invalid mail address. Retry!" << endl;
            createAccount();

        }
        catch (...){

            cout << "Error!" << endl;
            createAccount();

        }
        cout << "Year of Birth: "; cin >> yearOfBirthInput;

        try{
            cout << "Passowrd: "; cin >> passwordInput;
            for(int i = 0; i < passwordInput.length(); i++){
                if(passwordInput[i] > 'A' && passwordInput[i] < 'Z')
                    validatePasswordUpperL = 1;

                if(passwordInput[i] < 'A' || passwordInput[i] > 'z')
                    validatePasswordSymbol = 1;
            }

            if(validatePasswordSymbol == 0 || validatePasswordUpperL == 0){
                throw validatePasswordUpperL;
            }
        }
        catch (int e){

            cout << "Password must contains a Upper Letter and a Non-Letter Character!" << endl;
            cout << "Retry." << endl;
            createAccount();

        }
        catch (...){

            cout << "Error." << endl;
            createAccount();

        }

        try{

            cout << "Confirm your password: "; cin >> aux_st;
            if(passwordInput == aux_st)
                validatePassword = 1;

            if(validatePassword == 1){

                RSA rsa(passwordInput);
                rsa.rsa_key();
                rsa.encrypt();
                encryptedPassword = rsa.getEncryptedMessage();
                rsa.decrypt();
                decryptedPassword = rsa.getDecryptedMessage();


                cout << endl << "---" << passwordInput << "----" << decryptedPassword << "----" << endl;

                User user(usernameInput, mailInput, yearOfBirthInput, encryptedPassword, decryptedPassword);
                listOfUsers.push_back(user);

            }
            else
                throw validatePassword;
        }

        catch (int e){

            cout << "Passwords do not match." << endl;
            cout << "Retry." << endl;
            createAccount();

        }

        catch (...){

            cout << "Error." << endl;
            createAccount();

        }

        for(auto i = listOfUsers.begin(); i != listOfUsers.end(); ++i) i->getAllUserInfo();



    }


};



class FirstMenu : public Registration {

private:
    int status;

public:

    Application a;
    User u;
    Registration r;
    Operator o;


    /*FirstMenu(){

        Operator admin("admin", "admin");

    }*/


    /*void gotoOperatorSpace(Operator o){

        o.operatorAcces();

    } */



    void appMenu(){

        cout << "[ 1 ] Login" << endl;
        cout << "[ 2 ] Create an account" << endl;
        cout << "[ 3 ] Operator login" << endl;
        cout << "[ 4 ] Exit" << endl;
        cout << "Choose your option: ";

        int choise;

        cin >> choise;

        switch (choise) {

            case 1:
                u.userLogin();
                break;

            case 2:
                r.createAccount();
                appMenu();
                break;

            case 3:
                o.operatorAcces();
                break;

            case 4:
                exit(4);

            default:
                cout << "Invalid choise. Try again!" << endl;
                a.appOpen();
                appMenu();
        }



    }


};




int main() {


    User user;
    listOfUsers.push_back(user);

    Flights zbor("Franta", 2022, 1, 3, 10, 14, "USA", 2021, 1, 4, 2, 37, 7, 7);
    //zbor.getAllFlightInfo();

    Flights zbor1("Romania", 2021, 12, 13, 16, 30, "Bulgaria", 2021, 12, 13, 18, 20, 10, 2);
    //zbor1.getAllFlightInfo();
    Flights zbor2("Japonia", 2021, 12, 28, 14, 20, "Germania", 2021, 12, 29, 21, 29, 30, 18);

    listOfFlights.push_back(zbor);
    listOfFlights.push_back(zbor1);
    listOfFlights.push_back(zbor2);

    Application app;
    app.appOpen();

    FirstMenu menu;
    menu.appMenu();



    //Operator admin("admin", "admin");
    //admin.operatorAcces();

    //for(auto i = listOfFlights.begin(); i != listOfFlights.end(); ++i) i->getAllFlightInfo();



    //for(auto i = listOfUsers.begin(); i != listOfUsers.end(); ++i) cout << i->getUsername();


    return 0;
}
