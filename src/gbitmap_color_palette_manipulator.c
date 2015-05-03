
#include "gbitmap_color_palette_manipulator.h"

#ifdef PBL_COLOR

#define SHOW_APP_LOGS

char* get_gbitmapformat_text(GBitmapFormat format){
	switch (format) {
		case GBitmapFormat1Bit: return "GBitmapFormat1Bit";
		case GBitmapFormat8Bit: return "GBitmapFormat8Bit";
		case GBitmapFormat1BitPalette: return "GBitmapFormat1BitPalette";
		case GBitmapFormat2BitPalette: return "GBitmapFormat2BitPalette";
		case GBitmapFormat4BitPalette: return "GBitmapFormat4BitPalette";

		default: return "UNKNOWN FORMAT";
	}

}

int get_num_palette_colors(GBitmap *b){

	GBitmapFormat format = gbitmap_get_format(b);

	switch (format) {
		case GBitmapFormat1Bit: return 0;
		case GBitmapFormat8Bit: return 0;
		case GBitmapFormat1BitPalette: return 2;
		case GBitmapFormat2BitPalette: return 4;
		case GBitmapFormat4BitPalette: return 16;

		default: return 0;
	}

}

void replace_gbitmap_color(GColor color_to_replace, GColor replace_with_color, GBitmap *im, BitmapLayer *bml){

	//First determine what the number of colors in the palette
	int num_palette_items = get_num_palette_colors(im);

	#ifdef SHOW_APP_LOGS
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette has %d items", num_palette_items);
	#endif

	//Get the gbitmap's current palette
	GColor *current_palette = gbitmap_get_palette(im);

	//Iterate through the palette finding the color we want to replace and replacing 
	//it with the new color
	#ifdef SHOW_APP_LOGS
	APP_LOG(APP_LOG_LEVEL_DEBUG, "--Replace Color Start--");
	#endif 

	for(int i = 0; i < num_palette_items; i++){

		#ifdef SHOW_APP_LOGS
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette[%d] = %s (alpha:%d)", i, get_gcolor_text(current_palette[i]),(current_palette[i].argb >>6));
		#endif

		if ((color_to_replace.argb & 0x3F)==(current_palette[i].argb & 0x3F)){

			current_palette[i].argb = (current_palette[i].argb & 0xC0)| (replace_with_color.argb & 0x3F);
			#ifdef SHOW_APP_LOGS
			APP_LOG(APP_LOG_LEVEL_DEBUG, "-------[%d] replaced with %s (alpha:%d)", i, get_gcolor_text(current_palette[i]),(current_palette[i].argb >>6));
			#endif
			
		}

	}

	#ifdef SHOW_APP_LOGS
	APP_LOG(APP_LOG_LEVEL_DEBUG, "--Replace Color End--");
	#endif

	//Mark the bitmaplayer dirty
	if(bml != NULL){
		layer_mark_dirty(bitmap_layer_get_layer(bml));
	}

}

void gbitmap_fill_all_except(GColor color_to_not_change, GColor fill_color, bool fill_gcolorclear, GBitmap *im, BitmapLayer *bml){

	//First determine what the number of colors in the palette
	int num_palette_items = get_num_palette_colors(im);

	#ifdef SHOW_APP_LOGS
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette has %d items", num_palette_items);
	#endif

	//Get the gbitmap's current palette
	GColor *current_palette = gbitmap_get_palette(im);

	//Iterate through the palette replacing all colors except the color_to_not_change
	#ifdef SHOW_APP_LOGS
	APP_LOG(APP_LOG_LEVEL_DEBUG, "--Color Fill Start--");
	#endif

	for(int i = 0; i < num_palette_items; i++){

		#ifdef SHOW_APP_LOGS
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette[%d] = %s", i, get_gcolor_text(current_palette[i]));
		#endif

		if(!gcolor_equal(color_to_not_change, current_palette[i])){//all colors except color_to_not_change
			if((gcolor_equal(current_palette[i], GColorClear) && fill_gcolorclear) || !gcolor_equal(current_palette[i], GColorClear)){
				current_palette[i] = fill_color;
				#ifdef SHOW_APP_LOGS
				APP_LOG(APP_LOG_LEVEL_DEBUG, "-------[%d] filled with %s", i, get_gcolor_text(current_palette[i]) );
				#endif
			}
		}

	}
	#ifdef SHOW_APP_LOGS
	APP_LOG(APP_LOG_LEVEL_DEBUG, "--Color Fill End--");
	#endif

	//Mark the bitmap layer dirty
	if(bml != NULL){
		layer_mark_dirty(bitmap_layer_get_layer(bml));
	}

}

bool gbitmap_color_palette_contains_color(GColor m_color, GBitmap *im){

	int num_palette_items = get_num_palette_colors(im);
	GColor *current_palette = gbitmap_get_palette(im);
	for(int i = 0; i < num_palette_items; i++){

		if ((m_color.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			#ifdef SHOW_APP_LOGS
			APP_LOG(APP_LOG_LEVEL_DEBUG, "GBitmap contains: %s", get_gcolor_text(current_palette[i]));
			#endif

			return true;
		}

	}

	#ifdef SHOW_APP_LOGS
	APP_LOG(APP_LOG_LEVEL_DEBUG, "GBitmap does not contain: %s", get_gcolor_text(m_color));
	#endif

	return false;

}

void spit_gbitmap_color_palette(GBitmap *im){

	//First determine what the number of colors in the palette
	int num_palette_items = get_num_palette_colors(im);

	APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette has %d items", num_palette_items);

	GColor *current_palette = gbitmap_get_palette(im);

	APP_LOG(APP_LOG_LEVEL_DEBUG, "--Spit Palette Start--");
	for(int i = 0; i < num_palette_items; i++){

		APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette[%d] = %s (alpha:%d)", i, get_gcolor_text(current_palette[i]),(current_palette[i].argb >>6) );

	}
	APP_LOG(APP_LOG_LEVEL_DEBUG, "--Spit Palette End--");

}

const char * GColorsNames[]= {
 "GColorBlack", "GColorOxfordBlue", "GColorDukeBlue", "GColorBlue", 
 "GColorDarkGreen", "GColorMidnightGreen", "GColorCobaltBlue", "GColorBlueMoon", 
 "GColorIslamicGreen", "GColorJaegerGreen", "GColorTiffanyBlue", "GColorVividCerulean", 
 "GColorGreen", "GColorMalachite", "GColorMediumSpringGreen", "GColorCyan", 
 "GColorBulgarianRose", "GColorImperialPurple", "GColorIndigo", "GColorElectricUltramarine", 
 "GColorArmyGreen", "GColorDarkGray", "GColorLiberty", "GColorVeryLightBlue", 
 "GColorKellyGreen", "GColorMayGreen", "GColorCadetBlue", "GColorPictonBlue",
 "GColorBrightGreen", "GColorScreaminGreen", "GColorMediumAquamarine", "GColorElectricBlue",
 "GColorDarkCandyAppleRed", "GColorJazzberryJam", "GColorPurple", "GColorVividViolet",
 "GColorWindsorTan", "GColorRoseVale", "GColorPurpureus", "GColorLavenderIndigo",
 "GColorLimerick", "GColorBrass", "GColorLightGray", "GColorBabyBlueEyes",
 "GColorSpringBud", "GColorInchworm", "GColorMintGreen", "GColorCeleste",
 "GColorRed", "GColorFolly", "GColorFashionMagenta", "GColorMagenta",
 "GColorOrange", "GColorSunsetOrange", "GColorBrilliantRose", "GColorShockingPink",
 "GColorChromeYellow", "GColorRajah", "GColorMelon", "GColorRichBrilliantLavender",
 "GColorYellow", "GColorIcterine", "GColorPastelYellow", "GColorWhite"
};

const char* get_gcolor_text(GColor m_color){
	if(gcolor_equal(m_color, GColorClear))
		return "GColorClear";
	return GColorsNames[m_color.argb & 0x3F];

}
#endif	
