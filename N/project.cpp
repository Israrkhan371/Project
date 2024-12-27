#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iomanip>  // For formatting output
using namespace std;

struct Node {
    long long int card_no;
    int pin;
    string name;
    int cash;
    Node *next;
    Node *prev;
};

class ATM {
    Node *head;
    string x;
    long long int y;
    int z;
    int c;

public:
    ATM() {
        head = NULL;
        x = "";
        y = 0;
        z = 0;
        c = 0;
        loadAccountsFromFile();  // Load accounts from file when the ATM is initialized
    }

    // Load accounts from file
    void loadAccountsFromFile() {
        ifstream inFile("accounts.txt");
        if (!inFile) {
            cout << "No previous accounts found, starting with a fresh ATM." << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            Node* newNode = new Node;

            ss >> newNode->name >> newNode->card_no >> newNode->pin >> newNode->cash;
            newNode->next = NULL;
            newNode->prev = NULL;

            if (head == NULL) {
                head = newNode;
            } else {
                Node* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->prev = temp;
            }
        }
        inFile.close();
    }

    // Save accounts to file with a nice formatted table
    void saveAccountsToFile() {
        ofstream outFile("accounts.txt", ios::trunc);
        if (!outFile) {
            cout << "Unable to open file to save accounts!" << endl;
            return;
        }

        // Write headers with some formatting
        outFile << left << setw(20) << "Name" << setw(20) << "Account No" << setw(10) << "Pin" << "Balance" << endl;
        outFile << string(60, '-') << endl; // Add a line to separate headers from the data

        Node* temp = head;
        while (temp != NULL) {
            outFile << left << setw(20) << temp->name
                    << setw(20) << temp->card_no
                    << setw(10) << temp->pin
                    << temp->cash << endl;
            temp = temp->next;
        }
        outFile.close();
    }

    void CreateACC() {
        Node* newer = new Node;
        cout << "  Enter Name: ";
        cin >> x;
        newer->name = x;

        cout << "  Enter Card No: ";
        cin >> y;
        newer->card_no = y;

        cout << "  Enter Pin: ";
        cin >> z;
        newer->pin = z;

        newer->cash = 0;

        newer->next = NULL;

        if (head == NULL) {
            head = newer;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newer;
            newer->prev = temp;
        }

        cout << "Account Created" << endl;
        saveAccountsToFile();  // Save account details to file
    }

    int LOGIN_TO_ACCOUNT() {
        Node* temp = head;
        cout << "  Enter Card No: ";
        cin >> y;

        cout << "  Enter Your PIN: ";
        cin >> z;

        while (temp != NULL) {
            if (temp->card_no == y && temp->pin == z) {
                cout << "***********" << endl;
                cout << "  Name: " << temp->name << endl;
                return 1;  // Successfully logged in
            }
            temp = temp->next;
        }
        cout << "  You Entered Wrong Card No or Pin" << endl;
        return 0;
    }

    void Withdraw() {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->card_no == y && temp->pin == z) {
                cout << "Enter The Amount: ";
                cin >> c;
                if (temp->cash >= c) {
                    temp->cash -= c;
                    cout << "Amount successfully Withdrawn" << endl;
                } else {
                    cout << "You Don't Have Enough Balance To Withdraw" << endl;
                }
                break;
            }
            temp = temp->next;
        }
        saveAccountsToFile();  // Save account details to file after withdrawal
    }

    void Deposit() {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->card_no == y && temp->pin == z) {
                cout << "Enter The Amount: ";
                cin >> c;
                temp->cash += c;
                cout << "Amount successfully Added" << endl;
                break;
            }
            temp = temp->next;
        }
        saveAccountsToFile();  // Save account details to file after deposit
    }

    void Balance_Enquiry() {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->card_no == y && temp->pin == z) {
                cout << "Your Balance is: " << temp->cash << endl;
                break;
            }
            temp = temp->next;
        }
    }

    // This function will print all account details in a structured format
    void PrintAllAccounts() {
        Node* temp = head;

        if (temp == NULL) {
            cout << "No accounts created yet." << endl;
            return;
        }

        cout << "*********** All Accounts Information ***********" << endl;
        cout << left << setw(20) << "Name" << setw(20) << "Account No" << setw(10) << "Pin" << "Balance" << endl;
        cout << string(60, '-') << endl; // Add a line to separate headers from the data
        while (temp != NULL) {
            cout << left << setw(20) << temp->name
                 << setw(20) << temp->card_no
                 << setw(10) << temp->pin
                 << temp->cash << endl;
            temp = temp->next;
        }
    }

    void user_menu() {
        int command;
        bool running = true;

        while (running) {
            cout << "  USER MENU" << endl;
            cout << "  1. Deposit Money" << endl;
            cout << "  2. Withdraw Money" << endl;
            cout << "  3. Check Balance" << endl;
            cout << "  4. Main Menu" << endl;
            cout << "***********" << endl;
            cout << "  Enter the Command: ";
            cin >> command;

            switch (command) {
                case 1:
                    Deposit();
                    break;
                case 2:
                    Withdraw();
                    break;
                case 3:
                    Balance_Enquiry();
                    break;
                case 4:
                    running = false;
                    break;
                default:
                    cout << "  Invalid Command! Please Try Again." << endl;
            }
        }
    }

    void main_menu() {
        int Scommand;
        bool running = true;

        while (running) {
            cout << "***********" << endl;
            cout << "  MAIN MENU" << endl;
            cout << "  1. Create Account" << endl;
            cout << "  2. Login to Account" << endl;
            cout << "  3. Exit" << endl;
            cout << "***********" << endl;
            cout << "  Enter the Command: ";
            cin >> Scommand;

            switch (Scommand) {
                case 1:
                    CreateACC();
                    break;
                case 2:
                    if (LOGIN_TO_ACCOUNT()) {
                        user_menu();
                    }
                    break;
                case 3:
                    cout << "   Thanks For Choosing HBL ATM" << endl;
                    cout << "***********" << endl;
                    running = false;
                    break;
                default:
                    cout << "  Invalid Command! Please Try Again." << endl;
            }
        }
    }
};

int main() {
    ATM cb;

    cout << "***********" << endl;
    cout << "  WELCOME TO THE HBL ATM BANKING      " << endl;
    cout << "***********" << endl;

    cb.main_menu();
    
    // cb.PrintAllAccounts(); 

    return 0;
}
