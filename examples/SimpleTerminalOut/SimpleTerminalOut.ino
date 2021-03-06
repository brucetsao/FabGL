/*
  Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com) - www.fabgl.com
  Copyright (c) 2019 Fabrizio Di Vittorio.
  All rights reserved.

  This file is part of FabGL Library.

  FabGL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FabGL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FabGL.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "fabgl.h"

#include "vtanimations.h"



/* * * *  C O N F I G U R A T I O N  * * * */

// select one color configuration
#define USE_8_COLORS  0
#define USE_64_COLORS 1

// indicate VGA GPIOs to use for selected color configuration
#if USE_8_COLORS
  #define VGA_RED    GPIO_NUM_22
  #define VGA_GREEN  GPIO_NUM_21
  #define VGA_BLUE   GPIO_NUM_19
  #define VGA_HSYNC  GPIO_NUM_18
  #define VGA_VSYNC  GPIO_NUM_5
#elif USE_64_COLORS
  #define VGA_RED1   GPIO_NUM_22
  #define VGA_RED0   GPIO_NUM_21
  #define VGA_GREEN1 GPIO_NUM_19
  #define VGA_GREEN0 GPIO_NUM_18
  #define VGA_BLUE1  GPIO_NUM_5
  #define VGA_BLUE0  GPIO_NUM_4
  #define VGA_HSYNC  GPIO_NUM_23
  #define VGA_VSYNC  GPIO_NUM_15
#endif

/* * * *  E N D   O F   C O N F I G U R A T I O N  * * * */



TerminalClass Terminal;


void setup()
{
  Serial.begin(115200); delay(500); Serial.write("\n\n\n"); // DEBUG ONLY

  #if USE_8_COLORS
  VGAController.begin(VGA_RED, VGA_GREEN, VGA_BLUE, VGA_HSYNC, VGA_VSYNC);
  #elif USE_64_COLORS
  VGAController.begin(VGA_RED1, VGA_RED0, VGA_GREEN1, VGA_GREEN0, VGA_BLUE1, VGA_BLUE0, VGA_HSYNC, VGA_VSYNC);
  #endif

  VGAController.setResolution(VGA_640x350_70HzAlt1, 640, 350);
  //VGAController.setResolution(VGA_640x240_60Hz);    // select to have more free memory

  // this speed-up display but may generate flickering
  VGAController.enableBackgroundPrimitiveExecution(false);

  Terminal.begin();
  Terminal.setLogStream(Serial);  // DEBUG ONLY

  Terminal.enableCursor(true);
}


void slowPrintf(const char * format, ...)
{
  va_list ap;
  va_start(ap, format);
  int size = vsnprintf(NULL, 0, format, ap) + 1;
  if (size > 0) {
    char buf[size + 1];
    vsnprintf(buf, size, format, ap);
    for (int i = 0; i < size; ++i) {
      Terminal.write(buf[i]);
      delay(25);
    }
  }
  va_end(ap);
}


void demo1()
{
  Terminal.write("\e[40;32m"); // background: black, foreground: green
  Terminal.write("\e[2J");     // clear screen
  Terminal.write("\e[1;1H");   // move cursor to 1,1
  slowPrintf("* * * * W E L C O M E   T O   F a b G L * * * *\r\n");
  slowPrintf("2019 by Fabrizio Di Vittorio  -   www.fabgl.com\r\n");
  slowPrintf("===============================================\r\n\n");
  slowPrintf("This is a VGA Controller, PS2 Mouse and Keyboard Controller, Graphics Library,  Game Engine and ANSI/VT Terminal for the ESP32\r\n\n");
  slowPrintf("Current settings\r\n");
  slowPrintf("Screen Size   : %d x %d\r\n", VGAController.getScreenWidth(), VGAController.getScreenHeight());
  slowPrintf("Terminal Size : %d x %d\r\n", Terminal.getColumns(), Terminal.getRows());
  slowPrintf("Free Memory   : %d bytes\r\n\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
}

void demo2()
{
  Terminal.write("\e[40;32m"); // background: black, foreground: green
  slowPrintf("8 or 64 colors supported (depends by GPIOs used)\r\n");
  slowPrintf("ANSI colors:\r\n");
  // foregrounds
  Terminal.write("\e[31mRED\t"); delay(500);
  Terminal.write("\e[32mGREEN\t"); delay(500);
  Terminal.write("\e[33mYELLOW\t"); delay(500);
  Terminal.write("\e[34mBLUE\t"); delay(500);
  Terminal.write("\e[35mMAGENTA\t"); delay(500);
  Terminal.write("\e[36mCYAN\t"); delay(500);
  Terminal.write("\e[37mWHITE\r\n"); delay(500);
  Terminal.write("\e[90mHBLACK\t"); delay(500);
  Terminal.write("\e[91mHRED\t"); delay(500);
  Terminal.write("\e[92mHGREEN\t"); delay(500);
  Terminal.write("\e[93mHYELLOW\t"); delay(500);
  Terminal.write("\e[94mHBLUE\t"); delay(500);
  Terminal.write("\e[95mHMAGENTA\t"); delay(500);
  Terminal.write("\e[96mHCYAN\t"); delay(500);
  Terminal.write("\e[97mHWHITE\r\n"); delay(500);
  // backgrounds
  Terminal.write("\e[40mBLACK\t"); delay(500);
  Terminal.write("\e[41mRED\e[40m\t"); delay(500);
  Terminal.write("\e[42mGREEN\e[40m\t"); delay(500);
  Terminal.write("\e[43mYELLOW\e[40m\t"); delay(500);
  Terminal.write("\e[44mBLUE\e[40m\t"); delay(500);
  Terminal.write("\e[45mMAGENTA\e[40m\t"); delay(500);
  Terminal.write("\e[46mCYAN\e[40m\t"); delay(500);
  Terminal.write("\e[47mWHITE\e[40m\r\n"); delay(500);
  Terminal.write("\e[100mHBLACK\e[40m\t"); delay(500);
  Terminal.write("\e[101mHRED\e[40m\t"); delay(500);
  Terminal.write("\e[102mHGREEN\e[40m\t"); delay(500);
  Terminal.write("\e[103mHYELLOW\e[40m\t"); delay(500);
  Terminal.write("\e[104mHBLUE\e[40m\t"); delay(500);
  Terminal.write("\e[105mHMAGENTA\e[40m\t"); delay(500);
  Terminal.write("\e[106mHCYAN\e[40m\r\n"); delay(500);
}

void demo3()
{
  Terminal.write("\e[40;32m"); // background: black, foreground: green
  slowPrintf("\nSupported styles:\r\n");
  slowPrintf("\e[0mNormal\r\n");
  slowPrintf("\e[1mBold\e[0m\r\n");
  slowPrintf("\e[3mItalic\e[0m\r\n");
  slowPrintf("\e[4mUnderlined\e[0m\r\n");
  slowPrintf("\e[5mBlink\e[0m\r\n");
  slowPrintf("\e[7mInverse\e[0m\r\n");
  slowPrintf("\e[1;3mBoldItalic\e[0m\r\n");
  slowPrintf("\e[1;3;4mBoldItalicUnderlined\e[0m\r\n");
  slowPrintf("\e[1;3;4;5mBoldItalicUnderlinedBlinking\e[0m\r\n");
  slowPrintf("\e[1;3;4;5;7mBoldItalicUnderlinedBlinkingInverse\e[0m\r\n");
  slowPrintf("\e#6Double Width Line\r\n");
  slowPrintf("\e#6\e#3Double Height Line\r\n"); // top half
  slowPrintf("\e#6\e#4Double Height Line\r\n"); // bottom half
}

void demo4()
{
  Terminal.write("\e[40;32m"); // background: black, foreground: green
  slowPrintf("\nMixed text and graphics:\r\n");
  slowPrintf("Points...\r\n");
  for (int i = 0; i < 500; ++i) {
    Canvas.setPenColor(random(4), random(4), random(4));
    Canvas.setPixel(random(640), random(350));
    delay(15);
  }
  delay(500);
  slowPrintf("\e[40;32mLines...\r\n");
  for (int i = 0; i < 50; ++i) {
    Canvas.setPenColor(random(4), random(4), random(4));
    Canvas.drawLine(random(640), random(350), random(640), random(350));
    delay(50);
  }
  delay(500);
  slowPrintf("\e[40;32mRectangles...\r\n");
  for (int i = 0; i < 50; ++i) {
    Canvas.setPenColor(random(4), random(4), random(4));
    Canvas.drawRectangle(random(640), random(350), random(640), random(350));
    delay(50);
  }
  delay(500);
  slowPrintf("\e[40;32mEllipses...\r\n");
  for (int i = 0; i < 50; ++i) {
    Canvas.setPenColor(random(4), random(4), random(4));
    Canvas.drawEllipse(random(640), random(350), random(640), random(350));
    delay(50);
  }
  for (int i = 0; i < 30; ++i) {
    Terminal.write("\e[40;32mScrolling...\r\n");
    delay(250);
  }
}

void demo5()
{
  Terminal.write("\e[40;93m"); // background: black, foreground: yellow
  Terminal.write("\e[2J");     // clear screen
  slowPrintf("\e[10;56HFast Rendering");
  slowPrintf("\e[12;50HThis is a VT/ANSI animation");
  Terminal.write("\e[20h"); // automatic new line on
  Terminal.write("\e[92m"); // light-green
  Terminal.enableCursor(false);
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < sizeof(vt_animation); ++i) {
      Terminal.write(vt_animation[i]);
      if (vt_animation[i] == 0x1B && vt_animation[i + 1] == 0x5B && vt_animation[i + 2] == 0x48)
        delay(120); // pause 100ms every frame
    }
  }
  Terminal.enableCursor(true);
  Terminal.write("\e[20l"); // automatic new line off
}

void loop()
{
  delay(1000);
  demo1();
  delay(4000);
  demo2();
  delay(4000);
  demo3();
  delay(4000);
  demo4();
  delay(4000);
  demo5();
  delay(4000);
}
