
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "rule.h"
#include "helpers.h"

Rule* make_rule(char* key) {
  /*
    TODO 3
  */
    //constructor for rule, allocates memory for a new rule,
    //sets the key pointer to the argument and
    //sets the expansion pointer to a new linked list
    Rule* rule = malloc(sizeof(Rule));
    rule -> key = key;
    rule -> expansions = make_list();

    return rule;
  /*
    TODO 3
  */
}

void free_rule(Rule* rule) {
  /*
    TODO 3
  */
    if (rule -> key != NULL) {
        //if the key pointer of the rule is not NULL
        //frees the key pointer and
        //sets the key pointer to NULL
        free(rule -> key);
        rule -> key = NULL;
    }

    if (rule -> expansions != NULL) {
        //if the expansion pointer of the rule is not NULL
        //frees the expansion by freeing the linked list and
        //sets the expansion pointer to NULL
        free_list(rule -> expansions);
        rule -> expansions = NULL;
    }
  /*
    TODO 3
  */
	
}


List* read_grammar(char* filename) {
   
  /*
   * TODO 4A
   */ 
    List* grammar = make_list();
  /* 
   * TODO 4A
   */
  FILE* input_file = fopen(filename,"r");
  char buffer[1000];
  
  int number_of_expansions = 0;
  int buffer_index = 0;

  int number_of_rules = 0;
  for (char current = fgetc(input_file); current != EOF; current = fgetc(input_file)){
      if (current == ':'){
      
	  
      char* key = calloc(buffer_index+1,sizeof(char));
      memcpy(key,buffer,buffer_index);
      /*
       * TODO 4B
       */ 
	   Rule* rule = make_rule(key);
       add(grammar, grammar -> size, rule);
      //Construct a new Rule* and add it to grammar 
      /*
       * TODO 4B
       */ 
      buffer_index = 0;
    }
    else if (current == ',' || current == '\n') {
      char* expansion = calloc(buffer_index+1,sizeof(char));
      memcpy(expansion,buffer,buffer_index);
		
      /*
       * TODO 4C
       */
      Rule* rule = get(grammar, grammar -> size - 1);
      add(rule -> expansions, rule -> expansions -> size, expansion);
      //Get the last Rule* inserted into grammar and add expansion to it 
      /*
       *
       * TODO 4C
       */ 
      buffer_index = 0;
		 
    }
    else {
      buffer[buffer_index] = current;
      buffer_index++;
    }
  }
  fclose(input_file);

  
  /*
   * TODO 4D
   */ 
  return grammar; // replace this to return the grammar we just filled up
  /*
   * TODO 4D
   */ 
}



char* expand(char* text, List* grammar){

  /*
   * BONUS TODO
   */

    //splits the text by '#'
    //makes a new list that will store all possible expansion
	List* splitText = split(text, "#");
    List* possibleExpansion = make_list();

    for (int i = 0; i < splitText -> size; i++) {
        //loops through the processed text
        //copies the text at the current Index into a new String for memory safety
        char* textAtIndex = copy_string(get(splitText, i));

        if (i % 2 == 0) {
            //if the index is even
            //adds the text at the current index to the end of the possible expansion
            add(possibleExpansion, possibleExpansion -> size, textAtIndex);
        } else {
            //if the index is odd
            for (int j = 0; j < grammar -> size; j++) {
                //loops through the grammar
                //gets the rule, expansions, and key at the current index
                Rule* currentRule = get(grammar, j);
                List* currentList = currentRule -> expansions;
                char* keyAtIndex = currentRule -> key;

                if (strcmp(textAtIndex, keyAtIndex) == 0) {
                    //if the text at the current index in the split text is the same as the key
                    //at the index in the grammar
                    //picks a random expansion from the current expansion and recursively adds the random expansion
                    //to the possible expansions
                    char* randomExpansion = get_random(currentList);
                    add(possibleExpansion, possibleExpansion -> size, expand(randomExpansion, grammar));
                }
            }
        }
    }

    //converts the resulting linked list to a string
    //frees all lists and returns the string
    char* result = join(possibleExpansion);
    free_list(possibleExpansion);
    free_list(splitText);

    return result;
  /*
   * BONUS TODO
   */
}

//Iterates through a grammar list and prints out all of the rules
void print_grammar(List* grammar){
  
  for (int ii = 0; ii < grammar->size; ii++){
    Rule* rule = get(grammar,ii);
    for (int jj = 0; jj < rule->expansions->size; jj++){
      printf("A potential expansion of rule '%s' is '%s'\n",rule->key, (char*) get(rule->expansions,jj));
    }
  }
  
}
