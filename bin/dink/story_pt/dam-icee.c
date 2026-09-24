void main( void )
{
int &mholdx;
int &mholdy;

wait(1);

 if (&player_map == 579)
   {
    //are we about to free the guy from prison?
&mholdx = sp_x(&current_sprite, -1);
&mholdy = sp_y(&current_sprite, -1);
    //they are feeding the pigs.. maybe...

int &junk = inside_box(&mholdx,&mholdy, 300, 195, 388, 244);
    if (&junk == 1)
    {
    freeze(1);
    wait(200);
preload_seq(167);
    playsound(18, 8000,0,0,0);
int &mcrap = create_sprite(340, 200, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);

    playsound(18, 8000,0,0,0);
int &mcrap = create_sprite(360, 220, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);

    playsound(18, 8000,0,0,0);
int &mcrap = create_sprite(370, 240, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);

    playsound(18, 8000,0,0,0);
int &mcrap = create_sprite(360, 220, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);

    playsound(18, 8000,0,0,0);
int &mcrap = create_sprite(340, 200, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
int &mycrap = &current_sprite;
script_attach(1000);

sp_brain(&mycrap, 12);
sp_brain_parm(&mycrap, 9);

&mcrap = sp(22);
sp_hard(&mcrap, 1);
draw_hard_sprite(&mcrap);
sp_active(&mcrap, 0);
playsound(43, 22050,0,0,0);


   say_stop("`5Uau!", &temp1hold);
    wait(200);
    move_stop(&temp1hold, 1, 300, 1);
    say_stop("`5Ihuu! Finalmente sou um homem livre!", &temp1hold);
    wait(200);
    say_stop("`5Agora preciso cumprir minha missão.", &temp1hold);
    wait(200);
    say_stop("Missão? De quê, destruir o Clero?", 1);
    wait(200);
    move_stop(&temp1hold, 7, 250, 1);
    say_stop("`5Na real, era pra deter um doido chamado Bispo Nelson.", &temp1hold);
    wait(200);
    move_stop(&temp1hold, 4, 80, 1);
    say_stop("Espera... Não tô entendendo!", 1);
    say_stop("`5É melhor assim. Agora me segue que eu te tiro daqui.", &temp1hold);
    move_stop(&temp1hold, 4, -100, 1);
    sp_active(&temp1hold);
    unfreeze(1);

sp_brain(&current_sprite, 12);
sp_brain_parm(&current_sprite, 9);
 &caveguy = 5;

  kill_this_task();
   return;
    }

   }




wait(5000);


sp_brain(&current_sprite, 12);
sp_brain_parm(&current_sprite, 9);

}
