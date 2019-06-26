#pragma once

#include "allegro5/allegro.h"
#include "allegro5/color.h"
#include <string>
#include <vector>
#include "MerkleNode.h"
#include "Crypto.h"

using namespace std;

#define WIDTH_DEFAULT			1000
#define HEIGHT_DEFAULT			550
#define HEIGHT_EXTRA			150
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

#define NODE_IMG_SIZE 100
#define RADIUS (NODE_IMG_SIZE/2)

#define SPV_IMG_PATH			"spv.png"	//Imagen para SPV
#define FULL_IMG_PATH			"full.png"	//Imagen para Full
#define MINER_IMG_PATH			"miner.png" //Imagen para Miner

#define GRAPH_RADIUS			(HEIGHT_DEFAULT/2 - NODE_IMG_SIZE)

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
#define FONT_COLOR_BLOCK_NAME				"black"

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

#define COLOR_BACKGROUND_BLOCKCHAIN		"white"



//definitions transaction interface
#define TRANS_INTERF_CANT_PUSHB		1
#define TRANS_INTERF_CANT_EDITB		3
#define TRANS_INTERF_PUSHB1_NMBER	0
#define TRANS_INTERF_PUSHB_TITLE1	"SEND"
#define TRANS_INTERF_EDITB1_NMBER	0
#define TRANS_INTERF_EDITB_TITLE1	"FROM:"
#define TRANS_INTERF_EDITB2_NMBER	1
#define TRANS_INTERF_EDITB_TITLE2	"TO:"
#define TRANS_INTERF_EDITB3_NMBER	2
#define TRANS_INTERF_EDITB_TITLE3	"AMOUNT:"
#define TRANS_INTERF_PUSHB_WIDTH	100
#define TRANS_INTERF_PUSHB_HEIGTH	35
#define TRANS_INTERF_EDITB_WIDTH	250
#define TRANS_INTERF_EDITB_HEIGTH	50
#define TRANS_INTERF_POS_Y			(HEIGHT_DEFAULT + 10)
#define TRANS_INTERF_MARGIN_BTW_B	15

//definitions edit boxes transaction interface
#define COLOR_TITLE_PANEL			"black"
#define COLOR_EDIT_UNSELECT_PANEL	"white"
#define COLOR_EDIT_SELECT_PANEL		"yellow"
#define COLOR_EDIT_TEXT				"blue"
#define FONT_NAME_EDIT_TEXT			"Font.ttf"
#define FONT_NAME_TITLE_EDIT		"Font.ttf"
#define PERC_WIDTH_EDIT_TEXT		0.8
#define PERC_HEIGTH_EDIT_TEXT		0.6
#define SIZE_FONT_EDIT_TEXT			10
#define SIZE_FONT_TITLE_EDIT		8

//definitions pushbuttons transaction interface
#define COLOR_PUSHB_STATE1			"red"
#define COLOR_PUSHB_STATE2			"brown"
#define COLOR_PUSHB_TITLE			"white"
#define FONT_NAME_PUSHB_TEXT	    "Font.ttf"
#define SIZE_FONT_TITLE_PUSHBU		15

//definitions EdaCoin Network
#define FEE (12.5)


typedef struct {
	string blockID;
	string txID;
}InputS;

typedef struct {
	string publicKey;		//deberia llamarse publickey (o Se puede tomar el hashID?)
	
	double amount;
}OutputS;

typedef struct {
	string txID;
	//string txActor; // seria el nombre de quien hace la tx. (provisional)
	string PubKey;
	//string Signature;
	//**
	vector<byte> signature;
	//**

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

