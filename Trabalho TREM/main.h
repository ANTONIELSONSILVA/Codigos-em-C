#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//* Header simples para definir as estruturas e prototipos das funcoes

//* Estrutura do Vagão
typedef struct vagao{
    int destino; //número da hierarquia de destino
    struct vagao *proximo; //Ponteiro para o próximo vagão
    struct vagao *anterior; //ponteiro para o vagão anterior
}vagao;

typedef struct{
    //Estrutura do trem
    vagao *header; //cabecalho contendo o endereco do primeiro e ultimo vagao
    int tamanho; //tamanho do trem
    int prox; //proximo para liberar o trem para saida do patio
}trem;

typedef struct trilho{
    //Estrutura do trilho
    int quantidade; //quantidade de vagões presentes
    struct trilho *prox; //ponteiro para o próximo trilho
    vagao *header; // cabeçalho para o 1° vagão
}trilho;

typedef struct{
    //Estrutura do patio
    trilho *trilhos; //ponteiro para os trilhos
    int tamanho; //Quantos trilhos o pátio possui
    int espacos; //Quantos vagões os trilhos comportam
}patio;

//Cria um novo vagao
vagao* newVagao(int valor);
//Cria um novo trem
trem* newTrem();
//Insere vagão no trem
void insereVagao(trem *tr, vagao *vg);
//Remove vagão do trem
vagao* removeVagao(trem *tr);
//Cria um novo trilho
trilho* newTrilho();
//Insere um trilho à um pátio
void inserirTrilho(patio *pt, trilho * tl);
//Insere vagão na pilha de trilhos
void inserirPilha(trilho *tl , vagao *va);
//Remove vagão da pilha de trilhos
vagao* removerPilha(trilho *tl);
//Cria um novo pátio
patio* newPatio(int tamanho, int espacos);
//Verifica se o próximo vagão ja pode ser inserido direto no trem de saída
int Passagem(int *obj, int *prox);
//Verifica a sequencia e determina a quantidade mínima de trilhos necessária para a reorganização
void Quantidade(trem *tr, int *tamanho, int *espacos);
//Entrada da sequencia dos vagões
void Entrada(trem *tr);
//Exibe os valores do trem na tela
void ExibeTrem(trem *tr);
//Exibe os valores da pilha na tela
void ExibeTrilho(trilho *rl);
//Realiza a reorganização dos vagões
trem* iniciarTroca(trem *tr, patio *pt);
//Memória Indisponível
void memoriaIndisponivel();

#endif // MAIN_H_INCLUDED
