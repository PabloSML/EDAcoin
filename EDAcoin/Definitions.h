#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "allegro5/allegro.h"
#include "allegro5/color.h"
#include <string>
#include <vector>
#include "MerkleNode.h"
using namespace std;

#define WIDTH_DEFAULT			1000
#define HEIGHT_DEFAULT			600
#define FONT_SIZE_DEFAULT		30

#define BACKGROUND_PATH			"background2.png" //Imagen de fondo

#define FONT_PATH				"Font.ttf"
#define FONT_COLOR				"red"

#define IMAGE_BLOCK_PATH		"block-image.png"

#define PATH_BUTTON_LEFT		"button_left2.png"
#define PATH_BUTTON_RIGHT		"button_right2.png"

#define NODE_RADIUS				40
#define NODE_COLOR				(al_map_rgb(0,0,204)) // verde oscuro

#define LINE_COLOR				(al_map_rgb(102,204,255)) // azul claro
#define LINE_THICKNESS			10

#define MESSAGE_NODE_COLOR		(al_map_rgb(255,0,0)) // rojo puro
#define NODE_FONT_PATH			"Font.ttf"
#define NODE_FONT_COLOR			"red"
#define NODE_FONT_SIZE			8

typedef struct {
	string blockID;
	string txID;
}InputS;

typedef struct {
	string publicID;
	unsigned int amount;
}OutputS;

typedef struct {
	string txID;
	string txActor; // seria el nombre de quien hace la tx. (provisional)
	vector<InputS> inputs;
	vector<OutputS> outputs;
}TransactionS;

typedef struct {
	unsigned int merklePathLen;
	vector<Step> merklePath;
}MerkleValidationData;

typedef struct {
	unsigned int txCount;
	vector<TransactionS> transactions;
	vector<MerkleValidationData> merklePathDataForTxs;
	string blockID;
}EdaMerkleBlockS;


#endif // !DEFINITIONS_H
