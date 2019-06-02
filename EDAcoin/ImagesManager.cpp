#include "ImagesManager.h"

void destroy_images(ALLEGRO_BITMAP ** blocks_images, unsigned int cant_images)
{
	for (unsigned int i = 0; i < cant_images; i++)
	{
		al_destroy_bitmap(blocks_images[i]);
	}
}

/*
Genera un bitmap con el tamano que se determina a partir de la direccion de una imagen.
path_image: path a la imagen.
resize_x: ancho de la imagen.
resize_y: alto de la imagen.
*/
ALLEGRO_BITMAP * resize_image(const char* path_image, int resize_x, int resize_y)
{
	bool all_ok = true;

	ALLEGRO_BITMAP * image = nullptr;
	ALLEGRO_BITMAP * image_resize = nullptr;
	ALLEGRO_BITMAP * current_target = nullptr;

	int width_actual = 0;
	int height_actual = 0;

	current_target = al_get_target_bitmap(); 

	image = al_load_bitmap(path_image);		//cargo la imagen.

	if (image == nullptr)		//si falla...
	{
		all_ok = false;
		//**Seria conveniente poner un "return nullptr;"?
	}

	if (all_ok == true)			//si se pudo cargar la imagen... 
	{
		width_actual = al_get_bitmap_width(image);			//obtengo el ancho y alto de la imagen real.
		height_actual = al_get_bitmap_height(image);
		image_resize = al_create_bitmap(resize_x, resize_y);	//creo un bitmap con el ancho y el alto ingresado.
	}

	
	if (image_resize == nullptr)		//si no se pudo crear la imagen...
	{
		al_destroy_bitmap(image);
		all_ok = false;
	}

	if (all_ok == true)			//si se creo bien la imagen...
	{
		al_set_target_bitmap(image_resize);			//Pongo como target del bitmap creado.
		al_draw_scaled_bitmap(image, 0, 0, width_actual, height_actual, 0, 0, resize_x, resize_y, 0);		//Dibujo sobre ella la imagen cambiando el ancho y alto.

		al_set_target_bitmap(current_target); //vuelve al target original
		al_destroy_bitmap(image);
	}

	
	return image_resize;		//Devuelvo el puntero al bitmap creado.
}

/*
Genera un bitmap con el tamano que se determina a partir de otro bitmap.
resize_x: ancho de la imagen.
resize_y: alto de la imagen.
*/

ALLEGRO_BITMAP * resize_bitmap(ALLEGRO_BITMAP * bitmap, int resize_x, int resize_y)
{
	bool all_ok = true;

	ALLEGRO_BITMAP * image_resize = nullptr;
	ALLEGRO_BITMAP * current_target = nullptr;

	int width_actual = 0;
	int height_actual = 0;

	current_target = al_get_target_bitmap();

	
	width_actual = al_get_bitmap_width(bitmap);
	height_actual = al_get_bitmap_height(bitmap);
	image_resize = al_create_bitmap(resize_x, resize_y);
	


	if (image_resize == nullptr)
	{
		al_destroy_bitmap(bitmap);		//**No deberia destruir el bitmap que le pasan por parametro.
		all_ok = false;
	}

	if (all_ok == true)
	{
		al_set_target_bitmap(image_resize);
		al_draw_scaled_bitmap(bitmap, 0, 0, width_actual, height_actual, 0, 0, resize_x, resize_y, 0);

		al_set_target_bitmap(current_target); //vuelve al target original
	}


	return image_resize;

}
