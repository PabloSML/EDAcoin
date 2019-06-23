#pragma once

#include "Observer.h"

#include "View_PushButton.h"
#include "View_BoxText.h"

#include <vector>

class View_Transaction_GUI : public Observer
{
	public:
		View_Transaction_GUI();
		~View_Transaction_GUI(void);

		void update(void* model);

};