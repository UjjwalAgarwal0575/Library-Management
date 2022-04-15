#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

// Define the global variable of libsys
struct LibsysInfo repo_handle;

//--------------------------------create()---------------------------------
int libsys_create( char *repo_name1,char *repo_name2,char *repo_name3)
{
	char book_ndx_name[30];
	char book_name_copy[30];

	strcpy(book_ndx_name,repo_name1);	
	strcpy(book_name_copy,repo_name1);	

	char student_ndx_name[30];

	strcpy(student_ndx_name,repo_name2);	

	strcat(book_name_copy,".dat");
	FILE *book_fp=fopen(book_name_copy,"wb");

	FILE *student_fp=fopen(repo_name2,"wb");

	FILE *issue_fp=fopen(repo_name3,"wb");

	if(student_fp==NULL || book_fp==NULL || issue_fp==NULL)
		return LIB_FILE_ERROR;

	fclose(book_fp);
	fclose(student_fp);
	fclose(issue_fp);

	strcat(book_ndx_name,".ndx");
	FILE *book_ndx_fp=fopen(book_ndx_name,"wb");
	int t=0;
	int init_idx=fwrite(&t,sizeof(int),1,book_ndx_fp);
	if(init_idx!=1)
		return LIB_NDX_SAVE_FAILED;
	fclose(book_ndx_fp);

	strcat(student_ndx_name,".ndx");
	FILE *student_ndx_fp=fopen(student_ndx_name,"wb");
	t=0;
	init_idx=fwrite(&t,sizeof(int),1,student_ndx_fp);
	if(init_idx!=1)
		return LIB_NDX_SAVE_FAILED;
	fclose(student_ndx_fp);

	return LIB_SUCCESS;
}

    	// create booksys file pointer to open a file in 'wb' mode
 	// handle file pointer error if value is NULL return appropriate error code referring to the error codes 
    	// close file pointer
    	 

    	// create studsys file pointer to open a file in 'wb' mode
 	// handle file pointer error if value is NULL return appropriate error code referring to the error codes 
    	// close file pointer
    	


    	// create issuesys file pointer to open a file in 'wb' mode
 	// handle file pointer error if value is NULL return appropriate error code referring to the error codes 
// close file pointer

// Open the index file in "wb" mode
// Initialize index file by store "0" to indicate there are zero entries in index file

    	// return success 



//--------------------------------open()---------------------------------
int libsys_open(char *book_name,char *stud_name,char *issue_name)
{
	char book_index_name[30];
	strcpy(book_index_name,book_name);

	char student_index_name[30];
	strcpy(student_index_name,stud_name);

	if(booksys_open(book_name)==0 && studsys_open(stud_name)==0 && issuesys_open(issue_name)==0)
	{
		strcat(book_index_name,".ndx");
		strcat(student_index_name,".ndx");
		FILE *book_ndx_fp=fopen(book_index_name,"rb+");
		repo_handle.booksys_ndx_fp=book_ndx_fp;
		fread(&repo_handle.book_index_count,sizeof(int),1,book_ndx_fp);
   		fread(repo_handle.book_index_entries,sizeof(struct LIB_NdxInfo),repo_handle.book_index_count,book_ndx_fp);
		fclose(book_ndx_fp);
		FILE *student_ndx_fp=fopen(student_index_name,"rb+");
		repo_handle.studsys_ndx_fp=student_ndx_fp;
		fread(&repo_handle.student_index_count,sizeof(int),1,student_ndx_fp);
   		fread(repo_handle.student_index_entries,sizeof(struct LIB_NdxInfo),repo_handle.student_index_count,student_ndx_fp);
		fclose(student_ndx_fp);

		return LIB_SUCCESS;
	}
	else
	{
		return LIB_REPO_NOT_OPEN;
	}

}

	//call booksys_open()
	//call studsys_open()
	//call issuesys_open()

	// Open the index file in rb+ mode
	// Read number of index entries from index file
	// Load book_index_entries array by reading index entries from the index 	file
	// Close only the index file

	//check status of above functions
	// if all of them return success then return SUCCESS else return ERROR


int booksys_open( char *repo_name )
{

	char repo[30];
	strcpy(repo,repo_name);
	strcat(repo,".dat");
	FILE *book_fp=fopen(repo,"rb+");
	if(book_fp==NULL)
		return LIB_FILE_ERROR;
	repo_handle.booksys_data_fp=book_fp;
	// strcpy(repo_handle.booksys_name,repo_name);
	repo_handle.book_repo_status=LIB_REPO_OPEN;
	return BOOK_SUCCESS;

}

    	//1. assign repo handle a file pointer by opening file in 'rb+' mode
    	//2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
	//3. assign values (repo_name) to booksys_repo_handle
      	//4. assign value to repo_handle.book_repo_status=LIB_REPO_OPEN;
	//5. return booksys_success 


int issuesys_open( char *repo_name )
{
	
	FILE *issue_fp=fopen(repo_name,"rb+");
	if(issue_fp==NULL)
		return LIB_FILE_ERROR;
	repo_handle.issuesys_data_fp=issue_fp;
	strcpy(repo_handle.issuesys_name,repo_name);
	repo_handle.issue_repo_status=LIB_REPO_OPEN;
	return BOOK_SUCCESS;
}

    	//1. assign repo handle a file pointer by opening file in 'rb+' mode
    	//2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
	//3. assign values (repo_name) to issuesys_repo_handle
      	//4. assign value to repo_handle.issue_repo_status=LIB_REPO_OPEN;
	//5. return issuesys_success 



int studsys_open( char *repo_name )
{
	
	FILE *student_fp=fopen(repo_name,"rb+");
	if(student_fp==NULL)
		return LIB_FILE_ERROR;
	repo_handle.studsys_data_fp=student_fp;
	strcpy(repo_handle.studsys_name,repo_name);
	repo_handle.stud_repo_status=LIB_REPO_OPEN;
	return BOOK_SUCCESS;
}
    	//1. assign repo handle a file pointer by opening file in 'rb+' mode
    	//2. handle file pointer error if value is NULL return appropriate error code referring to the error codes 
	//3. assign values (repo_name) to studsys_repo_handle
      	//4. assign value to repo_handle.stud_repo_status=LIB_REPO_OPEN;
	//5. return studsys_success 


	

//------------------------------book:NO change ----------------------------

int get_book_by_isbn( int key, struct Book *rec )
{
	if( repo_handle.book_repo_status != LIB_REPO_OPEN ) {

		return LIB_REPO_NOT_OPEN;
	}

	for( int i = 0; i < repo_handle.book_index_count; i++ ) 
	{
		if( repo_handle.book_index_entries[i].key == key)
		{
			if(repo_handle.book_index_entries[i].flag==RECORD_PRESENT)
			{
				fseek( repo_handle.booksys_data_fp, repo_handle.book_index_entries[i].offset, SEEK_SET );
				fread( &key, sizeof( key ), 1, repo_handle.booksys_data_fp );
				fread( rec, sizeof( struct Book), 1, repo_handle.booksys_data_fp );
				// printf("Book Details:-\nISBN:%d\nTitle:%s\nAuthor:%s\nPrice:%.2f\n",rec->isbn,rec->title,rec->author,rec->price);
				
				// printf("Book is not issued\n");
				return LIB_SUCCESS;
			} 
			return LIB_REC_NOT_FOUND;
		}
	}
	return LIB_REC_NOT_FOUND;
}
// get_rec_by_key
//check repo status
// Search for index entry in book_index_entries array
//-----use flag to read valid entries
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key

int details_book_issued(int key)
{
	fseek(repo_handle.issuesys_data_fp,0,SEEK_SET);
	while(1)
	{
		if(feof(repo_handle.issuesys_data_fp))
			break;
		struct Issue iss;
		fread(&iss,sizeof(struct Issue),1,repo_handle.issuesys_data_fp);
		if(iss.isbn==key)
		{
			struct Student student;
			get_student_by_rollno(iss.rollno,&student);
			printf("\nBook is issued to :\nRollNo:%d\nName:%s\nAddress:%s\nCGPA:%.2f\n",student.rollno,student.name,student.address,student.cgpa);
			return LIB_SUCCESS;
		}

	}
	int Book_not_issued=1;
	printf("\nBook is not issued\n");
	return Book_not_issued;
}
int put_book_by_isbn(int key, struct Book *rec)
{
	if(repo_handle.book_repo_status!=LIB_REPO_OPEN)
      return LIB_REPO_NOT_OPEN;
  

	for(int i=0;i<repo_handle.book_index_count;i++)
	{
		
		
		if(repo_handle.book_index_entries[i].key==key)
		{
		if(repo_handle.book_index_entries[i].flag==RECORD_DELETED)
		{
			repo_handle.book_index_entries[i].flag=RECORD_PRESENT;
			// repo_handle.book_index_entries[i].offset=ftell(repo_handle.libsys_ndx_fp);
			return LIB_SUCCESS;
		}
		else
			return LIB_ADD_FAILED;
		
		}
	
	}

	fseek(repo_handle.booksys_data_fp,0,SEEK_END);
	int offset=ftell(repo_handle.booksys_data_fp);

	repo_handle.book_index_entries[repo_handle.book_index_count].key=key;
	repo_handle.book_index_entries[repo_handle.book_index_count].offset=offset;
	repo_handle.book_index_entries[repo_handle.book_index_count].flag=RECORD_PRESENT;
	strcpy(repo_handle.book_index_entries[repo_handle.book_index_count].second_key,rec->title);
	repo_handle.book_index_count++;
	// printf("%d\n",repo_handle.book_index_count);

	int put_key=fwrite(&key,sizeof(int),1,repo_handle.booksys_data_fp);
	int put_record=fwrite(rec,sizeof(struct Book),1,repo_handle.booksys_data_fp);


	if(put_key != 1 || put_record!=1)
		return LIB_ADD_FAILED;
	return LIB_SUCCESS;
}
//-----check index file for key
//-----if key already present check for flag [flag=1 : entry is valid]
//-----if key is present but flag is 0 then just add entry at same index i.e update only offset and update flag; return status
//-----if key is present but flag is 1 return failure as data is already present
//-----if key is not prsent then proceed with following steps:

// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
// return status




int delete_book_by_isbn( int key )
{
	if(repo_handle.book_repo_status!=LIB_REPO_OPEN)
    return LIB_REPO_NOT_OPEN;
	for(int i=0;i<repo_handle.book_index_count;i++)
	{
		if(repo_handle.book_index_entries[i].key==key)
		{
			
		
			if(repo_handle.book_index_entries[i].flag==RECORD_PRESENT)
			{
				fseek(repo_handle.issuesys_data_fp,0,SEEK_SET);
				while(1)
				{
					if(feof(repo_handle.issuesys_data_fp))
						break;
					struct Issue iss;
					fread(&iss,sizeof(struct Issue),1,repo_handle.issuesys_data_fp);
					if(iss.isbn==key)
						return LIB_REC_NOT_FOUND;
				}
				repo_handle.book_index_entries[i].flag=RECORD_DELETED;
				repo_handle.book_index_count--;
				return LIB_SUCCESS;
			}
			return LIB_REC_NOT_FOUND;
		}
	}
	return LIB_REC_NOT_FOUND;
}

//-----delete_rec_by_key
//-----check repo status
//-----Search for index entry in book_index_entries array
//-----if key matches and flag is 1 then reset flag
//-----if key matches but flag is already reset return status
//-----if key doesn't match then return status



//-----------------------------student: additional code---------------------------
int put_student_by_rollno( int rollno_to_write, struct Student *rec )
{
	if(repo_handle.stud_repo_status!=LIB_REPO_OPEN)
      return LIB_REPO_NOT_OPEN;
  

	for(int i=0;i<repo_handle.student_index_count;i++)
	{
		
		
		if(repo_handle.student_index_entries[i].key==rollno_to_write)
		{
			if(repo_handle.student_index_entries[i].flag==RECORD_DELETED)
			{
				repo_handle.student_index_entries[i].flag=RECORD_PRESENT;
				// repo_handle.student_index_entries[i].offset=ftell(repo_handle.libsys_ndx_fp);
				return LIB_SUCCESS;
			}
			else
				return LIB_ADD_FAILED;
		}
	
	}

	fseek(repo_handle.studsys_data_fp,0,SEEK_END);
	int offset=ftell(repo_handle.studsys_data_fp);

	repo_handle.student_index_entries[repo_handle.student_index_count].key=rollno_to_write;
	repo_handle.student_index_entries[repo_handle.student_index_count].offset=offset;
	repo_handle.student_index_entries[repo_handle.student_index_count].flag=RECORD_PRESENT;
	strcpy(repo_handle.student_index_entries[repo_handle.student_index_count].second_key,rec->name);
	repo_handle.student_index_count++;
	// printf("%d\n",repo_handle.student_index_count);

	int put_key=fwrite(&rollno_to_write,sizeof(int),1,repo_handle.studsys_data_fp);
	int put_record=fwrite(rec,sizeof(struct Student),1,repo_handle.studsys_data_fp);


	if(put_key != 1 || put_record!=1)
		return LIB_ADD_FAILED;
	return LIB_SUCCESS;
}


	//1. check if repo status is closed then return return appropriate error code referring to the error codes 
	//2. else continue with following action sequence
	//3. set the file pointer to end
	//4. write rollno_to_write 
	//5. write Student record
	//6. if both actions are successful then return studsys_success 
	//7. else return studsys_add_failed



int get_student_by_rollno( int rollno_to_read, struct Student *rec )
{
	if( repo_handle.stud_repo_status != LIB_REPO_OPEN ) {

		return LIB_REPO_NOT_OPEN;
	}

	for( int i = 0; i < repo_handle.student_index_count; i++ ) 
	{
		if( repo_handle.student_index_entries[i].key == rollno_to_read)
		{
			if(repo_handle.student_index_entries[i].flag==RECORD_PRESENT)
			{
				fseek( repo_handle.studsys_data_fp, repo_handle.student_index_entries[i].offset, SEEK_SET );
					fread( &rollno_to_read, sizeof( int ), 1, repo_handle.studsys_data_fp );
					fread( rec, sizeof( struct Student), 1, repo_handle.studsys_data_fp );
					return LIB_SUCCESS;
			} 
			return LIB_REC_NOT_FOUND;
		}
	}
	return LIB_REC_NOT_FOUND;
}
//1. check if repo status is closed then  return appropriate error code referring to the error codes 
//2. else continue with following action sequence

//3.1 read rollno
//3.2 check if rollno is equal to the rollno_to_read 
//3.3 if yes then read entire record of a Student and return studsys_success
//3.4 else skip the record and read next rollno of the Student
//4. Repeat step 4.1 to 4.4 till end of file 
//5. Return record not found : appropriate error code referring to the error codes 

int delete_student_by_rollno( int key )
{
	if(repo_handle.stud_repo_status!=LIB_REPO_OPEN)
    	return LIB_REPO_NOT_OPEN;
	for(int i=0;i<repo_handle.student_index_count;i++)
	{
		if(repo_handle.student_index_entries[i].key==key)
		{
		if(repo_handle.student_index_entries[i].flag==RECORD_PRESENT)
		{
			repo_handle.student_index_entries[i].flag=RECORD_DELETED;
			repo_handle.student_index_count--;
			return LIB_SUCCESS;

		}
	}
	}
	return LIB_REC_NOT_FOUND;
}

//-----delete_rec_by_key
//-----check repo status
//-----Search for index entry in book_index_entries array
//-----if key matches and flag is 1 then reset flag
//-----if key matches but flag is already reset return status
//-----if key doesn't match then return status

//---------------------------------------------------Additional Functions -----------------------

int get_student_by_name(char *name, struct Student *rec)
{
	if(repo_handle.stud_repo_status!=LIB_REPO_OPEN)
		return LIB_REPO_NOT_OPEN;
	for(int i=0;i<repo_handle.student_index_count;i++)
	{
		if(strcmp(repo_handle.student_index_entries[i].second_key,name)==0)
		{
			fseek(repo_handle.studsys_data_fp, repo_handle.student_index_entries[i].offset, SEEK_SET);
			int temp;
			fread(&temp,sizeof(temp),1,repo_handle.studsys_data_fp);
			fread(rec, sizeof(*rec), 1, repo_handle.studsys_data_fp);
			return LIB_SUCCESS;

		}
	}
	return LIB_REC_NOT_FOUND;
}

int get_book_by_title(char *title, struct Book *rec)
{
	if(repo_handle.book_repo_status!=LIB_REPO_OPEN)
		return LIB_REPO_NOT_OPEN;
	for(int i=0;i<repo_handle.book_index_count;i++)
	{
		if(strcmp(repo_handle.book_index_entries[i].second_key,title)==0)
		{
			fseek(repo_handle.booksys_data_fp, repo_handle.book_index_entries[i].offset, SEEK_SET);
			int temp;
			fread(&temp,sizeof(temp),1,repo_handle.booksys_data_fp);
			fread(rec, sizeof(*rec), 1, repo_handle.booksys_data_fp);
			// printf("Book Details:-\nISBN:%d\nTitle:%s\nAuthor:%s\nPrice:%.2f\n",rec->isbn,rec->title,rec->author,rec->price);
			
			fseek(repo_handle.issuesys_data_fp,0,SEEK_SET);
			while(1)
			{
				if(feof(repo_handle.issuesys_data_fp))
					break;
				struct Issue iss;
				fread(&iss,sizeof(struct Issue),1,repo_handle.issuesys_data_fp);
				if(iss.isbn==repo_handle.book_index_entries[i].key)
				{
					struct Student student;
					get_student_by_rollno(iss.rollno,&student);
						// printf("Book is issued to :\nRollNo:%d\nName:%s\nAddress:%s\nCGPA:%.2f\n",student.rollno,student.name,student.address,student.cgpa);
					return LIB_SUCCESS;
				}

			}
			// printf("Book is not issued\n");
			return LIB_SUCCESS;
		}
	}
	return LIB_REC_NOT_FOUND;
}
	


//--------------------------------issue()---------------------------------
int issue(int rollno, int isbn)
{
	if(repo_handle.book_repo_status!=LIB_REPO_OPEN || repo_handle.stud_repo_status!=LIB_REPO_OPEN || repo_handle.issue_repo_status!=LIB_REPO_OPEN)
		return LIB_FILE_ERROR;

	struct Book rec;
	struct Student stud;


	int status1=get_book_by_isbn(isbn,&rec);
	// printf("\n%d\n\n",status1);
	int status2=get_student_by_rollno(rollno,&stud);
	if(status1!=0 || status2!=0)
	{
		return BOOK_FAILURE;
	}
	struct Issue issue;
	issue.isbn=isbn;
	issue.rollno=rollno;

	fseek(repo_handle.issuesys_data_fp,0,SEEK_END);
	int write_issue=fwrite(&issue,sizeof(struct Issue),1,repo_handle.issuesys_data_fp);
	if(write_issue!=1)
		return BOOK_FAILURE;
	return LIB_SUCCESS;
}

	// check if book repo status is closed then return return appropriate error code referring to the error codes 
	// else continue with following action sequence


	// check if student repo status is closed then return return appropriate error code referring to the error codes 
	// else continue with following action sequence

	
	// check if issue repo status is closed then return return appropriate error code referring to the error codes 
	// else continue with following action sequence


	//declare student and book variables 

	//get book by isbn and store status in status1
	//get student by rollno and store status in status1
	
	
	// if status1 and status2 are successful then continue with following action sequence else return error
		
	// create Issue object and assign rollno and isbn 
	// set the file pointer to end
	// write issue record
	
	// if both actions are successful then return success 
	// else return failed		



//----------------------------------close()---------------------------------
int libsys_close()
{
	char index_name[30];
	strcpy(index_name,repo_handle.booksys_name);

	char student_index_name[30];
	strcpy(student_index_name,repo_handle.studsys_name);

	if(booksys_close()==0 && studsys_close()==0 && issuesys_close()==0)
	{
		
		strcat(index_name,".ndx");
		FILE *ndx_fp=fopen(index_name,"wb");

		if(ndx_fp==NULL)
			return LIB_FILE_ERROR;

		int put_size=fwrite(&repo_handle.book_index_count,sizeof(int),1,ndx_fp);
		int put_offsets=fwrite(repo_handle.book_index_entries,sizeof(struct LIB_NdxInfo),repo_handle.book_index_count,ndx_fp);
		
		if(put_size!=1 || put_offsets!=repo_handle.book_index_count) 
			return LIB_ADD_FAILED;
		fclose(ndx_fp);

		strcat(student_index_name,".ndx");
		FILE *student_ndx_fp=fopen(student_index_name,"wb");

		if(student_ndx_fp==NULL)
			return LIB_FILE_ERROR;

		put_size=fwrite(&repo_handle.student_index_count,sizeof(int),1,student_ndx_fp);
		put_offsets=fwrite(repo_handle.student_index_entries,sizeof(struct LIB_NdxInfo),repo_handle.student_index_count,student_ndx_fp);
		
		if(put_size!=1 || put_offsets!=repo_handle.student_index_count) 
			return LIB_ADD_FAILED;
		fclose(student_ndx_fp);

		return LIB_SUCCESS;
	}
	return LIB_FILE_ERROR;
}

	//call booksys_close()
	//call studsys_close()
	//call issuesys_close()

	// Open the index file in wb mode (write mode, not append mode)
	// Write number of index entries at the beginning of index file
	// Unload the index array into the index file (overwrite the entire index file)
	// Close the index file

	//check status of above functions
	// if all of them return success then return SUCCESS else return ERROR



int booksys_close()
{
	if(repo_handle.book_repo_status!=LIB_REPO_OPEN)
		LIB_REPO_NOT_OPEN;
	fclose(repo_handle.booksys_data_fp);
	repo_handle.book_repo_status=LIB_REPO_CLOSED;

	strcpy(repo_handle.booksys_name,"");
	return LIB_SUCCESS;
}

	//1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
	//2. else continue with following action sequence
	//3. close file pointer
	//4. set booksys_name as "" 
	//5. set book_repo_status=LIB_REPO_CLOSED
    	//6. return LIB_SUCCESS;




int studsys_close()
{
	if(repo_handle.stud_repo_status!=LIB_REPO_OPEN)
		LIB_REPO_NOT_OPEN;
	fclose(repo_handle.studsys_data_fp);
	repo_handle.stud_repo_status=LIB_REPO_CLOSED;

	strcpy(repo_handle.studsys_name,"");
	return LIB_SUCCESS;
}

	//1. check if repo status is closed then  return appropriate error code referring to the error codes 
	//2. else continue with following action sequence
	//3. close file pointer
	//4. set studsys_name as "" 
	//5. set stud_repo_status=LIB_REPO_CLOSED
    //6. return LIB_SUCCESS;



int issuesys_close()
{
	if(repo_handle.issue_repo_status!=LIB_REPO_OPEN)
		LIB_REPO_NOT_OPEN;
	fclose(repo_handle.issuesys_data_fp);
	repo_handle.issue_repo_status=LIB_REPO_CLOSED;

	strcpy(repo_handle.issuesys_name,"");
	return LIB_SUCCESS;
}
	//1. check if repo status is closed then  return appropriate error code referring to the error codes 
	//2. else continue with following action sequence
	//3. close file pointer
	//4. set issuesys_name as "" 
	//5. set issue_repo_status=LIB_REPO_CLOSED
    	//6. return LIB_SUCCESS;


