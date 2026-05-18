#include <iostream>
#include <string>
#include <vector> // Required for vectors

using namespace std;

class LibraryMember;

class LibraryResource {
protected:
    int resourceID;
    string title;
    string author;
    bool isAvailable;

public:
    LibraryResource() : resourceID(0), isAvailable(true) {}
    LibraryResource(int id, string t, string a) : resourceID(id), title(t), author(a), isAvailable(true) {}

    // virtual destructor is essential when using inheritance
    virtual ~LibraryResource() {}

    friend void adminView(const vector<LibraryResource>& resources, const vector<LibraryMember>& members);

    int getResourceID() const { return resourceID; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool available) { isAvailable = available; }

    void displayDetails() const {
        cout << "ID: " << resourceID << " | Title: " << title 
             << " | Author: " << author << " | Available: " 
             << (isAvailable ? "Yes" : "No") << endl;
    }

    // Made virtual so derived classes can override it correctly
    virtual int calculateLateFee(int daysLate) const {
        return 0; 
    }
};

class Book : public LibraryResource {
    string ISBN;
    int pageCount;
public:
    Book(int id, string t, string a, string isbn, int pages) : LibraryResource(id, t, a), ISBN(isbn), pageCount(pages) {}

    int calculateLateFee(int daysLate) const override {
        return daysLate * 5; 
    }
};

class Magazine : public LibraryResource {
    int issueNumber;
public:
    Magazine(int id, string t, string a, int issue) : LibraryResource(id, t, a), issueNumber(issue) {}

    int calculateLateFee(int daysLate) const override {
        return daysLate * 3;
    }
};

class DVD : public LibraryResource {
    int duration;
public:
    DVD(int id, string t, string a, int dur) : LibraryResource(id, t, a), duration(dur) {}

    int calculateLateFee(int daysLate) const override {
        return daysLate * 10;
    }
};

class LibraryMember {
private:
    int memberID; 
    string name; 
    vector<LibraryResource> borrowedItems; // Vector instead of array

public:
    LibraryMember() : memberID(0) {} 
    LibraryMember(int id, string n) : memberID(id), name(n) {}

    int getMemberID() const { return memberID; }

    void borrowResource(LibraryResource res) {
        if (borrowedItems.size() < 5) {
            res.setAvailability(false);
            borrowedItems.push_back(res);
            cout << "Resource added to member's record." << endl;
        } else {
            cout << "Borrowing limit reached." << endl;
        }
    }

    void returnResource(int resID) {
        for (auto it = borrowedItems.begin(); it != borrowedItems.end(); ++it) {
            if (it->getResourceID() == resID) {
                borrowedItems.erase(it); // Easy removal with vectors
                cout << "Resource returned successfully." << endl;
                return;
            }
        }
        cout << "Resource not found in member record." << endl;
    }

    void displayBorrowedItems() const {
        cout << "Borrowed items for " << name << ":" << endl;
        for (const auto& item : borrowedItems) {
            item.displayDetails();
        }
    }

    int calculateTotalLateFee(int daysLate) const {
        int total = 0;
        for (const auto& item : borrowedItems) {
            total += item.calculateLateFee(daysLate);
        }
        return total;
    }

    friend void adminView(const vector<LibraryResource>& resources, const vector<LibraryMember>& members);
};

void adminView(const vector<LibraryResource>& resources, const vector<LibraryMember>& members) {
    cout << "\n--- ADMIN VIEW ---" << endl;
    cout << "Library Resources:" << endl;
    for (const auto& res : resources) {
        cout << "Title: " << res.title << " | Available: " 
             << (res.isAvailable ? "Yes" : "No") << endl;
    }
    cout << "\nRegistered Members:" << endl;
    for (const auto& mem : members) {
        cout << "Member: " << mem.name << " (ID: " << mem.memberID << ")" << endl;
        mem.displayBorrowedItems();
    }
}

int main() {
    vector<LibraryResource> libraryStock; 
    vector<LibraryMember> members;
    int choice;

    while (true) {
        cout << "\n1. Add Resource\n2. Register Member\n3. Borrow\n4. Return\n5. View All Resources\n6. Member Items\n7. Late Fee\n8. Admin View\n9. Exit\nChoice: ";
        cin >> choice;
        if (choice == 9) break;

        if (choice == 1) {
            int id, type; string t, a;
            cout << "Type (1:Book, 2:Mag, 3:DVD): "; cin >> type;
            cout << "ID: "; cin >> id; cin.ignore();
            cout << "Title: "; getline(cin, t);
            cout << "Author: "; getline(cin, a);
            if (type == 1) libraryStock.push_back(Book(id, t, a, "ISBN-X", 200));
            else if (type == 2) libraryStock.push_back(Magazine(id, t, a, 5));
            else if (type == 3) libraryStock.push_back(DVD(id, t, a, 120));
        }
        else if (choice == 2) {
            int id; string n;
            cout << "ID: "; cin >> id; cin.ignore();
            cout << "Name: "; getline(cin, n);
            members.push_back(LibraryMember(id, n));
        }
        else if (choice == 3) {
            int mid, rid;
            cout << "Member ID: "; cin >> mid;
            cout << "Resource ID: "; cin >> rid;
            bool foundMember = false, foundResource = false;
            for (auto& member : members) {
                if (member.getMemberID() == mid) {
                    foundMember = true;
                    for (auto& res : libraryStock) {
                        if (res.getResourceID() == rid) {
                            foundResource = true;
                            if (res.getAvailability()) { 
                                res.setAvailability(false);
                                member.borrowResource(res);
                            } else {
                                cout << "Resource already borrowed" << endl;
                            }
                        }
                    }
                }
            }
            if(!foundMember) cout << "Member not found" << endl;
        }
        else if (choice == 4) {
            int mid, rid;
            cout << "Member ID: "; cin >> mid;
            cout << "Resource ID: "; cin >> rid;
            for (auto& member : members) {
                if (member.getMemberID() == mid) {
                    member.returnResource(rid);
                    for(auto& res : libraryStock) {
                        if(res.getResourceID() == rid) res.setAvailability(true);
                    }
                }
            }
        }
        else if (choice == 5) {
            for (const auto& res : libraryStock) res.displayDetails();
        }
        else if (choice == 6) {
            int mid;
            cout << "Member ID: "; cin >> mid;
            for (const auto& member : members) {
                if (member.getMemberID() == mid) member.displayBorrowedItems();
            }
        }
        else if (choice == 7) {
            int mid, days;
            cout << "Member ID: "; cin >> mid;
            cout << "Days late: "; cin >> days;
            for (const auto& member : members) {
                if (member.getMemberID() == mid) {
                    cout << "Total Fee: " << member.calculateTotalLateFee(days) << endl;
                }
            }
        }
        else if (choice == 8) {
            adminView(libraryStock, members);
        }
    }
    return 0;
}
