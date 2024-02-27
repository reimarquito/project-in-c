#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "equipamentos.h"
#include "utilizadores.h"


#define TAM_INICIAR_EQUIPAMENTO 5

/**
 * Imprimir um certo equipamento
 * @param Equipamento  para Buscar a struct Equipamento
 */


void imprimirEquipamento(Equipamento equipamento) {
    printf("ID: %d\n", equipamento.id_equipamento);
    printf("Categoria: %s\n", categoriaToString1(equipamento.categoria));
    printf("Data de criacao: %s\n", equipamento.dataCriacao);
    printf("Designacao: %s\n", equipamento.designacao);
    printf("Estado: %s\n", categoriaToString2(equipamento.estado));
}


void imprimirEquipamentoLivre(Equipamentos equipamentos, int categoria) {
    for (int i = 0; i < equipamentos.contador; i++) {
        if (equipamentos.equipamentos[i].estado != Para_Reciclagem && equipamentos.equipamentos[i].estado == categoria ){
        imprimirEquipamento(equipamentos.equipamentos[i]);
        }
    }
   
}

void imprimirEquipamentoReciclagem(Equipamentos equipamentos , int categoria) {
    for (int i = 0; i < equipamentos.contador; i++){
        if ( equipamentos.equipamentos[i].estado == Para_Reciclagem && equipamentos.equipamentos[i].estado == categoria ){
        imprimirEquipamento(equipamentos.equipamentos[i]);
        }
    }
    
}

void listar_reciclagem_categoria(Equipamentos equipamentos){
    int i;
    
    for (i = 0; i < 11; i++){
        imprimirEquipamentoReciclagem(equipamentos, i);
    }
}

void listar_livre_categoria(Equipamentos equipamentos){
    int i;
    
    for (i = 0; i < 11; i++){
        imprimirEquipamentoLivre(equipamentos, i);
    }
}

/**
 * apagar dados da memoria dinamica
 * @param Equipamento para Buscar a struct Equipamento
 */
void apagarDadosEquipamento(Equipamento * equipamento) {
    equipamento->id_equipamento = NULL;
    strcpy(equipamento->designacao, "");
    equipamento->categoria = -1;
    equipamento->estado = -1;
    equipamento->num_manutencoes = NULL;
    equipamento->codigo_utilizador = NULL;
    strcpy(equipamento->dataCriacao, "");
}

/**
 *   procurar dados na memoria dinamica
 * @param Equipamento para Buscar a struct Equipamento
 * @param o contador vai receber o codigo do equipamento
 */

int procurarEquipamento(Equipamentos equipamentos, int id_equipamento) {
    int i;

    for (i = 0; i < equipamentos.contador; i++) {
        if (equipamentos.equipamentos[i].id_equipamento == id_equipamento) {
            return i; // Retorna o índice do equipamento encontrado
        }
    }

    return -1; // Retorna -1 se o equipamento não for encontrado
}

/**
 * obter o numero de equipamento no ficheiro binario
 * @param Ficheiro receber o nome do ficheiro
 */
int obterContadorFXEquipamento(char* ficheiro) {
    int contador = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    }

    return contador;
}

/**
 * carregar o equipamentos do ficheiro para a memoria 
 * @param Equipamento para Buscar a struct Equipamento
 * @param Ficheiro receber o nome do ficheiro 
 */

int carregarEquipamentos(Equipamentos *equipamentos, char *ficheiro) {
    int sucesso = 0;
    FILE *fp = fopen(ficheiro, "rb");

    if (fp != NULL) {
        fread(&(equipamentos->contador), sizeof (int), 1, fp);

        if (equipamentos->contador > 0) {
            equipamentos->equipamentos = (Equipamento *) malloc(equipamentos->contador * sizeof (Equipamento));
            fread(equipamentos->equipamentos, sizeof (Equipamento), equipamentos->contador, fp);
            equipamentos->tamanho = equipamentos->contador;
            sucesso = 1;
        }
        fclose(fp);
    }

    if (sucesso != 1) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            equipamentos->equipamentos = (Equipamento *) malloc(TAM_INICIAR_EQUIPAMENTO * sizeof (Equipamento));
            equipamentos->contador = 0;
            equipamentos->tamanho = TAM_INICIAR_EQUIPAMENTO;
            fclose(fp);
            sucesso = 1;
        }
    }
    return sucesso;
}

/**
 * libertar a memoria dimanica
 * @param Equipamento para Buscar a struct Equipamento
 */
void libertarEquipamentos(Equipamentos * equipamentos) {
    free(equipamentos->equipamentos);
}

/**
 * atualizar o contador no ficheiro binario
 * @param contador receber o numero do contador da memoria
 * @param ficheiro receber o nome do ficheiro
 */
void atualizarContadorFXEquipamento(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

/**
 *   inserir um novo documento ao ficheiro
 * @param Documento para Buscar a struct Documento
 * @param ficheiro receber o nome do ficheiro
 */

void inserirEquipamentoFX(Equipamentos equipamentos, char *ficheiro) {
    atualizarContadorFXEquipamento(equipamentos.contador, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&equipamentos.equipamentos[equipamentos.contador - 1], sizeof (Equipamento), 1, fp);
    fclose(fp);
}

/**
 *   atualizar o equipamento no ficheiro
 * @param Equipamento para Buscar a struct Equipamento
 * @param ficheiro receber o nome do ficheiro
 */

void atualizarEquipamentoFX(Equipamentos *equipamentos, int i, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(fp, sizeof (int), SEEK_SET);
    fseek(fp, sizeof (Equipamento) * i, SEEK_CUR);

    fwrite(&(equipamentos->equipamentos[i]), sizeof (Equipamento), 1, fp);
    fclose(fp);
}

/**
 *   obter informacoes do equipamento
 * @param Equipamento para Buscar a struct Equipamento
 */

int inserirEquipamento(Equipamentos * equipamentos) {
    lerString(equipamentos->equipamentos[equipamentos->contador].designacao, MAX_TAMANHO_DESIGNACAO, MSG_PARA_OBTER_DESIGNACAO);
    lerString(equipamentos->equipamentos[equipamentos->contador].dataCriacao, MAX_TAMANHO_DATA, MSG_PARA_OBTER_DATA_CRIACAO);
    equipamentos->equipamentos[equipamentos->contador].id_equipamento = equipamentos->contador + 1;
    equipamentos->equipamentos[equipamentos->contador].categoria = obterInt(0,10,"Escolha a categoria:"
            "0-Impressora, 1-Computador, 2-Portátil, 3-Monitor, 4-Router, 5-Switch, 6-TV, 7-Projetor, 8-Controlador_de_acessos, 9-Rato, 10-Acessório, 11-Outro");
    equipamentos->equipamentos[equipamentos->contador].estado = obterInt(MIN_ESTADO, MAX_ESTADO, MSG_PARA_OBTER_ESTADO_EQUIPAMENTO);
     equipamentos->equipamentos[equipamentos->contador].codigo_utilizador = -1;
    equipamentos->contador++;
}

/**
 *   remover equipamento no ficheiro
 * @param Equipamento para Buscar a struct Equipamento
 * @param ficheiro receber o nome do ficheiro
 */

void removerEquipamentoFX(Equipamentos *equipamentos, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&equipamentos->contador, sizeof (int), 1, fp);
    fwrite(equipamentos->equipamentos, sizeof (Equipamento), equipamentos->contador, fp);

    fclose(fp);
}

/**
 *   atualiza o estado do equipamento 
 * @param Equipamento para Buscar a struct Equipamento
 * @param ficheiro receber o nome do ficheiro
 */

void atualizarEstadoequipamento(Equipamentos *equipamentos, char *ficheiro) {
    int num;
    int codigo;
    obterInt(codigo, MAX_DOC_EQUIPAMENTOS, MSG_PARA_OBTER_NUMERO_EQUIPAMENTO);
    num = procurarEquipamento(*equipamentos, codigo);

    if (num != -1) {
        int novoEstado = obterInt(0, 3, MSG_PARA_OBTER_NOVO_ESTADO);
        equipamentos->equipamentos[codigo].estado = novoEstado;
        atualizarEquipamentoFX(equipamentos, codigo, ficheiro);
        puts(MUDAR_ESTADO_EQUIPAMENTO);
    } else {
        puts(ERRO_O_EQUIPAMENTO_NAO_EXISTE);
    }
}

/**
 *   obter informacoes do equipamento para atualizar a empresa
 * @param Equipamento para Buscar a struct Equipamento
 */


void atualizarEquipamento(Equipamento * equipamento) {
    cleanInputBuffer();
    lerString(equipamento->designacao, MAX_TAMANHO_DESIGNACAO, MSG_PARA_OBTER_DESIGNACAO);
    printf("Impressora, Computador, Portátil, Monitor, Router, Switch, TV, Projetor, Controlador_de_acessos, Rato, Acessório, Outro:");
    scanf("%d", &equipamento->categoria);
    cleanInputBuffer();
    lerString(equipamento->dataCriacao, MAX_TAMANHO_DATA, MSG_PARA_OBTER_DATA_CRIACAO);
    equipamento->estado = obterInt(MIN_ESTADO, MAX_ESTADO, MSG_PARA_OBTER_ESTADO_EQUIPAMENTO);

    printf("Equipamento atualizado com sucesso!\n");
}

/**
 *   expandir memoria dinamica dos equipamentos
 * @param Equipamento para Buscar a struct Equipamento
 */
void expandirEquipamentos(Equipamentos * equipamentos) {
    int novoTam = equipamentos->tamanho * 2;
    Equipamento *novoArray = realloc(equipamentos->equipamentos, novoTam * sizeof (Equipamento));

    if (novoArray != NULL) {
        equipamentos->equipamentos = novoArray;
        equipamentos->tamanho = novoTam;
    } else {
        printf("Erro ao expandir o array de equipamentos.\n");
    }
}

/**
 *   obter informacoes para procurar na struct
 * @param Equipamento para Buscar a struct Equipamento
 */

void inserirEquipamentos(Equipamentos *equipamentos, char *ficheiro) {
    if (equipamentos->contador == equipamentos->tamanho) {
        expandirEquipamentos(equipamentos);
    }

    if (equipamentos->contador < equipamentos->tamanho) {
        int indice = inserirEquipamento(equipamentos);
        if (indice != -1) {
            inserirEquipamentoFX(*equipamentos, ficheiro);
        } else {
            puts(ERRO_O_EQUIPAMENTO_NAO_EXISTE);
        }
    } else {
        puts(ERRO_LISTA_ESTA_CHEIA);
    }
}

/**
 *   obter informacoes para procurar na struct
 * @param Equipamento para Buscar a struct Equipamento
 */
void procurarEquipamentos(Equipamentos equipamentos) {
    int id_equipamento;
    if ( equipamentos.contador != 1){
        id_equipamento = obterInt(1,equipamentos.contador , "Qual equipamento quer procurar?:");

        int indice = procurarEquipamento(equipamentos, id_equipamento);

        if (indice != -1) {
            printf(MSG_EQUIPAMENTO_ENCONTRADO);
            imprimirEquipamento(equipamentos.equipamentos[indice]);
        } else {
            printf(MSG_EQUIPAMENTO_NAO_ENCONTRADO);
        }
    }else{
        printf("Nao existe equipamentos");
    }
}

/**
 *   obter numero do equipamento para verificar se existe na memoria e no ficheiro
 * @param Equipamento para Buscar a struct Equipamento
 */

void atualizarEquipamentos(Equipamentos *equipamentos, char *ficheiro) {
    int id_equipamento;
    int indice;
    
    id_equipamento = obterInt(1,equipamentos->contador , "Qual equipamento quer atualizar?:");

    indice = procurarEquipamento(*equipamentos, id_equipamento);

    if (indice != -1) {

        atualizarEquipamento(&equipamentos->equipamentos[indice]);
        atualizarEquipamentoFX(equipamentos, indice, ficheiro);

        printf(MSG_EQUIPAMENTO_ATUALIZADO);
    } else {
        printf(MSG_EQUIPAMENTO_NAO_ENCONTRADO);
    }
}

/**
 *   verificar se ha equipamentos na memoria e imprimir todos
 * @param Equipamento para Buscar a struct Equipamento
 */

void listarEquipamentos(Equipamentos equipamentos) {
    int i;
    if (equipamentos.contador > 0) {
        for (i = 0; i < equipamentos.contador; i++) {
            imprimirEquipamento(equipamentos.equipamentos[i]);
        }

    } else {
        puts(ERRO_LISTA_ESTA_VAZIA);
    }
}


