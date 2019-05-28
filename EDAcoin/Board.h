#pragma once

#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "ImageDescriptor.h"
#include "MerkleNode.h"
#include "Definitions.h"

#define MAX_IMAGES_IN_THE_BOARD 9

#define CANT_BUTTONS 2
#define BUTTON_LEFT 0  //indices correspondientes al vector de botones.
#define BUTTON_RIGHT 1

#define FIRST_IMAGE_BOARD(button_actual) (MAX_IMAGES_IN_THE_BOARD * button_actual)
#define LAST_IMAGE_BOARD(button_actual) (MAX_IMAGES_IN_THE_BOARD * (button_actual + 1))

class board
{
	public:
		board(int width, int height, vector<ImageDescriptor> & blocks_images, vector<ImageDescriptor> & buttons, vector<MerkleNode> merkleTrees);
		~board();

		void refresh(void);
		void touch(unsigned int cordx_touch, unsigned int cordy_touch);

		bool is_some_image_select(void);

		void set_image_size(unsigned int sizeX_, unsigned int sizeY_);
		void set_button_size(unsigned int botonSizeX, unsigned int botonSizeY);

		vector <ImageDescriptor> & get_block_images(void);
		vector <ImageDescriptor> & get_buttons(void);

		int get_size_x(void);
		int get_size_y(void);

		int get_margin_x(void);
		int get_margin_y(void);

		int get_actual_board(void);
		int get_cant(void);

		bool is_images_error(void);

		vector<MerkleNode> & get_merkle_trees(void);
		
		void set_merkle_trees(vector<MerkleNode> & new_merkle_trees);
		void set_blocks_images(vector<ImageDescriptor> & new_blocks_images);



	private:

		vector<ImageDescriptor> blocks_images;
		vector<ImageDescriptor> buttons;
		vector<MerkleNode> merkleTrees;

		unsigned int image_size_x; //tamaño de cada image
		unsigned int image_size_y;

		unsigned int button_size_x; //tamaño de los botones
		unsigned int button_size_y;

		unsigned int margin_x; //margenes
		unsigned int margin_y;

		unsigned int width; //dimensiones del damero
		unsigned int height;

		unsigned int board_actual; // de cero a la cantidad de board -1
		unsigned int board_cant; // cantidad de board

		void change_board(int button_pressed);
};




#endif // !BOARD_H

