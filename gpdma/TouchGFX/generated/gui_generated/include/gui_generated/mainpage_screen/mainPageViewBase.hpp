/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINPAGEVIEWBASE_HPP
#define MAINPAGEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/mainpage_screen/mainPagePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class mainPageViewBase : public touchgfx::View<mainPagePresenter>
{
public:
    mainPageViewBase();
    virtual ~mainPageViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::FadeAnimator< touchgfx::Box > box1;
    touchgfx::FadeAnimator< touchgfx::Box > box2;

private:

};

#endif // MAINPAGEVIEWBASE_HPP
