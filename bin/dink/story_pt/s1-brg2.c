void main( void )
{
int &dumb = create_sprite(360, 300, 0, 64, 1);
sp_hard(&dumb, 0);
draw_hard_sprite(&dumb);
sp_disabled(&dumb, 1);

sp_base_walk(&current_sprite, 370);
sp_speed(&current_sprite, 3);
sp_timing(&current_sprite, 0);
}

void hit( void )
{
  say("`3Alguma coisa tocou em mim? Uma mosca, talvez?", &current_sprite);

}

void talk( void )
{
 freeze(1);
 choice_start();
        set_y 240
        set_title_color 3
        title_start();
"Olá, bom senhor, o pedágio da ponte é 100 de ouro."
        title_end();
"Pagar o pedágio"
"Discutir"
"Ir embora"
 choice_end();

  if (&result == 1)
  {

 if (&gold < 100)
 {
 wait(500);
 say_stop("`3Você não tem ouro suficiente, seu idiota!", &current_sprite);   
 unfreeze(1);
 return;
 }
 wait(500);
 say_stop("`3Valeu. Tenha um bom dia.", &current_sprite);   
 &gold -= 100;
 move_stop(&current_sprite, 4, -50, 1);
 &story = 7;
 unfreeze(1);
 sp_hard(&dumb, 1);
  force_vision(0);
// sp_active(&current_sprite, 0);

  kill_this_task();
 return;
  }

 if (&result == 2)
  {
 wait(500);
 say_stop("Isso é ridículo. Como você justifica cobrar tão caro?",1);
 wait(500);
 say_stop("`3Meus filhos precisam comer.", &current_sprite);
 wait(500);
 say_stop("O rei sabe do seu 'negocinho'?", 1);
 wait(500);
 say_stop("`3Claro que não.", &current_sprite);
 wait(500);
 say_stop("Palhaçada.", 1);
  }


 unfreeze(1);
}
