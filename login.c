#include "types.h"
#include "stat.h"
#include "user.h"

#define ROLE_USER 0
#define ROLE_ADMIN 1

struct user {
  char username[16];
  char password[16];
  int role;
};

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

    int fd = open("users", 0);
    if(fd < 0){
      printf(1, "Error: no user database\n");
      exit();
    }

    struct user u;
    int found = 0;

    while(read(fd, &u, sizeof(u)) == sizeof(u)){
      if(strcmp(u.username, username) == 0 &&
         strcmp(u.password, password) == 0){
        found = 1;
        printf(1, "\nWelcome %s!\n", u.username);

        char *argv[] = { "sh", 0 };
        exec("sh", argv);
      }
    }

    close(fd);

    if(!found){
      printf(1, "\nLogin failed\n\n");
    }
  }
}