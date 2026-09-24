//Script for achievement notification banners (PT-BR)
//Displays for five seconds, remaking banner if switching screens during that time.

void award( void )
{
    // &arg1 = achievement number (1..28)
    int &slot = 20 + &arg1;
    int &has = game_exist(&slot);
    if (&has == 0)
    {
        save_game(&slot);
        external("achievement", "achievement", &arg1);
    }
}

void menu( void )
{
    external("ach-menu", "achievement");
}

void achievement( void )
{
checka:
    int &check = get_sprite_with_this_brain(95, 0);

    if (&check > 0)
    {
        script_attach(1000);
        wait(1000);
        goto checka;
    }

    playsound(43, 22050, 0, 0, 0);
    int &chieve = create_sprite(500, 375, 95, 99, &arg1);

    &banframe = &arg1;
    sp_que(&chieve, 1000);

    spawn("achievement");
    kill_this_task();
}

void main( void )
{
    &juggle = &current_script;
    int &timer = spawn("timer");

checkloop:
    int &chievo = get_sprite_with_this_brain(95, 0);
    if (&chievo == 0)
    {
        &chievo = create_sprite(500, 375, 95, 99, &banframe);
        sp_que(&chievo, 1000);
    }
    wait(50);
    goto checkloop;
}

void remove( void )
{
    int &banner = get_sprite_with_this_brain(95, 0);
    if (&banner > 0)
    {
        sp_active(&banner, 0);
    }
    kill_this_task();
}
