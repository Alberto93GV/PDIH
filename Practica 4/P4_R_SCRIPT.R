# Cargamos las librerias
library(tuneR)
library(seewave)
library(audio)

# Indicamos el directorio donde se encuentran los sonidos
setwd("C:/Users/Alberto/Desktop/PDIH/PRACTICAS/P4/S6-sounds")

# Indicamos el directorio del reproductor de windows
# ERROR -> setWavPlayer("C:/Program Files/Windows Media Player/wmplayer.exe")
system(paste('"C:/Program Files/Window Media Player/wmplayer.exe"' , 'mysong.wav'))

# Cargamos y reproducimos
hola <- readWave('hola.wav')
hola
listen(hola)

perro <- readWave('perro.wav')
perro
listen(perro)

intro20th <- readMP3('intro20th.mp3')
intro20th
listen(intro20th)

# Forma de onda de 'hola.wav'
plot(extractWave(hola, from=1, to=11809))

# Forma de onda de 'perro.wav'
plot(extractWave(perro, from=1, to=159732))

# Forma de onda de 'intro20th.mp3'
plot(extractWave(intro20th, from=1, to=1110528))

# Cabeceras (info) de los sonidos
str(hola)
str(perro)
str(intro20th)

# Union de sonidos
union <- pastew(hola,perro,output="Wave")
union
listen(union)

# Forma de onda de 'union.wav'
plot(extractWave(union, from=1, to=171541))

# Eliminar frecuencias por debajo de los 3000Hz
f <- union@samp.rate
resultado <- bwfilter(union, f=f, channel=1, n=1, from=1, to=3000, bandpass=TRUE, output="Wave")
listen(resultado,f=f)

# Guardar la edicion anterior en disco en formato WAV
writeWave(resultado, file.path("mezcla.wav") )

# Cargar audio, aplicarle eco, darle la vuelta a dicho sonido y almacenarlo en disco
oveja <- readWave('oveja.wav')
oveja
listen(oveja)
f<-oveja@samp.rate
eco_oveja <- echo(oveja, f=f, amp=c(0.8,0.4,0.2), delay=c(1,2,3), output="Wave")
listen(eco_oveja)
oveja_del_reves <- revw(eco_oveja, output="Wave")
writeWave(oveja_del_reves, "oveja_del_reves.wav")
listen(oveja_del_reves)
