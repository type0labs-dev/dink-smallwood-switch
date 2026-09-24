void main( void )
{
 int &talker;
 &talker = 0;
 int &bsword;
 int &b2sword;
 int &bclaw;
 int &bnut; 
 int &bad;
 if (&story > 10)
 {
  &talker = 2;
  return;
 }
 &bad = random(3, 1);
 if (&bad == 1)
 {
  &bad = random(3, 1);
  if (&bad == 1)
  {
  say_stop("`2Bem-vindo ao penhor da Jill.", &current_sprite);
  }
  if (&bad == 2)
  {
  say_stop("`2Ah, também tem umas comidinhas...", &current_sprite);
  }
  if (&bad == 3)
  {
  say_stop("`2Os patos... os patos...", &current_sprite);
  }
 }
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
(&talker == 0)"Ver as novidades"
(&talker == 1)"Ver o que está à venda"
(&talker == 2)"Dizer oi"
 "Vender um item"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   say_stop("E aí, como andam as coisas por aqui?", 1);
   wait(250);
   say_stop("`2Ah, tudo bem, moço, valeu por perguntar.", &current_sprite);
   wait(250);
   say_stop("Que história é essa de patos?", 1);
   wait(250);
   say_stop("`2Esses patos são nossos amigos e guardiões,", &current_sprite);
   say_stop("`2e foi graças a eles que temos tudo hoje.", &current_sprite);
   wait(1000);
   say_stop("Tá, essa foi a frase mais bizarra que ouvi hoje.", 1);
   wait(250);
   say_stop("`2Trate bem os patos desta cidade.", &current_sprite);
   wait(250);
   say_stop("Claro, sem problemas.", 1);
   &talker = 1;
  }
  if (&result == 2)
  {
   say_stop("Ué, você tem algo pra vender?", 1);
   wait(250);
   say_stop("`2Bem, eu... receio que não no momento, moço.", &current_sprite);
   wait(250);
   say_stop("Por que não?", 1);
   wait(250);
   say_stop("`2Com os impostos que aumentaram por causa dos patos,", &current_sprite);
   wait(250);
   say_stop("`2eu fui forçado a vender quase tudo que tinha pra pagar.", &current_sprite);
   wait(250);
   say_stop("Entendi.", 1);
   wait(250);
   say_stop("`2Talvez se você voltar mais tarde,", &current_sprite);
   wait(250);
   say_stop("`2mas agora não dá.", &current_sprite);
  }
  if (&result == 3)
  {
   say_stop("Oi, Jill, como você tá?", 1);
   wait(250);
   say_stop("`2Ah, Dink, obrigada, muito obrigada por nos salvar.", &current_sprite);
   wait(250);
   say_stop("`2Eu não sabia o que ia ser da cidade.", &current_sprite);
   wait(250);
   say_stop("`2Eu tô bem, as coisas tão melhorando.", &current_sprite);
   wait(250);
   say_stop("`2Valeu mesmo.", &current_sprite);
  }
  if (&result == 4)
  {
   goto sell;
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 if (&story > 10)
 {
  say_stop("`2Que tipo de traidor doente você é?!?", &current_sprite);
  return;
 }
 say_stop("`2Por favor, não me bate, moço.", &current_sprite);
 wait(250);
}

void sell(void )
{
//let's sell some stuff back

sell:

//how many items do they have?

&bsword = count_item("item-sw1");
&b2sword = count_item("item-sw2");
&bclaw = count_item("item-cl");
&bnut = count_item("item-nut");

         choice_start()
        set_y 240
        set_title_color 6
        title_start();
"A gente quer comprar umas coisas. O que você tem?"
        title_end();
       (&bsword > 0)  "Vender uma Espada Longa - $200"
       (&bnut > 0)  "Vender uma noz - $2"
       (&b2sword > 0)  "Vender uma Espada Garra - $1000"
       (&bclaw > 0)  "Vender uma Garra Matadora - $150"
        "Não vender nada"
        choice_end()

if (&result == 1)
    {
     kill_this_item("item-sw1");
     &gold += 200;
    goto sell;
    }

if (&result == 2)
    {
     kill_this_item("item-nut");
     &gold += 2;
    goto sell;
    }

if (&result == 3)
    {
     kill_this_item("item-sw2");
     &gold += 1000;
    goto sell;
    }
if (&result == 4)
    {
     kill_this_item("item-cl");
     &gold += 150;
    goto sell;
    }

   unfreeze(1);
   goto mainloop;
   return;
}
