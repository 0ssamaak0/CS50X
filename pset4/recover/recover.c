#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t Byte;


int main(int argc, char *argv[])
{
    int jpgsnum = 0;
    char filename[500];
    int i = 0;
    Byte B512[512];
    if (argc != 2)
    {
        printf("Enter something!");
        return 1;
    }
    FILE *f = fopen(argv[1], "r"); 
    sprintf(filename, "%03i.jpg", jpgsnum);
    i = 0;
    FILE *img[50];
    img[i] = fopen(filename, "w");
    
    while (fread(B512, 512, 1, f) != 0)
    {
        if ((B512[0] == 0xff) && (B512[1] == 0xd8) && (B512[2] == 0xff) && ((B512[3] & 0xf0) == 0xe0))
        {
            fwrite(B512, 512, 1, img[i]);
            break;
        } 
    }
    while (fread(B512, 512, 1, f) != 0)
    {
        if ((B512[0] == 0xff) && (B512[1] == 0xd8) && (B512[2] == 0xff) && ((B512[3] & 0xf0) == 0xe0))
        {
            fclose(img[i]);
            jpgsnum ++;
            i ++;
            sprintf(filename, "%03i.jpg", jpgsnum);
            img[i] = fopen(filename, "w");
            fwrite(B512, 512, 1, img[i]);
        }
        else 
        {
            fwrite(B512, 512, 1, img[i]);
        }
    }
    fclose(f);
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//     while (fread(B512,512,1,f) != 0)
//     {
//         if ((B512[0] == 0xff) && (B512[1] == 0xd8) && (B512[2] == 0xff) && ((B512[3] & 0xf0 ) == 0xe0) && (i  == 0))
//         {
//             fwrite (B512,512, 1 , img);
//             i++;
//         }
//     }
//     while (fread(B512,512,1,f) != 0)
//     {
//             if ((B512[0] == 0xff) && (B512[1] == 0xd8) && (B512[2] == 0xff) && ((B512[3] & 0xf0 ) == 0xe0) && (i  != 0))
//             {
//                 if (i ==1)
//                 {
//                     fclose(img);
//                     sprintf(filename, "%03i.jpg", jpgsnum);
//                     FILE *img2 = fopen(filename, "w");
//                     fwrite (B512,512, 1 , img2);
//                     continue;
//                 }
//                 jpgsnum += 1; 
//                 sprintf(filename, "%03i.jpg", jpgsnum);
//                 FILE *img2 = fopen(filename, "w");
//                 fwrite (B512,512, 1 , img2);
//             }
//             else 
//             {
//                 fwrite (B512,512, 1 , img);    
//             }
//             i++;
//         }
//     fclose(f);
// }  
    
    
