void main( void )
{
}

void talk( void )
{
 freeze(1);
 say_stop("`%Casa à Venda: Fale com o Charlie pra saber mais.", &current_sprite);
 wait(250);
 sp_dir(1, 2);
 say_stop("Será que quem é esse Charlie?", 1);
 unfreeze(1);
}
