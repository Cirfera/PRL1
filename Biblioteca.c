#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 70
typedef struct Libro{
    int isbn;
    char titolo[MAX_LENGTH];
    char autore[MAX_LENGTH];
    int copie_totali;
    int copie_prestate;
    struct Libro* next;
} Libro;





Libro* trova_ordine(Libro* temp, char autore_corrente[], char titolo_corrente[])
{
    while (temp->next!=NULL)
    {
//fino a che non trovo l'ordine giusto
        while  (strcmp(temp->next->autore,autore_corrente)<=0) 
        {
//in caso fossero più libri dello stesso autore
            if (strcmp(temp->next->autore,autore_corrente)==0) 
            {
//metto il libro seguendo l'ordine del titolo
                while (strcmp(temp->next->autore,autore_corrente)==0 && strcmp(temp->next->titolo,titolo_corrente)<0) 
                    temp=temp->next;
                return temp;
            }
            temp=temp->next;
//se la lista non ha elementi successivi allora lo metto in fondo, ed esco subito per evitare accessi invalidi
            if (temp->next==NULL) 
                return temp;
        }
        return temp;
    }
    return temp;
}





Libro* inserimento_ordinato(Libro* head, int isbn_corrente, char autore_corrente[], char titolo_corrente[])
{
//solo se la lista è vuota, o se devo inserire l'elemento in cima alla lista
    if (head==NULL || strcmp(head->autore,autore_corrente)>0) 
    {
        Libro* nuovo_nodo=(Libro*)malloc(sizeof(Libro));
        nuovo_nodo->isbn=isbn_corrente;
        strcpy(nuovo_nodo->titolo,titolo_corrente);
        strcpy(nuovo_nodo->autore,autore_corrente);
        nuovo_nodo->copie_totali=1;
        nuovo_nodo->copie_prestate=0;
        nuovo_nodo->next=head;
        return nuovo_nodo;
    }
    Libro* precedente=trova_ordine(head, autore_corrente, titolo_corrente);
//nodo nuovo
    Libro* nuovo_nodo=(Libro*)malloc(sizeof(Libro)); 
    nuovo_nodo->isbn=isbn_corrente;
    strcpy(nuovo_nodo->titolo,titolo_corrente);
    strcpy(nuovo_nodo->autore,autore_corrente);
    nuovo_nodo->copie_totali=1;
    nuovo_nodo->copie_prestate=0;
    nuovo_nodo->next=precedente->next;
    precedente->next=nuovo_nodo;
    return head;
}






void stampa_catalogo(Libro* temp)
{
//fino a che la lista non è finita
    while (temp!=NULL) 
    {
        printf("%d - %s - %s (%d/%d)\n",temp->isbn,temp->autore,temp->titolo,temp->copie_totali-temp->copie_prestate,temp->copie_totali);
        temp=temp->next;
    }
}





_Bool trova_duplicati(Libro* temp,int isbn_corrente)
{
//scorre tutta la lista fino a trovare un duplicato, sennò ritorna 0.
    while (temp!=NULL) 
    {
        if (temp->isbn==isbn_corrente)
        {
            temp->copie_totali++;
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}





Libro* copia_libri_in_lista(Libro* head)
{
    char autore_corrente[MAX_LENGTH], titolo_corrente[MAX_LENGTH];
    int isbn_corrente=1;
    do
    {
        scanf(" %d,%[^,],%[^\n]",&isbn_corrente,titolo_corrente,autore_corrente); 
        _Bool libro_duplicato=0;
        if (head!=NULL && isbn_corrente!=0)
            libro_duplicato = trova_duplicati(head, isbn_corrente);
//aggiungo un nuovo nodo solo se non c'è già un duplicato dello stesso libro
        if (!libro_duplicato && isbn_corrente!=0) 
        {
            head=inserimento_ordinato(head,isbn_corrente,autore_corrente,titolo_corrente);
//se la lista è ancora vuota dopo aver provato ad inserire un elemento, significa che non c'è più memoria
            if (head==NULL) 
                return head;
        }
    }
    while (isbn_corrente!=0);
    return head;

}





void ricerca_ricorsiva(Libro* temp,char autore_ricerca[],char titolo_ricerca[])
{
    if (strcmp(temp->autore, autore_ricerca)==0 && strcmp(temp->titolo, titolo_ricerca)==0)
    {
//questa variabile locale mi permette di evitare di calcolare le copie disponibili tre volte
        int copie_disponibili=temp->copie_totali-temp->copie_prestate; 
        if (copie_disponibili>0)
            printf("%d copie disponibili.\n",copie_disponibili);
        else
            printf("Non ci sono copie disponibili del libro richiesto.\n");
        return;
    }
    else if (temp->next!=NULL)
//fino a che non trovo il libro, o fino a che non finisce la lista
        ricerca_ricorsiva(temp->next, autore_ricerca, titolo_ricerca); 
    if (temp->next==NULL)
        printf("Libro non trovato.\n");
}





//ricerca del libro inserito, in maniera ricorsiva
void ricerca_libri(Libro* head) 
{
    char autore_ricerca[MAX_LENGTH],titolo_ricerca[MAX_LENGTH];
    printf("Inserire nome autore: ");
//chiedo i dati necessari per la ricerca prima di avviarla
    scanf(" %[^\n]",autore_ricerca); 
    printf("Inserire titolo: ");
    scanf(" %[^\n]",titolo_ricerca);
    ricerca_ricorsiva(head,autore_ricerca,titolo_ricerca);

}





void prestito(Libro* temp) {
    int isbn_corrente=0;
    printf("ISBN: ");
    scanf(" %d",&isbn_corrente);
//scorro tutta la lista
    while (temp!=NULL) 
    {
//se trovo che e' presente una copia del libro
        if (isbn_corrente==temp->isbn) 
        {
            if (temp->copie_totali-temp->copie_prestate>0)
            {
                temp->copie_prestate++;
                printf("Operazione completata.\n");
            }
            else
                printf("Non ci sono copie disponibili del libro richiesto.\n");
            return;
        }
        temp=temp->next;
    }
    printf("Libro non trovato.\n");
}





void restituzione(Libro* temp)
{
    int isbn_corrente=0;
    printf("ISBN: ");
    scanf(" %d",&isbn_corrente);
//scorro tutta la lista
    while (temp!=NULL) 
    {
//se trovo il libro prestato
        if (isbn_corrente==temp->isbn) 
        {
            if (temp->copie_prestate>0)
            {
                temp->copie_prestate--;
                printf("Operazione completata.\n");
            }
            else
                printf("Non risultano copie in prestito.\n");
            return;
        }
        temp=temp->next;
    }
    printf("Libro non trovato.");
}





//bisogna cancellare la lista dei libri e liberare la memoria prima di terminare il programma
void uscita(Libro* head) 
{
    Libro* nodo;
    while ((nodo=head)!=NULL)
    {
        head=head->next;
        free(nodo);
    }
    printf("Bye\n");
    exit(0);
}





int main() {
    Libro* head=NULL;
    head=copia_libri_in_lista(head);
//se la lista è vuota, significa che non c'è memoria e il programma non può continuare
    if (head==NULL) 
        return 0;
    int scelta=0;
    void (*menu[5])(Libro*) = {stampa_catalogo,ricerca_libri,prestito,restituzione,uscita};
    while (scelta!=5)
    {
        printf("Scegli un opzione:\n1) Stampa catalogo.\n2) Cerca.\n3) Prestito.\n4) Restituzione.\n5) Esci.\nScelta:  ");
        while (!scanf(" %d%*[^\n]\n",&scelta) || scelta<1 || scelta>6)
        {
            printf("Errore. Scelta non valida.\n");
//ripulisco il buffer in modo che dati erroneamente lasciati in stdin non influiscano con la scelta
            while (getchar()!='\n'); 
        }
        (*menu[scelta-1])(head);
//ripulisco il buffer in modo che dati erroneamente lasciati in stdin non influiscano con la scelta
        while (getchar()!='\n'); 
    }
//in caso per qualsiasi motivo debba uscire dal while, la memoria dinamica allocata viene comunque liberata
    (*menu[scelta-1])(head); 
    return 0;
}
