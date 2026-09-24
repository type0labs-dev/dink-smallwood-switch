void main( void )
{
}

void talk( void )
{
 freeze(1);
 say_stop("`0Pra embarcar no barco com a Morte", &current_sprite);
 say_stop("`0por favor, peça a versão completa.", &current_sprite);
 wait(200);
 say_stop("`0Você não vai se arrepender!", &current_sprite);
 move_stop(1, 2, 147, 1);
 wait(200);
 say_stop("Me compra, vai!", 1);
 if(&story > 4)
 {
 say_stop("Minha mãe morreu e eu preciso de um lar.", 1);
 }
 unfreeze(1);
}
