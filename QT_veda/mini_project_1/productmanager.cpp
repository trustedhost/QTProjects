#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "product.h"
#include "productmanager.h"

#include "unistd.h"

ProductManager::ProductManager()
{
    ifstream file("productlist.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                double price = atof(row[2].c_str());
                Product* p = new Product(id, row[1], price);
                productList.insert({id, p});
            }
        }
    }
    file.close();

    std::cout << "########################################" << '\n';

}

ProductManager::~ProductManager()
{
    ofstream file;
    file.open("productlist.txt", std::ios::out);
    if(!file.fail()) {
        for (const auto& v : productList) {
            Product *p = v.second;
            std::cout << p->getId() << ", " << p->getName() << ", ";
            std::cout << p->getPrice() << endl;


            file << p->getId() << ", " << p->getName() << ", ";
            file << p->getPrice() << endl;
            // delete v.second;
        }
    } else {
        std::cout << "fuckfuckfuck" << '\n';
    }
    std::cout << "*************************************************************************************" << '\n' ;
    sleep(1);
    for (auto v : productList) {
        delete v.second;
    }
    productList.clear();
    file.close();
}

void ProductManager::inputProduct()
{
    std::string name;
    double price;
    cout << "name : "; cin.ignore(); getline(cin, name, '\n');
    cout << "price : "; cin >> price;


    int id = makeId();
    Product* p = new Product(id, name, price);
    productList.insert({id, p});

}

void ProductManager::addProduct(Product * p)
{
    productList.insert({ p->getId(), p} );
}

void ProductManager::deleteProduct(int key)
{
    productList.erase(key);
}

void ProductManager::modifyProduct(int key)
{
    Product* p = search(key);
    cout << "  ID  |     Name     | Price | " << endl;
    cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getName() << " | ";
    cout << setw(12) << p->getPrice() << endl;

    string name;
    double price;
    cout << "name : "; cin.ignore(); getline(cin, name, '\n');
    cout << "price : "; cin >> name;

    p->setName(name);
    p->setPrice(price);
    productList[key] = p;
}

Product *ProductManager::search(int id)
{
    return productList[id];
}

int ProductManager::makeId()
{
    if (productList.size() == 0) {
        return 0;
    } else {
        auto elem = productList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

void ProductManager::displayInfo()
{
    cout << endl << "  ID  |     Name     | Price | "<< endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getPrice() << endl;
    }

}

vector<string> ProductManager::parseCSV(istream &file, char delimiter)
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

bool ProductManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Modify Product                           " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    cin >> ch;
    switch(ch) {
    case 1:
        displayInfo();
        cin.ignore();
        getchar();
        break;
    case 2:
        inputProduct();
        break;
    case 3:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        deleteProduct(key);
        break;
    case 4:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        modifyProduct(key);
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



