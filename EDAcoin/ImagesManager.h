#pragma once

#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

void destroy_images(ALLEGRO_BITMAP ** blocks_images, unsigned int cant_images);

ALLEGRO_BITMAP * resize_image(const char* path_image, int resize_x, int resize_y);

ALLEGRO_BITMAP * resize_bitmap(ALLEGRO_BITMAP * bitmap, int resize_x, int resize_y);


#endif // !IMAGE_MANAGER_H

