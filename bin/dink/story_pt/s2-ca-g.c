void main( void )
{
int &jerry;
int &mcounter;
&jerry = 1;
sp_base_attack(&current_sprite, 720);
 sp_distance(&current_sprite, 60);
 sp_strength(&current_sprite, 50);
sp_hitpoints(&current_sprite, 100);
}

void attack( void )
{
playsound(36, 22050,0,&current_sprite, 0);
&mcounter = random(4000,0);
sp_attack_wait(&current_sprite, &mcounter);

}


void hit( void )
{
if (&story > 15)
  {
 say("`2Caramba, você ganhou o jogo e agora quer sair matando os guardas? Pode ir nessa!", &current_sprite);
sp_timing(&current_sprite, 0);
sp_speed(&current_sprite, 3);
return;
  }

 say("`2O cara me acertou! Agora eu vou matar ele.", &current_sprite);
sp_timing(&current_sprite, 0);
sp_speed(&current_sprite, 3);
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
         choice_start()
         "Perguntar sobre a história do castelo"
         "Perguntar sobre a história do Rei"
         "Pedir audiência com o Rei Daniel"
         "Sair"
         choice_end()

if (&result == 1)
  {
   Say_stop("Me conta sobre esse castelão, seu cavaleiro gente boa.", 1); 
wait(500);  
   Say_stop("`2O Castelo Bomcoração tá de pé há séculos.", &current_sprite);
wait(500);  
   Say_stop("`2É um testamento magnífico do que uma monarquia pode fazer.", &current_sprite);
wait(500);  
   Say_stop("Esse castelo não me parece tão grande assim.", 1); 
wait(500);  
   Say_stop("`2Por dentro é maior.", &current_sprite);
wait(500);  
   Say_stop("Ah.", 1); 
  }

if (&result == 2)
  {
   Say_stop("Me fala do nosso querido Rei.", 1); 
wait(500);  
   Say_stop("`2O Rei Daniel governa com mão de ferro há quase uma década.", &current_sprite);
wait(500);  
   Say_stop("`2Foi a sacada genial dele que estancou a grande invasão dos goblins em '23.", &current_sprite);
wait(500);  
   Say_stop("Ele matou todos?", 1); 
wait(500);  
   Say_stop("`2Não. Depois da guerra, ele criou um lugar especial pra eles viverem em paz.", &current_sprite);
wait(500);  
   Say_stop("Nossa, que cara legal.", 1); 

  }


if (&result == 3)
  {
   Say_stop("Preciso ver o Rei agora.", 1); 
wait(500);  

if (&story < 9)
{
   Say_stop("`2E você é?", &current_sprite);
wait(500);  
   Say_stop("Dink Smallwood.", 1); 
wait(500);  

}
  if (&story < 8)
   {
   Say_stop("`2Nunca ouvi falar de você. Dá o fora, volta pra sua vila e vai bancar o herói lá.", &current_sprite);
   }

  if (&story == 8)
   {
   Say_stop("`2Ah, o que salvou a menininha. Belo trabalho.", &current_sprite);
wait(500);  
   Say_stop("Então vai me deixar entrar?", 1); 
wait(500);  
   Say_stop("`2Desculpa, o Rei tá ocupado hoje.", &current_sprite);
   }

  if (&story == 9)
   {
   Say_stop("`2Ah, o que salvou a menininha. Belo trabalho.", &current_sprite);
wait(500);  
   Say_stop("Tenho informações sobre uma conspiração no Castelo!", 1); 
wait(500);  
   Say_stop("`2Desculpa, o Rei tá ocupado hoje.", &current_sprite);
   }


  if (&story == 10)
   {
   Say_stop("`2Olá, Smallwood. Parabéns por ter frustrado aquele ataque em KernSin.", &current_sprite);
   wait(500);  
   Say_stop("Qualquer um faria o mesmo.", 1); 
   wait(500);  
   Say_stop("`2Mas infelizmente o Rei tá viajando pro exterior.", &current_sprite); 
   wait(500);  
   Say_stop("Droga.", 1); 
   }

  if (&story == 11)
   {
   Say_stop("`2Ei, é o Sir Smallwood!", &current_sprite);
   wait(500);  
   Say_stop("Então o Rei tá em casa?", 1); 
   wait(500);  
   Say_stop("`2Não – Ele tá se despedindo do Milder antes da jornada dele pra Terra Sombria.", &current_sprite); 
   wait(500);  
   Say_stop("Milder?", 1); 
   wait(500);  
   Say_stop("`2Sim, o Flatstomp é o homem mais corajoso do reino.", &current_sprite); 
   wait(500);  
   Say_stop("Grrrrrrr.", 1); 
   }



  if (&story > 11)
   {
   Say_stop("`2Olá, Smallwood. Claro que pode ver o Rei!", &current_sprite);
   wait(500);  
   Say_stop("`2GUARDA, ABRE O PORTÃO!", &current_sprite);
   enter();
   }


  }

   unfreeze(1);
   unfreeze(&current_sprite);
 

 }                                   
}

void die( void )
{
  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 6); 

wait(500);
say("Matar guardas é divertido!",1);
}

void enter( void )
{
 int &gate = sp(4);
 sp_seq(&gate, 68);
script_attach(1000);
wait(1000);
fade_down();
&player_map = 102;
sp_x(1, 314);
sp_y(1, 349);
load_screen(102);
draw_screen();
fade_up();
unfreeze(1);
kill_this_task();
}

