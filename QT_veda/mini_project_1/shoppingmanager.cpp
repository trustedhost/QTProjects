#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>


#include "shoppingmanager.h"
#include "product.h"

ShoppingManager::ShoppingManager() {
    ifstream file;
    file.open("productlist.txt");
    if(!file.fail()) {
        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size()) {
                int id = atoi(row[0].c_str());
                double price = atof(row[2].c_str());
                Product* p = new Product(id, row[1], price);
                productList.insert( {id, p });
            }
        }
    }
    file.close();
}

ShoppingManager::~ShoppingManager()
{
    ofstream file;
    file.open("productlist.txt");
    if(!file.fail()) {
        for (const auto& v : productList) {
            Product *p = v.second;
            file << p->getId() << ", " << p->getName() << ", ";
            file << p->getPrice() << endl;
            delete v.second;
        }
    }
    productList.clear();
    file.close();
}

vector<string> ShoppingManager::parseCSV(istream &file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";
    while(!file.eof()) {
        char c = file.get();
        if( c == delimiter || c == '\r' || c == '\n') {
            if(file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        } else {
            ss << c;
        }
    }
    return row;
}

void ShoppingManager::displaySortedInfo(string column = "id", bool reverse = false)
{
    cout  << "  ID  |     Name     | Price | "<< endl;
    vector<Product*> sortedList;
    for (const auto& v : productList) {
        sortedList.push_back(v.second);
    }

    if (column == "name") {
        sort(sortedList.begin(), sortedList.end(), [](Product* a, Product* b) {
            if ( a->getName() == b->getName() ) {
                return a->getId() < b->getId();
            }
            return a->getName() < b->getName();
        });
    } else if (column == "price") {
        sort(sortedList.begin(), sortedList.end(), [](Product* a, Product* b) {
            if ( a->getPrice() == b->getPrice() ) {
                return a->getId() < b->getId();
            }
            return a->getPrice() < b->getPrice();
        });
    }

    if (reverse) {
        std::reverse(sortedList.begin(), sortedList.end());
    }
    for (const auto& p : sortedList) {
        cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getPrice() << endl;
    }
}
void ShoppingManager::displayInfo()
{
    cout  << "  ID  |     Name     | Price | "<< endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getPrice() << endl;
    }

}

bool ShoppingManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Shopping Mall                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\n";
    cout << "  Product List                     " << endl;
    cout << "---------------------------------------------" << endl;
    displayInfo();
    cout << "---------------------------------------------" << endl;
    cout << "\n";
    cout << "\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Sort Product by Price (low to high)     " << endl;
    cout << "  2. Sort Product by Price (high to low)     " << endl;
    cout << "  3. Sort Product by Name (A-Z)     " << endl;
    cout << "  4. Sort Product by Name (Z-A)     " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    cin >> ch;
    switch(ch) {
    case 1:
        displaySortedInfo("price");
        cin.ignore();
        getchar();
        break;
    case 2:
        displaySortedInfo("price", true);
        cin.ignore();
        getchar();
        break;
    case 3:
        displaySortedInfo("name");
        cin.ignore();
        getchar();
        break;
    case 4:
        displaySortedInfo("name", true);
        cin.ignore();
        getchar();
        break;
    case 5:
        return false;
    default:
        std::cout << '\n' << "Wrong input... try again." << '\n';
        std::cin.ignore();
        getchar();
        cin.clear();
    }
    return true;

}
