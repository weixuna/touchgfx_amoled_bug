/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/SlideMenuPageBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

SlideMenuPageBase::SlideMenuPageBase()
{
    setWidth(240);
    setHeight(296);
    box1.setPosition(0, 0, 240, 296);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    add(box1);

    button1.setXY(88, 116);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_FORE_ID), touchgfx::Bitmap(BITMAP_FORE_PRESSED_ID));
    add(button1);
}

SlideMenuPageBase::~SlideMenuPageBase()
{

}

void SlideMenuPageBase::initialize()
{

}
