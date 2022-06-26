#ifndef MODEL_HPP
#define MODEL_HPP

#include "main.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void HW_GetTime(void);
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
