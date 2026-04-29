.PHONY: all clean

CC  = gcc
# Para usar o AddressSanitizer acrescentar no CFLAGS: -fsanitize=address -fno-omit-frame-pointer
# e no LDFLAGS: -fsanitize=address
CFLAGS =  -Wall -Werror=discarded-qualifiers -Wextra -O3 -march=native -flto -c -g -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS =  -O3 -march=native -flto `pkg-config --libs glib-2.0` -lncursesw

TARGET = programa-principal
TARGET_TESTES = programa-testes
TARGET_INTERATIVO = programa-interativo
TESTES_COMMAND_NAME = testar
INTERATIVO_COMMAND_NAME = interativo
SRC_DIR = src
OBJ_DIR = obj
RST_DIR = resultados

#todos os .c
SOURCES = $(shell find $(SRC_DIR) -name "*.c")

# todos os .o (transforma os .c em .o)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
RESULTS = $(shell find $(RST_DIR) -name "*.txt") $(shell find $(RST_DIR) -name "*.csv")

all: $(TARGET) $(TESTES_COMMAND_NAME) $(INTERATIVO_COMMAND_NAME)

$(TARGET): $(OBJECTS) programas/programa-principal.o
	$(CC) $(OBJECTS) programas/programa-principal.o -o $(TARGET) $(LDFLAGS)

$(TESTES_COMMAND_NAME): $(OBJECTS) programas/programa-testes.o
	$(CC) $(OBJECTS) programas/programa-testes.o -o $(TARGET_TESTES) $(LDFLAGS)

$(INTERATIVO_COMMAND_NAME): $(OBJECTS) programas/programa-interativo.o
	$(CC) $(OBJECTS) programas/programa-interativo.o -o $(TARGET_INTERATIVO) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Cria a pasta automaticamente para colocar os .o
	$(CC) $(CFLAGS) -c $< -o $@

programas/programa-principal.o: programas/programa-principal.c
	$(CC) $(CFLAGS) -c $< -o $@

programas/programa-testes.o: programas/programa-testes.c
	$(CC) $(CFLAGS) -c $< -o $@

programas/programa-interativo.o: programas/programa-interativo.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(RESULTS) $(TARGET_TESTES) $(TARGET_INTERATIVO) programas/*.o

# Debug - ver quais arquivos foram encontrados
debug:
	@echo "Sources encontrados:"
	@echo $(SOURCES)
	@echo "Objects gerados:"
	@echo $(OBJECTS)