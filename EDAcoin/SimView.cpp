#include "SimView.h"

void 
SimView::update(void* model)
{
	Simulation* simModel = (Simulation*)model;

	al_set_target_backbuffer(simModel->getDisplay());

	al_clear_to_color(al_color_name("aquamarine"));
	
	drawConnections(simModel->getNodesPos(), simModel->getAdjMatrix());
	
	simModel->updateInsiderModels();
	
	al_set_target_backbuffer(simModel->getDisplay());

	al_flip_display();
}

void SimView::drawConnections(vector<pos_t> v, Graph* g)
{
	int cantnodes = v.size();
	//int cantE = 0;
	if (cantnodes != g->getN())
	{
		cout << "Error:CantNodes doesnt match with the size of position vector" << endl;
	}
	pos_t pos1;
	pos_t pos2;
	for (int i = 0; i < cantnodes; i++)
	{
		for (int j = i; j < cantnodes; j++)
		{
			if (g->isEdge(i, j))
			{
				pos1 = v[i];
				pos2 = v[j];
				al_draw_line(pos1.posX +RADIUS,pos1.posY + RADIUS,pos2.posX + RADIUS,pos2.posY + RADIUS, al_color_name("black"),5);
				//cantE++;
			}
		}
	}
	//cout << cantE << "=====" << g->getE() << endl;
}

