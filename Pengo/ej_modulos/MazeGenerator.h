/*=== Autor: Darwin E. Quiroz ===*/
/*=== Algoritmo de Prim ===*/
#pragma once
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

using namespace std;

const int nMax = 15;//impar
const int mMax=17;//impar
const int BLOQUE=0;
const int LIBRE=1;


class MazeGenerator {
    
    public:
        static void agregarParOrdenado(int [][2], int &, int , int );
        static void obtenerParOrdenadoRandom(int [][2], int &, int &, int &);
        static void crearLaberinto( int [][nMax],int , int );
        static bool comprobarPosiciones(int[][2]);
        static void generateRandomMaze(int** );


    private:
        static int maze[mMax][nMax];
        
};