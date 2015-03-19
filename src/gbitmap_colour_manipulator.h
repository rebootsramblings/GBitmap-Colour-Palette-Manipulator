#include <pebble.h>

#ifdef PBL_COLOR
char* get_gbitmapformat_text(GBitmapFormat format);
char* get_gcolor_text(GColor m_color);
void replace_gbitmap_colour(GColor colour_to_replace, GColor replace_with_colour, GBitmap *im, BitmapLayer *bml);
void spit_gbitmap_colour_palette(GBitmap *im);
#endif