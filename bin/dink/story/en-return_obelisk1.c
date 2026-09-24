// ========================================================
// en-return_obelisk1.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Monólito Mágico de Retorno (return_obelisk1)
// Descricao: Pilar rúnico místico que serve de ponto de teleporte e save.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 16);
    sp_speed(&current_sprite, 0);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 0);
    
    sp_base_walk(&current_sprite, 1290);
    sp_base_attack(&current_sprite, 1300);
    sp_base_death(&current_sprite, 1310);
    
    sp_touch_damage(&current_sprite, 0);
    sp_hitpoints(&current_sprite, 999);
    sp_defense(&current_sprite, 99);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 0 > 0)
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
        say("*O monólito rúnico brilha intensamente ao toque.*", &current_sprite);
    }
    if (&mhold == 2 && 1 > 1)
    {
        say("*O monólito rúnico brilha intensamente ao toque.*", &current_sprite);
    }
}

void die( void )
{
    playsound(22, 22050, 0, &current_sprite, 0);
    say("*Luz rúnica dissipa.*", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 0 > 0)
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
