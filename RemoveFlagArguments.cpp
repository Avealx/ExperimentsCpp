/* remove flag arguments
 *
 * refactoring, program to an interface
 *
 * motivator: Clean C++ Chapter04
 * Reducing the number of arguments relieves the cognitive load during code
 * reading and understanding. The idea is to lift the different computational
 * branches distinguished by the flag arguments into their own methods/classes
 * that self-document the behaviour.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct BookingItems {
    string name;
    vector<string> items;
};

// Version 1: use of flag argument 'printDetail' (bad practice)

struct Billing {
    void createInvoice(BookingItems const & bookingItems, bool printDetail=false) const {
        cout << "invoice for: " << bookingItems.name << "\n";
        if (printDetail)
            for (auto const & item : bookingItems.items)
                cout << item << "\n";
    }
};

// Version 2: split the computation branches into separate methods

struct BillingSeparated {
    void createInvoice(BookingItems const & bookingItems) const {
        cout << "invoice for: " << bookingItems.name << "\n";
    }

    void createInvoiceWithDetail(BookingItems const & bookingItems) const {
        createInvoice(bookingItems);
        for (auto const & item : bookingItems.items)
            cout << item << "\n";
    }
};

// Version 3: split the computation branches into separate classes

struct IBilling {
    virtual void createInvoice(BookingItems const & bookingItems) const = 0;
    virtual ~IBilling() {}
};

struct SimpleBilling : IBilling{
    virtual void createInvoice(BookingItems const & bookingItems) const override {
        cout << "invoice for: " << bookingItems.name << "\n";
    }
};

struct DetailedBilling : IBilling{
    virtual void createInvoice(BookingItems const & bookingItems) const override {
        simpleBilling.createInvoice(bookingItems);
        addDetail(bookingItems);
    }
    private:
    void addDetail(BookingItems const & bookingItems) const {
        for (auto const & item : bookingItems.items)
            cout << item << "\n";
        }
    SimpleBilling simpleBilling;
};


int main() {
    auto bookingItems = BookingItems{"MyItems", {"a house", "a Blouse", "and a mouse"}};

    cout << "--------------\n";
    cout << "basic billing:\n";
    cout << "--------------\n";
    auto bil = Billing{};
    bil.createInvoice(bookingItems);
    cout << "\n";
    bool withDetail = true;
    bil.createInvoice(bookingItems, withDetail);

    cout << "------------------\n";
    cout << "billing separated:\n";
    cout << "------------------\n";
    auto bilS = BillingSeparated{};
    bilS.createInvoice(bookingItems);
    cout << "\n";
    bilS.createInvoiceWithDetail(bookingItems);

    cout << "--------------------\n";
    cout << "billing Inheritance:\n";
    cout << "--------------------\n";
    auto bilSimple = SimpleBilling{};
    bilSimple.createInvoice(bookingItems);
    cout << "\n";
    auto bilDetail = DetailedBilling{};
    bilDetail.createInvoice(bookingItems);
}


