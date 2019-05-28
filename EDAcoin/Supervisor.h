#pragma once

#ifndef SUPERVISOR_H
#define SUPERVISOR_H


#include <allegro5\allegro.h>
#include "Viewer.h"
#include "Board.h"


class supervisor {
public:
	supervisor(viewer& viewer, double threshold);
	~supervisor();

	void dispatcher(viewer& viewer, board& board);
	bool is_init(void);
	bool is_finish(void);

private:
	ALLEGRO_EVENT_QUEUE* ev_queue;
	bool init;
	bool finish;
	double threshold;
};


#endif // !SUPERVISOR_H


