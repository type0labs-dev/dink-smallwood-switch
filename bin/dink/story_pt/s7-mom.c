void main( void )
{
 preload_seq(221);
 preload_seq(223);
 preload_seq(225);
 preload_seq(227);
 preload_seq(229);
 sp_base_walk(&current_sprite,220);
 sp_brain(&current_sprite, 16);
 sp_speed(&current_sprite,1);
 sp_timing(&current_sprite,33);
 sp_nohit(&current_sprite, 1);
 sp_nodraw(&current_sprite, 1);
 int &wait;

loop:

&wait = random(3000,1000);
wait(&wait);

&wait = random(5, 1);

if (&wait == 1)
  {
    say_stop("`#Nós estamos ferrados!",&current_sprite);

  }

if (&wait == 2)
  {

    say_stop("`#Você não pode nos machucar, Dink.",&current_sprite);

  }

if (&wait == 3)
  {
    sp_nodraw(&current_sprite, 1);
    say_stop("`#Você não pode nos ver, Dink.",&current_sprite);

  }

if (&wait == 4)
  {
    sp_nodraw(&current_sprite, 0);
    say_stop("`#CONTEMPLE MINHA CARA DEFORMA!",&current_sprite);
    wait(500);
    say_stop("Espírito, me deixa em paz!",1);
  }

if (&wait == 5)
  {
    say_stop("`#Alguns de nós gostam de comer humanos. Eu vazaria se fosse você.",&current_sprite);
    wait(500);
    say_stop("Eu não tenho medo, fantasma.",1);
  }



goto loop;

}


