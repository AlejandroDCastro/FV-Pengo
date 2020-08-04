#include "MazeGenerator.h"



int MazeGenerator::maze[mMax][nMax];



void MazeGenerator::agregarParOrdenado(int A[][2], int &k, int a, int b){
    bool Esta=false;
    for(int i=0;i<k;i++){
      if( a== A[i][0] && b==A[i][1]){
        Esta=true;
        break;
      }
    }
    if(Esta==false){
        A[k][0]=a;
        A[k][1]=b;
        k++;
    }
}

void MazeGenerator::obtenerParOrdenadoRandom(int a[][2], int &k, int &x, int &y){
    int index=rand()%k; //range 0 to k-1
    x=a[index][0];
    y=a[index][1];
    for(int i=index; i<k; i++){
        a[i][0]=a[i+1][0];
        a[i][1]=a[i+1][1];
    }
    k--;
}

void MazeGenerator::crearLaberinto( int M[][nMax],int m, int n){
    int ID_VECINOS_BLOQUEADOS[m+n][2],
        ID_VECINOS_DESBLOQUEADOS[4][2];
    int kb=0,kd=0, maxBlock=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            M[i][j]=BLOQUE;
        }
    }
    int Oi,Oj,Ii,Ij;
    Oi=1; Oj=1;
    M[Oi][Oj]=LIBRE;
    if(Oj-2>0   && M[Oi][Oj-2]==BLOQUE){
        agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi,Oj-2);
    }
    if(  Oj+2<n && M[Oi][Oj+2]==BLOQUE){
        agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi,Oj+2);
    }
    if(Oi-2>0 && M[Oi-2][Oj]==BLOQUE){
        agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi-2,Oj);
    }
    if(Oi +2< m && M[Oi+2][Oj]==BLOQUE){
        agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi+2,Oj);
    }
    int count =0;
    while(kb>0){
        if(maxBlock< kb){
            maxBlock=kb;
        }
        obtenerParOrdenadoRandom(ID_VECINOS_BLOQUEADOS, kb, Oi, Oj);//a) y g)
         //agregando vecinos desbloqueados
        kd=0;
         if(Oj-2>0   && M[Oi][Oj-2]==LIBRE){
            agregarParOrdenado(ID_VECINOS_DESBLOQUEADOS,kd,Oi,Oj-2);
        }
        if(  Oj+2<n && M[Oi][Oj+2]==LIBRE){
            agregarParOrdenado(ID_VECINOS_DESBLOQUEADOS,kd,Oi,Oj+2);
        }
        if(Oi-2>0 && M[Oi-2][Oj]==LIBRE){
            agregarParOrdenado(ID_VECINOS_DESBLOQUEADOS,kd,Oi-2,Oj);
        }
        if(Oi +2< m && M[Oi+2][Oj]==LIBRE){
            agregarParOrdenado(ID_VECINOS_DESBLOQUEADOS,kd,Oi+2,Oj);
        }
        obtenerParOrdenadoRandom(ID_VECINOS_DESBLOQUEADOS, kd, Ii, Ij);//c)
        if(Ii == Oi){//d)
            if(Ij < Oj){
                 M[Ii][Ij+1]=LIBRE;
            }else{
                 M[Ii][Oj+1]=LIBRE;
            }
        }else{
            if(Ii < Oi){
                  M[Ii+1][Ij]=LIBRE;
            }else{
                 M[Oi+1][Ij]=LIBRE;
            }
        }
	 M[Oi][Oj]=LIBRE; //f)
         //agregando vecinos bloqueados
        if(Oj-2>0   && M[Oi][Oj-2]==BLOQUE){
            agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi,Oj-2);
        }
        if(  Oj+2<n && M[Oi][Oj+2]==BLOQUE){
            agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi,Oj+2);
        }
        if(Oi-2>0 && M[Oi-2][Oj]==BLOQUE){
            agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi-2,Oj);
        }
        if(Oi +2< m && M[Oi+2][Oj]==BLOQUE){
            agregarParOrdenado(ID_VECINOS_BLOQUEADOS,kb,Oi+2,Oj);
        }
        count++;
    }
}



void MazeGenerator::generateRandomMaze(int **map)
{
    srand (time(NULL));

    int basic[mMax][nMax];

    crearLaberinto(maze,mMax, nMax);
    // copiamos la matriz
    for(int i=0;i<mMax;i++){
        for(int k=1; k<2; k++){
            for(int j=0;j<nMax;j++){
                if(j==0 || j== nMax-1){
                    basic[i][j] = (maze[i][j]==BLOQUE) ? 1 : 0;
                }else{
                    switch(maze[i][j]){
                        case BLOQUE:
                            basic[i][j] = 1;
                        break;
                        default:
                            basic[i][j] = 0;
                            break;
                    }
                }
            }
            if(i==0 || i==mMax-1){
                k=2;
            }
        }
    }

    // Fill the map
    for (int i=1; i<mMax-1; i++)
        for (int j=1; j<nMax-1; j++)
            map[i-1][j-1] = basic[i][j];
    
    // Pengo position is free
    map[6][6] = 0;
}
