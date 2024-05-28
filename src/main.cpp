/**
 * @file main.cpp
 * @brief Se realiza el llamado a las funciones, clase ValidadorEmail.hpp y menus del programa
 *
 * @author 
 * @date 2024
 * @version 1.0
 * @license MIT
 */
#include <string>
#include <iostream>
#include <algorithm>
#include <sqlite3.h> 
//#include "Funciones.hpp"
#include "clientDb.hpp"

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

/**
 * @brief Ejecuta menus del programa y realiza el llamado a multiples funciones de Funciones.hpp y clase ValidadorEmail.hpp.
 * 
 * @return 0 al terminar la ejecuacion del programa.
 */
int main() {

        //Variable entera que almacena el numero de opcion selecionada por el usuario
        int opcion;
        // Ruta a la base de datos
        std::string dbPath = "../databases/clientes.db";

        // Crear instancia de ClienteDB
        ClienteDB clienteDB(dbPath);

        // Crear tabla si no existe
        if (!clienteDB.createTable()) {
            std::cerr << "Failed to create table" << std::endl;
            return 1;
        }

        clienteDB.viewClientes();
        
        do {

            //Variable string que almacena el numero de opcion selecionada por el usuario
            string strOpcion;

            //Menu principal
            cout << "\nModalidad de operacion\n";
            cout << "1. Atencion al cliente\n";
            cout << "2. Informacion general sobre prestamos bancarios\n";
            cout << "3. Salir\n";
            cout << "Ingrese una opcion: ";
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
                            std::cout << "Ingrese el numero de identificacion del cliente: ";
                            std::getline(std::cin, id);
                            //std::cin.ignore();

                            // Verificar si el id existe en la base de datos
                            if (clienteDB.idExiste(id)) {

                                string atencionClienteOpt;
                                cout << "\nAtencion al cliente\n";
                                cout << "1. Cuenta colones\n";
                                cout << "2. Cuenta dolares\n";
                                cout << "3. Certificado de deposito a plazo\n";
                                cout << "Ingrese una opcion: ";
                                cin >> atencionClienteOpt;
                                cin.ignore();
                                //cin.ignore(); // Limpiar el buffer

                                if(all_of(atencionClienteOpt.begin(), atencionClienteOpt.end(), ::isdigit) && (atencionClienteOpt == "1" || atencionClienteOpt == "2" || atencionClienteOpt == "3" )){
                                
                                }else{
                                    throw std::invalid_argument("Se ingreso una opcion NO valida, vuelva a intentar...");
                                }


                            } else {
                                std::cout << "El numero de identificacion ingresado NO esta registrado" << std::endl;
                                //Variable string que almacena el numero de opcion selecionada por el usuario
                                string createUserOptOne;
                                
                                //Menu principal
                                cout << "\nCrear usuario\n";
                                cout << "1. Si\n";
                                cout << "2. No\n";
                                cout << "Ingrese una opcion: ";
                                cin >> createUserOptOne;
                                cin.ignore();
                                //cin.ignore(); // Limpiar el buffer

                                if(all_of(createUserOptOne.begin(), createUserOptOne.end(), ::isdigit) && (createUserOptOne == "1" || createUserOptOne == "2")){
                                    
                                if (createUserOptOne == "1"){

                                        std::string askId;
                                        std::cout << "Ingrese el numero de identificacion del cliente: ";
                                        std::getline(std::cin, askId);

                                        if(all_of(askId.begin(), askId.end(), ::isdigit)){

                                            int askIdConvert = stoi(askId);

                                            if (askIdConvert > 0 && askIdConvert < 999999999){
                                                
                                                if (!clienteDB.idExiste(askId)){

                                                    std::string askName;
                                                    std::cout << "Ingrese el nombre del cliente: ";
                                                    std::getline(std::cin, askName);

                                                    clienteDB.addCliente(askId, askName,0, 0, 0, "2024-05-24 15:30:45");
                                                    std::cout << "Usuario creado exitosamente..." << std::endl;
                                                
                                                }else{
                                                    throw std::invalid_argument("Debe ingresar otro numero de identificacion, vuelva a intentar...");
                                                }
                                                
                                            }else{
                                                throw std::invalid_argument("Debe ingresar un numero entero entre 0 y 999999999, vuelva a intentar...");
                                            }
                                            
                                        }else{
                                            throw std::invalid_argument("Debe ingresar un numero entero, vuelva a intentar...");
                                        }
                                    }
                                
                                }else{
                                    throw std::invalid_argument("Se ingreso una opcion NO valida, vuelva a intentar...");
                                }
                                
                            }
                            
                            }
                            break;

                        //Caso donde deseo informacion general
                        case INFORMACION:{

                            // Solicitar al usuario que ingrese un id
                            std::string id;
                            std::cout << "Ingrese el numero de identificacion cliente: ";
                            std::getline(std::cin, id);
                            

                            // Verificar si el id existe en la base de datos
                            if (clienteDB.idExiste(id)) {

                                std::cout << "Usuario existente ..." << std::endl;
                                //Variable int que almacena el numero de opcion selecionada por el usuario
                                int opcionTwo;
                                //Variable string que almacena el numero de opcion selecionada por el usuario
                                string strOpcionTwo;

                                //Menu sobre informaion general
                                //Aqui de sebe quitra la opcion de generar tabla, ya que el reporte se genera cuando el usuario ha realizado el prestamo
                                cout << "\nInformacion general\n";
                                cout << "1. Prestamos personales\n";
                                cout << "2. Prestamos prendarios\n";
                                cout << "3. Prestamos hipotecarios\n";
                                cout << "4. Generar tabla\n";
                                cout << "5. Salir\n";
                                cout << "Ingrese una opcion: ";
                                cin >> strOpcionTwo;
                                cin.ignore(); // Limpiar el buffer

                                //Verifico que se agregue un numero entero y que este sea 1,2,3,4 o 5
                                if(all_of(strOpcionTwo.begin(), strOpcionTwo.end(), ::isdigit) && (strOpcionTwo == "1" || strOpcionTwo == "2" || strOpcionTwo == "3"
                                || strOpcionTwo == "4" || strOpcionTwo == "5")){
                                    
                                    //Convierto el string a entero para almacenar opcion del usuario
                                    opcionTwo = stoi(strOpcionTwo);

                                    switch (opcionTwo) {
                            
                                        //Caso prestamo personal
                                        case PERSONAL:{

                                                
                                            }
                                            break;

                                        //Caso prestamo prendario
                                        case PRENDARIOS:{

                                        
                                            }
                                            break;

                                        //Caso prestamo hipotecario
                                        case HIPOTECARIOS:{

                                        
                                            }
                                            break;
                                        //Caso de creacion de tabla
                                        case TABLA:{

                                        
                                            }
                                            break;

                                        //Caso donde deseo salir
                                        case SALIRTWO:

                                            cout << "Saliendo...\n";

                                            break;

                                        //Caso por defecto
                                        default:

                                            cout << "Opcion no valida\n";

                                            break;
                                        }


                                }else{
                                    //Ocurre una excepcion cuando no agrego un numero entero que sea 1,2,3,4 o 5
                                    throw std::invalid_argument("Se ingreso una opcion NO valida, vuelva a intentar...");
                                }

                            } else {
                                std::cout << "El numero de identificacion del usuario ingresado NO esta registrado" << std::endl;
                                string createUserOptTwo;
                                
                                //Menu principal
                                cout << "\nCrear usuario\n";
                                cout << "1. Si\n";
                                cout << "2. No\n";
                                cout << "Ingrese una opcion: ";
                                cin >> createUserOptTwo;
                                cin.ignore(); // Limpiar el buffer

                                if(all_of(createUserOptTwo.begin(), createUserOptTwo.end(), ::isdigit) && (createUserOptTwo == "1" || createUserOptTwo == "2")){
                                    
                                if (createUserOptTwo == "1"){

                                        std::string askId;
                                        std::cout << "Ingrese el numero de identificacion del cliente: ";
                                        std::getline(std::cin, askId);

                                        if(all_of(askId.begin(), askId.end(), ::isdigit)){

                                            int askIdConvert = stoi(askId);

                                            if (askIdConvert > 0 && askIdConvert < 999999999){
                                                
                                                if (!clienteDB.idExiste(askId)){

                                                    std::string askName;
                                                    std::cout << "Ingrese el nombre del cliente: ";
                                                    std::getline(std::cin, askName);

                                                    clienteDB.addCliente(askId, askName,0, 0, 0, "2024-05-24 15:30:45");
                                                    std::cout << "Usuario creado exitosamente..." << std::endl;
                                                
                                                }else{
                                                    throw std::invalid_argument("Debe ingresar otro numero de identificacion, vuelva a intentar...");
                                                }

                                            }else{
                                                throw std::invalid_argument("Debe ingresar un numero entero entre 0 y 999999999, vuelva a intentar...");
                                            }
                                            
                                        }else{
                                            throw std::invalid_argument("Debe ingresar un numero entero, vuelva a intentar...");
                                        }
                                    
                                    }
                                
                                }else{
                                    throw std::invalid_argument("Se ingreso una opcion NO valida, vuelva a intentar...");
                                }

                            }



                            }
                            break;

                        //Caso donde deseo salir
                        case SALIR:

                            cout << "Saliendo...\n";

                            break;

                        //Caso por defecto
                        default:

                            cout << "Opcion no valida\n";

                            break;
                        }
                } else{
                    //Ocurre una excepcion cuando no agrego un numero entero que sea 1,2 o 3
                    throw std::invalid_argument("Se ingreso una opcion NO valida, vuelva a intentar...");
                }

            //Manejo de excepciones   
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
        } while(opcion != SALIR);

        return 0;
    }