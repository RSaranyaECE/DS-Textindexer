# DS-Textindexer

Before Running this program in ur system:

In command line run this:
	
	export LD_LIBRARY_PATH = "/home/.../Library"

	(* in your system where your r having this Library folder give that path)

Objective:

	To implement text indexer by using hash table  and sorted insert concept to meet the time complexity O(1).
	This program is intended to perform following operation
		Creating the database
		Searching word
		Editing word
		Deleting word
		Saving the  database

Algorithm:

Create database:

	STEP 1: Read file names
	STEP 2: Open files
	STEP 3: Read words from files
	STEP 4: Store the words in sorted order to Hash Table
	STEP 5: And also store file count file names and word count
	STEP 5: Close the opened files

Search Word:

	STEP 1: Read a word from user
	STEP 2: Search the word in Hash table
	STEP 3: Print the details about words
	STEP 4: Print error if word not present in hash table

Edit Word:

	STEP 1: Read a word to be editted and new word for replacement
	STEP 2: Read a files to be editted
	STEP 3: Open the files
	STEP 4: Replace the selected words by new word
	STEP 5: Close all the opened files

Delete Word:

	STEP 1: Read a word to be deleted
	STEP 2: Read a files 
	STEP 3: Open the files
	STEP 4: Delete the slected words
	STEP 5: Close all the opened files

Save Database:

	STEP 1: Open backup file
	STEP 2: Write hash table content in backup file 
	STEP 3: Close the file

Advantages:

	1. n no.of files can be accessed
	2. Database maintained if you are giving same file no need to read that file again

Future implementation:

	1. Database created for one file, we are giving the same file after editting some content as input file then this will fail

	so we have to do something to identify editted files

