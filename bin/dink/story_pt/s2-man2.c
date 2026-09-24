//script for old guys in the bar

void main( void )
{

preload_seq(411);
preload_seq(413);
int &myrand;
sp_brain(&current_sprite, 0);
sp_base_walk(&current_sprite, 410);
sp_speed(&current_sprite, 0);

//set starting pic

sp_pseq(&current_sprite, 411);
sp_pframe(&current_sprite, 1);

mainloop:
wait(2000);
if (&temp4hold == 1)
  {
&myrand = random(5, 1);
  if (&myrand == 1)
  {
  say_stop_npc("`0Lutar!!!", current_sprite);
  }
   goto mainloop;
  }
&myrand = random(8, 1);

  if (&myrand == 1)
  {
  sp_pseq(&current_sprite, 411);
  }

  if (&myrand == 2)
  {
  sp_pseq(&current_sprite, 413);
  }

&myrand = random(28, 1);

  if (&myrand == 1)
  {
  say_stop_npc("`3Nathan, que tal mais uma história?", &temp3hold);
  say_stop_npc("`0Beleza.", &current_sprite);
  say_stop_npc("`0Uma vez eu tava lutando com um dragão...", &current_sprite);
  say_stop_npc("`0Quando eu ia dar o golpe final...", &current_sprite);
  say_stop_npc("`0Ele implorou pela vida. Já viu dragão chorar?", &current_sprite);
  wait(400);
  say_stop_npc("`3Nunca.", &temp3hold);
  wait(400);
if (&temp4hold == 1)
  {
   goto mainloop;
  }

  say_stop_npc("`4Haha, esses véios são cheios de conversa fiada...", &temphold);
  say_stop_npc("`0Enfim, não foi bonito, então eu matei ele.", &current_sprite);
  say_stop_npc("`3E onde você viu um dragão, hein?", &temp3hold);
  say_stop_npc("`0Uhh... Ilha de Joppa!", &current_sprite);
  say_stop_npc("`3Mentiroso... Ilha de Joppa não existe, é história pra criança.", &temp3hold);

  }

  if (&myrand == 2)
  {
  say_stop_npc("`0Já te contei da vez que eu treinei um slayer?", &current_sprite);
  say_stop_npc("`3Você treinou um slayer?!?", &temp3hold);
  say_stop_npc("`0Isso. Criei ele desde filhote. Ele fazia tudo que eu mandava.", &current_sprite);
  say_stop_npc("`3E onde ele tá agora??!", &temp3hold);
  say_stop_npc("`0Tive que matar. Já comeu carne de slayer?", &current_sprite);
if (&temp4hold == 1)
  {
   goto mainloop;
  }

  say_stop_npc("`4Me poupa...", &temphold);
  say_stop_npc("`0É melhor do que essa gororoba que você serve aqui, seu barman!", &current_sprite);
  say_stop_npc("`4Vou anotar isso...", &temphold);

  }

  if (&myrand == 3)
  {
  say_stop_npc("`0E teve a vez que eu achei um pergaminho mágico", &current_sprite);
  say_stop_npc("`3Ah é?", &temp3hold);
  say_stop_npc("`0Demorou, era um feitiço de fogo estranho.", &current_sprite);
  say_stop_npc("`0Posso ter ajudado naquele incêndio enorme de algumas estações atrás.", &current_sprite);
  say_stop_npc("`0Esquentou bem o ambiente!", &current_sprite);
  say_stop_npc("`3Tanto faz, você bebeu demais.", &temp3hold);
  }
  if (&myrand == 4)
  {
  say_stop_npc("`0Cê quer ir caçar?", &current_sprite);
  say_stop_npc("`3Até que dá, por que você quer caçar?", &temp3hold);
  say_stop_npc("`0Ouvi dizer que tem uma caverna a nordeste com uma presa e tanto lá dentro.", &current_sprite);
  say_stop_npc("`3Sei não...", &temp3hold);
  }


goto mainloop;
}


void hit( void )
{
sp_speed(&current_sprite, 0);
wait(400);
say_stop_npc("`0É melhor você aprender a ter modos rápido, garoto.", &current_sprite);
wait(800);
goto mainloop;
}

void talk( void )
{

 freeze(1);
         choice_start()
(&s2-milder == 0) "Impressione os homens com suas histórias de bravura"
(&s2-milder == 1) "Convença os homens de que você É um guerreiro"
(&s2-milder == 2) (&story < 8) "Discuta com os homens ainda mais"
(&s2-milder == 2) (&story > 7) "Bater papo com os homens"
         "Sair"
         choice_end()

    if (&result == 1)
    {
wait(500);
 say_stop("Saudações, homens. Trago histórias das minhas aventuras do Leste.", 1);
     //scene with Milder
  preload_seq(401);
  preload_seq(403);
  preload_seq(407);
  preload_seq(409);
  sp_pseq(&temp3hold, 349);
  say_stop("`0Ah é? E quem seria você?", &current_sprite);
  wait(500);
  say_stop("Meu nome é Dink Smallwood. Eu sou um guerreiro!", 1);
  wait(500);
  sp_pseq(&current_sprite, 413);
  say_stop("`3Você teve aventuras, hein?", &temp3hold);
  wait(500);
  say_stop("Ah sim. Uma vez, eu estava numa caverna bem assustadora...", 1);
  wait(500);
  say_stop("`0Isso, continue!", &current_sprite);
  wait(500);
  say_stop("Quando vi, estava cara a cara com um monstro gigante...", 1);
  playmidi("bullythe.mid");
  int &milder = create_sprite(261, 440, 0, 0,0);
  sp_base_walk(&milder, 400);
  sp_speed(&milder, 1);
  sp_timing(&milder, 0);
move_stop(&milder, 9, 420, 1)
move_stop(&milder, 7, 386, 1)
sp_dir(1, 6);
say_stop("`6Que besteira é essa que esse criador de porco tá enfiando na cabeça de vocês?", &milder);
wait(300);
  say_stop("`0Ele é CRIADOR DE PORCO?!", &current_sprite);
  wait(300);
  say_stop("Droga, Milder! O que você tá fazendo aqui?", 1);
move_stop(&milder, 4, 300, 1)
  wait(300);

say_stop("`6Só passando... e você, o que faz longe da fazenda?", &milder);
  wait(300);
  say_stop("`3Fazenda?! Que perdedor!", &temp3hold);
  wait(300);
  sp_dir(1, 4);
  say_stop("Eu não cuido mais de porcos, sou um guerreiro poderoso.", 1);
  wait(500);
  say_stop("`0Ah, conversa fiada!", &current_sprite);
  wait(500);
  say("`3Hahahah!", &temp3hold);
  say_stop("`6Hahaha! Boa, camponês!", &milder);
 wait(400);
 say_stop("Isso NÃO tem graça.",1);
 wait(400);
  say_stop("`0Desculpa, Dink... Vou compensar te pagando uma bebida.", &current_sprite);
 wait(400);
 say_stop("Ótimo, de que tipo?",1);
 wait(400);
  say_stop("`0Uma garrafa de PORCO serve? Mwahahaha!", &current_sprite);
 wait(400);
  say("`3Hahahah!", &temp3hold);
  say_stop("`6Hahaha!", &milder);
 wait(200);
 say_stop("Seus caipiras idiotas! Eu odeio vocês dois!", 1);
 wait(200);
 say_stop("`6Foi divertido, menino dos porcos, mas eu tenho aventuras DE VERDADE pra fazer. Falou.", &milder);
 move_stop(&milder, 3, 370, 1)
 move_stop(&milder, 1, 210, 1)
  playmidi("");

 say_stop("`0Ele disse menino dos porcos...", &current_sprite);
 wait(400);
  say("`3Hahahah!", &temp3hold);
  say("`0Hahaha!", &current_sprite);
  wait(400);
  &s2-milder = 1;  
    }

if (&result == 2)
  {
   wait(500);
   say_stop("Olha... Minha época de fazenda acabou, beleza?", 1);
   wait(500);
   say_stop("`0Ok, você quer mesmo uma aventura?", &current_sprite);
   wait(500);
   say_stop("Ah, quero!",1);
   wait(500);
   say_stop("`0Vai arar o campo do Harper, filho do fazendeiro.", &current_sprite);
   wait(500);
  say("`3Hahahah!", &temp3hold);
  say_stop("`0Hahahah!", &current_sprite);
   wait(500);
   say_stop("Que tal eu arar a sua mãe?",1);
  &s2-milder = 2;
  }

 if (&result == 3)
  {
   wait(500);
   say_stop("Olha...",1);
   wait(500);
  say_stop("`0Guarda o discurso, garoto. Volta quando tiver feito algo importante.", &current_sprite);
  }


 if (&result == 4)
  {
   wait(500);
  say_stop("`0Ei, é o Dink! Mandou bem em salvar aquela garota!", &current_sprite);
   wait(500);
  say_stop("`3Eu te disse que ele tinha jeito pra herói!", &temp3hold);
   wait(500);
   say_stop("Na verdade, vocês não riram de mim e tal?",1);
   wait(500);
  say_stop("`0Não. Aquilo foi... hmm, dois outros caras...", &current_sprite);
   wait(500);
  }



   unfreeze(1);
   goto mainloop;
   return;
goto mainloop;

}

