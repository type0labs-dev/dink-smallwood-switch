void main( void )
{
 //setup Mog and do cutscene
freeze(1);
 playmidi("1009.mid");

wait(500);
 say_stop("Tanto massacre e ainda sem respostas.", 1);

 int &crap = create_sprite(317,301, 0, 0, 0);
 &temp2hold = &crap;
 sp_script(&crap, "en-gmog");
 freeze(&crap);
 
 wait(500);
 say_stop("`4Quem ousa acordar o poderoso Mog, rei dos Goblins?", &crap);
 wait(500);
 say_stop("Que isso? Você aprendeu bem a nossa língua, Mog.", 1);
 wait(500);
 say_stop("`4Claro. Fui criado por.. o que é isso? Meus camaradas estão todos no chão!", &crap);
 wait(500);
 say_stop("Fui eu quem os derrubou.",1);
 wait(500);
say_stop("AGORA ME CONTA DOS TEUS ESQUEMAS SECRETOS COM O CASTELO!", 1);
 wait(500);
 say_stop("`4Você? VOCÊ? EU TENHO QUE VINGAR MEUS IRMÃOS!", &crap);
 wait(500);
 sp_target(&crap, 1);
 sp_brain(&crap, 9);
screenlock(1);
unfreeze(1);
unfreeze(&crap);
}
