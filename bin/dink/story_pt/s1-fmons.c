void main( void )
{
 sp_hitpoints(&current_sprite, 30);
 sp_base_walk(&current_sprite, 130);
 sp_exp(&current_sprite, 30);
 
 int &how;
 if (&farmer_quest == 1)
 {
  say_stop("`9Você não vai nos vencer, seu Smallwood, somos demais pra você.", &current_sprite);
  say_stop("`9Dê o seu melhor, mas saiba que tá arriscando a vida...", &current_sprite);
 }
 &how = random(3,1);
 if (&how == 1)
 {
  say_stop("`9RRrrr ar a rar a arrgghhh.", &current_sprite);
  sp_speed(&current_sprite, 9);
  sp_timing(&current_sprite, 0);
  wait(4000);
  sp_speed(&current_sprite, 1);
  sp_timing(&current_sprite, 0);
 }
}

void talk( void )
{
}

void hit( void )
{
 sp_target(&current_sprite, &enemy_sprite);
 playsound(30, 17050, 4000, &current_sprite, 0);
  &how = random(2,1);
  if (&how == 1)
  {
   say("`9Você não vai ganhar, Smallwood.", &current_sprite);
  }
  if (&how == 2)
  {
   say("`9Você não vai ganhar, Smallwood.", &current_sprite);
  }
  sp_speed(&current_sprite, 9);
  sp_timing(&current_sprite, 0);
  wait(2000);
  sp_speed(&current_sprite, 1);
  sp_timing(&current_sprite, 33);
}

void die( void )
{
    external("achievement", "award", 5);

 &farmer_quest = 2;
        &exp += 40;
 say("`9Maldito seja... maldito... seja.", &current_sprite);
}
 