void main( void )
{
sp_speed(&current_sprite, 2);
sp_timing(&current_sprite, 0);
sp_base_walk(&current_sprite, 400);
preload_seq(401);
preload_seq(403);
preload_seq(407);
preload_seq(409);

if (&pig_story == 0)
{

        freeze(1);
wait(200);
say_stop("Vem cá, porquinho, porquinho.", 1);
wait(200);

    
        move_stop(&current_sprite, 1, 542, 1)
        playmidi("bullythe.mid");

        say_stop("`6Opa, olha só o que temos aqui.", &current_sprite);
        wait(200);
        say_stop("O que você quer, Milder?", 1);
        wait(200);
        say_stop("`6Nada.", &current_sprite);       
        wait(200);
        say_stop("`6Só vim ver você ralar... Cuidar de porco é divertido, ô mané?", &current_sprite);       
        wait(200);
        say_stop("Eu NÃO sou criador de porco, seu babaca!", 1);       
        wait(200);
        say_stop("`6Você tá alimentando o quê? Tua namorada?", &current_sprite);       
        wait(200);
        say_stop("Er... A minha..", 1);       
        wait(200);
        say_stop("Não, a tua...", 1);       
        wait(200);
        say_stop("`6Mwahahaha! Falou e disse, pirralho!", &current_sprite);       
        move_stop(&current_sprite, 3, 700, 1)
        say_stop("Nossa, como eu *DETESTO* esse desgraçado!", 1);       
        unfreeze(1);
       stopmidi();
        &pig_story = 1;
}

}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
