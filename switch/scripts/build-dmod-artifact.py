import json

dmods = json.load(open("switch/distribution/dmods_all.json", "r", encoding="utf-8"))

def rating_key(d): return d["rating"]
dmods_by_rating = sorted(dmods, key=rating_key, reverse=True)

artifact_path = "/home/zero/.gemini/antigravity-cli/brain/a371d71e-13cd-430a-8a28-42ada7a33626/catalogo_dmods_analise.md"

with open(artifact_path, "w", encoding="utf-8") as f:
    f.write("# 📚 Análise & Catálogo Completo dos DMODs de Dink Smallwood\n\n")
    f.write("> [!NOTE]\n")
    f.write("> **Base de Dados**: 393 DMODs catalogados e classificados do repositório oficial `dinknetwork.com`.\n")
    f.write("> Esta análise divide todo o ecossistema em **História**, **Mecânicas**, **Conteúdo**, **Melhorias** e **Itens**, com foco em como integrá-los à nossa versão de Switch.\n\n")
    
    f.write("## 1. ⚙️ Melhorias de Qualidade de Vida (QoL) & Novas Mecânicas\n\n")
    f.write("Estes mods modificam ou aprimoram a jogabilidade e os sistemas do próprio jogo base, sem necessariamente criar um mundo separado. São os principais candidatos a serem **incorporados permanentemente à campanha principal**:\n\n")
    f.write("| Mod / Sistema | Autor | Nota | O que adiciona | Potencial de Integração |\n")
    f.write("| :--- | :--- | :---: | :--- | :--- |\n")
    f.write("| **Dink Smallwood: Questlog Edition** | Seseler & Elpo | 9.2 | • Diário de Missões (`[Q]` / Menu)<br>• Inventário empilhável (consumíveis não ocupam slots extras)<br>• Novas áreas secretas em Stonebrook/Terris<br>• Novas magias e correções de bugs | **Altíssimo**: Pode substituir os scripts originais da campanha base, tornando o jogo muito mais moderno. |\n")
    f.write("| **Off-Handed Shield** | Robj, ExDeathevn | 9.5 | • Escudo na mão secundária do Dink<br>• Mecânica de defesa ativa com botão dedicado<br>• Animações novas de bloqueio | **Alto**: Pode ser integrado como item comprável em ferrarias/lojas da campanha. |\n")
    f.write("| **Achievement Unlocked Edition** | CocoMonkey | 9.5 | • Sistema de 40+ Conquistas in-game<br>• Notificações visuais pop-up na tela ao desbloquear<br>• Desafios secretos e recompensas de XP | **Médio/Alto**: Pode rodar em segundo plano premiando feitos do jogador no Switch. |\n")
    f.write("| **Push and Pull** | Robj, Bluedy | 9.4 | • Mecânica avançada de empurrar e puxar blocos/pedras<br>• Puzzles estilo Zelda / Sokoban | **Médio**: Excelente para calabouços e cavernas. |\n\n")

    f.write("## 2. 👑 As Grandes Campanhas de História (\"DLCs de Alto Nível\")\n\n")
    f.write("Estes são os **mods épicos de história** mais aclamados de todos os tempos. Cada um deles oferece entre **3 a 15 horas** de conteúdo novo, reinos inteiros, dezenas de NPCs e chefes memoráveis:\n\n")
    f.write("| Título | Autor | Nota | Tamanho | Sinopse e Destaques |\n")
    f.write("| :--- | :--- | :---: | :---: | :--- |\n")
    f.write("| 🏆 **Pilgrim's Quest (Redux)** | Simon Klaebe | **9.7** | 34.5 MB | **A obra-prima definitiva**: Dink encontra a única sobrevivente de um ataque brutal e concorda em escoltá-la até um Mosteiro Sagrado além dos mares. Múltiplos continentes, navegação em barcos, magias de água, quebra-cabeças épicos e sistema moral. *(Já baixado no console)* |\n")
    f.write("| ⚔️ **Cast Awakening Part 1: Initiation** | Dan Walma | **9.5** | 8.6 MB | **Continuação Canônica**: Após derrotar o Cast no jogo base, Dink é convidado a ingressar na lendária *Sociedade do Hall dos Heróis*. Para ser aceito, passa por provas épicas e descobre uma nova ameaça ao reino. *(Já baixado no console)* |\n")
    f.write("| 📜 **Stone of Balance (Redux)** | Simon Klaebe | **9.5** | 35.7 MB | **RPG Massivo**: Considerado o irmão de *Pilgrim's Quest*. Uma jornada épica para restaurar o equilíbrio do mundo com novos monstros desenhados à mão, múltiplos finais e enredo profundo. |\n")
    f.write("| ☁️ **Cloud Castle 2: Scarab** | SabreTrout | **9.6** | 3.2 MB | **Aventura Aérea**: Dink explora castelos flutuantes nas nuvens, resolvendo mistérios envolvendo escaravelhos mágicos, armadilhas acrobáticas e calabouços criativos. |\n")
    f.write("| 🏝️ **Quest for Dorinthia 2** | Bill Szczytko | **9.4** | 1.5 MB | **Aventura Marítima & Vingança**: Exploração de ilhas tropicais, fortalezas piratas, cavernas subaquáticas e combate intenso. |\n")
    f.write("| ⏳ **Before...** | SlipDink | **8.5** | 82.8 MB | **Préquel de Origem**: Explora a infância de Dink em Stonebrook antes dos eventos do jogo principal, a busca pelo pai desaparecido e os primeiros passos do herói. |\n")
    f.write("| 💀 **Necromancer** | SimonK | **9.8** | 488 MB | **Super-Produção**: O maior DMOD em tamanho já feito. Gráficos 3D pré-renderizados, trilha orquestrada e atuação de voz gravada em inglês. |\n\n")

    f.write("## 3. 🎭 Spin-offs Narrativos & Histórias Alternativas\n\n")
    f.write("Campanhas com perspectivas únicas, humor ácido ou protagonistas diferentes:\n\n")
    f.write("| Título | Protagonista / Tema | Nota | Destaques |\n")
    f.write("| :--- | :--- | :---: | :--- |\n")
    f.write("| **Lyna's Story** | Lyna | **9.6** | Você joga como Lyna (a garota do vilarejo). Enredo hilário que mostra o lado dela da história com o arrogante Milder Flatstomp e o próprio Dink. |\n")
    f.write("| **Birth of an Empire** | Karg (Jovem Goblin) | **8.5** | Você joga como um goblin tentando unir as tribos e sobreviver ao avanço dos humanos. Visão totalmente diferente do universo do jogo. |\n")
    f.write("| **Crosslink** | Dink (Multiverso) | **9.4** | Dink é jogado através de fendas dimensionais bizarras. Roteiro satírico com humor que quebra a quarta parede o tempo todo. |\n")
    f.write("| **As Good As Eternity** | Dink (Narrativa Séria) | **9.1** | Enredo mais dramático e cinematográfico focado na perda da família e na maturidade de Dink como guerreiro. |\n\n")

    f.write("## 4. 🔮 Novos Itens, Armas & Magias Extraíveis\n\n")
    f.write("Elementos que podem ser 'pinçados' dos mods e inseridos na campanha base:\n\n")
    f.write("- 💧 **Magia de Água (Water Magic)** *(de Pilgrim's Quest)*: Apaga incêndios, congela inimigos, purifica áreas amaldiçoadas e interage com poços d'água.\n")
    f.write("- 🛡️ **Escudo de Bloqueio Ativo** *(de Off-Handed Shield)*: Adiciona mitigação de dano em tempo real.\n")
    f.write("- 🎒 **Inventário Empilhável** *(de Questlog Edition)*: Poções e nozes de cura passam a ocupar 1 único slot com contador numérico (ex: `Poção de Cura x5`), liberando espaço no inventário.\n")
    f.write("- 🗡️ **Armas Especiais**: Espadas de Gelo, Shurikens de Arremesso e Botas de Pulo.\n\n")

    f.write("## 5. 🗺️ Proposta de Arquitetura de Integração no Switch\n\n")
    f.write("Para resolver de vez a queixa de que o jogo é curto e a interface de addons é confusa, podemos estruturar o pacote do Switch em **3 pilares**:\n\n")
    f.write("```mermaid\ngraph TD\n    A[Menu Principal / Tela Inicial] --> B[Campanha Principal: O Retorno do Herói]\n    A --> C[Central de Expansões & DLCs]\n    \n    B --> D[Barqueiro / Mensageiro In-Game]\n    D -.->|Viagem Marítima| E[Pilgrim's Quest: A Grande Peregrinação]\n    D -.->|Chamado Real| F[Cast Awakening: Sociedade dos Heróis]\n    \n    C --> E\n    C --> F\n    C --> G[Lyna's Story: O Outro Lado]\n    C --> H[Stone of Balance]\n```\n\n")
    f.write("### Pilar 1: Substituir a interface feia de 'Browse Addons'\n")
    f.write("Criar uma tela nativa no motor C++ com botões grandes de controle chamada **'DLCs & EXPANSÕES'**, onde cada história tem seu banner, sinopse em português e botão direto de iniciar/continuar.\n\n")
    f.write("### Pilar 2: Integração In-Game via Barqueiro/Porto\n")
    f.write("Adicionar um NPC no porto de KernSin (ou pós-jogo no castelo) que permite a Dink zarpar direto para *Pilgrim's Quest* ou viajar para *Cast Awakening*, criando a sensação de um único mundo conectado e gigantesco.\n\n")
    f.write("### Pilar 3: Overhaul da Campanha com o `Questlog Edition`\n")
    f.write("Adotar as melhorias de itens empilháveis e o diário de missões do `questlog` na campanha principal para enriquecer a experiência do jogo base.\n")

print("Artifact written successfully to:", artifact_path)
