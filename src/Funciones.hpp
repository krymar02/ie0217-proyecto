#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include "clientDb.hpp"
#include <string>
#include <algorithm>

using namespace std;

//Creo un nuevo usuario en caso de necesitarlo
void userNotExist(ClienteDB& clienteDB);

#endif //FUNCIONES_HPP