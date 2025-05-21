#ifndef SLIDEMENUPAGEVIEW_HPP
#define SLIDEMENUPAGEVIEW_HPP

#include <gui_generated/slidemenupage_screen/slideMenuPageViewBase.hpp>
#include <gui/slidemenupage_screen/slideMenuPagePresenter.hpp>

class slideMenuPageView : public slideMenuPageViewBase
{
public:
    slideMenuPageView();
    virtual ~slideMenuPageView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleGestureEvent(const touchgfx::GestureEvent &evt);

protected:
};

#endif // SLIDEMENUPAGEVIEW_HPP
