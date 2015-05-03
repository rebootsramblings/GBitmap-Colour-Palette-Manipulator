
#include "gbitmap_color_palette_manipulator.h"

static Window *window = NULL;
static BitmapLayer *b_layer = NULL;
static GBitmap *image = NULL;
static TextLayer *m_text_l = NULL;

#ifdef PBL_COLOR
static void display_gbitmapformat_text(GBitmap *b);
#endif

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	#ifdef PBL_COLOR
	if(gbitmap_color_palette_contains_color(GColorSunsetOrange, image)){
		gbitmap_fill_all_except(GColorSunsetOrange, GColorMayGreen, true, image, b_layer);
	}
	#endif

}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	#ifdef PBL_COLOR
		replace_gbitmap_color(GColorSunsetOrange, GColorDukeBlue, image, b_layer);
		//replace_image_color(GColorBlack, GColorDukeBlue, image, b_layer);
	#endif

}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	#ifdef PBL_COLOR
		replace_gbitmap_color(GColorDukeBlue, GColorSunsetOrange, image, b_layer);
		//replace_image_color(GColorDukeBlue, GColorBlack, image, b_layer);
	#endif

}

static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}



static void window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

	b_layer = bitmap_layer_create(GRect(0, 20, 144, 144));
	bitmap_layer_set_background_color(b_layer , GColorClear);

	m_text_l = text_layer_create(GRect(0, 0, 144-5, 20));
	text_layer_set_text_color(m_text_l, GColorBlack);
	text_layer_set_background_color(m_text_l, GColorWhite);
	text_layer_set_font(m_text_l, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));


	layer_add_child(window_layer, bitmap_layer_get_layer(b_layer));
	layer_add_child(window_layer, text_layer_get_layer(m_text_l));


	#ifdef PBL_COLOR
	//NOTE: Image is loaded with black background because it's a transparent PNG
	image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_STAR);
	bitmap_layer_set_bitmap(b_layer, image);
	spit_gbitmap_color_palette(image);

	//Function demo
	gbitmap_color_palette_contains_color(GColorSunsetOrange, image);

	//Display the format of the image
	display_gbitmapformat_text(image);

	#endif
}

static void window_unload(Window *window) {
	bitmap_layer_destroy(b_layer);
	gbitmap_destroy(image);
	text_layer_destroy(m_text_l);
}

static void init(void) {
	window = window_create();
	window_set_click_config_provider(window, click_config_provider);
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});
	const bool animated = true;
	window_stack_push(window, animated);
}

static void deinit(void) {
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}

#ifdef PBL_COLOR

static void display_gbitmapformat_text(GBitmap *b){

	GBitmapFormat format = gbitmap_get_format(b);
	char * format_text =  get_gbitmapformat_text(format);
	text_layer_set_text(m_text_l, format_text);

}
#endif
