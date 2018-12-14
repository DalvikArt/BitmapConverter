#include "threadproc.h"

#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <string>

#include "dir.h"
#include "bmp.h"

using namespace std;

#define THREAD_NUM 5

const string ORG_DIR("/media/dalvikart/extended/train/");
const string DST_DIR("/media/dalvikart/extended/bmp/");

PFILE_NODE head = NULL;
pthread_mutex_t lock;

void *GenBMPProc(void *args)
{
    while(head)
    {
        // try to get lock
        pthread_mutex_lock(&lock);

        // critical area
        PFILE_NODE cur = TakeNode(head);

        // release lock
        pthread_mutex_unlock(&lock); 

        string srcFileName = ORG_DIR + cur->fileName;
        string dstFileName = DST_DIR + cur->fileName;

        dstFileName = dstFileName.substr(0, dstFileName.length() - 6) + ".bmp";
        
        ConvertToBmp(srcFileName.c_str(), dstFileName.c_str());

        DeleteNode(cur);
    }
}

void StartGenBMP()
{
    head = ListDir(ORG_DIR.c_str());

    pthread_t threadPool[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; ++i)
    {
        int ret = pthread_create(&threadPool[i], NULL, GenBMPProc, NULL);
    }

    for(int i = 0; i < THREAD_NUM; ++i)
    {
        pthread_join(threadPool[i], NULL);
    }
}