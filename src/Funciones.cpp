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
void menuOperaciones(ClienteDB& clienteDB, const std::string& id, const std::string& tipoDeCuenta, TransactionDB& transferenciaDB, PrestamoDB& prestamosDB, CertificadoDepositoPlazo& certificadoDb) {
    //Caso donde seleciono cdp
    if (tipoDeCuenta == "3"){

        string operacionOpt;
        cout << "\nPor favor seleccione la operación que desea realizar\n";
        cout << "1. Depósitos\n";
        cout << "2. Retiros\n";
        cout << "Ingrese una opción: ";
        //cin >> operacionOpt;
        //cin.ignore(); // Se debe limpiar el buffer
        std::getline(std::cin, operacionOpt);
        removeWhiteSpaces(operacionOpt);

        if (all_of(operacionOpt.begin(), operacionOpt.end(), ::isdigit) &&
            (operacionOpt == "1" || operacionOpt == "2")) {
            // Se convierte la opción a entero
            int operacion = stoi(operacionOpt);
            std::string montoUsuario, tipoMoneda, selecionPrestamo;

            // Se realiza la logica para los tipos de operaciones
            switch (operacion) {

                case DEPOSITO:
                    std::cout << "Usted va a realizar un deposito en un certificado de depostio a plazo..." << std::endl;
                    //Deposito cdp
                    std::cout << "Informacion general ...." << std::endl;
                    std::cout << "Tasa de interes: 1,5 %" << std::endl;
                    std::cout << "Duracion: 1 anio" << std::endl;
                    std::cout << "Selecion de usuario, ingrese (colones o dolares)" << std::endl;
                    std::getline(std::cin, tipoMoneda);
                    removeWhiteSpaces(tipoMoneda);

                    if (tipoMoneda == "colones" || tipoMoneda == "dolares"){
                        while (true) {
                        std::cout << "Ingrese un monto a depositar: " << std::endl;
                        std::getline(std::cin, montoUsuario);

                        if (isValidMonto(montoUsuario)) {
                            break;
                        } else {
                            std::cout << "Monto inválido, vuelva a digitar." << std::endl;
                        }
                        }

                        string confirmacion;
                        std::cout << "¿Desea confirmar el CDP? (S/N (Presione cualquier tecla) ) : ";
                        //std::cin >> confirmacion;
                        std::getline(std::cin, confirmacion);
                        removeWhiteSpaces(confirmacion);

                        if (confirmacion == "S" || confirmacion == "s") {
                            //Agego cdp
                            certificadoDb.addCDP(stoi(id), stod(montoUsuario), tipoMoneda,1.5,1,getCurrentDateTime());
                            if (tipoMoneda == "colones"){
                                transferenciaDB.addTransaction(id, "CDP colones", stod(montoUsuario), -1,getCurrentDateTime());
                            } else{
                                transferenciaDB.addTransaction(id, "CDP dolares", stod(montoUsuario), -1,getCurrentDateTime());
                            }
                            std::cout << "CDP exitosamente efectuado... \n";
                        } else {
                            std::cout << "CDP NO efectudo... \n";
                        }

                    }else{
                        std::cout << "Ocurrio un error, deposito de CDP no efectuado" << std::endl;
                    }
                    
                    break;

                case RETIRO:
                    std::cout << "Usted va a realizar un retiro del CDP..." << std::endl;
                    // Retiros cdp
                    //Verifico que el usuario tenga cdps asociados
                    if (certificadoDb.idExiste(id)){
                        
                        //Vector con los numeros de id del cliente que pidio prestamo
                        std::vector<std::string> idVector = certificadoDb.cdpIdsCliente(id);
                        //Se le pide al usuario ingresar un valor
                        std::cout << "Selecione un IDs asociados al CDP del cliente " << id << ": ";
                        for (size_t i = 0; i < idVector.size(); ++i) {
                            std::cout << idVector[i];
                            if (i < idVector.size() - 1) {
                                std::cout << ", ";
                            }
                        }
                        std::cout << std::endl;
                        //std::cin >> selecionPrestamo;
                        //std::cin.ignore();
                        std::getline(std::cin, selecionPrestamo);
                        removeWhiteSpaces(selecionPrestamo);

                        //Verifico que el usuario agregue un id valido
                        if (std::find(idVector.begin(), idVector.end(), selecionPrestamo) != idVector.end()){
                            //Obtengo el monto, tasa y tipo moneda
                            auto info = certificadoDb.retornarInfo(selecionPrestamo); 
                            string confirmacion;
                            std::cout << "¿Desea retirar el cdp " << selecionPrestamo << " de :"<<std::get<0>(info)<<" " << std::get<1>(info) << " ? (S/N (Presione cualquier tecla) ) : ";
                            //std::cin >> confirmacion;
                            std::getline(std::cin, confirmacion);
                            removeWhiteSpaces(confirmacion);

                            if (confirmacion == "S" || confirmacion == "s") {
                                //Elimino cdp asociado
                                certificadoDb.deleteCDP(std::stoi(selecionPrestamo));
                                if ( std::get<1>(info) == "colones"){
                                    transferenciaDB.addTransaction(id, "Retiro CDP colones", std::get<0>(info), -1,getCurrentDateTime());
                                } else{
                                    transferenciaDB.addTransaction(id, "Retiro CDP dolares", std::get<0>(info), -1,getCurrentDateTime());
                                }
                                std::cout << "Retiro CDP exitoso... \n";
                            } else {
                                std::cout << "Retiro CDP NO efectudo... \n";
                            }
                            
                        } else{
                            throw std::invalid_argument("Debe ingresar un id valido, intente de nuevo...");
                        }
                        
                        
                    }else {
                        throw std::invalid_argument("Usuario ingresado no tiene cdps asociados, intente de nuevo...");
                    }
                    break;

                default:
                    cout << "Opción no valida\n";
                    break;
            }
        } else {
            throw std::invalid_argument("Ingresó una opción inválida vuelva a intentar...");
        }//aqui regresa al servicio al cliente
    
    }else{
        //Casos cuenta en dolares y colones
        string operacionOpt;
        cout << "\nPor favor seleccione la operación que desea realizar\n";
        cout << "1. Depósitos\n";
        cout << "2. Retiros\n";
        cout << "3. Transferencias entre cuentas\n";
        cout << "4. Abonos\n";
        cout << "Ingrese una opción: ";
        //cin >> operacionOpt;
        //cin.ignore(); // Se debe limpiar el buffer
        std::getline(std::cin, operacionOpt);
        removeWhiteSpaces(operacionOpt);

        if (all_of(operacionOpt.begin(), operacionOpt.end(), ::isdigit) &&
            (operacionOpt == "1" || operacionOpt == "2" || operacionOpt == "3" || operacionOpt == "4")) {
            // Se convierte la opción a entero
            int operacion = stoi(operacionOpt);
            std::string montoUsuario, tipoCuentaDestino, idCuentaDestino, selecionPrestamo;
            double montoUsuarioConversion;

            // Se realiza la logica para los tipos de operaciones
            switch (operacion) {

                case DEPOSITO:
                    std::cout << "Usted va a realizar un deposito..." << std::endl;
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
                        if (tipoDeCuenta == "1"){
                            transferenciaDB.addTransaction(id, "Depósito colones",stod(montoUsuario),-1,getCurrentDateTime());
                        }else{
                            transferenciaDB.addTransaction(id, "Depósito dolares",stod(montoUsuario),-1,getCurrentDateTime());
                        }
                        std::cout << "Depósito exitoso..." << std::endl;
        
                    }else{
                        std::cout << "Ocurrió un error durante el depósito..." << std::endl;
                    }
                    

                    break;

                case RETIRO:
                    std::cout << "Usted va a realizar un retiro..." << std::endl;
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
                        //transferenciaDB.addTransaction(id, "Retiro",stod(montoUsuario),-1,getCurrentDateTime());
                        if (tipoDeCuenta == "1"){
                            transferenciaDB.addTransaction(id, "Retiro colones",stod(montoUsuario),-1,getCurrentDateTime());
                        }else{
                            transferenciaDB.addTransaction(id, "Retiro dolares",stod(montoUsuario),-1,getCurrentDateTime());
                        }
                        std::cout << "Retiro exitoso..." << std::endl;

                    }else{
                        std::cout << "Ocurrió un error durante el retiro..." << std::endl;
                    }
                    break;

                case TRANSFERENCIA:
                    std::cout << "Usted va a realizar una transferencia..." << std::endl;
                    
                    // Obtener información del usuario
                    std::cout << "Ingrese el tipo de cuenta de destino (1 para colones, 2 para dolares): ";
                    //std::cin >> tipoCuentaDestino;
                    //std::cin.ignore();
                    std::getline(std::cin, tipoCuentaDestino);
                    removeWhiteSpaces(tipoCuentaDestino);

                    //Verifico si se agrega cuenta en colones, dolares o cdp
                    if(all_of(tipoCuentaDestino.begin(), tipoCuentaDestino.end(), ::isdigit) && (tipoCuentaDestino == "1" || tipoCuentaDestino == "2")){       
                
                        std::cout << "Ingrese el ID de la cuenta destino: ";
                        //std::cin >> idCuentaDestino;
                        //std::cin.ignore();
                        std::getline(std::cin, idCuentaDestino);
                        removeWhiteSpaces(idCuentaDestino);
                        
                        //Verifico que el usuario destino exista y que sea distino id usuario solicitante
                        if (clienteDB.idExiste(idCuentaDestino) && idCuentaDestino != id){
                            //Pregunto por monto double hasta que sea valido
                            while (true) {
                                std::cout << "Ingrese un monto a transferir: " << std::endl;
                                std::getline(std::cin, montoUsuario);

                                if (isValidMonto(montoUsuario)) {
                                    break;
                                } else {
                                    std::cout << "Monto inválido, vuelva a digitar." << std::endl;
                                }
                            }
                            
                            //Debo hacer conversion a dolares y colones y viceversa en caso de ser necesario
                            //Aqui paso de colones  a dolares, si seleciono colones o cdp y quiero transferir a dolares
                            if (tipoDeCuenta == "1"  && tipoCuentaDestino == "2"){
                                montoUsuarioConversion = stod(montoUsuario)/530;
                            }//Aqui paso de dolares a colones, si seleciono dolares y quiero transferir a colones o cdp
                            else if (tipoDeCuenta == "2" && tipoCuentaDestino == "1"){
                                montoUsuarioConversion = stod(montoUsuario)*530;
                            }else{
                                //Esta variable sera diferente en caso de hacer una conversion
                                montoUsuarioConversion = stod(montoUsuario);
                            }
                            
                            //En este caso retiro dinero de la cuenta de origen si la cuenta tiene fondos
                            if (clienteDB.actualizarCuenta(id, stod(montoUsuario),tipoDeCuenta,0)){

                                //En este caso agrego dinero de la cuenta de destino
                                clienteDB.actualizarCuenta(idCuentaDestino, montoUsuarioConversion,tipoCuentaDestino);
                                // Mensajes de éxito de la transferencia
                                //Operaciones se agregan al registro de transacciones
                                transferenciaDB.addTransaction(id, "Retiro de transferencia",stod(montoUsuario),-1,getCurrentDateTime());
                                transferenciaDB.addTransaction(idCuentaDestino, "Depósito de transferencia",montoUsuarioConversion,-1,getCurrentDateTime());
                                std::cout << "Transferencia exitosa." << std::endl;
                                std::cout << "Ha transferido " << montoUsuario << " de la cuenta de origen (" << id << ") a la cuenta de destino (" << idCuentaDestino << ")." << std::endl;
                            
                            } else{
                                std::cout << "Ocurrió un error durante la transferencia..." << std::endl;
                            }
                            
                        }else {
                            throw std::invalid_argument("Usuario inexistente o  invalido,vuelva a intentar...");
                        }
                        
                    }else {
                        throw std::invalid_argument("Se ingresó una opción NO válida, debe ingresar 1 o 2,vuelva a intentar...");
                    }
    
        break;
                case ABONO:
                    std::cout << "Usted va a realizar un abono..." << std::endl;
                    //Abonos
                    
                    std::cout << "Ingrese el ID de la cuenta destino: ";
                    //std::cin >> idCuentaDestino;
                    //std::cin.ignore();
                    std::getline(std::cin, idCuentaDestino);
                    removeWhiteSpaces(idCuentaDestino);
                    
                    //Verifico que el usuario destino exista y determino si tiene prestamos asociados
                    if (prestamosDB.idExiste(idCuentaDestino)){
                        
                        //Vector con los numeros de id del cliente que pidio prestamo
                        std::vector<std::string> idVector = prestamosDB.prestamosIdsCliente(idCuentaDestino);
                        //Se le pide al usuario ingresar un valor
                        std::cout << "Selecione un IDs asociados a prestamos del cliente " << idCuentaDestino << ": ";
                        for (size_t i = 0; i < idVector.size(); ++i) {
                            std::cout << idVector[i];
                            if (i < idVector.size() - 1) {
                                std::cout << ", ";
                            }
                        }
                        std::cout << std::endl;
                        //std::cin >> selecionPrestamo;
                        //std::cin.ignore();
                        std::getline(std::cin, selecionPrestamo);
                        removeWhiteSpaces(selecionPrestamo);

                        //Verifico que el usuario agregue un id valido
                        if (std::find(idVector.begin(), idVector.end(), selecionPrestamo) != idVector.end()){
                            //Obtengo el monto mensual del prestamo
                            std::pair<double, std::string> resultado = prestamosDB.obtenerMonto(selecionPrestamo);
                            
                            double cuotaMensual = resultado.first;
                            std::string moneda = resultado.second;  

                            string confirmacion;
                            std::cout << "¿Desea pagar la cuota "<< cuotaMensual << " en " << moneda <<" como abono al préstamo? (S/N (Presione cualquier tecla) ) : ";
                            //std::cin >> confirmacion;
                            std::getline(std::cin, confirmacion);
                            removeWhiteSpaces(confirmacion);

                            if (confirmacion == "S" || confirmacion == "s") {
                                //cuota mensual en colones, usuario retira dolares
                                if (tipoDeCuenta == "2" && moneda == "colones"){
                                    montoUsuarioConversion = cuotaMensual/530;

                                }else if (tipoDeCuenta == "1" && moneda == "dolares") {
                                    //cuota mensual colares y usuario retira ccolones
                                    montoUsuarioConversion = cuotaMensual*530;
                                }else{
                                    //No hay conversion
                                    montoUsuarioConversion = cuotaMensual;
                                }
                                
                                //En este caso retiro dinero de la cuenta de origen si la cuenta tiene fondos
                                if (clienteDB.actualizarCuenta(id, montoUsuarioConversion,tipoDeCuenta,0)){
                                    if (moneda == "colones"){
                                        transferenciaDB.addTransaction(id, "Abono en colones",montoUsuarioConversion,stoi(selecionPrestamo),getCurrentDateTime());
                                    }else{
                                        transferenciaDB.addTransaction(id, "Abono en dolares",montoUsuarioConversion,stoi(selecionPrestamo),getCurrentDateTime());
                                    }
                                    
                                    
                                    //Decremento en 1 la cantidad de cuotas hasta que el prestamo este pagado.
                                    prestamosDB.abonarPrestamo(selecionPrestamo);
                                    std::cout << "Abono exitoso... \n";
                                } else{
                                    std::cout << "Ocurrió un error durante el abono, abono NO efectuado..." << std::endl;
                                }
                            } else {
                                std::cout << "Abono NO efectudo... \n";
                            }
                            
                        } else{
                            throw std::invalid_argument("Debe ingresar un id valido, intente de nuevo...");
                        }
                        
                        
                    }else {
                        throw std::invalid_argument("Usuario ingresado no tiene prestamos asociados, intente de nuevo...");
                    }
                        
                    break;
                //Me falta agregar una opcion para salir o regresar
                default:
                    cout << "Opción no valida\n";
                    break;
            }
        } else {
            throw std::invalid_argument("Ingresó una opción inválida vuelva a intentar...");
        }//aqui regresa al servicio al cliente
    }
};

void userNotExist(ClienteDB& clienteDB){

  std::cout << "El número de identificación del usuario ingresado NO está registrado" << std::endl;
  string createUserOptTwo;

  //Menu de pregunta
  cout << "\nCrear usuario\n";
  cout << "1. Sí\n";
  cout << "2. No\n";
  cout << "Ingrese una opción: ";
  //cin >> createUserOptTwo;
  //cin.ignore(); // Limpiar el buffer
  std::getline(std::cin, createUserOptTwo);
  removeWhiteSpaces(createUserOptTwo);

  if(all_of(createUserOptTwo.begin(), createUserOptTwo.end(), ::isdigit) && (createUserOptTwo == "1" || createUserOptTwo == "2")){
      
  if (createUserOptTwo == "1"){

          std::string askId;
          std::cout << "Ingrese el número de identificación del cliente: ";
          std::getline(std::cin, askId);
          removeWhiteSpaces(askId);

          if(all_of(askId.begin(), askId.end(), ::isdigit) && askId.length()>0){

              int askIdConvert = stoi(askId);

              if (askIdConvert > 0 && askIdConvert < 999999999){
                  
                  if (!clienteDB.idExiste(askId)){

                      std::string askName;
                      std::cout << "Ingrese el nombre del cliente: ";
                      std::getline(std::cin, askName);

                      clienteDB.addCliente(askId, askName,0, 0, getCurrentDateTime());
                      std::cout << "Usuario creado exitosamente..." << std::endl;
                  
                  }else{
                      throw std::invalid_argument("Debe ingresar otro número de identificacion, vuelva a intentar...");
                  }

              }else{
                  throw std::invalid_argument("Debe ingresar un número entero entre 0 y 999999999, vuelva a intentar...");
              }
              
          }else{
              throw std::invalid_argument("Debe ingresar un número entero, vuelva a intentar...");
          }
      
      }

  }else{
      throw std::invalid_argument("Se ingreso una opción NO válida, vuelva a intentar...");
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

// Para validar la entrada plazo
bool isValidPlazo(const std::string &plazo) {
    //Caso donde no se digita nada
    if (plazo.empty()) return false; // Verifica si la cadena está vacía

    //Recorro cada uno de los elementos del string
    for (char c : plazo) {
        //Caso de encontrar espacios en el string
        if (!std::isdigit(c)) return false;
        
    }

    try {
        double value = std::stoi(plazo);
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

//Remuevo espacios en blanco
void removeWhiteSpaces(std::string &str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
}