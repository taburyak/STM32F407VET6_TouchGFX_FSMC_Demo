#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    presenter->UI_GetTime();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::function1()
{
	digitalClock1.setTime24Hour(digitalClock1.getCurrentHour() + 1, digitalClock1.getCurrentMinute(), digitalClock1.getCurrentSecond());
	presenter->UI_SetTime(digitalClock1.getCurrentHour(), digitalClock1.getCurrentMinute(), digitalClock1.getCurrentSecond());
}

void Screen2View::function2()
{
	digitalClock1.setTime24Hour(digitalClock1.getCurrentHour(), digitalClock1.getCurrentMinute() + 1, digitalClock1.getCurrentSecond());
	presenter->UI_SetTime(digitalClock1.getCurrentHour(), digitalClock1.getCurrentMinute(), digitalClock1.getCurrentSecond());
}

void Screen2View::function3()
{
	if(digitalClock1.getCurrentSecond() > 29)
	{
		digitalClock1.setTime24Hour(digitalClock1.getCurrentHour(), digitalClock1.getCurrentMinute() + 1, 0);
	}
	else
	{
		digitalClock1.setTime24Hour(digitalClock1.getCurrentHour(), digitalClock1.getCurrentMinute(), 0);
	}

	presenter->UI_SetTime(digitalClock1.getCurrentHour(), digitalClock1.getCurrentMinute(), digitalClock1.getCurrentSecond());
}

void Screen2View::updateTime(uint8_t hour, uint8_t minute, uint8_t second)
{
	digitalClock1.setTime24Hour(hour, minute, second);
}
