# c\_bitmap
A simple bare-bones implementation of bitmaps with BITMAPINFOHEADER DIB header

## Motive

I wanted something to make images using a low level language. After a quick
google search, I discovered that the bitmap format is simple enough and I
challenged myself to create a simple implementation.

The implementation is based mostly on the Wikipedia article here:
<https://en.wikipedia.org/wiki/BMP_file_format>

# Limitations

- No support for other formats like those found here:
  <https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header)>
- Not endianess agnostic. 
- No support for non required fields like those described here:
  <https://en.wikipedia.org/wiki/BMP_file_format#File_structure>
- No compression support
- No "read bitmap" support
- ...

# TODOs

### Higher priority:

- Reading a bitmap
- Make it endianess agnostic
- Provide for creating the image array for all Bits per Pixel formats

### Lower Priority:

Any other limitation listed above

# Examples

Example code of how to use the library can be found at the directory:
`src/test/`

