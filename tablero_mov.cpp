#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "motor.h"

//Clases declaradas en este archivo: mov, tablero
//Funciones declaradas en este archivo:

mov::mov(int desde_xx,int desde_yy, int hacia_xx,int hacia_yy, int tipoo){
    desde_x = desde_xx;
    desde_y = desde_yy;
    hacia_x = hacia_xx;
    hacia_y = hacia_yy;
    tipo = tipoo;
};
mov::mov(){tipo = -1;}
mov::~mov(){};
bool mov::escribir(int desde_xx,int desde_yy, int hacia_xx,int hacia_yy, int tipoo){
    desde_x = desde_xx;
    desde_y = desde_yy;
    hacia_x = hacia_xx;
    hacia_y = hacia_yy;
    tipo = tipoo;
}
bool mov::escribir(char* s){
    if(!strcmp(s, "O-O")){
        desde_x = 0;
        desde_y = 0;
        hacia_x = 0;
        hacia_y = 0;
        tipo = enroque_corto;
        return true;
    }else{
        if(!strcmp(s, "O-O-O")){
            desde_x = 0;
            desde_y = 0;
            hacia_x = 0;
            hacia_y = 0;
            tipo = enroque_largo;
            return true;
        }else{
            if(s[4]='q' && s[4]!='\0'){
                if(s[0]>='a' && s[0]<='h'
                && s[1]>='1' && s[1]<='8'
                && s[2]>='a' && s[2]<='h'
                && s[3]>='1' && s[3]<='8'){
                    desde_x = toascii(s[0])-97+2;
                    desde_y = toascii(s[1])-49+2;
                    hacia_x = toascii(s[2])-97+2;
                    hacia_y = toascii(s[3])-49+2;
                    tipo=PROMOCION_D;
                    return true;
                }
            }
            if(s[4]='r' && s[4]!='\0'){
                if(s[0]>='a' && s[0]<='h'
                && s[1]>='1' && s[1]<='8'
                && s[2]>='a' && s[2]<='h'
                && s[3]>='1' && s[3]<='8'){
                    desde_x = toascii(s[0])-97+2;
                    desde_y = toascii(s[1])-49+2;
                    hacia_x = toascii(s[2])-97+2;
                    hacia_y = toascii(s[3])-49+2;
                    tipo=PROMOCION_T;
                    return true;
                }
            }
            if(s[4]='b' && s[4]!='\0'){
                if(s[0]>='a' && s[0]<='h'
                && s[1]>='1' && s[1]<='8'
                && s[2]>='a' && s[2]<='h'
                && s[3]>='1' && s[3]<='8'){
                    desde_x = toascii(s[0])-97+2;
                    desde_y = toascii(s[1])-49+2;
                    hacia_x = toascii(s[2])-97+2;
                    hacia_y = toascii(s[3])-49+2;
                    tipo=PROMOCION_A;
                    return true;
                }
            }
            if(s[4]='n' && s[4]!='\0'){
                if(s[0]>='a' && s[0]<='h'
                && s[1]>='1' && s[1]<='8'
                && s[2]>='a' && s[2]<='h'
                && s[3]>='1' && s[3]<='8'){
                    desde_x = toascii(s[0])-97+2;
                    desde_y = toascii(s[1])-49+2;
                    hacia_x = toascii(s[2])-97+2;
                    hacia_y = toascii(s[3])-49+2;
                    tipo=PROMOCION_C;
                    return true;
                }
            }
            if(s[0]==s[2] && s[1]==s[3]){
                return false;
            }
            if(s[0]>='a' && s[0]<='h'
            && s[1]>='1' && s[1]<='8'
            && s[2]>='a' && s[2]<='h'
            && s[3]>='1' && s[3]<='8'){
                desde_x = toascii(s[0])-97+2;
                desde_y = toascii(s[1])-49+2;
                hacia_x = toascii(s[2])-97+2;
                hacia_y = toascii(s[3])-49+2;
                tipo = jugada_normal;
                return true;
            }else{
                return false;
            }
        }
    }
}
void mov::leer(){
    if(tipo!=-1){
        //printf(" a) %c%c%c%c", desde_x+97-2, desde_y+49-2, hacia_x+97-2, hacia_y+49-2);
        //printf(" b) %d%d%d%d  (%c%d%c%d)", desde_x, desde_y, hacia_x, hacia_y, desde_x+97-2, desde_y-1, hacia_x+97-2, hacia_y-1);
        printf("%c%d%c%d", desde_x+97-2, desde_y-1, hacia_x+97-2, hacia_y-1);
    }else{
        printf("----");
    }
};
int mov::leer_desde_x(){
    return desde_x;
};
int mov::leer_desde_y(){
    return desde_y;
};
int mov::leer_hacia_x(){
    return hacia_x;
};
int mov::leer_hacia_y(){
    return hacia_y;
};
int mov::leer_tipo(){
    return tipo;
};
tablero::tablero(){};
tablero::~tablero(){};
void tablero::nueva_partida(){
/*
        tablero_string[0] ={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        tablero_string[1] ={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        tablero_string[2] ={-1,-1,-3,-4,-5, 0,-7, 0,-4,-3,-1,-1};
        tablero_string[3] ={-1,-1,-2,-2,-2, 0, 0,-2,-2,-2,-1,-1};
        tablero_string[4] ={-1,-1, 0, 0, 0,-2, 0, 0, 0, 0,-1,-1};
        tablero_string[5] ={-1,-1, 0, 0,+4, 0,-2, 0, 0, 0,-1,-1};
        tablero_string[6] ={-1,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1};
        tablero_string[7] ={-1,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1};
        tablero_string[8] ={-1,-1,+2,+2,+2,+2, 0,+2,+2,+2,-1,-1};
        tablero_string[9] ={-1,-1,+3, 0,+5,+6,+7,+5,+4,+3,-1,-1};
        tablero_string[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        tablero_string[11]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
*/
        tablero_string[0][0]=-1;
        tablero_string[0][1]=-1;
        tablero_string[0][2]=-1;
        tablero_string[0][3]=-1;
        tablero_string[0][4]=-1;
        tablero_string[0][5]=-1;
        tablero_string[0][6]=-1;
        tablero_string[0][7]=-1;
        tablero_string[0][8]=-1;
        tablero_string[0][9]=-1;
        tablero_string[0][10]=-1;
        tablero_string[0][11]=-1;
/////////////////////////////////////////////////////////////////////////////listo
        tablero_string[1][0]=-1;
        tablero_string[1][1]=-1;
        tablero_string[1][2]=-1;
        tablero_string[1][3]=-1;
        tablero_string[1][4]=-1;
        tablero_string[1][5]=-1;
        tablero_string[1][6]=-1;
        tablero_string[1][7]=-1;
        tablero_string[1][8]=-1;
        tablero_string[1][9]=-1;
        tablero_string[1][10]=-1;
        tablero_string[1][11]=-1;
/////////////////////////////////////////////////////////////////////////////listo
        tablero_string[2][0]=-1;
        tablero_string[2][1]=-1;
        tablero_string[2][2]=-3;
        tablero_string[2][3]=-4;
        tablero_string[2][4]=-5;
        tablero_string[2][5]=-6;
        tablero_string[2][6]=-7;
        tablero_string[2][7]=-5;
        tablero_string[2][8]=-4;
        tablero_string[2][9]=-3;
        tablero_string[2][10]=-1;
        tablero_string[2][11]=-1;
/////////////////////////////////////////////////////////////////////////////
        tablero_string[3][0]=-1;
        tablero_string[3][1]=-1;
        tablero_string[3][2]=-2;
        tablero_string[3][3]=-2;
        tablero_string[3][4]=-2;
        tablero_string[3][5]=-2;
        tablero_string[3][6]=-2;
        tablero_string[3][7]=-2;
        tablero_string[3][8]=-2;
        tablero_string[3][9]=-2;
        tablero_string[3][10]=-1;
        tablero_string[3][11]=-1;
/////////////////////////////////////////////////////////////////////////////
        tablero_string[4][0]=-1;
        tablero_string[4][1]=-1;
        tablero_string[4][2]= 0;
        tablero_string[4][3]= 0;
        tablero_string[4][4]= 0;
        tablero_string[4][5]= 0;
        tablero_string[4][6]= 0;
        tablero_string[4][7]= 0;
        tablero_string[4][8]= 0;
        tablero_string[4][9]= 0;
        tablero_string[4][10]=-1;
        tablero_string[4][11]=-1;
////////////////////////////////////////////////////////////////////////////
        tablero_string[5][0]=-1;
        tablero_string[5][1]=-1;
        tablero_string[5][2]= 0;
        tablero_string[5][3]= 0;
        tablero_string[5][4]= 0;
        tablero_string[5][5]= 0;
        tablero_string[5][6]= 0;
        tablero_string[5][7]= 0;
        tablero_string[5][8]= 0;
        tablero_string[5][9]= 0;
        tablero_string[5][10]=-1;
        tablero_string[5][11]=-1;
////////////////////////////////////////////////////////////////////////////
        tablero_string[6][0]=-1;
        tablero_string[6][1]=-1;
        tablero_string[6][2]= 0;
        tablero_string[6][3]= 0;
        tablero_string[6][4]= 0;
        tablero_string[6][5]= 0;
        tablero_string[6][6]= 0;
        tablero_string[6][7]= 0;
        tablero_string[6][8]= 0;
        tablero_string[6][9]= 0;
        tablero_string[6][10]=-1;
        tablero_string[6][11]=-1;
////////////////////////////////////////////////////////////////////////////
        tablero_string[7][0]=-1;
        tablero_string[7][1]=-1;
        tablero_string[7][2]= 0;
        tablero_string[7][3]= 0;
        tablero_string[7][4]= 0;
        tablero_string[7][5]= 0;
        tablero_string[7][6]= 0;
        tablero_string[7][7]= 0;
        tablero_string[7][8]= 0;
        tablero_string[7][9]= 0;
        tablero_string[7][10]=-1;
        tablero_string[7][11]=-1;
/////////////////////////////////////////////////////////////////////////////
        tablero_string[8][0]=-1;
        tablero_string[8][1]=-1;
        tablero_string[8][2]=+2;
        tablero_string[8][3]=+2;
        tablero_string[8][4]=+2;
        tablero_string[8][5]=+2;
        tablero_string[8][6]=+2;
        tablero_string[8][7]=+2;
        tablero_string[8][8]=+2;
        tablero_string[8][9]=+2;
        tablero_string[8][10]=-1;
        tablero_string[8][11]=-1;
////////////////////////////////////////////////////////////////////////////
        tablero_string[9][0]=-1;
        tablero_string[9][1]=-1;
        tablero_string[9][2]=+3;
        tablero_string[9][3]=+4;
        tablero_string[9][4]=+5;
        tablero_string[9][5]=+6;
        tablero_string[9][6]=+7;
        tablero_string[9][7]=+5;
        tablero_string[9][8]=+4;
        tablero_string[9][9]=+3;
        tablero_string[9][10]=-1;
        tablero_string[9][11]=-1;
/////////////////////////////////////////////////////////////////////////////
        tablero_string[10][0]=-1;
        tablero_string[10][1]=-1;
        tablero_string[10][2]=-1;
        tablero_string[10][3]=-1;
        tablero_string[10][4]=-1;
        tablero_string[10][5]=-1;
        tablero_string[10][6]=-1;
        tablero_string[10][7]=-1;
        tablero_string[10][8]=-1;
        tablero_string[10][9]=-1;
        tablero_string[10][10]=-1;
        tablero_string[10][11]=-1;
/////////////////////////////////////////////////////////////////////////////
        tablero_string[11][0]=-1;
        tablero_string[11][1]=-1;
        tablero_string[11][2]=-1;
        tablero_string[11][3]=-1;
        tablero_string[11][4]=-1;
        tablero_string[11][5]=-1;
        tablero_string[11][6]=-1;
        tablero_string[11][7]=-1;
        tablero_string[11][8]=-1;
        tablero_string[11][9]=-1;
        tablero_string[11][10]=-1;
        tablero_string[11][11]=-1;
/////////////////////////////////////////////////////////////////////////////
/*
        tablero_string[1] ={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        tablero_string[2] ={-1,-1,-3,-4,-5,-6,-7,-5,-4,-3,-1,-1};
        tablero_string[3] ={-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1};
        tablero_string[4] ={-1,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1};
        tablero_string[5] ={-1,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1};
        tablero_string[6] ={-1,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1};
        tablero_string[7] ={-1,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1};
        tablero_string[8] ={-1,-1,+2,+2,+2,+2,+2,+2,+2,+2,-1,-1};
        tablero_string[9] ={-1,-1,+3,+4,+5,+6,+7,+5,+4,+3,-1,-1};
        tablero_string[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        tablero_string[11]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        */
        turno = BLANCO;
        index = 0;
        for(int i=0;i<=511;i++){
            registro[i].escribir(0,0,0,0,-1);
        }
};
int tablero::leer_turno(){
    return turno;
};
void tablero::leer(){
/*
    for(int i=9;i>1;i--){
        printf("\n%d", i-1);
        for(int j=2;j<10;j++){
            if(tablero_string[i][j]== 0)printf(" .");
            if(tablero_string[i][j]== 2)printf(" p");
            if(tablero_string[i][j]==-2)printf(" P");
            if(tablero_string[i][j]== 3)printf(" t");
            if(tablero_string[i][j]==-3)printf(" T");
            if(tablero_string[i][j]== 4)printf(" c");
            if(tablero_string[i][j]==-4)printf(" C");
            if(tablero_string[i][j]== 5)printf(" a");
            if(tablero_string[i][j]==-5)printf(" A");
            if(tablero_string[i][j]== 6)printf(" d");
            if(tablero_string[i][j]==-6)printf(" D");
            if(tablero_string[i][j]== 7)printf(" r");
            if(tablero_string[i][j]==-7)printf(" R");
        };
    };
    printf(" \n ");
    for(int i=0;i<8;i++){
        printf(" %c",i+97);
    }*/
    for(int i=11;i>=0;i--){
        printf("\n");
        for(int j=0;j<12;j++){
            if(tablero_string[i][j]==-1)printf("-1");
            if(tablero_string[i][j]== 0)printf(" .");
            if(tablero_string[i][j]== 2)printf(" p");
            if(tablero_string[i][j]==-2)printf(" P");
            if(tablero_string[i][j]== 3)printf(" t");
            if(tablero_string[i][j]==-3)printf(" T");
            if(tablero_string[i][j]== 4)printf(" c");
            if(tablero_string[i][j]==-4)printf(" C");
            if(tablero_string[i][j]== 5)printf(" a");
            if(tablero_string[i][j]==-5)printf(" A");
            if(tablero_string[i][j]== 6)printf(" d");
            if(tablero_string[i][j]==-6)printf(" D");
            if(tablero_string[i][j]== 7)printf(" r");
            if(tablero_string[i][j]==-7)printf(" R");
        }
    }
    printf("\n");
}
void tablero::xboard_edit(){
    printf("#\n");
    printf("e\n");
    for(int i=9;i>1;i--){
        for(int j=2;j<10;j++){
            if(tablero_string[i][j]== 0)printf("x%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]==-2)printf("P%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]==-3)printf("R%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]==-4)printf("N%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]==-5)printf("B%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]==-6)printf("Q%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]==-7)printf("K%c%d", j +'a'-2, i -1);
        };
    };
    printf("c\n");
    for(int i=9;i>1;i--){
        for(int j=2;j<10;j++){
            if(tablero_string[i][j]== 0)printf("x%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]== 2)printf("P%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]== 3)printf("R%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]== 4)printf("N%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]== 5)printf("B%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]== 6)printf("Q%c%d", j +'a'-2, i -1);
            if(tablero_string[i][j]== 7)printf("K%c%d", j +'a'-2, i -1);
        }
    }
    printf(".\n");
}
bool tablero::mover(mov m){
        bool primera_comp = false;
        bool segunda_comp = false;
        int desde_x = m.leer_desde_x();
        int desde_y = m.leer_desde_y();
        int hacia_x = m.leer_hacia_x();
        int hacia_y = m.leer_hacia_y();
    if(m.leer_tipo()==jugada_normal){
        //printf("desde tablero[%d][%d] = %d\n",desde_x, desde_y, tablero_string[desde_y][desde_x] );
        //printf("hacia tablero[%d][%d] = %d\n",hacia_x, hacia_y, tablero_string[hacia_y][hacia_x] );
        if(turno==NEGRO){
            if(tablero_string[desde_y][desde_x] > 1){
                if(tablero_string[hacia_y][hacia_x] == 0){
                    primera_comp=true;
                }
                if(tablero_string[hacia_y][hacia_x] < -1){
                    primera_comp=true;
                }
            }
        }
        if(turno==BLANCO){
            if(tablero_string[desde_y][desde_x] < -1){
                if(tablero_string[hacia_y][hacia_x] == 0){
                    primera_comp=true;
                }
                if(tablero_string[hacia_y][hacia_x] > 1){
                    primera_comp=true;
                }
            }
        }
        if(primera_comp==true){
            if(turno==BLANCO){
                if(tablero_string[desde_y][desde_x]==-2){
                    if(desde_y==3 && desde_y==hacia_y-2 && tablero_string[hacia_y][hacia_x] == 0 && desde_x==hacia_x && tablero_string[hacia_y-1][hacia_x] == 0){
                        segunda_comp=true;
                    }else{
                        if(desde_y==hacia_y-1){
                            if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] > 1){
                                segunda_comp=true;
                            }
                            if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                                segunda_comp=true;
                            }
                            if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] > 1){
                                segunda_comp=true;
                            }
                        }
                    }
                }
                if(tablero_string[desde_y][desde_x]==-3){
                        if(desde_x==hacia_x || desde_y==hacia_y){
                            bool continuo = true;
                            if(desde_x==hacia_x){
                                if(desde_y>hacia_y){
                                    for(int i=hacia_y+1;i<desde_y;i++){
                                        if(tablero_string[i][hacia_x]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                                if(desde_y<hacia_y){
                                    for(int i=desde_y+1;i<hacia_y;i++){
                                        if(tablero_string[i][hacia_x]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                            };
                            if(desde_y==hacia_y){
                                if(desde_x>hacia_x){
                                    for(int i=hacia_x+1;i<desde_x;i++){
                                        if(tablero_string[hacia_y][i]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                                if(desde_x<hacia_x){
                                    for(int i=desde_x+1;i<hacia_x;i++){
                                        if(tablero_string[hacia_y][i]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                            };
                            if(continuo==true){
                                if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] > 1){
                                    segunda_comp=true;
                                };
                            };
                        };
                };
                if(tablero_string[desde_y][desde_x]==-4){
                        if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] > 1){
                            if(desde_x==hacia_x+1 || desde_x==hacia_x-1){
                                if(desde_y==hacia_y+2 || desde_y==hacia_y-2){
                                    segunda_comp=true;
                                };
                            };
                            if(desde_x==hacia_x+2 || desde_x==hacia_x-2){
                                if(desde_y==hacia_y+1 || desde_y==hacia_y-1){
                                    segunda_comp=true;
                                };
                            };
                        };
                };
                if(tablero_string[desde_y][desde_x]==-5){
                            if(abs(desde_x-hacia_x)==abs(desde_y-hacia_y)){
                                if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] > 1){
                                    bool continuo=true;
                                    if(desde_x>hacia_x && desde_y>hacia_y){
                                        for(int i=1;i<desde_x-hacia_x;i++){
                                            if(tablero_string[hacia_y+i][hacia_x+i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(desde_x>hacia_x && desde_y<hacia_y){
                                        for(int i=1;i<desde_x-hacia_x;i++){
                                            if(tablero_string[hacia_y-i][hacia_x+i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(desde_x<hacia_x && desde_y>hacia_y){
                                        for(int i=1;i<hacia_x-desde_x;i++){
                                            if(tablero_string[hacia_y+i][hacia_x-i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(desde_x<hacia_x && desde_y<hacia_y){
                                        for(int i=1;i<hacia_x-desde_x;i++){
                                            if(tablero_string[hacia_y-i][hacia_x-i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(continuo==true){
                                        segunda_comp=true;
                                    };
                                };
                            };
                };
                if(tablero_string[desde_y][desde_x]==-6){
                        if(desde_x==hacia_x || desde_y==hacia_y){
                            bool continuo = true;
                            if(desde_x==hacia_x){
                                if(desde_y>hacia_y){
                                    for(int i=hacia_y+1;i<desde_y;i++){
                                        if(tablero_string[i][hacia_x]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                                if(desde_y<hacia_y){
                                    for(int i=desde_y+1;i<hacia_y;i++){
                                        if(tablero_string[i][hacia_x]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                            };
                            if(desde_y==hacia_y){
                                if(desde_x>hacia_x){
                                    for(int i=hacia_x+1;i<desde_x;i++){
                                        if(tablero_string[hacia_y][i]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                                if(desde_x<hacia_x){
                                    for(int i=desde_x+1;i<hacia_x;i++){
                                        if(tablero_string[hacia_y][i]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                            };
                            if(continuo==true){
                                if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] > 1){
                                    segunda_comp=true;
                                };
                            };
                        };
                        if(abs(desde_x-hacia_x)==abs(desde_y-hacia_y)){
                            if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] > 1){
                                bool continuo=true;
                                if(desde_x>hacia_x && desde_y>hacia_y){
                                    for(int i=1;i<desde_x-hacia_x;i++){
                                        if(tablero_string[hacia_y+i][hacia_x+i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(desde_x>hacia_x && desde_y<hacia_y){
                                    for(int i=1;i<desde_x-hacia_x;i++){
                                        if(tablero_string[hacia_y-i][hacia_x+i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(desde_x<hacia_x && desde_y>hacia_y){
                                    for(int i=1;i<hacia_x-desde_x;i++){
                                        if(tablero_string[hacia_y+i][hacia_x-i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(desde_x<hacia_x && desde_y<hacia_y){
                                    for(int i=1;i<hacia_x-desde_x;i++){
                                        if(tablero_string[hacia_y-i][hacia_x-i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(continuo==true){
                                    segunda_comp=true;
                                };
                            };
                        };
                };
                if(tablero_string[desde_y][desde_x]==-7){
                    if(abs(desde_x-hacia_x)<=1){
                        if(abs(desde_y-hacia_y)<=1){
                            segunda_comp=true;
                        }
                    }
                    if(desde_y == 2 && desde_x == 6 && hacia_y == 2 && hacia_x == 8){
                        if(tablero_string[2][6]==-7 && tablero_string[2][7]==0 && tablero_string[2][8]==0 && tablero_string[2][9]==-3){
                            tablero_string[2][6] = 0;
                            tablero_string[2][7] =-3;
                            tablero_string[2][8] =-7;
                            tablero_string[2][9] = 0;
                            turno=NEGRO;
                            return true;
                        }else{
                            return false;
                        }
                    }
                    if(desde_y == 2 && desde_x == 6 && hacia_y == 2 && hacia_x == 4){
                        if(tablero_string[2][6]==-7 && tablero_string[2][5]==0 && tablero_string[2][4]==0 && tablero_string[2][3]==0 && tablero_string[2][2]==-3){
                            tablero_string[2][6] = 0;
                            tablero_string[2][5] = -3;
                            tablero_string[2][4] = -7;
                            tablero_string[2][3] = 0;
                            tablero_string[2][2] = 0;
                            turno=NEGRO;
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
                if(segunda_comp==true){
                    tablero_string[hacia_y][hacia_x] = tablero_string[desde_y][desde_x] ;
                    tablero_string[desde_y][desde_x] = 0;
                    turno = NEGRO;
                    registro[index]=m;
                    index+=1;
                    return true;
                }else{
                    return false;
                }
            }
            if(turno==NEGRO){
                if(tablero_string[desde_y][desde_x]==2){
                    if(desde_y==8 && desde_y==hacia_y+2 && tablero_string[hacia_y][hacia_x] == 0 && desde_x==hacia_x){
                        segunda_comp=true;
                    }else{
                        if(desde_y==hacia_y+1){
                            if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] < -1){
                                segunda_comp=true;
                            }
                            if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                                segunda_comp=true;
                            }
                            if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] < -1){
                                segunda_comp=true;
                            }
                        }
                    }
                }
                if(tablero_string[desde_y][desde_x]==3){
                    if(desde_x==hacia_x || desde_y==hacia_y){
                        bool continuo = true;
                        if(desde_x==hacia_x){
                            if(desde_y>hacia_y){
                                for(int i=hacia_y+1;i<desde_y;i++){
                                    if(tablero_string[i][hacia_x]!=0){
                                        continuo=false;
                                        break;
                                    }
                                }
                            }
                            if(desde_y<hacia_y){
                                for(int i=desde_y+1;i<hacia_y;i++){
                                    if(tablero_string[i][hacia_x]!=0){
                                        continuo=false;
                                        break;
                                    }
                                }
                            }
                        }
                        if(desde_y==hacia_y){
                            if(desde_x>hacia_x){
                                for(int i=hacia_x+1;i<desde_x;i++){
                                    if(tablero_string[hacia_y][i]!=0){
                                        continuo=false;
                                        break;
                                    }
                                }
                            }
                            if(desde_x<hacia_x){
                                for(int i=desde_x+1;i<hacia_x;i++){
                                    if(tablero_string[hacia_y][i]!=0){
                                        continuo=false;
                                        break;
                                    }
                                }
                            }
                        }
                        if(continuo==true){
                            if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] < -1){
                                segunda_comp=true;
                            }
                        }
                    }
                }
                if(tablero_string[desde_y][desde_x]==4){
                        if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] < -1){
                            if(desde_x==hacia_x+1 || desde_x==hacia_x-1){
                                if(desde_y==hacia_y+2 || desde_y==hacia_y-2){
                                    segunda_comp=true;
                                };
                            };
                            if(desde_x==hacia_x+2 || desde_x==hacia_x-2){
                                if(desde_y==hacia_y+1 || desde_y==hacia_y-1){
                                    segunda_comp=true;
                                };
                            };
                        };
                };
                if(tablero_string[desde_y][desde_x]==5){
                            if(abs(desde_x-hacia_x)==abs(desde_y-hacia_y)){
                                if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] < -1){
                                    bool continuo=true;
                                    if(desde_x>hacia_x && desde_y>hacia_y){
                                        for(int i=1;i<desde_x-hacia_x;i++){
                                            if(tablero_string[hacia_y+i][hacia_x+i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(desde_x>hacia_x && desde_y<hacia_y){
                                        for(int i=1;i<desde_x-hacia_x;i++){
                                            if(tablero_string[hacia_y-i][hacia_x+i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(desde_x<hacia_x && desde_y>hacia_y){
                                        for(int i=1;i<hacia_x-desde_x;i++){
                                            if(tablero_string[hacia_y+i][hacia_x-i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(desde_x<hacia_x && desde_y<hacia_y){
                                        for(int i=1;i<hacia_x-desde_x;i++){
                                            if(tablero_string[hacia_y-i][hacia_x-i]!=0){
                                                continuo=false;
                                            };
                                        };
                                    };
                                    if(continuo==true){
                                        segunda_comp=true;
                                    };
                                };
                            };
                };
                if(tablero_string[desde_y][desde_x]==6){
                        if(desde_x==hacia_x || desde_y==hacia_y){
                            bool continuo = true;
                            if(desde_x==hacia_x){
                                if(desde_y>hacia_y){
                                    for(int i=hacia_y+1;i<desde_y;i++){
                                        if(tablero_string[i][hacia_x]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                                if(desde_y<hacia_y){
                                    for(int i=desde_y+1;i<hacia_y;i++){
                                        if(tablero_string[i][hacia_x]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                            };
                            if(desde_y==hacia_y){
                                if(desde_x>hacia_x){
                                    for(int i=hacia_x+1;i<desde_x;i++){
                                        if(tablero_string[hacia_y][i]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                                if(desde_x<hacia_x){
                                    for(int i=desde_x+1;i<hacia_x;i++){
                                        if(tablero_string[hacia_y][i]!=0){
                                            continuo=false;
                                            break;
                                        };
                                    };
                                };
                            };
                            if(continuo==true){
                                if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] <-1){
                                    segunda_comp=true;
                                };
                            };
                        };
                        if(abs(desde_x-hacia_x)==abs(desde_y-hacia_y)){
                            if(tablero_string[hacia_y][hacia_x]==0 || tablero_string[hacia_y][hacia_x] <-1){
                                bool continuo=true;
                                if(desde_x>hacia_x && desde_y>hacia_y){
                                    for(int i=1;i<desde_x-hacia_x;i++){
                                        if(tablero_string[hacia_y+i][hacia_x+i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(desde_x>hacia_x && desde_y<hacia_y){
                                    for(int i=1;i<desde_x-hacia_x;i++){
                                        if(tablero_string[hacia_y-i][hacia_x+i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(desde_x<hacia_x && desde_y>hacia_y){
                                    for(int i=1;i<hacia_x-desde_x;i++){
                                        if(tablero_string[hacia_y+i][hacia_x-i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(desde_x<hacia_x && desde_y<hacia_y){
                                    for(int i=1;i<hacia_x-desde_x;i++){
                                        if(tablero_string[hacia_y-i][hacia_x-i]!=0){
                                            continuo=false;
                                        };
                                    };
                                };
                                if(continuo==true){
                                    segunda_comp=true;
                                };
                            };
                        };
                };
                if(tablero_string[desde_y][desde_x]==7){
                    if(abs(desde_x-hacia_x)<=1){
                        if(abs(desde_y-hacia_y<=1)){
                            segunda_comp=true;
                        }
                    }
                    if(desde_y == 9 && desde_x == 6 && hacia_y == 9 && hacia_x == 8){
                        if(tablero_string[9][6]==-7 && tablero_string[9][7]==0 && tablero_string[9][8]==0 && tablero_string[9][9]==-3){
                            tablero_string[9][6] = 0;
                            tablero_string[9][7] =-3;
                            tablero_string[9][8] =-7;
                            tablero_string[9][9] = 0;
                            turno=BLANCO;
                            return true;
                        }else{
                            return false;
                        }
                    }
                    if(desde_y == 9 && desde_x == 6 && hacia_y == 9 && hacia_x == 4){
                        if(tablero_string[9][6]==7 && tablero_string[9][5]==0 && tablero_string[9][4]==0 && tablero_string[9][3]==0 && tablero_string[9][2]==3){
                            tablero_string[9][6] = 0;
                            tablero_string[9][5] = 3;
                            tablero_string[9][4] = 7;
                            tablero_string[9][3] = 0;
                            tablero_string[9][2] = 0;
                            turno=BLANCO;
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
                if(segunda_comp==true){
                    tablero_string[hacia_y][hacia_x] = tablero_string[desde_y][desde_x] ;
                    tablero_string[desde_y][desde_x] = 0;
                    turno = BLANCO;
                    registro[index]=m;
                    index+=1;
                    return true;
                }else{
                    return false;
                }
            }
        }
    }
    if(m.leer_tipo()==enroque_corto){
        if(turno==BLANCO){
            if(tablero_string[2][6]==-7 && tablero_string[2][7]==0 && tablero_string[2][8]==0 && tablero_string[2][9]==-3){
                tablero_string[2][6] = 0;
                tablero_string[2][7] =-3;
                tablero_string[2][8] =-7;
                tablero_string[2][9] = 0;
                turno=NEGRO;
                registro[index]=m;
                index+=1;
                return true;
            }else{
                return false;
            }
        }
        if(turno==NEGRO){
            if(tablero_string[9][6]== 7 && tablero_string[9][7]==0 && tablero_string[9][8]==0 && tablero_string[9][9]== 3){
                tablero_string[9][6] = 0;
                tablero_string[9][7] = 3;
                tablero_string[9][8] = 7;
                tablero_string[9][9] = 0;
                turno=BLANCO;
                registro[index]=m;
                index+=1;
                return true;
            }else{
                return false;
            }
        }
    }
    if(m.leer_tipo()==enroque_largo){
        if(turno==BLANCO){
            if(tablero_string[2][6]==-7 && tablero_string[2][5]==0 && tablero_string[2][4]==0 && tablero_string[2][3]==0 && tablero_string[2][2]==-3){
                tablero_string[2][6] = 0;
                tablero_string[2][5] =-3;
                tablero_string[2][4] =-7;
                tablero_string[2][3] = 0;
                tablero_string[2][2] = 0;
                turno=NEGRO;
                registro[index]=m;
                index+=1;
                return true;
            }else{
                return false;
            }
        }
        if(turno==NEGRO){
            if(tablero_string[9][6]== 7 && tablero_string[9][5]== 0 && tablero_string[9][4]== 0 && tablero_string[9][3]== 0 && tablero_string[9][2]== 3){
                tablero_string[9][6] = 0;
                tablero_string[9][5] = 3;
                tablero_string[9][4] = 7;
                tablero_string[9][3] = 0;
                tablero_string[9][2] = 0;
                turno=BLANCO;
                registro[index]=m;
                index+=1;
                return true;
            }else{
                return false;
            }
        }
    }
    if(m.leer_tipo()==PROMOCION_D){
        if(turno==BLANCO){
            if(desde_y==hacia_y-1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-6;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=-6;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-6;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(turno==NEGRO){
            if(desde_y==hacia_y+1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=6;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=6;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=6;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(primera_comp!=true){
            return false;
        }
    }
    if(m.leer_tipo()==PROMOCION_A){
        if(turno==BLANCO){
            if(desde_y==hacia_y-1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-5;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=-5;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-5;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(turno==NEGRO){
            if(desde_y==hacia_y+1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=5;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=5;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=5;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(primera_comp!=true){
            return false;
        }
    }
    if(m.leer_tipo()==PROMOCION_C){
        if(turno==BLANCO){
            if(desde_y==hacia_y-1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-4;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=-4;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-4;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(turno==NEGRO){
            if(desde_y==hacia_y+1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=4;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=4;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=4;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(primera_comp!=true){
            return false;
        }
    }
    if(m.leer_tipo()==PROMOCION_T){
        if(turno==BLANCO){
            if(desde_y==hacia_y-1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-3;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=-3;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] > 1){
                    tablero_string[hacia_y][hacia_x]=-3;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=NEGRO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(turno==NEGRO){
            if(desde_y==hacia_y+1){
                if(desde_x==hacia_x-1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=3;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x && tablero_string[hacia_y][hacia_x] == 0){
                    tablero_string[hacia_y][hacia_x]=3;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
                if(desde_x==hacia_x+1 && tablero_string[hacia_y][hacia_x] <-1){
                    tablero_string[hacia_y][hacia_x]=3;
                    tablero_string[desde_y][desde_x]=VACIA;
                    turno=BLANCO;
                    primera_comp=true;
                    return true;
                }
            }
        }
        if(primera_comp!=true){
            return false;
        }
    }
    if(m.leer_tipo()==INVALIDA){
        return false;
    }
}
int tablero::leer_tablero(int y, int x){
    return tablero_string[x][y];
}
void tablero::retroceder(){
    int aux = index-1;
    mov registroo[511];
    for(int i=0;i<=511;i++){
        registroo[i]=registro[i];
    }
    nueva_partida();
    for(int i=0;i<aux;i++){
        mover(registroo[i]);
    }
}
void tablero::print_registro(){
    for(int i=0; i<=index+15;i++){
        printf("%c%d%c%d\n", registro[i].leer_desde_x()+'a'-2, registro[i].leer_desde_y()-1,registro[i].leer_hacia_x()+'a'-2, registro[i].leer_hacia_y()-1);
    }
}

