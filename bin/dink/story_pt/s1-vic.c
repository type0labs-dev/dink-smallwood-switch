void main( void )
{
}

void talk( void )
{
    external("achievement", "award", 4);

 if (&safe == 0)
 {
 say("`3Me ajuda aí, pelo amor de Deus!", &current_sprite);
 return;
 }
 else
 {
 playmidi("love.mid");
 freeze(1);
 freeze(&current_sprite);
 say_stop("Tá de boa aí, parceiro?", 1);
 wait(200);
 say_stop("`3Graças a você, tô. Aqueles caras iam me matar!", &current_sprite);
 wait(200);
 say_stop("É, nunca vi nada assim acontecer", 1);
 say_stop("por aqui antes.", 1);
 wait(200);
 say_stop("`3Bom, como eu disse, viajo leve e não tenho", &current_sprite);
 say_stop("`3muita coisa comigo.", &current_sprite);
 wait(200);
 say_stop("`3Toma, essa moeda de ouro, é tudo que posso dar.", &current_sprite);
 &gold += 1;
 &exp += 15;
 sp_speed(&current_sprite, 3);
 sp_timing(&current_sprite, 0);
 move_stop(&current_sprite, 6, 680, 1);
 unfreeze(&current_sprite);
 unfreeze(1);
 sp_active(&current_sprite, 0);
 }
}
