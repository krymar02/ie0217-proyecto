# Makefile realizado para compilar el proyecto de gestion bancaria

# por aca se realiza la definición del compilador y las banderas de compilación
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wno-reorder -Wno-unused-variable -IC:\sqlite -LC:\sqlite

# En esta parte se encuentra el nombre del archivo ejecutable y lista de archivos objeto
TARGET = main.exe
OBJS = main.o clientDb.o Funciones.o prestamosDb.o transactionDb.o CertificadoDepositoPlazo.o

# Por este lado se encuentra la regla para construir todos los objetivos
all: $(TARGET)


# luego la regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lsqlite3 -static-libgcc -static-libstdc++

# Posteriormente se agregan las reglas para construir cada archivo objeto individualmente
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clientDb.o: clientDb.cpp clientDb.hpp
	$(CXX) $(CXXFLAGS) -c clientDb.cpp

Funciones.o: Funciones.cpp Funciones.hpp
	$(CXX) $(CXXFLAGS) -c Funciones.cpp

prestamosDb.o: prestamosDb.cpp prestamosDb.hpp
	$(CXX) $(CXXFLAGS) -c prestamosDb.cpp

transactionDb.o: transactionDb.cpp transactionDb.hpp
	$(CXX) $(CXXFLAGS) -c transactionDb.cpp

CertificadoDepositoPlazo.o: CertificadoDepositoPlazo.cpp CertificadoDepositoPlazo.hpp
	$(CXX) $(CXXFLAGS) -c CertificadoDepositoPlazo.cpp

# Y por ultimo se realiza la limpieza de archivos objeto y el ejecutable
clean:
	del *.o main.exe
