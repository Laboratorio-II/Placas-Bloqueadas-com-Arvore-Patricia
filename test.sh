#!/bin/bash

# Variáveis para contagem de resultados
PASS=0
FAIL=0

# Tempo limite de cada teste, em segundos
LIMITE=2

# Executa o programa para cada caso de teste na pasta input/
for input_file in input/*; do
    filename=$(basename "$input_file")
    expected_file="output/$filename"

    # Verifica se o arquivo de saída esperado existe
    if [ ! -f "$expected_file" ]; then
        echo "ERRO: Arquivo de saída esperado não encontrado: $expected_file"
        exit 1
    fi

    # Executa o programa com o arquivo de entrada e captura a saída
    # Cada teste tem no máximo LIMITE segundos para terminar
    actual=$(timeout $LIMITE ./prog < "$input_file")
    exit_code=$?

    # Código 124 indica que o tempo limite foi excedido
    if [ $exit_code -eq 124 ]; then
        echo "Teste $filename: Tempo limite excedido ($LIMITE s)"
        FAIL=$((FAIL + 1))
        continue
    fi

    # Verifica se o programa saiu com código zero 
    if [ $exit_code -ne 0 ]; then
        echo "ERRO: Programa encerrou com código diferente de 0"
        FAIL=$((FAIL + 1))
        continue
    fi

    # Compara a saída real com a saída esperada
    expected=$(cat "$expected_file")
    if [ "$(echo "$actual" | tr -s '[:space:]')" = "$(echo "$expected" | tr -s '[:space:]')" ]; then
        echo "Teste $filename: Saída correta"
        PASS=$((PASS + 1))
    else
        echo "Teste $filename: Saída incorreta"
        echo "-- Saída Esperada:"
	echo "$expected"
        echo "-- Saída Obtida:" 
	echo "$actual"
        FAIL=$((FAIL + 1))
    fi
done

# Resumo dos testes
echo ""
echo "Resultado testes: $PASS corretos, $FAIL errados."

if [ $FAIL -eq 0 ]; then
    echo "Todos os testes corretos!"
    exit 0
else
    echo "Existem testes incorretos!"
    exit 1
fi
