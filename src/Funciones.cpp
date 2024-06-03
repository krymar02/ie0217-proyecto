#include "Funciones.hpp"
//Estoy agregando el menu 5 le fantan implementaciones 
//Defino constantes de menu 5
enum Operacion {
    DEPOSITO = 1,
    RETIRO = 2,
    TRANSFERENCIA = 3,
    ABONO = 4
};

// Implementar la nueva función
void menuOperaciones(ClienteDB& clienteDB, const std::string& id) {
    string operacionOpt;
    cout << "\nSeleccione la operacion que desea realizar\n";
    cout << "1. Depositos\n";
    cout << "2. Retiros\n";
    cout << "3. Transferencias entre cuentas\n";
    cout << "4. Abonos\n";
    cout << "Ingrese una opcion: ";
    cin >> operacionOpt;
    cin.ignore(); // Se debe limpiar el buffer

    if (all_of(operacionOpt.begin(), operacionOpt.end(), ::isdigit) &&
        (operacionOpt == "1" || operacionOpt == "2" || operacionOpt == "3" || operacionOpt == "4")) {
        // Se convierte la opción a entero
        int operacion = stoi(operacionOpt);

        // Se realiza la logica para los tipos de operaciones (FALTA AGREGAR)
        switch (operacion) {
            case DEPOSITO:
                cout << "Realizar deposito..." << endl;
                // Depositos
                break;
            case RETIRO:
                cout << "Realizar retiro..." << endl;
                // Retiros
                break;
            case TRANSFERENCIA:
                cout << "Realizar transferencia..." << endl;
                // Transferencias
                break;
            case ABONO:
                cout << "Realizar abono..." << endl;
                //Abonopos
                break;
            //Me falta agregar una opcion para salir o regresar
            default:
                cout << "Opcion no valida\n";
                break;
        }
    } else {
        throw std::invalid_argument("Ingreso una opcion invalida vuelva a intentar...");
    }//aqui regresa al servicio al cliente
};

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