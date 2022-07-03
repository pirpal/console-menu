#include <stdlib.h>
#include <stdio.h>

#include "console_menu.h"


int main (void)
{
  

  ConsoleMenu *menu = new_menu("Console Menu");
  add_node(menu, 'a', "Do this");
  add_node(menu, 'b', "Do that");
  add_node(menu, 'c', "Exit");

  print_menu(menu);

  log_menu(stdout, menu);
  log_node(stdout, menu->root);
  log_node(stdout, get_last_node(menu->root));

  free_menu(menu);
  
  return EXIT_SUCCESS;
}
