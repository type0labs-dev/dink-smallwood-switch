void main( void )
{
}


void talk( void )
{
   if (&wizard_see > 3)
   {
    return;
   }
 freeze(1);
 say_stop("E aí, é um pergaminho da Martridge!", 1);
 say_stop("Deixa eu ver...", 1);
 wait(200);
 say_stop("`0Querido Dink,", &current_sprite);
 say_stop("`0Se você está vendo isto, significa que você", &current_sprite);
 say_stop("`0realmente tem talento pra magia.", &current_sprite);
 wait(200);
 say_stop("`0Infelizmente fui chamada pra longe e não posso", &current_sprite);
 say_stop("`0te ensinar mais nada. Mas existem muitos", &current_sprite);
 say_stop("`0mestres por aí, você vai encontrar um e continuar", &current_sprite);
 say_stop("`0seu treinamento.", &current_sprite);
 wait(200);
 say_stop("`0Tem 200 moedas de ouro junto, gaste com sabedoria.", &current_sprite);
 &gold += 200;
 wait(200);
 say_stop("`0Por enquanto, fica com isto, seu primeiro feitiço.", &current_sprite);
 say_stop("`0Aproveita, Dink, você mereceu.", &current_sprite);
 wait(200);
 say_stop("Beleza, meu primeiro feitiço! Quem sabe eu não toco fogo em umas árvores...", 1);
 wait(200);
   script_attach(1000);
 
 Playsound(22,22050,0,0,0);
 &wizard_see = 4;
 sp_brain_parm(&current_sprite, 5);
 sp_brain(&current_sprite, 12); 
 sp_touch_damage(&current_sprite, 0);
 sp_timing(&current_sprite, 0);
 &magic += 1;
 add_magic("item-fb",437, 1);
 say_stop("Agora tenho a magia da bola de fogo!", 1);

 unfreeze(1);
kill_this_task();
}
