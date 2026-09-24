//script for wench


void main( void )
{

preload_seq(221);
preload_seq(223);
preload_seq(227);
preload_seq(229);


int &myrand;
sp_brain(&current_sprite, 16);
Debug("Hi, current sprite is &current_sprite!");
sp_base_walk(&current_sprite, 220);
sp_speed(&current_sprite, 1);

//set starting pic

sp_pseq(&current_sprite, 223);
sp_pframe(&current_sprite, 1);

mainloop:
wait(2500);
  unfreeze(&current_sprite);
if (&temp4hold == 1)
  {
   //dink is gonna fight
sp_speed(&current_sprite, 2);
sp_timing(&current_sprite, 0);
  }

sp_speed(&current_sprite, 1);
sp_timing(&current_sprite, 33);


&myrand = random(50, 1);

  if (&myrand == 1)
  {
  freeze(&current_sprite);
  say_stop_npc("`#Mais uma rodada aqui?", &current_sprite);
  }

  if (&myrand == 2)
  {
  freeze(&current_sprite);
  say_stop_npc("`#Tô tão cansado... argh.", &current_sprite);
  }

  if (&myrand == 3)
  {
  freeze(&current_sprite);
  say_stop_npc("`#Meus pés tão doendo...", &current_sprite);
  }


  if (&myrand == 4)
  {
  freeze(&current_sprite);
  say_stop_npc("`#Dá pra dar uma pausa, chefe?", &current_sprite);

  if (&temp4hold == 1)
  {
    goto mainloop;
  }
  say_stop_npc("`4O inferno congelou?", &temphold);

  }



goto mainloop;
}


void hit( void )
{
freeze(&current_sprite);
wait(400);
say_stop_npc("`#Olha com os olhos, não com as mãos, querida.", &current_sprite);
wait(800);
goto mainloop;
}

void talk( void )
{

 freeze(1);
 freeze(&current_sprite);
         choice_start()
         "Pedir um encontro"
         "Humilhar ela na frente dos outros pra parecer machão"
         "Sair"
         choice_end()

        if (&result == 1)
        {

       if (&story > 15)
       {
        wait(400);
         say_stop("Quer comer alguma coisa mais tarde?", 1);
        wait(400);
         say_stop("`#Ah, sim! Ei, o herói Smallwood acabou de me chamar pra sair!", &current_sprite);
        wait(400);
         say_stop("Ah, vai ser fácil me acostumar com isso...", 1);
   unfreeze(1);
   goto mainloop;
   return;
         }

        wait(400);
         say_stop("Quer comer alguma coisa mais tarde?", 1);
        wait(400);
         say_stop("`#Desculpa, tô trabalhando mais tarde.", &current_sprite);
        wait(400);
         say_stop("Ah.", 1);

        }

        if (&result == 2)
        {
        wait(400);
         say_stop("Ei, gatinha! Quanto custa a cerveja aqui?", 1);
        wait(400);
         say_stop("`#Duas de ouro, senhor.", &current_sprite);
        wait(400);
         say_stop("E quanto é você?", 1);
        wait(400);
         say_stop("`#Não tô à venda, seu cretino!", &current_sprite);
        wait(400);
         say_stop("Qual é, gata, tô com três de ouro tinindo no bolso!", 1);
        wait(400);
         say_stop("`#CAI FORA!", &current_sprite);
        }


   unfreeze(1);
   goto mainloop;
   return;

}

