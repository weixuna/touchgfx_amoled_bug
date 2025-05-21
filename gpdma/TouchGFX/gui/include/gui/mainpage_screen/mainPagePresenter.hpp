#ifndef MAINPAGEPRESENTER_HPP
#define MAINPAGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class mainPageView;

class mainPagePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    mainPagePresenter(mainPageView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~mainPagePresenter() {}

private:
    mainPagePresenter();

    mainPageView& view;
};

#endif // MAINPAGEPRESENTER_HPP
