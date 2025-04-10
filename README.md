# 📘 Projeto: Philosophers

## 🧠 Objetivo
O projeto Philosophers simula o clássico problema da computação concorrente conhecido como "Dining Philosophers Problem", proposto por Edsger Dijkstra. O objetivo é implementar uma solução concorrente utilizando threads e mutexes em C para sincronizar o comportamento de filósofos que pensam, comem e dormem, evitando condições de corrida, deadlocks e fome (starvation).


## 🗂️ Estrutura de Arquivos
1. `philo.h`: Header com declarações de structs, enums, includes e funções.

2. `main.c`: Função principal e tratamento de argumentos.

3. `init.c`: Inicialização da mesa e filósofos.

4. `utils.c`: Funções auxiliares como ft_atol, print_message, clean, etc.

5. `monitor.c`: Monitoramento de morte dos filósofos e fim da simulação.

6. `routine.c`: Lógica da rotina dos filósofos.

7. `safe_functions.c`: Manipulação segura de mutexes.

8. `threads.c`: Criação e junção das threads.

## 🧩 Conceitos Utilizados
- `Threads`: Cada filósofo é uma thread (pthread).

- `Mutex`: Usado para proteger o acesso aos garfos e variáveis críticas.

- `Monitoramento`: Uma thread principal (monitor) verifica se algum filósofo morreu ou se todos completaram as refeições.

- `Sincronização`: Implementada com travamento ordenado dos mutexes para evitar deadlocks.

## 🧪 Funcionamento

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
```
- `number_of_philos`: Número de filósofos.

- `time_to_die`: Tempo máximo sem comer antes de morrer.

- `time_to_eat`: Tempo gasto comendo.

- `time_to_sleep`: Tempo dormindo.

- `number_of_times_each_philo_must_eat` (opcional): Se fornecido, simulação termina quando todos os filósofos comerem esse número de vezes.

## 🔄 Ciclo de Vida dos Filósofos
1. <strong>Pensar</strong>

2. <strong>Pegar garfos (com mutex)</strong>

3. <strong>Comer</strong>

4. <strong>Largar garfos</strong>

5. <strong>Dormir</strong>

6. <strong>Volta a pensar...</strong>

Cada ação é registrada com um `print_message` que exibe o ID do filósofo, timestamp relativo ao início, e a ação executada.

## 🔒 Segurança com Mutexes
Para evitar race conditions e garantir consistência:

- Todos os acessos e modificações em variáveis compartilhadas são protegidos com `pthread_mutex_lock` e `pthread_mutex_unlock`.

- Mutexes são encapsulados na função `safe_mutex`, que inclui tratamento de erros robusto via `handle_mutex_errors`.

## ⚠️ Casos Especiais
<strong>Um único filósofo</strong>: Pega um garfo e morre por não conseguir o segundo.

<strong>Argumentos inválidos</strong>: Detectados e tratados com mensagens de erro.

<strong>Simulação infinita</strong>: Caso `nbr_meals` não seja especificado.

## 🧹 Gerenciamento de Recursos
Ao fim da execução:

Todas as threads são encerradas com `pthread_join`.

Todos os mutexes são destruídos com `pthread_mutex_destroy`.

Memória alocada com `malloc` é liberada com `free`.

## 🧪 Exemplo de Execução
```bash
./philo 5 800 200 200 5
```
Neste exemplo:

- 5 filósofos

- 800ms antes de morrer sem comer

- 200ms comendo

- 200ms dormindo

Cada filósofo deve comer 5 vezes antes de a simulação terminar

## 📎 Conclusão
Esse projeto mostra a aplicação prática de concorrência em C, utilizando pthreads e sistemas de sincronização como mutexes. Ele representa um estudo importante para entender como lidar com problemas clássicos de concorrência, além de promover boas práticas de engenharia de software, como encapsulamento, modularização e tratamento de erros.