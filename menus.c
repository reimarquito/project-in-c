#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "equipamentos.h"
#include "utilizadores.h"
#include "manutencao.h"
#include "menus.h"

#define EQUIPAMENTOS_FILE "equipamentos.bin"
#define UTILIZADORES_FILE "utitilizadores.bin"
#define MANUTENCAO_FILE "manutencao.bin"

Equipamentos equipamentos;
Utilizadores utilizadores;
Manutencoes manutencoes;

int principal() {

    if (!carregarUtilizadores(&utilizadores, UTILIZADORES_FILE)) {
        puts(ERRO_O_UTILIZADOR_NAO_EXISTE);
        return (EXIT_FAILURE);
    }

    if (!carregarEquipamentos(&equipamentos, EQUIPAMENTOS_FILE)) {
        puts(ERRO_O_EQUIPAMENTO_NAO_EXISTE);
        return (EXIT_FAILURE);
    }

    if (!carregarManutencoes(&manutencoes, MANUTENCAO_FILE)) {
        puts(ERRO_MANUTENCAO_A_NAO_EXISTE);
        return (EXIT_FAILURE);
    }


    int menu;
    do {
        menu = obterInt(0, 3, "1 - Gerir Equipamentos\n"
                "2 - Gerir Utilizadores\n"
                "3 - Gerir Manutencoes\n"
                "0 - sair\n");
        switch (menu) {
            case 1:
                GerirEquipamentos();
                break;

            case 2:
                GerirUtilizadores();
                break;

            case 3:
                GerirManutencoes();
                break;
        }
    } while (menu != 0);
}

void GerirEquipamentos() {
    int menu;
    int temp;
    do {
        menu = obterInt(0, 5, "1 - Inserir equipamentos\n"
                "2 - Procurar equipamentos\n"
                "3 - atualizar equipamento\n"
                "4 - Mudar estado equipamento\n"
                "5 - Listar equipamentos\n"
                "0 - voltar\n");

        switch (menu) {
            case 1:
                inserirEquipamentos(&equipamentos, EQUIPAMENTOS_FILE);
                break;
            case 2:
                procurarEquipamentos(equipamentos);
                break;
            case 3:
                atualizarEquipamentos(&equipamentos, EQUIPAMENTOS_FILE);
                break;
            case 4:
                atualizarEstadoequipamento(&equipamentos, EQUIPAMENTOS_FILE);
                break;
            case 5:
                temp = obterInt(0, 2, "1 - listar livres\n"
                        "2 - Listar reciclagem\n"
                        "0 - voltar\n");
                switch (temp) {
                    case 1:
                        listar_livre_categoria(equipamentos);
                        break;
                    case 2:
                        listar_reciclagem_categoria(equipamentos);
                }

        }
    } while (menu != 0);

}

void GerirUtilizadores() {
    int menu;
    do {
        menu = obterInt(0, 6, "1 - Inserir utilizadores\n"
                "2 - Procurar utilizadores\n"
                "3 - atualizar utilizador\n"
                "4 - Mudar estado utilizador\n"
                "5 - Listar utilizadores\n"
                "6 - Eliminar utilizadores\n"
                "0 - voltar\n-");

        switch (menu) {
            case 1:
                inserirUtilizadores(&utilizadores, UTILIZADORES_FILE);
                break;
            case 2:
                procurarUtilizadores(utilizadores);
                break;
            case 3:
                atualizarUtilizadores(&utilizadores, UTILIZADORES_FILE);
                break;
            case 4:
                atualizarEstadoUtilizador(&utilizadores, UTILIZADORES_FILE);
                break;
            case 5:
                listarUtilizadores(utilizadores);
                break;
            case 6:
                removerUtilizadores(&utilizadores, UTILIZADORES_FILE);
                break;
        }
    } while (menu != 0);
    libertarUtilizadores(&utilizadores);
}

void GerirManutencoes() {
    int menu;
    do {
        menu = obterInt(0, 4, "1 - Inserir manutencao\n"
                "2 - Procurar manutencoes\n"
                "3 - atualizar manutencoes\n"
                "4 - Listar manutencoes\n"
                "0 - voltar\n-");

        switch (menu) {
            case 1:
                inserirManutencoes(&manutencoes, &utilizadores, &equipamentos, MANUTENCAO_FILE);
                break;
            case 2:
                procurarManutencoes(manutencoes);
                break;
            case 3:
                atualizarManutencoes(&manutencoes, MANUTENCAO_FILE);
                break;
            case 4:
                listarManutencoes(manutencoes);
                break;
        }
    } while (menu != 0);
    libertarManutencoes(&manutencoes);
}