//wizard cut scene

void main( void )
{
freeze(1);
playmidi("wanderer.mid");
int &mcrap = create_sprite(78, 319, 7, 167, 1);
sp_seq(&mcrap, 167);
sp_speed(&current_sprite, 1);
playsound(24, 22052, 0, 0, 0);
move_stop(&current_sprite, 6, 120, 1)
wait(300);
say_stop("Que isso?", 1);
wait(300);
move_stop(1, 8, 377, 1)
move_stop(1, 6, 341, 1)
move_stop(1, 8, 319, 1)
move_stop(1, 2, 319, 1)
move_stop(1, 4, 280, 1)
wait(300);
say_stop("Quem é você?", 1);
wait(200);
sp_pseq(&current_sprite, 561);
wait(200);
sp_pseq(&current_sprite, 563);
wait(200);
say_stop("`0Eu sou um grande mago.", &current_sprite);
wait(200);
say_stop("Nem fudendo! Você é tão fofo e pequenininho!", 1);
wait(200);
move_stop(&current_sprite, 6, 161, 1)
wait(200);
say_stop("`0Não sou nada disso!", &current_sprite);
wait(200);
move_stop(&current_sprite, 6, 192, 1)
wait(200);
say_stop("`0Você não pode medir magia pelo tamanho!", &current_sprite);
wait(200);
say_stop("Eu preciso te acariciar!", 1);
wait(200);
move_stop(1, 4, 145, 1)
wait(200);
say_stop("Hã? Acabei de atravessar você.", 1);
wait(200);
move_stop(1, 6, 304, 1)
wait(50);
move_stop(1, 4, 289, 1)
wait(200);
say_stop("Você não está realmente aqui, está?", 1);
wait(200);
say_stop("`0Claro que estou.. só que não fisicamente.", &current_sprite);
wait(200);
sp_pseq(&current_sprite, 561);
wait(200);
sp_pseq(&current_sprite, 563);
wait(200);
say_stop("`0Se quiser aprender mais.. Venha até minha cabana escondida.", &current_sprite);
wait(200);
say_stop("Como vou achar se é escondida?",1);
wait(200);
say_stop("`0Boa pergunta. Fica atrás de umas árvores a nordeste daqui.", &current_sprite);
wait(200);
say_stop("Ok, talvez eu apareça depois.. você é de um circo?", 1);
wait(200);
say_stop("`0NÃO ME IRRITE, HUMANO!", &current_sprite);
sp_speed(&current_sprite, 10);
sp_timing(&current_sprite, 0);
unfreeze(1);
move_stop(&current_sprite, 4, 71, 1)
move_stop(&current_sprite, 8, 213, 1)
move_stop(&current_sprite, 6, 323, 1)
move_stop(&current_sprite, 2, 295, 1)
move_stop(&current_sprite, 4, 145, 1)
move_stop(&current_sprite, 8, 217, 1)
move_stop(&current_sprite, 6, 316, 1)
move_stop(&current_sprite, 2, 336, 1)
move_stop(&current_sprite, 6, 545, 1)
move_stop(&current_sprite, 8, 241, 1)
move_stop(&current_sprite, 4, 359, 1)
&mcrap = create_sprite(359, 241, 7, 167, 1);
sp_seq(&mcrap, 167);
playsound(24, 22052, 0, 0, 0);
sp_active(&current_sprite, 0);
return;
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

