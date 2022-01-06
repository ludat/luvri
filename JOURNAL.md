# VERSION 0.94

## 30/10/2012

ahora el motor ya sabe que esta bueno promocionar (siempre promociona reina no veo porque promocionar otra cosa) 
resuelto el problema del crash estaba en la linea:

```C
int i = rand() % indice_mejoresjugadas[cont_mejoresjugadas-1];
```

el problema era que `indice_mejoresjugadas[cont_mejoresjugadas-1]`; ocacionalmente valia cero y crasheaba por division por cero

## 29/10/2012

todavia mas inteligente ahora sabe promocionar (no sabe que es algo bueno pero puede hacerlo) y me parece que ya esta arreglado
el problema del random ahora si es random pero despues de jugar contra si mismo el motor crashea no se porque...
la parte que crashea esta en el random (?(? investigar en internet

## 27/10/2012

el motor es un poquito mas inteligente(ahora siempre trata de comer piezas) si tiene para comer dama, peon o nada siempre siempre
siempre elige la dama... todavia falta aplicarle profundidad, si puede comer solo un peon sacrificando la dama lo hace sin pestañar O.O -.- O.O
encontre un nuevo bug... al principio si moves un peon a la ultima linea en winboard se promociona y come la pieza del contrario ahora lo prueba en del modo debug

## 26/10/2012

lindo bug en enroque con xboard arreglado e implementada la funcion tablero::retroceder() para volver atras una jugada (no sirve
demasiado contra la compu xD) GOBI GATO HACE LA FUNCION EVALUAR!

## 23/10/2012

el enroque ya funciona (el motor mueve el rey como para enrocar y no mada O-O hay que ver q en la casilla e1 este el rey)

## 21/10/2012

me parece que juega todo legal y no se buguea hasta el fin del juego cuando si le sacas todas las piezas(solo en winboard en
arena tenes que hacer jaque para hacerlo y no se puede)crashea en arena se puede escribir el comando show en la pestaña
engine->log window->commands o algo asi para ver como se imagina el motor que esta el tablero

Todavia falta resolver problemas con el enroque y el jaque. Ademas hay que crear una funcion tablero::retractarse() para
volver uno dos movimientos atras.
