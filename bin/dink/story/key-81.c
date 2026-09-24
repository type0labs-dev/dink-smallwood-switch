

void main ( void )
{
  freeze(1);
  external("ql-log", "log");
  unfreeze(1);
  kill_this_task();
}

