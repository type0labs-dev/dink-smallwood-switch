// ========================================================
// en-cursed_grave_ice.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Tumba do Inverno Eterno (cursed_grave_ice)
// Descricao: Cripta congelada que invoca horrores do gelo.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 0);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 65);
    
    sp_base_walk(&current_sprite, 1200);
    sp_base_attack(&current_sprite, 1210);
    sp_base_death(&current_sprite, 1220);
    
    sp_touch_damage(&current_sprite, 5);
    sp_hitpoints(&current_sprite, 90);
    sp_defense(&current_sprite, 7);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 5 > 0)
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
        say("*O gelo racha com força!*", &current_sprite);
    }
    if (&mhold == 2 && 1 > 1)
    {
        say("*O gelo racha com força!*", &current_sprite);
    }
}

void die( void )
{
    playsound(22, 22050, 0, &current_sprite, 0);
    say("*A cripta se desfaz em neve.*", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 25 > 0)
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
