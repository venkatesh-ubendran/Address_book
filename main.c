#include <stdio.h>
#include "addressbook.h"

int main(){
	int choice;
	struct Addressbook addressbook;
	addressbook.contactcount = 0;
	for(int i=0;i<100;i++){
		addressbook.index_record[i] = 0;
	}
	pull_file_data(&addressbook,"database.csv");

	do{
		printf("Address book menu\n");
		printf("Read statement: \n");
		printf("1. Add/create contact\n");
		printf("2. Search contact\n");
		printf("3. Edit contact\n");
		printf("4. delete contact\n");
		printf("5. List all contacts\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				add_contact(&addressbook);
				break;
			case 2:
				search_contact(&addressbook);
				break;
			case 3:
				edit_contact(&addressbook);
				break;
			case 4:
				delete_contact(&addressbook);
				break;
			case 5:
				list_contacts(&addressbook);
				break;
			case 6:
				push_data_to_file(&addressbook,"database.csv");
				printf("Exiting...\n");
				break;
			default:
				printf("Invalid choice,please try again\n");
		}
		

	}while(choice != 6);
	return 0;
}



