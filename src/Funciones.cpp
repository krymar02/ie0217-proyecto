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
void menuOperaciones(ClienteDB& clienteDB, const std::string& id, const std::string& tipoDeCuenta, TransactionDB& transferenciaDB) {
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
        std::string montoUsuario;

        // Se realiza la logica para los tipos de operaciones (FALTA AGREGAR)
        switch (operacion) {

            case DEPOSITO:

                //Depositos
                while (true) {
                    std::cout << "Ingrese un monto a depositar: " << std::endl;
                    std::getline(std::cin, montoUsuario);

                    if (isValidMonto(montoUsuario)) {
                        break;
                    } else {
                        std::cout << "Monto inválido, vuelva a digitar." << std::endl;
                    }
                }

                if(clienteDB.actualizarCuenta(id, stod(montoUsuario),tipoDeCuenta)){
                    //Creo registro de la operacion
                    transferenciaDB.addTransaction(id, "Deposito",stod(montoUsuario),-1,getCurrentDateTime());
                    std::cout << "Deposito exitoso..." << std::endl;
    
                }else{
                    std::cout << "Ocurrio un error durante el deposito..." << std::endl;
                }
                

                break;

            case RETIRO:

                // Retiros
                while (true) {
                    std::cout << "Ingrese un monto a retirar: " << std::endl;
                    std::getline(std::cin, montoUsuario);

                    if (isValidMonto(montoUsuario)) {
                        break;
                    } else {
                        std::cout << "Monto inválido, vuelva a digitar." << std::endl;
                    }
                }

                if(clienteDB.actualizarCuenta(id, stod(montoUsuario),tipoDeCuenta,0)){
                    //Creo registro de la operacion
                    transferenciaDB.addTransaction(id, "Retiro",stod(montoUsuario),-1,getCurrentDateTime());
                    std::cout << "Retiro exitoso..." << std::endl;

                }else{
                    std::cout << "Ocurrio un error durante el retiro..." << std::endl;
                }
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

                      clienteDB.addCliente(askId, askName,0, 0, 0, getCurrentDateTime());
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

bool isPositiveDouble(const char &c) {
    return std::isdigit(c) || c == '.';
};

bool isValidMonto(const std::string &monto) {
    //Caso donde no se digita nada
    if (monto.empty()) return false; // Verifica si la cadena está vacía

    bool dotFound = false;
    //Recorro cada uno de los elementos del string
    for (char c : monto) {
        //Caso de encontrar espacios en el string
        if (std::isspace(c)) return false;
        //Caso de no digitar un double positivo 
        if (!isPositiveDouble(c)) return false;
        //Verifico si hay más de un punto decimal 
        if (c == '.') {
            if (dotFound) return false;
            dotFound = true;
        }
    }

    try {
        double value = std::stod(monto);
        //Verifico si el valor es positivo
        if (value <= 0) return false; 
    } catch (...) {
        //Caso de que falle el double
        return false; 
    }

    return true;
};

//Obtengo hora actual
std::string getCurrentDateTime() {
    //Obtengo la hora actual de la computadora
    auto now = std::chrono::system_clock::now();
    //Convierto a tiempo en formato time_t
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    //Convierto time_t a tm struct
    std::tm now_tm = *std::localtime(&now_time_t);
    //Uso stringstream para formatear la fecha y hora
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    //Retrono hora como string
    return oss.str();
}