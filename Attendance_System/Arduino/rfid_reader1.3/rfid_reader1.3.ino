#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#if defined(ESP32)
#define SD_CS     5
#else
#define SD_CS     10
#endif
#define PALETTEDEPTH   0
char namebuf[32] = "/bitmaps/";
File root;
int pathlen;
int count = 0;
char input[24]; 
boolean flag = 0; 
int count1=0;
int a1=0, a2=0;
void setup()
{
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
    uint16_t ID;
    Serial.begin(9600);
    Serial.print("Show BMP files on TFT with ID:0x");
    ID = tft.readID();
    Serial.println(ID, HEX);
    if (ID == 0x0D3D3) ID = 0x9481;
    tft.begin(ID);
    tft.fillScreen(0x001F);
    tft.setTextColor(0xFFFF, 0x0000);
    bool good = SD.begin(SD_CS);
    if (!good) {
        Serial.print(F("cannot start SD"));
        while (1);
    }
    root = SD.open(namebuf);
    pathlen = strlen(namebuf);
    int f;
    for(f=0;f<=23;f++)
    {
    input[f]='0';
    }
    
}

void loop()
{
  int a=18; 
  long int c=0;
if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 24)
      {
         input[count] = Serial.read();
         count++;
         delay(5);
      }
      Serial.print(input); 

   }
          char *nm = namebuf + pathlen;
    File f = root.openNextFile();
    uint8_t ret;
    uint32_t start;
    if (f != NULL) {
#ifdef USE_SDFAT
        f.getName(nm, 32 - pathlen);
#else
        strcpy(nm, (char *)f.name());
#endif
        f.close();
        strlwr(nm);


         if(namebuf[9]==input[5]&&namebuf[10]==input[6]&&namebuf[11]==input[7]&&namebuf[12]==input[8]&&namebuf[13]==input[9]&&namebuf[14]==input[10])
         {
            Serial.print(namebuf);
            Serial.print(F(" - "));
            if(input[5]!='0'&&input[6]!='0'&&input[7]!='0'&&input[8]!='0'&&input[9]!='0'&&(input[10]!='0'||input[10]!='1'))
            {
            tft.fillScreen(0);
            }
            else if(input[5]=='0'&&input[6]=='0'&&input[7]=='0'&&input[8]=='0'&&input[9]=='0'&&input[10]=='2')
            {
            tft.fillScreen(0);
            }
            start = millis();
            ret = showBMP(namebuf, 5, 5);
            
            switch (ret) {
                case 0:
                    Serial.print(millis() - start);
                    Serial.println(F("ms"));
                    
                    while(a!=19)
                     {
                      if((Serial.available()||c>=500)/*&&input[5]!='0'&&input[6]!='0'&&input[7]!='0'&&input[8]!='0'&&input[9]!='0'&&input[10]!='0'*/){
                        a =19;
                        c=0;
                        if(a1==0&&a2==0){
                        input[5]='0';
                        input[6]='0';
                        input[7]='0';
                        input[8]='0';
                        input[9]='0';
                        input[10]='0';
                        a2=10;
                        a1=10;
                        count1=0;
                        }
                        else if(a2==10&&a1==10){
                        input[5]='0';
                        input[6]='0';
                        input[7]='0';
                        input[8]='0';
                        input[9]='0';
                        input[10]='1';
                        a1=0;
                        a2=0;
                        count1=0;
                        }
                        }
                        c++;
                        //count1=0;
                        delay(10);
                         }
                    break;
                case 1:
                    Serial.println(F("bad position"));
                    break;
                case 2:
                    Serial.println(F("bad BMP ID"));
                    break;
                case 3:
                    Serial.println(F("wrong number of planes"));
                    break;
                case 4:
                    Serial.println(F("unsupported BMP format"));
                    break;
                case 5:
                    Serial.println(F("unsupported palette"));
                    break;
                default:
                    Serial.println(F("unknown"));
                    break;
            }
          }



          else if(count1>12)
         {
                      input[5]='0';
                        input[6]='0';
                        input[7]='0';
                        input[8]='0';
                        input[9]='0';
                        input[10]='2';}
                }
    else root.rewindDirectory();
    count1++;
    if(count1>13)
    {
      count1=0;
    }
}
#define BMPIMAGEOFFSET 54

#define BUFFPIXEL      20

uint16_t read16(File& f) {
    uint16_t result;         // read little-endian
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}

uint32_t read32(File& f) {
    uint32_t result;
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}

uint8_t showBMP(char *nm, int x, int y)
{
    File bmpFile;
    int bmpWidth, bmpHeight;    // W+H in pixels
    uint8_t bmpDepth;           // Bit depth (currently must be 24, 16, 8, 4, 1)
    uint32_t bmpImageoffset;    // Start of image data in file
    uint32_t rowSize;           // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel in buffer (R+G+B per pixel)
    uint16_t lcdbuffer[(1 << PALETTEDEPTH) + BUFFPIXEL], *palette = NULL;
    uint8_t bitmask, bitshift;
    boolean flip = true;        // BMP is stored bottom-to-top
    int w, h, row, col, lcdbufsiz = (1 << PALETTEDEPTH) + BUFFPIXEL, buffidx;
    uint32_t pos;               // seek position
    boolean is565 = false;      //

    uint16_t bmpID;
    uint16_t n;                 // blocks read
    uint8_t ret;

    if ((x >= tft.width()) || (y >= tft.height()))
        return 1;               // off screen

    bmpFile = SD.open(nm);      // Parse BMP header
    bmpID = read16(bmpFile);    // BMP signature
    (void) read32(bmpFile);     // Read & ignore file size
    (void) read32(bmpFile);     // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile);       // Start of image data
    (void) read32(bmpFile);     // Read & ignore DIB header size
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    n = read16(bmpFile);        // # planes -- must be '1'
    bmpDepth = read16(bmpFile); // bits per pixel
    pos = read32(bmpFile);      // format
    if (bmpID != 0x4D42) ret = 2; // bad ID
    else if (n != 1) ret = 3;   // too many planes
    else if (pos != 0 && pos != 3) ret = 4; // format: 0 = uncompressed, 3 = 565
    else if (bmpDepth < 16 && bmpDepth > PALETTEDEPTH) ret = 5; // palette 
    else {
        bool first = true;
        is565 = (pos == 3);               // ?already in 16-bit format
        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * bmpDepth / 8 + 3) & ~3;
        if (bmpHeight < 0) {              // If negative, image is in top-down order.
            bmpHeight = -bmpHeight;
            flip = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        if ((x + w) >= tft.width())       // Crop area to be loaded
            w = tft.width() - x;
        if ((y + h) >= tft.height())      //
            h = tft.height() - y;

        if (bmpDepth <= PALETTEDEPTH) {   // these modes have separate palette
            bmpFile.seek(BMPIMAGEOFFSET); //palette is always @ 54
            bitmask = 0xFF;
            if (bmpDepth < 8)
                bitmask >>= bmpDepth;
            bitshift = 8 - bmpDepth;
            n = 1 << bmpDepth;
            lcdbufsiz -= n;
            palette = lcdbuffer + lcdbufsiz;
            for (col = 0; col < n; col++) {
                pos = read32(bmpFile);    //map palette to 5-6-5
                palette[col] = ((pos & 0x0000F8) >> 3) | ((pos & 0x00FC00) >> 5) | ((pos & 0xF80000) >> 8);
            }
        }

                tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
        for (row = 0; row < h; row++) {
            uint8_t r, g, b, *sdptr;
            int lcdidx, lcdleft;
            if (flip)   // Bitmap is stored bottom-to-top order (normal BMP)
                pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
            else        // Bitmap is stored top-to-bottom
                pos = bmpImageoffset + row * rowSize;
            if (bmpFile.position() != pos) { // Need seek?
                bmpFile.seek(pos);
                buffidx = sizeof(sdbuffer); // Force buffer reload
            }

            for (col = 0; col < w; ) {  //pixels in row
                lcdleft = w - col;
                if (lcdleft > lcdbufsiz) lcdleft = lcdbufsiz;
                for (lcdidx = 0; lcdidx < lcdleft; lcdidx++) { // buffer at a time
                    uint16_t color;
                    // Time to read more pixel data?
                    if (buffidx >= sizeof(sdbuffer)) { // Indeed
                        bmpFile.read(sdbuffer, sizeof(sdbuffer));
                        buffidx = 0; // Set index to beginning
                        r = 0;
                    }
                    switch (bmpDepth) {          // Convert pixel from BMP to TFT format
                        case 24:
                            b = sdbuffer[buffidx++];
                            g = sdbuffer[buffidx++];
                            r = sdbuffer[buffidx++];
                            color = tft.color565(r, g, b);
                            break;
                        case 16:
                            b = sdbuffer[buffidx++];
                            r = sdbuffer[buffidx++];
                            if (is565)
                                color = (r << 8) | (b);
                            else
                                color = (r << 9) | ((b & 0xE0) << 1) | (b & 0x1F);
                            break;
                        case 1:
                        case 4:
                        case 8:
                            if (r == 0)
                                b = sdbuffer[buffidx++], r = 8;
                            color = palette[(b >> bitshift) & bitmask];
                            r -= bmpDepth;
                            b <<= bmpDepth;
                            break;
                    }
                    lcdbuffer[lcdidx] = color;

                }
                tft.pushColors(lcdbuffer, lcdidx, first);
                first = false;
                col += lcdidx;
            }           // end cols
        }               // end rows
        tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1); //restore full screen
        ret = 0;        // good render
    }
    bmpFile.close();
    return (ret);
}

