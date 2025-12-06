#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

int createNewAccount() {
    string accountHolder, TYPE, password;
    double balance;
    long int Phone;

    cout << "Enter account holder's name: ";
    cin.ignore();
    getline(cin, accountHolder);

    cout << "Enter account TYPE: ";
    cin >> TYPE;

    cout << "Enter account holder's Phone number: ";
    cin >> Phone;

    cout << "Enter password: ";
    cin >> password;

    cout << "Enter initial balance: $";
    cin >> balance;

    ofstream outFile("accounts.txt", ios::out);
    if (outFile.is_open()) {
        outFile << "Account holder's name: " << accountHolder << endl
                << "\nAccount TYPE: " << TYPE << endl
                << "\nAccount holder's Phone number: " << Phone << endl
                << "\nInitial balance: $" << balance << endl
                << "\nPassword: " << password << "@";
        outFile.close();
        cout << "\nAccount created and stored in file successfully.\n";
    } else {
        cout << "\nError: Unable to open file.\n";
    }

    ifstream inFile("accounts.txt", ios::in);
    if (!inFile.is_open()) {
        cout << "Error: Unable to open the file." << endl;
        return 0;
    }

    cout << "-----Data present in the file -----\n";
    string line;
    while (getline(inFile, line) && line != "@") {
        cout << line << endl;
    }

    inFile.close();
    return 0;
}

class Account {
public:
    string accountHolder;
    double balance;
    string accountType;
    int accountID;

    Account(string a, int c, double b) {
        accountHolder = a;
        balance = b;
        accountID = c;
    }

    void display(Account& b1, Account& b2, Account& b3) {
        cout << "\n********************************************\n";
        cout << "*                                          *\n";
        cout << "  *      Welcome to the ATM, " << accountHolder << "        *\n";
        cout << "*                                          *\n";
        cout << "********************************************\n\n";

        cout << "Welcome - " << accountHolder << "!" << endl;
        cout << "\nPress Enter to proceed\n";
        cin.ignore();
        cin.get();
        cout << "\n----- ACCOUNT TYPE MENU -----" << endl << endl;
        cout << "1. Domestic Account";
        cout << "\t2. International Account(Not available)" << endl;
        cout << "\nEnter your choice: ";
        int accountChoice;
        cin >> accountChoice;
        switch (accountChoice) {
        case 1:
            domesticAccount(b1, b2, b3);
            break;
        case 2:
            cout << "\nInternational account not available.";
            cout << "\nPress Tab to take your card." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    void domesticAccount(Account& b1, Account& b2, Account& b3) {
        cout << "\nYou have selected Domestic Account." << endl;
        accountType = "Savings Account";
        int accountChoice;
        cout << "\n1. Savings Account";
        cout << "\t2. Current Account (Not Available)" << endl;
        cout << "\nEnter your choice: ";
        cin >> accountChoice;
        switch (accountChoice) {
        case 1:
            cout << "\nYou have selected Savings Account." << endl;
            savingsAccount(b1, b2, b3);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    void savingsAccount(Account& b1, Account& b2, Account& b3) {
        while (true) {
            int choice;
            cout << "***********  " << accountHolder << "-" << accountType << "  ***********" << endl;
            cout << "--------------------------------------------\n";
            cout << "|               ATM MENU                  |\n";
            cout << "--------------------------------------------\n";
            cout << "| 1. Withdraw                             |\n";
            cout << "| 2. Deposit                              |\n";
            cout << "| 3. Balance Enquiry                      |\n";
            cout << "| 4. Transfer Money                       |\n";
            cout << "| 5. Exit                                 |\n";
            cout << "--------------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                long double withdrawAmount;
                cout << "Enter withdrawal amount: $";
                cin >> withdrawAmount;
                withdraw(withdrawAmount);
                break;
            case 2:
                long double depositAmount;
                cout << "Enter deposit amount: $";
                cin >> depositAmount;
                deposit(depositAmount);
                break;
            case 3:
                cout << "Your current balance is $" << balance << endl;
                cout << "Press Enter to proceed\n";
                cin.ignore();
                cin.get();
                break;
            case 4:
                transferMoney(b1, b2, b3);
                break;
            case 5:
                cout << "Thanks and have a great day!" << endl;
                cout << "Press Tab to take your card." << endl;
                return;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }

    bool checkWithdraw(double amount) {
        const double minimumBalance = 100.0;
        if (balance - amount >= minimumBalance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    void deposit(long double dp) {
        balance += dp;
        cout << "Deposit successful." << endl;
        printReceipt("\nAmount deposited", dp);
    }

    void withdraw(double wd) {
        if (checkWithdraw(wd)) {
            cout << "Withdrawal successful." << endl;
            printReceipt("\nAmount withdrawn", wd);
        } else {
            cout << "Insufficient funds or violating minimum balance requirement." << endl;
        }
    }

    void transferMoney(Account& b1, Account& b2, Account& b3) {
        double transferAmount;
        cout << "Enter transfer amount: $";
        cin >> transferAmount;

        int recipientAccountNumber;
        cout << "1. Kishore " << endl;
        cout << "2. Hari " << endl;
        cout << "3. Dhanis " << endl;
        cout << "Enter recipient account number: ";
        cin >> recipientAccountNumber;

        switch (recipientAccountNumber) {
        case 1:
            transfer(transferAmount, b1);
            break;
        case 2:
            transfer(transferAmount, b2);
            break;
        case 3:
            transfer(transferAmount, b3);
            break;
        default:
            cout << "Invalid recipient account number." << endl;
            break;
        }
    }

    void transfer(double amount, Account& r) {
        if (amount <= balance) {
            balance -= amount;
            r.balance = r.balance + amount;
            cout << "Transfer successful.\n" ;
            cout << "You transferred Rs." << amount << " From " << accountHolder << " to " << r.accountHolder ;
            //cout << r.accountHolder << " \nBalance for - " << r.balance;

            
            char receiptChoice;
            cout << "\nDo you want a detailed receipt? (Y/N): ";
            cin >> receiptChoice;
            if (receiptChoice == 'Y' || receiptChoice == 'y') {
                printReceipt("Amount transferred", amount);
            } else {
                cout << "\nThank you for your transaction." ;
                cout << "Press Enter to proceed\n";
                cin.ignore();
                cin.get();
            }
        } else {
            cout << "Transfer failed. Insufficient funds." << endl;
        }
    }

    void printReceipt(const string& transactionType, double amount) {
        cout << "\n*******************************************\n";
        cout << "\tATM TRANSACTION RECEIPT\n";
        cout << " \n*******************************************\n";
        cout << "\nAccount Holder: " << accountHolder << endl;
        cout << "\nAccount Type: " << accountType << endl;
        cout << transactionType << ": Rs." << amount << endl;
        cout << "\nCurrent Balance: Rs." << balance << endl;
        cout << "\nTransaction Date & Time: " << __DATE__ << " " << __TIME__ << endl;
        cout << "\n*********************************************\n";
        cout << "End of Transaction\n";
        cout << "Press Enter to proceed\n";
        cin.ignore();
        cin.get();
    }
};

int main() {
    Account a1("Kishore", 101, 1000.0);
    Account a2("Hari", 102, 2000.0);
    Account a3("Dhanis", 103, 3000.0);
    string insertedCard;
    string enteredPin;
    int createAccountChoice;

    cout << "\nDo you want to create a new account?\n";
    cout << "1. Yes (create New Account)\n";
    cout << "2. No (Already Available)\n";
    cout << "Enter your choice: ";
    cin >> createAccountChoice;

    if (createAccountChoice == 1) {
        createNewAccount();
        return 0;
    }

    cout << "Press Enter to insert your card." << endl;
    getline(cin, insertedCard);

    cout << "Enter your PIN: ";
    cin >> enteredPin;

    if (enteredPin == "7373") {
        a1.display(a1, a2, a3);
    } else if (enteredPin == "1111") {
        a2.display(a1, a2, a3);
    } else if (enteredPin == "3333") {
        a3.display(a1, a2, a3);
    } else {
        cout << "PIN is wrong!!" << endl << "**************  Reload It  **************";
    }

    return 0;

}
