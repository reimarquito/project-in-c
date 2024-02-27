#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "equipamentos.h"
#include "utilizadores.h"
#include "manutencao.h"

#define TAM_INI_MANUTENCAO 5

/**
 * Imprimir uma certa manutençao
 * @param Manutencao para Buscar a struct Manutencao
 */
void imprimirManutencao(Manutencao manutencao) {
    printf("ID: %d\n", manutencao.idmanutencao);
    printf("Data Da Manutencao: %s\n", manutencao.dataCriacao);
    printf("ID Do Utilizador: %s\n", manutencao.idUtilizador);
    printf("Informaçao: %s\n", manutencao.informacao);
    printf("ID do Equipamento: %d\n", manutencao.idequipamento);
}

/**
 * apagar dados da memoria dinamica
 * @param manutençao para Buscar a struct manutençao
 */
void apagarDadosManutencao(Manutencao *manutencao) {
    manutencao->idmanutencao = 0;
    strcpy(manutencao->dataCriacao, "");
    strcpy(manutencao->idUtilizador, "");
    strcpy(manutencao->informacao, "");
    manutencao->idequipamento = 0;
}

/**
 *   procurar dados na memoria dinamica
 * @param manutençao para Buscar a struct manutençao
 * @param o contador vai receber o codigo do manutençao
 */

int procurarManutencao(Manutencoes manutencoes, int numero) {
    int i;
    for (i = 0; i < manutencoes.contador; i++) {
        if (manutencoes.manutencoes[i].idmanutencao == numero) {
            return i; // Retorna o índice do movimento encontrado
        }
    }

    return -1; // Retorna -1 se o movimento não for encontrado
}

/**
 * obter o numero da manutencao no ficheiro binario
 * @param Ficheiro receber o nome do ficheiro
 */

int obterContadorFXManutencao(char* ficheiro) {
    int contador;
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    }
    return contador;
}

/**
 * carregar a manutençao do ficheiro para a memoria 
 * @param Manutençao para Buscar a struct Manutençao
 * @param Ficheiro receber o nome do ficheiro 
 */

int carregarManutencoes(Manutencoes *manutencoes, char *ficheiro) {
    int sucesso;
    sucesso = 0;
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&manutencoes->contador, sizeof (int), 1, fp);
        if (manutencoes->contador > 0) {
            manutencoes->manutencoes = (Manutencao*) malloc(manutencoes->contador * sizeof (Manutencao));
            fread(manutencoes->manutencoes, sizeof (Manutencao), manutencoes->contador, fp);
            manutencoes->tamanho = manutencoes->contador;
            sucesso = 1;
        }
        fclose(fp);
    }

    if (sucesso != 1) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            manutencoes->manutencoes = (Manutencao*) malloc(TAM_INI_MANUTENCAO * sizeof (Manutencao));
            manutencoes->contador = 0;
            manutencoes->tamanho = TAM_INI_MANUTENCAO;
            fclose(fp);
            sucesso = 1;
        }
    }
    return sucesso;
}

/**
 * libertar a memoria dimanica
 * @param Manutençao para Buscar a struct Manutençao
 */
void libertarManutencoes(Manutencoes *manutencoes) {
    free(manutencoes->manutencoes);
}

/**
 * atualizar o contador no ficheiro binario
 * @param contador receber o numero do contador da memoria
 * @param ficheiro receber o nome do ficheiro
 */

void atualizarContadorFXManutencao(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

/**
 *   inserir uma nova manutençao ao ficheiro
 * @param Manutençao para Buscar a struct Manutençao
 * @param ficheiro receber o nome do ficheiro
 */

void inserirManutencaoFX(Manutencoes manutencoes, char *ficheiro) {
    atualizarContadorFXManutencao(manutencoes.contador, ficheiro);
    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&manutencoes.manutencoes[manutencoes.contador - 1], sizeof (Manutencao), 1, fp);
    fclose(fp);
}

/**
 *   atualizar a manutençao no ficheiro
 * @param Manutençao para Buscar a struct Manutençao
 * @param ficheiro receber o nome do ficheiro
 */

void atualizarManutencaoFX(Manutencoes *manutencoes, int indice, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fseek(fp, sizeof (int), SEEK_SET);
    fseek(fp, sizeof (Manutencao) * indice, SEEK_CUR);
    fwrite(&(manutencoes->manutencoes[indice]), sizeof (Manutencao), 1, fp);
    fclose(fp);
}

/**
 *   obter informacoes das manutencoes
 * @param Manutençao para Buscar a struct Manutençao
 */

int inserirManutencao(Manutencoes *manutencoes, Utilizadores *utilizadores, Equipamentos *equipamentos) {
    int i, j;
    char idutilizador[MAX_ID_UTILIZADOR];
    int idequipamento;
    cleanInputBuffer();
    
    lerString(idutilizador, MAX_ID_UTILIZADOR, MSG_PARA_OBTER_ID_UTILIZADOR);
    i = procurarUtilizador(*utilizadores, idutilizador);

    printf("Insira o equipamento: ");
    scanf("%d", &idequipamento);

    j = procurarEquipamento(*equipamentos, idequipamento);

    if (i == -1 || utilizadores->utilizadores[i].tipo != Ativo) {
        return -1;
    }

    if (j == -1 || equipamentos->equipamentos[j].estado != Operacional) {
        return -1;
    }
    cleanInputBuffer();
    lerString(manutencoes->manutencoes[manutencoes->contador].informacao, MAX_TAMANHO_INFORMACAO, MSG_PARA_OBTER_INFORMACAO_MANUTENCAO);
    strcpy(manutencoes->manutencoes[manutencoes->contador].idUtilizador, idutilizador);
    manutencoes->manutencoes[manutencoes->contador].idequipamento = idequipamento;
    lerString(manutencoes->manutencoes[manutencoes->contador].dataCriacao, MAX_TAMANHO_DATA, MSG_PARA_OBTER_DATA_CRIACAO);
    manutencoes->manutencoes[manutencoes->contador].idmanutencao = manutencoes->contador + 1;
    manutencoes->contador++;

    puts("foi bem inserido");
    return 0;
}

/**
 *   obter informacoes da manutencao para atualizar a empresa
 * @param Manutencao para Buscar a struct Manutencao
 */

void atualizarManutencao(Manutencao *manutencao) {
    lerString(manutencao->informacao, MAX_TAMANHO_INFORMACAO, MSG_PARA_OBTER_INFORMACAO_MANUTENCAO);
    lerString(manutencao->dataCriacao, MAX_TAMANHO_DATA, MSG_PARA_OBTER_DATA_CRIACAO);
    printf(MSG_MANUTENCAO_ATUALIZADA);
}

/**
 *   expandir memoria dinamica dos manutencoes
 * @param Manutencao para Buscar a struct Manutencao
 */

void expandirManutencoes(Manutencoes *manutencoes) {
    int novoTamanho = manutencoes->tamanho * 2;
    Manutencao *novoArray = realloc(manutencoes->manutencoes, novoTamanho * sizeof (Manutencao));

    if (novoArray != NULL) {
        manutencoes->manutencoes = novoArray;
        manutencoes->tamanho = novoTamanho;
    } else {
        printf("Erro ao expandir o array de movimentos.\n");
    }
}

/**
 *   funcao para verificar se ha tamanho na memoria e colocar no ficheiro
 * @param Manutencao para Buscar a struct Manutencao
 * @param ficheiro receber o nome do ficheiro
 */

void inserirManutencoes(Manutencoes *manutencoes, Utilizadores *utilizadores, Equipamentos *equipamentos, char *ficheiro) {
    if (manutencoes->contador == manutencoes->tamanho) {
        expandirManutencoes(manutencoes);
    }

    if (manutencoes->contador < manutencoes->tamanho) {
        if (inserirManutencao(manutencoes, utilizadores, equipamentos) == -1) {
            puts(ERRO_MANUTENCAO_A_NAO_EXISTE);
        } else {
            inserirManutencaoFX(*manutencoes, ficheiro);
        }
    } else {
        puts(ERRO_LISTA_ESTA_CHEIA);
    }
}

/**
 *   obter informacoes para procurar na struct
 * @param Manutencao para Buscar a struct Manutencao
 */

void procurarManutencoes(Manutencoes manutencoes) {
    int numero;
    int ID;

    puts(MSG_PARA_OBTER_NUMERO_MANUTENCAO);
    cleanInputBuffer();
    scanf("%d", &ID);

    numero = procurarManutencao(manutencoes, ID);

    if (numero != -1) {
        imprimirManutencao(manutencoes.manutencoes[numero]);
    } else {
        puts(ERRO_MANUTENCAO_A_NAO_EXISTE);
    }
}

/**
 *   obter numero da Manutencao para verificar se existe na memoria e no ficheiro
 * @param Manutencao para Buscar a struct Manutencao
 */

void atualizarManutencoes(Manutencoes *manutencoes, char *ficheiro) {
    int numero;
    int ID;
    cleanInputBuffer();
    ID = obterInt(1, MAX_ID_MANUTENCAO, MSG_PARA_OBTER_NUMERO_MANUTENCAO);

    numero = procurarManutencao(*manutencoes, ID);
    if (numero != -1) {
        atualizarManutencao(&manutencoes->manutencoes[numero]);
        atualizarManutencaoFX(manutencoes, numero, ficheiro);
        printf(MSG_MANUTENCAO_ATUALIZADO);
    } else {
        puts(ERRO_MANUTENCAO_A_NAO_EXISTE);
    }
}

/**
 *   Recebe as datas, comparando e verificando
 * @param Manutencao para Buscar a struct Manutencao
 */

int compararDatas(const char *data1, const char *data2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    // Extrai dia, mês e ano das strings de data
    scanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    scanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    // Compara ano, mês e dia
    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
}

/** 
@brief Ordena a lista de manutencoes por data.*
Esta função utiliza um algoritmo de ordenação para organizar as manutencoes
na lista de acordo com suas datas, em ordem crescente.
 *
@param Um ponteiro para a estrutura Manutencoes cuja lista de movimentos será ordenada.
 */

void ordenarManutencoesPorData(Manutencoes *manutencoes) {
    int i, j;
    for (i = 0; i < manutencoes->contador - 1; i++) {
        for (j = 0; j < manutencoes->contador - i - 1; j++) {
            if (compararDatas(manutencoes->manutencoes[j].dataCriacao, manutencoes->manutencoes[j + 1].dataCriacao) > 0) {
                Manutencao temp = manutencoes->manutencoes[j];
                manutencoes->manutencoes[j] = manutencoes->manutencoes[j + 1];
                manutencoes->manutencoes[j + 1] = temp;
            }
        }
    }
}

/**
 *   verificar se ha manutencoes na memoria e imprimir todos
 * @param Manutencao para Buscar a struct Manutencao
 */

void listarManutencoes(Manutencoes manutencoes) {
    int i;
    if (manutencoes.contador > 0) {
        for (i = 0; i < manutencoes.contador; i++) {
            imprimirManutencao(manutencoes.manutencoes[i]);
        }
    } else {
        puts(ERRO_LISTA_ESTA_VAZIA);
    }
}