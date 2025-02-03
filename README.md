# EmbarcaTech Tarefa Aula Sincrona 27/01/2025


<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=A6A6A6&height=120&section=header"/>
<h1 align="center">Embarcatec | Tarefa Aula Sincrona 27/01/2025</h1>

<div align="center">  
  <img width=40% src="http://img.shields.io/static/v1?label=STATUS&message=FINALIZADO&color=A6A6A6&style=for-the-badge"/>
</div>

## Objetivo do Projeto

Projeto para Placa Bitdoglab (Raspberry Pico W) de um contador que exibe na matriz WS2812, números de 0 a 9, e os incrementa cada vez que o botão A da placa é acionado e descrementa sempre que o botão B da placa é acionado. Uso do debounce implementado para os botões.


## 🗒️ Lista de requisitos

- Cabo USB
- Placa Bitdoglab ou os itens abaixo:
    - 2 Push buttons;
    - Protoboard;
    - Fios e jumpers; 
    - 1 led vermelho;
    - 1 Resistor 1kΩ;
    - Microcontrolador Raspberry Pi Pico W; 
    - Matriz de LEDs Coloridos (LED-RGB 5x5 WS2812);

## 🛠 Tecnologias

1. **Git e Github**;
2. **VScode**;
3. **Linguagem C**;
4. **Extensões no VScode do Raspberry Pi Pico Project e CMake**

## 💻 Instruções para Importar, Compilar e Rodar o Código Localmente

Siga os passos abaixo para clonar o repositório, importar no VS Code usando a extensão do **Raspberry Pi Pico Project**, compilar e executar o código.

1. **Clone o repositório para sua máquina local**  
   Abra o terminal e execute os comandos abaixo:
   ```bash
   git clone https://github.com/alexsami-lopes/EmbarcaTech-Tarefa-Aula-Sincrona-27-01-2025.git
   cd EmbarcaTech-Tarefa-Aula-Sincrona-27-01-2025

2. **Abra o VS Code e instale a extensão "Raspberry Pi Pico Project" (caso não já a tenha instalada)**
 - No VS Code, vá até "Extensões" (Ctrl+Shift+X)
 - Pesquise por "Raspberry Pi Pico Project"
 - Instale a extensão oficial

3. **Importe o projeto no VS Code**
 - No VS Code, na barra lateral do lado esquerdo clique em "Raspberry Pi Pico Project" <img src="images/icon_raspberry_pico_project.png" width="25px">
 - No menu que aparecer clique em <img src="images/icon_import_project.png" height="25px">
 - Clicando em "Change" escolha a pasta clonada do repositório
 - Escolha a versão do SDK 2.1.0
 - Clique em "Import"


    <img src="images/icon_import_project_settings.png" width="500px">


4. **Compile o projeto**
 - Com o projeto aberto no VS Code, pressione <img src="images/icon_compile.png" height="25px">
 - Aguarde a finalização do processo de build

5. **Rode o código no Raspberry Pi Pico**
 - Conecte o Raspberry Pi Pico ao PC segurando o botão "BOOTSEL".
 - Arraste e solte o arquivo `.uf2`, localizado dentro da pasta "build" do seu projeto, gerado na unidade USB montada.
 - O código será carregado automaticamente e o Pico será reiniciado.
 - Caso tenha instalado o driver com o Zadig clique em "Run" ao lado do botão <img src="images/icon_compile.png" height="25px">


## 🔧 Funcionalidades Implementadas:

1. O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo.
2. O botão A incrementa o número exibido na matriz de LEDs cada vez que for pressionado.
3. O botão B decrementa o número exibido na matriz de LEDs cada vez que for pressionado.
4. Os LEDs WS2812 foram ser usados para criar efeitos visuais representando números de 0 a 9.
• Formatação fixa: Cada número é exibido na matriz em um formato fixo, como caracteres em estilo digital (ex.: segmentos iluminados que formem o número).

## 💻 Desenvolvedor
 
<table>
  <tr>

<td align="center"><img style="" src="https://avatars.githubusercontent.com/u/103523809?v=4" width="100px;" alt=""/><br /><sub><b> Alexsami Lopes </b></sub></a><br />👨‍💻</a></td>

  </tr>
</table>


## 🎥 Demonstração no Wokwi: 

<div align="center">
  <figure>  
    <img src="images/Demo_Wokwi.png" width="500px">
    
<figcaption>

**Figura 1** - Demo do Projeto no Wokwi.com - Acessível em: https://wokwi.com/projects/421810650360925185
    </figcaption>
  </figure>
</div>


## 🎥 Demonstração na Placa (Video): 

<div align="center">
  <a href="https://youtu.be/csX0XGo6aso" target="_blank">
    <img src="images/Demo_Placa_Video.png" width="500px">
  </a>
</div>
