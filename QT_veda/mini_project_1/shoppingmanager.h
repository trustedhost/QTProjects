#ifndef SHOPPINGMANAGER_H
#define SHOPPINGMANAGER_H

#include <map>

class Product;

using namespace std;

// product sorting(by name, by price)
class ShoppingManager
{
public:
    ShoppingManager();
    ~ShoppingManager();
    vector<string> parseCSV(istream &file, char);
    void displaySortedInfo(string column, bool reverse);
    void displayInfo();
    bool displayMenu();
private:
    map<int, Product*> productList;


};

#endif // SHOPPINGMANAGER_H
