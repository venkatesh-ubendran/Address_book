# Address Book Management System

A console-based Address Book Management System developed in C.

## Features

- Add new contacts
- Search contacts by name, phone number, or email
- Edit existing contacts
- Delete contacts
- List all contacts
- Validate mobile numbers
- Validate Gmail addresses
- Prevent duplicate phone numbers and email addresses
- Store and retrieve contact data using CSV file handling

## Technologies Used

- C Programming
- Structures
- Pointers
- File Handling
- String Handling
- Git & GitHub
- Linux

## Project Structure

- `main.c` – Main program and menu handling
- `addressbook.c` – Address Book functionalities
- `addressbook.h` – Structure definitions and function declarations
- `database.csv` – Contact database

## How to Run

Compile the project using:

```bash
gcc main.c addressbook.c -o addressbook
Then run the application.
./addressbook
