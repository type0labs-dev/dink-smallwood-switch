void main( void )
{
int &hi;

 //people watching parade
 sp_hitpoints(&current_sprite, 20);
sp_brain(&current_sprite, 16);
}


void talk(void )

{
&hi = random(4, 1);

if (&hi == 1)
say("`3Não é maravilhoso?", &current_sprite);

if (&hi == 2)
say("`3A parada não durou muito, né...", &current_sprite);
if (&hi == 3)
say("`3Isso foi melhor que o ano passado!", &current_sprite);

if (&hi == 4)
 say("`3Que parada maneira!", &current_sprite);


}


void hit(void )

{

&hi = random(4, 1);

if (&hi == 1)
say("`3Socorro! Esse cara tá ficando doido!", &current_sprite);

if (&hi == 2)
say("`3Guardas!!! Aqui!!!", &current_sprite);
if (&hi == 3)
say("`3Socorro!! Esse tal de Dink não é herói nenhum, ele tava por trás do ataque!", &current_sprite);

if (&hi == 4)
say("`3Por favor, senhor... por favor... não!!! Qual é, me ajuda a lutar contra esse cara!", &current_sprite);
sp_frame_delay(&current_sprite, 50);
sp_brain(&current_sprite, 9);
sp_touch_damage(&current_sprite, 5);
sp_speed(&current_sprite, 2);
sp_target(&current_sprite, 1);
}

void die( void )
{
if (get_sprite_with_this_brain(16, &current_sprite) == 0)
 {

if (get_sprite_with_this_brain(9, &current_sprite) == 0)
  {
  //no more brain 9 monsters here, lets unlock the screen
wait(1000);
 say("Agora, ISSO é que é diversão!", 1);
  }
 }

&save_x = sp_x(&current_sprite, -1);
&save_y = sp_y(&current_sprite, -1);
external("emake","medium");


}

