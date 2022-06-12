#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::function1()
{
	digitalClock1.setTime24Hour(digitalClock1.getCurrentHour24() + 1, digitalClock1.getCurrentMinute(), digitalClock1.getCurrentSecond());
}

void Screen2View::function2()
{
	digitalClock1.setTime24Hour(digitalClock1.getCurrentHour24(), digitalClock1.getCurrentMinute() + 1, digitalClock1.getCurrentSecond());
}

void Screen2View::function3()
{
	digitalClock1.setTime24Hour(digitalClock1.getCurrentHour24(), digitalClock1.getCurrentMinute(), digitalClock1.getCurrentSecond() + 1);
}
