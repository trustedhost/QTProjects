#include <iostream>
#include "clientmanager.h"
#include "productmanager.h"
#include "shoppingmanager.h"
#include <string>
#include <unistd.h>

using namespace std::string_literals;

bool Display() {
    int option = 0;
    string mainDisplay = R"delimiter(*** 쇼핑물 프로그램 ***
1. 쇼핑몰
2. 고객 관리
3. 제품 관리
4. quit
어떤 메뉴를 선택하시겠습니까?)delimiter";

    cout << "\033[2J\033[1;1H";
    std::cout << mainDisplay;
    ShoppingManager sm;
    ClientManager cm;
    ProductManager pm;
    pm.displayInfo();

    // ShoppingManager* sm = new ShoppingManager();
    // ClientManager* cm = new ClientManager();
    // ProductManager* pm = new ProductManager();

    if( !(std::cin >> option) ) {
        std::cout << '\n' << "Wrong input... try again." << '\n';
        std::cin.clear();
        std::cin.ignore();
    }

    switch(option) {
    case 1:
        while(sm.displayMenu());
        break;
    case 2:
        while(cm.displayMenu());
        break;
    case 3:
        while(pm.displayMenu());
        break;
    case 4:
        return false;
    default:
        std::cout << "put the right number." << '\n';
        std::cin.ignore();
        getchar();
        cin.clear();
    }

    return true;
}

int main()
{
    while(Display());
    return 0;
}
