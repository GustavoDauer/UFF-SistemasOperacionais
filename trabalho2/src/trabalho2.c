/*
 ============================================================================
 Name        : trabalho2.c
 Author      : Gustavo Dauer
 Version     :
 Copyright   : Sistemas Operacionais - Ciência da Computação - UFF
 Description : Jantar dos filósofos em C utilizando a solução N-1 Tokens
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Necessário para a função usleep

#define NUM_FILOSOFOS 5 // Quantidade de filosofos
#define TEMPO 5000 // Tempo comendo
#define NUM_COMIDA 50 // Quantidade de espaguete (comida)

// Protótipos
void *filosofo(void *); // Função start_routine da thread
void pega_talher(int, int, char *);
void solta_talheres(int, int);
int comida_na_mesa();
void pega_token();
void retorna_token();

// Globais
pthread_mutex_t talheres[NUM_FILOSOFOS]; // Mutex
pthread_mutex_t comida_mutex; // Mutex
pthread_mutex_t podem_comer_mutex; // Mutex
pthread_t thread_filo[NUM_FILOSOFOS]; // Threads
int podem_comer = NUM_FILOSOFOS - 1;

int main(void)
{
	int i;
	pthread_mutex_init (&comida_mutex, NULL); // Inicialização dos mutex com valores padrão (NULL)
	pthread_mutex_init (&podem_comer_mutex, NULL);

	for (i = 0; i < NUM_FILOSOFOS; i++)
		pthread_mutex_init (&talheres[i], NULL);

	for (i = 0; i < NUM_FILOSOFOS; i++)
		pthread_create (&thread_filo[i], NULL, filosofo, (void *)i);

	for (i = 0; i < NUM_FILOSOFOS; i++)
		pthread_join (thread_filo[i], NULL);

	return EXIT_SUCCESS;
}

void *filosofo (void *num)
{
	int id;
	int talher_esquerdo, talher_direito, aux;
	id = (int)num;

	printf ("Filosofo %d esta pronto para comer\n", id);
	talher_direito = id;
	talher_esquerdo = id + 1;

	if (talher_esquerdo == NUM_FILOSOFOS) // Para garantir o número correto de talheres
		talher_esquerdo = 0;

	while (aux = comida_na_mesa()) { // Enquanto houver comida na mesa
		pega_token();
		pega_talher(id, talher_direito, "direito ");
		pega_talher(id, talher_esquerdo, "esquerdo ");

		printf("Filosofo %d: esta comendo\n", id);
		usleep(TEMPO * (NUM_COMIDA - aux));
		//usleep(TEMPO * (NUM_COMIDA - aux + 1));
		//printf("\n%d %d\n", TEMPO * (NUM_COMIDA - aux + 1), aux );

		solta_talheres(talher_esquerdo, talher_direito);
		retorna_token();
	}

	printf ("Filosofo %d acabou de comer\n", id);

	return NULL;
}

int comida_na_mesa ()
{
	static int comida = NUM_COMIDA; // Persistir o valor da comida
	int minha_comida;
	pthread_mutex_lock (&comida_mutex);

	if (comida > 0) {
		comida--;
	}

	minha_comida = comida;
	pthread_mutex_unlock (&comida_mutex);
	return minha_comida;
}

void pega_talher (int filo, int t, char *mao)
{
	pthread_mutex_lock (&talheres[t]);
	printf ("Filosofo %d: pegou o talher %s %d\n", filo, mao, t);
}

void solta_talheres (int t1, int t2)
{
	pthread_mutex_unlock (&talheres[t1]);
	pthread_mutex_unlock (&talheres[t2]);
}

void pega_token()
{
	int successful = 0;

	while (!successful) {
		pthread_mutex_lock (&podem_comer_mutex);

		if (podem_comer > 0) {
			podem_comer--;
			successful = 1;
		}
		else {
			successful = 0;
		}

		pthread_mutex_unlock (&podem_comer_mutex);
	}
}

void retorna_token()
{
	pthread_mutex_lock (&podem_comer_mutex);
	podem_comer++;
	pthread_mutex_unlock (&podem_comer_mutex);
}
