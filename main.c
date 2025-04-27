#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

int main(int argc, char *argv[]){
  FILE *fp;
  fp = fopen(argv[1], "r");
  
  if (fp == NULL){
    printf("Wrong file name\n");
    return 1;
  }

  int step_mode = 0;
  int edit_mode = 0;

  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "--step") == 0){
      step_mode = 1;
    }else if(strcmp(argv[i], "--edit") == 0){
      edit_mode = 1;
    }
  }

  int file_size = get_file_size(argv[1]);

  char a[file_size];

  //fgets(a, file_size, fp);

int i = 0, c;
while ((c = fgetc(fp)) != EOF && i < file_size - 1) {
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r') continue;
	a[i++] = c;
}
a[i] = '\0';
  
  compile(a, file_size);

  int *pointer = calloc(30000, sizeof(int));

  int a_i = 0;
  int p_i = 0;
  int stack[300];
  int stack_top = -1;
  char output_buffer[1024];
  int output_index = 0;
  int *num_stack = calloc(1500, sizeof(int));
  int stack_index = 0;
  
  while (a[a_i] != '\0'){
   if(a[a_i] == ' ' || a[a_i] == '\n' || a[a_i] == 10){
      a_i++;
      continue;
    }

     //printf("p_i before move: %d\n", p_i);
     switch (a[a_i]){

      case '+': if(pointer[p_i] == 255){pointer[p_i] = 0;}else{pointer[p_i]++;}; break;

      case '>': p_i++; break;

      case '<': if(p_i != 0){p_i--;}else{continue;}; break;

      case '-': if(pointer[p_i] == 0){pointer[p_i] = 255;}else{pointer[p_i]--;}; break;
      
      case '[':
        if (pointer[p_i] == 0){
          int depth = 1;
          
          while(depth > 0){
            a_i++;
            if(a[a_i] == ']'){
              depth--;
            }
          }
        }else{
          stack[++stack_top] = a_i;
        }
        break;
      
      case ']':
        if(pointer[p_i] != 0){
          a_i = stack[stack_top];
        }else{
          stack_top--;
        }
        break; 
       
      case '.': if (pointer[p_i] >= 32 && pointer[p_i] <= 126) {printf("%c\n", pointer[p_i]); if(output_index < sizeof(output_buffer) - 1){output_buffer[output_index++] = pointer[p_i];}}; break;

      case ',': pointer[p_i] = getchar(); break;

      case ';': if (scanf("%d", &pointer[p_i]) != 1) { printf("Invalid number input!\n"); exit(1); } int ch; while((ch = getchar()) != '\n' && ch != EOF); break;
      
      case ':': {
	      char num_output[16];
	      int len = snprintf(num_output, sizeof(num_output), "%d ", pointer[p_i]);
      	if (output_index + len < sizeof(output_buffer)) {
	      	for (int i = 0; i < len; i++) {
		      	output_buffer[output_index++] = num_output[i];
	      	}
       	}
      	break;
      }

      case '#':{
        int index_before = stack_index;
        if(num_stack[stack_index] != 0){
          while(num_stack[stack_index] != 0){
            stack_index++;
          }
        }
        num_stack[stack_index] = pointer[p_i];
        stack_index = index_before;

        break;
      }

      case '$':{
        int current_num = num_stack[stack_index];
        int amount_before_0 = 0;
        for(int i = 0; ; i++){
          if(num_stack[i] != 0){
            amount_before_0++;
          }else{
            break;
          }
        }

        printf("%d\n", amount_before_0);

        pointer[p_i] = num_stack[stack_index];
        
        if(amount_before_0 > 1){
          for(int i = 0; i < amount_before_0-1; i++){
            shift(num_stack, amount_before_0, stack_index);
          }
        }else{
          num_stack[stack_index] = 0;
        }

        break;
      }

      case '\\': {
        if(stack_index == 0){
          NULL;
        }else{
          stack_index--;
        }
        break;
      }

      case '/': {
        stack_index++;
      }

     }
    
    if(step_mode){
    print_code(a, a_i);
    print_pointer_cells(pointer, p_i, num_stack, stack_index);
    char act = getchar();
    if (act == 'x'){
        step_mode = 0;
        a_i++;
    }else if(act == 'q'){
      break;
    
    }else{ 
      a_i++;
    }
    
    }else{
    a_i++;
    if(output_buffer[0] == 'x'){
        output_buffer[0] = '\b';
      }
    }
  }

  if(edit_mode){
    printf("IRT EDITOR:\n");
    char *b = return_string(9999);
    while (!has_char(b, 'q')){
    for (int i = 0; b[i] != '\0'; i++){
       printf("\n");
       print_pointer_cells(pointer, p_i, num_stack, stack_index);
       printf("\n");
    
    }
    free(b);
     b = return_string(9999);
    }
    free(b);
  }
 
  output_buffer[output_index] = '\0';
  printf("\n\nFINAL OUTPUT:\n%s\n", output_buffer);
    
  printf("\n\nCODE:\n%s\n", a);
 
   for (int i = 0; i < 10; i++){
    printf(" %d |", pointer[i]);

  }

  printf("\nSTACK:\n");

  for(int i = 0; i < 10; i++){
    printf("%d | ", num_stack[i]);
  }
 
  printf("\n");
  free(pointer);
  fclose(fp);

  return 0;
}
