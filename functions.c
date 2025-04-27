#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "structures.c"

int get_file_size(char *file_name){
  int total = 1;
  int c = 0;

  FILE *fp;
  fp = fopen(file_name, "r");

  while ((c = fgetc(fp)) != EOF){
    total++;
  }
  fclose(fp);

  return total;
}

void print_code(const char *a, int current) {
	for (int i = 0; a[i] != '\0'; i++) {
		if (i == current)
			printf("\033[47;30m%c\033[0m", a[i]);
		else
			printf("%c", a[i]);
	}
	printf("\n");
}

void print_pointer_cells(int *pointer, int p_i, int *stack_pointer, int stack_index) {
	printf("CODE:\n");
  for (int i = 0; i < 10; i++) {
		if (i == p_i)
			printf("\033[47;30m %d \033[0m|", pointer[i]);
		else
			printf(" %d |", pointer[i]);
	}
	printf("\nSTACK:\n");

  for (int i = 0; i < 10; i++){
    if (i == stack_index){
      printf("\033[47;30m %d \033[0m|", stack_pointer[i]);
    }else{
      printf(" %d |", stack_pointer[i]);
    }
  }
  printf("\n");
}

void shift(int* list, int len, int starting_pos){
  for(int i = 0; i < len-1; i++){
    list[starting_pos] = list[starting_pos+1];
  }
  list[len-1] = 0;
}

char* return_string(int buffer_size) {
  char *buffer = (char*)malloc(buffer_size+1 * sizeof(char));  
  if (buffer == NULL) {
     perror("Failed to allocate memory");
    return NULL;
  }
  int i = 0;
  char ch;

  while ((ch = getchar()) != '\n' && i < buffer_size - 1) {
    buffer[i++] = ch;
  }
  buffer[i++] = '\0';
  return buffer;}

bool has_char(const char *arr, char target){
  for(int i = 0; arr[i] != '\0'; i++){
    if(arr[i] == target){
      return 1;
    }
  }
  return 0;
}

void compile(char *a, int fs){
  struct TOKENS tokens;

  tokens.PLUS = '+';
  tokens.MINUS = '-';
  tokens.LEFT = '<';
  tokens.RIGHT = '>';
  tokens.BRACKET_LEFT = '[';
  tokens.BRACKET_RIGHT = ']';
  tokens.PRINT = '.';
  tokens.INPUT = ',';
  tokens.NUMBER_INPUT = ';';
  tokens.PRINT_NUMBER = ':';
  tokens.ADD_STACK = '#';
  tokens.REMOVE_STACK = '$';
  tokens.STACK_LEFT = '\\';
  tokens.STACK_RIGHT = '/';
   
  int depth = 0;
  int left_brackets_amount = 0;
  int right_brackets_amount = 0;
  int stack_ini = 0;
   
   for (int i = 0; i < fs; i++){
    if (a[i] == tokens.PLUS){
      //printf("PLUS\n");
      NULL;

    }else if( a[i] == tokens.MINUS){
      //printf("MINUS\n");
      NULL;

    }else if(a[i] == tokens.LEFT){
      //printf("LEFT\n");
      NULL;

    }else if(a[i] == tokens.RIGHT){
      //printf("RIGHT\n");
      NULL;

    }else if(a[i] == tokens.BRACKET_LEFT){
      //printf("BRACKET_LEFT\n");
      left_brackets_amount++;
      depth++;

    }else if (a[i] == tokens.BRACKET_RIGHT){
      //printf("BRACKET_RIGHT\n");
      
      if (depth == 0){
        printf("Invalid syntax!\n']' found without a matching ']' at position %d\n", (i+1));
        exit(1);
      }
      right_brackets_amount++;
      depth--;

    }else if (a[i] == tokens.PRINT){
      //printf("PRINT\n");
      NULL;

    }else if (a[i] == tokens.INPUT){
      //printf("INPUT\n");
      NULL;

    }else if(a[i] == tokens.NUMBER_INPUT){
      NULL;

    }else if(a[i] == tokens.PRINT_NUMBER){
      NULL;

    }else if(a[i] == ' ' || a[i] == 10){
      //printf("%s\n", (a[i] == ' ') ? "SPACE":"NEW_LINE");
      if(a[i] == 10){
        a[i] = ' ';
      }
    
    }else if(a[i] == '\0'){
      //printf("EOF\n");
      NULL;

    }else if(a[i] == 127){
      NULL;

    }else if(a[i] < 32 || (a[i] > 126 && a[i] != '\0')){
      //printf("Invalid char '%c' (ASCII: %d) at position %d!\n", a[i], (int)a[i], i);
      //exit(1);
      a[i] = ' ';
    }else if(a[i] == tokens.STACK_LEFT || a[i] == tokens.STACK_RIGHT){
      NULL;

    }else if(a[i] == tokens.ADD_STACK){
      stack_ini = 1;

    }else if(a[i] == tokens.REMOVE_STACK){
      if (!stack_ini){
        printf("CANNOT REMOVE FROM STACK, AS IT WAS NOT INITIALIZED.\n");
        exit(1);

      }
    }
  }

  if(left_brackets_amount - right_brackets_amount != 0){
  printf("Error! there's a '%s' missing!\n", (left_brackets_amount > right_brackets_amount) ? "]" : "[" );
  exit(1);
  }
  printf("COMPILED SUCCEFULLY.\n");
}

