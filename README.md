# GBitmap-Colour-Palette-Manipulator

This library was created in order to manipulate the color palettes of gbitmaps at runtime. It will be useful if you are trying to adapt your black and white pebble app and app icons for Pebble Time (colors). Instead of including resources for each color of an image/icon, you can just change it's color palette with this library.

The library includes a sample project which loads a picture and spits out its color palette. You can then decide which colors to replace. 

Before you start. Ensure that your resources are of type ```pbi8``` or ```png``` in your ```appinfo.json``` file. Black and White images must be of type ```pbi8``` or they will be imported as 1 bit non paletized images. Resources of type ```pbi``` will not work since they do not have a color palette.

```c
"resources": {
        "media": [
            {
                "file": "images/android_bw.png",
                "name": "IMAGE_ANDROID",
                "type": "pbi8"
            },
            {
                "file": "images/star.png",
                "name": "IMAGE_STAR",
                "type": "png"
            }
        ]
    },
  ```

**The following library calls are available:**
```c
char* get_gbitmapformat_text(GBitmapFormat format);
```
This function will return the GBitmapFormat text for the given GBitmapFormat.

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
void gbitmap_fill_all_except(GColor color_to_not_change, GColor fill_color, bool fill_gcolorclear, GBitmap *im, BitmapLayer *bml);
```
This function will replace all colors in the gbitmap's palette except for the color your specify not to change. Tip: Very useful for filling the background color of a icon. I use this before setting a new icon color to clean up any stray colors, leaving only the background color and icon color. Pass NULL to *bml if you do not want to update a BitmapLayer (useful for gbitmaps on your action bar). Allows you to set whether you want GColorClear to be replaced with the fill color.

```c
void replace_gbitmap_color(GColor color_to_replace, GColor replace_with_color, GBitmap *im, BitmapLayer *bml);
```
This is function allows you to pass in a gbitmap, the color you want to replace and the target color. You also pass your BitmapLayer to this function so that it can automatically be marked dirty. This is an all in one function; it replaces the specified color and automatically updates the BitmapLayer. Pass NULL to *bml if you do not want to update a BitmapLayer (useful for gbitmaps on your action bar).

**Including the library in your project**

- 1) Copy ```gbitmap_color_palette_manipulator.c``` and ```gbitmap_color_palette_manipulator.h``` into your project.
- 2) Include the following at the top of your C file ```#include "gbitmap_color_palette_manipulator.h"```.
- 3) Use the functions you require.
- 4) IMPORTANT: Comment out ```#define SHOW_APP_LOGS``` when deploying your production app. Otherwise, calls to the library will be slowed down by redundant text display function calls while the app is running on your user's devices.

**Example uses**

**Cleaning up Black and White images for better color manipulation.**
This will set all palette entries to White except for the Black of your image/icon:
- 1) Ensure that the Black and White image is of resource type ```pbi8``` in your ```appinfo.json``` file.
- 2) Create the gbitmap from resource.
- 3) Perform the following function call on the gbitmap ```gbitmap_fill_all_except(GColorBlack, GColorWhite, true, your_gbitmap, NULL);```
- 4) The gbitmap now has a palette that contains only Black (for the icon) and White (as the icon background). You can now manipulate the palette of this gbitmap more efficiently.

Credits:
I'd like to thank @gregoiresage and @ron064 for their contributions to the library.

Jonathan.
