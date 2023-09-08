#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
				     // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48
		int casas[49]={ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1};
		int movimento[2];
		int i,j,k,m,o,confirm;
		int ponteiro = 24,input,casazero,podemover,souapeca=0,resta=32;


    int movimentovalido(int peca){

        if(  (casas[peca+1]==1 && casas[peca+2]==0) || (casas[peca-1]==1 && casas[peca-2]==0 ) || (casas[peca+7]==1 && casas[peca+14]==0) || (casas[peca-7]==1 && casas[peca-14]==0)){ // condições para a peça poder se mover
             if((peca-1 != 20 && peca+1 != 21 && peca-1 != 27 && peca+1 != 28 ) || (casas[28]==1 && casas[21]==1 && casas[14]==0) || (casas[14]==1 && casas[21]==1 && casas[28]==0)){  // codições especiais para as peças dos cantos
                                            souapeca=1; 
             }
        }
        return (0);

    }


	int tabuleiro(){

				// TABULEIRO
					printf("      ");

				for(i=0;i<=13;i++){

						if(i>=2 && i<=4){

							if(casas[i]==1 && souapeca != 1){ // condições para procura uma peça válida, a casa conter 1 e uma peça não tenha sido achada antes.
                            movimentovalido(i);
							}

							if(ponteiro==i){
								printf("[%i]",casas[i]);	// condições para a impressão do ponteiro
							}else{
								printf(" %i ",casas[i]);
							}
						}
						if(i==6){
							printf("\n      ");
						}
						if(i>=9 && i<=11){

                            if(casas[i]==1 && souapeca != 1){
                            movimentovalido(i);
							}

							if(ponteiro==i){
								printf("[%i]",casas[i]);
							}else{
								printf(" %i ",casas[i]);
							}
						}
				}
				printf("\n");

				for(j=14;j<=34;j++){

                            if(casas[j]==1 && souapeca != 1){
                            movimentovalido(j);
							}

					if(j == 20 || j == 27 || j == 34 ){
							if(ponteiro==j){
								printf("[%i]",casas[j]);
							}else{
								printf(" %i ",casas[j]);
							}
							printf("\n");
					}else{
							if(ponteiro==j){
							printf("[%i]",casas[j]);
							}else{
								printf(" %i ",casas[j]);
							}
					}
				}
				printf("      ");

				for(k=35;k<=48;k++){



						if(k>=37 && k<=39){

                            if(casas[k]==1 && souapeca != 1){
                            movimentovalido(k);
							}

							if(ponteiro==k){
								printf("[%i]",casas[k]);
							}else{
								printf(" %i ",casas[k]);
							}
						}
						if(k==41){
							printf("\n      ");
						}
						if(k>=44 && k<=46){

                            if(casas[k]==1 && souapeca != 1){
                            movimentovalido(k);
							}

							if(ponteiro==k){
								printf("[%i]",casas[k]);
							}else{
								printf(" %i ",casas[k]);
							}
						}
				}
				printf("\n");
            if(resta==1){					// caso o contador chegue a 1 deve imprimir a mensagem de vitória
                printf("Parabéns !!!!/n");
                system("pause");
                exit(0);
            }

				if(souapeca==0){		// ao final do ciclo se nenhuma peça for encontrada, deve finalizar o programa e imprimir a mensagem.
                    printf("GAME OVER, VOÇÊ NÂO PODE FAZER MAIS MOVIMENTOS/n");
                    exit(0);
				}
                souapeca=0;

	return(0);
}



	int navegador(){

		 input = getch();
				if(input==72){         //72 -- cima
					ponteiro = ponteiro-7;
				}

				if(input==80){          //80 -- baixo
					ponteiro = ponteiro+7;
				}

				if(input==75){         //75 -- esquerda
					ponteiro = ponteiro-1;
				}

				if(input==77){         //77 -- direita
					ponteiro = ponteiro+1;
				}

				if( ponteiro!=1 &&  ponteiro!=7 && ponteiro!=8 && ponteiro!=5 && ponteiro!=12 && ponteiro!=13 && ponteiro!=35 && ponteiro!=36 && ponteiro!=43 && ponteiro!=40 && ponteiro!=41 && ponteiro!=47 && ponteiro!=6 && ponteiro!=42 && ponteiro>0 && ponteiro<48 ){ //A fronteira perdida
					confirm = ponteiro;  // caso o conteiro seje direcionado para casas fora do tabuleiro, ele recebe a valor da casa anterio
				}else{
					ponteiro = confirm;	
				}

	return(0);
}


    int main(void){
        setlocale(LC_ALL, "Portuguese");

		while(resta!=0){

			for(m=1;m<=2;m++){
				 input=0;
				while(input != 13){
					system("cls");
					printf("use as setas para se movimenta e enter para selecionar\n");
					printf("primeiro seleção é a casa a ser movida, segunda seleção é a casa de destino\n");
                    printf("numero de peças restantes %i\n", resta);
					printf("ESC para sair\n");
					printf("\n");
                    tabuleiro();
					navegador();
					movimento[m] = ponteiro;

					if(input==27){	// comando para o esc
						printf("OBRIGADO POR JOGAR !!!");
					return 0;

					}
				}
			}


				if( (movimento[2]+14) == movimento[1] || (movimento[2]-14) == movimento[1] || (movimento[2]+2) == movimento[1] || (movimento[2]-2) == movimento[1] ){ // condições para a validação do movimento.
						if(casas[movimento[2]]==0 && casas[movimento[1]]==1 && casas[(movimento[2] + movimento[1])/2] ==1 ){
								casas[movimento[2]] = casas[movimento[1]];
								casazero=(movimento[2] + movimento[1])/2;    // essa parte faz a peça que foi pulada zerar(casazero armazena a localização da casa que deve ser zerada)
								casas[casazero]=0;						// operação de zerar
								casas[movimento[1]]=0;				//casa com o (1) movido zera

						}
				}
						//contador de peças
                        resta=0;
						for(o=0;o<=48;o++){
                            if(casas[o]==1){
                            resta = resta+1;
                            }
						}
						resta=resta-16; 


		}

	return 0;
}
