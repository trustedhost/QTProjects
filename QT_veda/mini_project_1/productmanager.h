#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <map>
#include <vector>

class Product;

using namespace std;

class ProductManager
{
public:
    ProductManager();
    ~ProductManager();

    void inputProduct();
    void addProduct(Product *);
    void deleteProduct(int);
    void modifyProduct(int);
    Product* search(int);
    int makeId();
    void displayInfo();
    vector<string> parseCSV(istream&, char);
    bool displayMenu();

    void saveList();
private:
    map<int, Product*> productList;
};

#endif // PRODUCTMANAGER_H
