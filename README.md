# ie0217-proyecto
Este repositorio es creado con el propósito de utilizarse como repo para desarrollar el proyecto final del curso de Estructuras Abstractas de Datos y Algoritmos para Ingeniería IE-0217.
## Grupo 2 estudiantes:
- Kryssia Martinez carne B84636.
- Jose Pablo Laurent carne B63761
-
## Tabla de Contenidos
1. [Descripción general del proyecto](#descripción)
2. [Instrucciones de Ejecución](#instrucciones)
3. [Notas](#notas)
4. [Primera parte del proyecto](#primera)
5. [Segunda parte del proyecto](#segunda)
## 1. Descripción general del proyecto
- ...
## 2. Instrucciones de Ejecución
Para compilar y ejecutar este proyecto, se deben seguir los siguientes pasos:
1. Clone el repositorio desde GitHub en su máquina local utilizando el siguiente comando:
```bash
git clone <URL_del_repositorio_del_proyecto>
```
- Reemplace <URL_del_repositorio_del_proyecto> por la url del repositorio de git.
2. Abra una terminal.
3. Navegue al directorio donde se encuentran los archivos, en este caso la estructura esta formada por una carpeta llamada ........
Ejemplo de como se la navegación hasta la carpeta: (REEMPLAZAR)
```
PS C:\Users\Dell\Desktop\ie0217> cd Tareas
PS C:\Users\Dell\Desktop\ie0217\Tareas> cd Tarea5
PS C:\Users\Dell\Desktop\ie0217\Tareas\Tarea5> cd src
PS C:\Users\Dell\Desktop\ie0217\Tareas\Tarea5\src> mingw32-make
>>
```
4. Ejecute el siguiente comando para compilar el programa y generar el ejecutable que a su vez inicia el programa con el menu de entrada del proyecto:
```bash
mingw32-make
```
De esa manera se genera un archivo ejecutable.
Ejemplo de como se ve el uso del comando: (REEMPLAZAR)
```
PS C:\Users\Dell\Desktop\ie0217\Tareas\Tarea5\src> mingw32-make
>>
```
4. Una vez compilado correctamente, se ve de la siguiente forma: (REEMPLAZAR)
```bash
g++ -std=c++11 -Wall -c main.cpp -o main.o
g++ -std=c++11 -Wall -c ValidadorEmail.cpp -o ValidadorEmail.o
g++ -std=c++11 -Wall -o tarea5.x main.o ValidadorEmail.o
./tarea5.x
```
7. Siga las instrucciones en pantalla para interactuar con el programa.
Ejemplo de salida del menu:
```bash
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
    - Sobre gestión de cuentas
    - Transacciones
    - Préstamos
- **Normativa:**
    - Regulaciones bancarias aplicables:
    - Cumplimiento de la normativa y seguridad:
### Modalidad de operación:
- **Información general:**
    - Muestra opciones de préstamos personales, prendarios e hipotecarios, de manera adicional genera una tabla de pagos pagos de acuerdo a la información elegida.
- **Atención al cliente:**
    - Procesos y operaciones realizadas en la atención directa a clientes.
<!-- **información general sobre los préstamos:**
    - información que se proporciona:
    - Herramientas y cálculos utilizados para mostrar opciones de préstamos.-->
### Tipos de préstamos:
- **Préstamos personales:**
    Este tipo de préstamo permite pedir dinero prestado a una institución financiera sin necesidad de tener como respaldo un bien en específico. Usualmente su tasa de interés suele ser más alta que las de otros tipos de préstamos debido debido a que no cuenta con el respaldo de un determinado bien.
- **Préstamos prendarios:**
    Este tipo de préstamo consiste en prestar dinero, donde el préstamo se encuentra respaldado por un bien tangible. En caso de no poder pagar el préstamo, la institución financiera se quedará con el bien tangible.
- **Préstamos hipotecarios:**
    El préstamo hipotecario consiste en prestar una determinada cantidad de dinero para la compra de una propiedad, si el prestatario no cumple con el pago el prestamista tiene derecho a tomar la propiedad.
- **Calculo de tablas de pagos:**
    - Fórmulas y métodos para calcular cuotas mensuales y tablas de interés:
- **Valores personalizados:**
    - Cálculo de tablas con valores personalizados de monto, cuotas, y tasa de interés:
### Cuentas bancarias:
- **Tipos de cuentas:**
    - Cuenta en colones: El cliente tiene la opción de tener una cuenta bancaria para gestionar sus ahorros.
    - Cuenta en dólares: De manera análoga, el cliente tiene la opción de tener una cuenta bancaria para      gestionar sus ahorros.
    - Certificados de depósito a plazo (CDP): El cliente tiene la opción de depositar una cantidad de dinero, en un periodo de tiempo fijo, a cambio de una tasa de interés más alta que una cuenta de ahorros, donde el dinero depositado no se podrá retirar antes de periodo de tiempo establecido sin incurrir en penalizaciones.
### Operaciones:
- **Depósitos:**
    El cliente podrá depositar dinero dentro de sus cuentas bancarias, ya sea en colones o en dólares.
    <!--El cliente podrá realizar depósitos a su préstamos, donde estos podrán ser una fracción del préstamos total aunado a la tasa de interés o se podrá pagar la totalidad del préstamos aunado a la tasa de interés..-->
- **Retiros:**
    El cliente podrá realizar retiros de su cuenta en colones o de sus cuenta en dólares, este retiro debe ser una fracción o la totalidad del dinero contenido en la cuenta bancaria seleccionada.
- **Transferencias:**
    El cliente podrá realizar transferencias entre cuentas bancarias, donde los clientes receptores deben de existir y el monto no debe superar la totalidad del monto almacenado dentro de la cuenta del emisor.
- **Abonos a préstamos:**
    El cliente podrá realizar abonos a su préstamos, donde estos podrán ser una fracción del préstamos total aunado a la tasa de interés o se podrá pagar la totalidad del préstamos aunado a la tasa de interés.
### Registro de las transacciones
- **Métodos disponibles:**
    Las transacciones serán almacenadas en una base de datos SQL, que almacenará un número de identificación del cliente, tipo de transacción efectuada, monto de la transacción efectuada y fecha a la que se efectuó la transacción.
### Seguridad
- **Método de identificación de los clientes:**
    Los clientes serán almacenados dentro de una base de datos SQl, que contendrá las columnas de un número de identificación único para cada cliente entre 0 y 999999999, saldo de la cuenta en colones, saldo de la cuenta en dólares, tipo de prestamo, saldo del tipo de prestamo y fecha a la que se creó el usuario del cliente.
### Préstamos asociados y Reportes:
- **Estructura de los Préstamos:**
    - Características específicas como tasa de interés, período y cuota mensual:
- **Generación de reportes:**
    - Cómo crear reportes detallados de préstamos en formato tabular:
- **Desglose de pagos:**
    -Diferencia entre aporte al capital y los intereses:


   
## 5. Segunda parte del proyecto
## Etapa de diseño


![Diagrama](gestionBancaria.png)




## Documentación Generada por Doxygen


La documentación de este proyecto ha sido generada utilizando Doxygen. (AGREGAR MAS COSAS)


### Acceder a la Documentación en Formato HTML


Se puede acceder a la documentación en formato HTML siguiendo este enlace:
[Documentación HTML](REEMPLAZAR)

