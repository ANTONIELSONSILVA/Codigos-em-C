#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "main.h"


//* Memória Indisponível
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

//* Cria um novo vagão
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

//* Insere um trilho à um pátio
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

//* Cria um novo pátio
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

//* Verifica se o próximo vagão ja pode ser inserido direto no trem de saída
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

//* Verifica a sequencia e diz a quantidade mínima de trilhos necessária para a reorganização
void Quantidade(trem *tr, int *tamanho, int *espacos)
{
    vagao *pw = tr->header->proximo;
    int prox = tr->prox; //? Indicador de qual vagão pode ser inserido diretamente no trem de saída
    int cont = 1; //? Contador para verificar a quantidade de casos de empilhamento
    int a = *tamanho ; //? Trilhos
    int b = *espacos; //? Capacidade dos Trilhos
    while(pw != tr->header)
    {
        if( !Passagem( &pw->destino, &prox ))  //? Se o vagão não pode ir direto para o outro trem
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

//* Remove vagão da pilha de trilhos
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

//* Remove vagão do trem
vagao* removerVagao(trem *tr)
{
    if(tr != NULL && tr->tamanho > 0 )
    {
        vagao *mod = tr->header->proximo;
        tr->header->proximo = mod->proximo;
        mod->proximo = NULL;
        mod->anterior = NULL;
        tr->tamanho -= 1; //? Decrementa a quantidade de vagões no trem
        return mod;
    }
    else
    {
        return NULL;
    }
}

//* Insere vagão no trem
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
        tr->tamanho++; //? Incrementa a quantidade de vagões no trem
    }
}

//* Insere vagão no trilho
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
        tl->quantidade++; //? Incrementa a quantidade de vagões no trilho
    }
}

//* Entrada da sequencia dos vagões
void Entrada(trem *tr)
{
    int valor = 1; //? Irá conter os valores da hierarquia
    int cont = 0; //? Contador de Vagões
    printf("Digite a ordem dos vagões\n\nObs: Digite qualquer n° negativo para indicar o fim da sequência.\n\n");
    while(valor > 0)
    {
        printf("%i° Vagão: ", (cont+1) );
        scanf("%i",&valor);
        fflush(stdin);
        if(valor > 0)
        {
            insereVagao(tr, newVagao(valor)); //Insere vagão criado no trem
            if(tr->prox > valor || cont == 0)  //Verifica se o valor atual é menor do que os anteriores
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
    printf("Destino\tPosição\t\n");
    while(pw != tr->header)
    {
        cont++;
        printf("%i\t%i°\t\n", pw->destino,cont);
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

//* Realiza a reorganização dos vagões
trem* iniciarTroca(trem *tr, patio *pt)
{
    trem *trem_saida = newTrem(); //Trem de saída
    int max_vagao = tr->tamanho; //Quantidade total de vagões
    vagao *vg; //Vagão que será retirado do trem
    trilho *pr; //Ponteiro para percorrer os trilhos
    int procura; //Indicador se achou um espaço livre no trilho
    int num_trilho; //Identificador de posição do vagão no trilho
    int cont = 0; //Contador de etapas de troca
    system("cls");
    printf("Organizando vagões...\n");
    printf("\nEtapas\tVagão\tTrilho\tPosição\tEmissor\tDestino\n");

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
        pr = pt->trilhos->prox; //? Aponta o ponteiro para o 1° trilho
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
    printf("\nTrilhos Usados: %d\nQuantidade Máxima de Vagões/Trilho: %d\n\n",pt->tamanho,pt->espacos);
    return trem_saida;
}
int menu()
{
    trem *tr = NULL; //Trem que será reorganizado
    patio *pt = NULL; //Pátio de Troca de Vagões
    int tamanho; //Quantidade de Trilhos
    int espacos; //Quantidade de Vagões que cada trilho suporta
    int input=0; //Leitura das opções escolhidas pelo usuário

    while(input != 4)
    {
        system("cls");
        printf("Escolha uma das opções abaixo\n");
        printf("1 - Inserir a sequência do trem\n");
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
            Quantidade(tr, &tamanho, &espacos); //? Determina quantos trilhos serão utilizados
            break;
        case 2:
            if(pt != NULL)
            {
                printf("\nA reorganização já foi realizada. Por favor, insire uma nova sequência!\n\n");
                free(pt);
                system("pause");
                menu();
            }
            if(tr != NULL)
            {
                printf("Digite a quantidade inicial de trilhos de espera (Mínimo 3): \n\n");
                scanf("%d", &tamanho);
                fflush(stdin);
                if(tamanho < 3)
                {
                    printf("\nA quantidade mínima de trilhos precisa ser 3!Por favor, repita a operação\n");
                    system("pause");
                    break;
                }
                printf("Agora digite a quantidade máxima de vagoes permitidos em cada um desses trilhos inseridos\n\n");
                scanf("%d", &espacos);
                fflush(stdin);
                if(espacos < tamanho)
                {
                    printf("O valor inserido é inferior a quantidade mínima de trilhos. Portanto, a reorganização não acontecerá corretamente! Refaça a operação\n");
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
            pt = newPatio(tamanho, espacos); //Aloca um novo pátio
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
                printf("\nNão existe nenhum trem para ser mostrado por aqui. Insira uma nova sequência!\n\n");
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
