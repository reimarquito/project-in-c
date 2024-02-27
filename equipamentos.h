#ifndef EQUIPAMENTOS_H
#define EQUIPAMENTOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "input.h"

#define MAX_TAMANHO_DESIGNACAO 50
#define MAX_TAMANHO_DATA 15
#define MSG_PARA_OBTER_DESIGNACAO "Insira a designação do equipamento:"   
#define MSG_PARA_OBTER_DATA_CRIACAO "Insira a data de criacao do equipamento(dd/mm/aaaa):"  
#define MSG_PARA_OBTER_ESTADO_EQUIPAMENTO "Insira o estado do equipamento (0 a 3):"
#define MSG_PARA_OBTER_NUMERO_EQUIPAMENTO "Insira o numero do equipamento:"
#define MUDAR_ESTADO_EQUIPAMENTO "Mudou o estado com sucesso :)"
#define ERRO_O_EQUIPAMENTO_NAO_EXISTE "Erro o equipamento nao existe :("
#define MSG_PARA_OBTER_NOVO_ESTADO "Escolha o novo estado (0 - Operacional, 1 - Em Manutenção, 2 - Não Operacional, 3 - Para Reciclagem):"
#define ERRO_LISTA_ESTA_CHEIA "Erro a lista esta cheia"
#define ERRO_LISTA_ESTA_VAZIA "Erro a lista esta vazia"    
#define MSG_EQUIPAMENTO_ENCONTRADO "Equipamento encontrado"
#define MSG_EQUIPAMENTO_NAO_ENCONTRADO "Equipamento nao encontrado"
#define MSG_EQUIPAMENTO_ATUALIZADO "Equipamento atualizado com sucesso :)"   
#define MIN_ESTADO 0
#define MAX_ESTADO 3    
#define MAX_DOC_EQUIPAMENTOS 5

    typedef enum {
        Impressora, Computador, Portátil, Monitor, Router, Switch, TV, Projetor, Controlador_de_acessos, Rato, Acessório, Outro
    } Categoria;

    typedef enum {
        Operacional, Em_Manutenção, Não_Operacional, Para_Reciclagem
    } Tipo;

    typedef struct {
        int id_equipamento;
        char designacao[MAX_TAMANHO_DESIGNACAO];
        Categoria categoria;
        char dataCriacao[MAX_TAMANHO_DATA];
        Tipo estado;
        int codigo_utilizador;
        int num_manutencoes;
    } Equipamento;

    /**
     * guarda o numero de equipamentos
     * @param contador de equipamentos
     */

    typedef struct {
        int contador, tamanho;
        Equipamento *equipamentos;
    } Equipamentos;

    int procurarEquipamento(Equipamentos equipamentos, int id_equipamento);
    int carregarEquipamentos(Equipamentos *equipamentos, char *ficheiro);
    void libertarEquipamentos(Equipamentos *equipamentos);
    int inserirEquipamento(Equipamentos *equipamentos);
    void atualizarEstadoequipamento(Equipamentos *equipamentos, char *ficheiro);
    void inserirEquipamentos(Equipamentos *equipamentos, char *ficheiro);
    void procurarEquipamentos(Equipamentos equipamentos);
    void atualizarEquipamentos(Equipamentos *equipamentos, char *ficheiro);
    void listarEquipamentos(Equipamentos equipamentos);
    const char* categoriaToString1(Categoria categoria);
    const char* categoriaToString2(Tipo estado);
    void listar_livre_categoria(Equipamentos equipamento);
    void listar_reciclagem_categoria(Equipamentos equipamento);
    void imprimirEquipamentoLivre(Equipamentos equipamentos, int categoria);
    void imprimirEquipamentoReciclagem(Equipamentos equipamentos , int categoria);
#ifdef __cplusplus
}
#endif

#endif 

