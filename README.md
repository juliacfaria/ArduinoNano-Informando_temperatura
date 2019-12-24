<h1>Desenvolvendo Sistemas Internet das Coisas com Arduino</h1>
Projeto BIC-Júnior realizado em 2017/2018<br>
![4](https://user-images.githubusercontent.com/42352103/71386566-81893e00-25cd-11ea-9572-db1d045a714a.PNG)
<h3>Motivação</h3>
O projeto baseou-se na necessidade da checagem da variação da temperatura em diversas áreas de trabalho e de pesquisa. Assim, teve como objetivo facilitar tal processo, por meio do desenvolvimento de um equipamento, que visa possibilitar que aquele que o utilize possa checar a temperatura online e em tempo real.
<h3>Materiais Necessários</h3>
<ul>
  <li> Arduino Nano, microcontrolador Atmel ATmega328	</li>
  <li>Display LCD 16x2</li>
  <li>Sensor 	de temperatura à prova d’água DS18B20	</li>
  <li>Placa de rede Arduino Ethernet Shield W5100	</li>
  <li>Cabo USB</li>
  <li>Cabo par trançado </li>
  <li>Jumpers	</li>
  <li>Protoboard</li>
  <li>Computador com acesso à internet, porta USB e que possua a IDE do Arduino</li>
  <li>Roteador</li>
 </ul>
 <h3>Metodologia</h3>
 Em relação ao hardware, todos os componentes foram ligados de forma direta ou indiretamente ao Arduino. O Arduino foi ligado pelos seus pinos à placa de rede e à protoboard. Por meio da protoboard, ele foi ligado ao display e ao sensor de temperatura, assim como indicado pela figura 1. Todas as ligações eletrônicas foram baseadas nos datasheets dos componentes e ocorreram por meio de jumpers.<br>
 ![2](https://user-images.githubusercontent.com/42352103/71386403-797cce80-25cc-11ea-9748-bc859e25cba9.PNG)<br>
 O sensor de temperatura foi responsável por medir a temperatura do local em que estiver e passá-las para o Arduino. Já o display LCD, mostra as temperaturas medidas pelo sensor na tela do equipamento. A placa de rede, realiza a conexão com a internet por meio de um cabo par trançado ligado da placa a um roteador. A conexão à internet é necessária para disponibilizar, em um site, as temperaturas medidas. <br>
 O Arduino foi a base do equipamento montado principalmente por ter relação com um ambiente de programação. Essa IDE comunica-se diretamente com o Arduino por meio de um cabo USB e envia as informações a respeito do que deve ser realizado pela placa.<br>
 O software foi desenvolvido na IDE do Arduino. As funcionalidades de cada componente foi definida no código e, posteriormente foram relacionadas de forma que todas funcionassem a partir de um único comando.<br>
 As informações da temperatura do ambiente são enviadas,a partir da conexão com a internet, à plataforma do ThingSpeak. Essa plataforma é responsável pelo desenvolvimento de gráficos com as informações enviadas de forma a facilitar a compreensão de tais dados.<br>
 O gráfico do ThingSpeak  foi disponibilizado em um site desenvolvido em HTML. Esse site é voltado para que o usuário verifique as informações da variação da temperatura do local em que o aparelho desenvolvido se encontra.<br>
 ![3](https://user-images.githubusercontent.com/42352103/71386459-bd6fd380-25cc-11ea-8e8e-68517635cbb4.PNG)<br>
 A ligação entre os componentes está evidenciada no Untitled Sketch.fzz<br>
 ![fzz](https://user-images.githubusercontent.com/42352103/71386497-117ab800-25cd-11ea-8b3c-716e8e5f5c5a.PNG)<br>
 <h5>O código do projeto está disponível no arquivo Sensor1.ino</h5>
