void main( void )
{
 int &nut;
 int &talker;
 &talker = 1;
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 &nut = sp_dir(1, -1);
 if (&talker == 0)
 {
  say_stop("Oi, pato gigante.", 1);
  wait(250);
  say_stop("`3Oi, e aí?", &current_sprite);
  wait(250);
  say_stop("`3Bem-vindo à nossa ilha.", &current_sprite);
  wait(250);
  say_stop("Valeu.", 1);
  wait(250);
  say_stop("`3Quer brincar comigo?", &current_sprite);
  wait(250);
  say_stop("Ah, agora não, tô... ocupado.", 1);
  wait(250);
  say_stop("`3Tá bom, quem sabe mais tarde.", 1);
  unfreeze(1);
  unfreeze(&current_sprite);
  &talker = 1;
  return;
 }
 if (&talker == 1)
 {
  say_stop("Oi, pato gigante.", 1);
  wait(250);
  say_stop("`3Oi, e aí?", &current_sprite);
  wait(250);
  say_stop("`3Bem-vindo à nossa ilha.", &current_sprite);
  wait(250);
  say_stop("Valeu.", 1);
  wait(250);
  say_stop("`3Quer brincar comigo?", &current_sprite);
  choice_start()
  "Bora brincar"
  "Agora não"
  choice_end()
  if (&result == 1)
  {
   &duckgame = 1;
   say_stop("Claro, vamos brincar de alguma coisa.", 1);
   wait(250);
   say_stop("`3Beleza, já sei qual jogo, vem comigo.", &current_sprite);
   wait(250);
   script_attach(1000);
   //fadeout & cutscene?
   fade_down();
   //change maps and stuff ...
   &player_map = 731;
   sp_x(1, 112);
   sp_y(1, 300);
   load_screen();
   draw_screen();
   draw_status();
   fade_up();
   kill_this_task();
  }
  if (&result == 2)
  {
   say_stop("Desculpa, agora não.", 1);
  }
 }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 freeze(&current_sprite);
 say_stop("`3Esse jogo não tem graça nenhuma!!!", &current_sprite);
 unfreeze(&current_sprite);
}

void die ( void )
{
  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 6); 

}


