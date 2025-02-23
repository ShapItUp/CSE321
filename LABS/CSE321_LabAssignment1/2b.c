#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *in_file, *out_file;
    char current_char, prev_char = ' ';  

    
    in_file = fopen("input.txt", "r");
    out_file = fopen("output.txt", "w");
    
    current_char = fgetc(in_file); 
    while (current_char != EOF) {
      
        if (!(prev_char == ' ' && current_char == ' ')) {
            fputc(current_char, out_file);
        }
        prev_char = current_char;
        current_char = fgetc(in_file); 
    }
    
    fclose(in_file);
    fclose(out_file);

    printf("Extra spaces have been removed!\n");

    return 0;
}

