#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void function1();
    virtual void function2();
    virtual void function3();
    virtual void function4();
    virtual void function5();
    void updateTime(uint8_t hour, uint8_t minute, uint8_t second);

protected:
};

#endif // SCREEN2VIEW_HPP
