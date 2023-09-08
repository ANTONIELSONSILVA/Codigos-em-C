#include "stdlib.h"
#include "stdio.h"
#include "icone.h"
#include "time.h"


typedef struct _icone
{

	short int **pixels;     // matriz representando imagem do �cone
	int tamanho;            // n�mero de linhas e colunas da matriz da imagem

}Icone;

// Essa fun��o deve alocar um �cone (n�o se esque�a de alocar espa�o
// para os pixels e testar se ocorreu erro)
// e retornar um ponteiro para a estrutura alocada.

Icone * icone_cria(int tam)
{

    Icone * ic = (Icone*)malloc(sizeof(Icone));                        // verificar ponteiro NULL

	if (ic == NULL) {
	   printf ("Erro, falta de mem�ria\n");
	   exit (EXIT_FAILURE);
	}

	ic->tamanho = tam;

	ic->pixels = (short int **)malloc (tam * sizeof(short int*));

	if (ic->pixels == NULL) {
	   printf ("Erro, falta de mem�ria\n");
	   exit (EXIT_FAILURE);
	}

    for (int i=0; i < tam; i++)
    {
        ic->pixels[i] = (short int*)malloc(tam * sizeof(short int));
    }

    return(ic);


 }


//Essa fun��o deve liberar toda a mem�ria associada ao �cone.
void icone_libera_memoria(Icone *ic)
{


	free(ic);
    //falta mais

}


//Essa fun��o deve atribuir um valor �v� ao elemento na posi��o (i, j) do �cone
void icone_atribui(Icone *ic, int i, int j, int v)
{

    // verificar limites?
    ic->pixels[i][j] = v;

}



//Essa fun��o deve retornar o elemento na posi��o (i, j) do �cone
int icone_acessa(Icone *ic, int i, int j)
{

    int valor;

    valor = ic->pixels[i][j];

    return(valor);

}



//Essa fun��o deve retornar o n�mero de linhas e colunas do �cone
int icone_tam (Icone *ic)
{

    int tam;

    tam = ic->tamanho;

    return(tam);

}


//Essa fun��o deve atribuir valores �1� a pixels aleat�rios do �cone.
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



//Essa fun��o deve imprimir o �cone na tela de forma semelhante a um bitmap
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



//Essa fun��o deve alocar e retornar um �cone contendo uma c�pia
//do �cone recebido como par�metro.
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



//Essa fun��o deve criar um �cone (use icone_cria!) e colocar nesse
//�cone o resultado da rota��o de ic1
//de 90 graus no sentido hor�rio.
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
