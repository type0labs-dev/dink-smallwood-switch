
void main(void)
{

}

void talk(void)
{
 if (&story > 3)
 {
 say_stop("Pode ter sido isso que começou aquele acidente.", 1);
 say("Mas agora não importa mais.", 1);
 return;
 }
 if (&story == 3)
 {
 say("Talvez isso tenha saído do controle.", 1);
 return;
 }
 say("Ahh, fogo. Quentinho.", 1);
}

void hit(void)
{
 if (&story > 3)
 {
 say("Lareira idiota!", 1);
 return;
 }
 say("Eita, que quente!", 1);
}

