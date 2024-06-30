# ie0217-proyecto
Este repositorio es creado con el propósito de utilizarse como repo para desarrollar el proyecto final del curso de Estructuras Abstractas de Datos y Algoritmos para Ingeniería IE-0217.
## Grupo 2 estudiantes:
- Kryssia Martinez, carnet B84636.
- Jose Pablo Laurent, carnet B63761
- Susan Morales Alfaro, carnet A94203
## Tabla de Contenidos
1. [Descripción general del proyecto](#descripción)
2. [Instrucciones de Ejecución](#instrucciones)
3. [Notas](#notas)
4. [Primera parte del proyecto](#primera)
5. [Segunda parte del proyecto](#segunda)
6. [Estructura del Proyecto](#estructura)
7. [Prerrequisitos](#prerrequisitos)
8. [Instalación y Configuración](#instalación)
9. [Pruebas](#pruebas)
10. [Lecciones Aprendidas](#lecciones)
11. [Desafíos y Soluciones](#desafíos)
12. [Futuras Mejoras](#futuras)
13. [Conclusiones](#conclusiones)
14. [Documentacion](#documentación)
## 1. Descripción general del proyecto
 El proyecto tiene como objetivo desarrollar un sistema de gestión bancaria utilizado por agentes en ventanillas para atender a clientes en una entidad bancarias.

## 2. Instrucciones de Ejecución
Para compilar y ejecutar este proyecto, se deben seguir los siguientes pasos:
1. Clone el repositorio desde GitHub en su máquina local utilizando el siguiente comando:
```bash
git clone <URL_del_repositorio_del_proyecto>
```
- Reemplace <URL_del_repositorio_del_proyecto> por la url del repositorio de git.
2. Abra una terminal.
3. Navegue al directorio donde se encuentran los archivos, en este caso la estructura esta formada por una carpeta llamada src
Ejemplo de como se la navegación hasta la carpeta:
```
PS C:\Users\Dell\Desktop\ie0217-proyecto> cd src
PS C:\Users\Dell\Desktop\ie0217-proyecto\src>
PS C:\Users\Dell\Desktop\ie0217-proyecto\src>  mingw32-make
>>
```
4. Ejecute el siguiente comando para compilar el programa y generar el ejecutable que a su vez inicia el programa con el menu de entrada del proyecto:
```bash
mingw32-make
```
- Una vez compilado correctamente, se ve de la siguiente forma: 
```bash
g++ -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite -c main.cpp
g++ -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite -c clientDb.cpp
g++ -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite -c Funciones.cpp
g++ -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite -c prestamosDb.cpp
g++ -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite -c transactionDb.cpp
g++ -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite -c CertificadoDepositoPlazo.cpp
g++ -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite -o main.exe main.o clientDb.o Funciones.o prestamosDb.o transactionDb.o CertificadoDepositoPlazo.o -lsqlite3 -static-libgcc -static-libstdc++
```
- De esa manera se genera un archivo ejecutable, por favor escriba lo siguiente para ingresar al menu:
Ejemplo de como se ve el uso del comando:
```bash
.\main.exe
```
7. Siga las instrucciones en pantalla para interactuar con el programa.
Ejemplo de salida del menú:
```Modalidad de operación
1. Atención al cliente
2. Información general sobre préstamos bancarios
3. Salir
Ingrese una opción:
```
## 3. Notas
- Este proyecto lleva los comentarios necesarios para dar a entender lo que se realizó durante su desarrollo y al final se encuentra la documentación creada de manera adecuada.


## 4. Primera parte del proyecto
## Parte Teórica
### Sistema de gestión bancaria
- **Qué es un sistema de gestión bancaria:**
    - La gestión bancaria se encarga de controlar y rastrear el flujo de dinero de una entidad, de esa manera se pueden tomar las medidas necesarias para que una compañía sea más rentable y segura económicamente.

    - En este caso, el sistema de gestión bancaria a realizar en este proyecto se trata de un sistema que va a utilizarse para gestionar ingresos, gastos y activos de las personas que lo utilicen, así como informar a las personas sobre los tipos de préstamos y todo lo necesario acerca de las cuentas bancarias. Esto mediante el menú de entrada interactivo, con las diferentes opciones para que una persona pueda obtener información y gestionar algún cambio en sus cuentas.

- **Funcionalidades:**
    - Sobre gestión de cuentas: En este caso, para este sistema un cliente puede tener hasta 2 cuentas bancarias, una en colones y otra en dólares, en las cuales puede gestionar sus ahorros o los certificados de depósito a corto plazo.
    - Transacciones: Referente a las transacciones, se puede acceder a la parte de registro, desde el menú, inicialmente una persona puede interactuar con las opciones disponibles para adquirir información o bien registrarse, ver los tipos de préstamo e incluso obtener la tabla de valores con las cuotas y tasas de interés.
    - Préstamos: Referente a esta etapa, se trabajará con préstamos personales, prendarios e hipotecarios en los cuales una persona puede adquirir uno, abonarlo o incluso abonar el de otras personas.
- **Normativa:**
    - Regulaciones bancarias aplicables: Esta parte es importante, en un banco normalmente se tiene un sistema que regula cuidadosamente las transacciones que realizan las personas, así como la confidencialidad la protección de datos, se previene el lavado de dinero y se intenta cumplir las normas del banco y otros organismos reguladores, para obtener un préstamo usualmente se hace un estudio, en el cual es necesario cumplir con ciertos requisitos y presentar documentos que respalden esos requisitos, después se revisan y se procede a hacer un estudio para rechazar o aprobar.
    - Cumplimiento de la normativa y seguridad: Luego, por esta parte el banco asegura la seguridad a sus clientes, con un sistema robusto que mantiene la integridad y confidencialidad de los datos de los clientes. Aquí se incluye el uso de protocolos de seguridad para la transmisión de datos y el almacenamiento seguro de información sensible de cada persona.

    - En este sistema: En el caso de este sistema, se intentará realizar un sistema seguro con manejo de excepciones, para el correcto funcionamiento y a los clientes se le asignará un numero de identificación único.
### Modalidad de operación:
- **Información general:**
    - Muestra opciones de préstamos personales, prendarios e hipotecarios, de manera adicional genera una tabla de pagos de acuerdo a la información elegida.
- **Atención al cliente:**
    - Procesos y operaciones realizadas en la atención directa a clientes.
<!-- **información general sobre los préstamos:**
    - información que se proporciona:
    - Herramientas y cálculos utilizados para mostrar opciones de préstamos.-->
### Tipos de préstamos:
- **Préstamos personales:**
    Este tipo de préstamo permite pedir dinero prestado a una institución financiera sin necesidad de tener como respaldo un bien en específico. Usualmente su tasa de interés suele ser más alta que las de otros tipos de préstamos debido a que no cuenta con el respaldo de un determinado bien. Según, el Banco de Costa Rica (BCR) las tasas de interés anual es alrededor de **15% - 20%**.
- **Préstamos prendarios:**
    Este tipo de préstamo consiste en prestar dinero, donde el préstamo se encuentra respaldado por un bien tangible. En caso de no poder pagar el préstamo, la institución financiera se quedará con el bien tangible. En Costa Rica, la tasa de interés anual para préstamos prendarios (préstamos con garantía) puede variar dependiendo de la institución financiera y las condiciones del mercado. Actualmente, los préstamos con garantía tienen tasas de interés entre el **12% y el 16%** anual​.
- **Préstamos hipotecarios:**
    El préstamo hipotecario consiste en prestar una determinada cantidad de dinero para la compra de una propiedad, si el prestatario no cumple con el pago el prestamista tiene derecho a tomar la propiedad. Las tasas de interés para préstamos hipotecarios en el Banco de Costa Rica (BCR) pueden estar alrededor del **8%** a **9%** anual.
- **Calculo de tablas de pagos:**
    - Fórmulas y métodos para calcular cuotas mensuales y tablas de interés: En este caso se puede utilizar una fórmula de amortización, la fórmula de interés compuesto para calcular las cuotas mensuales de los préstamos, para imprimir la tabla de pagos esperados. 

    - **Tasa de interés mensual:**


         ![Fórmula interés mensual](https://latex.codecogs.com/svg.image?&space;r=\frac{r_{a}}{12})

         - r, es la tasa de interés mensual y r_a es la tasa de interés anual.

    - **Cuota mensual:** 


         ![Fórmula cuota mensual](https://latex.codecogs.com/svg.image?&space;M=P\frac{r(1&plus;r)^{n}}{(1&plus;r)^{n}-1})


         - P es el monto del préstamo, r es la tasa de interés mensual y n es el número total de cuotas.
- **Valores personalizados:**
    - Cálculo de tablas con valores personalizados de monto, cuotas, y tasa de interés: En esta opción se hace uso de la misma fórmula, pero el usuario tiene la opción de obtener la tabla mediante valores personalizados puede ingresar el monto, la cantidad de cuotas y la tasa de interés, de esa manera se imprime la información esperada.

### Cuentas bancarias:
- **Tipos de cuentas:**
    - Cuenta en colones: El cliente tiene la opción de tener una cuenta bancaria para gestionar sus ahorros.
    - Cuenta en dólares: De manera análoga, el cliente tiene la opción de tener una cuenta bancaria para gestionar sus ahorros.
    - Certificados de depósito a plazo (CDP): El cliente tiene la opción de depositar una cantidad de dinero, en un periodo de tiempo fijo, a cambio de una tasa de interés más alta que una cuenta de ahorros, donde el dinero depositado no se podrá retirar antes de periodo de tiempo establecido sin incurrir en penalizaciones.
### Operaciones:
- **Depósitos:**
    El cliente podrá depositar dinero dentro de sus cuentas bancarias, ya sea en colones o en dólares.
    <!--El cliente podrá realizar depósitos a su préstamos, donde estos podrán ser una fracción del préstamos total aunado a la tasa de interés o se podrá pagar la totalidad del préstamos aunado a la tasa de interés..-->
- **Retiros:**
    El cliente podrá realizar retiros de su cuenta en colones o de sus cuentas en dólares, este retiro debe ser una fracción o la totalidad del dinero contenido en la cuenta bancaria seleccionada.
- **Transferencias:**
    El cliente podrá realizar transferencias entre cuentas bancarias, donde los clientes receptores deben de existir y el monto no debe superar la totalidad del monto almacenado dentro de la cuenta del emisor.
- **Abonos a préstamos:**
    El cliente podrá realizar abonos a sus préstamos, donde estos podrán ser una fracción del préstamos total aunado a la tasa de interés o se podrá pagar la totalidad del préstamos aunado a la tasa de interés.
### Registro de las transacciones
- **Métodos disponibles:**
    Las transacciones serán almacenadas en una base de datos SQL, que almacenará un número de identificación del cliente, tipo de transacción efectuada, monto de la transacción efectuada y fecha a la que se efectuó la transacción.
### Seguridad
- **Método de identificación de los clientes:**
    Los clientes serán almacenados dentro de una base de datos SQl, que contendrá las columnas de un número de identificación único para cada cliente entre 0 y 999999999, saldo de la cuenta en colones, saldo de la cuenta en dólares, tipo de préstamo, saldo del tipo de préstamo y fecha a la que se creó el usuario del cliente.
### Préstamos asociados y Reportes:
- **Estructura de los Préstamos:**
    - Características específicas como tasa de interés, período y cuota mensual:
        - Cada préstamo tendrá un registro que incluirá el monto principal, la tasa de interés, el plazo del préstamo (en meses), la cuota mensual, y la fecha de inicio.
- **Generación de reportes:**
    - Reportes detallados en formato tabular:
        - El sistema va a generar un archivo de texto con un reporte que incluye las cuotas pagadas hasta la fecha, incluyendo un desglose del monto destinado a capital y los intereses abonados hasta el momento.


   
## 5. Segunda parte del proyecto
## Etapa de diseño
### **Descripción del Diagrama**

#### 1. **Inicio:** 
 El sistema se inicia y presenta dos opciones principales: "Atención a Clientes" e "Información General sobre Préstamos". 

#### 2. **Selección de Modalidad:** 

 - Si se selecciona "Atención a Clientes", el flujo pasa a la interacción con los clientes. 

 - Si se selecciona "Información General sobre Préstamos", el flujo permite al usuario consultar información de préstamos y generar tablas de pagos. 

#### 3. **Interacción con Clientes:**

 - **Identificación del Cliente:** El agente ingresa el número de identificación del cliente. 

 - **Verificación de la Identidad:** El sistema verifica la identidad del cliente. 

 - **Operaciones Bancarias:** El cliente puede realizar operaciones como depósitos, retiros, transferencias y abonos a préstamos. 

 - **Registro de Transacciones:** Cada transacción se registra en la base de datos. 

 - **Generación de Reportes:** El cliente puede solicitar un reporte de sus préstamos. 

#### 4. **Información General sobre Préstamos:**

 - **Consulta de Tipos de Préstamos:** El usuario selecciona entre préstamos personales, prendarios e hipotecarios. 

 - **Generación de Tabla de Pagos:** El sistema genera una tabla de pagos esperados según el monto ingresado. 

 - **Personalización de Valores:** El usuario puede ingresar valores personalizados para monto, cuotas y tasa de interés. 

#### 5. **Fin:** 
 El flujo termina y el sistema puede cerrar la sesión o reiniciar para otra operación. 

#### **Diagrama**
 A continuación se muestra el diagrama que representa el sistema de gestión bancaria, que refleja los procesos clave desde la interacción inicial hasta la realización de las operaciones bancarias y la generación de informes.

![Diagrama](gestionBancaria.png)

### **Cronograma**
 Se planifica un cronograma detallado de actividades, asignando responsabilidades específicas a cada integrante del proyecto.

![Cronograma del Proyecto](Cronograma1.PNG)

## 6. Estructura del Proyecto
- Este proyecto se encuentra segmentado de la siguiente manera:

IE0217-PROYECTO/

├── databases/  
│  └── banco.db  
├── src/   
│   ├── main.cpp  
│   ├── clientDb.cpp  
│   ├── Funciones.cpp  
│   ├── prestamosDb.cpp  
│   ├── transactionDb.cpp  
│   ├── CertificadoDepositoPlazo.cpp  
│   ├── clientDb.hpp  
│   ├── Funciones.hpp  
│   ├── prestamosDb.hpp  
│   ├── transactionDb.hpp  
│   └── CertificadoDepositoPlazo.hpp  
├── readme.md  
├── Cronograma1.PNG  
└── gestionBancaria.png

- Cada uno de los archivos agregados son una parte importante para el correcto funcionamiento del sistema de gestion bancaria y fueron agregados para cumplir con las peticiones y requerimientos del enunciado del proyecto final.

- Acontinuación encontrará una descripcion de cada uno de los archivos y los puntos importantes. 
### Descripcion detallada de los archivos:

- *Main.cpp*: 
    - En este archivo se encuentra el punto de entrada del programa. Se encarga de inicializar las bases de datos y de ejecutar los diferentes menús del sistema bancario. A través de este archivo, se llaman a múltiples funciones y clases definidas en otros archivos importantes del proyecto.
    - Contenido:
        - Inclusión de librerías importantes: Se incluyen las librerías de C++ y las librerías específicas del proyecto como Funciones.hpp, clientDb.hpp, transactionDb.hpp y prestamosDb.hpp.
        - Enumeraciones: Se definen varias enumeraciones entre ellas Opciones, OpcionesGnerales, Operaciones, que son necesarias para gestionar las opciones del menú.
        - Declaraciones de funciones: En este caso se declaran las funciones necesarias para el funcionamiento del programa, como por ejemplo el menuOperaciones.
        - Función main: Es la que contiene la lógica principal para el desarrollo del programa, incluyendo la inicialización de las instancias de las clases ClienteDB, TransactionDB, PrestamoDB, y CertificadoDepositoPlazo.
        - Se realiza la creación de tablas en la base de datos.
        - Por ultimo se implementan los menús de interacción y el manejo de excepciones para validar las entradas del usuario.
    - Métodos y clases utilizadas:
        - ClienteDB: Es el que maneja operaciones relacionadas con la base de datos de clientes.
        - TransactionDB: Maneja las operaciones relacionadas con la base de datos de la parte de transacciones.
        - PrestamoDB: Se encarga de manejar las operaciones relacionadas con la base de datos de préstamos bancarios.
        - CertificadoDepositoPlazo: La ultima parte que se encargfa de las operaciones relacionadas con los certificados de depósito a plazo.

- *CertificadoDepositoPlazo.cpp*:
    - En este archivo se implementa la clase CertificadoDepositoPlazo, que gestiona la interacción con la base de datos de certificados de depósito a plazo (CDP).
    - Contenido: 
        - Se encuentra el constructor llamado `CertificadoDepositoPlazo(const std::string& dbPath)`, se encarga de iniciar la conexión a la base de datos y el destructor llamado `~CertificadoDepositoPlazo()`, que se encarga de cerrar la conexión con la base de datos.
    - Métodos: 
        - `createTable():` Crea la tabla cdp en la base de datos si no existe.
        - `addCDP(int clientId, double monto, const std::string& tipoMoneda, double tasaInteres, int duracion, const std::string& fecha):` Agrega un nuevo CDP a la base de datos.
        - `deleteCDP(int id):` Elimina un CDP de la base de datos.
        - `viewCDPs():` Muestra todos los CDP en la base de datos.
        - `idExiste(const std::string& id):` Verifica si un CDP existe en la base de datos.
        - `cdpIdsCliente(const std::string& clientId):` Retorna una lista de IDs de CDP asociados a un cliente.
        - `retornarInfo(const std::string& idCdp):` Retorna la información de un CDP específico.
        - `executeQuery(const std::string& query):` Ejecuta una consulta SQL en la base de datos.
        -  Callbacks: En este caso se basa en los métodos que procesan los resultados de las consultas SQL (callback, idExisteCallback, obtenerCdpsCallback, retornarInfoCallback).
- *clientDb.cpp:*
    - Este archivo se encarga de implementar la funcionalidad de la clase ClienteDB, que gestiona una base de datos SQLite para almacenar información de clientes. Contiene métodos para la creación de tablas, insertar y eliminar datos de clientes, visualización de datos de clientes, actualización de cuentas y verificación de la existencia de clientes.
    - Contenido: 
       - Inclusión de Librerías: Incluye clientDb.hpp, <iostream> y <stdexcept> para la definición de la clase y manejo de excepciones.

        - Constructor y Destructor: Define el constructor ClienteDB para abrir una conexión a la base de datos y el destructor para cerrarla adecuadamente.
    - Métodos:
        - `createTable`: Crea la tabla clientes en la base de datos si no existe.
        - `addCliente`: Inserta un nuevo cliente en la tabla clientes.
        - `deleteCliente`: Elimina un cliente de la tabla clientes basado en su ID.
        - `viewClientes`: Muestra todos los clientes almacenados en la base de datos.
        - `actualizarCuenta`: Actualiza el saldo de una cuenta de cliente (colones o dólares) según la operación especificada.
        - `executeQuery`: Método privado utilizado para ejecutar consultas SQL en la base de datos.
        - callback: Callback utilizado para procesar resultados de consultas SQL.
- *clientDb.hpp:*
    - Este archivo contiene la declaración de la clase ClienteDB, que gestiona operaciones en la base de datos SQLite para el almacenamiento de datos de clientes.
- *Funciones.cpp:*
    - Este archivo contiene la implementación de diversas funciones relacionadas con las operaciones bancarias, validaciones de entrada y gestión del tiempo.
    - Contenido:
        - Inclusión de librerías: 
            - Se incluyen las librerías estándar de C++ y las librerías específicas del proyecto como clientDb.hpp, transactionDb.hpp, prestamosDb.hpp y CertificadoDepositoPlazo.hpp.
        - Definición de funciones:
            - `menuOperaciones`: Implementa las operaciones disponibles para diferentes tipos de cuentas, incluyendo depósitos, retiros, transferencias y abonos. Gestiona interacciones con el usuario para cada operación, valida entradas y actualiza registros correspondientes en las bases de datos.
            - `userNotExist`: Maneja el caso en el que un usuario no está registrado, ofreciendo la opción de crear un nuevo usuario ingresando su número de identificación y nombre.
        - Funciones de validación:
            - `isPositiveDouble`: Verifica si un carácter es un dígito o un punto.
            - `isValidMonto`: Valida que la entrada del usuario para monto sea un número positivo, sin espacios en blanco y con formato válido.
            - `isValidPlazo`: Valida que la entrada del usuario para el plazo en años sea un número entero positivo.
            - getCurrentDateTime: Retorna la fecha y hora actuales en formato "YYYY-MM-DD hh:mm".
    - Métodos y clases:
        - `ClienteDB`: Gestiona operaciones relacionadas con la base de datos de clientes.
        - `TransactionDB`: Maneja operaciones relacionadas con la base de datos de transacciones.
        - `PrestamoDB`: Maneja operaciones relacionadas con la base de datos de préstamos.
        - `CertificadoDepositoPlazo`: Maneja operaciones relacionadas con los certificados de depósito a plazo.
        - `removeWhiteSpaces`: Elimina los espacios en blanco de una cadena de texto.
- *ClientDb.hpp:*
    - contiene las declaraciones de funciones y las inclusiones necesarias para operaciones bancarias específicas implementadas en el proyecto. Define funciones relacionadas con la gestión de clientes, transacciones, préstamos y certificados de depósito a plazo. 

- *prestamosDb.cpp:*
    - Contenido:
        - Bibliotecas:
            - #include "prestamosDb.hpp": Incluye la declaración de la clase PrestamoDB.
            - #include <iostream>: Para operaciones estándar de entrada/salida.
            - #include <filesystem>: Para crear directorios de reportes.
            - #include <fstream>: Para operaciones de archivos de salida.
            - #include <iomanip>: Para formateo de salida.
            - #include <stdexcept>: Para excepciones estándar.
            - #include <cmath>: Para cálculos matemáticos, como el cálculo de la cuota mensual.
        - Constructor y destructor:
            - `PrestamoDB`::PrestamoDB(const std::string& dbPath): Abre la base de datos SQLite en la ruta especificada dbPath.
            - `PrestamoDB`::~PrestamoDB(): Cierra la conexión con la base de datos SQLite al destruir el objeto.
    - Métodos:
        - `createTable()`: Crea la tabla prestamos en la base de datos si no existe.
        - `calcularMensualidad(double monto, double tasaInteres, int cuotas)`: Calcula la cuota mensual de un préstamo basado en el monto, la tasa de interés y el número de cuotas.
        - addPrestamo(...): Agrega un nuevo préstamo a la base de datos con detalles como el cliente, tipo de préstamo, monto, fecha, cuotas, tasa de interés y moneda.
        - `deletePrestamo(int id)`: Elimina un préstamo de la base de datos dado su id.
        - `viewPrestamo(const std::string& clientID)`: Genera un reporte en formato de tabla de los préstamos asociados a un cliente y lo guarda en un archivo .txt.
        - `idExiste(const std::string& id)`: Verifica si existe algún préstamo asociado a un cliente específico.
        - `prestamosIdsCliente(const std::string& clientId)`: Retorna un vector de strings con los IDs de los préstamos asociados a un cliente.
        - `obtenerMonto(const std::string& prestamoId)`: Retorna la cuota mensual y la moneda de un préstamo dado su ID.
        - `abonarPrestamo(const std::string& prestamoId)`: Reduce en 1 la cantidad de cuotas de un préstamo y verifica si el préstamo ha sido pagado completamente.
        - `executeQuery(const std::string& query)`: Ejecuta una consulta SQL en la base de datos SQLite.
        - callback, idExisteCallback, obtenerPrestamosCallback, obtenerMontoCallback, obtenerCuotasCallback: Funciones utilizadas como callbacks para procesar resultados de consultas SQL.
- *prestamosDb.hpp:*
    - contiene la declaración de la clase `PrestamoDB`, que gestiona operaciones relacionadas con los préstamos.
- *transactionDb.cpp:*
    - El archivo `TransactionDB.cpp` contiene la implementación de los métodos declarados en TransactionDB.hpp para la gestión de transacciones en una base de datos SQLite.
    - Contenido: 
        - Bibliotecas:
            - #include "TransactionDB.hpp": Incluye el archivo de encabezado TransactionDB.hpp para acceder a la definición de la clase TransactionDB.
            - #include <iostream>: Para la salida estándar y manejo de errores.
            - #include <stdexcept>: Para el manejo de excepciones estándar.
    - Métodos:
        - bool TransactionDB::addTransaction(...): Método para agregar una nueva transacción a la base de datos.
        - bool TransactionDB::deleteTransaction(int id): Método para eliminar una transacción de la base de datos dado su ID.
        - bool TransactionDB::executeQuery(const std::string& query): Método privado para ejecutar consultas SQL en la base de datos SQLite y manejar errores de ejecución.
        - void TransactionDB::viewTransaction(): Método para imprimir todas las transacciones almacenadas en la base de datos.
        - bool TransactionDB::idExiste(const std::string& id): Método para verificar la existencia de una transacción específica en la base de datos dado su ID.
- *transactionDb.hpp:*
    - El archivo TransactionDB.hpp contiene la declaración de la clase TransactionDB, que gestiona operaciones relacionadas.
    - Contenido: 
        - Directivas:
            - #ifndef TRANSACTIONDB_HPP y #define TRANSACTIONDB_HPP: Directivas para prevenir la inclusión múltiple del archivo de encabezado TransactionDB.hpp.
            - #endif // TRANSACTIONDB_HPP: Cierra la directiva de preprocesador #ifndef para TransactionDB.hpp.
        - Clase:
            - Define la clase TransactionDB, que encapsula la funcionalidad para gestionar transacciones.
 

## 7. Prerrequisitos
- En esta seccion se describen los prerrequisitos asi como la lista de software y herramientas necesarias para ejecutar el proyecto de manera correcta asi como las versiones específicas de compiladores y las librerías.

- **Compilador:**
  - Se requiere `g++` y que posea soporte para C++17 o versiones superiores.
  - Se recomienda utilizar MinGW para compilar en entornos como Windows como es el caso, pero tambien este proyecto puede ser ejecutado en Linux sin ningun problema ya que hicimos pruebas en ambos sistemas.
  
- **Bibliotecas:**
  - Se requiere SQLite3 ya que es utilizada en la base de datos del proyecto.

## 8. Instalación y Configuración
- En esta seccion puede encontrar las instrucciones necesarias y detalladas sobre cómo configurar el entorno de desarrollo y cualquier configuración específica que sea parte de los requerimientos del sistema.

### Configuración del Entorno de Desarrollo e instalacion si es necesaria

1. **Compilador:**
   - Es neccesario poseer un entorno adecuado, para ello recuerde instalar MinGW siguiendo las instrucciones en [MinGW Installation Guide](https://mingw-w64.org/doku.php/download).
   - Luego recuerde asegurarse de que `g++` esté disponible en la línea de comandos y configurado en las variables de entorno PATH, ya que es necesario.
   - Ademas puede utilizar el makefile implementado para complicar los archivos y generar el ejecutable, asi como limpiar los archivos generados de ser necesario.
2. **SQLite3:**
   - Esta parte es importante, ya que es la parte con la que desarrollamos la base de datos, por lo cual sino la posee en su sitema, debe descargar SQLite3 desde [SQLite Download Page](https://sqlite.org/download.html) e instalarlo según las instrucciones que se encuentran disponibles en el sitio.


## 9. Pruebas y demostracion de resultados
    
- En esta parte hemos agregado una pequeña demostracion de algunas funciones.
Acontinuacion se encuentra una muestra de la informacion de las tablas en la base de datos:
- Tabla inicial CDP:
![Tabla inicial CDP](./cdp1.PNG)

- Tabla inicial clientes:
![Tabla inicial clientes](./clientes2.PNG)

- Tabla inicial de cuotas:
![Tabla inicial de cuotas](./cuotasp.PNG)

- Tabla inicial de prestamos:
![Tabla inicial de prestamos](./prestamos.PNG)

- Tabla inicial registro:

![Tabla inicial registro](./conteo.PNG)

- Tabla inicial de transferencias:
![Tabla inicial de transferencias](./registro.PNG)

- Si desea realizar una transaccion con un cliente que existe se ve de la siguiente manera:
![Cliente existe](./clientee.PNG)

- Tabla clienta Ana Maria:
![Tabla de cliente](./clientes2.PNG)

- Si desea realizar una transaccion con un cliente que no existe se ve de la siguiente manera, se agrega el cliente y se realiza un prestamo:
![Tabla de cliente](./clienten.PNG)

- Tabla actualizada cliente nueva Andrea:
![Tabla de cliente](./clientn.PNG)

- Tabla con el prestamo nuevo:
![Tabla de prestamo](./prestamo1.PNG)

- Registro de las transacciones:
![Tabla de transaccion](./prueba.PNG)

- Si desea agregar un cdp:
![Tabla de cdp](./cdp.PNG)

- Cuando se agrega, se ve de la siguiente manera:
![Tabla de cdp](./cdpa.PNG)


## 10. Aprendizaje

- En esta seccion nos gustaria destacar que durante el desarrollo de este proyecto enfocado en el desarrollo de una entidad que funciona como un sistema de gestión bancaria como si fuera una persona en ventanilla, se adquirieron y reforzaron diversas habilidades y conocimientos en diferentes áreas así como aprender acerca de los conceptos y el funcionamiento de los prestamos y diferentes transacciones como abonos, certificados de deposito a plazos y diversas transferencias entre cuentas de colones o dólares, se aprendieron cosas en las siguientes áreas:

### Programación en C++ con el curso y los videos de las clases
- **Clases y Objetos**: Ya que a lo largo del curso se aprendio acerca de la implementación de clases, en este caso nos airvio para manejar diferentes entidades del sistema bancario como `ClienteDB`, `TransactionDB`, `PrestamoDB`, y `CertificadoDepositoPlazo`.
- **Herencia y Polimorfismo**: Se utilizo como apoyo programación orientada a objetos para facilitar la extensión y el mantenimiento del código a lo largo de la implementación del mismo.
- **Manejo de Memoria**: En este caso, el manejo y la utilización de punteros fue un reto ya que debe usarse correctamente para manejar la memoria dinámica de manera segura.
- **Estructuras de Datos**: En este caso se implementaron estructuras de datos personalizadas para gestionar la cantidad de información necesaria, se usan diferentes tablas para guardar la información.

### Manejo de Bases de Datos
- **SQLite**: En este caso es impotante, ya que el proyecto utiliza bases de datos, fue un reto aprender a utilizarlo correctamente y a su vez aprender el funcionamiento de cada parte y la manera en la que incluimos la informacion. Aca se logra integrar la base de datos y usamos SQLite para almacenar y recuperar datos de clientes, transacciones y préstamos.
  - **Aprendizaje desde cero**: Mediante lo visto en clase logramos adquirir los conocimientos basicos para manipular SQLite, y en un proceso de prueba y error a lo largo del proyecto ya que no se tenía mucho conocimiento previo en esta parte.
  - **Consultas SQL**: Se utilizo al igual que se aprendio para realizar una de las tareas la escritura de consultas SQL para realizar operaciones CRUD (Crear, Leer, Actualizar, Borrar) en la base de datos.
  - **Conexión y Manejo**: En esta parte logramos aprender sobre cómo conectar C++ de visual studio code con la base de datos SQLite y manejar las conexiones y operaciones de manera eficiente para desarrollar la totalidad del proyecto.
  - **DB Browser for SQLite**: En este caso utilizamos y aprendimos acerca de DB Browser para SQLite, nos permitio visualizar y gestionar los datos en las tablas, de esa manera se facilita el proceso de desarrollo y depuración de la información.


### Herramientas de Desarrollo
- **Visual Studio Code**: Se hizo uso del entorno de desarrollo integrado (IDE) para la edición y depuración de código como lo aqprendimos en el curso.
- **GCC y MinGW**: Se utilizaron estas herramientas y se aprendio mas acerca de la configuración y el uso del compilador GCC en el entorno MinGW para compilar el proyecto de manera correcta.
- **Makefile**: Como se aprendio a lo largo del curso se implemento la creación del Makefile para automatizar el proceso de compilación y la construcción del proyecto.


## 11. Desafios y soluciones
Durante el desarrollo del proyecto, enfrentamos varios desafíos. Tuvimos que cambiar ya ajustar diferentes partes para concretar correctamente lo que se queria realizar.

| Desafío | Descripción | Solución |
| --- | --- | --- |
| Ingresar correctamente Datos en las Tablas y las diferentes columnas. | Surgieron problemas al ingresar datos en las columnas de las tablas de la base de datos, por lo tanto se causaban errores y datos faltantes o inclusive datos que no se utilizaban en algunas partes del proyecto. | Se implementaron diferentes validaciones para asegurar que los datos ingresados fueran los correctos antes de ser insertados en la base de datos, asi como el dato y la columna a la que debia ir. |
| Información de menús de navegación. | En uno de los menús pedía el ID del cliente repetidamente, lo que podia causar confusión en el flujo de la navegación del código. | Se hizo un ajuste en los menús para que el ID del cliente se pidiera una sola vez y se reutilizara el dato de manera correcta a lo largo del código. |
| Manejar correctamente los caracteres especiales | El programa se caía al ingresar caracteres especiales, espacios o letras donde debían ir números y diferentes problemas relacionados con la interaccion del usuario. | Se añadieron validaciones de entrada para garantizar que solo se aceptaran datos válidos en cada campo y no se caiga el programa. |
| Realizar transferencias bancarias | Habian problemas al realizar transferencias, a veces al realizar las transferencias los datos no se reflejaban en la tabla de transacciones. | Se depuró el código de las transferencias para asegurar que todas las operaciones fueran las correctas y se restara la cantidad donde debia ser y a su vez que se reflejara correctamente la informacion en la base de datos. |
| La organización en el diseño del código | Al inicio fue complicado organizar las diferentes partes del programa, especialmente la entrada de datos y los menús, al realizar el diagrama de flujo no teniamos vision de como se iba ir acomodando todo. | Se reacomodaron algunas partes en el código dividiéndolo en funciones y clases más manejables, siguiendo en su mayoria la estructura del diagrama de flujo propuesto en el primer avance del proyecto. |

### Manejo de Errores y Depuración
- **Advertencias del Compilador**: Realizamos mensajes de advertencias y errores generados por el compilador, asi como el reordenamiento de inicializadores y variables no utilizadas para mejorar el uso de las buenas practicas de programación que hemos desarrollado a lo largo del curso.
- **Depuración**: También se utilizaron herramientas y técnicas de depuración para identificar y corregir los diferentes errores descritos anteriormente en el código.

### Gestión de Proyectos
- **Estructuración del Proyecto**: Se procedio a organizar del código fuente y todo el contenido en una estructura de carpetas para mejorar su lógica y que fuera manejable.
- **Documentación**: Se realizo la redacción de la documentación lo más claro posible y de forma detallada para facilitar la comprensión y el mantenimiento del proyecto y generar el doxyfile asi como aprendimos en el curso para alojarlo en netlify.


## 12. Mejoras futuras del funcionamiento 

- Sugerimos que en el futuro este código puede ser mejorado o manipulado por otras personas para ser de mayor utilidad.

1. **Interfaz Gráfica de Usuario (GUI)**: Se podria implementar una interfaz gráfica para mejorar la experiencia del usuario en comparación con la interfaz desde la línea de comandos actual.
2. **Autenticación y Seguridad**: Además podria agregarse mecanismos de autenticación más robustos y cifrado de datos para proteger la información de los clientes y las transacciones y otras funcionalidades que se nos puedan ocurrir.
3. **Manejo de Errores Avanzado**: Se podria implementar un sistema de manejo de errores más elaborado.
4. **Notificaciones y Alertas**: Se podria agregar un sistema de notificaciones por correo electrónico o SMS para alertar a los clientes sobre actividades importantes en sus cuentas o cosas similares.

Estas son algunas de las mejoras que podriamos implementar en un fututo o con mas tiempo para realizar de una mejor manera este proyecto, de igual manera estamos satisfechos con los resulatados adquiridos hasta este punto. 


## 13. Conclusiones

Este proyecto que simula un sitema de gestión bancaria ha sido una experiencia enriquecedora que ha permitido desarrollar una aplicación que resulta funcional para la gestión de clientes, transacciones, préstamos y certificados de depósito a plazo. A través de este proyecto, alcanzamos los objetivos planteados al inicio con el diseño del diagrama de flujo. Se realizaron pruebas importantes que nos permitieron llegar al resultado obtenido y completar todos los requirimientos planteados en el enunciado de este proyecto final.

Se creo un sistema robusto que permite realizar operaciones bancarias básicas de manera eficiente y segura. El sistema maneja depósitos, retiros, transferencias y consultas de saldos de manera efectiva, utilizando la base de datos SQLite. Durante el desarrollo de este proyecto, adquirimos conocimiento en algunas areas y reforzamos lo aprendido a lo largo del curso.Se enfrentaron y resolvieron los problemas que tuvimos en algunas partes del código y se logro llegar a completar las funciones básicas que debia realizar el sistema. En conclusión al realizar este proyecto en su totalidad reafirmamos los conocimientos adquiridos a lo largo de las clases.

## 14. Documentación Generada por Doxygen


La documentación de este proyecto ha sido generada utilizando Doxygen.


### Acceder a la Documentación en Formato HTML


Se puede acceder a la documentación en formato HTML siguiendo este enlace:
[Documentación HTML](https://6681ea25ca7a2bb3ff96244d--teal-gecko-b02ed0.netlify.app/)

- Ejemplo visual:
![Tabla de cdp](./sitio.PNG)