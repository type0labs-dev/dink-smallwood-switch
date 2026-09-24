void main( void )
{
 sp_speed(&current_sprite, 1);
 int &mydir;
 if(&rock_placement == 1)
 {
  sp_x(&current_sprite, 350);
  draw_hard_map();
 }
}

void talk( void )
{
 say_stop("E aí, parece que tem uma abertura atrás dessa pedra.", 1);
}

void push( void )
{

 if (&strength < 4)
 {
  say_stop("Tá pesada demais pra mim. Se eu fosse um pouco mais forte...", 1);
  return;
 }

   &mydir = sp_dir(1, -1);

   if (&rock_placement == 0)
   {
   //rock is over hole

   if (&mydir == 6)
     {
      say("Ela... ela tá se mexendo...", 1);
      freeze(1);
      move_stop(&current_sprite, 6, 350, 1);
      unfreeze(1);
      draw_hard_map();
      &rock_placement = 1;
      return;
      }
   }

   if (&rock_placement == 1)
   {
    //rock has already been pushed, can we push it back?

   if (&mydir == 4)
    {
      say("..pesada..pesada..", 1);
      freeze(1);
      move_stop(&current_sprite, 4, 285, 1);
      unfreeze(1);
      draw_hard_map();
      &rock_placement = 0;
      return;
     }
   }

      say("Não sai do lugar desse ângulo.", 1);

}
