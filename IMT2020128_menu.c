#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

//Your code must support menu-driven functionality.
//Function calls rollno_libsys.h
void display_menu()
{
    printf("\nMenu:\n\n1) Add book\n2) Add student\n3) Delete book \n4) Delete student\n5) Issue book\n6) Search book by isbn\n7) Search book by title\n8) Search student by roll number\n9) Search student by name\n0) Exit\n");
    printf("Enter your choice: ");
}
int main()
{
    printf("Creating Library \n");

    char *stud_repo = "Student_Repo";
    char *book_repo = "Book_Repo";
    char *issue_repo = "Issue_Repo";

    if(libsys_create(book_repo,stud_repo,issue_repo)!=LIB_SUCCESS){
		printf("Unable to create library\n");
		return 1;
	}
    libsys_open(book_repo,stud_repo,issue_repo);
    printf("Library successfully created!\n");

    int flag=1;
    while(flag)
    {
        display_menu();
        int user_choice;
        scanf("%d",&user_choice);
        if(user_choice==0)
        {
            flag=0;
            continue;
        }

        int isbn, rollno;
        char buf[40];
        
        char *name = (char *) malloc(sizeof(buf));
        char *title = (char *) malloc(sizeof(buf));
        struct Student student;
        struct Book book;

        switch(user_choice)
        {
            case 1:
                printf("Enter Book's isbn value: ");
                scanf("%d",&book.isbn);

                printf("Enter Book's name: ");
                scanf("%s", book.title);

                printf("Enter Book's author: ");
                scanf("%s", book.author);

                printf("Enter Book's price: ");
                scanf("%f", &book.price);

                if(put_book_by_isbn(book.isbn,&book)!=LIB_SUCCESS)
                    printf("\nBook cannot be added\n");
                else
                    printf("\nBook Added successfully\n");
                break;

            case 2:
                printf("Enter Student's rollno: ");
                scanf("%d", &student.rollno);

                printf("Enter Student's name: ");
                scanf("%s", student.name);

                printf("Enter Student's address: ");
                scanf("%s", student.address);

                printf("Enter Student's cgpa: ");
                scanf("%f", &student.cgpa);
            
                if (put_student_by_rollno(student.rollno, &student) != LIB_SUCCESS)
                    printf("\nStudent Cannot be added\n");
    
                else
                    printf("\nStudent added successfully\n");
                break;

            case 3:
                printf("\nEnter Book's isbn that is to be deleted\n");
                scanf("%d",&isbn);

                if(delete_book_by_isbn(isbn))
                    printf("\n Book cannot be deleted\n");
                else
                    printf("\nBook deleted successfully\n");
                break;

            case 4:
                printf("\nEnter student's rollno to delete: ");
                scanf("%d", &rollno);

                if(delete_student_by_rollno(rollno))
                    printf("\nStudent Cannot be deleted\n");
                else
                    printf("\nStudent deleted succesfully\n");
                break;
            case 5:
                printf("Enter Book's isbn: ");
                scanf("%d", &isbn);
                
                printf("Enter Student's roll no: ");
                scanf("%d", &rollno);

                if (issue(rollno, isbn))
                    printf("\nCannot issue\n");
                else
                    printf("\nBook issued successfully\n");
                break;
            case 6:
                printf("Enter Book's isbn to search: ");
                scanf("%d",&isbn);

                if(get_book_by_isbn(isbn,&book))
                    printf("\nBook not found\n");
                else{
                    printf("Book details\n ISBN: %d\n Title: %s\n Author: %s\n Price: %f",book.isbn,book.title,book.author,book.price);
                    details_book_issued(isbn);
                }
                break;

            case 7:
                printf("Enter Book's title to search: ");
                scanf("%s",title);

                if(get_book_by_title(title,&book))
                    printf("\nBook not found\n");
                else
                    printf("Book details\n ISBN: %d\n Title: %s\n Author: %s\n Price: %f",book.isbn,book.title,book.author,book.price);
                break;

            case 8:
                printf("Enter Student's roll number to search: ");
                scanf("%d",&rollno);

                if(get_student_by_rollno(rollno,&student))
                    printf("\nStudent not found\n");
                else  
                    printf("Student Details\n Roll number: %d\n Name: %s\nAddress: %s\nCGPA: %f\n",student.rollno,student.name,student.address,student.cgpa);
                break;
            case 9:
                printf("Enter Student's name to search: ");
                scanf("%s",name);

                if(get_student_by_name(name,&student))
                    printf("\nStudent not found\n");
                else  
                    printf("Student Details\n Roll number: %d\n Name: %s\nAddress: %s\nCGPA: %f\n",student.rollno,student.name,student.address,student.cgpa);
                break;
            default:
                printf("\nEnter a correct choice\n");
                break;


        }
    }

    libsys_close();
}