# Compilador a utilizar
CXX ?= g++

# Banderas del compilador 
# -std=c++98: Utiliza el estándar C++98
# -Wall: Activa todas las advertencias del compilador para detectar errores
# -Ilibs: Incluye la carpeta 'libs' en la ruta de búsqueda de archivos #include
CXXFLAGS = -std=c++98 -Wall -Wextra -Ilibs

# Nombre del archivo ejecutable de salida
TARGET = arboles

# Archivos fuente (en este caso solo main.cpp ya que las librerías son templates .hpp)
SOURCES = main.cpp

# Regla por defecto
all: $(TARGET)

# Regla para enlazar y compilar el ejecutable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Regla para limpiar los archivos generados (.exe o binarios)
clean:
	rm -f $(TARGET) $(TARGET).exe

# Evita conflictos si existen archivos con los mismos nombres que las reglas lógicas
.PHONY: all clean