//script for auntie

void main( void )
{
preload_seq(251);
preload_seq(253);
preload_seq(257);
preload_seq(259);

 if (&s2-aunt < 4)
 {
 int &temphold = create_sprite(160,150, 0, 0, 0);
 sp_script(&temphold, "s2-jack");
 wait(5);
 }
int &myrand;
sp_base_walk(&current_sprite, 250);
sp_speed(&current_sprite, 1);
//sp_timing(&current_sprite, 66);

//set starting pic

sp_pseq(&current_sprite, 251);
sp_pframe(&current_sprite, 1);

if (&s2-aunt == 2)
  {
   freeze(1);
   sp_hitpoints(&temphold, 50);
   sp_brain(&current_sprite, 0);
   sp_x(&current_sprite, 113);
   sp_y(&current_sprite, 180);
   sp_brain(&temphold, 0);
   sp_x(&temphold, 154);
   sp_y(&temphold, 160);
   sp_pseq(&current_sprite, 259);
   sp_pseq(&temphold, 341);
&save_x = sp_x(&current_sprite, -1);
&save_y = sp_y(&current_sprite, -1);
&save_y -= 40; 
   wait(500);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
  
   say_stop("`6Isso vai te ensinar a responder pra mim!", &temphold);
  sp_dir(&temphold, 1);
   wait(500);
  sp_dir(1, 1);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
  wait(300);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
 say_stop("`#Por favor, Jack! Para...", &current_sprite);
  wait(300);
  say_stop("`6Cala a boca!", &temphold);
  sp_dir(&temphold, 1);

   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
  wait(300);
 say_stop("`#Tô te largando! Acabou entre nós!", &current_sprite);
  wait(300);
  say_stop("`6Acabou, é?", &temphold);

   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(50);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(50);

   playsound(9, 17050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(50);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(50);
   playsound(9, 24050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(50);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(50);

   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(50);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(50);

   playsound(9, 17050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(50);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(50);
   playsound(9, 24050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 188, 1);
 sp_seq(&mcrap, 188);
wait(50);
   playsound(9, 22050,0,0,0);
 int &mcrap = create_sprite(&save_x, &save_y, 5, 189, 1);
 sp_seq(&mcrap, 189);
wait(50);




   wait(2000);

  say_stop("`6Tá bem, meu bem?", &temphold);
  wait(2000);
 &s2-aunt = 3;

  say_stop("`6Você não devia me deixar tão bravo.", &temphold);
  wait(1000);
 sp_brain(&current_sprite, 16);
  unfreeze(1);

 say_stop("`#<soluço>", &current_sprite);
 wait(1000);
 sp_brain(&temphold, 16);
  return;
  }


if (&s2-aunt == 0)
  {
   freeze(1);
  
   sp_x(&current_sprite, 600);
   sp_y(&current_sprite, -50);
   wait(500);
   say_stop("Olá.", 1);
   freeze(&temphold);
   sp_dir(&temphold, 3);
   wait(500);
   say_stop("`6Quem diabo é você?", &temphold);
   wait(500);
   say_stop("Eu... Eu sou o Dink Smallwood. Recebi uma carta e...", 1);
   wait(500);
   say_stop("`6Eu não mandei carta nenhuma pra ninguém, nunca.", &temphold);
   wait(500);
   say_stop("Mas eu...", 1);
   wait(300);
   say_stop("`6Cai fora da minha casa.", &temphold);

   move_stop(&current_sprite, 1, 430, 1);
   sp_seq(&current_sprite, 0);
   wait(500);
   say_stop("`#Dink! Você conseguiu!", &current_sprite);
   wait(500);
   say_stop("Tia Maria!", 1);
   wait(500);
   say_stop("`6Que isso? Como você conhece minha mulher? Vocês tão me traindo?", &temphold);
   wait(500);
   say_stop("`#Jack, este é meu sobrinho de Stonebrook.", &current_sprite);
   wait(500);
   say_stop("`#Ele vai ficar com a gente por um tempo.", &current_sprite);
   wait(500);
   say_stop("`6Hã? Desde quando? Droga!", &temphold);
   wait(500);
   say_stop("`#Dink, preparei um quarto pra você lá em cima.", &current_sprite);
   wait(500);
   say_stop("Valeu, tenho certeza que vai ser ótimo.", 1);
   wait(500);
   say_stop("`#É só pedir se precisar de algo.", &current_sprite);
   &s2-aunt = 1;
   unfreeze(&temphold);
    }


   unfreeze(1);
  }

sp_brain(&current_sprite, 16);


}

void talk( void )
{

 freeze(1);
 freeze(&current_sprite);
         choice_start()
(&s2-aunt == 1) "Perguntar sobre sua mãe"
(&s2-aunt == 1) "Perguntar sobre a cidade"
(&s2-aunt == 3) "Incentivá-la a largar o Jack"
(&s2-aunt == 3) "Incentivá-la a continuar apanhando do Jack"
(&s2-aunt == 4) "Confortá-la"
(&s2-aunt == 4) "Pedir uma cama maior"
(&s2-aunt == 4) (&story == 8) "Contar pra Maria sobre sua última aventura"
(&s2-aunt == 5) "Falar sobre nada"
(&s2-aunt == 4) (&story > 15) "Se gabar pra Maria de ter salvado o mundo"
         "Sair"
         choice_end()

        if (&result == 8)
        {
        wait(400);
        say_stop("Só queria dizer: valeu por me deixar ficar aqui.", 1);
        wait(400);
        say_stop("`#Não é problema nenhum, Dink. Você já procurou algum trabalho?", &current_sprite);
        wait(400);
        say_stop("Ops, preciso ir! Até mais!", 1);

        }
        if (&result == 7)
        {
        wait(400);
        say_stop("Adivinha o que eu fiz hoje!", 1);
        wait(400);
        say_stop("`#Salvou a filha da Nadine?", &current_sprite);
        wait(400);
        say_stop("Uh, sim. Como você soube?", 1);
        wait(400);
        say_stop("`#Saiu no Jornal do Rei, tem uma cópia na casa da curandeira.", &current_sprite);
        wait(400);
        say_stop("Ah. Ok.", 1);
        &s2-aunt = 5;
        }

        if (&result == 1)
        {
        wait(400);
         say_stop("Então, como você conhece minha mãe?", 1);
        wait(400);
        say_stop("`#Bem, ela é minha irmã.", &current_sprite);
        wait(400);
        say_stop("Ah, isso explica algumas coisas.", 1);
        }
        if (&result == 2)
        {
        wait(400);
         say_stop("Então me fala sobre Terris.", 1);
        wait(400);
        say_stop("`#Não é uma cidade ruim de se viver.", &current_sprite);
        wait(400);
        say_stop("Você não parece tão animada.", 1);
        wait(400);
        say_stop("`#Bem... as coisas andam meio difíceis ultimamente, só isso.", &current_sprite);
        }

        if (&result == 3)
        {
        wait(400);
         say_stop("Eu vi o Jack bater em você.", 1);
        wait(400);
        say_stop("`#Você... você viu?", &current_sprite);
        wait(400);
        say_stop("Por que você não larga ele? Agora? Essa noite?", 1);
        wait(400);
        say_stop("`#Eu tenho medo dele. Ele me acharia.", &current_sprite);
        wait(400);
        say_stop("Bem, talvez eu mesmo tenha que resolver isso.", 1);
        wait(400);
        say_stop("`#Cuidado! Ele é muito forte,", &current_sprite);
        wait(400);
        say_stop("Ele não é nada, é só você ver.", 1);
        }

        if (&result == 4)
        {
        wait(400);
         say_stop("Eu vi o Jack bater em você.", 1);
        wait(400);
        say_stop("`#Você... você viu?", &current_sprite);
        wait(400);
        say_stop("Sim, ele é bom nisso. Espero aprender muito com ele.", 1);
        wait(400);
        say_stop("`#O quê?!", &current_sprite);
        wait(400);
        say_stop("Só admiro o jeito que ele bate - precisa de prática, sabia?", 1);
        }

        if (&result == 5)
        {
        wait(400);
         say_stop("Como você tá aguentando?", 1);
        wait(400);
        say_stop("`#Tô bem. E você, o que acha da nossa cidade? E de morar aqui?", &current_sprite);
        wait(400);
        say_stop("Tô gostando. Acho que os locais também gostam de mim.", 1);
        wait(400);
        say_stop("`#Me sinto segura com você lá em cima.", &current_sprite);
        wait(400);
        say_stop("Eu também.", 1);
        }
        if (&result == 6)
        {
        wait(400);
         say_stop("Diga... eu gosto do quarto e tal, mas minha cama é meio pequena.", 1);
        wait(400);
        say_stop("`#Eu trocaria, mas a minha é exatamente do mesmo tamanho.", &current_sprite);
        wait(400);
        say_stop("E se você trocasse por uma cama grande pra gente dividir?", 1);
        wait(400);
        say_stop("`#Eu sou sua tia, Dink!", &current_sprite);
        wait(400);
        say_stop("E daí?", 1);
        wait(400);
        say_stop("`#Tenho um trabalho pra fazer.", &current_sprite);
        }


        if (&result == 9)
        {
        wait(400);
         say_stop("Ei, adivinha? Acabei de voltar de uma aventura enorme.", 1);
        wait(400);
        say_stop("`#Que ótimo.", &current_sprite);
        wait(400);
        say_stop("Eu praticamente salvei o universo.", 1);
        wait(400);
        say_stop("`#Uh hum, legal.", &current_sprite);
        wait(400);
        say_stop("Você não acredita em nada disso.", 1);
        wait(400);
        say_stop("`#Desculpa, Dink, eu sei como os jovens gostam de contar histórias.", &current_sprite);
        wait(400);
        choice_start()
        "Ignorar a indiferença dela de boa"
        "Ficar grosso com ela"
        choice_end();
         if (&result == 1)
         {
        say_stop("Heh - é disso que eu gosto em você, tia!", 1);

         }
         if (&result == 2)
         {
        say_stop("Sua puta idiota.", 1);
        wait(400);
        say_stop("`#Como é que é?", &current_sprite);
        wait(400);
        say_stop("Agora vejo que não devia ter matado o Jack.", 1);
        wait(400);
        say_stop("Devia ter me juntado a ele.", 1);       
         }


        }



   unfreeze(1);
   unfreeze(&current_sprite);
   return;

}

void hit(void)
{
 int &mcrap = random(4, 1);

  if (&mcrap == 1)
    Say("Aguenta a porrada como um homem, mulher!", 1);
  if (&mcrap == 2)
    Say("`#Por favor... por favor, não me bate!", &current_sprite);
  if (&mcrap == 3)
    Say("Espero que você goste de brincadeira pesada!", 1);
  if (&mcrap == 4)
    Say("Odeio parentes!", 1);


}
