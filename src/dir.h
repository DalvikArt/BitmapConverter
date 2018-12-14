typedef struct _FILE_NODE{
    const char *fileName;
    struct _FILE_NODE *next;
} FILE_NODE, *PFILE_NODE;

void DeleteNode(PFILE_NODE node);
PFILE_NODE ListDir(const char *path);
PFILE_NODE TakeNode(PFILE_NODE &head);