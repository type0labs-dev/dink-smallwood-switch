void main( void )
{
int &randy;
}

void hit( void )
{
&randy = random(3, 1); 

 if (&randy == 1)
 say("`4Mata ele, meninas!", &current_sprite);
 if (&randy == 2)
 say("`4Chegou o dia do juízo, pecador!", &current_sprite);
 if (&randy == 3)
 say("`4As meninas estão com fome - HORA DO JANTAR!", &current_sprite);

}

void talk( void )
{
&randy = random(3, 1); 

 if (&randy == 1)
 say("`4Você pisou na bola ao vir pra cá.", &current_sprite);
 if (&randy == 2)
 say("`4Seu sangue vai correr como o rio Jordão.", &current_sprite);
 if (&randy == 3)
 say("`4Posso te oferecer nosso presente de amor de dezembro? Só 80 reais!", &current_sprite);

}

