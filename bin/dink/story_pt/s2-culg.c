void main( void )
{
int &randy;
sp_hitpoints(&current_sprite, 20);
int &crap;
}

void talk( void )
{



if (get_sprite_with_this_brain(9, &current_sprite) == 0)
 {
  Playmidi("love.mid");


  //no more brain 9 monsters here, lets unlock the screen
  freeze(1);
  freeze(&current_sprite);

   say_stop("Mary, você tá bem?", 1);
   wait(500);
   say_stop("`#Graças a você. Quem é você?", &current_sprite);
   wait(500);
   choice_start();
   "Um amigo da terra."
   "Um herói, ou seja, seu mágico."
   "Seu pior pesadelo."
   "O líder de outro culto mais sádico"
   choice_end();
   wait(500);

   say_stop("`#Entendi. Você sempre será um herói pra mim.", &current_sprite);
   wait(500);
   say_stop("Hora de ir pra casa. Me segue.", 1);
   dink_can_walk_off_screen(1);
   move(1, 2, 700, 1);
   move(&current_sprite, 2, 700, 1);
   script_attach(1000);
   fade_down();
&player_map = 66;
load_screen(66);
freeze(1);
draw_screen();
sp_x(1, 320);
sp_y(1, 480);

 //build little girls
 &temp2hold = create_sprite(320,480, 0, 0, 0);
 
 sp_script(&temp2hold, "s2-qgirl");
 freeze(&temp2hold);
 freeze(&temp1hold);
 Debug("Ok, mother is &temp1hold and chick is &temp2hold");
 fade_up();
 wait(1500);

move_stop(1, 8, 353, 1)
move_stop(1, 9, 391, 1)
move_stop(1, 4, 388, 1)
wait(800);
say_stop("`5Ué.. Dink. O que você tá fazendo aqui?", &temp1hold);

wait(500);
say_stop("Trouxe uma companhia.", 1);
wait(500);
  move_stop(&temp2hold, 8, 292, 1)
  say_stop("`#Mãe!", &temp2hold);
  wait(500);
  say_stop("`5Oh Mary! Você voltou!",&temp1hold);
  wait(500);
  say_stop("`#Esse cara me salvou de umas pessoas malvadas!", &temp2hold);
  wait(500);
  say_stop("`5Dink, muito obrigado. Se precisar de qualquer coisa, é só pedir.",&temp1hold);
  wait(500);
say_stop("Só tava fazendo meu trabalho, dona.", 1);
&s2-nad = 3;
&story = 8;
wait(500);
  unfreeze(&temp1hold);
  unfreeze(&temp2hold);

  unfreeze(1);
   dink_can_walk_off_screen(0);
    kill_this_task();
 }



&randy = random(3, 1);

 if (&randy == 1)
 say("`#Me ajuda!", &current_sprite);
 if (&randy == 2)
 say("`#Me salva!", &current_sprite);
 if (&randy == 3)
 say("`#Quero ir pra casa!", &current_sprite);

}

void hit ( void )
{
 playsound(12, 22050, 0, 0, 0);
}


void die ( void )
{
 &life = 0;
 say("Nããããããããão! A mina morreu! EU FALHEI!!!!", 1);
}
