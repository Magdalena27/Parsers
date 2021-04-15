#include <regex.h>
#include <stdio.h>
#include <string.h>

//Funkcja sprawdzajaca poprawnosc wprowadzonego wyrazenia
void match(regex_t *PrecompiledPattern, char *InputString) {

	//Funkcja regexec() porownuje zadany ciag znakow ze skompilowanym wyrazeniem regularnym
	//i zwraca 0, jesli wprowadzone wyrazenie arytmetyczne jest zgodne z zaprojektowana
  //przeze mnie gramatyka.
  if (regexec(PrecompiledPattern, InputString, 0, NULL, 0) == 0) {
		printf("\nWyrazenie arytmetyczne: \"%s\" jest poprawne.\n", InputString);
	} else {
    printf("\nWyrazenie arytmetyczne: \"%s\" nie jest poprawne.\n", InputString);
    //Jesli wyrazenie nie jest poprawne, a zawiera ; a wiec sklada sie z kilku wyrazen arytmetycznych, sprawdzane jest kazde z nich.
    if (strstr(InputString, ";")!=NULL)
    {
      char *token;
      token = strtok(InputString, ";"); //Podzielenie wyrazenia
      while (token != NULL)
      {
        match(PrecompiledPattern, token); //Sprawdzanie pojedynczego wyrazenia arytmetycznego
        token = strtok(NULL, ";");
      }
    }
	}
}

//Funkcja odpowiedzialna za skuteczne pobranie wartosci wskazujacej czy program ma kontynuowac dzialanie, czy je zakonczyc
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

int main() {
  printf("______________________________________________________________________________\n");
  printf("Analizator skladniowy sprawdzajacy poprawnosc wyrazen arytmetycznych.\n");
  printf("Wyrazenia moga sie skladac z liczb naturalnych i operatorow: +, -, *, /, ^.\n");
  printf("Mozna wprowadzic kilka wyrazen oddzielonych srednikiem.\n");
  printf("Przyklad wyrazenia poprawnego: 159+987;1/2*15\n");
  printf("______________________________________________________________________________\n");

	int regcompValue;
	regex_t RegexExpression; //Zmienna, pod ktorej adresem przechowywane jest skompilowane wyrazenie regularne
  const char *Regex = "^[[:digit:]]+([-\\+\\*\\^\\/][[:digit:]]+)+(;[[:digit:]]+([-\\+\\*\\^\\/][[:digit:]]+)+)*$"; //Stala przechowujaca wyrazenie regularne
	//Kompilacja wyrazenia regularnego
	regcompValue = regcomp(&RegexExpression, Regex, REG_EXTENDED);

  //Funkcja regcomp() zwraca 0, gdy kompilacja wyrazenia regularnego zakonczyla sie sukcesem
  //W przeciwnym wypadku zwraca kod bledu
	if  (regcompValue != 0) {
		printf("Niepowodzenie kompilacji wyrazenia regularnego. Kod bledu: %d\n", regcompValue);
	}

  char DoYouWantToContinue; //Zmienna przechowujaca informacje, czy uzytkownik chce kontynuowac
  do
  {
    DoYouWantToContinue = 1;
    char InsertedExpression[100]; //Zmienna przechowujaca wprowadzone wyrazenie
    printf("\nWprowadz wyrazenie arytmetyczne: ");
    scanf("%s", InsertedExpression); //Strumien wejsciowy
    match(&RegexExpression, InsertedExpression); //Sprawdzenie poprawnosci wyrazenia
    DoYouWantToContinue = Continuation(); //Pobranie informacji o kontunuacji dzialania programu
  } while(DoYouWantToContinue=='y');

	//Zwolnienie pamieci zalokowanej przez funkcje regcomp()
	regfree(&RegexExpression);
	return 0;
}
