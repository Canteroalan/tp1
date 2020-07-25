**********************RESUMEN**************************

CALSE:

Cualquier sonido real tiene el tiempo de ataque, otro el sostenido y al final (cuando se apaga) el decaimiento. NO en todos los intrumentos es igual estos tiempos.


MIDI + SINTETIZADOR = WAVE (esto es lo que hay que hacer con el programa).


WAVE:
* Arhivo binario MUY sensillo. Se guarda el tramo creado (tramo_t) como enteros de 16bits (65k bits). Entonces el valor MAX de mi float, se ¨machee¨ con el 32767 y el MIN (-MAX) se ¨machee¨ con el -32768 (ESCALARLO).
* int16 vi[n];
  for(size_t i = 0; i < n; i++)
  	vi[i] = fi[i] * 2^31;
* Es escribir un encabezado y ESCUPIR muestras (que teniamos en float) en int16.


Se le tiene que pasar al programa un numerito que convierte el pulso del MIDI a segundos.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

ENUNCIADO:

La(A4) de la octava 4 tiene una frecuencia de 440Hz.

Formula para calcular las frecuencias:
Ej) A4 = 440Hz  ==> (440Hz) * 2 ^ (o + s / 12). Donde ¨o¨ es la octava y ¨s¨ es la cantidad de semitonos. 
Mismo semitono en distinta octava es el exponente o+0/12, y si es misma octava pero diferente semitono el exponente es 0+s/12.

MIDI:
* Cada CANAL tiene un instrumento asignado y es el mismo para todo el archivo.
* Pares INICIO-FINALIZADO de una nota en una pista.
* INICIO: ¨Nota Encendida¨ con velocidad distinto de 0.
* FINALIZADO: ¨Nota Apagada¨ o ¨Nota encendida¨ (con velocidad 0). 
* Es mas económico que una pista tenga solo el evento ¨Nota Encendida¨ (para INCIO y FINALIZADO).
* Intensidad de la nota = velocidad de ¨Nota Encendida¨.

WAVE:
* Tenemos que pasar las muestras almacenadas como flotantes a int16.


TRABAJO:
* Implementar solucion al tema de argumentos sin importar el orden en el cual el usuario pase a la hora de compilar el programa. Ademas si se ingresan dos veces el mismo valor se interpreta como 1 solo.
* Lee archivo MIDI de entrada.
* Muestrea los eventos del canal en el archivo de salida WAVE.
* El parámetro de ¨Pulsos por Segundo¨ es para pasar de Pulsos (de los eventos del MIDI) a Segundos.

SINTETIZADOR:
* Para realizar sintesis de una pista.
* Una nota tendra parametros de inicio, duracion, frecuencia e intensidad.
* Del ej2: tenemos la intensidad, la frecuencia de la nota. Ademas sabemos que la nota sonara desde t0 hasta t0 + d + td que es la duracion de la nota y tiempo de finalizacion.  
* Hay que multiplicar la f(t) del ej2 de cada nota por una de las 3 funciones (ataque, sostenido, decaimiento) dependiendo del valor de t.
* Ataque = ta - t0. fa(t - t0) entre t0 < t < t0 + ta.
* Sostenido = d - ta. fs(t - (t0 + ta)) entre t0 + ta < t < t0 + d.
* Decaimiento = td - d. fs(t0 + d) x fd(t -(t0 + d) entre t0 + d < t < t0 + d +td.
* Para otro t, 0.
* Es multiplicar la onda generada por tramo_crear_muestreo por m(t).
* Luego cada nota se puede sumarse a las ya generadas con tramo_extender.

FUNCIONES DE MODULACION
* No entendi bien si hay que hacer una funcion ¨modulacion¨ para cada funcion (cte, linear, ...).
* Tampoco entendi bien lo de ¨params[3]¨.
* Hay que usar punteros a funciones y diccionarios.

ARCHIVO DE SINTETIZADOR
* Archivo de texto plano.
* Cantidad de armonicos.
* Multiplicador e intensidad de cada armonico.
* 3 ultimas lineas. Cada una contiene el nombre de la funcion a utilizar y sus parametros. Primera = ataque, segunda = sostenido, tercera = decaimiento.
* Simplemente extrayendo valores numericos separados por espacios.
* Puede asumirse que la cantidad maxima de armonicos a procesar es un numero fijado en tiempo de compilacion. (???).

NOTAS:
* Los TDAs son cajitas cerradas. Tienen un unico proposito. Conocen un unico problema. Saben solo hacer eso. No conocen cual es el contexto del problema que van a resolver.
* MAL: TDA donde Alan asuma cosas que son responsabilidad de Barbara.
* MAL: Uso de TDA donde Barbara se meta en los detalles de la implementacion de Alan.
* Diseñar objetico de cada TDA y su invariante. Documentarlo.

REQUISITOS:
* Un TDA Nota.
* Un TDA que permita almacenar las notas de un (canal de un) MIDI.
* Un TDA Sintetizador.
* Un TDA que permita almacenar las muestras (tramo).
