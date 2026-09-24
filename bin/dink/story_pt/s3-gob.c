//Goblin George

void main( void )
{
int &mcounter;
sp_brain(&current_sprite, 16);
sp_speed(&current_sprite, 1);
sp_distance(&current_sprite, 50);
sp_timing(&current_sprite, 66);
sp_exp(&current_sprite, 50);
sp_base_walk(&current_sprite, 760);
sp_defense(&current_sprite, 2);
sp_hitpoints(&current_sprite, 40);
preload_seq(765);
preload_seq(761);
preload_seq(763);
preload_seq(767);
preload_seq(769);
wait(3500);

say("`6E aí, parça! Bora conversar?", &current_sprite);
}

void hit( void )
{
playsound(28, 22050,0,&current_sprite, 0);
&mcounter = random(3, 1);
sp_frame_delay(&current_sprite, 30);
sp_timing(&current_sprite, 0);
sp_speed(&current_sprite, 2);
sp_brain(&current_sprite, 9);
if (&mcounter == 1)
  say("`6Eita! Calma aí, meu! A gente pode ser amigo!", &current_sprite);

if (&mcounter == 2)
  say("`6Não me bate, cara!", &current_sprite);

if (&mcounter == 3)
  say("`6Eu não quero violência!", &current_sprite);

}

void die( void )
{
    external("achievement", "award", 9);

  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 1); 
  say("Que isso sirva de recado pro povo dele. Hahaha!", 1);
}
void talk( void )
{
        freeze(&current_sprite);
        freeze(1);

 choice_start()
 "Perguntar o nome do goblin"
 "Perguntar o que ele tá fazendo tão longe"
 "Perguntar sobre o Santuário dos Goblins"
 "Ir embora"
 choice_end()

  if (&result == 1)
   {
    say_stop("Qual é o seu nome, goblin?", 1);
    wait(500);
    say_stop("`6meu nome é george. a gente pode ser amigos?", &current_sprite);
    wait(500);
    say_stop("Não tô entendendo nada do que você fala.", 1);
   }


  if (&result == 2)
   {
    say_stop("Diga, por que você não tá no santuário dos goblins?", 1);
    wait(500);
    say_stop("`6eu quero morar com os humanos.", &current_sprite);
    wait(500);
    say_stop("Muita gente tem medo de goblin, sabia?", 1);
    wait(500);
    say_stop("`6george é humano também.", &current_sprite); 
    wait(500);
    say_stop("Ah, entendi. Boa sorte pra você.", 1);
   }

  if (&result == 3)
   {
    say_stop("Então, que história é essa do tal Santuário dos Goblins?", 1);
    wait(500);
    say_stop("`6eles são RUINS. eles só entendem UMA coisa.", &current_sprite);
    wait(500);
    say_stop("E que coisa é essa? Talvez eu precise saber.", 1);
    wait(500);
    say_stop("`6violência. pra invocar o mog você tem que MATAR muitos guardas.", &current_sprite); 
    wait(500);
    say_stop("Ah. Não sei direito quem é Mog, mas... valeu aí.", 1);
   }


unfreeze(&current_sprite);
unfreeze(1);

 

}

