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

//Contenido de defines contenidos en 1, solo tiene valores numericos y se llaman atraves de variables
enum Opciones {
    ATENCION = 1,
    INFORMACION,
    SALIR
};

enum OpcionesGnerales {
    PERSONAL = 1,
    PRENDARIOS,
    HIPOTECARIOS,
    TABLA,
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

        clienteDB.viewClientes();
        transferenciaDB.viewTransaction();
        prestamosDB.viewPrestamo();
        
        do {

            //Variable string que almacena el número de opción selecionada por el usuario
            string strOpcion;

            //Menu principal
            cout << "\nModalidad de operación\n";
            cout << "1. Atención al cliente\n";
            cout << "2. Información general sobre préstamos bancarios\n";
            cout << "3. Salir\n";
            cout << "Ingrese una opción: ";
            cin >> strOpcion;
            cin.ignore(); // Limpiar el buffer

            try{

                //Verifico que se agregue un numero entero y que este sea 1,2 o 3
                if(all_of(strOpcion.begin(), strOpcion.end(), ::isdigit) && (strOpcion == "1" || strOpcion == "2" || strOpcion == "3")){
                    
                    //Convierto el string a entero para almacenar opcion del usuario
                    opcion = stoi(strOpcion);
                    switch (opcion) {
                        
                        //Caso donde deseo utilizar la modalidad de atencion al cliente
                        case ATENCION:{

                            // Solicitar al usuario que ingrese un id
                            std::string id;
                            std::cout << "Ingrese el número de identificación del cliente: ";
                            std::getline(std::cin, id);
                            //std::cin.ignore();

                            // Verificar si el id existe en la base de datos
                            if (clienteDB.idExiste(id)) {

                                string atencionClienteOpt;
                                cout << "\nAtención al cliente\n";
                                cout << "1. Cuenta colones\n";
                                cout << "2. Cuenta dólares\n";
                                cout << "3. Certificado de depósito a plazo\n";
                                cout << "Ingrese una opción: ";
                                cin >> atencionClienteOpt;
                                cin.ignore(); // Limpiar el buffer

                                if(all_of(atencionClienteOpt.begin(), atencionClienteOpt.end(), ::isdigit) && (atencionClienteOpt == "1" || atencionClienteOpt == "2" || atencionClienteOpt == "3" )){
                                    // Llamar a la función del menú de operaciones (menu 5)
                                    menuOperaciones(clienteDB, id, atencionClienteOpt, transferenciaDB);
                                }else{
                                    throw std::invalid_argument("Se ingresó una opción NO válida, vuelva a intentar...");
                                }


                            } else {

                                // En caso de crear usuario que no existe
                                userNotExist(clienteDB);
                                
                            }
                            
                            }
                            break;

                        //Caso donde deseo informacion general
                        case INFORMACION:{

                            // Solicitar al usuario que ingrese un id
                            std::string id;
                            std::cout << "Ingrese el número de identificación cliente: ";
                            std::getline(std::cin, id);
                            

                            // Verificar si el id existe en la base de datos
                            if (clienteDB.idExiste(id)) {

                                std::cout << "Usuario existente ..." << std::endl;
                                //Variable int que almacena el numero de opcion selecionada por el usuario
                                int opcionTwo;
                                //Variable string que almacena el numero de opcion selecionada por el usuario
                                string strOpcionTwo;

                                //Menú sobre información general
                                //Aqui de sebe quitra la opcion de generar tabla, ya que el reporte se genera cuando el usuario ha realizado el prestamo
                                cout << "\nInformación general\n";
                                cout << "1. Préstamos personales\n";
                                cout << "2. Préstamos prendarios\n";
                                cout << "3. Préstamos hipotecarios\n";
                                cout << "4. Generar tabla\n";
                                cout << "5. Salir\n";
                                cout << "Ingrese una opción: ";
                                cin >> strOpcionTwo;
                                cin.ignore(); // Limpiar el buffer

                                //Verifico que se agregue un numero entero y que este sea 1,2,3,4 o 5
                                if(all_of(strOpcionTwo.begin(), strOpcionTwo.end(), ::isdigit) && (strOpcionTwo == "1" || strOpcionTwo == "2" || strOpcionTwo == "3"
                                || strOpcionTwo == "4" || strOpcionTwo == "5")){
                                    
                                    //Convierto el string a entero para almacenar opcion del usuario
                                    opcionTwo = stoi(strOpcionTwo);

                                    switch (opcionTwo) {
                            
                                        //Caso préstamo personal
                                        case PERSONAL:{
                                            std::string tipoPrestamo = "Personal";
                                            std::string montoUser;

                                            // Obtener la fecha actual
                                            std::string fecha = getCurrentDateTime(); 

                                            std::cout << "Ingrese el monto del préstamo personal: ";
                                            std::cin >> montoUser;

                                            // Excepciones para que el monto del préstamo sea válido (positivo)
                                            if (isValidMonto(montoUser)) {
                                                double monto = std::stod(montoUser); // Convertir string en double
                                                if (prestamosDB.addPrestamo(id, tipoPrestamo, monto, fecha)) {
                                                     std::cout << "Préstamo personal añadido exitosamente.\n";
                                                } else {
                                                    std::cout << "Error al añadir el préstamo personal.\n";
                                                }
                                            } else {
                                                std::cout << "Monto inválido. Debe ser un número positivo.\n";
                                            }
                                            break;
                                        }

                                        //Caso préstamo prendario
                                        case PRENDARIOS:{
                                            std::string montoUser;

                                            // Obtener la fecha actual
                                            std::string fecha = getCurrentDateTime(); 

                                            std::cout << "Ingrese el monto del préstamo prendario: ";
                                            std::cin >> montoUser;

                                            // Excepciones para que el monto del préstamo sea válido (positivo)
                                            if (isValidMonto(montoUser)) {
                                                double monto = std::stod(montoUser); // Convertir string en double
                                                if (prestamosDB.addPrestamo(id, tipoPrestamo, monto, fecha)) {
                                                     std::cout << "Préstamo prendario añadido exitosamente.\n";
                                                } else {
                                                    std::cout << "Error al añadir el préstamo prendario.\n";
                                                }
                                            } else {
                                                std::cout << "Monto inválido. Debe ser un número positivo.\n";
                                            }
                                            break;
                                        }

                                        //Caso préstamo hipotecario
                                        case HIPOTECARIOS:{
                                            std::string tipoPrestamo = "Hipotecario";
                                            std::string montoUser;

                                            // Obtener la fecha actual
                                            std::string fecha = getCurrentDateTime(); 

                                            std::cout << "Ingrese el monto del préstamo hipotecario: ";
                                            std::cin >> montoUser;

                                            // Excepciones para que el monto del préstamo sea válido (positivo)
                                            if (isValidMonto(montoUser)) {
                                                double monto = std::stod(montoUser); // Convertir string en double
                                                if (prestamosDB.addPrestamo(id, tipoPrestamo, monto, fecha)) {
                                                     std::cout << "Préstamo hipotecario añadido exitosamente.\n";
                                                } else {
                                                    std::cout << "Error al añadir el préstamo hipotecario.\n";
                                                }
                                            } else {
                                                std::cout << "Monto inválido. Debe ser un número positivo.\n";
                                            }
                                            break;
                                        }

                                        //Caso de creación de tabla
                                        case TABLA:{
                                            // Generar reporte de préstamos
                                            prestamosDB.viewPrestamo();
                                            
                                            break;
                                        }
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

                            cout << "Saliendo...\n";

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