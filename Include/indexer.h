#ifndef INDEXER_H
#define INDEXER_H

// flie list structure
typedef struct f_node
{
	char *f_name;

	int w_count;

	struct f_node *f_link;
} flist_t;

// wordlist structure
typedef struct w_node
{
	char *w_name;

	int f_count;

	struct f_node *f_head;
	
	struct w_node *w_link;
} wlist_t;

// print file list for search
void fl_print_list_search(flist_t *head);

// read files
char **read_files(int *size);
// create hash table
wlist_t **hash_table_creation(void);

// create database
void create_database(wlist_t **h_array, char **files, int size);
// search in hash table
wlist_t *search_hash_table(wlist_t **h_array, char *wname);
// edit word
void edit_word(wlist_t **h_array, char *word);
// delete word
void delete_word(wlist_t **h_array, char *word);

// check presence of backup
int check_presence_of_backup(char **array, int size);
// save database
void save_database(wlist_t **h_array, char **files, int size);
// read backup and create database
void read_backup_database(wlist_t **h_array);

// print hash table
void print_hash_table(wlist_t **h_array);

#endif
