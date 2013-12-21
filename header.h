#define PEON_NEGRO      +2
#define PEON_BLANCO     -2
#define TORRE_NEGRO     +3
#define TORRE_BLANCO    -3
#define CABALLO_NEGRO   +4
#define CABALLO_BLANCO  -4
#define ALFIL_NEGRO     +5
#define ALFIL_BLANCO    -5
#define DAMA_NEGRO      +6
#define DAMA_BLANCO     -6
#define REY_NEGRO       +7
#define REY_BLANCO      -7
#define VACIA           0
#define INVALIDA        -1
#define jugada_normal   0
#define enroque_corto   1
#define enroque_largo   2
#define PROMOCION_D     3
#define PROMOCION_T     4
#define PROMOCION_C     5
#define PROMOCION_A     6
#define EMPTY           0
#define BLANCO          1
#define NEGRO           2
class mov{
    public:
        mov();
        mov(int desde_xx,int desde_yy, int hacia_xx,int hacia_yy, int tipoo);
        mov(char*);
        ~mov();
        void leer();
        bool escribir(char*);
        bool escribir(int ,int , int ,int , int);
        int leer_desde_x();
        int leer_desde_y();
        int leer_hacia_x();
        int leer_hacia_y();
        int leer_tipo();
    private:
        int desde_x;
        int desde_y;
        int hacia_x;
        int hacia_y;
        int tipo;
};
void xboard();
bool read(char*);
class tablero{
    public:
        tablero();
        ~tablero();
        void retroceder();
        void nueva_partida();
        void leer();
        bool mover(mov);
        int leer_tablero(int,int);
        int leer_turno();
        void xboard_edit();
        void print_registro();
    private:
        mov registro[512];
        int tablero_string[12][12];
        int turno;
        int index;
};
