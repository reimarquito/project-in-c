#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "equipamentos.h"
#include "utilizadores.h"

#define TAM_INICIAR_UTILIZADOR 5

/**
 * Imprimir um certo Utilizador
 * @param Utilizador  para Buscar a struct Utilizador
 */

void imprimirUtilizador(Utilizador utilizador) {
    printf("ID: %s\n", utilizador.ID_utilizador);
    printf("Nome: %s\n", utilizador.nome);
    printf("Sigla: %s\n", utilizador.sigla);
    printf("Funçao: %s\n", utilizador.funcao);
    printf("Tipo: %s\n", utilizador.tipo == Ativo ? "Ativo" : "Inativo");
}

/**
 * apagar dados da memoria dinamica
 * @param utilizador para Buscar a struct utilizador
 */
void apagarDadosUtilizador(Utilizador *utilizador) {
    if (utilizador->tipo == Inativo) {
        strcpy(utilizador->nome, "");
        strcpy(utilizador->ID_utilizador, "");
        strcpy(utilizador->sigla, "");
        utilizador->utilizador = 0;
    }
}

/**
 *   procurar dados na memoria dinamica
 * @param Utilizador para Buscar a struct Utilizador
 * @param o contador vai receber o codigo do Utilizador
 */

int procurarUtilizador(Utilizadores utilizadores, char codigo[MAX_ID_UTILIZADOR]) {
    int i;
    for (i = 0; i < utilizadores.contador; i++) {
        if (strcmp(utilizadores.utilizadores[i].ID_utilizador, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * obter o numero de utilizador no ficheiro binario
 * @param Ficheiro receber o nome do ficheiro
 */
int obterContadorFXUtilizador(char* ficheiro) {
    int contador;
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    }
    return contador;
}

/**
 * carregar o utilizadores do ficheiro para a memoria 
 * @param Utilizador para Buscar a struct Utilizador
 * @param Ficheiro receber o nome do ficheiro 
 */

int carregarUtilizadores(Utilizadores *utilizadores, char *ficheiro) {
    int sucesso;
    sucesso = 0;
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&utilizadores->contador, sizeof (int), 1, fp);
        if (utilizadores->contador > 0) {
            utilizadores->utilizadores = (Utilizador*) malloc(utilizadores->contador * sizeof (Utilizador));
            fread(utilizadores->utilizadores, sizeof (Utilizador), utilizadores->contador, fp);
            utilizadores->tamanho = utilizadores->contador;
            sucesso = 1;
        }
        fclose(fp);
    }

    if (sucesso != 1) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            utilizadores->utilizadores = (Utilizador*) malloc(TAM_INICIAR_UTILIZADOR * sizeof (Utilizador));
            utilizadores->contador = 0;
            utilizadores->tamanho = TAM_INICIAR_UTILIZADOR;
            fclose(fp);
            sucesso = 1;
        }
    }
    return sucesso;
}

/**
 * libertar a memoria dimanica
 * @param utilizador para Buscar a struct utilizador
 */
void libertarUtilizadores(Utilizadores *utilizadores) {
    free(utilizadores->utilizadores);
}

/**
 * atualizar o contador no ficheiro binario
 * @param contador receber o numero do contador da memoria
 * @param ficheiro receber o nome do ficheiro
 */
void atualizarContadorFXUtilizador(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

/**
 *   inserir um novo utilizador ao ficheiro
 * @param Utilizador para Buscar a struct Utilizador
 * @param ficheiro receber o nome do ficheiro
 */

void inserirUtilizadorFX(Utilizadores utilizadores, char *ficheiro) {
    atualizarContadorFXUtilizador(utilizadores.contador, ficheiro);
    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&utilizadores.utilizadores[utilizadores.contador - 1], sizeof (Utilizador), 1, fp);
    fclose(fp);
}

/**
 *   atualizar o utilizador no ficheiro
 * @param Utilizador para Buscar a struct Utilizador
 * @param ficheiro receber o nome do ficheiro
 */

void atualizarUtilizadorFX(Utilizadores *utilizadores, int i, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fseek(fp, sizeof (int), SEEK_SET);
    fseek(fp, sizeof (Utilizador) * i, SEEK_CUR);
    fwrite(&(utilizadores->utilizadores[i]), sizeof (Utilizador), 1, fp);
    fclose(fp);
}

/**
 *   remover utilizador no ficheiro
 * @param Utilizador para Buscar a struct Utilizador
 * @param ficheiro receber o nome do ficheiro
 */

void removerUtilizadorFX(Utilizadores utilizadores, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&utilizadores, sizeof (Utilizador), 1, fp);
    fwrite(utilizadores.utilizadores, sizeof (Utilizador), utilizadores.contador, fp);
    fclose(fp);
}

/**
 *   atualiza o estado do utilizador 
 * @param Utilizador para Buscar a struct Utilizador
 * @param ficheiro receber o nome do ficheiro
 */

void atualizarEstadoUtilizador(Utilizadores *utilizadores, char *ficheiro) {
    int numero;
    char codigo[MAX_ID_UTILIZADOR];
    cleanInputBuffer();
    lerString(codigo, MAX_ID_UTILIZADOR, MSG_PARA_OBTER_ID_UTILIZADOR);
    numero = procurarUtilizador(*utilizadores, codigo);

    if (numero != -1) {
        utilizadores->utilizadores[numero].tipo = (utilizadores->utilizadores[numero].tipo == Ativo) ? Inativo : Ativo;

        atualizarUtilizadorFX(utilizadores, numero, ficheiro);
        puts(MUDAR_ESTADO_UTILIZADOR);
    } else {
        puts(ERRO_O_UTILIZADOR_NAO_EXISTE);
    }
}

/**
 *   obter informacoes do utilizadores
 * @param Utilizador para Buscar a struct Utilizador
 */

int inserirUtilizador(Utilizadores *utilizadores) {
    char codigo[MAX_ID_UTILIZADOR];
    lerString(codigo, MAX_ID_UTILIZADOR, MSG_PARA_OBTER_ID_UTILIZADOR);
    strcpy(utilizadores->utilizadores[utilizadores->contador].ID_utilizador, codigo);
    lerString(utilizadores->utilizadores[utilizadores->contador].nome, MAX_UTILIZADOR, MSG_PARA_OBTER_NOME_UTILIZADOR);
    lerString(utilizadores->utilizadores[utilizadores->contador].sigla, MAX_UTILIZADOR, MSG_PARA_OBTER_SIGLA_UTILIZADOR);
    lerString(utilizadores->utilizadores[utilizadores->contador].funcao, MAX_UTILIZADOR, MSG_PARA_OBTER_FUNCAO_UTILIZADOR);
    utilizadores->utilizadores[utilizadores->contador].tipo = Ativo;
    return utilizadores->contador++;
}

/**
 *   obter informacoes do utilizador para atualizar a empresa
 * @param Utilizador para Buscar a struct Utilizador
 */

void atualizarUtilizador(Utilizador *utilizador) {
    lerString(utilizador->nome, MAX_UTILIZADOR, MSG_PARA_OBTER_NOME_UTILIZADOR);
    lerString(utilizador->sigla, MAX_UTILIZADOR, MSG_PARA_OBTER_SIGLA_UTILIZADOR);
    lerString(utilizador->funcao, MAX_UTILIZADOR, MSG_PARA_OBTER_FUNCAO_UTILIZADOR);
    printf(MSG_UTILIZADOR_ATUALIZADO);
}

/**
 *   expandir memoria dinamica dos utilizadores
 * @param Utilizador para Buscar a struct Utilizador
 */
void expandirUtilizadores(Utilizadores *utilizadores) {
    Utilizador *temp = (Utilizador*) realloc(utilizadores->utilizadores, sizeof (Utilizador) * (utilizadores->tamanho * 2));
    if (temp != NULL) {
        utilizadores->tamanho *= 2;
        utilizadores->utilizadores = temp;
    }
}

/**
 *   funcao para verificar se ha tamanho na memoria e colocar no ficheiro
 * @param Utilizador para Buscar a struct Utilizador
 * @param ficheiro receber o nome do ficheiro
 */
void inserirUtilizadores(Utilizadores *utilizadores, char *ficheiro) {
    if (utilizadores->contador == utilizadores->tamanho) {
        expandirUtilizadores(utilizadores);
    }

    if (utilizadores->contador < utilizadores->tamanho) {
        int indice = inserirUtilizador(utilizadores);
        if (indice != -1) {
            inserirUtilizadorFX(*utilizadores, ficheiro);
        } else {
            puts(ERRO_O_UTILIZADOR_NAO_EXISTE);
        }
    } else {
        puts(ERRO_LISTA_ESTA_CHEIA);
    }
}

/**
 *   obter informacoes para procurar na struct
 * @param Utilizador para Buscar a struct Utilizador
 */

void procurarUtilizadores(Utilizadores utilizadores) {
    int numero;
    char codigo[MAX_ID_UTILIZADOR];

    puts(MSG_PARA_OBTER_ID_UTILIZADOR);
    scanf("%s", codigo);
    cleanInputBuffer();

    numero = procurarUtilizador(utilizadores, codigo);

    if (numero != -1) {
        imprimirUtilizador(utilizadores.utilizadores[numero]);
    } else {
        puts(ERRO_O_UTILIZADOR_NAO_EXISTE);
    }
}

/**
 *   obter numero do utilizador para verificar se existe na memoria e no ficheiro
 * @param Utilizador para Buscar a struct Utilizador
 */

void atualizarUtilizadores(Utilizadores *utilizadores, char *ficheiro) {
    int numero;
    char codigo[MAX_ID_UTILIZADOR];
    cleanInputBuffer();
    lerString(codigo, MAX_ID_UTILIZADOR, MSG_PARA_OBTER_ID_UTILIZADOR);

    numero = procurarUtilizador(*utilizadores, codigo);
    if (numero != -1) {
        atualizarUtilizador(&utilizadores->utilizadores[numero]);
        atualizarUtilizadorFX(utilizadores, numero, ficheiro);
        printf(MSG_UTILIZADOR_ATUALIZADO);
    } else {
        puts(ERRO_O_UTILIZADOR_NAO_EXISTE);
    }
}

/**
 *   obter numero do utilizador para verificar se existe na memoria e no ficheiro e remover se existir
 * @param Utilizador para Buscar a struct Utilizador
 * @param ficheiro receber o nome do ficheiro
 */

void removerUtilizadores(Utilizadores *utilizadores, char *ficheiro) {
    int i, numero;
    char codigo[MAX_ID_UTILIZADOR];
    cleanInputBuffer();
    lerString(codigo, MAX_ID_UTILIZADOR, MSG_PARA_OBTER_ID_UTILIZADOR);
    numero = procurarUtilizador(*utilizadores, codigo);

    if (numero != -1) {
        if (utilizadores->utilizadores[numero].utilizador == 1) {
            utilizadores->utilizadores[numero].tipo = Inativo;
            puts(ERRO_O_UTILIZADOR_NAO_EXISTE);
        } else {
            for (i = numero; i < utilizadores->contador - 1; i++) {
                utilizadores->utilizadores[i] = utilizadores->utilizadores[i + 1];
            }

            utilizadores->contador--;
            puts(MSG_UTILIZADOR_REMOVIDO);
            apagarDadosUtilizador(&utilizadores->utilizadores[numero]);
            removerUtilizadorFX(*utilizadores, ficheiro);
        }
    } else {
        puts(ERRO_O_UTILIZADOR_NAO_EXISTE);
    }
}

/**
 *   verificar se ha utilizadores na memoria e imprimir todos
 * @param Utilizador para Buscar a struct Utilizador
 */

void listarUtilizadores(Utilizadores utilizadores) {
    int i;
    if (utilizadores.contador > 0) {
        for (i = 0; i < utilizadores.contador; i++) {
            imprimirUtilizador(utilizadores.utilizadores[i]);
        }
    } else {
        puts(ERRO_LISTA_ESTA_VAZIA);
    }
}