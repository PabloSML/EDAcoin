#include "ImageDescriptor.h"
#include "Definitions.h"


//listo

//**Se necesita este constructor? Se podria construir un ImageDescriptor sin un path?
ImageDescriptor::ImageDescriptor()
{
	this->error = true;
	this->bitmap = nullptr;
	this->width = 0;
	this->height = 0;

	//**this->image_selected = false;
	//**this->path = nullptr;
	//**this->image_name = "Noname";


}

//listo
/*
Constructor:
-Crea un bitmap con el path de la imagen.
-Guarda el tamano original de la imagen en width y height.
*/
ImageDescriptor::ImageDescriptor(const char * path_image) :path(path_image)
{
	this->error = false;
	this->bitmap = resize_image(path_image, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	//**this->path = path_image;

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
const char * ImageDescriptor::get_image_name(void)
{
	return ((this->image_name).c_str());
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


void ImageDescriptor::set_image_name(string image_name)
{
	this->image_name = image_name;
}

