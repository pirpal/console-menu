#ifndef CONSOLE_MENU_H_
#define CONSOLE_MENU_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


/*
  Objectives:
- create a menu as a Tree, with nodes
- display the menu and prompt user for choice
*/

//--------------------------------------------------------------
#define MENU_MAXCHAR 128

//--------------------------------------------------------------
typedef struct MenuNode {
  /*
    TXT:     text to display for that node
    KEY: character (as user choice) for this node
    NEXT:    pointer to next node in the menu
   */
  char txt[MENU_MAXCHAR];
  char key;
  struct MenuNode *next;
} MenuNode;

//--------------------------------------------------------------
typedef struct ConsoleMenu {
  /*
    TITLE: text to display for that menu (header)
    ROOT: pointer to the first node of the menu
   */
  char title[MENU_MAXCHAR];
  MenuNode *root;
} ConsoleMenu;

//--------------------------------------------------------------
MenuNode *new_node(const char key, const char *txt);

ConsoleMenu *new_menu(const char *title);

MenuNode *get_last_node(MenuNode *root);

void add_node(ConsoleMenu *menu, const char key, const char *txt);

void print_nodes(const MenuNode *node);
  
void print_menu(const ConsoleMenu *menu);

void free_menu(ConsoleMenu *menu);

void log_menu(FILE *stream, const ConsoleMenu *menu);

void log_node(FILE *stream, const MenuNode *node);

bool key_in_menu(const char k, const MenuNode *root);



#endif // CONSOLE_MENU_H_
