//script for jack

void main( void )
{
preload_seq(341);
preload_seq(343);
preload_seq(347);
preload_seq(349);
if (&s2-aunt > 2)
{
 sp_hitpoints(&current_sprite, 50);
}
int &myrand;
sp_base_walk(&current_sprite, 340);
sp_speed(&current_sprite, 1);
sp_pseq(&current_sprite, 341);
sp_pframe(&current_sprite, 1);
sp_brain(&current_sprite, 16);
}

void talk( void )
{

 freeze(1);
 freeze(&current_sprite);
         choice_start()
(&s2-aunt == 1)         "Fala oi pro Jack"
(&s2-aunt == 1)         "Agradece o Jack pela hospedagem"
(&s2-aunt == 1)         "Fala uma grosseria pro Jack"
(&s2-aunt == 3)         "Manda o Jack parar de encher o saco da Maria"
(&s2-aunt == 3)         "Convence o Jack a bater na Maria de novo"
         "Ir embora"
         choice_end()

        if (&result == 1)
        {
        wait(400);
         say_stop("Oi Jack! Tá fazendo o quê?", 1);
        wait(400);
         say_stop("`6Cai fora.", &current_sprite);
        }

        if (&result == 2)
        {
        wait(400);
         say_stop("É mó legal da sua parte me deixar ficar aqui e tal.", 1);
        wait(400);
         say_stop("`6<resmunga>  Arranja um lugar novo amanhã.", &current_sprite);
        }
        if (&result == 3)
        {
        wait(400);
         say_stop("Ei, Jack!", 1);
        wait(400);
         say_stop("`6Que foi?", &current_sprite);
        wait(400);
         say_stop("Me lambe!", 1);
        wait(400);
         say_stop("`6Seu pestinha!!  Toma essa!", &current_sprite);
sp_touch_damage(&current_sprite, 10);
sp_speed(&current_sprite, 2);
sp_brain(&current_sprite, 9);
sp_target(&current_sprite, 1):
        }

        if (&result == 4)
        {
        wait(400);
         say_stop("Jack.  Eu sei que sou seu hóspede e tal, mas...", 1);
        wait(400);
         say_stop("`6Que foi?", &current_sprite);
        wait(400);
        say_stop("Se você encostar na Maria de novo, você não vai ver o sol nascer amanhã.", 1);
        wait(400);
         say_stop("`6Que tal eu encostar em você agora?", &current_sprite);
        wait(400);
        say_stop("Ô, não sou chegado nisso. Mas conheço um cara chamado Milder...", 1);
        }

        if (&result == 5)
        {
        wait(400);
         say_stop("Jack.  Adivinha quem tava falando mal de você agora há pouco...", 1);
        wait(400);
         say_stop("`6Minha mulherzinha chata?", &current_sprite);
        wait(400);
        say_stop("Isso. Melhor você dar uma lição nela, cê me entende.", 1);
        wait(400);
         say_stop("`6Ok.", &current_sprite);
        wait(400);

       move_stop(&current_sprite, 8, 140, 1);
       move_stop(&current_sprite, 2, 140, 1);
       move_stop(&current_sprite, 4, 255, 1);
       move_stop(&current_sprite, 6, 256, 1);
       say_stop("`6Ô docinho... pode vir aqui um instante?", &current_sprite);
        wait(400);
 freeze(&temp2hold);

       say_stop("`#Pois não, Jack.",&temp2hold);
       move_stop(&temp2hold, 8, 140, 1);
       move_stop(&temp2hold, 2, 140, 1);
       move_stop(&temp2hold, 6, 310, 1);
       move_stop(&temp2hold, 4, 309, 1);
wait(500);
       say_stop("`#O que foi?",&temp2hold);
wait(500);
       say_stop("`6Só isso", &current_sprite);

wait(500);

   playsound(9, 17050,0,0,0);
&save_x = sp_x(&temp2hold, -1);
&save_y = sp_y(&temp2hold, -1);
&save_y -= 40; 
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(100);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(100);
   playsound(9, 17050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(100);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(100);
 wait(500);
       say_stop("Ha! Boa, Jack!",1);
       
 wait(500);

       say_stop("`6Agora vai limpar a bagunça.", &current_sprite);
 wait(500);

   say_stop("`#<soluça>  Dink... eu... pensei que você fosse diferente.",&temp2hold);
 wait(500);
       say_stop("Acorda pra vida, querida. Como você acha que eu mantinha minha mãe na linha? Ha!",1);

       unfreeze(&temp2hold);

        }


   unfreeze(1);
   unfreeze(&current_sprite);
   return;

}

void hit(void)
{
Say("`6Ah, AGORA VOCÊ SE FERROU!", &current_sprite);
sp_touch_damage(&current_sprite, 10);
sp_speed(&current_sprite, 2);
sp_brain(&current_sprite, 9);
sp_target(&current_sprite, 1):
}

void die(void)
{
    external("achievement", "award", 13);

script_attach(1000);
freeze(1);
freeze(&temp2hold);
wait(500);
say_stop("`#Dink!  O que você fez!", &temp2hold);
wait(500);
say_stop('I guess I just killed your husband.", 1);
wait(500);
say_stop("`#Jack nem sempre foi assim. Ele costumava ser... <desaba em lágrimas>", &temp2hold);
wait(500);
say_stop("Eu sei. Tá tudo bem, agora eu tô aqui.", 1);
&exp += 100;
&s2-aunt = 4;
unfreeze(1);
unfreeze(&temp2hold);
}
