// ========================================================
// en-antlion_fossilized.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Aranha Fóssil de Pedra (antlion_fossilized)
// Descricao: Aracnídeo pré-histórico petrificado que despertou da rocha.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 2);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 75);
    
    sp_base_walk(&current_sprite, 970);
    sp_base_attack(&current_sprite, 980);
    sp_base_death(&current_sprite, 990);
    
    sp_touch_damage(&current_sprite, 9);
    sp_hitpoints(&current_sprite, 60);
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
        say("*Rocha sólida!*", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("*Poeira ancestral!*", &current_sprite);
    }
}

void die( void )
{
    playsound(19, 22050, 0, &current_sprite, 0);
    say("*Desaba em cascalho...*", &current_sprite);
    
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
