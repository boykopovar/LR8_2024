#include"task_2.h"
#include"../../global_utils.h"

void add_tickets(ticket*& tickets);
int print_tickets(const ticket* tickets, const std::string& name_filter= "");
void search_elements_by_group(const ticket* tickets);
void edit_element(ticket* tickets);
void sort_by_count(ticket* tickets);