#include "dir.h"

#include <iostream>
#include <cstring>
#include <dirent.h>

using namespace std;

void DeleteNode(PFILE_NODE node)
{
    if(node == NULL)
        return;

    if(node->fileName != NULL) delete[] node->fileName;
    delete[] node;
}

PFILE_NODE ListDir(const char *path)
{
    PFILE_NODE head = new FILE_NODE{NULL, NULL};
    PFILE_NODE cur = head;
    DIR *dir = opendir(path);

    if (dir != NULL)
    {
        dirent *dent;
        while (dent = readdir(dir))
        {
            // skip "." and ".."
            if(!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
                continue;

            size_t nameLen = strlen(dent->d_name);
            char *buffer = new char[nameLen + 1];
            strcpy(buffer, dent->d_name);
            buffer[nameLen] = 0;

            PFILE_NODE newNode = new FILE_NODE{buffer, NULL};
            cur->next = newNode;
            cur = cur->next;
        }
        closedir(dir);
    }
    else
    {
        cerr << "Couldn't read directory " << path << endl;
        return NULL;
    }

    PFILE_NODE old = head;
    head = head->next;

    // delete old head to avoid mem overflow
    DeleteNode(old);

    return head;
}

PFILE_NODE TakeNode(PFILE_NODE &head)
{
    if(head == NULL)
        return NULL;

    PFILE_NODE curNode = head;

    head = head->next;

    // set next pointer of curNode to NULL to avoid misoperation
    curNode->next = NULL;
    
    return curNode;
}
