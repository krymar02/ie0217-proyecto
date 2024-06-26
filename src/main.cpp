/**
 * @file main.cpp
 * @brief Se realiza el llamado a las funciones, clases y menus del programa
 *
 * @author 
 * @date 2024
 * @version 1.0
 * @license MIT
 */
//nuevo
#include <stdexcept>
#include <limits>
//nuevo
#include <string>
#include <iostream>
#include <algorithm>
#include <sqlite3.h> 
#include "Funciones.hpp"
#include "clientDb.hpp"
#include "transactionDb.hpp"
#include "prestamosDb.hpp"

using namespace std;

//Contenido de defines contenidos en 1, solo tiene valores numéricos y se llaman atraves de variables
enum Opciones {
    ATENCION = 1,
    INFORMACION,
    SALIR
};

enum OpcionesGnerales {
    PERSONAL = 1,
    PRENDARIOS,
    HIPOTECARIOS,
    SALIRTWO
};
//Para crear menu 5
enum Operaciones {
    DEPOSITO = 1,
    RETIRO,
    TRANSFERENCIA,
    ABONO
};

/**
 * @brief Ejecuta menus del programa y realiza el llamado a multiples funciones de Funciones.hpp y clase ValidadorEmail.hpp.
 * 
 * @return 0 al terminar la ejecuacion del programa.
 */


//Declaro la función para el menu 5
//void menuOperaciones(ClienteDB& clienteDB, const std::string& id);

int main() {

        //Variable entera que almacena el numero de opcion selecionada por el usuario
        int opcion;
        // Ruta a la base de datos
        std::string dbPath = "../databases/banco.db";

        // Crear instancia de ClienteDB
        ClienteDB clienteDB(dbPath);
        // Crear instancia de TransactionDB
        TransactionDB transferenciaDB(dbPath);
        // Crear instancia de PrestamosDB
        PrestamoDB prestamosDB(dbPath);
        

        // Crear tabla si no existe
        if (!clienteDB.createTable() || !transferenciaDB.createTable() | !prestamosDB.createTable()) {
            std::cerr << "Failed to create table" << std::endl;
            return 1;
        }
        
        do {

            //Variable string que almacena el número de opción selecionada por el usuario
            string strOpcion;

            //Menu principal
            cout << "\nModalidad de operación\n";
            cout << "1. Atención al cliente\n";
            cout << "2. Información general sobre préstamos bancarios\n";
            cout << "3. Salir\n";
            cout << "Ingrese una opción: ";
            //cin >> strOpcion;
            //cin.ignore(); // Limpiar el buffer
            std::getline(std::cin, strOpcion);
            removeWhiteSpaces(strOpcion);

            try{

                //Verifico que se agregue un número entero y que este sea 1,2 o 3
                if(all_of(strOpcion.begin(), strOpcion.end(), ::isdigit) && (strOpcion == "1" || strOpcion == "2" || strOpcion == "3")){
                    
                    //Convierto el string a entero para almacenar opción del usuario
                    opcion = stoi(strOpcion);
                    switch (opcion) {
                        
                        //Caso donde deseo utilizar la modalidad de atención al cliente
                        case ATENCION:{

                            // Solicitar al usuario que ingrese un id
                            std::string id;
                            std::cout << "Ingrese el número de identificación del cliente: ";
                            std::getline(std::cin, id);
                            //remuevo espacios en blanco
                            removeWhiteSpaces(id);
                            //std::cin.ignore();

                            // Verificar si el id existe en la base de datos
                            if (clienteDB.idExiste(id)) {

                                string atencionClienteOpt;
                                cout << "\nAtención al cliente.\n";
                                cout << "1. Cuenta en colones\n";
                                cout << "2. Cuenta en dólares\n";
                                cout << "3. Certificado de depósito a plazo\n";
                                cout << "Ingrese una opción: ";
                                //cin >> atencionClienteOpt;
                                //cin.ignore(); // Limpiar el buffer
                                std::getline(std::cin, atencionClienteOpt);
                                removeWhiteSpaces(atencionClienteOpt);

                                if(all_of(atencionClienteOpt.begin(), atencionClienteOpt.end(), ::isdigit) && (atencionClienteOpt == "1" || atencionClienteOpt == "2" || atencionClienteOpt == "3" )){
                                    // Llamar a la función del menú de operaciones (menú 5)
                                    menuOperaciones(clienteDB, id, atencionClienteOpt, transferenciaDB, prestamosDB);
                                }else{
                                    throw std::invalid_argument("Se ingresó una opción NO válida, vuelva a intentar...");
                                }


                            } else {

                                // En caso de crear usuario que no existe
                                userNotExist(clienteDB);
                                
                            }
                            
                            }
                            break;

                        //Caso donde deseo información general
                        case INFORMACION:{

                            // Solicitar al usuario que ingrese un id
                            std::string id;
                            std::cout << "Ingrese el número de identificación cliente: ";
                            std::getline(std::cin, id);
                            removeWhiteSpaces(id);

                            // Verificar si el id existe en la base de datos
                            if (clienteDB.idExiste(id)) {

                                std::cout << "Usuario existente ..." << std::endl;
                                //Variable int que almacena el número de opción selecionada por el usuario
                                int opcionTwo;
                                //Variable string que almacena el número de opción selecionada por el usuario
                                string strOpcionTwo;

                                //Menú sobre información general
                                cout << "\nInformación general\n";
                                cout << "1. Préstamos personales\n";
                                cout << "2. Préstamos prendarios\n";
                                cout << "3. Préstamos hipotecarios\n";
                                cout << "4. Salir\n";
                                cout << "Ingrese una opción: ";
                                //cin >> strOpcionTwo;
                                //cin.ignore(); // Limpiar el buffer
                                std::getline(std::cin, strOpcionTwo);
                                removeWhiteSpaces(strOpcionTwo);

                                //Verifico que se agregue un número entero y que este sea 1,2,3,4 o 5
                                if(all_of(strOpcionTwo.begin(), strOpcionTwo.end(), ::isdigit) && (strOpcionTwo == "1" || strOpcionTwo == "2" || strOpcionTwo == "3"
                                || strOpcionTwo == "4")){
                                    
                                    //Convierto el string a entero para almacenar opción del usuario
                                    opcionTwo = stoi(strOpcionTwo);

                                    switch (opcionTwo) {
                            
                                        //Caso para cada tipo de préstamo
                                        case PERSONAL:
                                        case PRENDARIOS:
                                        case HIPOTECARIOS: {
                                            std::string tipoPrestamo;
                                            if (opcionTwo == PERSONAL) {
                                                tipoPrestamo = "Personal";                                        
                                            } else if (opcionTwo == PRENDARIOS) {
                                                tipoPrestamo = "Prendario";
                                            } else if (opcionTwo == HIPOTECARIOS) {
                                                tipoPrestamo = "Hipotecario";
                                            }

                                            double monto;
                                            while (true) {
                                                try {
                                                    std::string montoUser;
                                                    std::cout << "Ingrese el monto del préstamo: ";
                                                    std::getline(std::cin, montoUser);

                                                    if (!isValidMonto(montoUser)) {
                                                        throw std::invalid_argument("Monto inválido, vuelva a digitar.");
                                                    }

                                                    monto = std::stod(montoUser); // Convertir el string a double
                                                    break; //salir del bucle si el monto es inválido
                                                } catch (const std::exception& e) {
                                                    std::cerr << e.what() << '\n';
                                                }
                                            }


                                           // Obtención del plazo en años para calcular las cuotas
                                           // Se agregan excepciones para que sólo acepte números positivos enteros
                                            int plazoAnios;
                                            while (true) {
                                                try {
                                                    std::string plazoAniosStr;
                                                    std::cout << "\nIngrese el plazo del préstamo en años: ";
                                                    std::getline(std::cin, plazoAniosStr);

                                                    if (!isValidPlazo(plazoAniosStr)) {
                                                        throw std::invalid_argument("\nPlazo inválido, Debe se un número entero positivo, vuelva a digitar.");
                                                    }

                                                    plazoAnios = std::stoi(plazoAniosStr);
                                                    break;
                                                } catch (const std::exception& e) {
                                                    std::cerr << e.what() << '\n';
                                                }
                                            }

                                            int cuotas = plazoAnios * 12;

                                            // Obtener fecha actual
                                            std::string fecha = getCurrentDateTime();

                                            double tasaInteres;
                                            if (tipoPrestamo == "Personal") {
                                                tasaInteres = 20.0;
                                            } else if (tipoPrestamo == "Prendario") {
                                                tasaInteres = 16.0;
                                            } else if (tipoPrestamo == "Hipotecario") {
                                                tasaInteres = 9.0;
                                            }

                                            double mensualidad = calcularMensualidad(monto, tasaInteres, cuotas);

                                            std::cout << "La mensualidad del préstamo es: " << mensualidad << std::endl;
                                            
                                            //EN ESTE CASO NO PUEDO CORREGIR ESPACIOS VARIABLE ES CHAR
                                            //SUGERENCIA PASAR A STRING
                                            char confirmacion;
                                            std::cout << "¿Desea agregar el préstamo? (S/N): ";
                                            std::cin >> confirmacion;

                                            if (confirmacion == 'S' || confirmacion == 's') {
                                                // Para registar la transacción del préstamo agregado
                                                int idPrestamo = prestamosDB.addPrestamo(id, tipoPrestamo, monto, fecha, cuotas);
                                                if (idPrestamo != -1) {
                                                    transferenciaDB.addTransaction(id, "Préstamo", monto, idPrestamo,fecha);
                                                    std::cout << "Préstamo añadido con éxito. \n";
                                                } else {
                                                    std::cout << "Error al añadir préstamo.\n";
                                                }
                                            } else {
                                                std::cout << "Préstamo no agregado. \n";
                                            }

                                            // Mostrar préstamos asociados al cliente
                                            prestamosDB.viewPrestamo();  
                                    
                                        }
                                        break;

                                        //Caso donde deseo salir
                                        case SALIRTWO:

                                            cout << "Saliendo...\n";

                                            break;

                                        //Caso por defecto
                                        default:

                                            cout << "Opción no válida\n";

                                            break;
                                        }


                                }else{
                                    //Ocurre una excepcion cuando no agrego un numero entero que sea 1,2,3,4 o 5
                                    throw std::invalid_argument("Se ingresó una opción NO válida, vuelva a intentar...");
                                }

                            } else {

                                // En caso de crear usuario que no existe
                                userNotExist(clienteDB);
                            }

                            }
                            break;

                        //Caso donde deseo salir
                        case SALIR:

                            cout << "Usted esta saliendo del sistema bancario...\n";

                            break;

                        //Caso por defecto
                        default:

                            cout << "Opción no válida\n";

                            break;
                        }
                } else{
                    //Ocurre una excepcion cuando no agrego un número entero que sea 1,2 o 3
                    throw std::invalid_argument("Se ingresó una opción NO válida, vuelva a intentar...");
                }

            //Manejo de excepciones   
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
        } while(opcion != SALIR);

        return 0;
    }