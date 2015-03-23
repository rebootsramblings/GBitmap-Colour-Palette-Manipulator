
#include "gbitmap_color_palette_manipulator.h"

#ifdef PBL_COLOR

#define SHOW_APP_LOGS true

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

	if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette has %d items", num_palette_items);

	//Get the gbitmap's current palette
	GColor *current_palette = gbitmap_get_palette(im);

	//Iterate through the palette finding the color we want to replace and replacing 
	//it with the new color
	if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "--Replace Color Start--");
	for(int i = 0; i < num_palette_items; i++){

		if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette[%d] = %s", i, get_gcolor_text(current_palette[i]));


		if ((color_to_replace.argb & 0x3F)==(current_palette[i].argb & 0x3F)){

			current_palette[i].argb = (current_palette[i].argb & 0xC0)| (replace_with_color.argb & 0x3F);
			if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "-------[%d] replaced with %s", i, get_gcolor_text(current_palette[i]) );

			//break;//the color should only appear once in the palette
		}

	}
	if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "--Replace Color End--");

	//Mark the bitmaplayer dirty
	if(bml != NULL){
		layer_mark_dirty(bitmap_layer_get_layer(bml));
	}

}

void gbitmap_fill_all_except(GColor color_to_not_change, GColor fill_color, GBitmap *im, BitmapLayer *bml){

	//First determine what the number of colors in the palette
	int num_palette_items = get_num_palette_colors(im);

	if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette has %d items", num_palette_items);

	//Get the gbitmap's current palette
	GColor *current_palette = gbitmap_get_palette(im);

	//Iterate through the palette replacing all colors except the color_to_not_change
	if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "--Color Fill Start--");
	for(int i = 0; i < num_palette_items; i++){

		if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "Palette[%d] = %s", i, get_gcolor_text(current_palette[i]));

		if(!GColorEq(color_to_not_change, current_palette[i])){
			current_palette[i] = fill_color;
			if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "-------[%d] filled with %s", i, get_gcolor_text(current_palette[i]) );
		}

	}
	if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "--Color Fill End--");

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
			if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "GBitmap contains: %s", get_gcolor_text(current_palette[i]));

			return true;
		}

	}

	if(SHOW_APP_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "GBitmap does not contain: %s", get_gcolor_text(m_color));
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
	if(GColorEq(m_color, GColorClear))
		return "GColorClear";
	return GColorsNames[m_color.argb & 0x3F];
/*
	m_color.argb|=0xC0; //optional method
	if(GColorEq(m_color, GColorBlack)){ return "GColorBlack";}
	else if(GColorEq(m_color, GColorOxfordBlue)){ return "GColorOxfordBlue";}
	else if(GColorEq(m_color, GColorDukeBlue)){ return "GColorDukeBlue";}
	else if(GColorEq(m_color, GColorBlue)){ return "GColorBlue";}
	else if(GColorEq(m_color, GColorDarkGreen)){ return "GColorDarkGreen";}
	else if(GColorEq(m_color, GColorMidnightGreen)){ return "GColorMidnightGreen";}
	else if(GColorEq(m_color, GColorCobaltBlue)){ return "GColorCobaltBlue";}
	else if(GColorEq(m_color, GColorBlueMoon)){ return "GColorCobaltBlue";}
	else if(GColorEq(m_color, GColorIslamicGreen)){ return "GColorIslamicGreen";}
	else if(GColorEq(m_color, GColorJaegerGreen)){ return "GColorJaegerGreen";}
	else if(GColorEq(m_color, GColorTiffanyBlue)){ return "GColorTiffanyBlue";}
	else if(GColorEq(m_color, GColorVividCerulean)){ return "GColorVividCerulean";}
	else if(GColorEq(m_color, GColorGreen)){ return "GColorGreen";}
	else if(GColorEq(m_color, GColorMalachite)){ return "GColorMalachite";}
	else if(GColorEq(m_color, GColorMediumSpringGreen)){ return "GColorMediumSpringGreen";}
	else if(GColorEq(m_color, GColorCyan)){ return "GColorCyan";}
	else if(GColorEq(m_color, GColorBulgarianRose)){ return "GColorBulgarianRose";}
	else if(GColorEq(m_color, GColorImperialPurple)){ return "GColorImperialPurple";}
	else if(GColorEq(m_color, GColorIndigo)){ return "GColorIndigo";}
	else if(GColorEq(m_color, GColorElectricUltramarine)){ return "GColorElectricUltramarine";}
	else if(GColorEq(m_color, GColorArmyGreen)){ return "GColorArmyGreen";}
	else if(GColorEq(m_color, GColorDarkGray)){ return "GColorDarkGray";}
	else if(GColorEq(m_color, GColorLiberty)){ return "GColorLiberty";}
	else if(GColorEq(m_color, GColorVeryLightBlue)){ return "GColorVeryLightBlue";}
	else if(GColorEq(m_color, GColorKellyGreen)){ return "GColorKellyGreen";}
	else if(GColorEq(m_color, GColorMayGreen)){ return "GColorMayGreen";}
	else if(GColorEq(m_color, GColorCadetBlue)){ return "GColorCadetBlue";}
	else if(GColorEq(m_color, GColorPictonBlue)){ return "GColorPictonBlue";}
	else if(GColorEq(m_color, GColorBrightGreen)){ return "GColorBrightGreen";}
	else if(GColorEq(m_color, GColorScreaminGreen)){ return "GColorScreaminGreen";}
	else if(GColorEq(m_color, GColorMediumAquamarine)){ return "GColorMediumAquamarine";}
	else if(GColorEq(m_color, GColorElectricBlue)){ return "GColorElectricBlue";}
	else if(GColorEq(m_color, GColorDarkCandyAppleRed)){ return "GColorDarkCandyAppleRed";}
	else if(GColorEq(m_color, GColorJazzberryJam)){ return "GColorJazzberryJam";}
	else if(GColorEq(m_color, GColorPurple)){ return "GColorPurple";}
	else if(GColorEq(m_color, GColorVividViolet)){ return "GColorVividViolet";}
	else if(GColorEq(m_color, GColorWindsorTan)){ return "GColorWindsorTan";}
	else if(GColorEq(m_color, GColorRoseVale)){ return "GColorWindsorTan";}
	else if(GColorEq(m_color, GColorPurpureus)){ return "GColorPurpureus";}
	else if(GColorEq(m_color, GColorLavenderIndigo)){ return "GColorLavenderIndigo";}
	else if(GColorEq(m_color, GColorLimerick)){ return "GColorLimerick";}
	else if(GColorEq(m_color, GColorBrass)){ return "GColorBrass";}
	else if(GColorEq(m_color, GColorLightGray)){ return "GColorLightGray";}
	else if(GColorEq(m_color, GColorBabyBlueEyes)){ return "GColorBabyBlueEyes";}
	else if(GColorEq(m_color, GColorSpringBud)){ return "GColorSpringBud";}
	else if(GColorEq(m_color, GColorInchworm)){ return "GColorInchworm";}
	else if(GColorEq(m_color, GColorMintGreen)){ return "GColorMintGreen";}
	else if(GColorEq(m_color, GColorCeleste)){ return "GColorCeleste";}
	else if(GColorEq(m_color, GColorRed)){ return "GColorRed";}
	else if(GColorEq(m_color, GColorFolly)){ return "GColorFolly";}
	else if(GColorEq(m_color, GColorFashionMagenta)){ return "GColorFashionMagenta";}
	else if(GColorEq(m_color, GColorMagenta)){ return "GColorMagenta";}
	else if(GColorEq(m_color, GColorOrange)){ return "GColorOrange";}
	else if(GColorEq(m_color, GColorSunsetOrange)){ return "GColorSunsetOrange";}
	else if(GColorEq(m_color, GColorBrilliantRose)){ return "GColorBrilliantRose";}
	else if(GColorEq(m_color, GColorShockingPink)){ return "GColorShockingPink";}
	else if(GColorEq(m_color, GColorChromeYellow)){ return "GColorChromeYellow";}
	else if(GColorEq(m_color, GColorRajah)){ return "GColorRajah";}
	else if(GColorEq(m_color, GColorMelon)){ return "GColorMelon";}
	else if(GColorEq(m_color, GColorRichBrilliantLavender)){ return "GColorRichBrilliantLavender";}
	else if(GColorEq(m_color, GColorYellow)){ return "GColorYellow";}
	else if(GColorEq(m_color, GColorIcterine)){ return "GColorIcterine";}
	else if(GColorEq(m_color, GColorPastelYellow)){ return "GColorPastelYellow";}
	else if(GColorEq(m_color, GColorWhite)){ return "GColorWhite";}

	return "UNKNOWN COLOR";
*/

}
#endif	
