#include <cairo.h>
#include "../src/cairo_surface_tools.h"

int main()
{
	cairo_surface_t *surface_dest; 
	cairo_surface_t *surface_gradient; 
	cairo_surface_t *img; 
	cairo_t *cr_dest; 
	cairo_t *cr_gradient;

	int w, h; 

	img = cairo_image_surface_create_from_png("cat.png"); 
	w = cairo_image_surface_get_width(img); 
	h = cairo_image_surface_get_height(img); 

	surface_dest = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h); /* create surface for result image */
	cr_dest = cairo_create(surface_dest); 

	surface_gradient = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h); /* create surface for gradient */
	cr_gradient = cairo_create(surface_gradient);

	draw_gradient(cr_gradient, 0.4);
	merge(cr_dest, img, surface_gradient, CAIRO_OPERATOR_HSL_HUE);

	cairo_surface_write_to_png(surface_dest, "res.png"); /* save result */

	/* free memory */ 
	cairo_destroy(cr_dest); 
	cairo_surface_destroy(surface_dest); 
	cairo_surface_destroy(img); 
	cairo_destroy(cr_gradient); 
	cairo_surface_destroy(surface_gradient); 

	return 0;
}
