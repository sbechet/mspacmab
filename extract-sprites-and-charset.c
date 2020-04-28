#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define BYTE_TO_BINARY_PATTERN "%c%c_%c%c_%c%c_%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


// Parts stolen from ` arcade.cxx` Copyright (c) 1997-2003,2004 Alessandro Scotti
char rom_5e[4096];
char rom_5f[4096];

unsigned char charmap[256*8*8];      // Character data for 256 8x8 characters
unsigned char spritemap[64*16*16];   // Sprite data for 64 16x16 sprites
unsigned char   palette[0x20];
unsigned char   color[0x100];
unsigned char wavedata[0x100];
unsigned        palette_[256];          // Color palette


void decodeCharByte( unsigned char b, unsigned char * charbuf, int charx, int chary, int charwidth )
{
    for( int i=3; i>=0; i-- ) {
        charbuf[charx+(chary+i)*charwidth] = (b & 1) | ((b >> 3) & 2);
        b >>= 1;
        // printf("x=%d, y=%d\n", charx, chary+i);
    }
}

void decodeCharLine( unsigned char * src, unsigned char * charbuf, int charx, int chary, int charwidth )
{
    // printf("linestart\n");
    for( int x=7; x>=0; x-- ) {
        decodeCharByte( *src++, charbuf, x+charx, chary, charwidth );
    }
}

void decodeCharSet( unsigned char * mem, unsigned char * charset )
{
    for( int i=0; i<256; i++ ) {
        unsigned char * src = mem + 16*i;
        unsigned char * dst = charset + 64*i;

        decodeCharLine( src,   dst, 0, 4, 8 );
        decodeCharLine( src+8, dst, 0, 0, 8 );
    }
}

void decodeSprites( unsigned char * mem, unsigned char * sprite_data )
{
    for( int i=0; i<64; i++ ) {
        unsigned char * src = mem + i*64;
        unsigned char * dst = sprite_data + 256*i;

        decodeCharLine( src   , dst, 8, 12, 16 );
        decodeCharLine( src+ 8, dst, 8,  0, 16 );
        decodeCharLine( src+16, dst, 8,  4, 16 );
        decodeCharLine( src+24, dst, 8,  8, 16 );
        decodeCharLine( src+32, dst, 0, 12, 16 );
        decodeCharLine( src+40, dst, 0,  0, 16 );
        decodeCharLine( src+48, dst, 0,  4, 16 );
        decodeCharLine( src+56, dst, 0,  8, 16 );
    }
}

/*
    Decode one byte from the encoded color palette.

    An encoded palette byte contains RGB information bit-packed as follows:
        
          bit: 7 6 5 4 3 2 1 0
        color: b b g g g r r r
*/
unsigned decodePaletteByte( unsigned char value )
{
    unsigned    bit0, bit1, bit2;
    unsigned    red, green, blue;

	bit0 = (value >> 0) & 0x01;
	bit1 = (value >> 1) & 0x01;
	bit2 = (value >> 2) & 0x01;
	red = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

    bit0 = (value >> 3) & 0x01;
	bit1 = (value >> 4) & 0x01;
	bit2 = (value >> 5) & 0x01;
	green = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

    bit0 = 0;
	bit1 = (value >> 6) & 0x01;
	bit2 = (value >> 7) & 0x01;
    blue = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

    // output : 0x00RRGGBB
    return (red << 16 ) | (green << 8) | blue;
}

void setColorROMs( const unsigned char * palette, const unsigned char * color )
{
    unsigned decoded_palette[0x20];

    int i;

    for( i=0x00; i<0x20; i++ ) {
        decoded_palette[i] = decodePaletteByte( palette[i] );
    }

    for( i=0; i<256; i++ ) {
        palette_[i] = decoded_palette[ color[i] & 0x0F ];
    }
}


void main(void)
{

    /********************************************/

    /* 8x8x256 */
    int f = open("5e", O_RDONLY);
    read(f, rom_5e, 4096);
    close(f);

    /*
        First One :
        ii vv abcd efgh -> ae bf cg dh -> ijkl

        00 cc 1100 1100 -> 11 11 00 00 -> 3300
        01 ee 1110 1110 -> 11 11 11 00 -> 3330
        02 11 0001 0001 -> 00 00 00 11 -> 0003
        03 11 0001 0001 -> 00 00 00 11 -> 0003
        04 33 0011 0011 -> 00 00 11 11 -> 0033
        05 ee 1110 1110 -> 11 11 11 00 -> 3330
        06 cc 1100 1100 -> 11 11 00 00 -> 3300
        07 00 0000 0000 -> 00 00 00 00 -> 0000

        08 11 0001 0001 -> 00 00 00 11 -> 0003
        09 33 0011 0011 -> 00 00 11 11 -> 0033
        0a 66 0110 0110 -> 00 11 11 00 -> 0330
        0b 44 0100 0100 -> 00 11 00 00 -> 0300
        0c 44 0100 0100 -> 00 11 00 00 -> 0300
        0d 33 0011 0011 -> 00 00 11 11 -> 0033
        0e 11 0001 0001 -> 00 00 00 11 -> 0003
        0f 00 0000 0000 -> 00 00 00 00 -> 0000

        90° rotated map : 
        0f 07 : 00000000
        0e 06 : 00033300
        0d 05 : 00333330
        0c 04 : 03000033
        0b 03 : 03000003
        0a 02 : 03300003
        09 01 : 00333330
        08 00 : 00033300

        must give:
        00000000,
        00033300,
        00300330,
        03300033,
        03300033,
        03300033,
        00330030,
        00033300,


    */
    decodeCharSet( rom_5e, charmap);

    printf("/// Each tile entry are 8x8 pixels size. 2-bit per pixel.\n");
    printf("const TILE: [ [u16; 8]; 256] = [\n");
    for (int i=0; i<256; i++) {
        printf("[\n");
        for (int y=0; y<8; y++) {
            printf("    ");
            // standard computing width 16 bits encoding
            unsigned int width = 0;
            for (int x=0; x<8; x++) {
                width |= (((unsigned int)charmap[i*8*8 + y*8 + x]) << 14) >> 2*x;
                // printf("%d,", charmap[i*8*8 + y*8 + x] );
                // printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(charmap[i*8*8 + y*8 + x]) );
                charmap[i*8*8 + y*8 + x] *= 64;
            }
            // printf("0x%04x,\n", width);
            printf("0b"BYTE_TO_BINARY_PATTERN"_"BYTE_TO_BINARY_PATTERN",\n", 
                BYTE_TO_BINARY(width>>8), BYTE_TO_BINARY(width));

        }
        printf("    ],");
    }
    printf("\n];\n");

    f = open("5e.ok", O_WRONLY|O_CREAT, 0644);
    write(f, charmap, 256*8*8);
    close(f);


    /********************************************/

    /* 16x16x64 */
    f = open("5f", O_RDONLY);
    read(f, rom_5f, 4096);
    close(f);

    decodeSprites( rom_5f, spritemap);

    printf("\n");
    printf("/// each sprite entry are 16x16 pixels size. 2-bit per pixel.\n");
    printf("const SPRITE: [ [u32; 16]; 64] = [\n");
    for (int i=0; i<64; i++) {
        printf("[\n");
        for (int y=0; y<16; y++) {
            printf("    ");
            // standard computing width 32 bits encoding
            unsigned int width = 0;
            for (int x=0; x<16; x++) {
                width |= (((unsigned int)spritemap[i*16*16 + y*16 + x]) << 30) >> 2*x;
                spritemap[i*16*16 + y*16 + x] *= 64;
            }
            printf("0b"BYTE_TO_BINARY_PATTERN"_"BYTE_TO_BINARY_PATTERN"_"BYTE_TO_BINARY_PATTERN"_"BYTE_TO_BINARY_PATTERN",\n", 
                BYTE_TO_BINARY(width>>24), BYTE_TO_BINARY(width>>16),
                BYTE_TO_BINARY(width>>8), BYTE_TO_BINARY(width));
        }
        printf("    ],");
    }
    printf("\n];\n");

    f = open("5f.ok", O_WRONLY|O_CREAT, 0644);
    write(f, spritemap, 16*16*64);
    close(f);

    /********************************************/

    f = open("82s126.4a", O_RDONLY);
    read(f, color, 256);
    close(f);

    f = open("82s123.7f", O_RDONLY);
    read(f, palette, 32);
    close(f);

    setColorROMs(palette, color);

    printf("\n");
    printf("/// each palette_ entry contains a color in RGB format encoded as 0x00rrggbb.\n");
    printf("const PALETTE: [u32; 256] = [\n");
    for (int i=0; i<256; i++) {
        printf("    0x%08X,\n", palette_[i]);
    }
    printf("];\n");


    /********************************************/

    f = open("82s126.1m", O_RDONLY);
    read(f, wavedata, 256);
    close(f);

    printf("\n");
    printf("/// Namco 3-channel Wave Sound Generator wave data (8 waveforms with 32 4-bit entries each)\n");
    printf("const WAVEDATA: [ [u8; 32]; 8] = [\n");

    for (int i=0; i<8; i++) {
        printf("    [");
        for (int x=0; x<32; x++) {
            printf("%d, ", wavedata[i*32 + x]);
        }
        printf("],\n");
    }
    printf("];\n");


}