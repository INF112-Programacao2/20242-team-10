

![menuJogo](https://github.com/user-attachments/assets/75a49074-cc73-47b3-b859-551521f1d9ac)


# Jogo 2D

Como proposto no inicio da disciplina de INF 112 um Projeto Final que envolvesse os conceitos da matéria bem como boas práticas de programação, o nosso grupo decidiu criar um jogo na linguagem C++ utilizando a biblioteca SFML de modo a aplicarmos alguns conceitos estudados nas aulas, como classes e objetos, herança e composição, entre outros.

# Integrantes
Caio César Oliveira Cândido - 116215

Fernando César Pereira Reis - 116212

Thales Barcelos de Castro - 116229

# História

Em um antigo reino, existia uma coroa mágica conhecida como a Coroa do Equilibrio. Essa coroa não era apenas um símbolo de poder, mas também uma relíquia que mantinha a ordem e a paz no reino. No entanto, durante uma invasão de criaturas sombrias, a coroa foi roubada e escondida em um lugar amaldiçoado: o Corredor das Almas Perdidas. Sua missao é atravessar este corredor e recuperar a coroa para que a harmônia do reino volte ao normal!

![printJogo1](https://github.com/user-attachments/assets/4406c5f0-c23a-44ab-a2ec-005b6f7be094)

![printJogo2](https://github.com/user-attachments/assets/f37ca1d7-ee55-4ed6-a314-9e12da194293)

![image](https://github.com/user-attachments/assets/3947ce74-bb08-4095-a889-484cbf15531a)

# Tutorial de Execução

Instalar a biblioteca SFML no Linux:

1- Abra o terminal e use o seguinte comando para atualizar o gerenciador de pacotes apt:

![Captura de tela 2025-01-29 203937](https://github.com/user-attachments/assets/74e9e938-7f86-4eea-92ff-1a4b4d014f37)

2- Digite o seguinte comando para instalar a biblioteca:

![Captura de tela 2025-01-29 204138](https://github.com/user-attachments/assets/de0b254a-b72b-43f9-a602-6e4bcd52b6e2)

3- Para instalar componentes específicos da SFML:
![Captura de tela 2025-01-29 204522](https://github.com/user-attachments/assets/06fbe0a1-61a8-4e1b-b90e-9fa33bf1fcd9)

Após esses passos a instalação será concluída.

4- Para compilar basta usar o comando "make" no makefile criado.

5- Para executar basta escrever "main" no terminal.

Após isso o jogo o programa irá rodar normalmente.










# Algumas Observações

- Dependendo da configuração de cada computador, pode ser que o jogo fique um pouco mais pesado e a velocidade do jogador principal, tanto andando quanto pulando, se altere. Nesse caso, é recomendável que se altere a velocidade do mesmo (ou diminua caso necessario) para uma melhor experiencia. Para isso, basta alterar os defines em: Jogador.h (#define VELOCIDADE_JOGADOR_X <*coloque uma velocidade adequada*> e #define TAMANHO_PULO <*coloque o tamanho do pulo adequado*>) e em Personagem.h (#define GRAVIDADE <*altera a gravidade de acordo com a movimentacao de pulo do jogador, aumente se ele estiver muito tempo no ar, ou dimua se ele nao esta pulando corretamente*>)

# LINKS
- Sprites utilizados:

    https://itch.io/
  
- Materiais de apoio:
  
    https://www.sfml-dev.org/
  
    https://pt.wikipedia.org/wiki/SFML    
  


