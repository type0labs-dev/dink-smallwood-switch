void main( void )
{
 int &dude;


 if (&caveguy == 0)
 {
  freeze(1);
  &dude = create_sprite(464, 116, 0, 0, 0);

 &temp1hold = &dude;
  sp_brain(&dude, 0);
  sp_base_walk(&dude, 370);
  sp_speed(&dude, 2);
  sp_timing(&dude, 0);
 //set starting pic
  sp_pseq(&dude, 373);
  sp_pframe(&dude, 1);
  sp_dir(&dude, 2);
  //Playmidi("Mystery.mid", 1);
  say_stop("`5Me ajuda!", &dude);
  wait(300);
  say_stop("Que diabos!?", 1);
  move_stop(1, 6, 130, 1);
  move_stop(1, 3, 190, 1);
  move_stop(1, 6, 300, 1);
  say_stop("Qual é o seu problema?", 1);
  move(&dude, 1, 400, 1);
  say_stop("`5Eles me jogaram aqui", &dude);
  wait(300);
  say_stop("Hã?", 1);
  wait(200);
  say_stop("Quem te jogou aqui?", 1);
  wait(300);

  say_stop("`5Eles, os agentes do Cast.", &dude);
  sp_dir(1, 2);
  wait(750);
  say_stop("Ele tá falando a verdade?", 1);
  sp_dir(1, 6);
  wait(500);
  say_stop("Você provavelmente mereceu...", 1);
  wait(300);
  say_stop("`5Não, na real não mereci.", &dude);
  wait(300);
  say_stop("Ah.", 1);
  wait(300);
  say_stop("`5Então você vai me tirar daqui ou não!", &dude);
  wait(300);
  say_stop("`5Eles voltam aqui logo, e vão matar a gente!", &dude);
  wait(300);
  say_stop("Tá bom, tá bom, como eu te tiro daí?", 1);
  wait(300);
  say_stop("`5Não sei. Aquela estátua parece que me prende aqui.", &dude);
  wait(200);
  say_stop("`5Acho que é protegida por magia.", &dude);
  wait(250);
  say_stop("`5Você conhece alguma, moleque?", &dude);
  wait(300);
  say_stop("Hmm, só minha bola de fogo.", 1);
  wait(300);
  say_stop("`5Acho que isso não vai adiantar.", &dude);
  wait(300);
  say_stop("`5Tenta na vila, alguém lá deve saber de algo.", &dude);
  wait(300);
  say_stop("Ok... a propósito, meu nome é Dink. Até mais.", 1);
  &caveguy = 1;
  unfreeze(1);
  return;
 }
 if (&caveguy == 1)
 {
  freeze(1);
  &dude = create_sprite(464, 116, 0, 0, 0);
 &temp1hold = &dude;

  sp_brain(&dude, 0);
  sp_base_walk(&dude, 370);
  sp_speed(&dude, 2);
  sp_timing(&dude, 0);
 //set starting pic
  sp_pseq(&dude, 371);
  sp_pframe(&dude, 1);
  sp_dir(&dude, 2);
  //Playmidi("Mystery.mid", 1);
  say_stop("`5E aí, alguma sorte?", &dude);
  move_stop(1, 6, 130, 1);
  say_stop("Ah, tô nessa.", 1);
  wait(500);
  say_stop("`5Se apressa!!", &dude);
  sp_dir(1, 2);
  wait(750);
  sp_dir(1, 6);
  wait(500);
  say_stop("Anotado.", 1);
  unfreeze(1);
 }
 if (&caveguy == 2)
 {
  freeze(1);
  &dude = create_sprite(464, 116, 0, 0, 0);
 &temp1hold = &dude;

  sp_brain(&dude, 0);
  sp_base_walk(&dude, 370);
  sp_speed(&dude, 2);
  sp_timing(&dude, 0);
 //set starting pic
  sp_pseq(&dude, 371);
  sp_pframe(&dude, 1);
  sp_dir(&dude, 2);
  //Playmidi("Mystery.mid");
  wait(500);
  say_stop("`5Já tem alguma sorte?", &dude);
  move_stop(1, 6, 130, 1);
  say_stop("Tem um velho na vila que conhece umas magias.", 1);
   wait(200:
  say_stop("Ele pode ter um feitiço que ajude a gente.", 1);
  wait(500);
  sp_dir(&dude, 2);
  wait(750);
  sp_dir(&dude, 4);
  wait(500);
  say_stop("`5ENTÃO POR QUE DIABOS VOCÊ TÁ AQUI?", &dude);
  wait(250);
  say_stop("Ah é, desculpa.", 1);
  unfreeze(1);
 }
 if (&caveguy == 3)
 {
  freeze(1);
 &temp1hold = &dude;

  &dude = create_sprite(464, 116, 0, 0, 0);
  sp_brain(&dude, 0);
  sp_base_walk(&dude, 370);
  sp_speed(&dude, 2);
  sp_timing(&dude, 0);
 //set starting pic
  sp_pseq(&dude, 371);
  sp_pframe(&dude, 1);
  sp_dir(&dude, 2);
  //Playmidi("Mystery.mid");
  wait(500);
  say_stop("`5E aí, alguma sorte AGORA!?", &dude);
  wait(250);
  move_stop(1, 6, 130, 1);
  say_stop("O maldito do velho diz que eu ainda não sou poderoso o bastante,", 1);
  wait(200);
  say_stop("então tô tentando aumentar minhas habilidades.", 1);
  wait(750);
  sp_dir(&dude, 2);
  wait(500);
  sp_dir(&dude, 4);
  wait(500);
  say_stop("`5Ah, que ótimo.", &dude);
  wait(200);
  say_stop("`5Eu vou ficar aqui MORRENDO e torcendo pra aqueles agentes não voltarem!!", &dude);
  wait(250);
  say_stop("Ok, ok, tô indo.", 1);
  unfreeze(1);
 }
 if (&caveguy == 4)
 {
  freeze(1);
  &dude = create_sprite(464, 116, 0, 0, 0);
 &temp1hold = &dude;

  sp_brain(&dude, 0);
  sp_base_walk(&dude, 370);
  sp_speed(&dude, 2);
  sp_timing(&dude, 0);
 //set starting pic
  sp_pseq(&dude, 371);
  sp_pframe(&dude, 1);
  sp_dir(&dude, 2);
  //Playmidi("Mystery.mid");
  wait(500);
  say_stop("`5Vou morrer logo, eu sei.", &dude);
  wait(300);
  say_stop("`5E aí, alguma sorte!?!", &dude);
  wait(250);
  move_stop(1, 6, 130, 1);
  say_stop("Consegui o feitiço, então vamos ver se funciona.", 1);
  wait(250);
  say_stop("`5Boa!!", &dude);
  wait(250);
  say_stop("`5Mas se apressa, que eu juro que ouvi algo antes de você chegar.", &dude);
  wait(250);
  say_stop("Ok.", 1);
  unfreeze(1);
 }
}


