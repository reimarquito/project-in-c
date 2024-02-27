#include <stdio.h>
#include <string.h>
#include "equipamentos.h"
#include "input.h"

#define VALOR_INVALIDO "O valor inserido é inválido."

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int obterInt(int minValor, int maxValor, char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

float obterFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

double obterDouble(double minValor, double maxValor, char *msg) {
    double valor;
    printf(msg);
    while (scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

char obterChar(char *msg) {
    char valor;
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    return valor;
}

void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

const char* categoriaToString1(Categoria categoria) {
    switch (categoria) {
        case Impressora:
            return "Impressora";
        case Computador:
            return "Computador";
        case Portátil:
            return "Portátil";
        case Monitor:
            return "Monitor";
        case Router:
            return "Router";
        case Switch:
            return "Switch";
        case Projetor:
            return "Projetor";
        case Controlador_de_acessos:
            return "Controlador_de_acessos";
        case Rato:
            return "Rato";
        case Acessório:
            return "Acessório";
        case Outro:
            return "Outro";
        default:
            return "Desconhecido";
    }
}

const char* categoriaToString2(Tipo estado) {
    switch (estado) {
        case Operacional:
            return "Operacional";
        case Em_Manutenção:
            return "Em_Manutenção";
        case Não_Operacional:
            return "Não_Operacional";
        case Para_Reciclagem:
            return "Para_Reciclagem";
            ;
    }
}
