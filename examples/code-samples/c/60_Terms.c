#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printLink(const ModioLink* link)
{
  if(link)
  {
    if(link->required)
    {
      printf("Visit %s on %s\n", link->text, link->url);
    }
  }
}

void printButton(const ModioButton* button, char keyChar)
{
  if (button)
  {
    printf("[%c] %s\n", keyChar, button->text);
  }
}

void onTerms(void* object, ModioResponse response, ModioTerms terms)
{
  bool* wait = object;
  if (response.code == 200)
  {
    printf("--------- TERMS ---------\n");
    printf("%s\n", terms.plaintext);
    printf("--------- LINKS ---------\n");
    printLink(&terms.privacy);
    printLink(&terms.terms);
    printLink(&terms.website);
    printLink(&terms.manage);
    printf("--------------------------");
    printButton(&terms.agree, 'Y');
    printButton(&terms.disagree, 'N');

    while(true)
    {
      int c = getchar();
      if(c == 'Y' || c == 'y')
      {
        printf("Great!");
        break;
      }
      else if(c == 'N' || c == 'n')
      {
        printf("Sorry, can't allow you you to create a account");
        break;
      }
    }
  }
  else
  {
    printf("Failed to get terms\n");
  }

  wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, false, true, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  modioGetTerms(&wait, MODIO_SERVICE_STEAM, onTerms);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
