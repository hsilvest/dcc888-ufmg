/*
 * main.c
 *
 *  Created on: Mar 6, 2014
 *      Author: ampaiva
 */

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv) {
  int i = 1;
  int max = 0;
  while (i < argc) {
    int aux = atoi(argv[i]);
    i++;
    if (aux > max) {
      max = aux;
    }
  }
  printf("Max = %d\n", max);
}
