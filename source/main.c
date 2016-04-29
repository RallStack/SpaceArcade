#include "charger.h"
#include "perso.h"
#include "path.h"

void erreur(const char*txt)
{
    ALLEGRO_DISPLAY*d;
    d=al_is_system_installed()?al_get_current_display():NULL;
    al_show_native_message_box(d,"ERREUR",txt,NULL,NULL,0);
    exit(EXIT_FAILURE);
}

int main()
{
int niveau[LARGEUR_MAP][HAUTEUR_MAP], pos[2], post[2] = {6, 5};
int lvl = 0, nbBleu = 0, mus_onoff = 0;
bool fin = false, quit = false, play = false;
char ennemi[6] = { 'e', 'n', 'n', 'e', 'm', 'i' };
char joueur[6] = { 'j', 'o', 'u', 'e', 'u', 'r' };

bool key[KEY_MAX] = { false };

al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

S_ENTITE vaisseau;
S_ENTITE ennemis;
path_directory *p_pile = NULL;
ALLEGRO_SAMPLE *sample=NULL;

/// *** Fonction d'initiaisation *** (1)

    if(!al_init())
    	erreur("al_init()");

	display=al_create_display(FENETRE_X, FENETRE_Y);
    if(!display)
        erreur("creation display");

    if(!al_install_keyboard())
        erreur("al_install_keyboard()");

    if (!al_init_image_addon())
        erreur("al_init_image_addon()");

    if (!al_install_mouse())
        erreur("al_install_mouse()");
	
    ALLEGRO_EVENT_QUEUE*queue;
    queue = al_create_event_queue();
    if(!queue)
        erreur("creation evenement");
        
    ALLEGRO_EVENT_QUEUE*souris;
    souris = al_create_event_queue();
    if(!souris)
        erreur("creation evenement");
        
    if(!al_install_audio())
    {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }

    if(!al_init_acodec_addon())
    {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "failed to reserve samples!\n");
        return -1;
    }

    sample = al_load_sample( "./musiques/musique_ambiante1.wav" );

    if (!sample)
    {
        printf( "Audio clip sample not loaded!\n" );
        return -1;
    }


    ALLEGRO_TIMER *timer;
    timer = al_create_timer(1.0 / 60.0);
	if (!timer) {
		erreur("al_create_timer");
	}

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	
	ALLEGRO_SAMPLE_INSTANCE* instance = al_create_sample_instance(sample);
    al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());

    al_set_sample_instance_playing(instance, true);
	
	al_start_timer(timer);

/// ******************************** (1)

/// *** Chargement des images en mémoire *** (2)
    buffer = al_create_bitmap(1078, 1078);
    if(!buffer)
        erreur("al_create_buffer()");
    vide = al_load_bitmap("./image/vide.png");
    if(!vide)
        erreur("al_load_vide()");
    mur = al_load_bitmap("./image/mur.png");
    if(!mur)
        erreur("al_load_mur()");
    bleu = al_load_bitmap("./image/bleu.png");
    if(!bleu)
        erreur("al_load_cristaux");
    rouge = al_load_bitmap("./image/rouge.png");
    if(!rouge)
        erreur("al_load_rouge");
        
	GUI = al_load_bitmap("./image/GUI.png");
    if(!GUI)
        erreur("al_load_GUI");
        
    on = al_load_bitmap("./image/on.png");
    if(!on)
        erreur("al_load_on");
        

/// **************************************** (2)
	
	while(!quit){

/// *** Construction du niveau *** (3)

    	charger(niveau, lvl);
    	positonPerso(pos, lvl);
    	init(&vaisseau, pos, joueur);
    	init(&ennemis, post, ennemi);
    	nbBleu = 0;
    	fin = false;

    	al_set_target_bitmap(buffer);
    	for(i = 0; i < LARGEUR_MAP; i++){
        	for(j = 0; j < HAUTEUR_MAP; j++){
        	    switch(niveau[i][j]){
        	        case VIDE:
        	            al_draw_bitmap(vide, TAILLE_BLOC*i, TAILLE_BLOC*j, 0);
        	            break;
        	        case MUR:
        	            al_draw_bitmap(mur, TAILLE_BLOC*i, TAILLE_BLOC*j, 0);
        	            break;
        	        case CRISTAUXB:
        	            al_draw_bitmap(bleu, TAILLE_BLOC*i, TAILLE_BLOC*j, 0);
        	            nbBleu++;
        	            break;
        	        case CRISTAUXR:
        	            al_draw_bitmap(rouge, TAILLE_BLOC*i, TAILLE_BLOC*j, 0);
        	            break;
        	    }
        	}
    	}

    	al_set_target_bitmap(al_get_backbuffer(display));
    	p_pile = createPath(niveau, &vaisseau, &ennemis);

/// ****************************** (3)

    	do{
			do{
				al_draw_bitmap(GUI, 0, 0, 0);
				al_wait_for_event(queue, &events);

				if(events.mouse.x > 1352 && events.mouse.x < 1646 && events.mouse.y > 443 && events.mouse.y < 541 && events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					fin = !fin;
					quit = !quit;
				}
				else if(events.mouse.x > 1352 && events.mouse.x < 1646 && events.mouse.y > 590 && events.mouse.y < 688 && events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					fin = !fin;
					quit = !quit;
				}
				else if((events.mouse.x > 1352 && events.mouse.x < 1646 && events.mouse.y > 296 && events.mouse.y < 394 && events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) ||
				(key[ESCAPE])){
					play = !play;
					key[UP] = false;
					key[RIGHT] = false;
		        	key[DOWN] = false;
		        	key[LEFT] = false;
                	key[ESCAPE] = false;
				}

				if(events.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch (events.keyboard.keycode){
		                case ALLEGRO_KEY_F1:
		                    key[F1] = true;
		                    break;
		                case ALLEGRO_KEY_F2:
		                    key[F2] = true;
		                    break;
		                case ALLEGRO_KEY_ESCAPE:
		                	key[ESCAPE] = true;
		                	break;
					}
				}
				else if(events.type == ALLEGRO_EVENT_KEY_UP)
				{
					switch (events.keyboard.keycode){
		                case ALLEGRO_KEY_F1:
		                    key[F1] = false;
		                    break;
		                case ALLEGRO_KEY_F2:
		                    key[F2] = false;
		                    break;
					}
				}

				if(key[F1]){
		            mus_onoff=0;
		            if(mus_onoff==0){
		                al_set_sample_instance_playing(instance, true);
		            }
				}
				if(key[F2]){
		            mus_onoff=1;
		            if (mus_onoff==1){
		                al_set_sample_instance_playing(instance, false);
		            }
				}

				if(mus_onoff == 0){
		            al_draw_bitmap(on, 126, 70, 0);
		        }

				al_draw_bitmap(buffer, 225, 1, 0);
				afficher(&vaisseau); afficher(&ennemis);
				al_flip_display();
			}while(!play);

			if(events.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (events.keyboard.keycode){
				    case ALLEGRO_KEY_UP:
				        key[UP] = true;
				        break;
				    case ALLEGRO_KEY_RIGHT:
				        key[RIGHT] = true;
				        break;
				    case ALLEGRO_KEY_DOWN:
				        key[DOWN] = true;
				        break;
				    case ALLEGRO_KEY_LEFT:
				        key[LEFT] = true;
				        break;
				}
			}
			else if(events.type == ALLEGRO_EVENT_KEY_UP)
			{
				switch (events.keyboard.keycode){
				    case ALLEGRO_KEY_UP:
				        key[UP] = false;
				        break;
				    case ALLEGRO_KEY_RIGHT:
				        key[RIGHT] = false;
				        break;
				    case ALLEGRO_KEY_DOWN:
				        key[DOWN] = false;
				        break;
				    case ALLEGRO_KEY_LEFT:
				        key[LEFT] = false;
				        break;
				}
			}
			
			if(events.type == ALLEGRO_EVENT_TIMER){
				if(key[RIGHT]){
					if(right(&vaisseau, buffer, niveau, nbBleu) == 1){
						fin =!fin;
						lvl++;
					}
					vaisseau.directory = RIGHT;
				}
				else if(key[LEFT]){
					if(left(&vaisseau, buffer, niveau, nbBleu) == 1){
						fin =!fin;
						lvl++;
					}
					vaisseau.directory = LEFT;
				}
				else if(key[UP]){
					if(up(&vaisseau, buffer, niveau, nbBleu) == 1){
						fin = !fin;
						lvl++;
					}
					vaisseau.directory = UP;
				}
				else if(key[DOWN]){
					if(down(&vaisseau, buffer, niveau, nbBleu) == 1){
						fin = !fin;
						lvl++;
					}
					vaisseau.directory = DOWN;
				}
			
				/// gestion de l'énnemis

				if(p_pile != NULL)
				{
					if(p_pile->directory == UP)
					{
						ennemis.y -= 7;
						if((ennemis.y-1)%98 == 0){
							p_pile = createPath(niveau, &vaisseau, &ennemis);
						}
						ennemis.directory = UP;
					}
					else if(p_pile->directory == DOWN)
					{
						ennemis.y += 7;
						if((ennemis.y-1)%98 == 0){
							p_pile = createPath(niveau, &vaisseau, &ennemis);
						}
						ennemis.directory = DOWN;
					}
					else if(p_pile->directory == RIGHT)
					{
						ennemis.x += 7;
						if((ennemis.x-225)%98 == 0){
							p_pile = createPath(niveau, &vaisseau, &ennemis);
						}
						ennemis.directory = RIGHT;
					}
					else if(p_pile->directory == LEFT)
					{
						ennemis.x -= 7;
						if((ennemis.x-225)%98 == 0){
							p_pile = createPath(niveau, &vaisseau, &ennemis);
						}
						ennemis.directory = LEFT;
					}
				}

				if(((vaisseau.x-225)/98 == (ennemis.x-225)/98) && ((vaisseau.y-1)/98 == (ennemis.y-1)/98)){
					fin = !fin;
					quit = !quit;
				}
        		
        		/// fin gestion
			
			}
    	}while(!fin);
	}

    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(mur);
    al_destroy_bitmap(vide);
    al_destroy_bitmap(bleu);
    al_destroy_bitmap(rouge);
    al_destroy_bitmap(buffer);
    al_destroy_bitmap(image);
    al_destroy_bitmap(GUI);
    al_destroy_bitmap(on);

    return 0;
}
