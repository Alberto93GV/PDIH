#include <stdio.h>
#include <dos.h>

//////////////////////////////////////////////////////
void gotoXY(int f, int c){
	union REGS inregs, outregs;
	inregs.h.ah = 2;
	inregs.h.dh = f; // Numero de fila
	inregs.h.dl = c; // Numero de columna
	inregs.h.bh = 0; // Numero de pagina

	int86(0x10, &inregs, &outregs);
}

//////////////////////////////////////////////////////
void setTipoCursor(int tipo){
	union REGS inregs, outregs;
	inregs.h.ah = 1;

	switch(tipo){
		case 0: // Invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: // Normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: // Grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}

	int86(0x10, &inregs, &outregs);
}


//////////////////////////////////////////////////////
void setModoGrafico(int modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0;

	switch(modo){
		case 1: // 320x200 - 4 colores
			inregs.h.al = 0x04; break;
		case 2: // 320x200 - 4 colores
			inregs.h.al = 0x05; break;
		case 3: // 640x200 - 2 colores
			inregs.h.al = 0x06; break;
		case 4: // 320x200 - 16 colores
			inregs.h.al = 0x0D; break;
		case 5: // 640x200 - 16 colores
			inregs.h.al = 0x0E; break;
		case 6: // 640x350 - 2 colores
			inregs.h.al = 0x0F; break;
		case 7: // 640x480 - 16 colores
			inregs.h.al = 0x12; break;
		case 8: // 320x200 - 256 colores
			inregs.h.al = 0x13; break;
	}

	int86(0x10, &inregs, &outregs);
}


//////////////////////////////////////////////////////
void getModoVideoActual(){
	union REGS inregs, outregs;

	inregs.h.ah = 0xF;
	int86(0x10, &inregs, &outregs);

	printf("\n El modo de video actual es: %x\n", outregs.h.al);
}


//////////////////////////////
// 	VAR. GLOBALES
int front_color, back_color;
//////////////////////////////////////////////////////
void setColor(int fc, int bc){
	front_color = fc;
	back_color = bc;
}
//////////////////////////////////////////////////////
void caracterEnColor(const char c){
	union REGS inregs, outregs;

	int color = back_color << 4 | front_color;

	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = color;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;

	int86(0x10, &inregs, &outregs);
}


//////////////////////////////////////////////////////
void limpiarPantalla(){
	union REGS inregs, outregs;
	char rc = '\n';
	int i = 0;

	inregs.h.ah = 2;
	inregs.h.dl = rc;
	
	while(i<=30){ // 30 retornos de carro
		int86(0x21, &inregs, &outregs);
		i++;
	}
}


//////////////////////////////////////////////////////
void leerMostrarCaracter(){
	union REGS inregs1, outregs1;
	union REGS inregs2, outregs2;

	// Leer caracter pulsado
	inregs1.h.ah = 1;
	int86(0x21, &inregs1, &outregs1);

	// Mostrar caracter por pantalla
	inregs2.h.ah = 2;
	inregs2.h.dl = outregs1.h.al; // Le pasamos de 'outregs1' el cod. ASCII del caracter pulsado
	printf("\nLa tecla que acabas de pulsar es -> ");
	int86(0x21, &inregs2, &outregs2);
}



//////////////////////////////////////////////////////
// 					INT MAIN()
//////////////////////////////////////////////////////
int main(){
	
	/*
	gotoXY(20,20);

	setTipoCursor(2);

	setModoGrafico(1);

	getModoVideoActual();

	const char c = 'A';
	setColor(4,2);
	caracterEnColor(c);

	limpiarPantalla();

	leerMostrarCaracter();
	*/

	

	return 0;
}