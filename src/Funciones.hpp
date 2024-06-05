#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include "clientDb.hpp"
#include "transactionDb.hpp"
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

using namespace std;

//Creo un nuevo usuario en caso de necesitarlo
void userNotExist(ClienteDB& clienteDB);

// Declarar la nueva función del menu 5
void menuOperaciones(ClienteDB& clienteDB, const std::string& id, const std::string& tipoDeCuenta, TransactionDB& transferenciaDB);

//Verifico si el usuario agrega un monto positivo
bool isPositiveDouble(const char &c);

//Verifico que la entrada del usuario sea valida, no tenga espacios en blanco, sea un double
//no teeeenga mas de un punto y el valor sea positivo.
bool isValidMonto(const std::string &monto);
//Con esta funcion obtengo la hora actual en formato YYYY-MM-DD hh:mm:ss
std::string getCurrentDateTime();

#endif //FUNCIONES_HPP