#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "allegro5/allegro.h"
#include "allegro5/color.h"
#include <string>
#include <vector>
#include "MerkleNode.h"

using namespace std;

#define FPS	50

#define WIDTH_DEFAULT			1000
#define HEIGHT_DEFAULT			600
#define FONT_SIZE_DEFAULT		20
#define MARGIN_X_DISPLAY		50
#define MARGIN_Y_DISPLAY		50

#define IMAGE_SIZE_X 180 //256 
#define IMAGE_SIZE_Y 100 //130
#define BUTTON_SIZE_X 80
#define BUTTON_SIZE_Y 80
#define SPACE 10


#define UNIT 1
#define MARGIN_RATE 0.1

#define BACKGROUND_PATH			"background2.png" //Imagen de fondo

#define NODE_IMG_SIZE 150

#define SPV_IMG_PATH			"spv.png"	//Imagen para SPV
#define FULL_IMG_PATH			"full.png"	//Imagen para Full

#define FIRST_POS_W				WIDTH_DEFAULT/3 - NODE_IMG_SIZE/2
#define FIRST_POS_H				HEIGHT_DEFAULT/3 - NODE_IMG_SIZE/2
#define SECOND_POS_W			WIDTH_DEFAULT*(2.0/3.0) - NODE_IMG_SIZE/2
#define	SECOND_POS_H			HEIGHT_DEFAULT/3 - NODE_IMG_SIZE/2
#define	THIRD_POS_W				WIDTH_DEFAULT/2 - NODE_IMG_SIZE/2
#define THIRD_POS_H				HEIGHT_DEFAULT*(2.0/3.0) - NODE_IMG_SIZE/2

#define FONT_PATH				"American Captain.ttf"
#define FONT_COLOR				"red"

#define DEFAULT_WIDTH_BLOCK					60
#define DEFAULT_HEIGTH_BLOCK				(DEFAULT_WIDTH_BLOCK)
#define MARGIN_BLOCK_BTW_NAME_AND_IMAGE		10
#define IMAGE_BLOCK_PATH					"block-image.png"
#define FONT_PATH_BLOCK_NAME				"American Captain.ttf"
#define FONT_SIZE_BLOCK_NAME				9
#define FONT_COLOR_BLOCK_NAME				"white"

#define PATH_BUTTON_LEFT		"button_left2.png"
#define PATH_BUTTON_RIGHT		"button_right2.png"

#define SCALE_LEVEL_SIZE_NODE	3
#define NODE_RADIUS				12
#define NODE_COLOR				(al_map_rgb(0,0,204)) // verde oscuro

#define LINE_COLOR				(al_map_rgb(102,204,255)) // azul claro
#define LINE_THICKNESS			10

#define MESSAGE_NODE_COLOR			(al_map_rgb(0,0,0)) // negro
#define NODE_FONT_PATH				"Font.ttf"
#define NODE_FONT_SIZE				10
#define SCALE_LEVEL_SIZE_TEXT_NODE	2
#define DX_TEXT						5

#define MAX_BLOCKS_PER_DISPLAY 9

#define TYPE_NAME_FULLNODE	"Full Node"
#define TYPE_NAME_SPV_NODE	"SPV Node"

#define MERKLE_DISPLAY_MARGIN_DEFAULT_WIDTH		20
#define MERKLE_DISPLAY_MARGIN_DEFAULT_HEIGTH	15
#define MERKLE_NODE_IMAGE_PATH					"MerkelNode.png"


#define MAX_SIZE_TEXT_BOXTEXT						25


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
