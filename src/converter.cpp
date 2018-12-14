#include <iostream>
#include <time.h>

#include "threadproc.h"

using namespace std;

int main(int argc, char argv[])
{
    cout << "Start bitmaps generating..." << endl;

    time_t startTime = time(NULL);

    StartGenBMP();

    time_t duration = time(NULL) - startTime;

    cout << "Done. Duration: " << duration << "s." << endl;

    return 0;
}