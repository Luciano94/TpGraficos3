#ifndef _DEBUG
#define ALLEGRO_STATICLINK
#endif // !_DEBUG
#define PLAYER_FILE "player.png"
#define ENEMY_FILE "enemy.png"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
/*constantes*/
const float FPS = 60;		//tasa de fps
const int SCREEN_W = 640;	//ancho de pantalla
const int SCREEN_H = 480;	//largo de pantalla
const int PLAYER_SIZE = 32;	//tama�o de imagen de  jugador
const int ENEMY_SIZE = 32;	// tama�o de imagen de enemigo

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;					// pantalla
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;			//cola de eventos
	ALLEGRO_TIMER *timer = NULL;						//timer de juego
	ALLEGRO_BITMAP *player = NULL;						//bitmap de player
	ALLEGRO_BITMAP *enemy = NULL;						// bitmap de enemigo
	float player_x = SCREEN_W / 2.0 - PLAYER_SIZE / 2.0;//posicion en x de player
	float player_y = SCREEN_H / 2.0 - PLAYER_SIZE / 2.0;//posicion en y de player
	float enemy_x = 0;									//posicion en x de enemigo
	float enemy_y = 0;									//posicion en y de enemigo
	bool redraw = true;
	bool doexit = false;
	/*inicializo allegro*/
	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	/*inicializo addon para cargar imagenes*/
	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}
	/*inicializo el timer del juego*/
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize timer!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	/*inicializo la ventana*/
	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_timer(timer);
		return -1;
	}
	/*cargo la imagen del player*/
	player = al_load_bitmap(PLAYER_FILE);
	if (!player) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load bouncer!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	/*cargo la imagen del enemigo*/
	enemy = al_load_bitmap(ENEMY_FILE);
	if (!enemy) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load bouncer!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	/*inicializo cola de eventos*/
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize event queue!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_bitmap(player);
		al_destroy_bitmap(enemy);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display)); //inicializo eventos de ventana

	al_register_event_source(event_queue, al_get_timer_event_source(timer)); //inicializo eventos de timer

	al_clear_to_color(al_map_rgb(0, 0, 0)); //pongo pantalla en negro

	al_flip_display();

	al_start_timer(timer); //inicio el timer
	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(player, player_x, player_y, 0);

			al_draw_bitmap(enemy, enemy_x, enemy_y, 0);

			al_flip_display();
		}
	}

	al_destroy_bitmap(player);
	al_destroy_bitmap(enemy);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}