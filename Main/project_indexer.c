#include <stdio.h>
#include <indexer.h>

/*********************************************** TEXT INDEXER ******************************************/

int main()
{
	int option, size;
	wlist_t *wnode;
	char ch, word[32];

	// read input files
	char **files = read_files(&size);

	// create hash table
	wlist_t **h_array = hash_table_creation();
	
	// check presence of backup file and input files
	int flag = check_presence_of_backup(files, size);

	do
	{
		// print options to user
		printf("\nOPTIONS : \n\t1. Create database\n\t2. Search word\n\t3. Edit word\n\t4. Delete word\n\t5. Display\n\t6. Exit\n\n");

		// read option
		printf("\nEnter the option : ");
		scanf("%d", &option);

		// select case
		switch (option)
		{
			// Create database
			case 1:

				// flag is set create database from backupfile
				if (flag)
				{
					printf("\nYou have a backup_file for this set of files\n");
					read_backup_database(h_array);
				}

				// create database 
				else
				
					create_database(h_array, files, size);
				
				break;

			// Search word
			case 2:

				// read word
				printf("\nEnter the word to be searched : ");
				scanf("%s", word);

				wnode = search_hash_table(h_array, word);

				if (wnode != NULL)
				{
					printf("\nWord : %s\nFile count : %d\n\n", wnode->w_name, wnode->f_count);

					fl_print_list_search(wnode->f_head);
				}

				break;

			// Edit word
			case 3:

				// read word
				printf("\nEnter the word to be editted : ");
				scanf("%s", word);

				edit_word(h_array, word);

				break;

			// Delete word
			case 4:

				// read word
				printf("\nEnter the word to be deleted : ");
				scanf("%s", word);

				delete_word(h_array, word);

				break;

			// Display
			case 5:

				// print heading
				printf("***************************************************************************\n");
				printf("%-20s\t%-10s\t%-20s\t%-5s\n", "Word", "No_Files", "File_Name", "Word_count");
				printf("***************************************************************************\n");

				// print hash table
				print_hash_table(h_array);

				break;

			// Exit
			case 6:

				// Save the database 
				save_database(h_array, files, size);

				return 0;

				break;

			default:

				printf("\nInvalid option\n");
		}

		// to continue the process
		printf("\nDo you want to continue : ");
		scanf("\n%c", &ch);

	// ch is y/Y continue
	} while (ch == 'y' || ch == 'Y');

	return 0;
}
