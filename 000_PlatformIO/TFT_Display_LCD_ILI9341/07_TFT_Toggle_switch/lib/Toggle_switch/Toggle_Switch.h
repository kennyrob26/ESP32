#ifndef _TOGGLE_SWITCH_INCLUDED_
#define _TOGGLE_SWITCH_INCLUDED_

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

class Toggle_Switch
{
    public:
        Toggle_Switch();

        void initToggle(TFT_eSPI *gfx, uint16_t x, uint16_t y, uint8_t style, uint8_t size, uint16_t outline, uint16_t color_on, uint16_t color_off, uint16_t color_paddle);

        void drawToggle();

        boolean contains(int16_t t_x, int16_t t_y);

        void pressed();

        void setStatus(bool status);

        void changeStatus();

        bool returnStatus();
    
    private:
        TFT_eSPI *gfx;

        uint8_t  radius,
                 style,
                 size,
                 height,
                 margin,
                 border;

        uint16_t x,
                 y,
                 width;

        uint32_t outline,
                 color_on,
                 color_off,
                 color_paddle;


        bool status;

        void style1_toggleOn();

        void style1_toggleOff();

        void style2_toggleOn();

        void style2_toggleOff();
};

#endif