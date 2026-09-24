// ========================================================
// en-knight.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: Cavaleiro Nobre (knight)
// Descricao: Guerreiro de armadura completa, paladino defensor das terras de Dink.
// ========================================================

void main( void )
{
    int &mhold;
    // Configuracao basica de IA de Monstro (Brain 9: perseguicao e combate)
    sp_brain(&current_sprite, 9);
    sp_speed(&current_sprite, 2);
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, 80);
    
    // Vinculacao de sequencias de animacao
    sp_base_walk(&current_sprite, 970);
    sp_base_attack(&current_sprite, 980);
    sp_base_death(&current_sprite, 990);
    
    // Atributos de combate
    sp_touch_damage(&current_sprite, 10);
    sp_hitpoints(&current_sprite, 80);
    sp_defense(&current_sprite, 10);
    
    // Caixas de profundidade e solidez
    sp_target(&current_sprite, 1);
}

void touch( void )
{
    // Causar dano por contato
    if (&life > 0)
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
    // Reacao ao ser atingido por Dink
    playsound(14, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    // Falas de combate em Portugues Brasileiro
    &mhold = random(4, 1);
    if (&mhold == 1)
    {
        say("Pela honra do reino!", &current_sprite);
    }
    if (&mhold == 2)
    {
        say("Seu aço é fraco diante de minha fé!", &current_sprite);
    }
}

void die( void )
{
    // Efeito sonoro de morte
    playsound(15, 22050, 0, &current_sprite, 0);
    
    // Fala de morte dramatica
    say("Minha guarda... caiu...", &current_sprite);
    
    // Dropar recompensa (moedas de ouro ou coracao)
    &mhold = random(3, 1);
    if (&mhold == 1)
    {
        int &gold = create_sprite(&current_sprite_x, &current_sprite_y, 0, 160, 1);
        sp_brain(&gold, 6);
    }
    
    // Limpeza da tela e memoria de kill
    int &hold = sp_editor_num(&current_sprite);
    if (&hold != 0)
    {
        editor_type(&hold, 1);
    }
}
