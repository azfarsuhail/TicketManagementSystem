#include <iostream>
#include <string>
using namespace std;

// Abstract base class for Ticket
class ITicket {
public:
    virtual ~ITicket() {}

    // Abstract functions to be implemented by derived classes
    virtual void cancel() = 0;
    virtual void displayInfo() const = 0;
    virtual int getNumber() const = 0;
    virtual bool isTicketCancelled() const = 0;
};

// Concrete class representing a Ticket
class Ticket : public ITicket {
private:
    int ticketNumber;
    string passengerDetails;
    string seatInfo;
    string departure;
    string destination;
    double price;
    bool isCancelled;

public:
    // Default constructor
    Ticket() : ticketNumber(0), passengerDetails(""), seatInfo(""), departure(""), destination(""), price(0.0), isCancelled(false) {}

    // Parameterized constructor
    Ticket(int ticketNum, const string& passDetails, const string& seat,
           const string& depart, const string& dest, double ticketPrice)
        : ticketNumber(ticketNum), passengerDetails(passDetails), seatInfo(seat),
          departure(depart), destination(dest), price(ticketPrice), isCancelled(false) {}

    // Implementation of virtual functions from ITicket
    void cancel() override {
        isCancelled = true;
    }

    void displayInfo() const override {
        cout << "Ticket Number: " << ticketNumber << endl;
        cout << "Passenger: " << passengerDetails << endl;
        cout << "Seat: " << seatInfo << endl;
        cout << "Departure: " << departure << endl;
        cout << "Destination: " << destination << endl;
        cout << "Price: " << price << " PKR" << endl;
        cout << "Cancelled: " << (isCancelled ? "Yes" : "No") << endl;
        cout << "\n";
    }

    int getNumber() const override {
        return ticketNumber;
    }

    bool isTicketCancelled() const override {
        return isCancelled;
    }
};

// Class representing a Reservation System
class ReservationSystem {
private:
    Ticket* tickets;  // Pointer to the array of tickets
    int numTickets;
    int maxTickets;   // Maximum number of tickets

public:
    // Constructor
    ReservationSystem(Ticket* ticketArray, int maxTickets) : tickets(ticketArray), numTickets(0), maxTickets(maxTickets) {}

    // Function to book a ticket
    void bookTicket(const Ticket& ticket) {
        if (numTickets < maxTickets) {
            tickets[numTickets++] = ticket;
            cout << "Ticket booked successfully." << endl;
        } else {
            cout << "No more tickets can be booked. Ticket limit reached." << endl;
        }
    }

    // Function to get the number of booked tickets
    int getNumTickets() const {
        return numTickets;
    }

    // Function to cancel a ticket by ticket number
    bool cancelTicket(int ticketNumber) {
        for (int i = 0; i < numTickets; ++i) {
            if (tickets[i].getNumber() == ticketNumber) {
                tickets[i].cancel();
                cout << "Ticket cancelled successfully." << endl;
                return true;
            }
        }
        cout << "Ticket not found." << endl;
        return false;
    }

    // Function to get information for a ticket by ticket number
    void getTicketInfo(int ticketNumber) const {
        for (int i = 0; i < numTickets; ++i) {
            if (tickets[i].getNumber() == ticketNumber) {
                tickets[i].displayInfo();
                return;
            }
        }
        cout << "Ticket not found." << endl;
    }

    // Function to display information for available tickets
    void getAvailableTickets() const {
        bool available = false;
        for (int i = 0; i < numTickets; ++i) {
            if (!tickets[i].isTicketCancelled()) {
                available = true;
                break;
            }
        }

        if (available) {
            cout << "Available Tickets:\n";
            for (int i = 0; i < numTickets; ++i) {
                if (!tickets[i].isTicketCancelled()) {
                    tickets[i].displayInfo();
                }
            }
        } else {
            cout << "No available tickets." << endl;
        }
    }
};

// Main function
int main() {
    const int MAX_TICKETS = 2;
    Ticket ticketArray[MAX_TICKETS];
    ReservationSystem reservationSystem(ticketArray, MAX_TICKETS);

    int choice;
    int ticketNumber;

    do {
        cout << "\n1. Book a Ticket\n";
        cout << "2. Cancel a Ticket\n";
        cout << "3. Get Ticket Information\n";
        cout << "4. Get Available Tickets\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        // Input validation
        while (!(cin >> choice) || choice < 0 || choice > 4) {
            cout << "Invalid input. Please enter a number between 0 and 4: ";
            cin.clear();  // Clear input buffer to restore cin to a usable state
            cin.ignore(); 
        }

        switch (choice) {
            case 1: {
                int numTicketsToBook;
                cout << "Enter the number of tickets to book: ";
                while (!(cin >> numTicketsToBook) || numTicketsToBook <= 0) {
                    cout << "Invalid input. Please enter a positive number: ";
                    cin.clear();
                    cin.ignore();
                }

                for (int i = 0; i < numTicketsToBook; ++i) {
                    int ticketNum = reservationSystem.getNumTickets() + 1;
                    string passDetails, seat, depart, dest;
                    double ticketPrice;

                    cout << "\nEnter details for Ticket " << ticketNum << ":\n";
                    cout << "Passenger Name: ";
                    cin.ignore();  // Clear the newline character from the buffer
                    getline(cin, passDetails);

                    cout << "Seat: ";
                    cin >> seat;

                    cout << "Departure: ";
                    cin >> depart;

                    cout << "Destination: ";
                    cin >> dest;

                    cout << "Ticket Price: ";
                    while (!(cin >> ticketPrice) || ticketPrice <= 0) {
                        cout << "Invalid input. Please enter a positive number: ";
                        cin.clear();
                        cin.ignore();
                    }

                    Ticket newTicket(ticketNum, passDetails, seat, depart, dest, ticketPrice);
                    reservationSystem.bookTicket(newTicket);
                }
                break;
            }
            case 2:
                cout << "Enter the ticket number to cancel: ";
                cin >> ticketNumber;
                reservationSystem.cancelTicket(ticketNumber);
                break;
            case 3:
                cout << "Enter the ticket number to get information: ";
                cin >> ticketNumber;
                reservationSystem.getTicketInfo(ticketNumber);
                break;
            case 4:
                reservationSystem.getAvailableTickets();
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

