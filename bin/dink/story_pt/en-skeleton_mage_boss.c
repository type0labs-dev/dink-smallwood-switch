// ========================================================
// en-skeleton_mage_boss.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Lorde Lich Necromante (skeleton_mage_boss)
// Descricao: Chefe supremo dos mortos-vivos com báculo de almas.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 2);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 180);
    
    sp_base_walk(&current_sprite, 900);
    sp_base_attack(&current_sprite, 910);
    sp_base_death(&current_sprite, 920);
    
    sp_touch_damage(&current_sprite, 16);
    sp_hitpoints(&current_sprite, 110);
    sp_defense(&current_sprite, 6);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 16 > 0)
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
        say("SUA ALMA PERTENCE AO MEU BÁCULO!", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("Tolos mortais!", &current_sprite);
    }
}

void die( void )
{
    playsound(15, 22050, 0, &current_sprite, 0);
    say("EU VOLTAREI... EM OUTRA ERA!", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 45 > 0)
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
