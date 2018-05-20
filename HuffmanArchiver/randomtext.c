#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


int main(){

  FILE* setfile = fopen("message.txt" , "w");

  char ALLSIMBOLS[256];
  for(int i= 0; i < 256; i++){
    ALLSIMBOLS[i] = i;
  }

  srand(time(0));
  for(int i = 0; i < 10202; i++){
    fprintf(setfile , "%c" , ALLSIMBOLS[rand() % 256]);
  }
  fclose(setfile);
  return 0;
}