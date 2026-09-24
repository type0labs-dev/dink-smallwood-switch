void main( void )
{
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 say_stop("E aí, pato, valeu pelo jogo.", 1);
 wait(250);
 say_stop("`3E aí, sem problemas.", &current_sprite);
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 freeze(&current_sprite);
 say_stop("`3Fala sério, mano, não me faz te colocar na arena!", &current_sprite);
 unfreeze(&current_sprite);
}
