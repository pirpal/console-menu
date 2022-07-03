#include "console_menu.h"
#include <stdlib.h>
#include <string.h>


//--------------------------------------------------------------
// § Static functions
//--------------------------------------------------------------
static bool is_node_key(const char k, const MenuNode* node) {
  return (k == node->key);
}


static void err_exit(const char *msg) {
  fprintf(stderr, "[ERR] %s\n", msg);
  exit(EXIT_FAILURE);
}

//--------------------------------------------------------------
// § Functions
//--------------------------------------------------------------
ConsoleMenu *new_menu(const char *title) {
  ConsoleMenu *menu = malloc(sizeof(ConsoleMenu));
  if (menu == NULL)
    err_exit("failed to malloc ConsoleMenu*");
  strcpy(menu->title, title);
  menu->root = NULL;
  return menu;
}

MenuNode *new_node(const char key, const char *txt) {
  MenuNode *node = malloc(sizeof(MenuNode));
  if (node == NULL)
    err_exit("failed to malloc *MenuNode");
  node->key = key;
  strcpy(node->txt, txt);
  node->next = NULL;
  return node;
}

MenuNode *get_last_node(MenuNode *root) {
  /* RECURSIVE function */
  if (root->next == NULL)
    return root;
  return get_last_node(root->next);
}

void add_node(ConsoleMenu *menu, const char key, const char *txt) {
  // check for keys unicity
  MenuNode *node = new_node(key, txt);
  if (menu->root == NULL) {
    menu->root = node;
    return;
  }
  MenuNode *last = get_last_node(menu->root);
  last->next = node;
}

void print_nodes(const MenuNode *root) {
  /* RECURSIVE function */
  if (root == NULL)
    return;
  printf("\t(%c) %s\n", root->key, root->txt);
  print_nodes(root->next);
}

void print_menu(const ConsoleMenu *menu) {
  printf("%s\n", menu->title);
  print_nodes(menu->root);
}

void free_nodes(MenuNode *root) {
  /* RECURSIVE function */
  if (root->next == NULL) {
    free(root);
    return;
  }
  MenuNode *temp = root->next;
  free(root);
  free_nodes(temp);
}

void free_menu(ConsoleMenu *menu) {
  free_nodes(menu->root);
  free(menu);
}

void log_menu(FILE* stream, const ConsoleMenu* menu) {
  fprintf(stream, "<ConsoleMenu %p>\n", (void*) menu);
}

void log_node(FILE* stream, const MenuNode* node) {
  fprintf(stream,
	  "<MenuNode %p> key: '%c', txt: '%s', ",
	  (void*) node,
	  node->key,
	  node->txt);
  if (node->next) {
    fprintf(stream, "next: <MenuNode %p>\n", (void*) node->next);
  } else {
    fprintf(stream, "next: NULL\n");
  }
}


bool key_in_menu(const char k, const MenuNode *root) {
  if (is_node_key(k, root)) {
    return true;
  } else {
    if (root->next == NULL) {
      return false;
    } else {
      return key_in_menu(k, root->next);
    }
  }
}
