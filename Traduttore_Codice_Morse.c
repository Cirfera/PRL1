#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 200
//36 è la somma dell'alfabeto+numeri da 0 a 9
#define ROWS 36 
//10 è lo spazio minimo in cui posso memorizzare tutti i caratteri di ogni lettera del codice morse
#define COLS 10 
FILE *fPtr;





void traduci_Frase(char dizionario[ROWS][COLS], char buffer[])
{
    for (int i=0;i<strlen(buffer);i++)
    {
//se è una lettera minuscola
        if (islower(buffer[i])) 
            printf("%s",dizionario[buffer[i]-97]);
//se è uno spazio
        else if (isblank(buffer[i])) 
            printf("       ");
//se è una lettera maiuscola
        else if (isupper(buffer[i])) 
            printf("%s",dizionario[buffer[i]-65]);
//se è un numero
        else if (isdigit(buffer[i])) 
            printf("%s",dizionario[buffer[i]-22]);
//se la lettera corrente non è uno spazio, se non lo è nemmeno la prossima e se il file non è finito o non finirà nel prossimo carattere, allora metto i tre spazi per separare una lettera dall'altra
        if (!isblank(buffer[i]) && !isblank(buffer[i+1]) && buffer[i]!=0 && buffer[i+1]!=0) 
            printf("   ");
    }
    printf("\n");
}





void copia_File_in_Array(char dizionario[ROWS][COLS])
{
    for (int i=0;i<ROWS;i++)
        fscanf(fPtr," %*c:%[^\n]s",dizionario[i]);
//così legge anche gli asterischi
    fscanf(fPtr," %*[^\n]\n",NULL); 
}





void copia_Frase_in_Buffer(char buffer[])
{
//copio frase per frase, fino al newline, includendo quindi anche gli spazi
    fscanf(fPtr," %[^\n]s",buffer); 
}





_Bool frase_Valida(char buffer[])
{
    int i=0;
//fino a che la frase non è finita
    while (buffer[i]!='\0') 
    {
//minuscole
        if (islower(buffer[i])) 
            i++;
//maiuscole
        else if (isupper(buffer[i])) 
            i++;
//spazio
        else if (isblank(buffer[i])) 
            i++;
//numeri
        else if (isdigit(buffer[i])) 
            i++;
        else
            return 0;
    }
    return 1;
}





int main()
{
    char buffer[MAX_LENGTH];
//memorizzando i codici morse in una matrice, anche se in qualche lettera spreco qualche byte di memoria lasciandolo vuoto, posso trovare istantaneamente la posizione giusta del vettore lavorando con i codici ASCII dei caratteri da tradurre, risparmiando quindi molti cicli di calcolo rispetto a una lista
    char dizionario[ROWS][COLS]; 
//se non riesco ad aprire il file
    if ((fPtr=fopen("input.txt", "r"))==NULL) 
    {
        printf("Impossibile aprire file");
        return 0;
    }
//copio il file input.txt fino ai quattro asterischi in memoria, in modo da avere il dizionario pronto per la traduzione
    copia_File_in_Array(dizionario); 
    while (!feof(fPtr))
    {
        copia_Frase_in_Buffer(buffer);
//se la frase non è valida non comincio nemmeno a tradurre
        if (!frase_Valida(buffer)) 
        {

            printf("Errore nell'input\n");
            fscanf(fPtr,"[^\n]");
//se la frase non è valida allora svuoto il buffer, in modo da evitare eventuali errori o dati sbagliati nelle stringhe successive
            for (int i=0;i<strlen(buffer);i++) 
                buffer[i]=0;
        }
        else
            traduci_Frase(dizionario,buffer);
    }
//il file va chiuso prima di terminare il programma
    fclose(fPtr); 
    return 0;

}
