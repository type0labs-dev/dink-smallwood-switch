void main( void )
{
}
                
void talk( void )
{
freeze(1);
freeze(&current_sprite);
    choice_start();
   "Manda o pato ir pra casa"
   "Grita com ele"
    choice_end();
   if (&result == 1)
   {
 wait(500);
 say_stop("Ei, patinho, cê tem que voltar pra casa da Rita.", 1);
 wait(500);
 say_stop("`0QUACK!!", &current_sprite);
 wait(500);
   }
   if (&result == 2)
   {
 wait(500);
 say_stop("Tu é um lixo, patinho, nem eu fujo de casa assim.", 1);
 wait(250);
 say_stop("Deveria ter vergonha na cara.", 1);
 wait(500);
 say_stop("`0Vai me morder", &current_sprite);
 wait(250);
 say_stop("`0Mas tá bom, eu vou pra casa...", &current_sprite);
 wait(500);
 &old_womans_duck = 2;
 sp_speed(&current_sprite, 2);
 sp_timing(&current_sprite, 0);

 move_stop(&current_sprite, 8, -12, 1);
 sp_active(&current_sprite, 0);

   }
unfreeze(1);
unfreeze(&current_sprite);
}

void die( void )
{
    external("achievement", "award", 2);

 &old_womans_duck = 3;
 say_stop("Hehehe!", 1);
}


