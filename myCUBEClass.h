/*
Name    : myCUBEClass.h
Project : LED CUBE 16x8x8 (8x8x8 RED & 8x8x8 GREEN)
Version : 1.0
Date    : 03.06.2018
Author  : tuenhidiy
Email   : tuenhi.n2012@gmail.com
*/

#ifndef myCUBEClass_h
#define myCUBEClass_h
#include <avr/pgmspace.h>
#include "Arduino.h"
  

#define CUBE_XSIZE  8 ///< Cube size in the X axis
#define CUBE_YSIZE  16 ///< Cube size in the Y axis
#define CUBE_ZSIZE  8 ///< Cube size in the Z axis

#define CUBE_BYTES  128

#define AXIS_X      0
#define AXIS_Y      1
#define AXIS_Z      2

#define DEMO_RUNTIME  20000L


typedef struct {
  float x;
  float y;
  float z;
} vertex;

typedef uint8_t     type_polarity;

enum polarity_t : uint8_t
  {
    POSITIVE,
    NEGATIVE,
  };

  
class myCUBE
{
  public:
    unsigned char cube[8][16];
    unsigned char fb[8][16];

    myCUBE();
    void Init(uint8_t pinDATA, uint8_t pinCLOCK, 
                 uint8_t pinRowA, uint8_t pinRowB, uint8_t pinRowC, uint8_t pinRowD,
                 uint8_t pinOE, uint8_t pinSTB);

    
    // Draw functions.
    void delay_ms (uint16_t x);
    void launch_effect (int effect);
    void setvoxel(int x, int y, int z);
    void clrvoxel(int x, int y, int z);
    void tmpsetvoxel(int x, int y, int z);
    void tmpclrvoxel(int x, int y, int z);

    unsigned char inrange(int x, int y, int z);
    unsigned char getvoxel(int x, int y, int z);
    void flpvoxel(int x, int y, int z);
    void altervoxel(int x, int y, int z, int state);
    
    void setplane_z(int z);
    void clrplane_z(int z);
    void setplane_x(int x);
    void clrplane_x(int x);
    void setplane_y(int y);
    void clrplane_y(int y);

    void setplane (char axis, unsigned char i);
    void clrplane (char axis, unsigned char i);


    void fill(unsigned char pattern);
    void tmpfill(unsigned char pattern);
    char flipbyte(char byte);
    char byteline (int start, int end);
    void argorder(int ix1, int ix2, int *ox1, int *ox2); 
    void Show();
        
    void mirror_x(void);
    void mirror_y(void);
    void mirror_z(void);

    // Handwritten functions.
    void HandwrittenNumber(char axis, byte xyz, byte offset, byte number, bool hwclock);
    void DrawDigit(char axis, byte xyz, byte dots[][2], byte siz, byte offset, bool hwclock);
    void Eraser(char axis, byte xyz, uint8_t offset);
    void fillRectangle(char axis, uint8_t xyz, uint8_t z1, uint8_t x1, uint8_t z2, uint8_t x2, bool state, uint8_t offset);
    int checkConstrains(int value, int min, int max);
    
    void TranslateScroll(char axis, int8_t value);  
    void TransitionScroll(char axis, const type_polarity polarity, const uint8_t delayx);    
    void shift (char axis, int direction);      
    void TransitionShift(char axis, const type_polarity polarity, const uint8_t delayms);


  private:
    byte row;
    //byte y_T;
    //byte z_T;

    volatile uint8_t *outDATA;
    volatile uint8_t *outCLOCK;
    volatile uint8_t *outRowA;
    volatile uint8_t *outRowB;
    volatile uint8_t *outRowC;
    volatile uint8_t *outRowD;
    volatile uint8_t *outOE;
    volatile uint8_t *outSTB;
    
    uint8_t bitDATA;
    uint8_t bitCLOCK;
    uint8_t bitRowA;
    uint8_t bitRowB;
    uint8_t bitRowC;
    uint8_t bitRowD;
    uint8_t bitOE;
    uint8_t bitSTB;
  
    void DIY_shiftOut(uint8_t DATA);    
    void RowScan(byte row);

    void Timer1Setup(void);    
};

//  END OF class myCUBE
#endif
