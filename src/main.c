/* 
Contador de palavras
 *
 * /* Data de submissao: 03/07
 * Nome: Lucas Leite Tavares  
 * RA: 156377
 * 
 */
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>

#define MAX_ENT 1000000 //numero máximo de entradas.
#define MAX_P 4 // nmero maximp de processos que nosso prog deve rodar paralelamente

unsigned long int VerificarPrimo(int Num);

unsigned long int main() {
	/* Leitura da entrada foi retirada de :
	https://stackoverflow.com/questions/4358728/end-of-file-eof-in-c
	e alterado para encaixar no atual programa*/
	int Num;
	unsigned long int Num_Entrada[MAX_ENT];
	int cont = 0;

		while(scanf("%d", &Num) != EOF){
			Num_Entrada[cont] = Num;
			//printf("%ls\n",Num_Entrada);
			cont++; //conta quantos numeros serao tratados 
   		}
	
	/*O typedef que tem os valores que seram verificados como primos ou nao*/	
	pid_t NumTratados[MAX_P];
		
	/*Poteção e Visibilidade, dados em aula*/
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON; 
	int *NumSalvos;

	NumSalvos = (int*)
	
	/* Mapeamamos os dados na memoria juntamente com os dados da entrada que ja selecionamos*/
		mmap(NULL,sizeof(int)*MAX_ENT,protection, visibility, 0, 0);

	
	/* Vamos adotar a tática, de verificar qual processo esta aberto e assim usa-lo.*/
	int *Process_Open;  
	Process_Open = (int*) mmap(NULL,sizeof(int)*MAX_P, protection, visibility, 0, 0);

	/*Parte mais importante, onde verifivamos o processo aberto, e abrimos um novo processo
	a partir das informações que ja temos de disponibilidade*/
	int Num_p = 0;
	int z = 0;

		while(z < cont){ 
			for(int i = 0;i < MAX_ENT; i++){
				if(Process_Open[i] == 0){ 
					NumTratados[i] = fork();
					Process_Open[i] = 1;
					// apos a verificação e abertura de um novo processo, salvamos esse numero primo;
						if(NumTratados[i] == 0){			
						NumSalvos[z] = VerificarPrimo(Num_Entrada[z]);
						Process_Open[i] = 0;
						exit(0);
					}
					z++;
					break;	// proximo valor a ser verificado;
				}
				
			}
		}		
	/* Verificamos se todos os valores foram tratados, terminamos o processos e printamos esse valores*/
	for (int i=0; i < MAX_P; i++) {
		 waitpid(NumTratados[i], NULL, 0);
  	}
	int Final_Process;
	Final_Process = 0;
	for(int i=0;i < cont;i++){
		Final_Process = Final_Process + NumSalvos[i];
	}
	printf("%d\n",Final_Process);
	return 0;
}

/* Para verificar se é primo ou nao baseamos em:
http://www.bosontreinamentos.com.br/programacao-em-linguagem-c/programa-para-determinar-se-um-numero-e-primo-em-c/
para criar a função de vrificação a abixo*/
unsigned long int VerificarPrimo(int Num){

	int n,a,b;
	int Primo = 1;
	
	n = Num;

		if(n <= 1){
		Primo = 0	;
		}
		else if (n == 2){
		Primo = 1;
		}
		else{
			for(a = 2; a <= n/2;a++){
				b = Num%a;
				if(b == 0){ 
				Primo = 0;
				break;
			}
		}
	}
	return Primo;

}


/*
  unsigned long int  x, y;

  scanf("%l %l\n", &x, &y);
  printf("%l\n", x + 200);
  return 0;
}
*/