#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  clear(); //custom system call that was created to clear the console
  char username[32];
  char password[32];

  printf(1, "                                            \n");
  printf(1, "                                            \n");
  printf(1, "                                            \n");
  printf(1, "            \\  /  \\      /                \n");
  printf(1, "             \\/    \\    /  __             \n");
  printf(1, "             /\\     \\  /  |__             \n");
  printf(1, "            /  \\     \\/   |__|            \n");
  printf(1, "                                            \n");
  printf(1, "       Welcome to this Random System        \n");
  printf(1, "                                            \n");
  printf(1, "============================================\n");
  printf(1, "=      Please Enter Your Credentials       =\n");
  printf(1, "============================================\n");

  printf(1, "\n");
  printf(1, "\n");


  while(1){
    printf(1, "Username: ");
    gets(username, sizeof(username));

    printf(1, "Password: ");
    gets(password, sizeof(password));

    username[strlen(username)-1] = 0;
    password[strlen(password)-1] = 0;

    if(strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0){
      printf(1, "\nWelcome %s!\n", username);

      char *argv[] = { "sh", 0 };
      exec("sh", argv);

      printf(1, "Failed to start shell\n");
      exit();
    } else {
      printf(1, "\nLogin failed\n\n");
    }
  }

  exit();
}