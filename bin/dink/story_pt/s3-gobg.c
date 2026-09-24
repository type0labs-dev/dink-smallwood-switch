
void main( void )
{
int &mcounter;
sp_brain(&current_sprite, 0);
sp_speed(&current_sprite, 1);
sp_distance(&current_sprite, 50);
sp_range(&current_sprite, 35);
sp_timing(&current_sprite, 0);
sp_frame_delay(&current_sprite, 55);
sp_exp(&current_sprite, 150);
sp_base_walk(&current_sprite, 800);
sp_base_attack(&current_sprite, 790);
sp_defense(&current_sprite, 6);
sp_strength(&current_sprite, 25);
sp_hitpoints(&current_sprite, 80);
preload_seq(792);
preload_seq(794);
preload_seq(796);
preload_seq(798);
preload_seq(805);

preload_seq(801);
preload_seq(803);
preload_seq(807);
preload_seq(809);
}


void hit( void )
{
sp_brain(&current_sprite, 9);
sp_target(&current_sprite, &enemy_sprite);
//lock on to the guy who just hit us
//playsound
playsound(28, 22050,0,&current_sprite, 0);
sp_touch_damage(&current_sprite, 10);

}

void die( void )
{
  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 6); 
}
void attack( void )
{
playsound(27, 22050,0,&current_sprite, 0);
&mcounter = random(4000,0);
sp_attack_wait(&current_sprite, &mcounter);
}

void talk ( void )
{

int &temp;
&temp = sp_brain(&current_sprite, -1);
if (&temp == 9)
  {
  say("`6ei, tô te chamando, ô mané!", &current_sprite);
  return; 
  }

freeze(1);
freeze(&current_sprite);
 choice_start()
(&gobpass == 0) "Pedir pro guarda goblin deixar você entrar"
 "Arranjar uma 'confusão'"
 "Ir embora"
 choice_end()

 if (&result == 1)
 {
  wait(400);
  say_stop("Saudações, meu bom companheiro! Posso entrar no seu belo estabelecimento?", 1);
  wait(400);
  say_stop("`6hmm.", &current_sprite);
  wait(400);
  int &dumb = compare_weapon("item-b1");
debug("Dumb is &dumb");
  if (&dumb == 1)
    {
      if (&mayor != 3)
       {
        //if they have not talked to the mayor, let's not let them in.
  say_stop("`6hmm... cê tá falando sério?? Volta mais tarde! Cedo demais.", &current_sprite);
  wait(400);
  unfreeze(1);
 unfreeze(&current_sprite);
  return;    

       }
     //they are holding the bow
   say_stop("`6acho que cê tem razão. PORTA ABERTA!", &current_sprite);
playsound(43, 22050,0,0,0);

        &gobpass = 1;
        //remove gate
        &dumb = sp(3);
        sp_hard(&dumb, 1);
        draw_hard_sprite(&dumb);
        sp_active(&dumb, 0);
unfreeze(1);
unfreeze(&current_sprite);
  return;    
    }
  say_stop("`6aff, humanos NÃO são bem-vindos! Cai fora!", &current_sprite);
  wait(400);
  say_stop("Ah, qual é, me deixa entrar!", 1);
  wait(400);
  say_stop("`6sem reverência?!!! e não tá falando sério! Cai fora!!", &current_sprite);
 }

 if (&result == 2)
 {
  wait(400);
  say_stop("Diz aí. Então que tal aquela guerra de '23? Vocês tomaram uma coça bem feia.", 1);
  wait(400);
  say_stop("`6cê tá me irritando!", &current_sprite);
  wait(400);
  say_stop("Quer dizer, o Rei Daniel basicamente esmagou vocês todos como insetinhos.", 1);
  wait(400);
  say_stop("`6Ritchard!??? agora cê vai morrer!", &current_sprite);
  sp_brain(&current_sprite, 9);
  sp_target(&current_sprite, 1);
 }

unfreeze(1);
unfreeze(&current_sprite);

}
