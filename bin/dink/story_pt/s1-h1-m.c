
void main(void)
{
int &whob = sp(26);
sp_hitpoints(&current_sprite, 0);


 if (&story > 2)
 {
 sp_active(&whob,0);
// draw_hard_map();
 return;
 }

 if (&old_womans_duck > 2)
 {
 if (&pig_story == 0)
 {
move_stop(&current_sprite, 2, 160, 1);
freeze(&current_sprite);
wait(200);
say_stop("`#Dink, já tá anoitecendo! Nada de comida até você dar de comer aos porcos!", &current_sprite);
wait(200);
unfreeze(&current_sprite);
return;
 }
 &story = 2;
 move_stop(1, 8, 370, 1);
freeze(1);
move_stop(&current_sprite, 2, 200, 1);
freeze(&current_sprite);
wait(1000);
 say_stop("`#Dink, pode fazer uma coisa pra mim?", &current_sprite);
 wait(500);
 say_stop("Sim, o que foi?", 1);
 wait(500);
 say_stop("`#Pode ir até a floresta e ver se você consegue achar,", &current_sprite);
 wait(500);
 say_stop("`#umas nozes, acho que tá na época.", &current_sprite);
 wait(500);
 say_stop("Sem problema, já volto.", 1);
 wait(250);
 say_stop("`#Você é um amor.", &current_sprite);
 unfreeze(1);
 unfreeze(&current_sprite);
 return;
 }



 if (&story == 0)
 {
 //new game was just started.
 //make script live on
 int &cur_sprite = &current_sprite;
 playmidi("5.mid");
 freeze(1);
 freeze(&cur_sprite);
 wait(1000);
 say_stop("`#Dink, vai dar de comer aos porcos?", &cur_sprite);
 wait(200);
 say_stop("O quê, agora?", 1);
 wait(200);
 say_stop("`#SIM, AGORA.", &cur_sprite);
 unfreeze(1);
 unfreeze(&cur_sprite);
 playsound(22, 22050, 0,0,0);
 &update_status = 1;
 draw_status();
 &story = 1;

if (get_version() > 108)
{
//iphone will be changed to "large" in filename automatically if applicable
show_popup("interface/iphone/quicktip_feeding.rttex", 1000);

}
 return;
 }

}

void talk(void)
{
 freeze(1);
 freeze(&current_sprite);
 choice_start();
   "Perguntar sobre como alimentar os porcos"
   "Perguntar sobre seu pai" 
   "Pegar informação sobre a vila"
   "Ficar pistola sem motivo nenhum"
(&pig_story == 1) "Dizer que alimentou os porcos"
   "Sair"
 choice_end();

 wait(200);

 if (&result == 1)
  {
  say_stop("Mãe, como é que alimenta os porcos? Esqueci!",1);
  wait(200);
  say_stop("`#Muito engraçadinho, Dink. Você pega o saco de ração e", &current_sprite);
  say_stop("`#espalha no chiqueiro. E não fica provocando eles!", &current_sprite);
  wait(100);
  }

 if (&result == 2)
  {
  say_stop("Que tipo de homem era o pai?",1);
  wait(200);
  say_stop("`#Ele era um camponês como a gente.", &current_sprite);
  wait(200);
  say_stop("Ele era bom com a espada?",1);
  wait(200);
  say_stop("`#Claro que não. Ele era um ótimo fazendeiro e marido.", &current_sprite);

  }
 if (&result == 3)
  {
  say_stop("Me conta sobre essa vila.",1);
  wait(200);
  say_stop("`#O pessoal da vila é gente boa. Ah, a Rita quer te ver.", &current_sprite);
  wait(200);
  say_stop("Rita? Ela é muito véia, né?",1);
  wait(200);
  say_stop("`#Sim, Dink, ela é. <risada>", &current_sprite);
  }

 if (&result == 4)
  {
  say_stop("EU TE ODEIO!",1);
  wait(200);
  say_stop("`#Engole o choro que passa.",&current_sprite);
  }

 if (&result == 5)
  {
  say_stop("Terminei minhas tarefas, mãe.",1);
  wait(200);
  say_stop("`#Bom garoto. Vai visitar nossos vizinhos enquanto eu preparo o jantar.", &current_sprite);
  }


 unfreeze(1);
 unfreeze(&current_sprite);

  }

}

void hit(void)
{
 say_stop("`#Ai! Para com isso!", &current_sprite);

}

