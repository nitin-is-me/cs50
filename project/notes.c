#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addNote(void);
void listNotes(void);
void readNote(int id);
void deleteNote(int id);
void searchNote(char keyword[]);
int getNextId(void);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage:\n");
        printf("./notes add\n");
        printf("./notes list\n");
        printf("./notes read <id>\n");
        printf("./notes delete <id>\n");
        printf("./notes search <keyword>\n");
        return 1;
    }

    if (strcmp(argv[1], "add") == 0)
    {
        addNote();
    }
    else if (strcmp(argv[1], "list") == 0)
    {
        listNotes();
    }
    else if (strcmp(argv[1], "read") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: ./notes read <id>\n");
            return 1;
        }
        readNote(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "delete") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: ./notes delete <id>\n");
            return 1;
        }
        deleteNote(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "search") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: ./notes search <keyword>\n");
            return 1;
        }
        searchNote(argv[2]);
    }
    else
    {
        printf("Unknown command.\n");
    }

    return 0;
}

int getNextId(void)
{
    FILE *file = fopen("notes.txt", "r");
    if (file == NULL)
    {
        return 1;
    }

    char line[256];
    int id = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "ID:", 3) == 0)
        {
            sscanf(line, "ID:%d", &id);
        }
    }

    fclose(file);
    return id + 1;
}

void addNote(void)
{
    int nextId = getNextId();
    FILE *file = fopen("notes.txt", "a");

    if (file == NULL)
    {
        printf("Could not open notes.txt\n");
        return;
    }

    char title[100];
    char content[500];

    printf("Title: ");
    fgets(title, sizeof(title), stdin);

    printf("Content: ");
    fgets(content, sizeof(content), stdin);

    fprintf(file, "ID:%d\n", nextId);
    fprintf(file, "TITLE:%s", title);
    fprintf(file, "CONTENT:%s", content);
    fprintf(file, "====================================\n");

    fclose(file);
    printf("Note #%d saved successfully!\n", nextId);
}

void listNotes(void)
{
    FILE *file = fopen("notes.txt", "r");
    if (file == NULL)
    {
        printf("No notes found.\n");
        return;
    }

    char line[256];
    int id;
    char title[100];
    int hasNotes = 0;

    printf("\n--- YOUR NOTES ---\n");
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "ID:%d", &id) == 1)
        {
            if (fgets(line, sizeof(line), file))
            {
                // strip the "TITLE:" prefix for clean listing
                if (strncmp(line, "TITLE:", 6) == 0)
                {
                    strcpy(title, line + 6);
                    // remove trailing newline
                    title[strcspn(title, "\n")] = 0;
                    printf("[%d] %s\n", id, title);
                    hasNotes = 1;
                }
            }
        }
    }
    printf("------------------\n");

    if (!hasNotes)
    {
        printf("No notes to display.\n");
    }

    fclose(file);
}

void readNote(int id)
{
    FILE *file = fopen("notes.txt", "r");
    if (file == NULL)
    {
        printf("No notes found.\n");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int currentId;
        if (sscanf(line, "ID:%d", &currentId) == 1)
        {
            if (currentId == id)
            {
                found = 1;
                printf("\n--- Note #%d ---\n", id);

                // read and print title
                if (fgets(line, sizeof(line), file)) printf("%s", line);
                // read and print content
                if (fgets(line, sizeof(line), file)) printf("%s", line);

                printf("----------------\n");
                break;
            }
        }
    }

    if (!found)
    {
        printf("Note #%d not found.\n", id);
    }

    fclose(file);
}

void deleteNote(int id)
{
    FILE *file = fopen("notes.txt", "r");
    if (file == NULL)
    {
        printf("No notes found.\n");
        return;
    }

    // temporary file to write everything except the deleted note
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error creating temporary storage.\n");
        fclose(file);
        return;
    }

    char line[256];
    int currentId;
    int found = 0;
    int skipping = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "ID:%d", &currentId) == 1)
        {
            if (currentId == id)
            {
                skipping = 1; // start skipping lines for this note
                found = 1;
                continue;
            }
            else
            {
                skipping = 0; // keep other notes
            }
        }

        // if we reach the dividor line of the deleted note, stop skipping
        if (skipping && strcmp(line, "====================================\n") == 0)
        {
            skipping = 0;
            continue;
        }

        if (!skipping)
        {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // replace the original file with the updated temporary file
    remove("notes.txt");
    rename("temp.txt", "notes.txt");

    if (found)
    {
        printf("Note #%d deleted successfully.\n", id);
    }
    else
    {
        printf("Note #%d not found.\n", id);
    }
}

void searchNote(char keyword[])
{
    FILE *file = fopen("notes.txt", "r");
    if (file == NULL)
    {
        printf("No notes found.\n");
        return;
    }

    char line[256];
    char noteBlock[1000] = "";
    int currentId = 0;
    int foundMatch = 0;

    printf("\n--- Search Results for '%s' ---\n", keyword);

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "ID:", 3) == 0)
        {
            sscanf(line, "ID:%d", &currentId);
            strcpy(noteBlock, ""); // reset block for new note
        }

        strcat(noteBlock, line);

        // if we hit the end of a note block, inspect it
        if (strcmp(line, "====================================\n") == 0)
        {
            // Case sensitive search
            if (strstr(noteBlock, keyword) != NULL)
            {
                printf("Match found in Note #%d:\n%s", currentId, noteBlock);
                foundMatch = 1;
            }
        }
    }

    if (!foundMatch)
    {
        printf("No notes matched your search query.\n");
    }
    printf("----------------------------------------\n");

    fclose(file);
}
