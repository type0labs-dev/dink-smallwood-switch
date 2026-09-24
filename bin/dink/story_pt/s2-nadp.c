//script for nadine

void main( void )
{
preload_seq(361);
preload_seq(363);
preload_seq(367);
preload_seq(369);
&temp1hold = &current_sprite;
//lets remember the handle to Nadine, may need to control her with another
//script
int &myrand;
sp_base_walk(&current_sprite, 360);
sp_speed(&current_sprite, 1);
//sp_timing(&current_sprite, 66);

//set starting pic

sp_pseq(&current_sprite, 361);
sp_pframe(&current_sprite, 1);
sp_brain(&current_sprite, 16);

}

void talk( void )
{

 freeze(1);
 freeze(&current_sprite);
         choice_start()
(&s2-nad == 0) "Perguntar pra Nadine por que a casa dela tá um chiqueiro"
(&s2-nad == 1) "Oferecer pra achar a mocinha da Nadine"
(&s2-nad == 1) "Ser grosso com a Nadine"
(&s2-nad == 2) "Deixar claro como a sua busca tá rendendo nada até agora"
(&s2-nad == 3) "Perguntar pra Nadine como ela e a Mary tão"
         "Sair"
         choice_end()
        if (&result == 5)
        {
        wait(400);
         say_stop("E aí, como cêis tão? A menina e você?", 1);
        wait(400);
        say_stop("`5Ótimo!", &current_sprite);
        wait(400);
        say_stop("Tô vendo que cê não teve tempo de limpar a casa...", 1);
        wait(400);
        say_stop("`5A Mary acabou de chegar! A gente limpa isso depois.", &current_sprite);
        }



        if (&result == 4)
        {
        wait(400);
         say_stop("A pequena Mary ainda tá lá fora, em algum lugar.", 1);
        wait(400);
        say_stop("`5Ela deve tá com tanto medo e tão sozinha lá fora!", &current_sprite);
        wait(400);
        say_stop("É... a não ser que ela tenha sido sequestrada por gente muito legal.", 1);
        wait(400);
        say_stop("`5Agora sai, por favor.", &current_sprite);
        }

        if (&result == 1)
        {
        wait(400);
         say_stop("Oi Nadine. Sou novo na cidade. Por que sua casa tá um chiqueiro?", 1);
        wait(400);
        say_stop("`5Desde que minha menininha foi sequestrada, eu meio que larguei as coisas.", &current_sprite);
        wait(400);
        say_stop("Sequestrada?! Por que o povo da cidade não tá formando um grupo de busca?", 1);
        wait(400);
        say_stop("`5Eles não tão nem aí. A gente é pobre.", &current_sprite);
        &s2-nad = 1;
        }

        if (&result == 2)
        {
        wait(400);
         say_stop("Nadine - eu não tô nem aí pra sua situação financeira. Eu vou te ajudar.", 1);
        wait(400);
        say_stop("`5Você... você vai?", &current_sprite);
        wait(400);
        say_stop("Claro. Qual era o nome da coitadinha?", 1);
        wait(400);
        say_stop("`5Mary. O nome dela era Mary.", &current_sprite);
        wait(400);
        say_stop("Cê tem alguma ideia de quem pode ter levado ela?", 1);
        wait(400);
        say_stop("`5Não... não tenho.", &current_sprite);
        wait(400);
        say_stop("Poxa, que droga.", 1);
        &s2-nad = 2;
        }

        if (&result == 3)
        {
        wait(400);
         say_stop("Nadine - se você tivesse uma grana guardada, eu achava a sua menina.", 1);
        wait(400);
        say_stop("`5Você sabe que eu não tenho nada! Olha a minha despensa!", &current_sprite);
        wait(400);
        say_stop("Não, valeu. E seus braços parecem pontudos e idiotas.", 1);
        wait(400);
        say_stop("`5Como você ousa!", &current_sprite);
        }


   unfreeze(1);
   unfreeze(&current_sprite);
   return;

}

void hit(void)
{
 int &mcrap = random(4, 1);
    Say("E aí, tá sentindo o gostinho?", 1);
}
