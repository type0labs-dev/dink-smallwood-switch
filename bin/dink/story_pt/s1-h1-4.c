
void main(void)
{
if(&story > 3)
{
 int &who = sp(22);
 int &who2 = sp(23);
 int &who3 = sp(24);
 int &who4 = sp(20);
 int &who5 = sp(21);
 sp_active(&who,0);
 sp_active(&who2,0);
 sp_active(&who3,0);
 sp_active(&who4,0);
 sp_active(&who5,0);
 sp_active(&current_sprite,0);
 draw_hard_map();
}
}

void talk(void)
{
 if (&story >= 3)
 {
 say("Daqui a pouco pega fogo.", 1);
 return;
 }
say("Não tô com fome agora..", 1);
}

void hit(void)
{
 if (&story >= 3)
 {
 say("Ahh, não consigo salvar isso.", 1);
 return;
 }
say("Por que eu tenho que atacar móveis?", 1);
}

void push( void )
{
wait(500);

 if (&story >= 3)
 {
 say("É grande demais pra mover!", 1);
 return;
 }
say("Essa mesa deve estar parafusada no chão.", 1);


}


 