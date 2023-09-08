#include <stdlib.h>
#include <stdio.h>
#include "icone.h"
#define MEM_MAXX 10          // Posi��es iniciais.

typedef struct _lista
{

    Icone *icone;
    int status;

} Lista;

Lista * lista;

int espacoDmemoria=MEM_MAXX;   // Espa�o inicial de mem�ria.
int tam,valor;				   // tam = usado em algumas fun��es que precis�o do tamanho do icone.
int operacao;				   // Escolher a fun��o desejada.
int indice;					   // Armazena o icone desejado.

int menu();
int criarNaLista();			   // Cria um icone e armazena a localiza��o da estrutura Lista.
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
        // Percorre a Lista em busca de uma posi��o vazia, indicada
        // pela variavel status == 0.
        for (int i = 0; i < espacoDmemoria; ++i)
        {
            if ((lista + i)->status == 0)
            {
                // icone_cria devolve um ponteiro que � armazenado em lista[i].icon.
                lista[i].icone = icone_cria(tam);

                (lista + i)->status = 1;

                return i;
            }
        }

        // Se o ciclo n�o fornecer nenhuma posi��o vaga
        // � alocado a quantidade indicada por MEM_MAXX.

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

    // CriarNaLista retorna a posi��o onde o �cone foi criado.
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

                // Valores diferentes de 1 e 0 s�o entendidos como 1
                // para facilitar a inser��o.
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



void imprimir_icones()        // Mostrar �cones criados.
{

    // Somente chama a fun��o onde o
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

    // N�o deixa o usu�rio selecionar uma posi��o inv�lida.
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

            // Se a transposta do icone, no caso k i � diferente de i k
            // n�o � simetrico.

            if(icone_acessa(lista[valor].icone,i,k) != icone_acessa(lista[valor].icone,k,i))
            {
                printf("O icone %i nao � simetricos \n", valor);
                return;
            }

        }

    }

    // Se o ciclo n�o encontrar nenhuma posi��o diferente
    // confirma transposta.
    printf("O icone %i � simetricos \n", valor);

}


void reflexao_horizontal()   //  Criar a reflex�o horizontal de um dado �cone, tendo a op��o de armazen�-lo.
{


    printf("Qual icone deseja refletir na horizontal: ");
    scanf("%i", &valor);

    // Validar se o usu�rio selecionou um icone existente.
    if(lista[valor].status != 1)
    {
        system("cls");
        printf("Localizacao invalida!\n");
        return;
    }

    // Receber o tamanho do icone selecionado pelo usu�rio.
    tam = icone_tam(lista[valor].icone);

    // Cria um segundo icone de mesmo tamanho
    // para receber os valores da reflex�o.
    indice = criarNaLista(tam);


    for (int i = 0; i < tam; ++i)
    {

        // Um ciclo for duplo para ser possivel percorrer a mesma linha
        // s� que em sentidos diferentes, se ler o �ltimo valor
        // de uma matriz e grava o valor na primeira posi��o da outra.
        for (int k = 0, j = (tam-1); k < tam && j >= 0; ++k, --j)
        {

            icone_atribui(lista[indice].icone, i, j, icone_acessa(lista[valor].icone, i, k));

        }

    }

    // imprime o valor obtido.
    icone_imprime(lista[indice].icone);


    printf("Deseja armazenar? 1=sim :");
    scanf("%i", &valor);

    // O �cone � armazenado de antem�o, se o usu�rio n�o
    // quiser armazen� lo, ele � apagado e sua posi��o
    // liberada.

    if(valor != 1)
    {
        lista[indice].status = 0;
        icone_libera_memoria(lista[indice].icone);

    }

}



void reflexao_vertical()          //  Criar a reflex�o vertical de um dado �cone, tendo a op��o de armazen�-lo.
{


    printf("Qual icone deseja refletir na vertical: ");
    scanf("%i", &valor);

    // Validar se o usu�rio selecionou um icone existente.
    if(lista[valor].status != 1)
    {
        system("cls");
        printf("Localizacao invalida!\n");
        return;
    }

    tam = icone_tam(lista[valor].icone);

    indice = criarNaLista(tam);


    // A l�gica e a mesma da reflax�o horizontal, com a diferen�a que
    // na reflexao horizontal o segundo ciclo for � duplo, e aqui �
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

    // O �cone � armazenado de antem�o, se o usu�rio n�o
    // quiser armazen� lo, ele � apagado e sua posi��o
    // liberada.

    if(valor != 1)
    {
        lista[indice].status = 0;
        icone_libera_memoria(lista[indice].icone);
    }

}





void ampliar_icone()
{

    int ampliacao;      // Amplia��o desejada
    int Ma=0,Na=0;      // Controles do ciclo for

    printf("Qual icone deseja aumenta: ");
    scanf("%i", &valor);

    // Validar se o usu�rio selecionou um icone existente.
    if(lista[valor].status != 1)
    {
        system("cls");
        printf("Localizacao invalida!\n");
        return;
    }


    // Enquanto o usu�rio n�o selecionar um amplia��o v�lida
    // continua no ciclo.
    do
    {
        printf("\nIcone selecionado: %i\n", indice);
        printf("Deseja ampliar 2 ou 4 vezes: ");
        scanf("%i", &ampliacao);

    }
    while(ampliacao != 2 && ampliacao != 4);

    // Recebe o tamanho do �cone selecionado.
    tam = icone_tam(lista[valor].icone);

    // Armazena na mem�ria um espa�o suficiente para
    // o novo �cone.
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
                    // se repetem de acordo com a amplia��o isso �, o valor que foi lido em i=0 e j=0
                    // vai ser gravado no segundo icone com n�mero de casas igual a amplia��o.
                    icone_atribui(lista[indice].icone, Ma, Na, icone_acessa(lista[valor].icone, i, j));
                    Na++;

                }
            }

            Na=0;   // A vari�vel Na � posi��o da amplia��o

            Ma++;	// A vari�vel Ma serve para que as posi��es no sentido coluna( para baixo )
            // sejam tamb�m gravadas, identicas as primeiras.
        }
    }


    icone_imprime(lista[indice].icone);

    printf("Deseja armazenar? 1=sim :");
    scanf("%i", &valor);

    // O �cone � armazenado de antem�o, se o usu�rio n�o
    // quiser armazen� lo, ele � apagado e sua posi��o
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
