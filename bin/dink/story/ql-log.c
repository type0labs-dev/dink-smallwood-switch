// QUEST VALUES
//
//   1 - Feed pigs
//   2 - Find Quackers
//   3 - Kill farm bugs
//   4 - Get nuts
//   5 - Visit vizard
//   6 - Kill bonca
//   7 - Visit aunt
//   8 - Help Terris thief
//   9 - (find guy in cave)
//  10 - Help guy in cave
//  11 - Find Mary
//  12 - (visit Kernsin)
//  13 - Warn Kernsin of Cast attack
//  14 - Find evidence of Cast plot
//  15 - (visit Windemere)
//  16 - (solve the hunger crisis)
//  17 - (visit Joppa Island)
//  18 - (visit Castle Goodheart)
//  19 - Find Milder
//  20 - Return to Castle Goodheart / Game Complete
//  21 - Bonny the bonca
// Quests 1-3 and 8-11 form clusters that can be started (and, for 1 and 2, solved) in parallel
// Quest 7 is optional, and quests 3 and 8 don't even need to be started
// Descriptions in parenthesis indicate segments where player has no explicit goal


void quest_started(void)
{
  if(&arg1 == 1)
  {
    return(1);
  }

  if(&arg1 == 2)
  {
    if(&old_womans_duck > 0)
    {
      return(1);
    }
  }

  if(&arg1 == 3)
  {
    if(&farmer_quest > 0)
    {
      return(1);
    }
  }

  if(&arg1 == 4)
  {
    if(&story > 1)
    {
      return(1);
    }
  }

  if(&arg1 == 5)
  {
    if(&wizard_again > 0)
    {
      return(1);
    }
  }

  if(&arg1 == 6)
  {
    if(&wizard_see > 1)
    {
      return(1);
    }
  }

  if(&arg1 == 7)
  {
    if(&letter > 1)
    {
      return(1);
    }
  }

  if(&arg1 == 8)
  {
    if(&thief > 1)
    {
      return(1);
    }
  }

  if(&arg1 == 10)
  {
    if(&caveguy > 0)
    {
      return(1);
    }
  }

  if(&arg1 == 11)
  {
    if(&s2-nad > 1)
    {
      return(1);
    }
  }
  
  if(&arg1 == 13)
  {
    if(&story > 8)
    {
      return(1);
    }
  }

  if(&arg1 == 14)
  {
    if(&mayor > 2)
    {
      return(1);
    }
  }
  
  if(&arg1 == 16)
  {
    if(&windemere > 0)
    {
      return(1);
    }
  }
  
  if(&arg1 == 19)
  {
    if(&story > 13)
    {
      return(1);
    }
  }

  if(&arg1 == 20)
  {
    if(&story > 14)
    {
      return(1);
    }
  }

  if(&arg1 == 21)
  {
    if(&boncahunt > 1)
    {
      return(1);
    }
  }


}

void quest_done(void)
{
  if(&arg1 == 1)
  {
    if(&pig_story > 0)
    {
      return(1);
    }
  }

  if(&arg1 == 2)
  {
    if(&old_womans_duck > 2)
    {
      return(1);
    }
  }

  if(&arg1 == 3)
  {
    if(&farmer_quest > 1)
    {
      return(1);
    }
  }

  if(&arg1 == 4)
  {
    if(&story > 2)
    {
      return(1);
    }
  }

  if(&arg1 == 5)
  {
    if(&wizard_see > 0)
    {
      return(1);
    }
  }

  if(&arg1 == 6)
  {
    if(&wizard_see > 2)
    {
      return(1);
    }
  }

  if(&arg1 == 7)
  {
    if(&s2-aunt > 1)
    {
      return(1);
    }
  }
  
  if(&arg1 == 8)
  {
    if(&thief > 3)
    {
      return(1);
    }
  }

  if(&arg1 == 10)
  {
    if(&caveguy > 4)
    {
      return(1);
    }
  }

  if(&arg1 == 11)
  {
    if(&s2-nad > 2)
    {
      return(1);
    }
  }   
  
  if(&arg1 == 13)
  {
    if(&mayor > 2)
    {
      return(1);
    }
  }    

  if(&arg1 == 14)
  {
    if(&mayor > 4)
    {
      return(1);
    }
  }

  if(&arg1 == 16)
  {
    if(&story > 10)
    {
      return(1);
    }
  }    

  if(&arg1 == 17)
  {
    if(&story > 11)
    {
      return(1);
    }
  }  

  if(&arg1 == 19)
  {
    if(&story > 14)
    {
      return(1);
    }
  }  

  if(&arg1 == 20)
  {
    if(&story > 15)
    {
      return(1);
    }
  }
  
  if(&arg1 == 21)
  {
    if(&boncahunt > 3)
    {
      return(1);
    }
  }

  return(0);
}

void quest_ongoing (void)
{
  quest_started(&arg1);
  if (&return == 1)
  {
    quest_done(&arg1);
    int &s = &return;
    if (&s == 0)
    {
      return(1);
    }
  }
  return(0);
}
void get_main_quest (void)
{
  return(0);

}

void log (void)
{
int &next;
start:
if (&next == 0)
{
	goto mainquest;
}
if (&next == 1)
{
	goto sidequest;
}
if (&next == 2)
{
	goto completed;
}
return;

mainquest:	
  quest_ongoing(1);
  if (&return == 1)
  {
    quest_ongoing(2);
    if (&return == 1)
    {
      choice_start();
      set_y 240
      title_start();
      -*- Missões Atuais -*-
      Minha mãe me pediu para alimentar os porcos.
      O pato de estimação da Ethel, Quackers, fugiu. Ela me pediu para procurá-lo.
        title_end();
		"Missões secundárias"
		"Missões concluídas"
        "Voltar"
        choice_end();
        if (&result == 1)
		{
			&next = 1;
			goto start;
		}
		if (&result == 2)
		{
			&next = 2;
			goto start;
		}
        return;
    }
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    Minha mãe me pediu para alimentar os porcos.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(2);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    O pato de estimação da Ethel, Quackers, fugiu. Ela me pediu para procurá-lo.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(4);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    Minha mãe me pediu para trazer nozes da árvore de Alktree.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(5);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    Um mago simpático me convidou para sua cabana a nordeste de Stonebrook.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(6);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    O Mago Martridge me encarregou de matar um Bonca que vive numa caverna a oeste.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(10);
  if (&return == 1)
  {
    quest_ongoing(11);
    if (&return == 1)
    {
		choice_start();
		set_y 240
		title_start();
		-*- Missões Atuais -*-
		Aceitei libertar um homem aprisionado pelos Cast na Mina Condenada.
		Aceitei procurar a filha da Nadine, Mary, que está desaparecida.
		title_end();
		"Missões secundárias"
		"Missões concluídas"
		"Voltar"
		choice_end();
		if (&result == 1)
		{
			&next = 1;
			goto start;
		}
		if (&result == 2)
		{
			&next = 2;
			goto start;
		}
		return;
	}
	choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    Aceitei libertar um homem aprisionado pelos Cast na Mina Condenada.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(11);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    Aceitei procurar a filha da Nadine, Mary, que está desaparecida.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  //Let's wait a bit so engine can clean up garbage or whatever
  //AFAIK this is only needed for 'vanilla' 1.08, not freedink, hd or their derivatives
  wait(0);
  quest_ongoing(13);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    Ouvi cavaleiros dos Cast tramando atacar Kernsin durante o festival. Preciso impedi-los!
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(14);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    O prefeito de Kernsin precisa de provas dos planos de ataque dos Cast.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  quest_ongoing(16);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    O povo de Windemere está morrendo de fome. Devo tentar encontrar comida para eles.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  } 
  quest_ongoing(19);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    O Rei Daniel me deu uma missão: descobrir o paradeiro de Milder Flatstomp nas Terras Sombrias.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }     
  quest_ongoing(20);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Atual -*-
    Preciso retornar ao Castelo de Goodheart para relatar ao Rei o ocorrido nas Terras Sombrias.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }       
  
  quest_done(20);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    Eu completei o jogo e salvei o reino!
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
    return;
  }
  choice_start();
  set_y 240
  title_start();
  Não tenho nenhuma missão principal ativa no momento.
    title_end();
	"Missões secundárias"
	"Missões concluídas"
    "Voltar"
    choice_end();
    if (&result == 1)
	{
		&next = 1;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
  return;
  
sidequest:
quest_ongoing(3);
if (&return == 1)
{
	quest_ongoing(7);
	if (&return == 1)
    {
		quest_ongoing(8);
		if (&return == 1)
		{
				quest_ongoing(21);
				if (&return == 1)
				{
				  choice_start();
				  set_y 240
				  title_start();
				  -*- Missões Secundárias -*-
				  	I should kill the monsters at Smilestein's farm, visit my aunt in Terris, help a shady-looking guy in his job west of the bar in Terris and find a lost pet bonca in Murkwood Forest.
					title_end();
					"Missões principais"
					"Missões concluídas"
					"Voltar"
					choice_end();
					if (&result == 1)
					{
						&next = 0;
						goto start;
					}
					if (&result == 2)
					{
						&next = 2;
						goto start;
					}
					return;
				}	
			  choice_start();
			  set_y 240
			  title_start();
			  -*- Missões Secundárias -*-
			  I should kill the monsters at Smilestein's farm, visit my aunt in Terris and help a shady-looking guy in his job west of the bar in Terris.
				title_end();
				"Missões principais"
				"Missões concluídas"
				"Voltar"
				choice_end();
				if (&result == 1)
				{
					&next = 0;
					goto start;
				}
				if (&result == 2)
				{
					&next = 2;
					goto start;
				}
				return;
		}
		quest_ongoing(21);
		if (&return == 1)
		{
		  choice_start();
		  set_y 240
		  title_start();
		  -*- Missões Secundárias -*-
		  	I should kill the monsters at Smilestein's farm, visit my aunt in Terris, and find a lost pet bonca in Murkwood Forest.
			title_end();
			"Missões principais"
			"Missões concluídas"
			"Voltar"
			choice_end();
			if (&result == 1)
			{
				&next = 0;
				goto start;
			}
			if (&result == 2)
			{
				&next = 2;
				goto start;
			}
			return;
		}	
		  choice_start();
		  set_y 240
		  title_start();
		  -*- Missões Secundárias -*-
		  O Sr. Smilestein me pediu para dar um jeito nos monstros da fazenda dele.
		  Minha tia, Maria Kneedlewood, me convidou para sua casa em Terris.
			title_end();
			"Missões principais"
			"Missões concluídas"
			"Voltar"
			choice_end();
			if (&result == 1)
			{
				&next = 0;
				goto start;
			}
			if (&result == 2)
			{
				&next = 2;
				goto start;
			}
			return;
    }
	quest_ongoing(8);
	if (&return == 1)
    {
		quest_ongoing(21);
		if (&return == 1)
		{
		  choice_start();
		  set_y 240
		  title_start();
		  -*- Missões Secundárias -*-
		  	I should kill the monsters at Smilestein's farm, help a shady-looking guy in his job west of the bar in Terris and find a lost pet bonca in Murkwood Forest.
			title_end();
			"Missões principais"
			"Missões concluídas"
			"Voltar"
			choice_end();
			if (&result == 1)
			{
				&next = 0;
				goto start;
			}
			if (&result == 2)
			{
				&next = 2;
				goto start;
			}
			return;
		}	
		  choice_start();
		  set_y 240
		  title_start();
		  -*- Missões Secundárias -*-
		  O Sr. Smilestein me pediu para dar um jeito nos monstros da fazenda dele.
		  Ofereci ajuda para um sujeito no bar de Terris. Ele marcou a oeste do bar.
			title_end();
			"Missões principais"
			"Missões concluídas"
			"Voltar"
			choice_end();
			if (&result == 1)
			{
				&next = 0;
				goto start;
			}
			if (&result == 2)
			{
				&next = 2;
				goto start;
			}
			return;
	}
	quest_ongoing(21);
	if (&return == 1)
	{
	  choice_start();
	  set_y 240
	  title_start();
	  -*- Missões Secundárias -*-
	  O Sr. Smilestein me pediu para dar um jeito nos monstros da fazenda dele.
      Ofereci ajuda para Emily encontrar seu Bonca de estimação, Bonny, na Floresta Murkwood.		  
		title_end();
		"Missões principais"
		"Missões concluídas"
		"Voltar"
		choice_end();
		if (&result == 1)
		{
			&next = 0;
			goto start;
		}
		if (&result == 2)
		{
			&next = 2;
			goto start;
		}
		return;
	}	
    choice_start();
    set_y 240
    title_start();
    -*- Missão Secundária -*-
	O Sr. Smilestein me pediu para dar um jeito nos monstros da fazenda dele.
    title_end();
	"Missões principais"
	"Missões concluídas"
    "Voltar"
	choice_end();
	if (&result == 1)
	{
		&next = 0;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
	return;
  }	
  quest_ongoing(7);
  if (&return == 1)
  {
    quest_ongoing(8);
    if (&return == 1)
    {
		quest_ongoing(21);
		if (&return == 1)
		{
		  choice_start();
		  set_y 240
		  title_start();
		  -*- Missões Secundárias -*-
		  I should visit my aunt in Terris, help a shady-looking guy in his job west of the bar in Terris and find a lost pet bonca in Murkwood Forest.
			title_end();
			"Missões principais"
			"Missões concluídas"
			"Voltar"
			choice_end();
			if (&result == 1)
			{
				&next = 0;
				goto start;
			}
			if (&result == 2)
			{
				&next = 2;
				goto start;
			}
			return;
		}
      choice_start();
      set_y 240
      title_start();
      -*- Missões Secundárias -*-
      Minha tia, Maria Kneedlewood, me convidou para sua casa em Terris.
      Ofereci ajuda para um sujeito no bar de Terris. Ele marcou a oeste do bar.
		title_end();
		"Missões principais"
		"Missões concluídas"
		"Voltar"
		choice_end();
		if (&result == 1)
		{
			&next = 0;
			goto start;
		}
		if (&result == 2)
		{
			&next = 2;
			goto start;
		}
		return;
    }
	quest_ongoing(21);
    if (&return == 1)
    {
      choice_start();
      set_y 240
      title_start();
      -*- Missões Secundárias -*-
      Minha tia, Maria Kneedlewood, me convidou para sua casa em Terris.
      Ofereci ajuda para Emily encontrar seu Bonca de estimação, Bonny, na Floresta Murkwood.	  
		title_end();
		"Missões principais"
		"Missões concluídas"
		"Voltar"
		choice_end();
		if (&result == 1)
		{
			&next = 0;
			goto start;
		}
		if (&result == 2)
		{
			&next = 2;
			goto start;
		}
		return;
    }	
    choice_start();
    set_y 240
    title_start();
	-*- Missão Secundária -*-
    Minha tia, Maria Kneedlewood, me convidou para sua casa em Terris.
    title_end();
	"Missões principais"
	"Missões concluídas"
    "Voltar"
	choice_end();
	if (&result == 1)
	{
		&next = 0;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
	return;
  }  
  quest_ongoing(8);
  if (&return == 1)
  {
	quest_ongoing(21);
    if (&return == 1)
    {
      choice_start();
      set_y 240
      title_start();
      -*- Missões Secundárias -*-
      Ofereci ajuda para um sujeito no bar de Terris. Ele marcou a oeste do bar.
      Ofereci ajuda para Emily encontrar seu Bonca de estimação, Bonny, na Floresta Murkwood.	  
		title_end();
		"Missões principais"
		"Missões concluídas"
		"Voltar"
		choice_end();
		if (&result == 1)
		{
			&next = 0;
			goto start;
		}
		if (&result == 2)
		{
			&next = 2;
			goto start;
		}
		return;
    }
    choice_start();
    set_y 240
    title_start();
    -*- Missão Secundária -*-
    Ofereci ajuda para um sujeito no bar de Terris. Ele marcou a oeste do bar para um 'trabalho'.
    title_end();
	"Missões principais"
	"Missões concluídas"
    "Voltar"
	choice_end();
	if (&result == 1)
	{
		&next = 0;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
	return;
  }
  quest_ongoing(21);
  if (&return == 1)
  {
    choice_start();
    set_y 240
    title_start();
    -*- Missão Secundária -*-
    Ofereci ajuda para Emily encontrar seu Bonca de estimação, Bonny, na Floresta Murkwood.
    title_end();
	"Missões principais"
	"Missões concluídas"
    "Voltar"
	choice_end();
	if (&result == 1)
	{
		&next = 0;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
	return;
  }
  choice_start();
  set_y 240
  title_start();
  Não tenho nenhuma missão secundária ativa.
    title_end();
	"Missões principais"
	"Missões concluídas"
    "Voltar"
	choice_end();
	if (&result == 1)
	{
		&next = 0;
		goto start;
	}
	if (&result == 2)
	{
		&next = 2;
		goto start;
	}
	return;

completed:
quest_done(1);
if (&return == 0)
{
	quest_done(2);
	if (&return == 0)
	{	
	choice_start();
		set_y 240  
	title_start();
	  Ainda não concluí nenhuma missão. É melhor eu me mexer!
		title_end();
		
		"Missões principais"
		"Missões secundárias"
		"Voltar"
		choice_end();
		if (&result == 1)
		{
			&next = 0;
			goto start;
		}
		if (&result == 2)
		{
			&next = 1;
			goto start;
		}
		return;

	}
}
choice_start();
	set_y 240  
title_start();
  Missões concluídas:
    title_end();
	(&pig_story > 0)"Criação de porcos"
	(&old_womans_duck > 1)"A busca pelo pato"
	(&farmer_quest > 1)"A fazenda de Smilestein"
	(&story > 2)"Colheita de nozes"
	(&wizard_see > 0)"Visita mágica"
	(&wizard_see > 2)"Caçada ao Bonca"
	(&s2-aunt > 0)"Mudando para Terris"
	(&caveguy > 4)"Fuga da prisão"
	(&thief > 3)"Aplicando a lei"
	(&s2-nad > 2)"O resgate da garota"
	(&mayor > 4)"Salvando o desfile"
	(&boncahunt > 3)"Caçada amigável ao Bonca"
	(&story > 10)"Pato na panela"
	(&story > 11)"O extermínio dos dragões"
	(&story > 15)"Derrotando os Anciões"
	"Missões principais ativas"
	"Missões secundárias ativas"
    "Voltar"
	choice_end();
	if (&result == 1)
	{
        choice_start()
        set_y 240
        title_start();
Alimentei os porcos, como minha mãe pediu.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 2)
	{
		if (&old_womans_duck == 3)
		{
        choice_start()
        set_y 240
        title_start();
Encontrei o Quackers... a Ethel nunca mais vai vê-lo.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
		}
		if (&old_womans_duck == 5)
		{
        choice_start()
        set_y 240
        title_start();
Encontrei o Quackers. Agora a Ethel aprendeu a não mandar em mim!
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
		}
        choice_start()
        set_y 240
        title_start();
Encontrei o Quackers e convenci ele a voltar para a Ethel.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 3)
	{
        choice_start()
        set_y 240
        title_start();
Acabei com todos os monstros que aterrorizavam a fazenda do Sr. Smilestein.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 4)
	{
        choice_start()
        set_y 240
        title_start();
Peguei as nozes que minha mãe pediu. Se ao menos eu tivesse voltado um pouco antes...
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 5)
	{
        choice_start()
        set_y 240
        title_start();
Visitei o Martridge na cabana dele. Ele disse que vê potencial mágico em mim!
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 6)
	{
        choice_start()
        set_y 240
        title_start();
Derrotei o terrível Bonca.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 7)
	{
        choice_start()
        set_y 240
        title_start();
A tia Maria me recebeu muito bem. O marido dela, por outro lado, me odiou.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 8)
	{
		if (&caveguy > 6)
		{
        choice_start()
        set_y 240
        title_start();
Libertei o sujeito aprisionado pelos Cast e salvei a vida dele.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
		}
        choice_start()
        set_y 240
        title_start();
Libertei o sujeito da prisão dos Cast. Mas os guardas o mataram logo em seguida.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 9)
	{
        choice_start()
        set_y 240
        title_start();
Eu, er... ajudei os guardas a prender um criminoso em Terris.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 10)
	{
        choice_start()
        set_y 240
        title_start();
Resgatei Mary das garras do culto diabólico dos Cavaleiros de Cast.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 11)
	{
        choice_start()
        set_y 240
        title_start();
Frustrei completamente o plano dos Cast de atacar Kernsin!
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 12)
	{
        choice_start()
        set_y 240
        title_start();
Encontrei o Bonca da Emily na floresta e levei ela de volta sã e salva para casa.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 13)
	{
        choice_start()
        set_y 240
        title_start();
Consegui comida para o povo de Windemere e, de quebra, desmantelei a religião dos patos!
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 14)
	{
        choice_start()
        set_y 240
        title_start();
Derrotei os dois dragões que aterrorizavam os moradores da Ilha de Joppa.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}
	if (&result == 15)
	{
        choice_start()
        set_y 240
        title_start();
Derrotei o antigo Seth e salvei o reino, embora tenha chegado tarde demais para salvar Milder.
        title_end();
         "Voltar"
         choice_end()	 
		 goto start;
	}			
	if (&result == 16)
	{
		&next = 0;
		goto start;
	}
	if (&result == 17)
	{
		&next = 1;
		goto start;
	}
	return;

}

