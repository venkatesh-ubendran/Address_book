#include "addressbook.h" 
#include <string.h>
int search_flag = 0;
void pull_file_data(struct Addressbook *addressbook,char * database)
{
	FILE *fp = fopen(database,"r");


	if(fp == NULL)
	{
    	printf("Unable to open file\n");
    	return;
	}

	while(fscanf(fp,"%[^,],%[^,],%s\n",
                        addressbook->contacts[addressbook->contactcount].name,
                        addressbook->contacts[addressbook->contactcount].phone,
                        addressbook->contacts[addressbook->contactcount].email) == 3){
		addressbook->contactcount++;
	}
	fclose(fp);
}

void add_contact(struct Addressbook *addressbook)
{
	char temp_name[50];
	char phone[15];
	char email[30];

	printf("Enter the name: ");
	scanf(" %[^\n]",temp_name);

	label1:printf("Enter your phone_number: ");
	scanf("%s",phone);

	

	if(mobile_verify(phone) == 0){
		printf("Invalid mobile number.\n");
		printf("Please try valid number.\n");
		goto label1;
	}
	   label2: printf("Enter your email: ");
        scanf("%s",email);

	if(gmail_verify(addressbook,email) == -1){
		printf("Gmail already exists.\n");
		printf("please try another gmail.\n");
		goto label2;
	}
	
	if(gmail_verify(addressbook,email) == 0){
                printf("Invalid gmail.\n");
                printf("Please enter valid gmail.\n");
                goto label2;
        }
	if((mobile_verify(phone) == 1) && (gmail_verify(addressbook,email) == 1)){
		strcpy(addressbook->contacts[addressbook->contactcount].name, temp_name);

		strcpy(addressbook->contacts[addressbook->contactcount].phone, phone);

		strcpy(addressbook->contacts[addressbook->contactcount].email, email);

		addressbook->contactcount++;

		printf("Contact added successfully.\n");
	}

}

int mobile_verify(char *mobile)
{
	int i;
	for(i=0;mobile[i];i++){
		if(mobile[i] < '0' || mobile[i] > '9'){
			return 0;
		}
	}

	if(strlen(mobile) != 10){
	       return 0;
	}


	if(mobile[0] < 53 || mobile[0] > 57){
		return 0;
	}

	return 1;

}
int gmail_verify(struct Addressbook *addressbook, char *gmail)
{
    int l = strlen(gmail);

    if(l <= 10)
    {
        return 0;
    }

    if(strcmp(gmail + l - 10, "@gmail.com"))
    {
        return 0;
    }

    for(int i = 0; i < addressbook->contactcount; i++)
    {
        if(strcmp(gmail, addressbook->contacts[i].email) == 0)
        {
            return -1;
        }
    }

    return 1;
}
void list_contacts(struct Addressbook *addressbook)
{ 	printf("\n");
	printf("-----------------------------------------\n");
       for(int i=0;i<addressbook->contactcount;i++){
       printf("%d %s  ",i+1,addressbook->contacts[i].name);
       printf("%s  ",addressbook->contacts[i].phone);
       printf("%s\n",addressbook->contacts[i].email);
       }
       printf("------------------------------------------\n");
       printf("\n");
}

void search_contact(struct Addressbook *addressbook)
{	
	printf("choose the given option: \n");
	printf("1.search by name\n");
        printf("2.search by phone\n");
	printf("3.search by gamil\n");
 	int choice;
	printf("Enter your choice: ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			char name[50];
			printf("Enter the name:");
			scanf("%s",name);
			search_by_name(addressbook,name);
			break;
		case 2:
			char phone[15];
                        printf("Enter the mobile_no:");
                        scanf("%s",phone);
			search_by_phone(addressbook,phone);
			break;
		case 3:
			char gmail[30];
                        printf("Enter the gmail:");
                        scanf("%s",gmail);
			search_by_gmail(addressbook,gmail);
			break;
		default:
			printf("Invalid option,choose between 1 to 3.");
	}
}

void search_by_name(struct Addressbook *addressbook,char *name){
	int s_no = 1;

	for(int i=0;i<addressbook->contactcount;i++){
		if(strcmp(addressbook->contacts[i].name,name) == 0){
			printf("%d",s_no);
            		printf("Name  : %s\n", addressbook->contacts[i].name);
            		printf("Phone : %s\n", addressbook->contacts[i].phone);
            		printf("Email : %s\n", addressbook->contacts[i].email);
			s_no++;
			addressbook->index_record[i] = 1;
		}
	}
	if(s_no == 1){
		printf("Name not found\n");
		return;
	}
	if(search_flag == 1){
		int choice,match_count=0,search_index;
		char opt;
		printf("Are you sure to delete this: \n");
		printf("(y / n)?");
		scanf(" %c",&opt);
		switch(opt){
			case 'y':
			case 'Y':

				printf("Enter the serial number you want.\n");
                		scanf("%d",&choice);
				if(choice<s_no && choice >= 1){
					for(int i=0;i<addressbook->contactcount;i++){
						
						if(addressbook->index_record[i] == 1){
							match_count++;
						if(choice == match_count){
                                          		search_index = i;
							    
								for(int j=search_index;j<addressbook->contactcount-1;j++){
									addressbook->contacts[j] = addressbook->contacts[j+1];
								}
							addressbook->contactcount--;
							printf("Deleted\n");
							break;
				
						
							}
						}
					}
					
				}
				else{
                        		printf("invalid choice");
                			}
				break;
				
			case 'n':
			case 'N':
				break;
			default:
				printf("invalid option\n");
		}
	}
	         
        if(search_flag == 2){
                 int choice,match_count=0,search_index;
                char opt;
                printf("Are you sure to edit this: \n");
                printf("(y / n)?");
                scanf(" %c",&opt);
                switch(opt){
                        case 'y':
                        case 'Y':

                                printf("Enter the serial number you want.\n");
                                scanf("%d",&choice);
                                if(choice<s_no && choice >= 1){
                                        for(int i=0;i<addressbook->contactcount;i++){

                                                if(addressbook->index_record[i] == 1){
                                                        match_count++;
                                                if(choice == match_count){
                                                        search_index = i;
                                                        char new_name[50];
                                                        printf("Enter new name: ");
                                                        scanf("%s",new_name);

                                                                strcpy(addressbook->contacts[search_index].name,new_name);
                                                        

                                                        printf("Edited\n");
                                                        break;

                                                        }
                                                }
                                        }

                                }
                                else{
                                         printf("invalid choice");
                                        }
                                break;

                        case 'n':
                        case 'N':
                                break;
                        default:
                                printf("invalid option\n");
                        }
                }


	
}
           

void search_by_phone(struct Addressbook *addressbook,char *phone){
        int s_no = 1;
        for(int i=0;i<addressbook->contactcount;i++){
                if(strcmp(addressbook->contacts[i].phone,phone) == 0){
                        printf("%d",s_no);
                        printf("Name  : %s\n", addressbook->contacts[i].name);
                        printf("Phone : %s\n", addressbook->contacts[i].phone);
                        printf("Email : %s\n", addressbook->contacts[i].email);
                        s_no++;
                        addressbook->index_record[i] = 1;
                }
        }
        if(s_no == 1){
                printf("Name not found\n");
		return;
        }

        if(search_flag == 1){
                int choice,match_count=0,search_index;
                char opt;
                printf("Are you sure to delete this: \n");
                printf("(y / n)?");
                scanf(" %c",&opt);
                switch(opt){
                        case 'y':
                        case 'Y':

                                printf("Enter the serial number you want.\n");
                                scanf("%d",&choice);
                                if(choice<s_no && choice >= 1){
                                        for(int i=0;i<addressbook->contactcount;i++){

                                                if(addressbook->index_record[i] == 1){
                                                        match_count++;
                                                if(choice == match_count){
                                                        search_index = i;

                                                                for(int j=search_index;j<addressbook->contactcount-1;j++){
                                                                        addressbook->contacts[j] = addressbook->contacts[j+1];
                                                                }
                                                        addressbook->contactcount--;
                                                        printf("Deleted\n");
                                                        break;


                                                        }
                                                }
                                        }

                                }
                                else{
					         printf("invalid choice");
                                        }
                                break;

                        case 'n':
                        case 'N':
                                break;
                        default:
                                printf("invalid option\n");
                        }
                }
	if(search_flag == 2){
                 int choice,match_count=0,search_index;
                char opt;
                printf("Are you sure to edit this: \n");
                printf("(y / n)?");
                scanf(" %c",&opt);
                switch(opt){
                        case 'y':
                        case 'Y':

                                printf("Enter the serial number you want.\n");
                                scanf("%d",&choice);
                                if(choice<s_no && choice >= 1){
                                        for(int i=0;i<addressbook->contactcount;i++){

                                                if(addressbook->index_record[i] == 1){
                                                        match_count++;
                                                if(choice == match_count){
                                                        search_index = i;
                                                        char new_phoneno[20];
                                                        printf("Enter new phonenumber: ");
                                                        scanf("%s",new_phoneno);
                                                        if(gmail_verify(addressbook,new_phoneno) == 1){

                                                                strcpy(addressbook->contacts[search_index].phone,new_phoneno);
                                                        }
                                                        else{
                                                                printf("Invalid format.\n");
                                                                return;
                                                        }

                                                        printf("Edited\n");
                                                        break;


                                                        }
                                                }
                                        }

                                }
                                else{
                                         printf("invalid choice");
                                        }
                                break;

                        case 'n':
                        case 'N':
                                break;
                        default:
                                printf("invalid option\n");
                        }
                }


}
void search_by_gmail(struct Addressbook *addressbook,char *gmail){
        int s_no = 1;
        for(int i=0;i<addressbook->contactcount;i++){
                if(strcmp(addressbook->contacts[i].email,gmail) == 0){
                        printf("%d",s_no);
                        printf("Name  : %s\n", addressbook->contacts[i].name);
                        printf("Phone : %s\n", addressbook->contacts[i].phone);
                        printf("Email : %s\n", addressbook->contacts[i].email);
                        s_no++;
                        addressbook->index_record[i] = 1;
                }
        }
        if(s_no == 1){
                printf("Name not found\n");
        }

        if(search_flag == 1){
                int choice,match_count=0,search_index;
                char opt;
                printf("Are you sure to delete this: \n");
                printf("(y / n)?");
                scanf(" %c",&opt);
                switch(opt){
                        case 'y':
                        case 'Y':

                                printf("Enter the serial number you want.\n");
                                scanf("%d",&choice);
                                if(choice<s_no && choice >= 1){
                                        for(int i=0;i<addressbook->contactcount;i++){

                                                if(addressbook->index_record[i] == 1){
                                                        match_count++;
                                                if(choice == match_count){
                                                        search_index = i;

                                                                for(int j=search_index;j<addressbook->contactcount-1;j++){
                                                                        addressbook->contacts[j] = addressbook->contacts[j+1];
                                                                }
                                                        addressbook->contactcount--;
                                                        printf("Deleted\n");
                                                        break;


                                                        }
                                                }
                                        }

                                }
                                else{


                 printf("invalid choice");
                                        }
                                break;

                        case 'n':
                        case 'N':
                                break;
                        default:
                                printf("invalid option\n");
                        }
                }
	if(search_flag == 2){
		 int choice,match_count=0,search_index;
                char opt;
                printf("Are you sure to edit this: \n");
                printf("(y / n)?");
                scanf(" %c",&opt);
                switch(opt){
                        case 'y':
                        case 'Y':

                                printf("Enter the serial number you want.\n");
                                scanf("%d",&choice);
                                if(choice<s_no && choice >= 1){
                                        for(int i=0;i<addressbook->contactcount;i++){

                                                if(addressbook->index_record[i] == 1){
                                                        match_count++;
                                                if(choice == match_count){
                                                        search_index = i;
							char new_mail[50];
							printf("Enter new gmail: ");
						        scanf("%s",new_mail);
							if(gmail_verify(addressbook,new_mail) == 1){

                                                                strcpy(addressbook->contacts[search_index].name,new_mail);
							}
							else{
								printf("Invalid format.\n");
								return;
							}
                                                      
                                                        printf("Edited\n");
                                                        break;


                                                        }
                                                }
                                        }

                                }
                                else{
					 printf("invalid choice");
                                        }
                                break;

                        case 'n':
                        case 'N':
                                break;
                        default:
                                printf("invalid option\n");
                        }
                }



}
void delete_contact(struct Addressbook *addressbook)
{
	search_flag = 1;
	search_contact(addressbook); 
 	search_flag == 0;
                for(int i=0;i<100;i++){
                        addressbook->index_record[i] = 0;
                }
        	
}

void edit_contact(struct Addressbook *addressbook)
{
    search_flag = 2;

    search_contact(addressbook);

    search_flag = 0;
	  for(int i=0;i<100;i++){
                        addressbook->index_record[i] = 0;
                }
}
void push_data_to_file(struct Addressbook *addressbook, char *database)
{
    FILE *fp = fopen(database, "w");

    if(fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    for(int i = 0; i < addressbook->contactcount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressbook->contacts[i].name,
                addressbook->contacts[i].phone,
                addressbook->contacts[i].email);
    }

    fclose(fp);
}
