#include "bmp.h"

extern "C" {
    void Convert(const char *srcFile, const char *dstFile)
    {
        ConvertToBmp(srcFile, dstFile);
    }
}