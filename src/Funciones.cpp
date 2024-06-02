#include "Funciones.hpp"

void userNotExist(ClienteDB& clienteDB){

  std::cout << "El numero de identificacion del usuario ingresado NO esta registrado" << std::endl;
  string createUserOptTwo;

  //Menu de pregunta
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

};