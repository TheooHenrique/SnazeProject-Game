# Identificação Pessoal

Preencha os dados abaixo para identificar a autoria do trabalho.

- Nome: *<Theo Henrique da Silva Borges>*
- Email: *<theo123b@gmail.com>*
- Turma: *<Programação 1>*

- Nome: *<Haniel Lucas Machado Rocha>*
- Email: *<hani.lucas70@gmail.com>*
- Turma: *<Programação 1>*

# Introduction
This project aims to simulate the famous "snake game," but with two twists: (1) the snake is trapped in a maze; and (2) it must find the food on its own.

Below is the manual with all the options the user can enter in the terminal to view the simulation however they wish.

```
--help Print this help text

--fps <num> Number of frames (board) presented per second. Default = 10.

--lives <num> Number of lives the snake shall have. Default = 5.

--food <num> Number of food pellets for the entire simulation. Default = 10.

--playertype <type> Type of snake intelligence: random, backtracking. Default = Random (NOT IMPLEMENTED)
```    
# Member Contribution

## Theo
Created the diagrams, classes, various functions, the snake's walk, reading the phase files and validating the arguments.

## Haniel
Created the functions for food generation, snake growth, scoring and lives system, and maze rendering.

# Compiling & Running

To compile this code, we are using g++ compiler. To compile, use this code in root directory of the project:

```
g++ -o snaze source/dictionaries.cpp source/level.cpp source/main.cpp source/player.cpp source/positiondirection.cpp source/reader.cpp source/simulation.cpp source/snake.cpp 
```
To run the `snaze` executable created, run this code

```
./snaze <the commands described in the Introduction (optional)>
```

# Difficulties

## States management:
We did the state diagram before the development of the code, altough, it still difficult to manage all the states. We had special problems to the configure the "post mortem" of the snake and manage when she will still alive (if she still have lives).

## Colision logic:
This was very hard to think. Create a logic to check if the snake is at a prision was very hard to do, due to it's body. As a head, it was easy, but when we implemented the body, we had to remake this logic several times. The difficult to check if the snake will hit is related to the next difficult.

## Virtual snake logic:
This is VERY confusing! The solution of create a simulation snake to search the food is a good solution, but is very confusing to know where to use the real snake or the virtual snake.

## Random search logic: 
At first, we tought: "Oh, a dumb snake check if there is something in front of her, and if there is not, go ahead". But this logic had a problem: If the food is no in a wall, the snake will never get it! So, we had to rework ALL the RANDOM_SEARCH state.

# Indique quais itens da avaliação foram realizados

- [V] Valida corretamente arquivo de entrada (20 pontos)

- [V] Simulador apenas sugere direções randômicas para cobra (10 pontos)
OU
- [ ] Simulador direciona a cobra corretamente para a comida (50 pontos)

- [V] Apresentar e manipula corretamente os estados da simulação (30 pontos)

- [ ] **Extra**: simulação gera o menor caminho
- [ ] **Extra**: 

--------
&copy; DIMAp/UFRN 2021.
