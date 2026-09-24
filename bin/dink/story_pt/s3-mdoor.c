void main( void )
{
}

void touch( void )
{
 freeze(1);
 move_stop(1, 4, 300,1 );
 sp_dir(1, 6);
 say("Tá trancado.", 1);
 unfreeze(1); 
}
