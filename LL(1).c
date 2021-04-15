#include <stdio.h>
#include <string.h>

//Symbole pierwsze dla kolejnych produkcji gramatyki
const char FIRST_Z[] = "0123456789( ";
const char FIRST_W[] = "0123456789(";
const char FIRST_W_PRIM[] = "*:+-^ ";
const char FIRST_P[] = "0123456789(";
const char FIRST_R[] = "0123456789";
const char FIRST_R_PRIM[] = ". ";
const char FIRST_L[] = "0123456789";
const char FIRST_L_PRIM[] = "0123456789 ";
const char FIRST_C[] = "0123456789";
const char FIRST_O[] = "*:+-^";

/*
Analizator skladniowy dziala na takiej samej zasadzie jak reczne sprawdzanie poprawnosci wyrazenia z dana gramatyka.
Gramatyka, zktora zgodnosc wprowadzanego wyrazenia jest sprawdzana (pusty - oznacza symbol pusty):
S::=W;Z
Z::=W;Z|pusty
W::=PW'
W'::=OW|pusty
P::=R|(W)
R::=LR'
R'::=.L|pusty
L::=CL'
L'::=L|pusty
C::=0|1|2|3|4|5|6|7|8|9
O::=*|:|+|-|^
*/

/*
Funkcje S, Z, W, WPrim, P, R, RPrim, L, LPrim, C, O sprawdzaja czy aktualnie sprawdzany znak nalezy do znakow pierwszych danej produkcji. Jesli tak zapisuja odpowiednie terminale i nieterminale (prawe strony produkcji dla wybranej alternatywy) do wektora ProductionList[]. Wszystkie dzialaja na tej samej zasadzie, dlatego opisuje tylko pierwsza z nich.
*/
char *S(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_W, ActualChar)!=NULL)
    {
            //Przypisywanie odpowiednich nieterminali i terminali od konca
            ProductionList[IndexOfMostLeftProduction] = 'Z';
            IndexOfMostLeftProduction--;
            ProductionList[IndexOfMostLeftProduction] = ';';
            IndexOfMostLeftProduction--;
            ProductionList[IndexOfMostLeftProduction] = 'W';
            ProductionList[0] = 'y'; //Wyrazenie zgodne z gramatyka na tym etapie analizy
    }
    else
    {
           ProductionList[0] = 'n'; //Wyrazenie niezgodne z gramatyka
    }
    return(ProductionList);
}

/*
Funkcje IndexAfterS, IndexAfterZ, IndexAfterW, IndexAfterWPrim, IndexAfterP, IndexAfterR, IndexAfterRPrim, IndexAfterL, IndexAfterLPrim, IndexAfterC oraz IndexAfterO zwracaja numer indeksu, pod ktorym znajduje sie pierwszy terminal badz nieterminal w ProductionList. Wszystkie dzialaja na tej samej zasadzie, dlatego opisuje tylko pierwsza z nich.
*/
int IndexAfterS(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    int NewIndex;
    if(strchr(FIRST_W, ActualChar)!=NULL)
    {
        NewIndex = IndexOfMostLeftProduction - 2; //Zatem pierwszy od lewej indeks z zapisanym nieterminalem jest rowny 43 i zgodnie z funkcja S odpowiada wpisowi 'W'
    }
    else
    {
        NewIndex = IndexOfMostLeftProduction; //W przypadku niezgodnosci wyrazenia z gramatyka nie zmieniam indeksu
    }
    return (NewIndex);
}

char *Z(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_W, ActualChar)!=NULL)
    {
            ProductionList[IndexOfMostLeftProduction] = 'Z';
            IndexOfMostLeftProduction--;
            ProductionList[IndexOfMostLeftProduction] = ';';
            IndexOfMostLeftProduction--;
            ProductionList[IndexOfMostLeftProduction] = 'W';
            ProductionList[0] = 'y';
    }
    else if(ActualChar==' ')
    {
        ProductionList[IndexOfMostLeftProduction] = ' ';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'n';
    }
    return(ProductionList);
}

int IndexAfterZ(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int newIndex;
    if(strchr(FIRST_W, InsertedProduction[AnalyzedChar])!=NULL)
    {
        newIndex = IndexOfMostLeftProduction - 2;
    }
    else if(InsertedProduction[AnalyzedChar]==' ')
    {
        newIndex = IndexOfMostLeftProduction;
    }
    else
    {
        newIndex = IndexOfMostLeftProduction;
    }
    return(newIndex);
}

char *W(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_P, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = 'w'; //Ma³e w jest równoznaczne W'
        IndexOfMostLeftProduction--;
        ProductionList[IndexOfMostLeftProduction] = 'P';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'n';
    }
    return(ProductionList);
}

int IndexAfterW(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NewIndex;
    if(strchr(FIRST_P, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NewIndex = IndexOfMostLeftProduction - 1;
    }
    else
    {
        NewIndex = IndexOfMostLeftProduction;
    }
    return(NewIndex);
}

char *WPrim(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_O, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = 'W';
        IndexOfMostLeftProduction--;
        ProductionList[IndexOfMostLeftProduction] = 'O';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[IndexOfMostLeftProduction] = ' ';
        ProductionList[0] = 'y';
    }
    return(ProductionList);
}

int IndexAfterWPrim(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NewIndex;
    if(strchr(FIRST_O, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NewIndex = IndexOfMostLeftProduction - 1;
    }
    else
    {
        NewIndex = IndexOfMostLeftProduction + 1;
    }
    return(NewIndex);
}

char *P(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_R, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = 'R';
        ProductionList[0] = 'y';
    }
    else if(ActualChar=='(')
    {
        ProductionList[IndexOfMostLeftProduction] = ')';
        IndexOfMostLeftProduction--;
        ProductionList[IndexOfMostLeftProduction] = 'W';
        IndexOfMostLeftProduction--;
        ProductionList[IndexOfMostLeftProduction] = '(';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'n';
    }
    return(ProductionList);
}

int IndexAfterP(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NewIndex;
    if(strchr(FIRST_R, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NewIndex = IndexOfMostLeftProduction;
    }
    else if(InsertedProduction[IndexOfMostLeftProduction]=='(')
    {
        NewIndex = IndexOfMostLeftProduction-2;
    }
    else
    {
        NewIndex = IndexOfMostLeftProduction;
    }
    return(NewIndex);
}

char *R(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_L, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = 'r'; //male r rownoznaczne z R'
        IndexOfMostLeftProduction--;
        ProductionList[IndexOfMostLeftProduction] = 'L';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'n';
    }
    return(ProductionList);
}

int IndexAfterR(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NewIndex;
    if(strchr(FIRST_L, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NewIndex = IndexOfMostLeftProduction - 1;
    }
    else
    {
        NewIndex = IndexOfMostLeftProduction;
    }
    return(NewIndex);
}

char *RPrim(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(ActualChar=='.')
    {
        ProductionList[IndexOfMostLeftProduction]='L';
        IndexOfMostLeftProduction--;
        ProductionList[IndexOfMostLeftProduction]='.';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'y';
    }
    return(ProductionList);
}

int IndexAfterRPrim(char *InsertedProduction, int AnalyzedChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    int NextIndex;
    if(InsertedProduction[AnalyzedChar]=='.')
    {
        NextIndex = IndexOfMostLeftProduction - 1;
    }
    else
    {
        NextIndex = IndexOfMostLeftProduction + 1;
    }
    return(NextIndex);
}


char *L(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_C, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = 'l'; //Male l rownoznaczne z L'
        IndexOfMostLeftProduction--;
        ProductionList[IndexOfMostLeftProduction] = 'C';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'n';
    }
    return(ProductionList);
}

int IndexAfterL(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NextIndex;
    if(strchr(FIRST_C, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NextIndex = IndexOfMostLeftProduction - 1;
    }
    else
    {
        NextIndex = IndexOfMostLeftProduction;
    }
    return(NextIndex);
}

char *LPrim(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_L, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = 'L';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[IndexOfMostLeftProduction] = ' ';
        ProductionList[0] = 'y';
    }
    return(ProductionList);
}

int IndexAfterLPrim(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NextIndex;
    if(strchr(FIRST_L, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NextIndex = IndexOfMostLeftProduction;
    }
    else
    {
        NextIndex = IndexOfMostLeftProduction + 1;
    }
    return(NextIndex);
}

char *C(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_C, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = ' ';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'n';
    }
    return(ProductionList);
}

int IndexAfterC(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NextIndex;
    if(strchr(FIRST_C, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NextIndex = IndexOfMostLeftProduction + 1;
    }
    else
    {
        NextIndex = IndexOfMostLeftProduction;
    }
    return(NextIndex);
}

char *O(char ActualChar, char ProductionList[], int IndexOfMostLeftProduction)
{
    if(strchr(FIRST_O, ActualChar)!=NULL)
    {
        ProductionList[IndexOfMostLeftProduction] = ' ';
        ProductionList[0] = 'y';
    }
    else
    {
        ProductionList[0] = 'n';
    }
    return(ProductionList);
}

int IndexAfterO(char *InsertedProduction, int AnalyzedChar, char *ProductionList, int IndexOfMostLeftProduction)
{
    int NextIndex;
    if(strchr(FIRST_O, InsertedProduction[AnalyzedChar])!=NULL)
    {
        NextIndex = IndexOfMostLeftProduction + 1;
    }
    else
    {
        NextIndex = IndexOfMostLeftProduction;
    }
    return(NextIndex);
}

char Continuation()
{
  //Jesli uzytkownik chce kontynuowac wpisuje: y
  //W przeciwnym wypadku wpisuje: n
  char WantToContinue;
  printf("\n\nCzy chcesz wprowadzic kolejne wyrazenie? (y/n)\n");
  scanf("%s", &WantToContinue);
  if (WantToContinue=='y'||WantToContinue=='n')
    return WantToContinue;
  else
  {
    //Jesli uzytkownik wpisal litere inna niz y lub n jest proszony o ponowny wybor
    printf("Nieobslugiwany znak. Wprowadz y - jesli chcesz kontynuowac lub n - jesli nie.");
    Continuation();
  }
  return WantToContinue;
}

int main()
{
    printf("*************************************************************************\n");
    printf("Witaj w analizatorze skladniowym. \nAnalizator sprawdza poprawnosc wyrazen arytmetycznych. \nMozna wprowadzic kilka wyrazen po oddzieleniu ich srednikami. \nNa koncu kazdego wyrazenia musi stac srednik, w przeciwnym wypadku nie ma \nodpowiedzi czy wyrazenie jest poprawne. \nNie uzywaj spacji. \nPrzyklad poprawnego wyrazenia: (1.2+5)*7;5-3;\n");
    printf("*************************************************************************\n\n");
    char DoYouWantToContinue; //Zmienna przechowujaca informacje, czy uzytkownik chce kontynuowac
    do
    {
      int IndexOfMostLeftProduction = 45; //Zmienna przechowujaca aktualny indeks terminala badz nieterminala, ktory wystepuje w ProductionList jako pierwszy od lewej
      int PreviousIndexOfMostLeftProduction; //Zmienna przechowujaca poprzedni indeks IndexOfMostLeftProduction
      char ProductionList[50]; //Wektor produkcji wedlug ktorych sprawdzane jest wprowadzone wyrazenie
      ProductionList[45]='S'; //Pierwszy nieterminal wpisany w wektorze
      ProductionList[0] = 'y'; //y - oznacza zgodnosc aktualnie sprawdzanego znaku z gramatyka
      char InsertedProduction[100]; //tablica przechowujaca wprowadzane wyrazenie
      int AnalyzedChar = 0; //Indeks aktualnie sprawdzanego znaku z wprowadzonego wyrazenia
      DoYouWantToContinue = 1;
      printf("\nWprowadz wyrazenie arytmetyczne: ");
      scanf("%s", InsertedProduction); //Strumien wejsciowy

      //Glowna petla programu
      while(AnalyzedChar<(int)strlen(InsertedProduction)) //Analizator analizuje wyrazenie, az do ostatniego znaku
      {
        char ActualChar = InsertedProduction[AnalyzedChar];
        printf("\nAnalizowany znak: %c\n", ActualChar);
        printf("Sprawdzanie poprawnosci z: ");

        if(ProductionList[0]=='y')//Jesli do tej pory wyrazenie jest zgodne z gramatyka, jest analizowane dalej
        {
        //Wybor produkcji (pierwsza od lewej w ProductionList) wedlug ktorej ma byc analizowany kolejny znak
        switch(ProductionList[IndexOfMostLeftProduction])
        {
        //Kazdy case dziala tak samo, dlatego opisalam tylko pierwszy
        case 'S':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction; //Zapisanie poprzedniego indeksu
            IndexOfMostLeftProduction = IndexAfterS(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction); //Znalezienie aktualnego indeksu pierwszego od lewej wpisu w ProductionList
            strcpy(ProductionList, S(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction)); //Zaktualizowanie ProductionList
            printf("S\n"); //Wyswietlenie pierwszej z lewej produkcji
            break;
        case 'Z':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterZ(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, Z(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("Z\n");
            break;
        case 'W':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterW(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, W(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("W\n");
            break;
        case 'w':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterWPrim(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, WPrim(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("w\n");
            break;
        case 'P':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterP(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, P(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("P\n");
            if(ActualChar=='(') //Zatwierdzenie terminala
            {
                IndexOfMostLeftProduction--;
                AnalyzedChar++;
            }
            break;
        case 'R':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterR(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, R(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("R\n");
            break;
        case 'r':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterRPrim(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, RPrim(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("r\n");
            if(ActualChar=='.') //Zatwierdzenie terminala
            {
                IndexOfMostLeftProduction++;
                AnalyzedChar++;
            }
            break;
        case 'L':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterL(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, L(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("L\n");
            break;
        case 'l':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterLPrim(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, LPrim(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            printf("l\n");
            break;
        case 'C':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterC(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, C(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            AnalyzedChar++;
            printf("C\n");
            break;
        case 'O':
            PreviousIndexOfMostLeftProduction = IndexOfMostLeftProduction;
            IndexOfMostLeftProduction = IndexAfterO(InsertedProduction, AnalyzedChar, ProductionList, IndexOfMostLeftProduction);
            strcpy(ProductionList, O(ActualChar, ProductionList, PreviousIndexOfMostLeftProduction));
            AnalyzedChar++;
            printf("O\n");
            break;
        case ';':
            printf(";\n");
            if(ActualChar==';')
            {
              ProductionList[IndexOfMostLeftProduction] = ' ';
              IndexOfMostLeftProduction++;
              AnalyzedChar++;
              printf("\n____Wyrazenie poprawne____\n");
            }
            else
            {
              //Niepoprawne wyrazenie
              ProductionList[0] = 'n';
            }

            break;
        case ')':
          printf(")\n");
          if(ActualChar==')')
          {
            //Zatwierdzenie terminala
            ProductionList[IndexOfMostLeftProduction] = ' ';
            IndexOfMostLeftProduction++;
            AnalyzedChar++;
          }
          else
          {
            //Niepoprawne wyrazenie
            ProductionList[0] = 'n';
          }

          break;
        }
    }
    else
    {
        printf("\n____Wyrazenie niezgodne z gramatyka____\n");
        break;
    }
    }

    DoYouWantToContinue = Continuation(); //Pobranie informacji o kontunuacji dzialania programu
    } while(DoYouWantToContinue=='y');

  return 0;
}
