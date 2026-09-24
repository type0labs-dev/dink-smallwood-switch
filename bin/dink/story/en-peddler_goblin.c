// ========================================================
// en-peddler_goblin.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Goblin Mascate Pacífico (peddler_goblin)
// Descricao: Raro goblin amigável que troca bugigangas brilhantes.
// ========================================================

void main( void )
{
    int &mhold;
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 2);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 15);
    
    sp_base_walk(&current_sprite, 1280);
    sp_base_attack(&current_sprite, 1290);
    sp_base_death(&current_sprite, 1300);
    
    sp_touch_damage(&current_sprite, 3);
    sp_hitpoints(&current_sprite, 30);
    sp_defense(&current_sprite, 3);
    
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    if (&life > 0 && 3 > 0)
    {
        &mhold = random(3, 1);
        if (&mhold == 1)
        {
            playsound(13, 22050, 0, &current_sprite, 0);
        }
    }
}

void hit( void )
{
    playsound(11, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    &mhold = random(4, 1);
    if (&mhold == 1)
    {
        say("Goblin bom não ataca humano! Goblin só quer moedinhas!", &current_sprite);
    }
    if (&mhold == 2 && 2 > 1)
    {
        say("Não me machuca!", &current_sprite);
    }
}

void die( void )
{
    playsound(12, 22050, 0, &current_sprite, 0);
    say("Brilhantes... adeus...", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && 40 > 0)
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
