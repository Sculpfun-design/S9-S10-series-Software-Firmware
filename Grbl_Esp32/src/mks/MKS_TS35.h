#ifndef __MKS_TS35_H
#define __MKS_TS35_H

#include "../Grbl.h"
#include "SPI.h" 
#include "lvgl.h"
#include "TFT_eSPI.h"

#define LCD_WIDTH               480
#define LCD_HEIGHT              320

#define	CHX 	                  0x90
#define	CHY 	                  0xD0

#define XPT2046_DFR_MODE        0x00
#define XPT2046_SER_MODE        0x04
#define XPT2046_CONTROL         0x80

#if !defined(XPT2046_Z1_THRESHOLD)
  #define XPT2046_Z1_THRESHOLD      10
#endif

#ifndef TOUCH_CALIBRATION_X
  #define TOUCH_CALIBRATION_X           -17253
#endif
#ifndef TOUCH_CALIBRATION_Y
  #define TOUCH_CALIBRATION_Y            11579
#endif
#ifndef TOUCH_OFFSET_X
  #define TOUCH_OFFSET_X                   514
#endif
#ifndef TOUCH_OFFSET_Y
  #define TOUCH_OFFSET_Y                   -24
#endif

#define TFT_COLOR_RED		                0xF800
#define TFT_COLOR_GREEN		              0x07E0
#define TFT_COLOR_BLUE		              0x001F
#define TFT_COLOR_BLACK		              0x0000
#define TFT_COLOR_WHITE		              0xFFFF
#define TFT_COLOR_YELLOW                0xFFE0


#define TFT_LCD_CS_H        digitalWrite(LCD_CS, HIGH)
#define TFT_LCD_CS_L        digitalWrite(LCD_CS, LOW)

#define TFT_TOUCH_CS_H      digitalWrite(TOUCH_CS, HIGH)
#define TFT_TOUCH_CS_L      digitalWrite(TOUCH_CS, LOW)


#ifdef USE_VERSION_003
#define LCD_BLK_ON          digitalWrite(LCD_EN, HIGH)
#define LCD_BLK_OFF         digitalWrite(LCD_EN, LOW)
#else
#define LCD_BLK_ON          digitalWrite(LCD_EN, LOW)
#define LCD_BLK_OFF         digitalWrite(LCD_EN, HIGH)
#endif


typedef struct {

    uint32_t LCD_W;
    uint32_t LCD_H;
    uint32_t LCD_COLOR;

    int16_t TOUCH_X;
    int16_t TOUCH_Y;
    
}TS35_DEF;

extern TS35_DEF ESP_TS35;

enum XPTCoordinate : uint8_t {
  XPT2046_X  = 0x10 | XPT2046_CONTROL | XPT2046_DFR_MODE,
  XPT2046_Y  = 0x50 | XPT2046_CONTROL | XPT2046_DFR_MODE,
  XPT2046_Z1 = 0x30 | XPT2046_CONTROL | XPT2046_DFR_MODE,
  XPT2046_Z2 = 0x40 | XPT2046_CONTROL | XPT2046_DFR_MODE,
};

extern TFT_eSPI tft;
// extern TFT_Touch touch;

// LCD Driver
void TS35_init(void);
void TFT_DisplayOn(void);
void TFT_DisplayOff(void);
void TFT_DrawPoint(uint16_t x,uint16_t y,uint16_t color);
void TFT_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);
void TFT_Clear(void);
void TS35_Test(void);
// Touch Driver
void TS35_touch_init(void);
uint8_t touch_read_write_byte(uint8_t sdata);
void XPT2046_Rd_Addata(void);
uint16_t touch_getRawData(uint8_t sdata);
bool getRawPoint(int16_t *x, int16_t *y);
void ts32_touch_read(void);
void LCD_Clear(void);

void tft_TS35_init();
void tft_TS35_SPI_begin(void);
void ts35_beep_init();
void ts35_beep_on(void);
void ts35_beep_off(void);
void mks_motor_unclock(void);

void bsp_led_init(void);
void ts35_set_flag(bool flag);

void bsp_led_run(void);

#endif

