#pragma once

#include "Widget.h"
#include "Subject.h"

class Model_Button_Blockchain: public Subject, public Widget{

	public:
		Model_Button_Blockchain(unsigned int width, unsigned height);
		~Model_Button_Blockchain();

};