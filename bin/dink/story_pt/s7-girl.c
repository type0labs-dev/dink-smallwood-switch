void main( void )
{
 preload_seq(331);
 preload_seq(333);
 preload_seq(335);
 preload_seq(337);
 preload_seq(339);
 sp_base_walk(&current_sprite,330);
 sp_brain(&current_sprite, 16);
 sp_speed(&current_sprite,1);
 sp_timing(&current_sprite,33);
 sp_nohit(&current_sprite, 1);
 int &wait;
   sp_nodraw(&current_sprite, 1);
wait(4000);

loop:
&wait = random(3000,2000);
wait(&wait);

&wait = random(8, 1);

if (&wait == 1)
  {
    say_stop("`#Tô com fome, mãezinha.",&current_sprite);

  }

if (&wait == 2)
  {

    say_stop("`#Me sinto tão velho... mas por que não envelheci?",&current_sprite);

  }

if (&wait == 3)
  {
    sp_nodraw(&current_sprite, 1);
    say_stop("`#A última coisa que lembro é daquele bando de cavaleiros... e sangue.",&current_sprite);

  }

if (&wait == 4)
  {
    sp_nodraw(&current_sprite, 0);
    say_stop("`#EU ODEIO ESTAR AQUI!",&current_sprite);
    playsound(12,22050,0,&current_sprite,0);
  }

if (&wait == 5)
  {
    say_stop("`#Mãe, o homem tá perdido? Igual a gente?",&current_sprite);
  }

if (&wait == 6)
  {
    say_stop("`#Quer ver eu tirar minha cabeça?",&current_sprite);
  }

if (&wait == 7)
  {
  sp_nodraw(&current_sprite, 0);
  }

if (&wait == 8)
  {
   sp_nodraw(&current_sprite, 1);
  }


goto loop;

}

void hit( void )
{
 say_stop("`#<risadinhas> Que cócegas!",&current_sprite);
 goto loop;

}

