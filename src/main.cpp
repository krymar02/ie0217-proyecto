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

            try{

                //Verifico que se agregue un numero entero y que este sea 1,2 o 3
                if(all_of(strOpcion.begin(), strOpcion.end(), ::isdigit) && (strOpcion == "1" || strOpcion == "2" || strOpcion == "3")){
                    
                    //Convierto el string a entero para almacenar opcion del usuario
                    opcion = stoi(strOpcion);
                    switch (opcion) {
                        
                        //Caso donde deseo utilizar la modalidad de atencion al cliente
                        case ATENCION:{

                            //AQUI DEBE PREGUNTAR POR LA EXISTENCIA DEL USUARIO 
                                
                            }
                            break;

                        //Caso donde deseo informacion general
                        case INFORMACION:{

                            //AQUI DEBE PREGUNTAR POR LA EXISTENCIA DEL USUARIO, ANTES DE EJECUTAR EL CODIGO
                            //RESTANTE

                            //Variable int que almacena el numero de opcion selecionada por el usuario
                            int opcionTwo;
                            //Variable string que almacena el numero de opcion selecionada por el usuario
                            string strOpcionTwo;

                            //Menu sobre informaion general
                            cout << "\nInformacion general\n";
                            cout << "1. Prestamos personales\n";
                            cout << "2. Prestamos prendarios\n";
                            cout << "3. Prestamos hipotecarios\n";
                            cout << "4. Generar tabla\n";
                            cout << "5. Salir\n";
                            cout << "Ingrese una opcion: ";
                            cin >> strOpcionTwo;
                            
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