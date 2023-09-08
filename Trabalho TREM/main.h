#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//* Header simples para definir as estruturas e prototipos das funcoes

//* Estrutura do Vag�o
typedef struct vagao{
    int destino; //n�mero da hierarquia de destino
    struct vagao *proximo; //Ponteiro para o pr�ximo vag�o
    struct vagao *anterior; //ponteiro para o vag�o anterior
}vagao;

typedef struct{
    //Estrutura do trem
    vagao *header; //cabecalho contendo o endereco do primeiro e ultimo vagao
    int tamanho; //tamanho do trem
    int prox; //proximo para liberar o trem para saida do patio
}trem;

typedef struct trilho{
    //Estrutura do trilho
    int quantidade; //quantidade de vag�es presentes
    struct trilho *prox; //ponteiro para o pr�ximo trilho
    vagao *header; // cabe�alho para o 1� vag�o
}trilho;

typedef struct{
    //Estrutura do patio
    trilho *trilhos; //ponteiro para os trilhos
    int tamanho; //Quantos trilhos o p�tio possui
    int espacos; //Quantos vag�es os trilhos comportam
}patio;

//Cria um novo vagao
vagao* newVagao(int valor);
//Cria um novo trem
trem* newTrem();
//Insere vag�o no trem
void insereVagao(trem *tr, vagao *vg);
//Remove vag�o do trem
vagao* removeVagao(trem *tr);
//Cria um novo trilho
trilho* newTrilho();
//Insere um trilho � um p�tio
void inserirTrilho(patio *pt, trilho * tl);
//Insere vag�o na pilha de trilhos
void inserirPilha(trilho *tl , vagao *va);
//Remove vag�o da pilha de trilhos
vagao* removerPilha(trilho *tl);
//Cria um novo p�tio
patio* newPatio(int tamanho, int espacos);
//Verifica se o pr�ximo vag�o ja pode ser inserido direto no trem de sa�da
int Passagem(int *obj, int *prox);
//Verifica a sequencia e determina a quantidade m�nima de trilhos necess�ria para a reorganiza��o
void Quantidade(trem *tr, int *tamanho, int *espacos);
//Entrada da sequencia dos vag�es
void Entrada(trem *tr);
//Exibe os valores do trem na tela
void ExibeTrem(trem *tr);
//Exibe os valores da pilha na tela
void ExibeTrilho(trilho *rl);
//Realiza a reorganiza��o dos vag�es
trem* iniciarTroca(trem *tr, patio *pt);
//Mem�ria Indispon�vel
void memoriaIndisponivel();

#endif // MAIN_H_INCLUDED
