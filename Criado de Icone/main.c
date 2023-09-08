#include <stdlib.h>
#include <stdio.h>
#include "icone.h"
#define MEM_MAXX 10          // Posições iniciais.

typedef struct _lista
{

    Icone *icone;
    int status;

} Lista;

Lista * lista;

int espacoDmemoria=MEM_MAXX;   // Espaço inicial de memória.
int tam,valor;				   // tam = usado em algumas funções que precisão do tamanho do icone.
int operacao;				   // Escolher a função desejada.
int indice;					   // Armazena o icone desejado.

int menu();
int criarNaLista();			   // Cria um icone e armazena a localização da estrutura Lista.
void criar_icone();
void imprimir_icones();
void deletar_icone();
void icones_simetricos( );
void reflexao_horizontal();
void reflexao_vertical();
void ampliar_icone();



int main()
{


    lista = (Lista*)malloc(espacoDmemoria * sizeof(Lista));
    for (int i = 0; i < espacoDmemoria; ++i)
    {
        (lista + i)->status = 0;
    }


    for(;;)
    {

        operacao = menu();

        switch(operacao)
        {
        case 1:

            criar_icone();
            break;

        case 2:

            system("cls");
            imprimir_icones();
            break;

        case 3:

            deletar_icone();
            break;

        case 4:

            icones_simetricos();
            break;


        case 5:

            reflexao_horizontal();
            break;

        case 6:

            reflexao_vertical();
            break;


        case 7:

            ampliar_icone();
            break;

        }
    }

    return (0);
}






int criarNaLista(int tam)
{

    while(1)
    {
        // Percorre a Lista em busca de uma posição vazia, indicada
        // pela variavel status == 0.
        for (int i = 0; i < espacoDmemoria; ++i)
        {
            if ((lista + i)->status == 0)
            {
                // icone_cria devolve um ponteiro que é armazenado em lista[i].icon.
                lista[i].icone = icone_cria(tam);

                (lista + i)->status = 1;

                return i;
            }
        }

        // Se o ciclo não fornecer nenhuma posição vaga
        // é alocado a quantidade indicada por MEM_MAXX.

        espacoDmemoria += MEM_MAXX;
        lista = (Lista*) realloc(lista, espacoDmemoria * sizeof(Lista));

        for (int i = espacoDmemoria-MEM_MAXX; i < espacoDmemoria + 10; ++i)
        {
            (lista + i)->status = 0;
        }

    }

}



void criar_icone()
{

    printf("Escolha um tamanho: ");
    scanf("%i", &tam);

    // CriarNaLista retorna a posição onde o ícone foi criado.
    indice = criarNaLista(tam);

    printf("Deseja digitar linha por linha ou atribui aleatoriamente?\n");
    printf("1 = Linha a Linha, 2 = aleatoriamente: ");
    scanf("%i", &valor);


    if(valor == 1)
    {

        for (int i = 0; i < tam; ++i)
        {
            for (int j = 0; j < tam; ++j)
            {
                printf("Valor do linha %i coluna %i ", i, j);
                scanf("%i", &valor);

                // Valores diferentes de 1 e 0 são entendidos como 1
                // para facilitar a inserção.
                if(valor != 1 || valor != 0)
                {
                    valor = 1;
                }

                icone_atribui(lista[indice].icone, i, j, valor);

            }
        }
    }
    else if(valor == 2)
    {

        icone_preenche_aleatorio(lista[indice].icone);
        system("cls");
        printf("Icone %i \n", indice);
        icone_imprime(lista[indice].icone);
    }
    else
    {
        system("cls");
        printf("OPCAO INVALIDA\n");
    }


}



void imprimir_icones()        // Mostrar ícones criados.
{

    // Somente chama a função onde o
    // status mostra == 1, ou seja possitivo.
    for (int i = 0; i < espacoDmemoria; ++i)
    {
        if ((lista + i)->status == 1)
        {
            printf("Icone: %i\n", i);
            icone_imprime(lista[i].icone);
        }
    }
    printf("\n");
}




void deletar_icone()
{

    printf("Qual icone contaria de deletar: ");
    scanf("%i", &valor);

    if(lista[valor].status == 1)
    {

        lista[valor].status = 0;
        icone_libera_memoria(lista[valor].icone);
        system("cls");

    }else{

        system("cls");
        printf("Localizacao invalida!\n");

    }

}



void icones_simetricos()
{

    printf("Escolha o icone: ");
    scanf("%i", &valor);

    // Não deixa o usuário selecionar uma posição inválida.
    if(lista[valor].status != 1)
    {
        system("cls");
        printf("Localizacao invalida!\n");
        return;
    }

    for (int i = 0; i < tam; ++i)
    {
        for (int k = 0; k < tam; ++k)
        {

            // Se a transposta do icone, no caso k i é diferente de i k
            // não é simetrico.

            if(icone_acessa(lista[valor].icone,i,k) != icone_acessa(lista[valor].icone,k,i))
            {
                printf("O icone %i nao é simetricos \n", valor);
                return;
            }

        }

    }

    // Se o ciclo não encontrar nenhuma posição diferente
    // confirma transposta.
    printf("O icone %i é simetricos \n", valor);

}


void reflexao_horizontal()   //  Criar a reflexão horizontal de um dado ícone, tendo a opção de armazená-lo.
{


    printf("Qual icone deseja refletir na horizontal: ");
    scanf("%i", &valor);

    // Validar se o usuário selecionou um icone existente.
    if(lista[valor].status != 1)
    {
        system("cls");
        printf("Localizacao invalida!\n");
        return;
    }

    // Receber o tamanho do icone selecionado pelo usuário.
    tam = icone_tam(lista[valor].icone);

    // Cria um segundo icone de mesmo tamanho
    // para receber os valores da reflexão.
    indice = criarNaLista(tam);


    for (int i = 0; i < tam; ++i)
    {

        // Um ciclo for duplo para ser possivel percorrer a mesma linha
        // só que em sentidos diferentes, se ler o último valor
        // de uma matriz e grava o valor na primeira posição da outra.
        for (int k = 0, j = (tam-1); k < tam && j >= 0; ++k, --j)
        {

            icone_atribui(lista[indice].icone, i, j, icone_acessa(lista[valor].icone, i, k));

        }

    }

    // imprime o valor obtido.
    icone_imprime(lista[indice].icone);


    printf("Deseja armazenar? 1=sim :");
    scanf("%i", &valor);

    // O ícone é armazenado de antemão, se o usuário não
    // quiser armazená lo, ele é apagado e sua posição
    // liberada.

    if(valor != 1)
    {
        lista[indice].status = 0;
        icone_libera_memoria(lista[indice].icone);

    }

}



void reflexao_vertical()          //  Criar a reflexão vertical de um dado ícone, tendo a opção de armazená-lo.
{


    printf("Qual icone deseja refletir na vertical: ");
    scanf("%i", &valor);

    // Validar se o usuário selecionou um icone existente.
    if(lista[valor].status != 1)
    {
        system("cls");
        printf("Localizacao invalida!\n");
        return;
    }

    tam = icone_tam(lista[valor].icone);

    indice = criarNaLista(tam);


    // A lógica e a mesma da reflaxão horizontal, com a diferença que
    // na reflexao horizontal o segundo ciclo for é duplo, e aqui é
    // o primeiro.

    for (int i = 0, j = (tam-1) ; i < tam && j >=0 ; ++i, j--)
    {
        for (int k = 0; k < tam; ++k)
        {
            icone_atribui(lista[indice].icone, i, k, icone_acessa(lista[valor].icone, j, k));
        }
    }


    icone_imprime(lista[indice].icone);

    printf("Deseja armazenar? 1=sim :");
    scanf("%i", &valor);

    // O ícone é armazenado de antemão, se o usuário não
    // quiser armazená lo, ele é apagado e sua posição
    // liberada.

    if(valor != 1)
    {
        lista[indice].status = 0;
        icone_libera_memoria(lista[indice].icone);
    }

}





void ampliar_icone()
{

    int ampliacao;      // Ampliação desejada
    int Ma=0,Na=0;      // Controles do ciclo for

    printf("Qual icone deseja aumenta: ");
    scanf("%i", &valor);

    // Validar se o usuário selecionou um icone existente.
    if(lista[valor].status != 1)
    {
        system("cls");
        printf("Localizacao invalida!\n");
        return;
    }


    // Enquanto o usuário não selecionar um ampliação válida
    // continua no ciclo.
    do
    {
        printf("\nIcone selecionado: %i\n", indice);
        printf("Deseja ampliar 2 ou 4 vezes: ");
        scanf("%i", &ampliacao);

    }
    while(ampliacao != 2 && ampliacao != 4);

    // Recebe o tamanho do ícone selecionado.
    tam = icone_tam(lista[valor].icone);

    // Armazena na memória um espaço suficiente para
    // o novo ícone.
    indice = criarNaLista(tam*ampliacao);


    for (int i = 0; i < tam; ++i)
    {
        for (int m = 0; m < ampliacao; ++m)
        {
            for (int j = 0; j < tam; ++j)
            {
                for (int n = 0; n < ampliacao; ++n)
                {

                    // Os ciclo i e j percorrem normalmente o icone informado, os ciclos m e n
                    // se repetem de acordo com a ampliação isso é, o valor que foi lido em i=0 e j=0
                    // vai ser gravado no segundo icone com número de casas igual a ampliação.
                    icone_atribui(lista[indice].icone, Ma, Na, icone_acessa(lista[valor].icone, i, j));
                    Na++;

                }
            }

            Na=0;   // A variável Na é posição da ampliação

            Ma++;	// A variável Ma serve para que as posições no sentido coluna( para baixo )
            // sejam também gravadas, identicas as primeiras.
        }
    }


    icone_imprime(lista[indice].icone);

    printf("Deseja armazenar? 1=sim :");
    scanf("%i", &valor);

    // O ícone é armazenado de antemão, se o usuário não
    // quiser armazená lo, ele é apagado e sua posição
    // liberada.
    if(valor != 1)
    {
        lista[indice].status = 0;
        icone_libera_memoria(lista[indice].icone);
    }

}




int menu()
{

    int op;

    do
    {

        printf(" ___________________________________________________ \n");
        printf("| ================================================= |\n");
        printf("| #            =======> MENU <=======             # |\n");
        printf("| #                                               # |\n");
        printf("| # 1 - Criar icone                               # |\n");
        printf("| # 2 - Mostrar icones criados                    # |\n");
        printf("| # 3 - Apagar um icone                           # |\n");
        printf("| # 4 - Verificar simetria entre icones           # |\n");
        printf("| # 5 - Reflexao horizontal do icone              # |\n");
        printf("| # 6 - Reflexao vertical do icone                # |\n");
        printf("| # 7 - Criar copia ampliada                      # |\n");
        printf("| # 8 - Sair                                      # |\n");
        printf("| #                                               # |\n");
        printf("| ================================================= |\n");
        printf(" --------------------------------------------------- \n");

        printf("Escolha a opcao: ");
        scanf("%i", &op);

        if(op == 8)
        {
            exit(0);
        }
        else if(op < 1 || op > 8)
        {
            system("cls");
            printf("Escolha um opcao valida \n");
        }


    }
    while(op <1 || op > 8);


    return op;

}
