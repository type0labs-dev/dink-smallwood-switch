// ========================================================
// en-wyvern_water.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Wyvern Glacial das Profundezas (wyvern_water)
// Descricao: Dragão azul das geleiras eternas com sopro congelante.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 4);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 125);
    
    sp_base_walk(&current_sprite, 1120);
    sp_base_attack(&current_sprite, 1130);
    sp_base_death(&current_sprite, 1140);
    
    sp_touch_damage(&current_sprite, 13);
    sp_hitpoints(&current_sprite, 100);
    sp_defense(&current_sprite, 7);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 13 > 0)
    {
        &mhold = random(3, 1);
        if (&mhold == 1)
        {
            playsound(26, 22050, 0, &current_sprite, 0);
        }
    }
}

void hit( void )
{
    playsound(24, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    &mhold = random(4, 1);
    if (&mhold == 1)
    {
        say("*Vento cortante do ártico!*", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("*Nevasca destruidora!*", &current_sprite);
    }
}

void die( void )
{
    playsound(25, 22050, 0, &current_sprite, 0);
    say("*Asas congeladas caem...*", &current_sprite);
    
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
