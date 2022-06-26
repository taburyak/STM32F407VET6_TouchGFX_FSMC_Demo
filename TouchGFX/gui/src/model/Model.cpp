#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C" {
	extern uint8_t flagOnePerSecond;
	extern RTC_TimeTypeDef ShowRTC_Calendar(void);
}

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if (flagOnePerSecond != 0)
	{
		flagOnePerSecond = 0;
		RTC_TimeTypeDef sTime = ShowRTC_Calendar();
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		modelListener->updateTime(sTime.Hours, sTime.Minutes, sTime.Seconds);
	}
}

void Model::HW_GetTime()
{
	RTC_TimeTypeDef sTime = ShowRTC_Calendar();
	modelListener->updateTime(sTime.Hours, sTime.Minutes, sTime.Seconds);
}
