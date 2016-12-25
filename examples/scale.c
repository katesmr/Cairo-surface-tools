#include <cairo.h>
#include "../src/cairo_surface_tools.h"

#define scale_delta 0.6

int main()
{
	cairo_surface_t *surface_dest; 
	cairo_surface_t *img; 
	cairo_t *cr_dest; 

	img = cairo_image_surface_create_from_png("cat.png"); 
	int width = cairo_image_surface_get_width(img); 
  	int height = cairo_image_surface_get_height(img); 
 
 	/* create surface for result image */
	surface_dest = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width*scale_delta, height*scale_delta); 
	cr_dest = cairo_create(surface_dest); 

	rescale(cr_dest, img, scale_delta, scale_delta);

	cairo_surface_write_to_png(surface_dest, "res.png"); /* save result */

	/* free memory */
	cairo_destroy(cr_dest); 
	cairo_surface_destroy(img); 
	cairo_surface_destroy(surface_dest); 

	return 0;
}
