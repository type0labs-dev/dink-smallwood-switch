//script for slayer-little girl cult

void main( void )
{

if (&s2-nad != 2)
{

wait(1000);

if (&s2-nad < 3)
 say("Que quintalzinho bonito.", 1);

if (&s2-nad > 2)
 say("Ah, as lembranças...", 1);

 return;
}
preload_seq(531);
preload_seq(533);
preload_seq(537);
preload_seq(539);
preload_seq(551);
preload_seq(553);
preload_seq(557);
preload_seq(559);
preload_seq(542);
preload_seq(544);
preload_seq(546);
preload_seq(548);

 //build little girls
 int &crap = create_sprite(265,176, 0, 0, 0);
 &temphold = &crap;
 sp_script(&crap, "s2-cg1");

 //build little girls
 &crap = create_sprite(383,179, 0, 0, 0);
 &temp2hold = &crap;
 sp_script(&crap, "s2-cg2");

 &crap = create_sprite(229,278, 0, 0, 0);
 &temp3hold = &crap;
 sp_script(&crap, "s2-cg3");

 &crap = create_sprite(393,278, 0, 0, 0);
 &temp4hold = &crap;
 sp_script(&crap, "s2-cg4");
 freeze(1);


move(1, 4, 583, 1);


  wait(500);


  say_stop("`#Eu te amo, Cadáver de Dragão Morto.", &temphold);
  wait(500);
  say_stop("`#Eu te adoro, Cadáver de Dragão Morto.", &temp2hold);
   wait(500);
  say_stop("`#Eu mataria por você, Cadáver de Dragão Morto.", &temp3hold);
   wait(500);
  say_stop("`#Eu faria qualquer coisa por você, CDM.", &temp4hold);
   wait(500);
  say_stop("`#Por favor, Cindy, fala o nome completo toda vez.", &temphold);
   wait(500);
  say_stop("`#Tá bom.", &temp4hold);
   wait(500);
  say_stop("`#Eu faria qualquer coisa por você, CADÁVER DE DRAGÃO MORTO.", &temp4hold);

   wait(500);
  say_stop("Que festinha interessante a que temos aqui...", 1);

start4:

 &crap = create_sprite(329,450, 0, 0, 0);
 &temp5hold = &crap;
preload_seq(341);
preload_seq(343);
preload_seq(347);
preload_seq(349);
sp_base_walk(&temp5hold, 340);
sp_speed(&temp5hold, 1);
//sp_timing(&current_sprite, 66);
sp_pseq(&temp5hold, 349);
sp_pframe(&temp5hold, 1);

move_stop(&temp5hold, 8, 320, 1);
wait(500);
say_stop("`4Como vai o culto ao Cadáver de Dragão Morto, meninas?", &temp5hold);
wait(500);
say_stop("`#Maravilhoso - obrigada por nos mostrar a luz, Bispo Nelson!", &temphold);
wait(500);
say_stop("`4Adivinha, tenho uma surpresinha pra vocês hoje.", &temp5hold);
wait(500);
   wait(500);
  say_stop("`#Mais sangue de cabra?", &temp4hold);
wait(500);
say_stop("`4Não, Cindy.", &temp5hold);
wait(500);
say_stop("`4Temos uma nova integrante.  Vem cá, Mary!", &temp5hold);

 &crap = create_sprite(300,450, 0, 0, 0);
 &temp6hold = &crap;
 sp_script(&crap, "s2-cg5");
move_stop(&temp6hold, 8, 360, 1);
wait(500);
say_stop("`#Por favor!  Eu não quero entrar nesse culto!", &temp6hold);
wait(500);
say_stop("`4Você VAI aprender a amar o Cadáver de Dragão Morto, Mary.", &temp5hold);
wait(500);
say_stop("`#Como vocês podem adorar um cadáver podre?!", &temp6hold);
wait(500);
  say_stop("`#Acho que o Cadáver apreciaria outro sacrifício, Bispo Nelson.", &temphold);
  wait(500);
say_stop("`4Excelente observação, Jennifer.", &temp5hold);
wait(500);

start:

choice_start();
        set_y 240
        set_title_color 10
        title_start();
Uma garota está prestes a morrer num ritual de culto.  O que você faz?
        title_end();
"Dizer algo no sentido de que você vai salvá-la"
"Concordar que Mary deve ser sacrificada"
"Usar a cuca e ficar escondido"
choice_end()
wait(500);
if (&result == 3)
   {
     wait(200);
   sp_dir(1, 2);
     wait(200);
    say_stop("Não, acho que prefiro gritar alguma coisa.", 1);
     wait(300);
   sp_dir(1, 4);
  wait(200);
   goto start;
   }

if (&result == 1)
  {
    Say_stop("Com licença?", 1);
    wait(500);
          say_stop("`#Tem um homem escondido nos arbustos!", &temphold);
          wait(500);
    Say_stop("Tira as mãos dela, Nelson!  Ela vem comigo!", 1);
    wait(500);
    say_stop("`4Acho que não, Smallwood.", &temp5hold);
wait(500);
move_stop(1, 4, 470, 1);
    wait(500);
    Say_stop("Meninas!  Esse homem é um louco - virem-se contra ele e destruam-no!", 1);

  }


if (&result == 2)
  {
    Say_stop("Concordo, crucifiquem a novata!", 1);
    wait(500);
          say_stop("`#Tem um homem escondido nos arbustos!", &temphold);
          wait(500);
    Say_stop("Eu simplesmente adoro seus rituais sádicos.  Posso continuar assistindo?", 1);
    wait(500);
    say_stop("`4Vem cá, criança.", &temp5hold);
wait(500);
move_stop(1, 4, 470, 1);
    wait(500);
    Say_stop("Ahh, essa vista é bem melhor.", 1);

  }


    wait(500);
    say_stop("`4O Cadáver de Dragão Morto está pedindo um sacrifício...", &temp5hold);
    wait(500);
    say_stop("`4NELE!", &temp5hold);
preload_seq(167);

  say_stop("`#Meninas, TRANSFORMEM-SE!", &temphold);
  wait(500);
screenlock(1);
unfreeze(1);

sp_brain(&temp5hold, 16);
sp_script(&temp5hold, "s2-cman");

sp_brain(&temp6hold, 16);
sp_script(&temp6hold, "s2-culg");


playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(265, 176, 7, 167, 1);
sp_seq(&mcrap, 167);
sp_script(&temphold, "s2-cbon");
wait(800);



playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(383, 179, 7, 167, 1);
sp_seq(&mcrap, 167);
sp_script(&temp2hold, "s2-cbon");
wait(800);

playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(229, 278, 7, 167, 1);
sp_seq(&mcrap, 167);
sp_script(&temp3hold, "s2-cbon");
wait(800);

playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(393, 278, 7, 167, 1);
sp_seq(&mcrap, 167);
sp_script(&temp4hold, "s2-cbon");
wait(800);

say_stop("`4Viu, minhas garotas são mais do que aparentam.", &temp5hold);
//haha, transformers reference

playmidi("denube.mid");
}


