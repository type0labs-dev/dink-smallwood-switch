void main( void )
{
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 say_stop("`3Fala aí.", &current_sprite);
 wait(250);
 say_stop("Oi, quem é você?", 1);
 wait(250)
 say_stop("`3Sou a pata mãe.", &current_sprite);
 wait(250);
 say_stop("Ah, entendi.", 1);
 wait(250);
 say_stop("E como vão seus filhotes?", 1);
 wait(250);
 say_stop("`3Tão bem.", &current_sprite);
 wait(250);
 say_stop("Ei, que ótimo.", 1);
 unfreeze(1);
 unfreeze(&current_sprite);
}
             
void hit( void )
{
 freeze(&current_sprite);
 say_stop("É, isso é divertido!", 1);
 unfreeze(&current_sprite);
}

void die ( void )
{
  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 6); 

}



