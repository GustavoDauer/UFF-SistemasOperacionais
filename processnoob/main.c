/******************************************************************************
* FILE: main.c
* Alunos: Gustavo Dauer
* 		  Pablo Moreira
*
* Resposta questão 2
* O objetivo do "process scheduling" é manter a CPU ocupada o tempo inteiro e
* entregar respostas para todos os programas. A forma como isso é implementado
* é através de filas, o que fica evidente na saída do programa abaixo onde, é
* respeitada a ordem de criação dos processos.
*
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

	int total = 0;
	pid_t child_pid;
	int child_status;
	int i;

	printf("Digite o número de processos: ");
	scanf("%d",&total);

	for (i = 1; i <= total; i++) {
		child_pid = fork();

		switch (child_pid) {
		case -1:
			perror("fork");
			exit(1);
		case 0:
			printf("Eu sou o %dº filho e meu PID é %ld\n", i,getpid());
			exit(0);

		default:

			wait(&child_status);
		}
	}
	printf("Eu sou o pai e meu PID é %ld \n",getpid());

}
