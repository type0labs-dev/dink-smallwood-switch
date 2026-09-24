void main( void )
{
 int &what;
 &temp1hold = sp(7);
}

void touch( void )
{
 if (&story > 10)
 {
  move_stop(1, 2, 175,1 );
  sp_dir(1, 6);
  say("`3Valeu por nos salvar, Dink!", &temp1hold);
  return;
 }
 &what = random(6, 1);
 freeze(1);
 move_stop(1, 2, 175,1 );
 sp_dir(1, 6);
 if (&what == 1)
 {
  say("`3Tá trancado.", &temp1hold);
 }
 if (&what == 2)
 {
  say("`3Cai fora.", &temp1hold);
 }
 if (&what == 3)
 {
  say("`3Eu te odeio.", &temp1hold);
 }
 if (&what == 4)
 {
  say("`3Nãããããooo!!", &temp1hold);
 }
 if (&what == 5)
 {
  say("`3Você não entra.", &temp1hold);
 }
 if (&what == 6)
 {
  say("`3Me deixa em paz.", &temp1hold);
 }
 unfreeze(1); 
}
