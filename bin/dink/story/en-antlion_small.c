// ========================================================
// en-antlion_small.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Aranha Filhote do Enxame (antlion_small)
// Descricao: Pequena e veloz, ataca em bandos vorazes nas profundezas.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 4);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 10);
    
    sp_base_walk(&current_sprite, 950);
    sp_base_attack(&current_sprite, 960);
    sp_base_death(&current_sprite, 970);
    
    sp_touch_damage(&current_sprite, 3);
    sp_hitpoints(&current_sprite, 12);
    sp_defense(&current_sprite, 1);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 3 > 0)
    {
        &mhold = random(3, 1);
        if (&mhold == 1)
        {
            playsound(20, 22050, 0, &current_sprite, 0);
        }
    }
}

void hit( void )
{
    playsound(18, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    &mhold = random(4, 1);
    if (&mhold == 1)
    {
        say("*Cric!*", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("*Chii!*", &current_sprite);
    }
}

void die( void )
{
    playsound(19, 22050, 0, &current_sprite, 0);
    say("*Esmagada...*", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 2 > 0)
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
