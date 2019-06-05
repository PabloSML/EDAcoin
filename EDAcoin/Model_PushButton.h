#include "BoxPanel.h"
#include <stdio.h>	

using namespace std;


class Model_PushButton : public BoxPanel
{
	public:
		Model_PushButton(string& first_title, unsigned int first_width, unsigned int first_heigth);
		~Model_PushButton(void);
};
