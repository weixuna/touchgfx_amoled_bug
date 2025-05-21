#include <gui/slidemenupage_screen/slideMenuPageView.hpp>

slideMenuPageView::slideMenuPageView()
{
}

void slideMenuPageView::setupScreen()
{
    slideMenuPageViewBase::setupScreen();
}

void slideMenuPageView::tearDownScreen()
{
    slideMenuPageViewBase::tearDownScreen();
}
void slideMenuPageView::handleGestureEvent(const touchgfx::GestureEvent &evt)
{
    // 检测上滑手势
    if (evt.getType() == touchgfx::GestureEvent::SWIPE_VERTICAL)
    {
        // 上滑滑时
        if (evt.getVelocity() < 0)
        {
            application().gotomainPageScreenSlideTransitionSouth();
        }
    }

    // 正确调用父类方法，避免递归
    slideMenuPageViewBase::handleGestureEvent(evt);
}
