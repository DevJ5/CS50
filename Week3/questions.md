# Questions

## What's `stdint.h`?

TODO

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The whole point is to write implementation-independent code. unsigned char is not guaranteed to be an 8-bit type.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1 unsigned
DWORD = 4 unsigned
LONG = 4 signed
WORD = 2 unsigned

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x 42 4D -> BM

## What's the difference between `bfSize` and `biSize`?

bfSize: The size, in bytes, of the bitmap file.
biSize: The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

Permission issues, file does not exist. Check errno if fopen() == null.

## Why is the third argument to `fread` always `1` in our code?

Cause it is 1 structure

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Moves the file pointer to a new location that is offset from origin

## What is `SEEK_CUR`?

Starts where the file pointer is currently
