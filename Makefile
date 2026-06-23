# --- CONFIGURACION DEL COMPILADOR ---
CC         := mpicc
CFLAGS     := -Wall -Wextra -Wpedantic -std=c11 -Iinclude $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS    := -lpthread $(shell pkg-config --libs gtk+-3.0)

# --- DIRECTORIOS ---
SRC_DIR    := src
TEST_DIR   := tests
OBJ_DIR    := build
BIN_DIR    := bin

# --- OBJETOS ---
# Lista de todos los archivos .o que necesitamos generar
OBJS       := $(OBJ_DIR)/main.o \
              $(OBJ_DIR)/client.o \
              $(OBJ_DIR)/coordinator.o \
              $(OBJ_DIR)/mpi_wrapper.o \
              $(OBJ_DIR)/protocol.o \
			  $(OBJ_DIR)/gui.o \

# --- EJECUTABLE FINAL ---
TARGET     := $(BIN_DIR)/mpi_messaging
# --- REGLAS PRINCIPALES ---
all: $(TARGET)

# Como enlazar el ejecutable final
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@
	@echo "Program ready on ./$@. Me go home."

# --- REGLAS DE COMPILACION DE OBJETOS ---
# Regla para compilar los .c que estan en src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla especifica para compilar el archivo de tests/
$(OBJ_DIR)/tests.o: $(TEST_DIR)/tests.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para crear las carpetas si no existen
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# --- PRUEBAS ---
test: $(TARGET)
	@echo "Executing test unit (Unity)"
	./$(TARGET) -DTESTING
	valgrind ./$(TARGET)
# --- LIMPIEZA ---
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaning done. me go home. ('/build' & '/bin' removed)"

.PHONY: all clean test