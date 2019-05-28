#include "ImageDescriptor.h"
#include "Definitions.h"

#define ASCII_BARRA_INV 92 // de '\'

#define MAX_SIZE_FILENAME 50

//listo
ImageDescriptor::ImageDescriptor()
{
	this->error = true;
	this->bitmap = nullptr;
	this->width = 0;
	this->height = 0;

}

//listo
ImageDescriptor::ImageDescriptor(const char * path_image) :path(path_image)
{
	this->file_name = extract_name_file(path_image);
	this->error = false;
	this->bitmap = resize_image(path_image, IMAGE_SIZE_X, IMAGE_SIZE_Y);

	if (bitmap == nullptr)
	{
		this->error = true;
	}

	ALLEGRO_BITMAP * aux_image = al_load_bitmap(path_image);

	if (aux_image == nullptr)
	{
		this->error = true;
	}
	else
	{
		this->width = al_get_bitmap_width(aux_image);
		this->height = al_get_bitmap_height(aux_image);
		al_destroy_bitmap(aux_image);
	}

}

ImageDescriptor::ImageDescriptor(const char * path_image, int no_image) : path(path_image)
{
	if (no_image == FLAG_NO_IMAGE_DESCOMPR)
	{
		this->file_name = extract_name_file(path_image);
	}
	
}

//listo
ImageDescriptor::~ImageDescriptor()
{
	
}

//listo
bool ImageDescriptor::is_select(void)
{
	return (this->image_selected);
}

//listo
void ImageDescriptor::toggle_selection(void)
{
	(this->image_selected) = !(this->image_selected);
}

//listo
void ImageDescriptor::set_pos(int pos_x, int pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

//listo
int ImageDescriptor::get_pos_x(void)
{
	return (this->pos_x);
}

//listo
int ImageDescriptor::get_pos_y(void)
{
	return (this->pos_y);
}

//listo
unsigned int ImageDescriptor::get_width()
{
	return (this->width);
}

//listo
unsigned int ImageDescriptor::get_heigth()
{
	return (this->height);
}

//listo
const char * ImageDescriptor::get_path(void)
{
	return (this->path);
}

//listo
const char * ImageDescriptor::get_name_file(void)
{
	return ((this->file_name).c_str());
}

//listo
ALLEGRO_BITMAP * ImageDescriptor::get_bitmap(void)
{
	return (this->bitmap);
}

//listo
bool ImageDescriptor::get_error(void)
{
	return (this->error);
}


//listo
string ImageDescriptor::extract_name_file(const char * image_path) 
{
	string aux (image_path);
	string aux_reverse;
	string name_file = ".-";


	int j = 0;

	for (int i = (int)aux.size(); (i > 0) && (aux.back() != '/') && (j < MAX_SIZE_FILENAME) ; i--, j++) //guardo el fileName en un string auxiliar, maximo filename es MAX_SIZE_FILENAME
	{																				
		aux_reverse.push_back(aux.back());
		aux.pop_back();
	}


	//hasta aqui se obtuvo un string del nombre pero con las letras ordenadas alrevés
	for (int i = (int)aux_reverse.size(); i > 0; i--) //doy vuelta el string
	{
		name_file.push_back(aux_reverse.back());
		aux_reverse.pop_back();
	}
	return name_file;
}
