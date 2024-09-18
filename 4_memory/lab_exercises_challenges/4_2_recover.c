#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK = 512;

int isJpeg(BYTE buff[]);
void writeBuffer(BYTE *buff, FILE *stream);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage ./recover image");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.", argv[1]);
    }

    // Initialize total jpegs created variable
    int jpegCount = 0;
    char *filename = malloc(8);

    // Buffer to direct block info
    BYTE buffer[BLOCK];

    // Declare img file
    FILE *img;

    // Iterare trhough memory card in 512 bytes at a time until it ends
    while(fread(&buffer, sizeof(BYTE), BLOCK, card))
    {
        // Check if is the start of a jpeg
        if (isJpeg(buffer) == 1) {
            // If it's the first jpeg
            if (jpegCount > 0) {
                // Close past jpeg
                fclose(img);
            }
            // Config new filename and open new jpg file
            sprintf(filename, "%03i.jpg", jpegCount);
            img = fopen(filename, "w");
            // Write current buffer to file
            writeBuffer(buffer, img);
            jpegCount++;
            continue;
        }
        // If jpeg > 0 and it's not a jpeg keep writing to current jpeg
        if (jpegCount > 0) {
            // Write current buffer
            writeBuffer(buffer, img);
        }
    }
    fclose(card);
    fclose(img);
    free(filename);
    return 0;
}

// Helper function to check if block is the start of a jpeg
int isJpeg(BYTE buff[]) {
    if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] & 0xf0) == 0xe0) {
        return 1;
    }
    return 0;
}

// Helper function to reduce code smell when writing to a file
void writeBuffer(BYTE *buff, FILE *stream) {
    fwrite(buff, sizeof(BYTE), BLOCK, stream);
}