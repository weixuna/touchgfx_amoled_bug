#include <gui/mainpage_screen/mainPageView.hpp>
#include <images/BitmapDatabase.hpp>
mainPageView::mainPageView():showingImage1(true)
{
	//image1.setTouchable(true);
}

void mainPageView::setupScreen()
{
    mainPageViewBase::setupScreen();

    box1.setAlpha(255);   // 默认可见
    box2.setAlpha(0);     // 默认隐藏

    box1.setVisible(true);
    box2.setVisible(true);  // FadeAnimator 要求 visible，透明度控制显示

    box1.setTouchable(false);
    box2.setTouchable(false);

    box1.invalidate();
    box2.invalidate();
}


void mainPageView::tearDownScreen()
{
    mainPageViewBase::tearDownScreen();
}

void mainPageView::handleGestureEvent(const touchgfx::GestureEvent &evt)
{
    // 检测下滑手势
    if (evt.getType() == touchgfx::GestureEvent::SWIPE_VERTICAL)
    {
        // 下滑时 (正值表示向下滑动)
        if (evt.getVelocity() > 0)
        {
            application().gotoslideMenuPageScreenSlideTransitionNorth();
        }
    }

    // 正确调用父类方法，避免递归
    mainPageViewBase::handleGestureEvent(evt);
}
void mainPageView::handleClickEvent(const touchgfx::ClickEvent &evt)
{
	bool isInImage1 = box1.getX() <= evt.getX() && evt.getX() <= box1.getX() + box1.getWidth() &&
			box1.getY() <= evt.getY() && evt.getY() <= box1.getY() + box1.getHeight();

	bool isInImage2 = box2.getX() <= evt.getX() && evt.getX() <= box2.getX() + box2.getWidth() &&
			box2.getY() <= evt.getY() && evt.getY() <= box2.getY() + box2.getHeight();

    if (evt.getType() == touchgfx::ClickEvent::PRESSED)
    {
    	if (isInImage1 && showingImage1)
    	{
    		box1.startFadeAnimation(0, 40);
    		box2.startFadeAnimation(255, 40);
    	    showingImage1 = false;
    	}
    	else if (isInImage2 && !showingImage1)
    	{
    		box1.startFadeAnimation(0, 40);
    		box2.startFadeAnimation(255, 40);
    	    showingImage1 = true;
    	}

    }

    // 传给基类，保持默认行为
    mainPageViewBase::handleClickEvent(evt);
}
