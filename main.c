#include "src/analizer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fptr = fopen("test.txt", "r");
  if (fptr == NULL) {
    perror("File not read");
    return 1;
  }

  char line[100];

  while (fgets(line, sizeof(line), fptr)) {
    read_line(line);
  }

  fclose(fptr);

  return 0;
}
