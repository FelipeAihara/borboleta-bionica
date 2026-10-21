# Borboleta Biônica (RC Bionic Butterfly)

Projeto de uma borboleta biônica controlada via rádio (RC), com batimento de asas acionado por 2 servos e controlado por um Arduino Pro Micro. O firmware lê os canais do receptor ELRS (protocolo nativo **CRSF**, via UART de hardware) e gera o movimento de batida das asas em onda senoidal, além de modos de "pousar" (perching) e "planar" (glide).

Baseado no projeto S-DiY 2 Servo Flap RC Bionic Butterfly.

## Estrutura do projeto

```
src/
  borboleta_bionica.ino     # Firmware principal
testes/
  teste_servo.ino           # Sketch de teste dos servos
  teste_receptor_elrs.ino   # Sketch de teste do receptor ELRS
```

## Funcionamento

- O receptor ELRS envia os canais via protocolo nativo **CRSF**, na porta serial de hardware `Serial1` do Arduino Pro Micro (RX1 = pino 0, TX1 = pino 1).
- Dois servos (esquerdo e direito) são controlados nos pinos 4 e 5.
- O canal de throttle controla a velocidade do batimento das asas (onda senoidal).
- Switches/canais auxiliares permitem alternar entre os modos **batimento (sine)**, **planeio (glide)** e **pousada (perch)**, além de trim de direção/profundidade e um LED indicador (pino 6).
- Em caso de perda de sinal (failsafe), as asas retornam suavemente à posição central.

## Materiais necessários

- [ ] 2x Fibra de carbono 1.0mm — [link](https://pt.aliexpress.com/item/1005005928525467.html?spm=a2g0o.order_list.order_list_main.273.5186caa4bKIPHd&gatewayAdapt=glo2bra)
- [ ] Fibra de carbono 1.5mm — [link](https://pt.aliexpress.com/item/1005005928525467.html?spm=a2g0o.order_list.order_list_main.267.5186caa4bKIPHd&gatewayAdapt=glo2bra)
- [ ] 2x Servo PTK 7465W MG 9g — [link](https://pt.aliexpress.com/item/1005007811142605.html?spm=a2g0o.order_list.order_list_main.167.5186caa4bKIPHd&gatewayAdapt=glo2bra)
- [ ] Bateria Lipo 2S 350mAh — [link](https://pt.aliexpress.com/item/1005012768253482.html?spm=a2g0o.order_list.order_list_main.339.5186caa4bKIPHd&gatewayAdapt=glo2bra)
- [ ] Receptor ELRS — [link](https://pt.aliexpress.com/item/1005009645506956.html?spm=a2g0o.order_list.order_list_main.89.5186caa4bKIPHd&gatewayAdapt=glo2bra)

## Dependências (Arduino)

- Biblioteca [`Servo`](https://www.arduino.cc/reference/en/libraries/servo/)
- Biblioteca [`AlfredoCRSF`](https://github.com/AlfredoSystems/AlfredoCRSF) (leitura do protocolo CRSF do receptor ELRS)

## Como usar

1. Monte a estrutura das asas com as fibras de carbono.
2. Instale os dois servos e conecte-os aos pinos 4 (esquerdo) e 5 (direito) do Arduino.
3. Conecte o receptor ELRS à porta serial de hardware do Pro Micro: TX do receptor → RX1 (pino 0), e opcionalmente RX do receptor → TX1 (pino 1) para telemetria. Alimente com a bateria Lipo 2S. **Atenção:** receptores ELRS operam em 3.3V — verifique a compatibilidade de nível lógico do seu Pro Micro.
4. Instale as bibliotecas `Servo` e `AlfredoCRSF` na IDE do Arduino.
5. Faça upload do sketch `src/borboleta_bionica.ino` para a placa.
6. Use os sketches em `testes/` para validar individualmente o receptor e os servos antes de rodar o firmware completo.
