#include <stdio.h>
#include <stdlib.h>

#include "equipamentos.h"
#include "manutencao.h"
#include "utilizadores.h"
#include "input.h"
#include "menus.h"

int main(int argc, char** argv) {
    Equipamentos equipamentos;
    Utilizadores utilizadores;
    Manutencoes manutencoes;
    
    principal();
    
    libertarEquipamentos(&equipamentos);
    return (EXIT_SUCCESS);
}

