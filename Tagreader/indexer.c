#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <indexer.h>


// Create word Node
flist_t *create_file_node(char *fname, int count)
{
	// allocate memory
	flist_t *new = malloc(sizeof(flist_t));

	// store file name
	int length = strlen(fname);

	new->f_name = malloc(length + 1);

	// store file name
	strcpy(new->f_name, fname);

	new->f_name[length] = '\0';

	// no. of time word exist in this file
	new->w_count = count;

	// make structure ptr NULL
	new->f_link = NULL;

	// return address
	return new;
}


void fl_insert_last(flist_t **head, char *fname, int count)
{
	// head is null then create node
	if (*head == NULL)

		*head = create_file_node(fname, count);

	// create node and insert after last node
	else 
	{
		flist_t *ptr;

		for (ptr = *head; ptr->f_link != NULL; ptr = ptr->f_link);

		ptr->f_link = create_file_node(fname, count);
	}
}


// Print list
void fl_print_list(flist_t *head)
{
	// Error print
	if (head == NULL)

		printf("No list is present\n");

	// list is present then print the data upto last node
	else
	{
		flist_t *ptr;

		int flag = 0;

		for (ptr = head; ptr != NULL; ptr = ptr->f_link)
		{
			if (flag)
			{
				printf("%-20s\t%-10s\t", "", "");
			}

			else
			{
				flag = 1;
			}
			
			printf("%-20s\t%-5d\n", ptr->f_name, ptr->w_count);
		}	

		printf("\n");
	}
}

// Print list
void fl_print_list_search(flist_t *head)
{
	// Error print
	if (head == NULL)

		printf("No list is present\n");

	// list is present then print the data upto last node
	else
	{
		flist_t *ptr;

		for (ptr = head; ptr != NULL; ptr = ptr->f_link)
		{
			printf("\tFile_name : %s\n\tWord_count : %d\n\n", ptr->f_name, ptr->w_count);
		}	

		printf("\n");
	}
}

// Create word Node
wlist_t *create_word_node(char *wname, char *fname, int fcount, int wcount)
{
	// allocate memory
	wlist_t *new = malloc(sizeof(wlist_t));

	int length = strlen(wname);

	new->w_name = malloc(length + 1);

	// store file name
	strcpy(new->w_name, wname);

	new->w_name[length] = '\0';

	// no. of time word exist in this file
	new->f_count = fcount;

	// make structure ptr NULL
	new->w_link = NULL;

	new->f_head = create_file_node(fname, wcount);

	// return address
	return new;
}


// Insert First
void wl_insert_first(wlist_t **head, char *wname, char *fname, int fcount, int wcount)
{
	wlist_t *new = create_word_node(wname, fname, fcount, wcount);

	new->w_link = *head;

	*head = new;
}

void wl_insert_last(wlist_t **head, char *wname, char *fname, int fcount, int wcount)
{
	wlist_t *ptr;

	for (ptr = *head; ptr->w_link != NULL; ptr = ptr->w_link);

	ptr->w_link = create_word_node(wname, fname, fcount, wcount);
}

// Insert After Element
void wl_insert_after(wlist_t **head, char *e_name, char *wname, char *fname, int fcount, int wcount)
{
	wlist_t *ptr;

	// find element position
	for (ptr = *head; ptr != NULL && strcmp(ptr->w_name, e_name) != 0; ptr = ptr->w_link);

	wlist_t *new = create_word_node(wname, fname, fcount, wcount);

	new->w_link = ptr->w_link;

	ptr->w_link = new;
}


// Insert sorted
void wl_insert_sorted(wlist_t **head, char *wname, char *fname, int fcount, int wcount)
{
	// Error print
	if (*head == NULL)
	{
		*head = create_word_node(wname, fname, fcount, wcount);
	}

	// value is lessthan header data
	else if (strcmp((*head)->w_name, wname) > 0)
	{
		wl_insert_first(head, wname, fname, fcount, wcount);
	}

	// value greatethan header data
	else
	{
		wlist_t *ptr1 = *head, *ptr2 = *head;

		while (ptr2->w_link != NULL)
		{
			ptr2 = ptr2->w_link;

			// insert value in middle
			if (strcmp(ptr1->w_name, wname) < 0 && strcmp(ptr2->w_name, wname) > 0)
			{
				wl_insert_after(head, ptr1->w_name, wname, fname, fcount, wcount);

				break;
			}

			ptr1 = ptr1->w_link;
		}

		// value greaterthan the last node data
		if (ptr2->w_link == NULL && strcmp(ptr2->w_name, wname) < 0)
		{
			wl_insert_last(head, wname, fname, fcount, wcount);
		}
	}
}

void wl_print_list(wlist_t *head)
{
	// Error print
	if (head == NULL)

		printf("No list is present\n");

	// list is present then print the data upto last node
	else
	{
		wlist_t *ptr;

		printf("\n");
		for (ptr = head; ptr != NULL; ptr = ptr->w_link)
		{
			printf("%-20s\t%-10d\t", ptr->w_name, ptr->f_count);
			
			if (ptr->f_head != NULL)
			{
				fl_print_list(ptr->f_head);
			}
		}	

		printf("\n");
		printf("---------------------------------------------------------------------------\n");
	}
}

// Create hash table
wlist_t **hash_table_creation(void)
{
	int index;

	// array of pointer to single linked list
	wlist_t **a_ptr = malloc(52 * sizeof(wlist_t *));

	// make all the pointers NULL
	for (index = 0; index < 52; index++)

		a_ptr[index] = NULL;

	// return addrs
	return a_ptr;
}

// Get index
int get_index_value(char ch)
{
	// Capital letters index value 0 t0 25
	if ('A' <= ch && ch <= 'Z')

		return ch - 'A';

	// Small letters index value 26 t0 51
	else if ('a' <= ch && ch <= 'z')

		return ch - 'a' + 26;
}

// HASH create database
void hash_create_database(wlist_t **h_array, char *wname, char *fname)
{
	int index = get_index_value(wname[0]);

	wlist_t *ptr = h_array[index];

	// check the word alread present or not
	while (ptr != NULL && strcmp(ptr->w_name, wname) != 0)
	{
		ptr = ptr->w_link;		
	}

	// if present then increment the word count
	if (ptr != NULL)
	{
		flist_t *f_ptr = ptr->f_head;

		// file already exist or not
		while (f_ptr != NULL && strcmp(f_ptr->f_name, fname) != 0)
		{
			f_ptr = f_ptr->f_link;
		}

		// not present increment the file count
		if (f_ptr != NULL)
		{
			f_ptr->w_count = f_ptr->w_count + 1;
		}

		else
		{
			fl_insert_last(&ptr->f_head, fname, 1);

			ptr->f_count = ptr->f_count + 1;
		}
	}

	// insert that word
	else
	{
		wl_insert_sorted(&h_array[index], wname, fname, 1, 1);
	}
}

// Search in hash table
wlist_t *search_hash_table(wlist_t **h_array, char *wname)
{
	int index = get_index_value(wname[0]);

	wlist_t *ptr = h_array[index];

	// search word in corresponding list
	while (ptr != NULL && strcmp(ptr->w_name, wname) != 0)
	{
		ptr = ptr->w_link;		
	}

	// found return that node address
	if (ptr != NULL)
	{
		return ptr;
	}

	// print error
	else
	{
		printf("Word is not present in these files\n");
	
		return NULL;
	}
}

// print hash table
void print_hash_table(wlist_t **h_array)
{
	int index = 0;

	while (index < 52)
	{
		if (h_array[index] != NULL)
		{
			wl_print_list(h_array[index]);
		}

		index++;
	}
}

// read files
char **read_files(int *size)
{
	char buff[32];

	int index, length;

	// read no. of files
	printf("Enter the no.of files : ");
	scanf("%d", size);

	char **array = malloc(*size * sizeof(char *));

	printf("Enter the files : \n");

	// read file names
	for (index = 0; index < *size; index++)
	{
		scanf("%s", buff);

		length = strlen(buff);

		array[index] = malloc(length + 1);

		strcpy(array[index], buff);
	}

	// return file array address
	return array;
}

// File open
FILE *file_open(char *file_name, char *mode)
{
	FILE *fptr = fopen(file_name, mode);

	// error handling
	if (fptr == NULL)
	{
		printf("Error...File couldn't be opened\n");
	}

	return fptr;
}

// get word
FILE *get_word(FILE *fptr, char *word)
{
	char ch;

	int index = 0;

	// file reached the EOF return empty string
	if (feof(fptr) != 0)
	{
		word[0] = '\0';

		return fptr;
	}

	// get word from file 
	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1 ,fptr);

		if (ch < 31 || '!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
		{
			if (index != 0)
			{
				word[index] = '\0';

				break;
			}
		}	

		else if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z')
		{
			word[index++] = ch;
		}
	}

	return fptr;
}

// Create database
void create_database(wlist_t **h_array, char **files, int size)
{
	int index;
	char word[32];
	FILE *fptr;

	// run upto no.of files
	for (index = 0; index < size; index++)
	{
		// open file
		if ((fptr = file_open(files[index], "r")) == NULL)

			return;			

		// read words upto file reaches EOF
		while (1)
		{
			fptr = get_word(fptr, word);

			if (strlen(word) == 0)
			{
				break;
			}

			if ('A' <= word[0] && word[0] <= 'Z' || 'a' <= word[0] && word[0] <= 'z')

				hash_create_database(h_array, word, files[index]);
		}

		// close file
		fclose(fptr);	
	}
}

// write file list to the backupfile
FILE  *fl_write_list(flist_t *head, FILE *fptr)
{
	flist_t *ptr;
	char n_line = '\n', buff[10];

	for (ptr = head; ptr != NULL; ptr = ptr->f_link)
	{
		fwrite(ptr->f_name, strlen(ptr->f_name), 1, fptr);
		fwrite(",", 1, 1, fptr);
		sprintf(buff, "%d", ptr->w_count);
		fwrite(buff, strlen(buff), 1, fptr);
		fwrite(",", 1, 1, fptr);
	}

	fseek(fptr, -1, SEEK_CUR);

	fwrite(&n_line, 1, 1, fptr);

	return fptr;
}

// write word list to the backup file
FILE *wl_write_list(wlist_t *head, FILE *fptr)
{
	wlist_t *ptr;
	char buff[10];

	for (ptr = head; ptr != NULL; ptr = ptr->w_link)
	{
		fwrite(ptr->w_name, strlen(ptr->w_name), 1, fptr);
		fwrite(",", 1, 1, fptr);
		sprintf(buff, "%d", ptr->f_count);
		fwrite(buff, strlen(buff), 1, fptr);
		fwrite(",", 1, 1, fptr);

		if (ptr->f_head != NULL)
		{
			fptr = fl_write_list(ptr->f_head, fptr);
		}
	}

	return fptr;
}

// write hash table content to backupfile
FILE *write_hash_table(wlist_t **h_array, FILE *fptr)
{
	int index = 0;

	while (index < 52)
	{
		if (h_array[index] != NULL)
		{
			fptr = wl_write_list(h_array[index], fptr);
		}

		index++;
	}

	return fptr;
}

// Save database
void save_database(wlist_t **h_array, char **files, int size)
{
	// open backupfile 
	FILE *fptr = file_open("backup_file.csv", "w");
	int index;
	char n_line = '\n', buff[10];

	if (fptr == NULL)

		return;

	sprintf(buff, "%d", size);

	// write no.of files and file names
	fwrite(buff, strlen(buff), 1, fptr);
	fwrite(",", 1, 1, fptr);

	for (index = 0; index < size; index++)
	{
		fwrite(files[index], strlen(files[index]), 1, fptr);
		fwrite(",", 1, 1, fptr);
	}

	fseek(fptr,-1 ,SEEK_CUR);
	fwrite(&n_line, 1, 1, fptr);

	// write hash table contents
	fptr = write_hash_table(h_array, fptr);

	fclose(fptr);
}


// Read word for backup
FILE *read_word_backup(char *word, FILE *fptr)
{
	int index = 0;
	char ch;

	if (feof(fptr) != 0)
	{
		word[0] = '\0';

		return fptr;
	}

	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1, fptr);

		if (ch < 31 || ch == ',' || ch == '\n')
		{
			if (index != 0)
			{
				word[index] = '\0';

				break;
			}
		}

		word[index++] = ch;
	}

	return fptr;
}


// read Backupfile and create database
void read_backup_database(wlist_t **h_array)
{
	char word[32] = "hai", fcount[10], file[32], wcount[10], ch;
	int fct, wct, index, jdx;
	wlist_t *ptr;

	// open backupfile
	FILE *fptr = file_open("backup_file.csv", "r");
	if (fptr == NULL)

		return;

	fread(&ch, 1, 1, fptr);

	while (ch != '\n')

		fread(&ch, 1, 1, fptr);

	// read word, file count and file and word count and store it in the hash table
	while (1)
	{
		if (strlen(word) == 0)

			break;

		fptr = read_word_backup(word, fptr);
		fptr = read_word_backup(fcount, fptr);
		sscanf(fcount, "%d", &fct);

		fptr = read_word_backup(file, fptr);
		fptr = read_word_backup(wcount, fptr);
		sscanf(wcount, "%d", &wct);

		jdx = get_index_value(word[0]);

		if (!(word[0] >= 'A' && word[0] <= 'Z' || word[0] >= 'a' && word[0] <= 'z'))

			continue;

		wl_insert_sorted(&h_array[jdx], word, file, fct, wct);

		ptr = h_array[jdx];

		while (ptr != NULL && strcmp(ptr->w_name, word) != 0)

			ptr = ptr->w_link;

		for (index = 0; index < fct - 1; index++)
		{
			fptr = read_word_backup(file, fptr);
			fptr = read_word_backup(wcount, fptr);
			sscanf(wcount, "%d", &wct);

			fl_insert_last(&ptr->f_head, file, wct);
		}		
	}
}

// read inputs for delete
char **read_inputs_delete(wlist_t **h_array, char *word, wlist_t **wnode)
{
	int index, f_option;

	// search word
	*wnode = search_hash_table(h_array, word);

	wlist_t *ptr = *wnode; 
		
	// error handling
	if (ptr == NULL)
	{
		printf("Invalid word\n");

		return NULL;
	}

	flist_t *file = ptr->f_head;

	char *addrs[ptr->f_count], **files;

	// print those files containg this word
	printf("1. All\n");

	for (index = 0; index < ptr->f_count; index++)
	{
		addrs[index] = file->f_name;

		printf("%d. %s\n", index + 2, addrs[index]);

		file = file->f_link;
	}

	// choose the file
	printf("Select file : ");
	scanf("%d", &f_option);

	// copy the files to array
	if (f_option == 1)
	{
		files = malloc((ptr->f_count + 1) * sizeof (char *));

		for (index = 0; index < ptr->f_count; index++)
		{
			files[index] = addrs[index];
		}

		files[ptr->f_count] = NULL;
	}
	
	else if (f_option > 0 && f_option < ptr->f_count + 2)
	{
		files = malloc(2 * sizeof (char *));
		
		files[0] = addrs[f_option - 2];
		files[1] = NULL;
	}

	else
	{
		printf("Invalid option\n");

		files = malloc(1 * sizeof (char *));

		files[0] = NULL;
	}

	return files;
}

// Delete Element
void fl_delete_element(flist_t **head, char *file)
{
	flist_t *ptr, *prev = *head;

	// find the element position in list
	for (ptr = *head, prev = *head; ptr != NULL && strcmp(file, ptr->f_name) != 0; prev = ptr, ptr = ptr->f_link);

	if (ptr != *head)
	{
		prev->f_link = ptr->f_link;
	}

	// element present in header then delete head and make next node as head
	else
	{
		*head = (*head)->f_link;
	}

	free(ptr);
}

// Delete Element
void wl_delete_element(wlist_t **head, char *word)
{
	wlist_t *ptr, *prev = *head;

	// find the element position in list
	for (ptr = *head, prev = *head; ptr != NULL && strcmp(word, ptr->w_name) != 0; prev = ptr, ptr = ptr->w_link);

	if (ptr != *head)
	{
		prev->w_link = ptr->w_link;
	}

	// element present in header then delete head and make next node as head
	else
	{
		*head = (*head)->w_link;
	}

	free(ptr);
}

// delete word from file
void delete_word_from_file(char *word, char *file)
{
	int length = strlen(word), r_byte = 0, sflag = 1, flag = 0, dflag = 0, index;
	char buff[100], ch;

	// open src file
	FILE *fptr = file_open(file, "r");
	if (fptr == NULL)
		return;
	
	// open temp file
	FILE *temp = file_open("temp.txt", "w");
	if (temp == NULL)
		return;

	// read word form file and copy to the temp file when deleteword arrives ignore the word ang continue copying upto EOF
	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1, fptr);

		if (flag || sflag || dflag || '!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
		{
			sflag = 0;
			dflag = 0;

			flag = 1;
		}

		else

			flag = 0;

		if (flag && ch == word[0])
		{
			index = 0;
			buff[index++] = ch;

			while (1)
			{
				fread(&ch, 1, 1, fptr);

				if ('!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
				{
					dflag = 1;

					buff[index] = '\0';

					break;
				}
				
				buff[index++] = ch;
			}

			if (strcmp(word, buff) == 0)
			{
				fwrite(&ch, 1, 1, temp);

				continue;
			}
			
			else
			{
				fwrite(buff, strlen(buff), 1, temp);

				fwrite(&ch, 1, 1, temp);
			}
		}

		else

			fwrite(&ch, 1, 1, temp);
	}

	fclose(fptr);
	fclose(temp);

	// copy temp file content to the src file
	fptr = file_open(file, "w");
	if (fptr == NULL)
		return;
	
	temp = file_open("temp.txt", "r");
	if (temp == NULL)
		return;

	while (feof(temp) == 0)
	{
		r_byte = fread(buff, 1, 100, temp);
		buff[r_byte] = '\0';
		fwrite(buff, 1, r_byte, fptr);
	}
}

// Delete word
void delete_word(wlist_t **h_array, char *word)
{
	int f_option, index;
	wlist_t *wnode;

	// read inputs
	char **files = read_inputs_delete(h_array, word, &wnode);
	int jdx = get_index_value(word[0]);

	if (files == NULL)

		return;

	for (index = 0; files[index] != NULL; index++)
	{
		// delete word from file 
		delete_word_from_file(word, files[index]);

		// delete file node
		fl_delete_element(&wnode->f_head, files[index]);

		wnode->f_count = wnode->f_count - 1;
	}

	// delete word node
	if (wnode->f_head == NULL)
	
		wl_delete_element(&h_array[jdx], word);
}

// Read inputs fron edit
char **read_inputs_edit(wlist_t **h_array, char *word, char *new_word, wlist_t **wnode)
{
	int index, f_option;

	// search word
	*wnode = search_hash_table(h_array, word);

	wlist_t *ptr = *wnode; 
		
	// error handling
	if (ptr == NULL)
	{
		printf("Invalid word\n");

		return NULL;
	}

	// read new word
	printf("Enter the new word : ");
	scanf("%s", new_word);

	flist_t *file = ptr->f_head;

	char *addrs[ptr->f_count], **files;

	// print corresponding files
	printf("1. All\n");

	for (index = 0; index < ptr->f_count; index++)
	{
		addrs[index] = file->f_name;

		printf("%d. %s\n", index + 2, addrs[index]);

		file = file->f_link;
	}

	// select file
	printf("Select file : ");
	scanf("%d", &f_option);

	// copy the file names to array and return
	if (f_option == 1)
	{
		files = malloc((ptr->f_count + 1) * sizeof (char *));

		for (index = 0; index < ptr->f_count; index++)
		{
			files[index] = addrs[index];
		}

		files[ptr->f_count] = NULL;
	}
	
	else if (f_option > 0 && f_option < ptr->f_count + 2)
	{
		files = malloc(2 * sizeof (char *));
		
		files[0] = addrs[f_option - 2];
		files[1] = NULL;
	}

	else
	{
		printf("Invalid option\n");

		files = malloc(1 * sizeof (char *));

		files[0] = NULL;
	}

	return files;
}

// Edit word from file
void edit_word_from_file(char *word, char *new_word, char *file)
{
	int length = strlen(word), r_byte = 0, flag = 0, sflag = 1, dflag = 0, index;
	char buff[100], ch;

	// open src file
	FILE *fptr = file_open(file, "r");
	if (fptr == NULL)
		return;
	
	// open temp file
	FILE *temp = file_open("temp.txt", "w");
	if (temp == NULL)
		return;

	// read word form file and copy to the temp file when editword arrives replace that word by new word and continue copying upto EOF
	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1, fptr);

		if (flag || sflag || dflag || '!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
		{
			sflag = 0;
			dflag = 0;

			flag = 1;
		}

		else

			flag = 0;

		if (flag && ch == word[0])
		{
			index = 0;
			buff[index++] = ch;

			while (1)
			{
				fread(&ch, 1, 1, fptr);

				if ('!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
				{
					dflag = 1;

					buff[index] = '\0';

					break;
				}
				
				buff[index++] = ch;
			}

			if (strcmp(word, buff) == 0)
			{
				fwrite(new_word, strlen(new_word), 1, temp);
				fwrite(&ch, 1, 1, temp);

				continue;
			}
			
			else
			{
				fwrite(buff, strlen(buff), 1, temp);

				fwrite(&ch, 1, 1, temp);
			}
		}

		else

			fwrite(&ch, 1, 1, temp);

	}

	fclose(fptr);
	fclose(temp);

	// copy temp file content to src file
	fptr = file_open(file, "w");
	if (fptr == NULL)
		return;
	
	temp = file_open("temp.txt", "r");
	if (temp == NULL)
		return;

	while (feof(temp) == 0)
	{
		r_byte = fread(buff, 1, 100, temp);
		buff[r_byte] = '\0';
		fwrite(buff, 1, r_byte, fptr);
	}
}

// Edit word
void edit_word(wlist_t **h_array, char *word)
{
	int f_option, index;
	char new_word[32];
	wlist_t *wnode;

	// read edit inputs
	char **files = read_inputs_edit(h_array, word, new_word, &wnode);
	int jdx = get_index_value(word[0]);

	if (files == NULL)

		return;

	// edit word from file
	for (index = 0; files[index] != NULL; index++)
		
		edit_word_from_file(word, new_word, files[index]);
}

// get word from backupfile
FILE *get_word_backup(FILE *fptr, char *array)
{
	char ch;
	int index = 0;

	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1, fptr);

		if (ch == ',' || ch == '\n')
		{
			array[index] = '\0';

			break;
		}

		array[index++] = ch;
	}

	return fptr;
}


int check_presence_of_backup(char **array, int size)
{
	int n_files, i_index, j_index, flag = 0;
	char buff[32];

	// open backupfile
	FILE *fptr = fopen("backup_file.csv", "r");

	// file is present
	if (fptr != NULL)
	{
		// get no.of files
		fptr = get_word_backup(fptr, buff);
		sscanf(buff, "%d", &n_files);

		// no. of file is matches with input files count
		if (size == n_files)
		{
			// get all the files names and matches then return 1
			for (i_index = 0; i_index < size; i_index++)
			{
				fptr = get_word_backup(fptr, buff);
				
				for (j_index = 0; j_index < size; j_index++)
				{
					if (strcmp(buff, array[j_index]) == 0)
					{
						flag = 1;

						break;
					}

					else

						flag = 0;
				}

				if (flag == 0)

					break;
			}

			fclose(fptr);
	
			if (flag)

				return 1;

			else

				return 0;
		}
	}

	// error return 
	return 0;
}
		
