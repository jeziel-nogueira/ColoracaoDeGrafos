# include <iostream>

using namespace std;

int **mat; // reserva ponteiro para ponteiro
int matX = 7;
int matY = 7;
int nCromatico;
int maiorGrau;
int aux = 0;

void definirGrauVertice();
int buscarVerticeGrauMaior();
void definirCorVertice();
void printRes();
void liberarMemoria();

void selecaoGrafo();
void petersen();
void setMatriz();

int main()
{
    selecaoGrafo();

    definirGrauVertice();
    definirCorVertice();
    printRes();

    cout << "Numero cromatio: " << nCromatico << endl;
    cout << "Maior grau: " << maiorGrau << endl;

    liberarMemoria();
    return 0;
}

void definirGrauVertice(){
    maiorGrau = 0;
    for(int i = 0; i < matX; i++){
        int grau = 0;        
        for (int j = 0; j < matY; j++){
            if(mat[i][j] > 0){
                grau++;
            }
        }
        mat[i][matY + 1] = grau;
        if(grau > maiorGrau){
            maiorGrau = grau;
        }
    }
}

int buscarVerticeGrauMaior(){
    // escolhe o vertice de maior grau ainda n colorido
    int grau = 0;
    int vert = -1;
    for(int i = 0; i < matX; i++){        
       if(mat[i][matY + 1] > grau && mat[i][matY + 2] == 0){
            grau = mat[i][matY + 1];
            vert = i;
        }
    }
    return vert;
}

void definirCorVertice(){
    bool colorido = false;// saber se o grafo esta totalmente clorido
    nCromatico = 0;
    while (!colorido)
    {   
        int x = buscarVerticeGrauMaior();// busca o indice do vertice de maior grau ainda n colorido
        if(x >= 0){
            int corDisponivel = 1;// escolhe a menor cor possivel
            bool essaCor = false;
            while (mat[x][matY + 2] == 0){// enquanto n receber uma cor
                
                if (!essaCor)
                {
                    essaCor = true;
                    for (int i = 0; i < matY; i++)
                    {
                        if(mat[x][i] > 0 && i != x){// se existe uma aresta entre entre o vertice x e i
                            if(mat[i][matY + 2] == corDisponivel){//se a cor atual esta sendo usada aumenta o valor da cor;
                                corDisponivel++;
                                essaCor = false;                         
                            }                
                        }             
                    }
                }else{
                    mat[x][matY + 2] = corDisponivel;
                    if(nCromatico < corDisponivel){
                        nCromatico = corDisponivel;
                    }
                    corDisponivel = 1;
                }
            }
        }else{
            colorido = true;
        }        
    }
    
}

void printRes(){
    cout << "Resultado:" << endl;
    for(int i = 0; i < matX; i++){
        cout << i << ": "; 
        for (int j = 0; j < matY; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << mat[i][matY + 1] << " | ";// mostrar o grau do vertice
        cout << mat[i][matY + 2] << " ";// mostrar a cor definida para o vertice
        cout << endl;
    }
}

void selecaoGrafo(){
    cout << "Qual grafo quer usar?" << endl;
    int selected = 0;
    cin >> selected;
 
    if(selected == 1){
        petersen();
    }else if (selected == 2)
    {
        setMatriz();
    }
    
}

void liberarMemoria(){
    for (int i = (matX -1); i >= 0; i--)
    {
        free(mat[i]);
    }
    free(mat);    
}


void setMatriz(){
    matX = 7; matY = 7;

            cout << "grafo de roda com sete vertices e doze arestas" << endl;
            int roda[matX][matY] = {
            {0, 1, 1, 1, 1, 1, 1}, 
            {1, 0, 1, 0, 0, 0, 0}, 
            {1, 1, 0, 1, 0, 0, 0}, 
            {1, 0, 1, 0, 1, 0, 0}, 
            {1, 0, 0, 1, 0, 1, 0}, 
            {1, 0, 0, 0, 1, 0, 1}, 
            {1, 0, 0, 0, 0, 1, 0}};
            mat = (int**)malloc(matX*sizeof(int*));
            for(int i = 0; i < matX; i++){
                mat[i] = (int*)malloc((matY + 2) * sizeof(int));
            }
            // populando a matriz com numeros 
            for(int i = 0; i < matX; i++){
                for (int j = 0; j < matY; j++)
                {
                    mat[i][j] = roda[i][j];
                }
                mat[i][matY+1] = 0; // limpar memoria para cor, sendo 0 uma cor n definida
                mat[i][matY+2] = 0; // limpar memoria para booleana; deixando 0 como !colorido
            }
}

void petersen(){
    matX = 10; matY = 10;
            cout << "grafo de Petersen com 10 vertices e 15 arestas" << endl;

            int petersen[10][10] = {{0, 1, 0, 0, 1, 1, 0, 0, 0, 0}, {1, 0, 1, 0, 0, 0, 1, 0, 0, 0}, {0, 1, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1, 1, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 1, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 1, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 1, 1, 0, 0}};
            // aloca espaço para um vetor de ponteiros do comprimento da var "matX"
            mat = (int**)malloc(matX*sizeof(int*));

            // aloca espaço para um vetor de inteiros apartir do vetor de ponteiros, adicionando 2 espaços a mais para controle do algoritmo(grau, cor)
            for(int i = 0; i < matX; i++){
                mat[i] = (int*)malloc((matY + 2) * sizeof(int));
            }
            // populando a matriz com numeros 
            for(int i = 0; i < matX; i++){
                for (int j = 0; j < matY; j++)
                {
                    mat[i][j] = petersen[i][j];
                }
                mat[i][matY+1] = 0; // limpar memoria para cor, sendo 0 uma cor n definida
                mat[i][matY+2] = 0; // limpar memoria para booleana; deixando 0 como !colorido
            }
}