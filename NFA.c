#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RowsNumber = 11;
int ColumnsNumber = 8;

//Tabela stanow
char* StateTable[11][8] =
{
    {"delta(q,sigma)", "0", "1", "2", "3", "a", "b", "c"},
    {"s", "s, q0", "s, q1", "s, q2", "s, q3", "s, qa", "s, qb", "s, qc"},
    {"q0", "qi", "X", "X", "X", "X", "X", "X"},
    {"q1", "X", "qi", "X", "X", "X", "X", "X"},
    {"q2", "X", "X", "qi", "X", "X", "X", "X"},
    {"q3", "X", "X", "X", "qi", "X", "X", "X"},
    {"qa", "X", "X", "X", "X", "qch", "X", "X"},
    {"qb", "X", "X", "X", "X", "X", "qch", "X"},
    {"qc", "X", "X", "X", "X", "X", "X", "qch"},
    {"qi", "qi", "qi", "qi", "qi", "qi", "qi", "qi"},
    {"qch", "qch", "qch", "qch", "qch", "qch", "qch", "qch"}
};

int Table[10][7][2] =
{
    {{1,-1},{2,-1},{3,-1},{4,-1},{5,-1},{6,-1},{7,-1}},
    {{8},{-2},{-2},{-2},{-2},{-2},{-2}},
    {{-2},{8},{-2},{-2},{-2},{-2},{-2}},
    {{-2},{-2},{8},{-2},{-2},{-2},{-2}},
    {{-2},{-2},{-2},{8},{-2},{-2},{-2}},
    {{-2},{-2},{-2},{-2},{9},{-2},{-2}},
    {{-2},{-2},{-2},{-2},{-2},{9},{-2}},
    {{-2},{-2},{-2},{-2},{-2},{-2},{9}},
    {{8},{8},{8},{8},{8},{8},{8}},
    {{9},{9},{9},{9},{9},{9},{9}}
};

//s = -1
//q0 = 1
//q1 = 2
//q2 = 3
//q3 = 4
//qa = 5
//qb = 6
//qc = 7
//qi = 8
//qch =9
//X = -2

//Zdefiniowanie znaku oddzielajacego slowa
const char delimiter[] = "#";

int main()
{
    printf("**********************************************************");
    printf("\nNFA sprawdzajacy czy w slowach z pliku\n!!!!\t\t text.txt \t\t!!!!\nwytepuja powtorzenia symboli znajdujacych sie obok siebie.\n\nDozwolone symbole: 0, 1, 2, 3, a, b, c\nSlowa powinny byc oddzielone '#'.\n\nPrzyklad zawartosci pliku: 03221#10aa2#\n");
    printf("***********************************************************\n\n\n");

    //Wczytywanie pliku
    FILE *readedFile;
    static char fileContent[1000]; //Plik moze zawierac do 1000 znakow
    if((readedFile = fopen("text.txt", "r")) !=NULL)
    {
        while (fgets(fileContent, sizeof(fileContent), readedFile))
        {
            printf("Zawartosc Twojego pliku: %s\n", fileContent);

            char *token; //Przechowuje wczytywane slowo
            token = strtok(fileContent, delimiter);
            while (token != NULL)
            {
                //Definiowanie niezbednych zmiennych
                printf("\n\t\tSlowo: %s\n", token); //Wyswietlenie sprawdzanego slowa
                int searchedColumn; //Zmienna przechowujaca indeks kolumny
                int state_history[100][100];
                state_history[0][0] = -1;
                int index = 0; //Poczatkowy indeks wiersza tabeli z historia stanow
                int actual_state; //Jeden z aktywnych stanow
                int accepted; //Przechowuje informacje czy slowo zostalo zaakceptowane
                int c_index = 0; //Poczatkowy indeks kolumny tabeli z historia stanow
                int WordLen; //Dlugosc slowa
                int WL = (int)strlen(token);
                char *Translated[100][100]; //Tabela zawierajaca historie stanow

                while (*token) //Dla kazdego slowa
               {

                  printf("symbol: %c\n", *token); //Wyswietlenie analizowanego symbolu
                  WordLen = (int)strlen(token); //Oblicznie dlugosci slowa
                  if (state_history[index][0]==-1) //Jesli aktualny stan
                  {
                    state_history[index+1][0] = -1;//to s to jednym z kolejnych tez bedzie s
                  }
                  c_index = 0;
                  actual_state = 0;

                  for (int i=0; i<WordLen; i++)
                  {
                    //Instrukcja switch umozliwia wybor odpowiedniej kolumny tabeli stanow
                    //w zaleznosci od kolejnego analizowanego symbolu
                    switch(token[i])
                    {
                    case '0':
                      searchedColumn = 0;
                      break;
                    case '1':
                      searchedColumn = 1;
                      break;
                    case '2':
                      searchedColumn = 2;
                      break;
                    case '3':
                      searchedColumn = 3;
                      break;
                    case 'a':
                      searchedColumn = 4;
                      break;
                    case 'b':
                      searchedColumn = 5;
                      break;
                    case 'c':
                      searchedColumn = 6;
                      break;
                    default:
                      printf("Char not allowed. Allowed chars: 0, 1, 2, 3, a, b, c\n");
                    }
                    c_index++;

                    //Uzupelnienie historii stanow i okreslenie stanu aktualnego
                    state_history[index][c_index] = Table[actual_state][searchedColumn][0];
                    actual_state = Table[actual_state][searchedColumn][0];

                    if(actual_state==-2) //Zatrzymanie analizy galezi, gdy brak kolejnego stanu
                    {
                      actual_state = -1;
                      c_index = 0;
                      break;
                    }
                    if(actual_state == 8)
                    {
                      accepted = 1; //Zapisanie faktu pierwszego powtorzenia symbolu dla cyfry
                    }
                    if(actual_state == 9)
                    {
                      accepted = 2; //Zapisanie faktu pierwszego powtorzenia symbolu dla litery
                    }
                  }

                  token++;

                  //Przepisanie historii stanow do tabeli docelowej
                  for(int i=0; i<WL+1; i++)
                  {
                    for(int j=0; j<WL; j++)
                    {
                      switch(state_history[i][j])
                      {
                        case -2:
                          Translated[i][j] = "X";
                          break;
                        case 1:
                          Translated[i][j] = "q0";
                          break;
                        case 2:
                          Translated[i][j] = "q1";
                          break;
                        case 3:
                          Translated[i][j] = "q2";
                          break;
                        case 4:
                          Translated[i][j] = "q3";
                          break;
                        case 5:
                          Translated[i][j] = "qa";
                          break;
                        case 6:
                          Translated[i][j] = "qb";
                          break;
                        case 7:
                          Translated[i][j] = "qc";
                          break;
                        case 8:
                          Translated[i][j] = "qi";
                          break;
                        case 9:
                          Translated[i][j] = "qch";
                          break;
                        case -1:
                          Translated[i][j] = "s";
                          break;
                        default:
                          Translated[i][j] = " ";
                      }
                    }
                  }

                  //Wyswietlenie aktywnych stanow
                  printf("Aktywne stany: ");
                  for(int m=0; m<index+2; m++)
                  {
                    printf("%s ", Translated[index+1-m][0+m]);
                  }
                  printf("\n");
                  index++;

        }
                  //Wyswietlenie historii stanow
                  printf("\nHistoria stanow: \n");
                  for (int j=0; j<WL+1; j++)
                  {
                    for(int k=0; k<WL; k++)
                    {
                     printf("%s ", Translated[j][k]);
                    }
                    printf("\n");
                  }

                //Sprawdzenie czy w chodz jeden ze stanow jest akceptujacy
                if(accepted==1)
                {
                printf("Przynajmniej jeden ze stanow koncowych jest stanem akceptujacym.\nSlowo zaakceptowane.\nPowtorzenie wystapilo wsrod cyfr.\n\n");
                }
                else if(accepted==2)
                {
                printf("Przynajmniej jeden ze stanow koncowych jest stanem akceptujacym.\nSlowo zaakceptowane.\nPowtorzenie wystapilo wsrod liter.\n\n");
                }
                else
                {
                  printf("Zaden ze stanow koncowych nie jest stanem akceptujacym.\nSlowo niezaakceptowane.\n\n");
                }
                token = strtok(NULL, delimiter); //Pobranie kolejnego slowa
            }
        }

    }
    else
    {
        printf("Nie ma takiego pliku. Plik powinien miec nazwe \n!!!!\t\t text.txt\t\t!!!!\n Mozna rowniez zmienic nazwe wczytywanego pliku w 61 linii kodu.\n Nastepnie sprobuj ponownie uruchomic program.\n");
    }

    fclose(readedFile); //Zamkniecie pliku

    return 0;
}
