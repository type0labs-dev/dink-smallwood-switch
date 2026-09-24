// Script de Menu de Pausa (ESC / Menu) - Dink Smallwood Definitive Edition PT-BR

void main(void)
{
    int &old_result;
    playsound(18, 22050, 0, 0, 0);
    freeze(1);

help:
    choice_start();
    "Carregar jogo salvo"
    "Salvar o jogo atual"
    "Diário de Missões"
    "Lista de Conquistas"
    "Configurar botões do controle"
    "Recomeçar do início"
    "Sair do jogo"
    "Continuar jogando"
    choice_end();

    // 1 - Carregar Jogo
    if (&result == 1)
    {
        choice_start();
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "Deixa pra lá"
        choice_end();

        if (&result == 11) goto help;

        if (game_exist(&result) == 0)
        {
            unfreeze(1);
            wait(500);
            say("Nenhum jogo salvo encontrado nesse espaço.", 1);
            kill_this_task();
            return;
        }

        init("load_sequence_now graphics\\dink\\walk\\ds-w1- 71 43 38 72 -14 -9 14 9");
        init("load_sequence_now graphics\\dink\\walk\\ds-w2- 72 43 37 69 -13 -9 13 9");
        init("load_sequence_now graphics\\dink\\walk\\ds-w3- 73 43 38 72 -14 -9 14 9");
        init("load_sequence_now graphics\\dink\\walk\\ds-w4- 74 43 38 72 -12 -9 12 9");
        init("load_sequence_now graphics\\dink\\walk\\ds-w6- 76 43 38 72 -13 -9 13 9");
        init("load_sequence_now graphics\\dink\\walk\\ds-w7- 77 43 38 72 -12 -10 12 10");
        init("load_sequence_now graphics\\dink\\walk\\ds-w8- 78 43 37 69 -13 -9 13 9");
        init("load_sequence_now graphics\\dink\\walk\\ds-w9- 79 43 38 72 -14 -9 14 9");

        init("load_sequence_now graphics\\dink\\idle\\ds-i2- 12 250 33 70 -12 -9 12 9");
        init("load_sequence_now graphics\\dink\\idle\\ds-i4- 14 250 30 71 -11 -9 11 9");
        init("load_sequence_now graphics\\dink\\idle\\ds-i6- 16 250 36 70 -11 -9 11 9");
        init("load_sequence_now graphics\\dink\\idle\\ds-i8- 18 250 32 68 -12 -9 12 9");

        init("load_sequence_now graphics\\dink\\hit\\ds-h2- 102 100 55 72 -18 -9 18 9");
        init("load_sequence_now graphics\\dink\\hit\\ds-h4- 104 100 48 70 -18 -9 18 9");
        init("load_sequence_now graphics\\dink\\hit\\ds-h6- 106 100 59 72 -18 -9 18 9");
        init("load_sequence_now graphics\\dink\\hit\\ds-h8- 108 100 51 77 -18 -9 18 9");

        init("load_sequence_now graphics\\dink\\die\\ds-d1- 169 85 43 72 -23 -9 21 11");

        load_game(&result);
        unfreeze(1);
        kill_this_task();
        return;
    }

    // 2 - Salvar Jogo
    if (&result == 2)
    {
        choice_start();
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "&savegameinfo"
        "Deixa pra lá"
        choice_end();

        if (&result == 11) goto help;

        save_game(&result);
        playsound(34, 22050, 0, 0, 0);
        say("Jogo salvo com sucesso!", 1);
        unfreeze(1);
        kill_this_task();
        return;
    }

    // 3 - Diário de Missões
    if (&result == 3)
    {
        external("ql-log", "log");
        goto help;
    }

    // 4 - Conquistas
    if (&result == 4)
    {
        external("achievement", "menu");
        goto help;
    }

    // 5 - Configurar Controles
    if (&result == 5)
    {
    buttonstart:
        choice_start();
        "Botão 1 - &buttoninfo"
        "Botão 2 - &buttoninfo"
        "Botão 3 - &buttoninfo"
        "Botão 4 - &buttoninfo"
        "Botão 5 - &buttoninfo"
        "Botão 6 - &buttoninfo"
        "Botão 7 - &buttoninfo"
        "Botão 8 - &buttoninfo"
        "Botão 9 - &buttoninfo"
        "Botão 10 - &buttoninfo"
        "Deixa pra lá"
        choice_end();

        if (&result != 11)
        {
            &old_result = &result;
            choice_start();
            set_y 140;
            title_start();
            O que o botão &old_result deveria fazer?
            title_end();
            "Atacar / Ação primária"
            "Conversar / Olhar"
            "Lançar Magia"
            "Abrir Inventário de Itens"
            "Menu Principal"
            "Ver Mapa"
            "Deixa pra lá"
            choice_end();

            if (&result < 7)
            {
                set_button(&old_result, &result);
            }
            goto buttonstart;
        }
        goto help;
    }

    // 6 - Recomeçar
    if (&result == 6)
    {
        choice_start();
        "Sim, quero recomeçar do zero"
        "Não, me tire daqui!"
        choice_end();

        if (&result == 2) goto help;

        if (&result == 1)
        {
            unfreeze(1);
            restart_game();
            kill_this_task();
            return;
        }
    }

    // 7 - Sair
    if (&result == 7)
    {
        choice_start();
        "Sim, quero mesmo sair"
        "Não, ainda quero jogar!"
        choice_end();

        if (&result == 2) goto help;

        if (&result == 1)
        {
            kill_game();
            return;
        }
    }

    // 8 - Continuar jogando
    unfreeze(1);
    kill_this_task();
}
