// ========================================================
// en-wyvern_air_boss.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Rei Dragão Tempestuoso Soberano (wyvern_air_boss)
// Descricao: O mais lendário soberano dos céus, o maior chefe dracônico.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 4);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 450);
    
    sp_base_walk(&current_sprite, 1130);
    sp_base_attack(&current_sprite, 1140);
    sp_base_death(&current_sprite, 1150);
    
    sp_touch_damage(&current_sprite, 22);
    sp_hitpoints(&current_sprite, 250);
    sp_defense(&current_sprite, 14);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 22 > 0)
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
        say("OS CÉUS SE CURVAM AO MEU COMANDO!", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("MORTAIS NÃO TOCAM AS NUVENS!", &current_sprite);
    }
}

void die( void )
{
    playsound(25, 22050, 0, &current_sprite, 0);
    say("A TEMPESTADE... ENFIM... CESSA...", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 120 > 0)
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
