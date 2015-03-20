# GBitmap-Colour-Palette-Manipulator

This library was created in order to manipulate the color palettes of gbitmaps. It will be useful if you are trying to adapt your black and white pebble app and app icons for Pebble Time (colors). Instead of including resources for each color of an icon, you can just change it's color palette with this library.

The library includes a sample project which loads a picture and spits out its color palette. You can then decide which colors to replace. 

The following library calls are available:
```c
char* get_gbitmapformat_text(GBitmapFormat format);
```
This function will return the GBitmapFormat for the given GBitmapFormat.

```c
char* get_gcolor_text(GColor m_color);
```
This function will return the text of the given GColor (ex: "GColorDukeBlue")

```c
bool gbitmap_color_palette_contains_color(GColor m_color, GBitmap *im);
```
This function will return true if the provided gbitmap contains the specified color. False otherwise. 

```c
void spit_gbitmap_color_palette(GBitmap *im);
```
This function will spit out the number of colors in a gbitmap and will list which colors it contains. This is one of the most important functions in this library since you'll want to pass your gbitmap to it the first time in order to determine which colors it contains; which you'll use in the next function.

```c
void replace_gbitmap_color(GColor color_to_replace, GColor replace_with_color, GBitmap *im, BitmapLayer *bml);
```
This is function allows you to pass in a gbitmap, the color you want to replace and the target color. You also pass your BitmapLayer to this function so that it can automatically be marked dirty. This is an all in one function; it replaces the specified color and automatically updates the BitmapLayer.

Enjoy and feel free to provide feedback or ideas.

Jonathan.
