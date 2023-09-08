#include "stdlib.h"
#include "stdio.h"
#include "icone.h"
#include "time.h"


typedef struct _icone
{

	short int **pixels;     // matriz representando imagem do ícone
	int tamanho;            // número de linhas e colunas da matriz da imagem

}Icone;

// Essa função deve alocar um ícone (não se esqueça de alocar espaço
// para os pixels e testar se ocorreu erro)
// e retornar um ponteiro para a estrutura alocada.

Icone * icone_cria(int tam)
{

    Icone * ic = (Icone*)malloc(sizeof(Icone));                        // verificar ponteiro NULL

	if (ic == NULL) {
	   printf ("Erro, falta de memória\n");
	   exit (EXIT_FAILURE);
	}

	ic->tamanho = tam;

	ic->pixels = (short int **)malloc (tam * sizeof(short int*));

	if (ic->pixels == NULL) {
	   printf ("Erro, falta de memória\n");
	   exit (EXIT_FAILURE);
	}

    for (int i=0; i < tam; i++)
    {
        ic->pixels[i] = (short int*)malloc(tam * sizeof(short int));
    }

    return(ic);


 }


//Essa função deve liberar toda a memória associada ao ícone.
void icone_libera_memoria(Icone *ic)
{


	free(ic);
    //falta mais

}


//Essa função deve atribuir um valor ‘v” ao elemento na posição (i, j) do ícone
void icone_atribui(Icone *ic, int i, int j, int v)
{

    // verificar limites?
    ic->pixels[i][j] = v;

}



//Essa função deve retornar o elemento na posição (i, j) do ícone
int icone_acessa(Icone *ic, int i, int j)
{

    int valor;

    valor = ic->pixels[i][j];

    return(valor);

}



//Essa função deve retornar o número de linhas e colunas do ícone
int icone_tam (Icone *ic)
{

    int tam;

    tam = ic->tamanho;

    return(tam);

}


//Essa função deve atribuir valores “1” a pixels aleatórios do ícone.
void icone_preenche_aleatorio(Icone *ic)
{

    int m;

    int tam = icone_tam (ic);

    srand(time(NULL));

    for (int i = 0; i < tam; ++i)
    {
        for (int j = 0; j < tam; ++j)
        {
            m = rand() % 100;

            if(m % 2 == 0){
                icone_atribui(ic, i, j, 1);
            }else{
                icone_atribui(ic, i, j, 0);
            }

        }
    }



}



//Essa função deve imprimir o ícone na tela de forma semelhante a um bitmap
//(dica: utilizar o caractere
// ASCII 219).

void icone_imprime(Icone *ic)
{

    int tam = ic->tamanho;
    int ascii=219;


    for (int i = 0; i < tam; ++i)
    {
        printf("\n");
        for (int j = 0; j < tam; ++j)
        {
            if(ic->pixels[i][j] == 1)
            {
                printf("%c", ascii);
            }else
            {
                printf(" ");
            }

        }
    }

    printf("\n");

}



//Essa função deve alocar e retornar um ícone contendo uma cópia
//do ícone recebido como parâmetro.
Icone* icone_copia(Icone *ic)                                          //       perguntar pra Dilza se pode+
{

    int tam = ic->tamanho;

    Icone *ic2 = icone_cria(tam);

    for (int i = 0; i < tam; ++i)
    {
        for (int j = 0; j < tam; ++j)
        {
            icone_atribui(ic2, i, j, icone_acessa(ic, i, j));
        }
    }

    return(ic2);

}



//Essa função deve criar um ícone (use icone_cria!) e colocar nesse
//ícone o resultado da rotação de ic1
//de 90 graus no sentido horário.
Icone* icone_rotaciona(Icone *ic1)
{

     int tam = ic1->tamanho;

     Icone *ic2 = icone_cria(tam);


        for (int i = 0, k = (tam-1); i < tam && k >= 0; ++i , --k)
        {
            for (int j=0; j < tam; ++j)
            {
                 icone_atribui(ic2, j, i, icone_acessa(ic1, i, j) );
            }

        }




    return ic2;

}
