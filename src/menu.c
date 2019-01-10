
#include <menu.h>

void menu(bool * procced, int (*f)(bool)) {
    int names_count = 3;
    char input;
    char names2[] = "start#stop#show [ip] count#--help#exit";
    char names[names_count][BUFFER_LENGTH];
    int nread = 0;
    int step = 0;
    int count = 0;

    for (int i = 0; i < names_count; i++) {
      sscanf(names2 + step, "%[^#]%*c%n", names[i], &nread);
      step += nread;
    }
  
    for (;true;) {
        
        system("clear");
  
      puts("Available commands\n");
      for (int i = 0; i < names_count; i++)
        printf(" %s ,", names[i]);

        getchar();
      input = getchar();
  
      if (input = '1') {
        procced = false;
        return;
      }
        /*
      else if (!strcmp(input, "stop"))
        procced = false;
      else if (!strcmp(input, "show [ip] count")) {
      }else if (!strcmp(input, "--help")) {
      }else if (!strcmp(input, "exit")) 
        return;
      */
    }
  }