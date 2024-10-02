cmake_minimum_required(VERSION 3.5)

project(mini_project_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mini_project_1 main.cpp
    client.h client.cpp
    clientmanager.h clientmanager.cpp
    product.h product.cpp


    productmanager.h productmanager.cpp
    shoppingmanager.h shoppingmanager.cpp)

include(GNUInstallDirs)
install(TARGETS mini_project_1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
