#include "bmp.h"

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

typedef unsigned short      WORD;
typedef unsigned int        DWORD;
typedef unsigned char       BYTE;
typedef int LONG;

typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
}__attribute__((packed)) BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct _tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
}__attribute__((packed)) BITMAPINFOHEADER;

BITMAPFILEHEADER ConstructBMPHeader(size_t length)
{
    DWORD headerLen = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;

    BITMAPFILEHEADER header;

    memset(&header, 0, sizeof(header));

    header.bfType = 0x4d42;

    header.bfSize = length + headerLen;

    header.bfOffBits = headerLen;

    return header;
}

BITMAPINFOHEADER ConstructInfoHeader(size_t length)
{
    BITMAPINFOHEADER header;

    memset(&header, 0, sizeof(header));

    header.biSize = sizeof(header);

    header.biWidth = 512;
    header.biHeight = length / 512;

    header.biPlanes = 1;
    header.biBitCount = 8;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;

    return header;
}

void ConvertToBmp(const char *srcFile, const char *dstFile)
{
    ifstream ifs;
    ifs.open(srcFile, ios::binary);

    ifs.seekg(0, ifs.end);
    DWORD length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    char *buffer = new char[length];
    ifs.read(buffer, length);

    ifs.close();

    BITMAPFILEHEADER fileHeader = ConstructBMPHeader(length);
    BITMAPINFOHEADER infoHeader = ConstructInfoHeader(length);

    // construct rgb panel
    RGBQUAD rgbquad[256];
    for(int i = 0; i < 256; i++)
    {
        rgbquad[i].rgbBlue = i;
        rgbquad[i].rgbGreen = i;
        rgbquad[i].rgbRed = i;
        rgbquad[i].rgbReserved = 0;
    } 

    ofstream ofs;
    ofs.open(dstFile, ios::binary);

    ofs.write((const char*)&fileHeader, sizeof(fileHeader));
    ofs.write((const char*)&infoHeader, sizeof(infoHeader));
    ofs.write((const char*)&rgbquad, sizeof(RGBQUAD)*256);

    ofs.write((const char*)buffer, length);

    ofs.close();

    delete[] buffer;
}