#ifndef MANUTENCAO_H
#define MANUTENCAO_H

#include "utilizadores.h"
#include "input.h"
#include "equipamentos.h" 

#define MAX_TAMANHO_INFORMACAO 30
#define MAX_TAMANHO_DATA 15
#define MAX_ID_MANUTENCAO 5
#define MSG_PARA_OBTER_INFORMACAO_MANUTENCAO "Insira a informaçao da manutencao:"
#define MSG_PARA_OBTER_NUMERO_MANUTENCAO "Insira o numero da manutencao:"
#define MSG_OBTER_DATA_CRIACAO "Insira a data de criacao da manutencao(dd/mm/aaaa):" 
#define MSG_MANUTENCAO_ATUALIZADA "Manutençao atualizada com sucesso :)"
#define ERRO_MANUTENCAO_A_NAO_EXISTE "Erro, a manutecao nao existe :("
#define ERRO_LISTA_ESTA_CHEIA "Erro a lista esta cheia"
#define ERRO_LISTA_ESTA_VAZIA "Erro a lista esta vazia"  
#define MSG_MANUTENCAO_ATUALIZADO "Manutencao atualizada com sucesso :)"

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    int idmanutencao;
    char informacao[MAX_TAMANHO_INFORMACAO];
    int idequipamento;
    char dataCriacao[MAX_TAMANHO_DATA];
    char idUtilizador[MAX_UTILIZADOR]; // Código do utilizador associado
}Manutencao;

typedef struct {
    int contador, tamanho;
    Manutencao *manutencoes;
} Manutencoes;

int procurarManutencao(Manutencoes manutencoes, int numero);
int carregarManutencoes(Manutencoes *manutencoes, char *ficheiro);
void libertarManutencoes(Manutencoes *manutencoes);
int inserirManutencao(Manutencoes *manutencoes, Utilizadores *utilizadores, Equipamentos *equipamentos);
void inserirManutencoes(Manutencoes *manutencoes, Utilizadores *utilizadores, Equipamentos *equipamentos, char *ficheiro);
void procurarManutencoes(Manutencoes manutencoes);
void atualizarManutencoes(Manutencoes *manutencoes, char *ficheiro);
void listarManutencoes(Manutencoes manutencoes);



#endif /* MANUTENCAO_H */

