#include <stdio.h>
#include <stdlib.h>


typedef struct _client
{
	int id;
	char mobile[64];
	char name[128];
	struct _client * next;
} client;


int read_client(FILE * fp, client * c)
{
	return fscanf(fp, "%s %d %[^\n]s", c->mobile, &c->id, c->name);
}

void print_client(client *c)
{
	printf("%s %s %d\n", c->name, c->mobile, c->id);
}

void insert(client ** head, client ** tail, client * aux)
{
	client * c = (client *) malloc(sizeof(client));

	if (c == NULL)
	{
		puts("ERROR: out of memory");
		exit(0);
	}

	*c = *aux; /*copy info from aux to c*/

	c->next = NULL;


	/* se a lista tiver vazia */
	if (*head == NULL)
	{
		*tail = c;
		*head = c;
	}
	else
	{
		/* se a lista nao tiver vazia */
		(*tail)->next = c;
		*tail = c;
	}
}

void list(client * head)
{
	client *aux;

	for(aux = head; aux != NULL; aux = aux -> next)
	{
		print_client(aux);
	}


}

int pop(client ** head, client ** tail)
{
	client *aux;
	/* se a lista tiver vazia */
	if (*head == NULL)
	{
		return 0;
	}
	/* se a lista nao tiver vazia */

	aux = *head;
	*head = (*head) -> next;

	/* se a lista ficou vazia temos que actualizar o tail */
	if (*head == NULL)
		*tail = NULL;


	free(aux);
	return 1;
}


int main(int argc, char * argv[])
{
	int i;
	FILE * fp;
	client aux;

	client *head, *tail;

	head = NULL;
	tail = NULL;

	printf("argc = %d\n", argc);

	puts("lista de parametros passados:");
	for (i = 0; i < argc; i++)
	{
		puts(argv[i]);
	}

	if (argc < 2)
	{
		puts("syntax error: specify file name");
		return 0;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		puts("Error: could not open file");
		return 0;
	}

	while(read_client(fp, &aux) != EOF)
	{
		insert(&head, &tail, &aux);
	}

	puts("do you want to print all elements of the list?");
	getchar();

	list(head);

	puts("do you want to remove all elements of the list?");
	getchar();

	while(pop(&head, &tail));

	puts("do you want to print all elements of the list?");
	getchar();
	list(head);

	fclose(fp);

	return 0;
}