#include "Toggle_Switch.h"

unsigned long currentTime = 0,
              previousTime = 0;

//=================== ---|| CONSTRUCTOR METHOD ||--- ============================
            
Toggle_Switch::Toggle_Switch()
{
    this->x            = 0;
    this->y            = 0;
    this->height       = 0;
    this->width        = 0;
    this->radius       = 0;
    this->outline      = 0;
    this->color_on     = 0;
    this->color_off    = 0;
    this->color_paddle = 0;
    this->status       = false;
    this->margin       = 0;
    this->border       = 0;

}

//=================== ---|| PUBLIC METHODS ||--- ============================



//====================== --- initToggle --- =============================

void Toggle_Switch::initToggle(TFT_eSPI *gfx, uint16_t x, uint16_t y, uint8_t style, uint8_t size, uint16_t outline, uint16_t color_on, uint16_t color_off, uint16_t color_paddle)
{
    this->gfx          = gfx;
    this->x            = x;
    this->y            = y;
    this->style        = style;
    this->size         = size;
    this->height       = size * 5 + 15;
    this->width        = height * 2;
    this->radius       = height/2;
    this->outline      = outline;
    this->color_on     = color_on;
    this->color_off    = color_off;
    this->color_paddle = color_paddle;
    this->margin       = height / 10; //10%
    this->border       = margin * 2;
}

//====================== --- Draw Toggle --- =============================

void Toggle_Switch::drawToggle()
{
    switch (style)
    {
    case 1:
        if(status)
            this->style1_toggleOn();
        else
            this->style1_toggleOff();
        break;

    case 2:
        if(status)
            this->style2_toggleOn();
        else
            this->style2_toggleOff();
        break;

    default:
        break;
    }

}

//====================== --- Contains--- =============================

boolean Toggle_Switch::contains(int16_t t_x, int16_t t_y)
{
    return
    (
        (t_x >= x) && (t_x < (x + width))
        &&
        (t_y >= y) && (t_y < (y + height))
    );
}

//====================== --- Pressed --- =============================

void Toggle_Switch::pressed()
{
    uint16_t pauseTime = 1000;
    currentTime = millis();

    if(currentTime > previousTime + pauseTime)
    {
        this->changeStatus();
        this->drawToggle();
        previousTime = currentTime; 
    }

}

//=================== ---|| PRIVATE METHODS ||--- ============================



//====================== ---  Style1  on/off --- =============================

void Toggle_Switch::setStatus(bool status)
{
    this->status = status;
}

void Toggle_Switch::changeStatus()
{
    this->setStatus(!status);
}

bool Toggle_Switch::returnStatus()
{
    return(status);
}

void Toggle_Switch::style1_toggleOff()
{
    gfx->fillRoundRect(x-margin, y-margin, width+border, height+border, (height+border)/2, outline);
    gfx->fillRoundRect(x, y, width, height, radius, color_off);
    gfx->fillCircle(x+radius, y+radius, radius - margin, color_paddle);
}

void Toggle_Switch::style1_toggleOn()
{
     gfx->fillRoundRect(x-margin, y-margin, width+border, height+border, (height+border)/2, outline);
    gfx->fillRoundRect(x, y, width, height, radius, color_on);
    gfx->fillCircle(x+width-radius, y+radius, radius - margin, color_paddle);
    
}

//====================== --- Style2 on/off --- =============================

void Toggle_Switch::style2_toggleOff()
{
    uint8_t w_Padlle  = width/6,
            h_Paddle = height-margin*2,
            r_Paddle = width/4/4;

    gfx->fillRoundRect(x-margin, y-margin, width+border, height+border, (height+border)/4, outline);
    gfx->fillRoundRect(x, y, width, height, radius/2 , color_off);
    gfx->fillRoundRect(x+margin, y+margin, w_Padlle, h_Paddle, r_Paddle, color_paddle);

    uint8_t centerToggle = (width - w_Padlle)/2 + w_Padlle,
            textSize     = size%2==0? size/2 : (size + 1) / 2;

    gfx->setTextColor(color_paddle, color_off);
    gfx->setTextDatum(MC_DATUM);
    gfx->setTextSize(textSize);
    gfx->drawString("OFF", x+centerToggle+margin, y+height/2);
}

void Toggle_Switch::style2_toggleOn()
{
    uint8_t w_Padlle  = width/6,
            h_Paddle = height-margin*2,
            r_Paddle = width/4/4;

    gfx->fillRoundRect(x-margin, y-margin, width+border, height+border, (height+border)/4, outline);
    gfx->fillRoundRect(x, y, width, height, radius/2 , color_on);
    gfx->fillRoundRect(x+width-(w_Padlle)-margin, y+margin, w_Padlle, h_Paddle, r_Paddle, color_paddle);

    uint8_t centerToggle = (width - w_Padlle)/2,
            textSize     = size%2==0? size/2 : (size + 1) / 2;

    gfx->setTextColor(color_paddle, color_on);
    gfx->setTextDatum(MC_DATUM);
    gfx->setTextSize(textSize);
    gfx->drawString("ON", x+(centerToggle)+margin, y+height/2);
    
}


//====================== ---|| END CODE ||--- =============================
