#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  char username[32];
  char password[32];

  printf(1, "login: ");
  gets(username, sizeof(username));

  printf(1, "password: ");
  gets(password, sizeof(password));

  printf(1, "\nYou entered:\n");
  printf(1, "username: %s\n", username);
  printf(1, "password: %s\n", password);

  exit();
}