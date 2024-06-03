#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include "clientDb.hpp"
#include <string>
#include <algorithm>

using namespace std;

//Creo un nuevo usuario en caso de necesitarlo
void userNotExist(ClienteDB& clienteDB);

// Declarar la nueva función del menu 5
void menuOperaciones(ClienteDB& clienteDB, const std::string& id);

#endif //FUNCIONES_HPP