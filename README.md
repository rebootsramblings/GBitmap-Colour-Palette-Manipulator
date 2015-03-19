# GBitmap-Colour-Palette-Manipulator

This library was created in order to manipulate the colour palettes of gbitmaps. It will be useful if you are trying to adapt your black and white pebble app and app icons for Pebble Time (colours). Instead of including resources for each colour of an icon, you can just change it's colour palette with this library.

The library includes a sample project which loads a picture and spits out its colour palette. You can then decide which colours to replace. 

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
void spit_gbitmap_colour_palette(GBitmap *im);
```
This function will spit out the number of colours in a gbitmap and will list which colours it contains. This is one of the most important functions in this library since you'll want to pass your gbitmap to it the first time in order to determine which colours it contains; which you'll use in the next function.

```c
void replace_gbitmap_colour(GColor colour_to_replace, GColor replace_with_colour, GBitmap *im, BitmapLayer *bml);
```
This is function allows you to pass in a gbitmap, the colour you want to replace and the target colour. You also pass your BitmapLayer to this function so that it can automatically be marked dirty. This is an all in one function; it replaces the specified colour and automatically updates the BitmapLayer.

Enjoy and feel free to provide feedback or ideas.

Jonathan.
