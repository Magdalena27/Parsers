#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RowsNumber = 7; //ilosc wierszy tabeli przejsc - uzywana w dalszej czesci programu
int ColumnsNumber = 4; //ilosc kolumn tabeli przejsc - uzywana w dalszej czesici programu
//Tabla przejsc. Znak theta jest symbolizowany przez _
char* StateTable[7][4] =
{
    {"delta", "0", "1", "_"},
    {"q0", "1, q1, L", "0, q2, L", "-, q4, -"},
    {"q1", "-, q4, -", "-, q4, -", "1, q3, -"},
    {"q2", "-, q4, -", "-, q4, -", "0, q5, L"},
    {"q3", "-, q4, -", "-, q4, -", "-, -, -"},
    {"q4", "-, -, -", "-, -, -", "-, -, -"},
    {"q5", "-, q4, -", "-, q4, -", "1, q3, -"},
};

//Funkcja wyswietlajaca instrukcje
void PrintInfo(void)
{
    printf("Wprowadz jednocyfrowa liczbe binarna.\nWpis powinien byc poprzedzony znakiem pustym _.\n");
    printf("Przykladem poprawnego wpisu jest: _0\n");
    printf("Liczba zostanie zwiekszona o 3.\n\n");
}

//Funkcja przejscia: pobiera aktualny stan i odczytany symbol oraz zwraca kolejny stan
char * TransitionFunction(char *actual_state, char *NextChar)
{
    char *start_state = actual_state;
    char *next_state;

    for (int i=0; i<RowsNumber; i++) //dla kazdej komorki w pierwszej liczac od lewej kolumnie
        if (strcmp(start_state, StateTable[i][0])==0) //sprawdza czy stan, to stan aktualny
            {
                    //jesli tak
                for (int j=0; j<ColumnsNumber; j++) //dla kazdej komorki w pierwszym wierszu


                    if(strcmp(NextChar, StateTable[0][j])==0) //sprawdza czy zawartosc komorki odpowiada wprowadzonemu symbolowi
                    {
                        if(strstr(StateTable[i][j], "q1")!=NULL)
                            next_state = "q1";
                        else if(strstr(StateTable[i][j], "q2")!=NULL)
                            next_state = "q2";
                        else if(strstr(StateTable[i][j], "q3")!=NULL)
                            next_state = "q3";
                        else if(strstr(StateTable[i][j], "q4")!=NULL)
                            next_state = "q4";
                        else if(strstr(StateTable[i][j], "q5")!=NULL)
                            next_state = "q5";
                        else
                            next_state = "-";
                        //jesli tak ustawia kolejny stan na stan
                        //znaleziony wsrod informacji rekordu tabeli
                        //o znalezionym wierszu i kolumnie
                        }
                }
        return next_state;
}

//Funkcja zapisujaca cyfre na podstawie rekordu tabeli przejsc
char * WriteNumber(char *actual_state, char *NextChar)
{
  char *start_state = actual_state;
  char *next_binary;
  for (int i=0; i<RowsNumber; i++) //dla kazdej komorki w pierwszej liczac od lewej kolumnie
        if (strcmp(start_state, StateTable[i][0])==0) //sprawdza czy stan, to stan aktualny
            {
                    //jesli tak
                for (int j=0; j<ColumnsNumber; j++) //dla kazdej komorki w pierwszym wierszu


                    if(strcmp(NextChar, StateTable[0][j])==0) //sprawdza czy zawartosc komorki odpowiada wprowadzonemu symbolowi
                    {
                        if(strstr(StateTable[i][j], "0")!=NULL)
                            next_binary = "0";
                        else if(strstr(StateTable[i][j], "1")!=NULL)
                            next_binary = "1";

                        //jesli tak ustawia kolejna cyfre na cyfre
                        //znaleziony wsrod informacji rekordu tabeli
                        //o znalezionym wierszu i kolumnie
                    }
            }
  return next_binary;
}

//Funkcja okreslajaca czy w znalezionym rekordzie tabeli wystepuje L
char* IsL(char *actual_state, char *NextChar)
{
  char *start_state = actual_state;
  char *Lyn;
  for (int i=0; i<RowsNumber; i++) //dla kazdej komorki w pierwszej liczac od lewej kolumnie
        if (strcmp(start_state, StateTable[i][0])==0) //sprawdza czy stan, to stan aktualny
            {
                    //jesli tak
                for (int j=0; j<ColumnsNumber; j++) //dla kazdej komorki w pierwszym wierszu


                    if(strcmp(NextChar, StateTable[0][j])==0) //sprawdza czy zawartosc komorki odpowiada wprowadzonemu symbolowi
                    {
                        //jesli tak sprawdza czy w komorce wystepuje napis "L"
                        if(strstr(StateTable[i][j], "L")!=NULL)
                            Lyn="y";
                        else
                            Lyn="n";

                        //jesli tak zwraca "y"
                        //jesli nie zwraca "n"
                    }
            }
  return Lyn;
}

int main()
{
    char *actual_state = StateTable[1][0];

    //Definiuje tablice zbierajaca kolejne stany posrednie i stan koncowy
    char *Path[100][5];
    Path[0][0]=actual_state;

    //Definiuje tablice na kolejne zapisywane cyfry
    char *NextBinary[10];
    int WhichIteration = 0;
    int x;

    PrintInfo();
    char InsertedBinaryNumber [ 5 ];

    //Tablica, ktora po wpisaniu wartosci przez uzytkownika bedzie nadpisana
    //Przechowuje wpisany lancuch znakow
    char *InsertedNumber[3]={"_","_","_"};
    char *OK;
    int L;

    //Petla obslugujaca strumien wejsciowy
    do
    {
      printf("Wprowadz liczbe binarna: ");
      scanf("%5s", InsertedBinaryNumber); //strumien wejsciowy

      //jesli liczba nalezy do alfabetu
      if (strcmp(InsertedBinaryNumber, "_0")==0)

      {
        printf("\nLiczba prawidlowa\n\n"); //jest zaakceptowana
        OK = "Y";
        InsertedNumber[2] = "0";
        L=1;
      }
      else if(strcmp(InsertedBinaryNumber, "_1")==0)
      {
        printf("\nLiczba prawidlowa\n\n"); //jest zaakceptowana
        OK = "Y";
        InsertedNumber[2] = "1";
        L=2;
      }
      else if(strcmp(InsertedBinaryNumber, "_")==0)
      {
        printf("Wprowadzono jedynie znak pusty. Sprobuj jeszcze raz.\n");
        OK = "N";
      }
      else //jesli nie
      {
        printf("Wpis nieobslugiwany. Sprobuj ponownie.\n"); //zwraca komunikat
        OK = "N";

      }
      } while(strcmp(OK, "Y")!=0);

int InputLen = strlen(InsertedBinaryNumber);
int TabLen = 3;
int BinaryLen = 4;

char *NextChar;
char *next_binary;
char* Lyn;

//Glowna petla programu
do
{
  printf("Aktualny stan: %s\n", actual_state); //wyswietlenie informacji o stanie
  NextChar = InsertedNumber[TabLen-1]; //pobranie kolejnego znaku
  printf("Kolejny symbol: %s\n", NextChar); //wyswietlenie pobranego znaku
  Lyn = IsL(actual_state, NextChar); //sprawdzenie czy maszyna powinna przesunac glowice
  next_binary = WriteNumber(actual_state, NextChar); //pobranie cyfry do zapisania na tasmie
  actual_state = TransitionFunction(actual_state, NextChar); //przypisanie nowej wartosci stanu
  printf("Stan po wprowadzeniu: %s\n\n", actual_state); //wyswietlenie nowego stanu
  x = WhichIteration+1;//liczba porzadkowa aktualnej iteracji
  Path[x][0] = actual_state;//dopisanie kolejnego stanu do sciezki
  NextBinary[L+1] = next_binary;//napisanie cyfry na tasme
  if(strcmp(Lyn,"y")==0)
  {
    L--; //przesuniecie glowicy
  }
  WhichIteration++;
  TabLen--;
  BinaryLen--;
} while(strcmp(actual_state, "q3")!=0);


//wyswietlenie sciezki - kolejnych stanow w ktorych znalazl sie automat
printf("Sciezka: ");
for (int p=0;p<WhichIteration+1;p++)
    printf("%s, ", Path[p][0]);

//wyswietlenie uzyskanej liczby - zapis z tasmy
printf("\nUzyskana liczba: ");
for (int r=1; r<WhichIteration+1;r++)
    printf("%s", NextBinary[r]);

return 0;
}
