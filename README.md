Projeto: Controle de LEDs com Interrupções e Debouncing
Descrição do Projeto
Este projeto foi desenvolvido para a placa de desenvolvimento BitDogLab e tem como objetivo demonstrar o uso de interrupções, debouncing via software, e controle de LEDs comuns e endereçáveis WS2812. O projeto combina hardware e software para criar uma aplicação funcional que responde a eventos de botões e controla uma matriz de LEDs.

Funcionalidades Implementadas
Piscar o LED Vermelho:

O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo, demonstrando o controle de LEDs comuns.
Incrementar Número com Botão A:

O botão A, conectado à GPIO 5, incrementa o número exibido na matriz de LEDs cada vez que é pressionado. O número varia de 0 a 9 e é exibido em um formato fixo na matriz de LEDs.
Decrementar Número com Botão B:

O botão B, conectado à GPIO 6, decrementa o número exibido na matriz de LEDs cada vez que é pressionado. O número varia de 0 a 9 e é exibido em um formato fixo na matriz de LEDs.
Exibição de Números na Matriz de LEDs:

A matriz 5x5 de LEDs endereçáveis WS2812, conectada à GPIO 7, exibe números de 0 a 9 em um formato fixo. Cada número é representado por um padrão de LEDs iluminados.
Componentes Utilizados
Placa de Desenvolvimento: BitDogLab
Matriz de LEDs: 5x5 LEDs endereçáveis WS2812
LED RGB: Pinos conectados às GPIOs 11, 12 e 13
Botões:
Botão A conectado à GPIO 5
Botão B conectado à GPIO 6
Botão J conectado à GPIO 22 (opcional)
Requisitos do Projeto
Uso de Interrupções:

Todas as funcionalidades relacionadas aos botões são implementadas utilizando rotinas de interrupção (IRQ).
Debouncing:

O tratamento do bouncing dos botões é implementado via software utilizando um tempo de debounce configurável.
Controle de LEDs:

O projeto inclui o uso de LEDs comuns e LEDs WS2812, demonstrando o domínio de diferentes tipos de controle.
Organização do Código:

O código está bem estruturado e comentado para facilitar o entendimento.
Instruções de Compilação e Execução

Compile o Projeto:

Siga as instruções específicas para compilar o projeto na sua IDE ou ambiente de desenvolvimento preferido.
Carregue o Código na Placa:

Conecte a placa BitDogLab ao seu computador e carregue o código compilado.
Execute o Projeto:

Após carregar o código, o projeto deve iniciar automaticamente. Verifique se o LED vermelho está piscando e teste os botões A e B para incrementar e decrementar o número exibido na matriz de LEDs.
Vídeo de Demonstração
Um vídeo de demonstração do projeto em funcionamento está disponível aqui: 
https://youtube.com/shorts/7X57HLwehyk?feature=share
