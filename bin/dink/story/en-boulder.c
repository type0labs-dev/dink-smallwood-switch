// ========================================================
// en-boulder.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Golem de Pedra Viva (boulder)
// Descricao: Monstro rochoso que rola e esmaga tudo em seu caminho.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 2);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 120);
    
    sp_base_walk(&current_sprite, 1080);
    sp_base_attack(&current_sprite, 1090);
    sp_base_death(&current_sprite, 1100);
    
    sp_touch_damage(&current_sprite, 12);
    sp_hitpoints(&current_sprite, 100);
    sp_defense(&current_sprite, 12);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 12 > 0)
    {
        &mhold = random(3, 1);
        if (&mhold == 1)
        {
            playsound(23, 22050, 0, &current_sprite, 0);
        }
    }
}

void hit( void )
{
    playsound(21, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    &mhold = random(4, 1);
    if (&mhold == 1)
    {
        say("*Estrondo ensurdecedor!*", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("*Pedra contra carne!*", &current_sprite);
    }
}

void die( void )
{
    playsound(22, 22050, 0, &current_sprite, 0);
    say("*Desmorona em seixos e cascalho.*", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 30 > 0)
    {
        int &gold = create_sprite(&current_sprite_x, &current_sprite_y, 0, 160, 1);
        sp_brain(&gold, 6);
    }
    
    int &hold = sp_editor_num(&current_sprite);
    if (&hold != 0)
    {
        editor_type(&hold, 1);
    }
}
