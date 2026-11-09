# Variáveis de configuração
CC = gcc
CFLAGS = -Wall -std=c99 -Werror=implicit-function-declaration
LIBS = -lm
TARGET = prog
SRCS = $(wildcard *.c) # Detecta automaticamente todos os .c 
OBJS = $(SRCS:.c=.o) # Substitui a extensão .c por .o para gerar a lista de objetos

# Regra padrão
all: $(TARGET)

# Compilação do executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Regra para compilar os arquivos objeto
# Significado dos símbolos: $< = arquivo fonte (.c), $@ = arquivo objeto (.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de execução
run: $(TARGET)
	./$(TARGET)

# Regra para testar o programa
test: $(TARGET)
	./test.sh $(TARGET)

# Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run test clean
