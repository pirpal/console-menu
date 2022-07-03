#include <criterion/criterion.h>

#include "../src/console_menu.h"

Test(console_menu_tests, test_get_last_node) {
 ConsoleMenu* menu = new_menu("Console Menu");  
 add_node(menu, 'a', "Do this");
 add_node(menu, 'b', "Do that");
 add_node(menu, 'c', "Exit");
 MenuNode* last = get_last_node(menu->root);
 cr_expect(last->key == 'c',
	   "Last node's key should be equal to 'c'");
 free_menu(menu);
}

Test (console_menu_tests, test_next_node) {
  ConsoleMenu* menu = new_menu("Console Menu");
  add_node(menu, 'a', "Do this");
  add_node(menu, 'b', "Do that");
  cr_expect(menu->root->next != NULL,
	    "Menu root->next should not be NULL");

  MenuNode* last = get_last_node(menu->root);
  cr_expect(last->next == NULL,
	    "Menu's last node->next should be NULL");

  free_menu(menu);
}


Test(console_menu_tests, test_key_in_menu) {
  ConsoleMenu* menu = new_menu("Console Menu");
  add_node(menu, 'a', "Do this");
  add_node(menu, 'b', "Do that");
  add_node(menu, 'c', "Exit");
  cr_assert(key_in_menu('a', menu->root) == true,
	    "Key 'a' should be found in menu");
  cr_assert(key_in_menu('?', menu->root) == false,
	    "Key '?' should not be found in menu");
  free_menu(menu);
}
