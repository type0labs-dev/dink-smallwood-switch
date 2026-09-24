// ========================================================
// en-peasant_woman1.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Aldeã Camponesa (peasant_woman1)
// Descricao: Moradora local com histórias sobre criaturas da floresta.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 16);
    sp_speed(&current_sprite, 2);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 5);
    
    sp_base_walk(&current_sprite, 1240);
    sp_base_attack(&current_sprite, 1250);
    sp_base_death(&current_sprite, 1260);
    
    sp_touch_damage(&current_sprite, 1);
    sp_hitpoints(&current_sprite, 25);
    sp_defense(&current_sprite, 1);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 1 > 0)
    {
        &mhold = random(3, 1);
        if (&mhold == 1)
        {
            playsound(17, 22050, 0, &current_sprite, 0);
        }
    }
}

void hit( void )
{
    playsound(14, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    &mhold = random(4, 1);
    if (&mhold == 1)
    {
        say("Socorro! Alguém ajude!", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("Não faça isso!", &current_sprite);
    }
}

void die( void )
{
    playsound(15, 22050, 0, &current_sprite, 0);
    say("Piedade...", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 5 > 0)
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
