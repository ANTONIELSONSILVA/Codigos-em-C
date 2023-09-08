#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "main.h"


//* Mem�ria Indispon�vel
void memoriaIndisponivel()
{
    printf("Problema de alocacao ou erro de memoria!");
    exit(1);
}

//* Cria um novo trem
trem* newTrem()
{
    trem* tr = (trem*)malloc(sizeof(trem) );
    if(tr == NULL)
    {
        memoriaIndisponivel();
        free(tr);
        return NULL;
    }
    else
    {
        tr->tamanho = 0;
        tr->header = newVagao(0);
        return tr;
    }
}

//* Cria um novo vag�o
vagao* newVagao(int valor)
{
    vagao *vg = (vagao*)malloc(sizeof(vagao));
    if(vg == NULL)
    {
        memoriaIndisponivel();
        free(vg);
        return NULL;
    }
    else
    {
        vg->destino = valor;
        return vg;
    }
}

//* Cria um novo trilho
trilho* newTrilho()
{
    trilho *tl = (trilho*)malloc(sizeof(trilho));
    if(tl == NULL)
    {
        free(tl);
        memoriaIndisponivel();
        return NULL;
    }
    else
    {
        tl->quantidade = 0;
        tl->header = newVagao(0);
        return tl;
    }
}

//* Insere um trilho � um p�tio
void inserirTrilho(patio *pt, trilho * tl)
{
    if(pt != NULL && tl != NULL)
    {
        if(pt->tamanho == 0)
        {
            pt->trilhos->prox = tl;
            tl->prox = pt->trilhos;
        }
        else
        {
            tl->prox = pt->trilhos->prox;
            pt->trilhos->prox = tl;
        }
    }
}

//* Cria um novo p�tio
patio* newPatio(int tamanho, int espacos)
{
    patio* pt = (patio*) malloc(sizeof(patio));
    if(pt == NULL)
    {
        memoriaIndisponivel();
    }
    else
    {
        pt->tamanho = 0;
        pt->trilhos = newTrilho();
        while(pt->tamanho < tamanho)
        {
            inserirTrilho(pt, newTrilho());
            pt->tamanho++;
        }
        pt->tamanho = tamanho;
        pt->espacos = espacos;

    }
    return pt;
}

//* Verifica se o pr�ximo vag�o ja pode ser inserido direto no trem de sa�da
int Passagem(int *mod, int *prox)
{
    if(*mod == *prox)
    {
        *prox += 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

//* Verifica a sequencia e diz a quantidade m�nima de trilhos necess�ria para a reorganiza��o
void Quantidade(trem *tr, int *tamanho, int *espacos)
{
    vagao *pw = tr->header->proximo;
    int prox = tr->prox; //? Indicador de qual vag�o pode ser inserido diretamente no trem de sa�da
    int cont = 1; //? Contador para verificar a quantidade de casos de empilhamento
    int a = *tamanho ; //? Trilhos
    int b = *espacos; //? Capacidade dos Trilhos
    while(pw != tr->header)
    {
        if( !Passagem( &pw->destino, &prox ))  //? Se o vag�o n�o pode ir direto para o outro trem
        {
            if(pw->destino < pw->anterior->destino)  //? Se o grau de hierarquia do anterior for menor ao atual
            {
                cont++;
                if(cont > b)
                {
                    b = cont;
                }
                if(a == 0)
                {
                    a = 1;
                }
            }
            else
            {
                a += 1;
                cont = 1;
            }
        }
        pw = pw->proximo;
    }
}

//* Remove vag�o da pilha de trilhos
vagao* removerPilha(trilho *tl)
{
    if(tl != NULL && tl->quantidade > 0)
    {
        vagao *mod = tl->header->proximo;
        tl->header->proximo = mod->proximo;
        mod->anterior = NULL;
        mod->proximo = NULL;
        tl->quantidade--;
        return mod;
    }
    else
    {
        return NULL;
    }
}

//* Remove vag�o do trem
vagao* removerVagao(trem *tr)
{
    if(tr != NULL && tr->tamanho > 0 )
    {
        vagao *mod = tr->header->proximo;
        tr->header->proximo = mod->proximo;
        mod->proximo = NULL;
        mod->anterior = NULL;
        tr->tamanho -= 1; //? Decrementa a quantidade de vag�es no trem
        return mod;
    }
    else
    {
        return NULL;
    }
}

//* Insere vag�o no trem
void insereVagao(trem *tr, vagao *vg)
{
    if(tr != NULL && vg != NULL)
    {
        if(tr->tamanho == 0)
        {
            tr->header->proximo = vg;
            tr->header->anterior = vg;
            vg->anterior = tr->header;
            vg->proximo = tr->header;
        }
        else
        {
            vg->anterior = tr->header->anterior;
            vg->proximo = tr->header->anterior->proximo;
            tr->header->anterior->proximo = vg;
            tr->header->anterior = vg;
        }
        tr->tamanho++; //? Incrementa a quantidade de vag�es no trem
    }
}

//* Insere vag�o no trilho
void inserirPilha(trilho *tl, vagao *vg)
{
    if(tl != NULL && vg != NULL)
    {
        if(tl->quantidade == 0)
        {
            tl->header->proximo = vg;
            vg->proximo = NULL;
        }
        else
        {
            vg->proximo = tl->header->proximo;
            tl->header->proximo = vg;
        }
        tl->quantidade++; //? Incrementa a quantidade de vag�es no trilho
    }
}

//* Entrada da sequencia dos vag�es
void Entrada(trem *tr)
{
    int valor = 1; //? Ir� conter os valores da hierarquia
    int cont = 0; //? Contador de Vag�es
    printf("Digite a ordem dos vag�es\n\nObs: Digite qualquer n� negativo para indicar o fim da sequ�ncia.\n\n");
    while(valor > 0)
    {
        printf("%i� Vag�o: ", (cont+1) );
        scanf("%i",&valor);
        fflush(stdin);
        if(valor > 0)
        {
            insereVagao(tr, newVagao(valor)); //Insere vag�o criado no trem
            if(tr->prox > valor || cont == 0)  //Verifica se o valor atual � menor do que os anteriores
            {
                tr->prox = valor; //Recebe o menor valor da hierarquia indicando o que deve sair primeiro
            }
            cont++;
        }
        else
        {
            printf("\nFim da contagem!\n\n");
            cont++;
        }
    }

}

//* Exibe os valores do trem na tela
void ExibeTrem(trem *tr)
{
    vagao *pw = tr->header->proximo;
    int cont = 0;
    printf("Destino\tPosi��o\t\n");
    while(pw != tr->header)
    {
        cont++;
        printf("%i\t%i�\t\n", pw->destino,cont);
        pw = pw->proximo;
    }
}

//* Exibe os valores da pilha na tela
void ExibeTrilho(trilho *tl)
{
    trilho *pr = tl->prox;
    vagao *pw = pr->header->proximo;
    while(pr != tl)
    {
        while(pw != NULL)
        {
            printf("%i ",pw->destino);
            pw = pw->proximo;
        }
        pr = pr->prox;
        pw = pr->header->proximo;
        printf("\n");
    }
}

//* Realiza a reorganiza��o dos vag�es
trem* iniciarTroca(trem *tr, patio *pt)
{
    trem *trem_saida = newTrem(); //Trem de sa�da
    int max_vagao = tr->tamanho; //Quantidade total de vag�es
    vagao *vg; //Vag�o que ser� retirado do trem
    trilho *pr; //Ponteiro para percorrer os trilhos
    int procura; //Indicador se achou um espa�o livre no trilho
    int num_trilho; //Identificador de posi��o do vag�o no trilho
    int cont = 0; //Contador de etapas de troca
    system("cls");
    printf("Organizando vag�es...\n");
    printf("\nEtapas\tVag�o\tTrilho\tPosi��o\tEmissor\tDestino\n");

    while(tr->tamanho > 0)
    {
        pr = pt->trilhos->prox;
        num_trilho = 1;
        vg = removerVagao(tr);
        procura = 0;
        if(!(vg->destino == tr->prox))
        {
            while(pr != pt->trilhos && procura == 0)
            {
                if(pr->quantidade > 0)
                {
                    if(pr->header->proximo->destino > vg->destino && pr->quantidade < pt->espacos)
                    {
                        cont++;
                        inserirPilha(pr, vg);
                        procura = 1;
                        printf("%d\t%d\t%d\t%d\tTrem\tTrilho\t\n",cont,vg->destino, num_trilho, pr->quantidade);
                    }
                    else
                    {
                        pr = pr->prox;
                        num_trilho++;
                    }
                }
                else
                {
                    cont++;
                    inserirPilha(pr,vg);
                    procura = 1;
                    printf("%d\t%d\t%d\t%d\tTrem\tTrilho\t\n",cont,vg->destino, num_trilho, pr->quantidade);
                }
            }
        }
        else
        {
            if(Passagem(&vg->destino, &tr->prox))
            {
                insereVagao(trem_saida, vg);
            }
        }

    }
    while(trem_saida->tamanho < max_vagao)
    {
        pr = pt->trilhos->prox; //? Aponta o ponteiro para o 1� trilho
        num_trilho = 1;
        trem_saida->tamanho = max_vagao+1;
        while(pr != pt->trilhos)
        {
            if( pr->quantidade > 0 && Passagem( &pr->header->proximo->destino, &tr->prox))
            {
                cont++;
                vg = removerPilha(pr);
                insereVagao(trem_saida, vg);
                printf("%d\t%d\t%d\t%d\tTrilho\tTrem\t\n",cont,vg->destino, num_trilho, (pr->quantidade+1) );
            }
            else
            {
                pr = pr->prox;
                num_trilho++;
            }

        }
        if(trem_saida->tamanho == max_vagao+1)
            {
                memoriaIndisponivel();
            }
    }
    printf("\nTrilhos Usados: %d\nQuantidade M�xima de Vag�es/Trilho: %d\n\n",pt->tamanho,pt->espacos);
    return trem_saida;
}
int menu()
{
    trem *tr = NULL; //Trem que ser� reorganizado
    patio *pt = NULL; //P�tio de Troca de Vag�es
    int tamanho; //Quantidade de Trilhos
    int espacos; //Quantidade de Vag�es que cada trilho suporta
    int input=0; //Leitura das op��es escolhidas pelo usu�rio

    while(input != 4)
    {
        system("cls");
        printf("Escolha uma das op��es abaixo\n");
        printf("1 - Inserir a sequ�ncia do trem\n");
        printf("2 - Reordenar o trem\n");
        printf("3 - Exibir o trem\n");
        printf("4 - Sair do Programa\n");
        scanf("%d",&input);
        fflush(stdin);
        switch(input)
        {
        case 1:
            system("cls");

            if(tr != NULL)
            {
                free(tr); //? Libera caso queira entrar novamento com novos dados
            }
            tr = newTrem(); //? Aloca um novo trem
            Entrada(tr); //? Entrada de dados
            Quantidade(tr, &tamanho, &espacos); //? Determina quantos trilhos ser�o utilizados
            break;
        case 2:
            if(pt != NULL)
            {
                printf("\nA reorganiza��o j� foi realizada. Por favor, insire uma nova sequ�ncia!\n\n");
                free(pt);
                system("pause");
                menu();
            }
            if(tr != NULL)
            {
                printf("Digite a quantidade inicial de trilhos de espera (M�nimo 3): \n\n");
                scanf("%d", &tamanho);
                fflush(stdin);
                if(tamanho < 3)
                {
                    printf("\nA quantidade m�nima de trilhos precisa ser 3!Por favor, repita a opera��o\n");
                    system("pause");
                    break;
                }
                printf("Agora digite a quantidade m�xima de vagoes permitidos em cada um desses trilhos inseridos\n\n");
                scanf("%d", &espacos);
                fflush(stdin);
                if(espacos < tamanho)
                {
                    printf("O valor inserido � inferior a quantidade m�nima de trilhos. Portanto, a reorganiza��o n�o acontecer� corretamente! Refa�a a opera��o\n");
                    system("pause");
                    break;
                }
            }
            else
            {
                memoriaIndisponivel();
                free(pt->trilhos);
                free(pt);
            }
            pt = newPatio(tamanho, espacos); //Aloca um novo p�tio
            tr = iniciarTroca(tr, pt); //Inicia a troca

            system("pause");
            break;
        case 3:
            if(tr != NULL)
            {
                system("cls");
                ExibeTrem(tr); //Exibe a sequencia do trem na tela
                printf("\n");
            }
            else
            {
                printf("\nN�o existe nenhum trem para ser mostrado por aqui. Insira uma nova sequ�ncia!\n\n");
            }
            system("pause");
            break;

        default:
            break;
        }
    }
    return 0;
}
int main(void)
{
    setlocale(LC_ALL,"Portuguese");
    menu();
    return 0;
}
