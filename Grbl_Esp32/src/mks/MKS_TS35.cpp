#include "MKS_TS35.h"

// XPT2046_Touchscreen touch(TOUCH_CS);
TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
// TFT_Touch touch = TFT_Touch(TOUCH_CS,LCD_SCK,LCD_MOSI,LCD_MISO);


// SPIClass * LCD_SPI = NULL;
TS35_DEF ESP_TS35;
//static const uint32_t TS_SPI_BUF_SIZE = 8192;
// uint8_t *spi_master_tx_buf;

#define SPI_DMA_CHANNAL     1
#define LCD_SPI_SPEED       80000000        // 80M
#define TOUCH_SPI_SPEED     1000000        //  1M
#define LCD_SPI_MODE        SPI_MODE0

#define HMIN 0
#define HMAX 4095
#define VMIN 0
#define VMAX 4095
#define XYSWAP 0 // 0 or 1

void tft_LCD_Fill() {
    tft.fillRect(0, 0,480, 320, TFT_COLOR_RED);
}

void tft_TS35_init() {
    tft.begin();
    tft.setRotation(1);
    tft.initDMA();
    delay_ms(100);
}   

bool beep_flag = false;
uint32_t beep_start_tim = 0;
uint32_t beep_end_tim = 0;

void ts35_beep_init() { 
    pinMode(BEEPER, OUTPUT);
    digitalWrite(BEEPER, LOW);
}

void ts35_beep_on(void) {
    if(beep_status->get()) digitalWrite(BEEPER, HIGH);
}

void ts35_beep_off(void) {
    digitalWrite(BEEPER, LOW);
}

void ts35_set_flag(bool flag) {

    beep_flag = flag;
} 

void ts35_get_start_tim(uint32_t tim) {

    beep_start_tim = tim;
}

void ts35_get_end_tim(uint32_t tim) {

    beep_end_tim = tim;
}

void ts35_beep_tim_rst(void) {

    beep_start_tim = 0;
    beep_end_tim = 0;
}

uint32_t beep_get_dec() {

    return beep_end_tim - beep_start_tim;
}

#define LED_RESOLUTION      10
#define LED_CHANNEL         14
void bsp_led_init(void) { 
#ifdef LED_PIN
    ledcSetup(LED_CHANNEL, 1000, LED_RESOLUTION); // 设置通道14 ,分辨率为10（2^10 = 1024）
    ledcAttachPin(LED_PIN, LED_CHANNEL);  // 将通道与对应的引脚连接
#endif
}

void bsp_set_duty(uint32_t duty) {
#ifdef LED_PIN
    ledcWrite(LED_CHANNEL, duty);
#endif
}

// 0-255
void bsp_led_pwm_speed(uint8_t speed) {
    uint32_t duty = 1024;
    duty = (duty * (255 - speed)) / 255;
    bsp_set_duty(duty);
}


uint32_t led_count = 0;;
uint8_t led_dir_flag = 1;
void bsp_led_run(void) {

    if(led_dir_flag) {
        led_count = led_count + 15;
        if(led_count >= 255) {
            led_dir_flag = 0;
        }
    }else{
        led_count = led_count - 15;
        if(led_count == 0) {
            led_dir_flag = 1;
        }
    }
    bsp_led_pwm_speed(led_count);
}


// void tft_TS35_SPI_begin(void) {
//     tft.begin();
// }

// static void LCD_TOUCH_CS_CTRL(uint8_t LCD_CS1) {
//     digitalWrite(LCD_CS, LCD_CS1);
//     digitalWrite(TOUCH_CS, !LCD_CS1);
// }

// static void LCD_WR_REG(uint8_t cmd) {
//     digitalWrite(LCD_CS, LOW);
//     digitalWrite(LCD_RS, LOW); 
//     LCD_SPI->beginTransaction(SPISettings(LCD_SPI_SPEED, MSBFIRST, LCD_SPI_MODE));
//     LCD_SPI->transfer(cmd);
//     LCD_SPI->endTransaction();
//     digitalWrite(LCD_CS, HIGH);
// }

// static void LCD_WR_DATA(uint8_t data) {
//     digitalWrite(LCD_CS, LOW); 
//     digitalWrite(LCD_RS, HIGH); 
//     LCD_SPI->beginTransaction(SPISettings(LCD_SPI_SPEED, MSBFIRST, LCD_SPI_MODE));
//     LCD_SPI->transfer(data);
//     LCD_SPI->endTransaction();
//     digitalWrite(LCD_CS, HIGH); 
// }

// static void LCD_WR_REG_16(uint16_t cmd) {
//     digitalWrite(LCD_CS, LOW); 
//     digitalWrite(LCD_RS, LOW); 
//     LCD_SPI->beginTransaction(SPISettings(LCD_SPI_SPEED, MSBFIRST, LCD_SPI_MODE));
//     LCD_SPI->transfer16(cmd);
//     LCD_SPI->endTransaction();
//     digitalWrite(LCD_CS, HIGH); 
// }

// static void LCD_WR_DATA_16(uint16_t data) {
//     digitalWrite(LCD_CS, LOW); 
//     digitalWrite(LCD_RS, HIGH); 
//     LCD_SPI->beginTransaction(SPISettings(LCD_SPI_SPEED, MSBFIRST, LCD_SPI_MODE));
//     LCD_SPI->transfer16(data);
//     LCD_SPI->endTransaction();
//     digitalWrite(LCD_CS, HIGH); 
// }

// static void LCD_WR_DATA_16_COLOR(uint16_t data) {
//     LCD_SPI->transfer16(data);
// }

// static void LCD_WR_DATA_32_COLOR(uint32_t data) {
//     LCD_SPI->transfer32((data<<16)|data);
// }


// static uint8_t LCD_Read(uint8_t sdata) {
//     uint16_t data;
//     return  LCD_SPI->transfer(sdata);
// }

// void LCD_Clear(void) {
//     TFT_Clear();
// }

// void TS35_init(void) {

//     LCD_SPI = new SPIClass(VSPI);
//     LCD_SPI->begin(LCD_SCK,LCD_MISO,LCD_MOSI,LCD_CS);   //VSPI

//     /* Init GPIO Pin */
//     pinMode(LCD_CS,OUTPUT);  // LCD CS
//     pinMode(LCD_RS,OUTPUT);  // LCD RS
//     pinMode(LCD_EN,OUTPUT);  // LCD EN
//     pinMode(LCD_RST,OUTPUT); // LCD RST
    
//     /* Close Motor EN */
//     digitalWrite(X_DISABLE_PIN,HIGH);
//     digitalWrite(Y_DISABLE_PIN,HIGH);
//     digitalWrite(Z_DISABLE_PIN,HIGH);
//     digitalWrite(BEEPER,LOW);

//     ESP_TS35.LCD_H = LCD_HEIGHT;
//     ESP_TS35.LCD_W = LCD_WIDTH;
//     ESP_TS35.LCD_COLOR = TFT_COLOR_RED;

//     /* Set GPIO pin status */
//     digitalWrite(LCD_CS, HIGH); 
//     digitalWrite(TOUCH_CS, HIGH); 
//     digitalWrite(LCD_RS, HIGH); 
//     digitalWrite(LCD_EN, LOW);      //Disable LCD BackLight
//     digitalWrite(LCD_RST, HIGH);

    // delay_ms(50);
    // digitalWrite(LCD_RST, LOW);
    // delay_ms(50);
    // digitalWrite(LCD_RST, HIGH);
    // delay_ms(20);
    
//     LCD_WR_REG(0x11);
//     delay_ms(20);
//     LCD_WR_REG(0x36);
//     LCD_WR_REG(0xF0);
//     LCD_WR_DATA(0xC3);
//     LCD_WR_REG(0xF0);
//     LCD_WR_DATA(0x96);
//     LCD_WR_REG(0x36);
//     LCD_WR_DATA(0x28);
//     LCD_WR_DATA(0x28);
//     LCD_WR_REG(0x3A);
//     LCD_WR_DATA(0x55);
//     LCD_WR_REG(0xB4);
//     LCD_WR_DATA(0x01);
//     LCD_WR_REG(0xB7);
//     LCD_WR_DATA(0xC6);
//     LCD_WR_REG(0xE8);
//     LCD_WR_DATA(0x40);
//     LCD_WR_DATA(0x8A);
//     LCD_WR_DATA(0x00);
//     LCD_WR_DATA(0x00);
//     LCD_WR_DATA(0x29);
//     LCD_WR_DATA(0x19);
//     LCD_WR_DATA(0xA5);
//     LCD_WR_DATA(0x33);
//     LCD_WR_REG(0xC1);
//     LCD_WR_DATA(0x06);
//     LCD_WR_REG(0xC2);
//     LCD_WR_DATA(0xA7);
//     LCD_WR_REG(0xC5);
//     LCD_WR_DATA(0x18);
//     LCD_WR_REG(0xE0);     // Positive Voltage Gamma Control
//     LCD_WR_DATA(0xF0);
//     LCD_WR_DATA(0x09);
//     LCD_WR_DATA(0x0B);
//     LCD_WR_DATA(0x06);
//     LCD_WR_DATA(0x04);
//     LCD_WR_DATA(0x15);
//     LCD_WR_DATA(0x2F);
//     LCD_WR_DATA(0x54);
//     LCD_WR_DATA(0x42);
//     LCD_WR_DATA(0x3C);
//     LCD_WR_DATA(0x17);
//     LCD_WR_DATA(0x14);
//     LCD_WR_DATA(0x18);
//     LCD_WR_DATA(0x1B);
//     LCD_WR_REG(0xE1);     // Negative Voltage Gamma Control
//     LCD_WR_DATA(0xF0);
//     LCD_WR_DATA(0x09);
//     LCD_WR_DATA(0x0B);
//     LCD_WR_DATA(0x06);
//     LCD_WR_DATA(0x04);
//     LCD_WR_DATA(0x03);
//     LCD_WR_DATA(0x2D);
//     LCD_WR_DATA(0x43);
//     LCD_WR_DATA(0x42);
//     LCD_WR_DATA(0x3B);
//     LCD_WR_DATA(0x16);
//     LCD_WR_DATA(0x14);
//     LCD_WR_DATA(0x17);
//     LCD_WR_DATA(0x1B);
//     LCD_WR_REG(0xF0);
//     LCD_WR_DATA(0x3C);
//     LCD_WR_REG(0xF0);
//     LCD_WR_DATA(0x69);
//     delay_ms(120);           // Delay 120ms
//     LCD_WR_REG(0x29);        // Display ON
//     LCD_Clear();
//     digitalWrite(LCD_EN, HIGH);
// }

// void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
// {
// 	x2 = x2>LCD_WIDTH ? LCD_WIDTH:x2;
// 	y2 = y2>LCD_WIDTH ? LCD_HEIGHT:y2;

//     LCD_WR_REG(0x2a);//列地址设置
//     LCD_WR_DATA_16(x1);
//     LCD_WR_DATA_16(x2);

//     LCD_WR_REG(0x2b);//行地址设置
//     LCD_WR_DATA_16(y1);
//     LCD_WR_DATA_16(y2);
//     LCD_WR_REG(0x2c);//储存器写
// }

// void TFT_DisplayOn(void) {
// 	LCD_WR_REG(0x29);
// }

// void TFT_DisplayOff(void) {
// 	LCD_WR_REG(0x28);
// }

// void TFT_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
// {
//     LCD_Address_Set(x,y,x,y);//设置光标位置
//     LCD_WR_DATA_16(color);
// }


// void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
// {  
// 	uint16_t i,j;			
// 	uint16_t width=ex-sx+1; 		//得到填充的宽度
// 	uint16_t height=ey-sy+1;		//高度

//     LCD_Address_Set(sx,sy,ex,ey);      //设置光标位置

//     digitalWrite(LCD_CS, LOW); 
//     digitalWrite(LCD_RS, HIGH); 
//     LCD_SPI->beginTransaction(SPISettings(LCD_SPI_SPEED, MSBFIRST, LCD_SPI_MODE));
// 	for(i=0;i<height;i++)
// 	{
// 		for(j=0;j<width;j++)
//             LCD_WR_DATA_16_COLOR(color[i*width+j]);
// 	}
//     LCD_SPI->endTransaction();
// } 


// void TFT_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
// {  
//     uint32_t x,y;
//     y = (x2-x1)*(y2-y1);
//     LCD_Address_Set(x1,y1,x2,y2);      //设置光标位置
//     digitalWrite(LCD_CS, LOW); 
//     digitalWrite(LCD_RS, HIGH); 

//     LCD_SPI->beginTransaction(SPISettings(LCD_SPI_SPEED, MSBFIRST, LCD_SPI_MODE));
//     for(x=0; x<y; x++)  {
//         LCD_WR_DATA_16_COLOR(color);
//     }
//     LCD_SPI->endTransaction();
//     digitalWrite(LCD_CS, HIGH); 
// }


// void TFT_Clear(void) {
    // TFT_Fill(0,0,LCD_WIDTH,LCD_HEIGHT,TFT_COLOR_GREEN);
// }

// void TS35_Test(void) {

//     static uint8_t bk_color = 0;

//     switch (bk_color) {
//         case 0: TFT_Fill(0,0,LCD_WIDTH,LCD_HEIGHT,TFT_COLOR_RED); break;
//         case 1: TFT_Fill(0,0,LCD_WIDTH,LCD_HEIGHT,TFT_COLOR_GREEN); break;
//         case 2: TFT_Fill(0,0,LCD_WIDTH,LCD_HEIGHT,TFT_COLOR_BLUE); break;
//         case 3: TFT_Fill(0,0,LCD_WIDTH,LCD_HEIGHT,TFT_COLOR_BLACK); break;
//         case 4: TFT_Fill(0,0,LCD_WIDTH,LCD_HEIGHT,TFT_COLOR_WHITE); break;
//         case 5: TFT_Fill(0,0,LCD_WIDTH,LCD_HEIGHT,TFT_COLOR_YELLOW); break;
//     }
//     bk_color++;
//     if (bk_color > 5) {
//         bk_color = 0;
//     }
// }

// /**************************************************TOUCH****************************************************/

// uint8_t touch_read_write_byte(uint8_t sdata) {

//     uint8_t rdata = 0;

//     TFT_LCD_CS_H;
//     TFT_TOUCH_CS_L;
//     // delayMicroseconds(DELAY_LCD);
//     LCD_SPI->beginTransaction(SPISettings(TOUCH_SPI_SPEED, MSBFIRST, SPI_MODE0));
//     rdata = LCD_SPI->transfer(sdata);
//     LCD_SPI->endTransaction();
//     TFT_TOUCH_CS_H;
//     // delayMicroseconds(DELAY_LCD);
//     return rdata;
// }

// uint16_t IO(uint16_t sdata) {
//     uint8_t rdata = 0;
//     LCD_SPI->beginTransaction(SPISettings(TOUCH_SPI_SPEED, MSBFIRST, SPI_MODE0));
//     rdata = LCD_SPI->transfer(sdata);
//     LCD_SPI->endTransaction();
//     return rdata;
// }
// uint16_t delta(uint16_t a, uint16_t b) { return a > b ? a - b : b - a; }

// bool isBusy() { return false;}

// bool isTouched() {
//  return isBusy() ? false :(touch_read_write_byte(XPT2046_Z1) >= XPT2046_Z1_THRESHOLD);
// }

// uint16_t touch_getRawData(uint8_t sdata) {

//     TFT_LCD_CS_H;
//     TFT_TOUCH_CS_L;
//     uint16_t data[3];

//     for(uint16_t i=0; i<3; i++) {
//         IO(sdata);
//         data[i] = (IO(0x00) << 4) | (IO(0x00) >> 4);
//     }
//     TFT_TOUCH_CS_H;

//     uint16_t delta01 = delta(data[0], data[1]),
//              delta02 = delta(data[0], data[2]),
//              delta12 = delta(data[1], data[2]);

//     if (delta01 > delta02 || delta01 > delta12)
//     data[delta02 > delta12 ? 0 : 1] = data[2];

//     return (data[0] + data[1]) >> 1;
// }

// bool getRawPoint(int16_t *x, int16_t *y) {

//     if (isBusy()) return false;
//     if (!isTouched()) return false;
//     *x = touch_getRawData(XPT2046_X);
//     *y = touch_getRawData(XPT2046_Y);
//     return isTouched();
// }

// void TS35_touch_init(void) {

//     ESP_TS35.TOUCH_X = 0;
//     ESP_TS35.TOUCH_Y = 0;
//     // Read once to enable pendrive status pin
//     touch_getRawData(XPT2046_X);
// }

// void ts32_touch_read(void) {
//     getRawPoint(&ESP_TS35.TOUCH_X, &ESP_TS35.TOUCH_Y);
//     ESP_TS35.TOUCH_X =  int16_t( ((int32_t(ESP_TS35.TOUCH_X) * TOUCH_CALIBRATION_X) >> 16) + (500));
//     ESP_TS35.TOUCH_Y =  int16_t( (int32_t(ESP_TS35.TOUCH_Y) * TOUCH_CALIBRATION_Y) >> 16);
// }

void mks_motor_unclock(void) {
    /* Init GPIO Pin */
    digitalWrite(X_DISABLE_PIN,HIGH);
    digitalWrite(Y_DISABLE_PIN,HIGH);
    digitalWrite(Z_DISABLE_PIN,HIGH);
    digitalWrite(BEEPER,LOW);
}

// void XPT2046_Rd_Addata(void) {
//     uint16_t temp;
//     //delay_ms(1);
//     touch_read_write_byte( CHX ) ;
//     //delay_ms(1);
//     temp=0;//相当于简短的延时啦
//     temp= touch_read_write_byte(0x00) ;
//     ESP_TS35.TOUCH_Y = temp<<8;
//     temp= touch_read_write_byte(0x00) ;
//     ESP_TS35.TOUCH_Y |=temp;
//     ESP_TS35.TOUCH_Y >>=3;
//     ESP_TS35.TOUCH_Y &= 0XFFF;
//     //GPIO_SetBits(GPIOC, GPIO_Pin_9);
    
//     //GPIO_ResetBits(GPIOC, GPIO_Pin_9);
//     //delay_ms(1);
//     touch_read_write_byte( CHY) ;
//     temp=0;
//     //delay_ms(1);
//     temp= touch_read_write_byte(0x00);
//     ESP_TS35.TOUCH_X=temp<<8;
//     temp= touch_read_write_byte(0x00);
//     ESP_TS35.TOUCH_X |=temp;
//     ESP_TS35.TOUCH_X >>=3;
//     ESP_TS35.TOUCH_X &=0XFFF;
// }










