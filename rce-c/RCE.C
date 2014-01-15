/****************************************************************************
** Warning, do not run this through the IDE                                **
*****************************************************************************
** Demonstration of a simple raycasting engine                             **
**  by Steven H Don                                                        **
**                                                                         **
** This is the TurboC source code of a simple raycasting engine.           **
** It is merely meant as an example for you to help building your own.     **
** You may use it in your own code though, but please credit me.           **
**                                                                         **
** For questions, feel free to e-mail me.                                  **
**                                                                         **
**    shd@geocities.com                                                    **
**    http://shd.cjb.net                                                   **
**                                                                         **
****************************************************************************/
//Include files
#include <conio.h>
#include <dos.h>
#include <malloc.h>
#include <math.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#ifdef __DJGPP
  #include <SYS/nearptr.h>
#endif
//Values for several angles
#define ANGLE_0       0
#define ANGLE_30    171
#define ANGLE_45    256
#define ANGLE_60    341
#define ANGLE_90    512
#define ANGLE_180  1024
#define ANGLE_270  1536
#define ANGLE_360  2048

//Cursor key scancodes
#define CUp       18432
#define CDown     20480
#define CLeft     19200
#define CRight    19712

 //maps
  unsigned char xGrid [4356];
  unsigned char yGrid [4356];
  unsigned char  Grid [4096];
 //Tables
  long         *CosineTable;
  long         *SineTable;
  long	       *TangentTable;
  long	       *iTangentTable;
  long 	       *NextXTable;
  long         *NextYTable;
  unsigned int HeightTable   [3073];
  short int    fv            [ 360];
 //File handle
  FILE             *RayCastingFile;
 //Off-screen buffer
  #ifdef __DJGPP
    unsigned char Buffer [64000];
    unsigned char *Screen;
  #else
    unsigned char far *Buffer;
    unsigned char far *Screen;
  #endif
 //Global counter
  int                      Counter;
 //Player coordinates and viewing angle
  long                           x;
  long                           y;
  long                       Angle;
 //Keyboard input receiver
  unsigned int                 Key;
 //Distance counters
  long	                      xDst;
  long	                      yDst;

/**************************************************************************
** Set to VGA 320x200 256 colours                                        **
**************************************************************************/
void VGAScreen()
{
  union REGS r;
  r.h.ah = 0;
  r.h.al = 0x13;
  int86(0x10, &r, &r);
}

/**************************************************************************
** Set to text mode                                                      **
**************************************************************************/
void TextScreen()
{
  union REGS r;
  r.h.ah = 0;
  r.h.al = 0x3;
  int86(0x10, &r, &r);
}

/**************************************************************************
** Read a key from the keyboard buffer                                   **
**************************************************************************/
unsigned int Inkey()
{
  unsigned int Temp = 0;

  if (kbhit()) {
    Temp = getch();
    //If extended key, read in second half
    if (!Temp) Temp = getch() << 8;
  }
  return (Temp);
}

/**************************************************************************
** Draw vertical line                                                    **
**************************************************************************/
void DrawLine(int x, int y1, int y2, unsigned char c)
{
  unsigned int OffSet;
  unsigned int EndOffSet;

  //Clip top of screen
  if (y1 < 0) y1 = 0;
  //Clip bottom of screen
  if (y2 > 199) y2 = 199;
  //Offset at start of line
  OffSet    = (y1 << 8) + (y1 << 6) + x;
  //Offset at end of line
  EndOffSet = (y2 << 8) + (y2 << 6) + x;

  while (OffSet < EndOffSet) {
    //Set pixel
    Buffer[OffSet] = c;
    //Go to next scan line
    OffSet += 320;
  }

}

/**************************************************************************
** Load and calculate trigonometric tables.                              **
**************************************************************************/
void SetTables ()
{
  //Good estimate for pi
  float Pi = 4 * atan(1);
  float          Radians;
  //Display message
  printf("Calculating...");
  //Assign memory
  CosineTable = (long *)malloc (2048 << 2);
  SineTable = (long *)malloc (2048 << 2);
  TangentTable = (long *)malloc (2048 << 2);
  iTangentTable = (long *)malloc (2048 << 2);
  NextXTable = (long *)malloc (2048 << 2);
  NextYTable = (long *)malloc (2048 << 2);

  //Read field of view correction from file FOV.SSF which must be included
  RayCastingFile = fopen("FOV.SSF", "rb");
  fread(&fv, 720, 1, RayCastingFile);
  fclose(RayCastingFile);

  //Calculate other values
  for (Counter = ANGLE_0; Counter < ANGLE_360; Counter++) {
    //Convert angle to radians
      Radians = (Counter * Pi) / ANGLE_180;
    //Sine
      SineTable[Counter]    = (long)(sin(Radians) * 32768);
    //CoSine
      CosineTable[Counter]  = (long)(cos(Radians) * 32768);

    //Next Y value
    if (Counter != ANGLE_90 && Counter != ANGLE_270) {
      //Tangent
      TangentTable[Counter] = (long)(tan(Radians) * 32768);
      //Next Y value
      NextYTable[Counter] = labs ((long)(tan(Radians) * 32768 * 64));
    }

    //Next X value
    if (Counter != ANGLE_0 && Counter != ANGLE_180) {
      //Inverse tangent
      iTangentTable[Counter] = (long)(32768 / tan(Radians));
      //Next X value
      NextXTable[Counter] = labs ((long)(64 * 32768 / tan(Radians)));
      if (Counter == ANGLE_90 || Counter == ANGLE_270) {
        iTangentTable[Counter] = 0;
        NextXTable[Counter] = 0;
      }
    }
  }

  //Height table
  HeightTable[0] = 36000;
  for (Counter = 1; Counter < 3071; Counter++)
    HeightTable[Counter] = 12000 / Counter;
}

/**************************************************************************
** Make map            							 **
**************************************************************************/
void MakeMap()
{
  unsigned char tx;
  unsigned char ty;
  unsigned char  c;
  memset( Grid, 0, 4096);
  memset(xGrid, 0, 4356);
  memset(yGrid, 0, 4356);
  for (tx = 0; tx <= 16; tx++)
    for (ty = 0; ty <= 16; ty++) {
      //Select random colour
      #ifdef __DJGPP
        c = random () % 16 + 1;
      #else
        c = random(16) + 1;
      #endif
      //Fill the borders of a 16 by 16 block, max map size is 64 by 64
      if ((tx & 15) == 0 || (ty & 15) == 0)
	Grid[(ty << 6) + tx] = c;
      else
	Grid[(ty << 6) + tx] = 0;
    }

  //Place a few random blocks
  for (Counter = 0; Counter < 15; Counter++)
    #ifdef __DJGPP
      Grid[(random() % 16 << 6) + random() % 16] = random() % 16 + 1;
    #else
      Grid[(random(16) << 6) + random(16)] = random(16) + 1;
    #endif

  for (tx = 0; tx <= 16; tx++)
    for (ty = 0; ty <= 16; ty++) {
      //Make sure the X and Y walls are set up properly
      c = Grid[(ty << 6) + tx];
      if (c) {
	xGrid[(ty       << 6) + tx    ] = c;
	xGrid[(ty       << 6) + tx + 1] = c;
	yGrid[(ty       << 6) + tx    ] = c;
	yGrid[((ty + 1) << 6) + tx    ] = c;
      }
    }
}

/***************************************************************************
** Check for a hit within the master grid (used during movement)	  **
***************************************************************************/
unsigned char CheckHit(long CheckX, long CheckY)
{

if (CheckX < 0 || CheckY < 0 || CheckX > 4096 || CheckY > 4096)
  //If outside the map, simulate a hit...
  return (1);
else
  //...otherwise the value at current location
  return (Grid[(CheckY & 0xFFC0) + (CheckX >> 6)]);

}

/****************************************************************************
** Cast a ray to hit Vertical walls.                                       **
****************************************************************************/
unsigned char xRay(long x, long y, int CurAng)

{
  long 	           x1;
  long 		   y1;
  long             y2;
  long 	        xStep;
  long          yStep;
  unsigned char     c;

  //Can't hit parallel walls
  if (CurAng == ANGLE_90 || CurAng == ANGLE_270) return (0);

  //Make sure we step in the correct direction
  if (CurAng > ANGLE_90 && CurAng < ANGLE_270) {
    xStep = -64;
    x1    =  x       & 0xFFC0;
  } else {
    xStep =  64;
    x1    = (x + 64) & 0xFFC0;
  }

  //Make sure we step in the correct direction
  if (CurAng > ANGLE_180)
    yStep = -NextYTable [CurAng];
  else
    yStep =  NextYTable [CurAng];

  //Setup Y location, with extra precision
  y1 = (y << 15) + (x1 - x) * TangentTable [CurAng];

  while (1) {
    //Compensate for extra precision
    y2 = y1 >> 15;
    //If outside the map, stop looking
    if (x1 < 0 || y2 < 0 || x1 > 4096 || y2 > 4096) return (0);

    //Read map at current location
    c = xGrid[(y2 & 0xFFC0) + (x1 >> 6)];
    //If it contains a value...
    if (c) {
      //..calculate the distance and...
      xDst = ((x1 - x) << 15) / CosineTable [CurAng];
      //...end the loop
      return (c);
    }
    //Adjust current location
    x1 += xStep;
    y1 += yStep;
  }
}

/****************************************************************************
** Cast a ray to hit Horizontal walls.                                     **
****************************************************************************/
unsigned char yRay(long x, long y, int CurAng)

{
  long 	           x1;
  long 		   y1;
  long             x2;
  long 	        xStep;
  long          yStep;
  unsigned char     c;

  //Can't hit parallel walls
  if (CurAng == 0 || CurAng == ANGLE_180) return (0);

  //Make sure we step in the correct direction
  if (CurAng < ANGLE_180) {
    y1    = (y + 64) & 0xFFC0;
    yStep =  64;
  } else {
    y1    =  y       & 0xFFC0;
    yStep = -64;
  }

  //Make sure we step in the correct direction
  if (CurAng > ANGLE_90 && CurAng < ANGLE_270)
    xStep = -NextXTable[CurAng];
  else
    xStep =  NextXTable[CurAng];

  //Setup X location, with extra precision
  x1 = (x << 15) + (y1 - y) * iTangentTable[CurAng];

  while (1) {
    //Compensate for extra precision
    x2 = x1 >> 15;
    //If outside the map, stop looking
    if (x2 < 0 || y1 < 0 || x2 > 4096 || y1 > 4096) return (0);
    //Read map at current location
    c = yGrid[(y1 & 0xFFC0) + (x2 >> 6)];
    //If it contains a value...
    if (c) {
      //...calculate the distance and...
      yDst = ((y1 - y) << 15) / SineTable[CurAng];
      //...end the loop
      return (c);
    }
    //Adjust current location
    x1 += xStep;
    y1 += yStep;
  }

}

/****************************************************************************
** Display an entire screen worth of walls.				   **
****************************************************************************/
void DrawView(long x, long y, long Angle)

{
  int           ScreenColumn;
  int                 CurAng;
  int                CalcAng;
  int                 Height;
  int                   TopY;
  int                BottomY;
  unsigned char        Color;
  unsigned char       XColor;
  unsigned char       YColor;
  long              Distance;

  //Clear background by writing 0 to the buffer
  #ifdef __DJGPP
    memset(Buffer, 0, 64000);
  #else
    _fmemset(Buffer, 0, 64000);
  #endif

  for (ScreenColumn = 0; ScreenColumn < 319; ScreenColumn++) {

    //Set angles and keep them within the range of ANGLE_0 through ANGLE_360
    CurAng  = (ANGLE_360 + Angle + (int)fv[ScreenColumn + 20]) & (ANGLE_360 - 1);
    CalcAng = (ANGLE_360 + Angle - CurAng)                & (ANGLE_360 - 1);
    //Set distances to a ridiculously long distance
    xDst = 0x7FFFFFFF;
    yDst = 0x7FFFFFFF;

    //Check X walls
    XColor = xRay(x, y, CurAng);
    //Check Y walls
    YColor = yRay(x, y, CurAng);

    //If a wall was found
    if (XColor || YColor) {

      Distance = 0x7FFFFFFF;
      //Assume X wall
      if (XColor) {
        Distance = xDst;
        Color = XColor;
      }
      //But then again, it could have been an Y wall
      if (YColor) {
	if (Distance > yDst) {
          Distance = yDst;
          Color = YColor;
	}
      }

      //Compensate for fish eye effect
      Distance = (Distance * CosineTable[CalcAng]) >> 15;
      //Limit distance
      if (Distance > 3071) Distance = 3071;
      //Read height from table
      Height = HeightTable[Distance];
      //Set top and bottom coordinates
      TopY    = 100 - (Height >> 1);
      BottomY = TopY + Height;

      //Draw wall slice
      DrawLine(ScreenColumn, TopY, BottomY, Color);
    }
  }

  //Copy Buffer to screen
  memcpy (Screen, Buffer, 64000);
}


/****************************************************************************
** Main programme.                                                         **
****************************************************************************/
void main (void) {
  //Calculate tables
  SetTables();
  //Make map
  MakeMap();

  //Allocate memory for screen buffer
  #ifdef __DJGPP
    __djgpp_nearptr_enable ();
    Screen = (char *) (__djgpp_conventional_base + 0xA0000);
  #else
    Screen = (unsigned char *)MK_FP (0xA000, 0000);
    //Assign memory to buffer
    if ((Buffer = (unsigned char far *) farmalloc(64000))==NULL) {
      //If there wasn't enough memory, quit
      TextScreen ();
      printf ("Not enough memory for frame buffer!\n");
      return;
    }
  #endif

  //Set to VGA 320x200x256
  VGAScreen();

  //Set location at 256,256
  x = 256;
  y = 256;

  while (1) {

    //Read key from buffer
    Key = Inkey();

      //turn right
      if (Key == CRight) {
	Angle = (Angle + 32) & (ANGLE_360 - 1);
      }

      //turn left
      if (Key == CLeft) {
	Angle = (Angle + 2016) & (ANGLE_360 - 1);
      }

      //move forward
      if (Key == CUp) {
        //check to see if new location is empty
        if (!CheckHit(x + CosineTable[Angle] / 5000,
                      y + SineTable[Angle] / 5000)) {
	  //if so, move player
	  x += CosineTable[Angle] / 5000;
	  y += SineTable[Angle]   / 5000;
        }
      }

      //move backward
      if (Key == CDown) {
	//check to see if new location is empty
        if (!CheckHit(x - CosineTable[Angle] / 5000,
                      y - SineTable[Angle] / 5000)) {
	  //if so, move player
	  x -= CosineTable[Angle] / 5000;
	  y -= SineTable[Angle]   / 5000;
	}
      }

    //ESCAPE = quit
    if (Key == 27) break;

    //Display view
    DrawView(x, y, Angle);
  }

  //Return to text mode
  TextScreen();
}