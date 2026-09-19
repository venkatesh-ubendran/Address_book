#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>
#include <string.h>

struct contact
{
	char name[50];
	char phone[15];
	char email[50];

};

struct Addressbook
{
	struct contact contacts[100];
	int contactcount;
	int index_record[100];
	int ir_size;
};

void pull_file_data(struct Addressbook *,char *);
void push_data_to_file(struct Addressbook *,char *);
void add_contact(struct Addressbook *addressbook);
void search_contact(struct Addressbook *addressbook);
void edit_contact(struct Addressbook *addressbook);
void delete_contact(struct Addressbook *addressbook);
void list_contacts(struct Addressbook *addressbook);
int mobile_verify(char mobile[]);
int gmail_verify(struct Addressbook *,char gmail[]);
void search_by_name(struct Addressbook *,char name[]);
void search_by_phone(struct Addressbook *,char phone[]);
void search_by_gmail(struct Addressbook *,char gmail[]);
/*int check_duplicate_mobile(struct Addressbook *,char mobile[]);*/


#endif
