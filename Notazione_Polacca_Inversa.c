#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#define MAX_LENGTH 50
typedef struct Stack
{
	int dato;
	struct Stack* next;
} Stack;
 //visto che praticamente tutte le funzioni usano head, dichiaro head come variabile globale per rendere tutto il codice molto più leggibile
Stack* head=NULL;






//inserisco un elemento nello Stack
void push(int input) 
{
	Stack* elem_stack=malloc(sizeof(Stack));
	elem_stack->dato=input;
	elem_stack->next=head;
	head=elem_stack;
}





//tolgo l'ultimo elemento dallo Stack
int pop() 
{
	Stack* cima=head;
	int elemento=cima->dato;
	head=cima->next;
//libero la memoria allocata dinamicamente
	free(cima); 
	return elemento;
}





_Bool calcola(char input[])
{
//due variabili necessarie per trovare gli overflow e per invertire gli operandi durante la sottrazione
	int n,m; 
//divido l'input in parti, separate dallo spazio
	char* token=strtok(input," ");
//fino a che strtok non ritorna null, quindi fino a che l'input non è finito 
	while (token!=NULL) 
	{
//push nello stack solo se questo è un numero, e se non causa overflow/underflow
		if (isdigit(token[1]) || isdigit(token[0])) 
		{
			int operando=atoi(token);
//se il numero era originariamente positivo ed è diventato negativo con atoi, sicuramente c'è stato un overflow
			if (isdigit(token[0]) && (operando<0))
//overflow nei dati di input 
				return 1; 
			push(operando);
		}
		else
		{
			switch (*token)
			{
				case '+': 
					m=pop();
					n=pop();
					if ((m>0 && n>INT_MAX-m) || (m<0 && n<INT_MIN+m))
//c'è stato un overflow
						return 1; 
					push(m+n);
					break;
				case '-': 
					m = pop();
					n = pop();
					if ((m<0 && n<INT_MIN-m) || (m>0 && n<INT_MIN+m) || (n==0 && m+1==n-INT_MAX))
//c'è stato un overflow
						return 1; 
					push(n-m);
					break;
				case '*': 
					m=pop();
					n=pop();
					if ((m>1 && n>INT_MAX/m) || (m<-1 && n<=INT_MIN))
//c'è stato un overflow
						return 1; 
					push(m*n);
					break;
				default:
					break;
			}
		}
//aggiorno il token con il prossimo operando o operatore
		token=strtok(NULL," "); 
	}
	stampa_risultato(pop());
	return 0;
}





void stampa_risultato(int risultato)
{
	printf("%d in C2: ",risultato);
	const int bit = sizeof(unsigned int) * CHAR_BIT;
    	unsigned int j = 1;

    	for(int i = 0; i < bit; i++) 
	{ 
        	unsigned int maschera = 1 << (bit - 1 - i);
        	printf("%c", (risultato & maschera) ? '1' : '0');
        	if(j % 4 == 0) 
            	printf(" ");
        	j++;
    	}
    	printf("\n");
}





int main()
{
	char input[MAX_LENGTH];
	do
	{
		do
		{
//chiedo l'input fino a che non è sintatticamente corretto e non è vuoto
			scanf(" %[^\n]s",input); 
			if (!strcmp(input,"fine"))
				return 0;
		}
		while (input[0]=='\0');
//provo a calcolare il risultato
		if (calcola(input)) 
		{
			printf("Overflow!\n");
//c'è stato un overflow, dunque svuoto lo stack
			while (head!=NULL) 
				pop();
		}
	}
//controllo che il programma si chiuda se per qualche motivo sono arrivato qua dopo aver letto fine
	while (strcmp(input,"fine\n")); 
	return 0;
}
