// ========================================================
// en-frozen_zombie.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Zumbi Congelado (frozen_zombie)
// Descricao: Cadáver preservado no gelo que causa lentidão ao atacar.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 1);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 35);
    
    sp_base_walk(&current_sprite, 1150);
    sp_base_attack(&current_sprite, 1160);
    sp_base_death(&current_sprite, 1170);
    
    sp_touch_damage(&current_sprite, 6);
    sp_hitpoints(&current_sprite, 60);
    sp_defense(&current_sprite, 5);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 6 > 0)
    {
        &mhold = random(3, 1);
        if (&mhold == 1)
        {
            playsound(29, 22050, 0, &current_sprite, 0);
        }
    }
}

void hit( void )
{
    playsound(27, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    &mhold = random(4, 1);
    if (&mhold == 1)
    {
        say("Friiiooo...", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("Gelo eterno...", &current_sprite);
    }
}

void die( void )
{
    playsound(28, 22050, 0, &current_sprite, 0);
    say("Descongelando...", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 8 > 0)
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
