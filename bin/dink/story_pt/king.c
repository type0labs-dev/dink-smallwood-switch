void talk( void )
{
freeze(1);

 if (&story == 15)
 {
 playmidi("1011");
 say_stop("`%SMALLWOOD VOLTOU!", &current_sprite);
 wait(300);
 say_stop("Tenho más notícias, meu Rei.",1);
 wait(300);
 say_stop("Sir Flatstomp morreu. Morreu nos meus braços, corajosamente.", 1);
 wait(300);
 say_stop("`%Vou informar a Lyna. Eu temia que fosse assim.", &current_sprite);
 wait(300);
 say_stop("E também - o maligno Seth ancestral foi derrotado.", 1);
 wait(300);
 say_stop("`%Viva! O mundo está salvo!", &current_sprite);

  say_stop_xy("PARABÉNS!", 20, 380);
 wait(300);
  say_stop_xy("VOCÊ TERMINOU O JOGO.", 20, 380);
 wait(300);
  say_stop_xy("Você pegou um garoto e o transformou em herói.", 20, 380);
 wait(300);
  say_stop_xy("Este é o fim?", 20, 380);
 wait(300);
  say_stop_xy("Nem de longe.", 20, 380);
 wait(300);
  say_stop_xy("Ainda há centenas de aventuras esperando por você.", 20, 380);
 wait(300);
  say_stop_xy("Pegue elas (e outros jogos incríveis!) em www.rtsoft.com", 20, 380);
 wait(300);
  say_stop_xy("Ou crie as suas, baixe o kit de desenvolvimento grátis.", 20, 380);
 wait(300);
  say_stop_xy("Agradecimentos especiais para:", 20, 380);
 wait(300);
  say_stop_xy("Justin - desculpa por te fazer desenhar sangue ;)", 20, 380);
 wait(300);
  say_stop_xy("Pap - Ótimo design de fases e história (quando você estava aqui...)", 20, 380);
 wait(300);
  say_stop_xy("Shawn - corndogs NÃO são a comida dos Deuses", 20, 380);
 wait(300);
  say_stop_xy("(para outras frases sem noção, confira o arquivo QUOTES.TXT)", 20, 380);
 wait(300);
  say_stop_xy("Obrigado por jogar - Seth", 20, 380);

 wait(300);
 say_stop("`%E agora, comida para o meu herói faminto!", &current_sprite);

playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(273, 264, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
 &temp1hold = create_sprite(273, 264, 0,0,0);
 sp_script(&temp1hold, "rpotion");
wait(300);

playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(336, 264, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
 &temp1hold = create_sprite(336, 264, 0,0,0);
 sp_script(&temp1hold, "rpotion");
wait(300);

playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(401, 264, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
 &temp1hold = create_sprite(401, 264, 0,0,0);
 sp_script(&temp1hold, "rpotion");
wait(300);


playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(273, 302, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
 &temp1hold = create_sprite(273, 302, 0,0,0);
 sp_script(&temp1hold, "ppotion");
wait(300);

playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(336, 302, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
 &temp1hold = create_sprite(336,302, 0,0,0);
 sp_script(&temp1hold, "ppotion");
wait(300);

playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(401, 302, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
 &temp1hold = create_sprite(401,302, 0,0,0);
 sp_script(&temp1hold, "ppotion");
wait(300);



 &story = 16;
 unfreeze(1);
 return;
 }


 if (&story == 16)
 {
 say("`%Ah, meu assunto favorito!", &current_sprite);
 unfreeze(1);
 return;
 }



 if (&story == 14)
 {
  say_stop("`%Você precisa se apressar, Dink.", &current_sprite);
 unfreeze(1);
 return;
 }

 if (&story == 12)
 {
  say_stop("`%Olá, Dink.", &current_sprite);
  wait(300);
  say_stop("`%Já ouvi muito sobre você - é bom finalmente te conhecer.", &current_sprite);
  wait(300);
  say_stop("Saudações, meu senhor.", 1);
  wait(300);
  say_stop("`%Agora, no que posso lhe ajudar?", &current_sprite);
  wait(300);
  &story = 13;
  }

  choice_start();
(&story == 13)  "Reclamar dos seus impostos"
(&story == 13)  "Oferecer ajuda ao Milder"
  "Sair"
  choice_end();

if (&result == 1)
   {
    //whine about taxes
  wait(300);
  say_stop("Bem... acho que você deveria baixar o imposto dos porcos, senhor.", 1);
  wait(300);
  say_stop("`%Ah, é mesmo?", &current_sprite);
  wait(300);
  say_stop("Sim - minha família é passada pra trás pela coroa todo ano.", 1);
  wait(300);
  say_stop("`%Vou levar isso em consideração, Dink, vou mesmo.", &current_sprite);
   }

if (&result == 2)
   {
    //help Milder
  wait(300);
  say_stop("Ouvi falar do Milder.", 1);
  wait(300);
  say_stop("`%Sim... ele era um cavaleiro muito corajoso - ele entrou nas terras sombrias sabendo...", &current_sprite);
  wait(300);
  say_stop("`%muito bem que poucos voltam. E agora ele também está perdido.", &current_sprite);
  wait(300);
  say_stop("Gostaria de permissão para ir atrás dele, meu Rei.", 1);
  wait(300);
  say_stop("`%Você, Dink? Isso é suicídio.", &current_sprite);
  wait(300);
  say_stop("Ele cresceu na minha vila - não posso virar as costas pra ele.", 1);
  wait(300);
  say_stop("`%E eu não posso recusar você.", &current_sprite);
  wait(300);
  say_stop("`%Mas... só chegar nas terras sombrias já é um baita desafio...", &current_sprite);
  wait(300);
  say_stop("Por favor - só me diga o caminho.", 1);
  wait(300);
  say_stop("`%Vá para o norte deste castelo até chegar nos penhascos.", &current_sprite);
  wait(300);
  say_stop("`%Terei homens lá para te guiar pela passagem.", &current_sprite);
  wait(300);
  say_stop("`%E Dink...", &current_sprite);
  wait(300);
  say_stop("`%Algo muito estranho está acontecendo com o mundo...", &current_sprite);
  wait(300);
  say_stop("`%As terras sombrias parecem ser a origem. Tenha cuidado.", &current_sprite);
  wait(300);
  say_stop("Obrigado. Voltarei, e não virei sozinho.", 1);
  &story = 14;
   }

   

 
unfreeze(1);

}


 void hit ( void )
 {
  //they try to damage the king

  say_stop("`%Você acabou de me atacar, o Rei?", &current_sprite);
  wait(300);
  say_stop("`%Ah, o famoso senso de humor do Dink Smallwood, do qual tanto ouvi falar!", &current_sprite);
 }
