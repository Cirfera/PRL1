#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>





#define NUMERO_STATI 11





enum stato { Stato_0, Stato_1, Stato_2, Stato_3, Stato_4, Stato_5, Stato_6, Stato_fine_0, Stato_fine_1, Stato_fine_2, Stato_fine_3, ERRORE};




//Regole di transazioni dallo Stato_0;
enum stato S0 (char c)
{
  //Il carattere è una lettera maiuscola
  if(isupper(c))
  {
    return Stato_0;
  }
  else
  {
    if (c=='0')
    {
      return Stato_1;
    }
    else
    {
      //Il carattere è una lettera minuscola o un numero [1-9]
      return ERRORE;
    }
  }
}




//Dopo la lettura di '0' mi ritrovo in questo stato
enum stato S1 (char c)
{
  //Controllo se inserisco una cifra;
  if(isdigit(c))
  {
    if(c=='1')
    {
      return Stato_4;
    }
    //Se la cifra è diversa da 1;
    else
    {
      return Stato_2;
    }
  }
  //Se è una lettera;
  else
  {
    return ERRORE;
  }
}




//La stringa letta è del tipo [A-Z]*0[02-9]
enum stato S2 (char c)
{
  //Controllo se ho inserito una cifra
  if(isdigit(c))
  {
    return Stato_3;
  }
  else
  //In caso di lettera;
  {
    return ERRORE;
  }
}




//Stringa letta è del tipo [A-Z]*0[02-9][0-9]
enum stato S3 (char c)
{
  //Controllo se ho inserito una cifra
  if(isdigit(c))
  {
    return Stato_fine_3;
  }
  //Se inserisco una lettera;
  else
  {
    return ERRORE;
  }
}




//Stringa letta fino ad ora è del tipo [A-Z]*01
enum stato S4 (char c)
{
  //Controllo se ho una cifra
  if(isdigit(c))
  {
    if(c=='1')
    {
      return Stato_5;
    }
    //Se la cifra è diversa da 1;
    else
    {
      return Stato_6;
    }
  }
  //Se trovo una lettera;
  else
  {
    return ERRORE;
  }
}




//Stringa letta fino ad ora tipo [A-Z]*011
enum stato S5 (char c)
{
  //Controllo se ho una cifra;
  if (isdigit(c))
  {
    //Se leggo tre volte 1 consecutivamente;
    if (c=='1')
    {
      return Stato_fine_0;
    }
    //La cifra è diversa da 1;
    else
    {
      return Stato_fine_1;
    }
  }
  //Se trovo una lettera;
  else
  {
    return ERRORE;
  }
}




//La stringa letta è del tipo [A-Z]*01[02-9]
enum stato S6 (char c)
{
  //Controllo se ho una cifra;
  if (isdigit(c))
  {
    return Stato_fine_2;
  }
  //Se è una lettera;
  else
  {
    return ERRORE;
  }
}




//Stringa letta fino ad ora [A-Z]*01111*, cioè ho letto tre 1 come cifre terminali ma posso continuare a leggerne o leggere le 3 cifre finali differenti ;
enum stato SF0 (char c)
{
  //Controllo se è una cifra
  if (isdigit(c))
  {
    //Se 1 rimango nello stesso stato
    if(c=='1')
    {
      return Stato_fine_0;
    }
    //Se diverso da 1 cambio stato
    else
    {
      return Stato_fine_1;
    }
  }
  //Se è una lettera;
  else
  {
    return ERRORE;
  }
}




//Stringa letta fino ad ora termina con [09]{3} di cui l'ultimo diverso da 1 quindi posso leggere altre due cifre;
enum stato SF1 (char c)
{
  //Controllo se è un numero;
  if (isdigit(c))
  {
    return Stato_fine_2;
  }
  //Se è una lettera;
  else
  {
    return ERRORE;
  }
}




//La stringa letta fino ad ora termina con [0-9]{3} di cui il secondo è diverso da 1 quindi posso inserire ancora un'altra cifra;
enum stato SF2 (char c)
{
  //Controllo se è un numero;
  if (isdigit(c))
  {
    return Stato_fine_3;
  }
  //Se è una lettera;
  else
  {
    return ERRORE;
  }
}




//La stringa letta fino ad ora termina con  [0-9]{3} di ui il primo diverso da 1
enum stato SF3 (char c)
{
  //Ho già letto i caratteri terminali;
  return ERRORE;
}





int main ()
{
  //Array di puntatori a funzioni per i passaggi da uno stato all'altro;
  enum stato(*transizione[NUMERO_STATI])(char) = {S0, S1, S2, S3, S4, S5, S6, SF0, SF1, SF2, SF3};
  //Inzializzazione automa;
  enum stato automa = Stato_0;
  char input;
  //Eseguo transizioni fino a quando non viene letta tutta la stringa o fino a quando l'automa finice in errore;
  while((input=getchar()) != '\n' & automa != ERRORE)
  {
    automa = (*transizione[automa])(input);
  }
  //Verifico in che stato sia l'automa al termine delle transizioni;
  if(automa>6 && automa<11)
  {
    printf("stringa appartenente al linguaggio\n");
  }
  else
  {
    printf("stringa non appartenente al linguaggio\n");
  }
  return 0;
}
