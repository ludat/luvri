#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "header.h"
#include "motor.h"
mov pensar(tablero super_original){
    posibles mejores_jugadas;
    tablero super_aux = super_original;
    int i = 0;
    //mejores_jugadas.leer();
    //printf("\n");
    mejor_jugada(super_aux, &mejores_jugadas, 0, 1  , super_aux.leer_turno());
    //printf("saliendo del loop mejor_jugada\n");
    //mejores_jugadas.leer();
    //printf("\n");
    return mejores_jugadas.leer_mejor();
}


void mejor_jugada(tablero original,posibles* mejores_jugadas, int ply, int max_ply, int color_tablero_original){
    //printf("entrando a mejor_jugada(tablero, mejores_jugadas, %d, %d",ply,max_ply);
    //system("pause");
    //printf("%d == %d afuera del if\n",ply,max_ply);
    if(ply!=max_ply+1){
        //printf("%d == %d adentro del if\n",ply,max_ply);
        tablero aux;
        mov posibilidades[101];
        int valores_de_jugadas[101];
        int mejorjugada = 0;//esto es solo el valor de la mejor jugada
        int indice_mejoresjugadas[101];
        int cont_mejoresjugadas = 0;
        mov movimiento;
        aux=original;
        generar_jugadas(original, posibilidades);
        //asigna a cada movimiento un valor entero de cuanto vale el movimiento posibilidades[i] en valores_de_jugadas[i]
        for(int i = 0;i<=100;i++){
            if(aux.mover(posibilidades[i])){
                valores_de_jugadas[i] = evaluar(aux);
                aux=original;
            }else{
                posibilidades[i].escribir(0,0,0,0,-1);
            }
        }
        //printf("\n%d\n", ply);
        //for(int i = 0;i<=40;i++){
        //    printf("%d    ",i);
        //    posibilidades[i].leer();
        //    printf("              %d\n", valores_de_jugadas[i]);
        //}
        //system("pause");
        //analiza cada caso, busca el mayor y hace que los demas sean jugadas invalidas
        //CODIGO TERRIBLEMENTE CONFUSO E INENTENDIBLE SI FUNCIONA SOY JESUS (soy jesus funciona! esta vivo!)
        /*lo que hace este codigo tan feo es optimizar un poco la velocidad del algoritmo de busqueda basado en la siguiente cosa
        si a>b y b>c entonces a>c sabiendo esto reduzco la cantidad de fors para encontrar la jugada que
        deje al oponente con menos piezas ahora la explico linea por linea*/
        mejorjugada=valores_de_jugadas[0];  //primero supongo que la primer jugada es la mejor
        for(int i = 0;i<=100;i++){
            indice_mejoresjugadas[i]=0;
        }
        cont_mejoresjugadas = 1;
        if(ply!=0){          //el contador de jugadas ahora vale uno(cuenta la cantidad de jugadas "mejores" que teng
            if(original.leer_turno()==BLANCO){
                for(int i = 0;i<=100;i++){         //un for para recorrer todas las jugadas
                    if(posibilidades[i].leer_tipo()!=-1){       //veo si la jugada es o no INVALIDA o sea de mov.tipo != -1
                        //printf("\n%d lalalalalalalallalllalalalla %d\n", ply,i);
                        //for(int i = 0;i<=40;i++){
                        //    printf("%d    ",i);
                        //    posibilidades[i].leer();
                        //    printf("              %d\n", valores_de_jugadas[i]);
                        //}
                        //system("pause");
                        if(mejorjugada<valores_de_jugadas[i]){//si la jugada es peor que la mejor..
                            valores_de_jugadas[i]=0;//el valor vale 0 en index i
                            posibilidades[i].escribir(0,0,0,0,-1);//y la jugada se trata como nula y no es considerada
                            continue;
                        }//si no..
                        if(mejorjugada==valores_de_jugadas[i]){//si lajugada es igual a la mejor..
                            indice_mejoresjugadas[cont_mejoresjugadas] = i;//guarda el indice en indice_mejoresjugadas en el indice uno mayor al anterior
                            cont_mejoresjugadas += 1;//aumenta en uno el indice para no sobreescribir
                            continue;
                        }
                        if(mejorjugada>valores_de_jugadas[i]){//si es mejor que la mejor jugada...
                            mejorjugada=valores_de_jugadas[i];//la mejor jugada es sustituida
                            for(int j = 0; j<cont_mejoresjugadas; j++){//un for para recorrer todas las "mejores" encontradas hasta ahora
                                posibilidades[indice_mejoresjugadas[j]].escribir(0,0,0,0,-1);//busca todas las jugadas iguales a la mejor anterior y la anula a todas
                                valores_de_jugadas[indice_mejoresjugadas[j]]=0;//anula el valor
                            }
                            cont_mejoresjugadas = 0;
                            indice_mejoresjugadas[cont_mejoresjugadas] = i;
                            cont_mejoresjugadas += 1;//reinicia el contador de validas
                            continue;
                        }
                    }
                }
            }
            if(original.leer_turno()==NEGRO){
                for(int i = 0;i<=100;i++){         //un for para recorrer todas las jugadas
                    if(posibilidades[i].leer_tipo()!=-1){       //veo si la jugada es o no INVALIDA o sea de mov.tipo != -1
                        //printf("%d es el menor puntaje conseguido y estoy en el bucle %d/100\n",mejorjugada,i);//imprimir boludeces para guiarme
                        if(mejorjugada>valores_de_jugadas[i]){//si la jugada es peor que la mejor..
                            valores_de_jugadas[i]=0;//el valor vale 0 en index i
                            posibilidades[i].escribir(0,0,0,0,-1);//y la jugada se trata como nula y no es considerada
                        }else{//si no..
                            if(mejorjugada==valores_de_jugadas[i]){//si lajugada es igual a la mejor..
                                indice_mejoresjugadas[cont_mejoresjugadas] = i;//guarda el indice en indice_mejoresjugadas en el indice uno mayor al anterior
                                cont_mejoresjugadas += 1;//aumenta en uno el indice para no sobreescribir
                            }
                            if(mejorjugada<valores_de_jugadas[i]){//si es mejor que la mejor jugada...
                                mejorjugada=valores_de_jugadas[i];//la mejor jugada es sustituida
                                for(int j = 0; j<cont_mejoresjugadas; j++){//un for para recorrer todas las "mejores" encontradas hasta ahora
                                    posibilidades[indice_mejoresjugadas[j]].escribir(0,0,0,0,-1);//busca todas las jugadas iguales a la mejor anterior y la anula a todas
                                    valores_de_jugadas[indice_mejoresjugadas[j]]=0;//anula el valor
                                }
                                cont_mejoresjugadas = 0;//reinicia el contador de validas
                                indice_mejoresjugadas[cont_mejoresjugadas] = i;
                                cont_mejoresjugadas +=1;
                            }
                        }
                    }
                }
            }
        }
       // printf("\n%d\n", ply);
        //for(int i = 0;i<=40;i++){
        //    printf("%d    ",i);
        //    posibilidades[i].leer();
        //    printf("              %d\n", valores_de_jugadas[i]);
        //}
        //printf("el valor de la mejor jugada es: %d\n", mejorjugada);
        //printf("y esta en el indice: %d\n", indice_mejoresjugadas[0]);
        //system("pause");
        bool mate = true;
        for(int i = 0; i<=100;i++){
            aux = original;
            if(posibilidades[i].leer_tipo()!=-1){
                aux.mover(posibilidades[i]);
                if(come_rey(aux)){
                    //printf("upsi sigo en come_rey busco otra jugada\n");
                    //movimiento.leer();//guias
                    //printf("\n");
                }else{
                    mate = false;
                    mejores_jugadas->addnew(posibilidades[i],valores_de_jugadas[i],ply,max_ply, color_tablero_original);
                    //printf("ply = %d\n", ply);
                    //mejores_jugadas->leer();
                    //system("pause");
                    //printf("nueva jugada guardada\n");
                    //mejores_jugadas->leer();
                    //printf("el movimiento anterior a este es:");
                    //posibilidades[i].leer();
                    //printf("\n");
                    //printf("\n");
                    mejor_jugada(aux, mejores_jugadas, ply+1, max_ply, color_tablero_original);
                }
            }
        }
        if(mate==true){
            generar_jugadas(original, posibilidades);
            for(int i = 0; i<=100;i++){
                aux = original;
                if(posibilidades[i].leer_tipo()!=-1){
                    aux.mover(posibilidades[i]);
                    if(come_rey(aux)){
                        //printf("upsi sigo en come_rey busco otra jugada\n");
                        //movimiento.leer();//guias
                        //printf("\n");
                    }else{
                        mate = false;
                        mejores_jugadas->addnew(posibilidades[i],valores_de_jugadas[i],ply,max_ply, color_tablero_original);
                        //printf("ply = %d\n", ply);
                        //mejores_jugadas->leer();
                        //system("pause");
                        //printf("nueva jugada guardada\n");
                        //mejores_jugadas->leer();
                        //system("pause");
                        //posibilidades[i].leer();
                        //printf("\n");
                        mejor_jugada(aux, mejores_jugadas, ply+1, max_ply, color_tablero_original);
                    }
                }
            }
        }
        if(mate==true){
            printf("encontre un mate la puta madre\n");
            posibilidades[0].escribir(0,0,0,0,-2);
            mejores_jugadas->addnew(posibilidades[0],1000000,ply, max_ply, color_tablero_original);//ESTA PARTE DEL CODIGO ES PARA EL MATE.. DESPUES LA VOY A REVISAR MAS PROFUNDAMENTE
        }
        //si ninguna de las jugadas anteriores no terminaba en come_rey busca de nuevo todas las jugadas y sacrifica el comer piezas
        //para salir de la situacion de come_rey
        //generar_jugadas(original,posibilidades);
        //for(int i = 0;i<=100;i++){//prueba todas las jugadas legales y si una termina en no estar en come_rey la juega
        //    movimiento = random(original, posibilidades,i);
        //    aux.mover(movimiento);
        //    if(come_rey(aux)){
        //        aux = original;
        //    }else{
        //        mejores_jugadas->addnew(posibilidades[i],valores_de_jugadas[i],ply,max_ply, original.leer_turno());
        //        mejor_jugada(aux, mejores_jugadas, ply+1, max_ply);
        //    }
        //}
    }
}


void generar_jugadas(tablero tablero_a_buscar, mov* pposibilidades){
    for(int i=0;i<101;i++){
        pposibilidades[i].escribir(0, 0, 0, 0, -1);
    };
    int index=0;
    //tablero_a_buscar.leer();
    if(tablero_a_buscar.leer_turno() == BLANCO){
        for(int i=2;i<10;i++){
            for(int j=2;j<10;j++){
                if(tablero_a_buscar.leer_tablero(i,j)==-2){
                    if(j==3 && tablero_a_buscar.leer_tablero(i,j+2)==0 && tablero_a_buscar.leer_tablero(i,j+1)==0){
                        pposibilidades[index].escribir(i, j, i, j+2, 0);
                        index +=1;
                    }
                    if(tablero_a_buscar.leer_tablero(i,j+1)==0){
                        if(j==8){
                            pposibilidades[index].escribir(i, j, i, j+1, PROMOCION_D);
                            index +=1;
                        }else{
                            pposibilidades[index].escribir(i, j, i, j+1, 0);
                            index +=1;
                        }
                    }
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)>1){
                        if(j==8){
                            pposibilidades[index].escribir(i, j, i+1, j+1, PROMOCION_D);
                            index +=1;
                        }else{
                            pposibilidades[index].escribir(i, j, i+1, j+1, 0);
                            index +=1;
                        }
                    }
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)>1){
                        if(j==8){
                            pposibilidades[index].escribir(i, j, i-1, j+1, PROMOCION_D);
                            index +=1;
                        }else{
                            pposibilidades[index].escribir(i, j, i-1, j+1, 0);
                            index +=1;
                        }
                    }
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-3){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)>1){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)>1){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)>1){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)>1){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-4){
                    if(tablero_a_buscar.leer_tablero(i+2,j+1)==0 || tablero_a_buscar.leer_tablero(i+2,j+1)>1){
                        pposibilidades[index].escribir(i,j,i+2,j+1,0);
                        index +=1;
                    }
                    if(tablero_a_buscar.leer_tablero(i+2,j-1)==0 || tablero_a_buscar.leer_tablero(i+2,j-1)>1){
                        pposibilidades[index].escribir(i,j,i+2,j-1,0);
                        index +=1;
                    }
                    if(tablero_a_buscar.leer_tablero(i-2,j+1)==0 || tablero_a_buscar.leer_tablero(i-2,j+1)>1){
                        pposibilidades[index].escribir(i,j,i-2,j+1,0);
                        index +=1;
                    }
                    if(tablero_a_buscar.leer_tablero(i-2,j-1)==0 || tablero_a_buscar.leer_tablero(i-2,j-1)>1){
                        pposibilidades[index].escribir(i,j,i-2,j-1,0);
                        index +=1;
                    }/////////////////////////////////////////////////////////////////////////////////////////
                    if(tablero_a_buscar.leer_tablero(i+1,j+2)==0 || tablero_a_buscar.leer_tablero(i+1,j+2)>1){
                        pposibilidades[index].escribir(i,j,i+1,j+2,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-2)==0 || tablero_a_buscar.leer_tablero(i+1,j-2)>1){
                        pposibilidades[index].escribir(i,j,i+1,j-2,0);
                        index +=1;
                    }
                    if(tablero_a_buscar.leer_tablero(i-1,j+2)==0 || tablero_a_buscar.leer_tablero(i-1,j+2)>1){
                        pposibilidades[index].escribir(i,j,i-1,j+2,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-2)==0 || tablero_a_buscar.leer_tablero(i-1,j-2)>1){
                        pposibilidades[index].escribir(i,j,i-1,j-2,0);
                        index +=1;
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-5){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)>1){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)>1){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            }else{
                                derecha=false;
                            }
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)>1){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            }
                        }
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            }
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)>1){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            }
                        }
                    }
                }
                if(tablero_a_buscar.leer_tablero(i,j)==-6){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)>1){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)>1){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)>1){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)>1){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            };
                        };
                    };
                    izquierda = true;
                    derecha = true;
                    arriba = true;
                    abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)>1){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)>1){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)>1){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)>1){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-7){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)==0 || tablero_a_buscar.leer_tablero(i+1,j+1)>1){
                        pposibilidades[index].escribir(i,j,i+1,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j)==0 || tablero_a_buscar.leer_tablero(i+1,j)>1){
                        pposibilidades[index].escribir(i,j,i+1,j,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)==0 || tablero_a_buscar.leer_tablero(i+1,j-1)>1){
                        pposibilidades[index].escribir(i,j,i+1,j-1,0);
                        index +=1;
                    };//////////////////////
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)==0 || tablero_a_buscar.leer_tablero(i-1,j+1)>1){
                        pposibilidades[index].escribir(i,j,i-1,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j)==0 || tablero_a_buscar.leer_tablero(i-1,j)>1){
                        pposibilidades[index].escribir(i,j,i-1,j,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)==0 || tablero_a_buscar.leer_tablero(i-1,j-1)>1){
                        pposibilidades[index].escribir(i,j,i-1,j-1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j+1)==0 || tablero_a_buscar.leer_tablero(i,j+1)>1){
                        pposibilidades[index].escribir(i,j,i,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j-1)==0 || tablero_a_buscar.leer_tablero(i,j-1)>1){
                        pposibilidades[index].escribir(i,j,i,j-1,0);
                        index +=1;
                    }
                }
            }
        }
    }
    if(tablero_a_buscar.leer_turno() == NEGRO){
        for(int i=2;i<10;i++){
            for(int j=2;j<10;j++){
                if(tablero_a_buscar.leer_tablero(i,j)==2){
                    if(j==8 && tablero_a_buscar.leer_tablero(i,j-2)==VACIA && tablero_a_buscar.leer_tablero(i,j-1)==VACIA){
                        pposibilidades[index].escribir(i, j, i, j-2, 0);
                        index +=1;
                    }
                    if(tablero_a_buscar.leer_tablero(i,j-1)==VACIA){
                        if(j==3){
                            pposibilidades[index].escribir(i, j, i, j-1, PROMOCION_D);
                            index +=1;
                        }else{
                            pposibilidades[index].escribir(i, j, i, j-1, 0);
                            index +=1;
                        }
                    }
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)<-1){
                        if(j==3){
                            pposibilidades[index].escribir(i, j, i+1, j-1, PROMOCION_D);
                            index +=1;
                        }else{
                            pposibilidades[index].escribir(i, j, i+1, j-1, 0);
                            index +=1;
                        }
                    }
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)<-1){
                        if(j==3){
                            pposibilidades[index].escribir(i, j, i-1, j-1, PROMOCION_D);
                            index +=1;
                        }else{
                            pposibilidades[index].escribir(i, j, i-1, j-1, 0);
                            index +=1;
                        }
                    }
                }
                if(tablero_a_buscar.leer_tablero(i,j)==3){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)<-1){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)<-1){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)<-1){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)<-1){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==4){
                    if(tablero_a_buscar.leer_tablero(i+2,j+1)==0 || tablero_a_buscar.leer_tablero(i+2,j+1)<-1){
                        pposibilidades[index].escribir(i,j,i+2,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i+2,j-1)==0 || tablero_a_buscar.leer_tablero(i+2,j-1)<-1){
                        pposibilidades[index].escribir(i,j,i+2,j-1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j+1)==0 || tablero_a_buscar.leer_tablero(i-2,j+1)<-1){
                        pposibilidades[index].escribir(i,j,i-2,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j-1)==0 || tablero_a_buscar.leer_tablero(i-2,j-1)<-1){
                        pposibilidades[index].escribir(i,j,i-2,j-1,0);
                        index +=1;
                    };//////////////////////////////////////////////////////////////////////////////
                    if(tablero_a_buscar.leer_tablero(i+1,j+2)==0 || tablero_a_buscar.leer_tablero(i+1,j+2)<-1){
                        pposibilidades[index].escribir(i,j,i+1,j+2,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-2)==0 || tablero_a_buscar.leer_tablero(i+1,j-2)<-1){
                        pposibilidades[index].escribir(i,j,i+1,j-2,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j+2)==0 || tablero_a_buscar.leer_tablero(i-1,j+2)<-1){
                        pposibilidades[index].escribir(i,j,i-1,j+2,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-2)==0 || tablero_a_buscar.leer_tablero(i-1,j-2)<-1){
                        pposibilidades[index].escribir(i,j,i-1,j-2,0);
                        index +=1;
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==5){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)<-1){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)<-1){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)<-1){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)<-1){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==6){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)<-1){
                                pposibilidades[index].escribir(i, j, i, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)<-1){
                                pposibilidades[index].escribir(i, j, i, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)<-1){
                                pposibilidades[index].escribir(i, j, i+k, j,0);
                                index +=1;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)<-1){
                                pposibilidades[index].escribir(i, j, i-k, j,0);
                                index +=1;
                            };
                        };
                    };
                    izquierda = true;
                    derecha = true;
                    arriba = true;
                    abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)<-1){
                                pposibilidades[index].escribir(i, j, i+k, j+k,0);
                                index +=1;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)<-1){
                                pposibilidades[index].escribir(i, j, i-k, j-k,0);
                                index +=1;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)<-1){
                                pposibilidades[index].escribir(i, j, i+k, j-k,0);
                                index +=1;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)<-1){
                                pposibilidades[index].escribir(i, j, i-k, j+k,0);
                                index +=1;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==7){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)==0 || tablero_a_buscar.leer_tablero(i+1,j+1)<-1){
                        pposibilidades[index].escribir(i,j,i+1,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j)==0 || tablero_a_buscar.leer_tablero(i+1,j)<-1){
                        pposibilidades[index].escribir(i,j,i+1,j,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)==0 || tablero_a_buscar.leer_tablero(i+1,j-1)<-1){
                        pposibilidades[index].escribir(i,j,i+1,j-1,0);
                        index +=1;
                    };//////////////////////
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)==0 || tablero_a_buscar.leer_tablero(i-1,j+1)<-1){
                        pposibilidades[index].escribir(i,j,i-1,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j)==0 || tablero_a_buscar.leer_tablero(i-1,j)<-1){
                        pposibilidades[index].escribir(i,j,i-1,j,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)==0 || tablero_a_buscar.leer_tablero(i-1,j-1)<-1){
                        pposibilidades[index].escribir(i,j,i-1,j-1,0);
                        index +=1;
                    };///////////////////////
                    if(tablero_a_buscar.leer_tablero(i,j+1)==0 || tablero_a_buscar.leer_tablero(i,j+1)<-1){
                        pposibilidades[index].escribir(i,j,i,j+1,0);
                        index +=1;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j-1)==0 || tablero_a_buscar.leer_tablero(i,j-1)<-1){
                        pposibilidades[index].escribir(i,j,i,j-1,0);
                        index +=1;
                    }
                }
            }
        }
    }
}


mov random(tablero tablerin, mov* pposibilidades){
    srand(time(NULL));
    int index=0;
    for(;;){
        int i=rand();
        if(pposibilidades[i].leer_tipo()!=-1){
            return pposibilidades[i];
        }
    }
}


mov random(tablero tablerin, mov* pposibilidades,int indice){
    return pposibilidades[indice];
};


bool come_rey(tablero tablero_a_buscar){
    if(tablero_a_buscar.leer_turno() == BLANCO){
        for(int i=2;i<10;i++){
            for(int j=2;j<10;j++){
                if(tablero_a_buscar.leer_tablero(i,j)==-2){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)== 7){
                        return true;
                    }
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)== 7){
                        return true;
                    }
                }
                if(tablero_a_buscar.leer_tablero(i,j)==-3){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-4){
                    if(tablero_a_buscar.leer_tablero(i+2,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+2,j-1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j-1)==7){
                        return true;
                    };//////////////////////////////////////////////////////////////////////////////
                    if(tablero_a_buscar.leer_tablero(i+1,j+2)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-2)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j+2)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-2)==7){
                        return true;
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-5){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-6){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==7){
                                return true;
                            };
                        };
                    };
                    izquierda = true;
                    derecha = true;
                    arriba = true;
                    abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-7){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)==7){
                        return true;
                    };//////////////////////
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j-1)==7){
                        return true;
                    }
                }
            }
        }
    }
    if(tablero_a_buscar.leer_turno() == NEGRO){
        for(int i=2;i<10;i++){
            for(int j=2;j<10;j++){
                if(tablero_a_buscar.leer_tablero(i,j)==2){
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)== -7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)== -7){
                        return true;
                    }
                };
                if(tablero_a_buscar.leer_tablero(i,j)==3){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==-7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==4){
                    if(tablero_a_buscar.leer_tablero(i+2,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+2,j-1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j-1)==-7){
                        return true;
                    };//////////////////////////////////////////////////////////////////////////////
                    if(tablero_a_buscar.leer_tablero(i+1,j+2)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-2)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j+2)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-2)==-7){
                        return true;
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==5){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==-7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==6){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==-7){
                                return true;
                            };
                        };
                    };
                    izquierda = true;
                    derecha = true;
                    arriba = true;
                    abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==-7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==7){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)==-7){
                        return true;
                    };//////////////////////
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j-1)==-7){
                        return true;
                    }
                }
            }
        }
    }
}
/*
esta funcion evaluar la ventaja material que tiene el color introducido en el parametro si se hace una de las jugadas de la
variable posibilidades (tambien en parametros) en el tablero del parmetro y devuelve el puntaje material del tablero
que deberia ser uno auxiliar
*/



int evaluar(tablero a_evaluar){
    int puntaje_material = 0; //declaramos la variable que retornara el puntaje material
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){
            if(a_evaluar.leer_tablero(i,j)==2){
                puntaje_material += PEON;
            }
            if(a_evaluar.leer_tablero(i,j)==3){
                puntaje_material += TORRE;
            }
            if(a_evaluar.leer_tablero(i,j)==4){
                puntaje_material += CABALLO;
            }
            if(a_evaluar.leer_tablero(i,j)==5){
                puntaje_material += ALFIL;
            }
            if(a_evaluar.leer_tablero(i,j)==6){
                puntaje_material += DAMA;
            }
            if(a_evaluar.leer_tablero(i,j)==7){
                puntaje_material += REY;
            }
            if(a_evaluar.leer_tablero(i,j)==-2){
                puntaje_material -= PEON;
            }
            if(a_evaluar.leer_tablero(i,j)==-3){
                puntaje_material -= TORRE;
            }
            if(a_evaluar.leer_tablero(i,j)==-4){
                puntaje_material -= CABALLO;
            }
            if(a_evaluar.leer_tablero(i,j)==-5){
                puntaje_material -= ALFIL;
            }
            if(a_evaluar.leer_tablero(i,j)==-6){
                puntaje_material -= DAMA;
            }
            if(a_evaluar.leer_tablero(i,j)==-7){
                puntaje_material -= REY;
            }
        }
    }
    int puntaje_posibles=0;
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){
            if(a_evaluar.leer_tablero(i,j)==-2){
                if(j==3 && a_evaluar.leer_tablero(i,j+2)==VACIA && a_evaluar.leer_tablero(i,j+1)==VACIA){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i,j+1)==VACIA){
                    if(j==8){
                        puntaje_posibles -=1;
                    }else{
                        puntaje_posibles -=1;
                    }
                };
                if(a_evaluar.leer_tablero(i+1,j+1)>1){
                    if(j==8){
                        puntaje_posibles -=1;
                    }else{
                        puntaje_posibles -=1;
                    }
                };
                if(a_evaluar.leer_tablero(i-1,j+1)>1){
                    if(j==8){
                        puntaje_posibles -=1;
                    }else{
                        puntaje_posibles -=1;
                    }
                };
            };
            if(a_evaluar.leer_tablero(i,j)==-3){
                bool izquierda = true;
                bool derecha = true;
                bool arriba = true;
                bool abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i,j+k)==0){
                            puntaje_posibles -=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i,j+k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i,j-k)==0){
                            puntaje_posibles -=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i,j-k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j)==0){
                            puntaje_posibles -=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j)==0){
                            puntaje_posibles -=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j)>1){
                            puntaje_posibles -=1;
                        };
                    };
                };
            };
            if(a_evaluar.leer_tablero(i,j)==-4){
                if(a_evaluar.leer_tablero(i+2,j+1)==0 || a_evaluar.leer_tablero(i+2,j+1)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i+2,j-1)==0 || a_evaluar.leer_tablero(i+2,j-1)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i-2,j+1)==0 || a_evaluar.leer_tablero(i-2,j+1)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i-2,j-1)==0 || a_evaluar.leer_tablero(i-2,j-1)>1){
                    puntaje_posibles -=1;
                };//////////////////////////////////////////////////////////////////////////////
                if(a_evaluar.leer_tablero(i+1,j+2)==0 || a_evaluar.leer_tablero(i+1,j+2)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i+1,j-2)==0 || a_evaluar.leer_tablero(i+1,j-2)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i-1,j+2)==0 || a_evaluar.leer_tablero(i-1,j+2)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i-1,j-2)==0 || a_evaluar.leer_tablero(i-1,j-2)>1){
                    puntaje_posibles -=1;
                };
            };
            if(a_evaluar.leer_tablero(i,j)==-5){
                bool izquierda = true;
                bool derecha = true;
                bool arriba = true;
                bool abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i+k,j+k)==0){
                            puntaje_posibles -=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j+k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i-k,j-k)==0){
                            puntaje_posibles -=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j-k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j-k)==0){
                            puntaje_posibles -=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j-k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j+k)==0){
                            puntaje_posibles -=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j+k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                };
            };
            if(a_evaluar.leer_tablero(i,j)==-6){
                bool izquierda = true;
                bool derecha = true;
                bool arriba = true;
                bool abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i,j+k)==0){
                            puntaje_posibles -=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i,j+k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i,j-k)==0){
                            puntaje_posibles -=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i,j-k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j)==0){
                            puntaje_posibles -=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j)==0){
                            puntaje_posibles -=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j)>1){
                            puntaje_posibles -=1;
                        };
                    };
                };
                izquierda = true;
                derecha = true;
                arriba = true;
                abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i+k,j+k)==0){
                            puntaje_posibles -=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j+k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i-k,j-k)==0){
                            puntaje_posibles -=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j-k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j-k)==0){
                            puntaje_posibles -=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j-k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j+k)==0){
                            puntaje_posibles -=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j+k)>1){
                            puntaje_posibles -=1;
                        };
                    };
                };
            };
            if(a_evaluar.leer_tablero(i,j)==-7){
                if(a_evaluar.leer_tablero(i+1,j+1)==0 || a_evaluar.leer_tablero(i+1,j+1)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i+1,j)==0 || a_evaluar.leer_tablero(i+1,j)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i+1,j-1)==0 || a_evaluar.leer_tablero(i+1,j-1)>1){
                    puntaje_posibles -=1;
                };//////////////////////
                if(a_evaluar.leer_tablero(i-1,j+1)==0 || a_evaluar.leer_tablero(i-1,j+1)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i-1,j)==0 || a_evaluar.leer_tablero(i-1,j)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i-1,j-1)==0 || a_evaluar.leer_tablero(i-1,j-1)>1){
                    puntaje_posibles -1;
                };
                if(a_evaluar.leer_tablero(i,j+1)==0 || a_evaluar.leer_tablero(i,j+1)>1){
                    puntaje_posibles -=1;
                };
                if(a_evaluar.leer_tablero(i,j-1)==0 || a_evaluar.leer_tablero(i,j-1)>1){
                    puntaje_posibles -=1;
                }
            }
        }
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){
            if(a_evaluar.leer_tablero(i,j)==2){
                if(j==8 && a_evaluar.leer_tablero(i,j-2)==VACIA && a_evaluar.leer_tablero(i,j-1)==VACIA){
                    puntaje_posibles +=1;
                }
                if(a_evaluar.leer_tablero(i,j-1)==VACIA){
                    if(j==3){
                        puntaje_posibles +=1;
                    }else{
                        puntaje_posibles +=1;
                    }
                }
                if(a_evaluar.leer_tablero(i+1,j-1)<-1){
                    if(j==3){
                        puntaje_posibles +=1;
                    }else{
                        puntaje_posibles +=1;
                    }
                }
                if(a_evaluar.leer_tablero(i-1,j-1)<-1){
                    if(j==3){
                        puntaje_posibles +=1;
                    }else{
                        puntaje_posibles +=1;
                    }
                }
            }
            if(a_evaluar.leer_tablero(i,j)==3){
                bool izquierda = true;
                bool derecha = true;
                bool arriba = true;
                bool abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i,j+k)==0){
                            puntaje_posibles +=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i,j+k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i,j-k)==0){
                            puntaje_posibles +=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i,j-k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j)==0){
                            puntaje_posibles +=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j)==0){
                            puntaje_posibles +=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                };
            };
            if(a_evaluar.leer_tablero(i,j)==4){
                if(a_evaluar.leer_tablero(i+2,j+1)==0 || a_evaluar.leer_tablero(i+2,j+1)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i+2,j-1)==0 || a_evaluar.leer_tablero(i+2,j-1)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i-2,j+1)==0 || a_evaluar.leer_tablero(i-2,j+1)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i-2,j-1)==0 || a_evaluar.leer_tablero(i-2,j-1)<-1){
                    puntaje_posibles +=1;
                };//////////////////////////////////////////////////////////////////////////////
                if(a_evaluar.leer_tablero(i+1,j+2)==0 || a_evaluar.leer_tablero(i+1,j+2)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i+1,j-2)==0 || a_evaluar.leer_tablero(i+1,j-2)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i-1,j+2)==0 || a_evaluar.leer_tablero(i-1,j+2)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i-1,j-2)==0 || a_evaluar.leer_tablero(i-1,j-2)<-1){
                    puntaje_posibles +=1;
                };
            };
            if(a_evaluar.leer_tablero(i,j)==5){
                bool izquierda = true;
                bool derecha = true;
                bool arriba = true;
                bool abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i+k,j+k)==0){
                            puntaje_posibles +=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j+k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i-k,j-k)==0){
                            puntaje_posibles +=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j-k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j-k)==0){
                            puntaje_posibles +=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j-k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j+k)==0){
                            puntaje_posibles +=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j+k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                };
            };
            if(a_evaluar.leer_tablero(i,j)==6){
                bool izquierda = true;
                bool derecha = true;
                bool arriba = true;
                bool abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i,j+k)==0){
                            puntaje_posibles +=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i,j+k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i,j-k)==0){
                            puntaje_posibles +=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i,j-k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j)==0){
                            puntaje_posibles +=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j)==0){
                            puntaje_posibles +=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                };
                izquierda = true;
                derecha = true;
                arriba = true;
                abajo = true;
                for(int k=1;k<8;k++){
                    if(arriba){
                        if(a_evaluar.leer_tablero(i+k,j+k)==0){
                            puntaje_posibles +=1;
                        }else{
                            arriba=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j+k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(abajo){
                        if(a_evaluar.leer_tablero(i-k,j-k)==0){
                            puntaje_posibles +=1;
                        }else{
                            abajo=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j-k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(derecha){
                        if(a_evaluar.leer_tablero(i+k,j-k)==0){
                            puntaje_posibles +=1;
                        }else{
                            derecha=false;
                        };
                        if(a_evaluar.leer_tablero(i+k,j-k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                    if(izquierda){
                        if(a_evaluar.leer_tablero(i-k,j+k)==0){
                            puntaje_posibles +=1;
                        }else{
                            izquierda=false;
                        };
                        if(a_evaluar.leer_tablero(i-k,j+k)<-1){
                            puntaje_posibles +=1;
                        };
                    };
                };
            };
            if(a_evaluar.leer_tablero(i,j)==7){
                if(a_evaluar.leer_tablero(i+1,j+1)==0 || a_evaluar.leer_tablero(i+1,j+1)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i+1,j)==0 || a_evaluar.leer_tablero(i+1,j)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i+1,j-1)==0 || a_evaluar.leer_tablero(i+1,j-1)<-1){
                    puntaje_posibles +=1;
                };//////////////////////
                if(a_evaluar.leer_tablero(i-1,j+1)==0 || a_evaluar.leer_tablero(i-1,j+1)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i-1,j)==0 || a_evaluar.leer_tablero(i-1,j)<-1){
                    puntaje_posibles +=1;
                };
                if(a_evaluar.leer_tablero(i-1,j-1)==0 || a_evaluar.leer_tablero(i-1,j-1)<-1){
                    puntaje_posibles +=1;
                };///////////////////////
                if(a_evaluar.leer_tablero(i,j+1)==0 || a_evaluar.leer_tablero(i,j+1)<-1){
                    puntaje_posibles +=1;
                }
                if(a_evaluar.leer_tablero(i,j-1)==0 || a_evaluar.leer_tablero(i,j-1)<-1){
                    puntaje_posibles +=1;
                }
            }
        }
    }
    int puntaje_jaque = 0;
    if(a_evaluar.leer_turno() == BLANCO){
        if(jaque(a_evaluar)){
            puntaje_jaque -= 100;
        }
    }
    if(a_evaluar.leer_turno() == NEGRO){
        if(jaque(a_evaluar)){
            puntaje_jaque += 100;
        }
    }
    return puntaje_material+puntaje_posibles+puntaje_jaque;
}


bool jaque(tablero tablero_a_buscar){
    if(tablero_a_buscar.leer_turno() == NEGRO){
        for(int i=2;i<10;i++){
            for(int j=2;j<10;j++){
                if(tablero_a_buscar.leer_tablero(i,j)==-2){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)== 7){
                        return true;
                    }
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)== 7){
                        return true;
                    }
                }
                if(tablero_a_buscar.leer_tablero(i,j)==-3){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-4){
                    if(tablero_a_buscar.leer_tablero(i+2,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+2,j-1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j-1)==7){
                        return true;
                    };//////////////////////////////////////////////////////////////////////////////
                    if(tablero_a_buscar.leer_tablero(i+1,j+2)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-2)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j+2)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-2)==7){
                        return true;
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-5){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-6){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==7){
                                return true;
                            };
                        };
                    };
                    izquierda = true;
                    derecha = true;
                    arriba = true;
                    abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==-7){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)==7){
                        return true;
                    };//////////////////////
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j+1)==7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j-1)==7){
                        return true;
                    }
                }
            }
        }
    }
    if(tablero_a_buscar.leer_turno() == BLANCO){
        for(int i=2;i<10;i++){
            for(int j=2;j<10;j++){
                if(tablero_a_buscar.leer_tablero(i,j)==2){
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)== -7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)== -7){
                        return true;
                    }
                };
                if(tablero_a_buscar.leer_tablero(i,j)==3){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==-7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==4){
                    if(tablero_a_buscar.leer_tablero(i+2,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+2,j-1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-2,j-1)==-7){
                        return true;
                    };//////////////////////////////////////////////////////////////////////////////
                    if(tablero_a_buscar.leer_tablero(i+1,j+2)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-2)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j+2)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-2)==-7){
                        return true;
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==5){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==-7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==6){
                    bool izquierda = true;
                    bool derecha = true;
                    bool arriba = true;
                    bool abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j)==-7){
                                return true;
                            };
                        };
                    };
                    izquierda = true;
                    derecha = true;
                    arriba = true;
                    abajo = true;
                    for(int k=1;k<8;k++){
                        if(arriba){
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==0){
                            }else{
                                arriba=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j+k)==-7){
                                return true;
                            };
                        };
                        if(abajo){
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==0){
                            }else{
                                abajo=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j-k)==-7){
                                return true;
                            };
                        };
                        if(derecha){
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==0){
                            }else{
                                derecha=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i+k,j-k)==-7){
                                return true;
                            };
                        };
                        if(izquierda){
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==0){
                            }else{
                                izquierda=false;
                            };
                            if(tablero_a_buscar.leer_tablero(i-k,j+k)==-7){
                                return true;
                            };
                        };
                    };
                };
                if(tablero_a_buscar.leer_tablero(i,j)==7){
                    if(tablero_a_buscar.leer_tablero(i+1,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i+1,j-1)==-7){
                        return true;
                    };//////////////////////
                    if(tablero_a_buscar.leer_tablero(i-1,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i-1,j-1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j+1)==-7){
                        return true;
                    };
                    if(tablero_a_buscar.leer_tablero(i,j-1)==-7){
                        return true;
                    }
                }
            }
        }
    }
}


void posibles::addnew(mov movimiento, int puntaje, int ply, int max_ply, int color){
    //printf("funcion llamada lpm\n");
    if(movimiento.leer_tipo()!=-1){
        if(ply == max_ply){
            if(cont_mejores_movimientos==0){
                mejores_movimientos[cont_mejores_movimientos][ply]=movimiento;
                mejores_movimientos[cont_mejores_movimientos+1][ply]=movimiento;
                valores_mejores_movimientos[cont_mejores_movimientos]=puntaje;
                valores_mejores_movimientos[cont_mejores_movimientos+1]=puntaje;
                mejor_movimiento = puntaje;
                cont_mejores_movimientos = 1;
                printf("a1\n");
            }else{
                for(int i=ply;i>=0;i--){
                    mejores_movimientos[cont_mejores_movimientos][i] = mejores_movimientos[cont_mejores_movimientos-1][i];
                }
                mejores_movimientos[cont_mejores_movimientos+1][ply] = movimiento;//guarda el indice en indice_mejoresjugadas en el indice uno mayor al anterior
                valores_mejores_movimientos[cont_mejores_movimientos+1]= puntaje;
                mejores_movimientos[cont_mejores_movimientos][ply] = movimiento;//guarda el indice en indice_mejoresjugadas en el indice uno mayor al anterior
                valores_mejores_movimientos[cont_mejores_movimientos]= puntaje;
                if(color==NEGRO){
                    if(mejor_movimiento>puntaje){
                        for(int i=ply;i>=0;i--){
                            mejores_movimientos[cont_mejores_movimientos+1][i].escribir(0,0,0,0,-1);
                        }
                        valores_mejores_movimientos[cont_mejores_movimientos+1]=0;
                    }
                    if(mejor_movimiento==puntaje){//si lajugada es igual a la mejor..
                        cont_mejores_movimientos += 1;//
                    }
                    if(mejor_movimiento<puntaje){//si es mejor que la mejor jugada...
                        mejor_movimiento=puntaje;//la mejor jugada es sustituida
                        for(int i=ply;i>=0;i--){
                            mejores_movimientos[0][i] = mejores_movimientos[cont_mejores_movimientos+1][i];
                        }//guarda el indice en indice_mejoresjugadas en el indice uno mayor al anterior
                        cont_mejores_movimientos = 1;//reinicia el contador de validas
                        valores_mejores_movimientos[0]= puntaje;
                        for(int j = 2; j<=200; j++){
                            for(int k =0; k<=6; k++){
                                //un for para recorrer todas las "mejores" encontradas hasta ahora
                                mejores_movimientos[j][k].escribir(0,0,0,0,-1);//busca todas las jugadas iguales a la mejor anterior y la anula a todas
                                valores_mejores_movimientos[j]=0;//anula el valor
                            }
                        }
                    }
                }
                if(color==BLANCO){
                    if(mejor_movimiento<puntaje){
                        for(int i=ply;i>=0;i--){
                            mejores_movimientos[cont_mejores_movimientos+1][i].escribir(0,0,0,0,-1);
                        }
                        valores_mejores_movimientos[cont_mejores_movimientos+1]=0;
                    }
                    if(mejor_movimiento==puntaje){//si lajugada es igual a la mejor..
                        cont_mejores_movimientos += 1;//
                    }
                    if(mejor_movimiento>puntaje){//si es mejor que la mejor jugada...
                        mejor_movimiento=puntaje;//la mejor jugada es sustituida
                        for(int i=ply;i>=0;i--){
                            mejores_movimientos[0][i] = mejores_movimientos[cont_mejores_movimientos+1][i];
                        }//guarda el indice en indice_mejoresjugadas en el indice uno mayor al anterior
                        cont_mejores_movimientos = 1;//reinicia el contador de validas
                        valores_mejores_movimientos[0]= puntaje;
                        for(int j = 2; j<=200; j++){
                            for(int k =0; k<=6; k++){
                                //un for para recorrer todas las "mejores" encontradas hasta ahora
                                mejores_movimientos[j][k].escribir(0,0,0,0,-1);//busca todas las jugadas iguales a la mejor anterior y la anula a todas
                                valores_mejores_movimientos[j]=0;//anula el valor
                            }
                        }
                    }
                }
            }
        }else{
                if(cont_mejores_movimientos==0){
                    mejores_movimientos[cont_mejores_movimientos][ply] = movimiento;
                }else{
                    for(int i=ply-1;i>=0;i--){
                        mejores_movimientos[cont_mejores_movimientos][i] = mejores_movimientos[cont_mejores_movimientos-1][i];
                    }
                    mejores_movimientos[cont_mejores_movimientos][ply]=movimiento;
                    for(int i=ply-1;i>=0;i--){
                        mejores_movimientos[cont_mejores_movimientos+1][i] = mejores_movimientos[cont_mejores_movimientos+1-1][i];
                    }
                    mejores_movimientos[cont_mejores_movimientos+1][ply]=movimiento;
                }
            }
        }
        //movimiento.leer();
        //printf("      ply = %d      contador = %d\n",ply,cont_mejores_movimientos);
        //this->leer();
        //system("pause");
}


posibles::posibles(){
    for(int i = 0;i<=200; i++){
        for(int j = 0;j<=6; j++){
            mejores_movimientos[i][j].escribir(0,0,0,0,-1);
        }
        valores_mejores_movimientos[i]=0;
    }
    mejor_movimiento = 0;
    cont_mejores_movimientos = 0;
}


posibles::~posibles(){};


mov posibles::leer_mejor(){
    if(cont_mejores_movimientos==0){
        printf("la jugada que espero que el contrario haga es:");
        mejores_movimientos[0][1].leer();
        return mejores_movimientos[0][0];
    }else{
        int aux = rand() % cont_mejores_movimientos;
        printf("la jugada que espero que el contrario haga es:");
        mejores_movimientos[0][1].leer();
        return mejores_movimientos[aux][0];
    }
}


void posibles::leer(){

    for(int i=0;i<=10;i++){
        for(int j=0;j<=6;j++){
            mejores_movimientos[i][j].leer();
            printf(" ");
        }
    printf("%d \n",valores_mejores_movimientos[i]);
    }
}
