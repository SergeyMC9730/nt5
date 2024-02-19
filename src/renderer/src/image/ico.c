/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

#include <nt5emul/renderer.h>

#include <stdio.h>

#include <memory.h>

rsb_array_Image *_ntRendererLoadIco(const char *filename, int *count) {
    rsb_array_Image *images = RSBCreateArrayImage();

    // Icon File Header (6 bytes)
    typedef struct {
        unsigned short reserved;    // Must be always 0
        unsigned short imageType;   // Specifies image type: 1 for icon (.ICO) image, 2 for cursor (.CUR) image. Other values are invalid.
        unsigned short imageCount;  // Specifies number of entries in the file.
    } IcoHeader;

    // Icon Entry info (16 bytes)
    typedef struct {
        unsigned char width;        // Specifies image width in pixels. Can be any number between 0 and 255. Value 0 means image width is 256 pixels.
        unsigned char height;       // Specifies image height in pixels. Can be any number between 0 and 255. Value 0 means image height is 256 pixels.
        unsigned char colpalette;   // Specifies number of colors in the color palette. Should be 0 if the image does not use a color palette.
        unsigned char reserved;     // Reserved. Should be 0.
        unsigned short planes;      // In ICO format: Specifies color planes. Should be 0 or 1.
        // In CUR format: Specifies the horizontal coordinates of the hotspot in number of pixels from the left.
        unsigned short bpp;         // In ICO format: Specifies bits per pixel. [Notes 4]
        // In CUR format: Specifies the vertical coordinates of the hotspot in number of pixels from the top.
        unsigned int size;          // Specifies the size of the image's data in bytes
        unsigned int offset;        // Specifies the offset of BMP or PNG data from the beginning of the ICO/CUR file
    } IcoDirEntry;

    FILE *icoFile = fopen(filename, "rb");

    if (!icoFile) return images;

    // Load .ico information
    IcoHeader icoHeader = { 0 };
    fread(&icoHeader, 1, sizeof(IcoHeader), icoFile);

    *count = icoHeader.imageCount;

    IcoDirEntry *icoDirEntry = (IcoDirEntry *)RL_CALLOC(icoHeader.imageCount, sizeof(IcoDirEntry));

    for (int i = 0; i < icoHeader.imageCount; i++) fread(&icoDirEntry[i], 1, sizeof(IcoDirEntry), icoFile);

    for (int i = 0; i < icoHeader.imageCount; i++)
    {
        char *icoImageData = (char *)RL_CALLOC(icoDirEntry[i].size, 1);
        fread(icoImageData, icoDirEntry[i].size, 1, icoFile);    // Read icon image data

        SaveFileData(TextFormat("_ico_%d.dat", i), icoImageData, icoDirEntry[i].size);

        // Check if image data starts with DIB data structure
        bool isDib = icoImageData[0] == 0x28;

        // Choose file format
        const char *format = (isDib) ? ".bmp" : ".png";
        
        printf("[%s] is dib: %d (%s)\n", filename, isDib, format);

        // Reading image data from memory buffer
        RSBAddElementImage(images,
            LoadImageFromMemory(format, (const unsigned char *)icoImageData, icoDirEntry[i].size)
        );

        RL_FREE(icoImageData);
    }

    RL_FREE(icoDirEntry);

    fclose(icoFile);

    return images;
}