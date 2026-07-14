# Notes - A Simple Command Line Notes Manager

#### Video Demo: https://youtu.be/i6Bv40YEQTg

#### Description:

Notes is a simple command-line application written in C that allows users to create, view, search, and manage personal notes directly from the terminal. The purpose of this project is to provide a lightweight alternative to graphical note-taking applications while demonstrating fundamental programming concepts learned throughout CS50.

The application is executed entirely through command-line arguments. Rather than displaying an interactive menu, users execute commands such as `add`, `list`, `read`, `delete`, and `search`. This design was inspired by common Linux command-line utilities, where each command performs one specific task.

The project stores all notes inside a plain text file named `notes.txt`. Every note consists of four lines:

```
ID:1
TITLE:Example Title
CONTENT:Example Content
====================================
```

Each note is assigned a unique numeric ID that is automatically generated whenever a new note is added. This allows notes to be identified and managed easily regardless of their title.

## Features

### Add Note

The `add` command allows the user to create a new note by entering a title and a short content. The program automatically generates the next available ID and appends the note to `notes.txt`.

Example:

```
./notes add
```

The user is prompted for:

- Title
- Content

The note is then saved successfully.

---

### List Notes

The `list` command displays every note currently stored inside the file. Instead of printing the complete note, only the note ID and title are displayed. This provides a quick overview without overwhelming the user.

Example:

```
./notes list
```

Output:

```
[1] JDBC
[2] SQL
[3] Linux Commands
```

---

### Read Note

The `read` command displays the complete contents of a specific note using its ID.

Example:

```
./notes read 2
```

The program searches through the file until it finds the requested note and then prints both its title and content.

If the specified ID does not exist, an appropriate error message is displayed.

---

### Delete Note

The `delete` command removes a note from storage.

Since text files cannot directly remove content from the middle of a file, the program creates a temporary file, copies every note except the selected one, deletes the original file, and finally renames the temporary file back to `notes.txt`.

Example:

```
./notes delete 3
```

If the requested note is found, it is permanently removed.

---

### Search Notes

The `search` command allows users to search for a keyword.

The program scans every stored note and prints any notes whose title or content contains the given keyword.

Example:

```
./notes search JDBC
```

If no matching notes exist, an informative message is displayed.

---

## Files

### notes.c

This file contains the complete implementation of the application, including:

- command-line argument processing
- file reading and writing
- automatic ID generation
- adding notes
- listing notes
- reading notes
- deleting notes
- searching notes

### notes.txt

This file serves as the application's database. All notes created by the user are permanently stored inside this file using a simple text-based format.

### README.md

This file documents the project, explains its features, internal design, and usage instructions.

---

## Design Choices

One important design decision was to store notes inside a plain text file rather than using a database such as SQLite.

Since this project was intended to practice the concepts taught in CS50, using plain text files allowed me to work directly with C file handling functions such as `fopen`, `fgets`, `fprintf`, `fputs`, `remove`, and `rename`. This also made the project lightweight because it has no external dependencies.

Another design decision was using command-line arguments instead of creating an interactive menu. This approach makes the application resemble common Linux utilities and keeps the program simple to use.

The project intentionally keeps the note format straightforward and human-readable, allowing users to inspect or modify the file manually if necessary.

---

## What I Learned

Building this project helped reinforce many concepts introduced throughout CS50, including:

- command-line arguments (`argc` and `argv`)
- functions
- strings
- arrays
- file handling
- parsing text files
- searching through files
- creating temporary files
- basic data management
- modular program organization

The project also provided practical experience with designing a complete application from scratch instead of solving a predefined programming problem.

---

## AI Acknowledgement

During development, I used AI tools as assistants for explanations, debugging, and discussing implementation ideas, in accordance with the CS50 final project policy. All design decisions, testing, integration, and understanding of the project were completed by me.
