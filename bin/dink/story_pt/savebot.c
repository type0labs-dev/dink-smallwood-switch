void main( void )
{
sp_seq(&current_sprite, 449);
sp_sound(&current_sprite, 34);
sp_brain(&current_sprite, 6);
sp_hitpoints(&current_sprite, 0);
}

void hit( void )
{
 say("Morre, troço bizarro que não devia tá aqui!", 1);
}

void talk( void )
{
Playsound(18,22050,0,0,0);

       freeze(1);
        choice_start();
        "Salvar o jogo"
        "Sair dessa máquina estranha"
        choice_end();
         unfreeze(1);

        if (&result == 2)
        {
         unfreeze(1);
         return;
        }
        choice_start();
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo" 
        "&savegameinfo" 
        "&savegameinfo" 
        "&savegameinfo" 
        "&savegameinfo" 
        "&savegameinfo" 
        "&savegameinfo" 
         "Deixa pra lá"
        choice_end();

  unfreeze(1);

  if (&result < 11)
 {
  save_game(&result);
  say_xy("`%Jogo salvo", 1, 30);
  }

}
