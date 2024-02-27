#ifndef UTILIZADORES_H
#define UTILIZADORES_H

#include "input.h"

#define MAX_ID_UTILIZADOR 5
#define MAX_UTILIZADOR 20
#define MSG_PARA_OBTER_ID_UTILIZADOR "Insira o id do utilizador:"
#define MUDAR_ESTADO_UTILIZADOR "Mudou o estado com sucesso :)"
#define ERRO_O_UTILIZADOR_NAO_EXISTE "Erro o utilizador nao existe :("
#define MSG_PARA_OBTER_NOME_UTILIZADOR "Insira o nome do utilizador:"
#define MSG_PARA_OBTER_SIGLA_UTILIZADOR "Insira a sigla do utilizador:"
#define MSG_PARA_OBTER_FUNCAO_UTILIZADOR "Insira a funcao do utilizador:"
#define MSG_UTILIZADOR_ATUALIZADO "Utilizador atualizado com sucesso :)"
#define ERRO_O_UTILIZADOR_NAO_EXISTE "Erro o utilizador nao existe :("
#define ERRO_LISTA_ESTA_CHEIA "Erro a lista esta cheia"
#define ERRO_LISTA_ESTA_VAZIA "Erro a lista esta vazia"  
#define MSG_UTILIZADOR_REMOVIDO "Utilizador foi removido com sucesso :)"

typedef enum {
    Inativo, Ativo
} Tipo_utilizador;

typedef struct {
    char ID_utilizador[MAX_ID_UTILIZADOR];
    char sigla[MAX_UTILIZADOR];
    char nome[MAX_UTILIZADOR];
    char funcao[MAX_UTILIZADOR];
    Tipo_utilizador tipo;
    int utilizador;
} Utilizador;

/**
 * guarda o numero de utilizadores
 * @param contador de utilizadores
 */

typedef struct {
    int contador, tamanho;
    Utilizador *utilizadores;
} Utilizadores;

int procurarUtilizador(Utilizadores utilizadores, char codigo[MAX_ID_UTILIZADOR]);
int carregarUtilizadores(Utilizadores *utilizadores, char *ficheiro);
void libertarUtilizadores(Utilizadores *utilizadores);
void atualizarEstadoUtilizador(Utilizadores *utilizadores, char *ficheiro);
void inserirUtilizadores(Utilizadores *utilizadores, char *ficheiro);
void procurarUtilizadores(Utilizadores Utilizador);
void atualizarUtilizadores(Utilizadores *utilizadores, char *ficheiro);
void removerUtilizadores(Utilizadores *utilizadores, char *ficheiro);
void listarUtilizadores(Utilizadores utilizadores);

#endif /* UTILIZADORES_H */

