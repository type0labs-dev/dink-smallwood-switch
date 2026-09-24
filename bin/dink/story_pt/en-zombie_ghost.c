// ========================================================
// en-zombie_ghost.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Espectro / Alma Penada (zombie_ghost)
// Descricao: Fantasma etéreo translúcido imune a ataques físicos convencionais.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 3);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 60);
    
    sp_base_walk(&current_sprite, 1170);
    sp_base_attack(&current_sprite, 1180);
    sp_base_death(&current_sprite, 1190);
    
    sp_touch_damage(&current_sprite, 9);
    sp_hitpoints(&current_sprite, 40);
    sp_defense(&current_sprite, 8);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 9 > 0)
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
        say("*Lamento agoniante!*", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("Você não pode ferir o que já morreu!", &current_sprite);
    }
}

void die( void )
{
    playsound(28, 22050, 0, &current_sprite, 0);
    say("Paz... finalmente...", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 15 > 0)
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
