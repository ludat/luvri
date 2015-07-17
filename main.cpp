#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "header.h"
#include "motor.h"
using namespace std;
mov oponente;
tablero principal;
mov computadora;
bool turno;
tablero auxiliar;
int main(int argc, char *argv[]){
    srand(time(NULL));
    char entrada[256];
    printf("Motor con aproximadamente 800 de elo que hace estupideces ocacionalmente.\n");
    printf("El motor se llama Luvri\n");
    printf("Primer prueba de make command");
    printf("veamos que onda\n");
    printf("ESCRIBIR EL COMANDO:\"help\" PARA CONSEGUIR AYUDA\n");
    principal.nueva_partida();
    int color_compu = NEGRO;
    for(;;){
        printf("%d",evaluar(principal));
        if(color_compu!=EMPTY){
            if(color_compu == principal.leer_turno()){
                computadora=pensar(principal);
                principal.mover(computadora);
                principal.leer();
                printf("move %c%d%c%d", computadora.leer_desde_x()+'a'-2, computadora.leer_desde_y()-1,computadora.leer_hacia_x()+'a'-2, computadora.leer_hacia_y()-1);
            }
        }
            printf("\nluvri0.1>");
            if(scanf("%s", entrada)==EOF){
                return 0;
            }
            if(!strcmp(entrada, "help")){
                printf("print: escribe la ultima jugada\n");
                printf("exit: sale del programa\n");
                printf("new: incia una nueva partida\n");
                printf("show: muestra el tablero y de quien es el turno\n");
                printf("xboard: entra en el modo Xboard\n");
                printf("blanco o negro: indica que color debe jugar la maquina\n");
                printf("gente: hace que la maquina no juegue hasta que se le indique un color\n");
                printf("move: juega en esa jugada\n");
                printf("ret: retrocede un movimiento (usar el comando gente o si no la maquina jugara de nuevo y no se podra retroceder nada\n");
                printf("reg: muestra el registro de jugadas hechas hasta ahora\n");
                printf("save: guarda la ultima partida jugada en el archivo partidas.txt... proximamente\n");
                continue;
            }
            if(!strcmp(entrada, "exit")){
                break;
            }
            if(!strcmp(entrada, "print")){
                oponente.leer();
                continue;
            }
            if(!strcmp(entrada, "xboard")){
                xboard();
                break;
            }
            if(!strcmp(entrada, "new")){
                principal.nueva_partida();
                principal.leer();
                continue;
            }
            if(!strcmp(entrada, "show")){
                principal.leer();
                continue;
            }
            if(!strcmp(entrada, "blanco")){
                color_compu=BLANCO;
                continue;
            };
            if(!strcmp(entrada, "negro")){
                color_compu=NEGRO;
                continue;
            };
            if(!strcmp(entrada, "gente")){
                color_compu = EMPTY;
                continue;
            };
            if(!strcmp(entrada, "move")){
                computadora=pensar(principal);
                principal.mover(computadora);
                principal.leer();
                continue;
            };
            if(!strcmp(entrada, "ret")){
                principal.retroceder();
                continue;
            };
            if(!strcmp(entrada, "reg")){
                principal.print_registro();
                continue;
            };
            if(oponente.escribir(entrada)){
                //printf("jugada legal\n");
                /*if(principal.mover(oponente)){
                    printf("Movida realizada con exito\n");
                }else{
                    printf("funcion mover devolvio false\n");
                }*/
                principal.mover(oponente);
                //principal.leer();
            }else{
                printf("WTF");
            };
   };
};
void xboard(){
    int color_comp=NEGRO;
    char line[256], command[256];
    signal(SIGINT, SIG_IGN);
    setbuf(stdout, NULL);
    int m;
    principal.nueva_partida();
    for (;;) {
        //printf("el valor actual del tablero es:%d\n",evaluar(principal));
        if (principal.leer_turno() == color_comp) {
            computadora=pensar(principal);
            if(principal.mover(computadora)){
                    printf("\nmove %c%d%c%d\n", computadora.leer_desde_x()+'a'-2, computadora.leer_desde_y()-1,
                                                computadora.leer_hacia_x()+'a'-2, computadora.leer_hacia_y()-1);
            }else{
                printf("el tablero no dejo mover");
            }
        };
        if (!fgets(line, 256, stdin)){
            return;
        };
        if (line[0] == '\n'){
            fflush(stdout);
            continue;
        };
        sscanf(line, "%s", command);
        if (!strcmp(command, "xboard")){
            continue;
        };
        if (!strcmp(command, "new")){
            principal.nueva_partida();
            color_comp = NEGRO;
            continue;
        };
        if(!strcmp(command, "show")){
            principal.leer();
            continue;
        };
        if (!strcmp(command, "quit"))
            return;
        if (!strcmp(command, "force")){
            color_comp = EMPTY;
            continue;
        };
        if (!strcmp(command, "white")) {
            color_comp = BLANCO;
            continue;
        };
        if (!strcmp(command, "black")){
            color_comp = NEGRO;
            continue;
        };
        if (!strcmp(command, "undo")) {
            principal.retroceder();
            continue;
        }
        if (!strcmp(command, "remove")) {
            principal.retroceder();
            principal.retroceder();
            continue;
        }/*
        if (!strcmp(command, "st")) {
            sscanf(line, "st %d", &max_time);
            max_time *= 1000;
            max_depth = 32;
            continue;
        };
        if (!strcmp(command, "sd")) {
            sscanf(line, "sd %d", &max_depth);
            max_time = 1 << 25;
            continue;
        }
        if (!strcmp(command, "time")) {
            sscanf(line, "time %d", &max_time);
            max_time *= 10;
            max_time /= 30;
            max_depth = 32;
            continue;
        }
        if (!strcmp(command, "otim")) {
            continue;
        }
        if (!strcmp(command, "go")) {
            color_comp = principal.leer_turno();
            continue;
        }
        if (!strcmp(command, "hint")) {
            think(0);
            if (!pv[0][0].u)
                continue;
            printf("Hint: %s\n", move_str(pv[0][0].b));
            continue;
        }
        if (!strcmp(command, "post")) {
            post = 2;
            continue;
        }
        if (!strcmp(command, "nopost")) {
            post = 0;
            continue;
        }*/
        if(oponente.escribir(command)){
            if(principal.mover(oponente)){
            }else{
                printf("Illegal move: %c%d%c%d\n",  oponente.leer_desde_x()+'a'-2, oponente.leer_desde_y()-1,
                                                    oponente.leer_hacia_x()+'a'-2, oponente.leer_hacia_y()-1);
            }
        }
    }
}

