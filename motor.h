#define REY             10000
#define DAMA            800
#define TORRE           450
#define ALFIL           325
#define CABALLO         300
#define PEON            100
//RECORDATORIO: LAS NEGRAS BUSCAN EL MAYOR VALOR DE LA FUNCION EVALUAR Y LAS BLANCAS EL MENOR
void generar_jugadas(tablero,mov*);
//mov random(tablero,mov*);
mov random(tablero,mov*,int);
class posibles{
    public:
        posibles();
        ~posibles();
        void addnew(mov,int,int,int,int);
        mov leer_mejor();
        void leer();
    private:
        mov mejores_movimientos[201][7];
        int valores_mejores_movimientos[201];
        int mejor_movimiento;
        int cont_mejores_movimientos;
};
void mejor_jugada(tablero, posibles*, int, int, int);
//mov mejor_jugada(tablero);
mov pensar(tablero);
bool come_rey(tablero);
bool jaque(tablero);
int evaluar(tablero);
