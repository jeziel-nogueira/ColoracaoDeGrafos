# include <iostream>

using namespace std;

int **mat; // reserva ponteiro para ponteiro
int matX = 7;
int matY = 7;
int nCromatico;
int maiorGrau;
int aux = 0;
int totalArestas = 0;
int totalVertices = 0;

void definirGrauVertice();
int buscarVerticeGrauMaior();
void definirCorVertice();
bool escolherCor(int index, int cor);
void printRes();
void liberarMemoria();

void selecaoGrafo();
int somaVizinhosPintados(int index, int grau);
void konigsberg();
void petersen();
void singleton();
void hadamard();

int main()
{
    selecaoGrafo();

    definirGrauVertice();
    definirCorVertice();
    //printRes();

    cout << "Total de arestas encontrados: " << (totalArestas / 2) << endl;
    cout << "Total de vertices encontrados: " << totalVertices << endl;
    cout << "Numero cromatio identificado: " << nCromatico << endl;
    cout << "Maior grau de vertice identificado: " << maiorGrau << endl;

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
                totalArestas++;
            }
        }
        mat[i][matY + 1] = grau;
        if(grau > maiorGrau){
            maiorGrau = grau;
        }
    }
}

int buscarVerticeGrauMaior(){
    // escolhe o vertice de maior grau ainda n colorido com o maior numero de vizinhos ja coloridos
    int grau = 0;
    int vert = -1;
    int vizinhosColoridos = -1;
    for(int i = 0; i < matX; i++){
       if(mat[i][matY + 1] >= grau && mat[i][matY + 2] == 0){
            
            grau = mat[i][matY + 1];
            int saturacao = somaVizinhosPintados(i, grau);// quantas cores os vizinhos estao usando
            if( saturacao > vizinhosColoridos){
                vizinhosColoridos = saturacao;
                vert = i;
            }            
        }
    }    
    return vert;
}

int somaVizinhosPintados(int index, int grau){
    int coresDiferentes[grau] = {0};
    int saturacao = 0;
    
    for (int i = 0; i < matY; i++)
    {
        if(mat[index][i] > 0 && mat[i][matY + 2] > 0){

            int cor = mat[i][matY + 2];
            bool corNUsada = true;
            for (int x = 0; x < grau; x++)
            {
                if(coresDiferentes[x] == cor){
                    corNUsada = false;     
                }
            }
            if(corNUsada){
                coresDiferentes[saturacao] = mat[i][matY + 2];
                saturacao++;
            }
        }
    }
    return saturacao;
}

void definirCorVertice(){
    bool colorido = false;// saber se o grafo esta totalmente clorido
    nCromatico = 0;
    while (!colorido)
    {   
        int x = buscarVerticeGrauMaior();// busca o indice do vertice de maior grau ainda n colorido
        if(x >= 0){
            int corDisponivel = 1;// define a menor cor possivel

            while (mat[x][matY + 2] == 0){// enquanto nao receber uma cor
                bool aux = escolherCor(x , corDisponivel);
                if (aux)
                {                    
                    mat[x][matY + 2] = corDisponivel;
                    if(corDisponivel > nCromatico){
                        nCromatico = corDisponivel;
                    }
                    totalVertices ++;
                }else{
                    corDisponivel++;
                }
            }
        }else{
            colorido = true;
        }        
    }
    
}

bool escolherCor(int index, int cor){
     for (int i = 0; i < matY; i++)
     {
        if(mat[index][i] > 0 && mat[i][(matY + 2)] == cor ){
            return false;
        }
     }     
     return true;
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
        konigsberg();
    }else if (selected == 2)    {
        petersen();

    }else if(selected == 3){
        singleton();

    }else if(selected == 4){
        hadamard();

    }else{
        cout << "Opcao nao encontrada." << endl;
        selecaoGrafo();
    }
    
}

void liberarMemoria(){
    for (int i = (matX -1); i >= 0; i--)
    {
        free(mat[i]);
    }
    free(mat);    
}


void konigsberg(){
    matX = 4; matY = 4;

            cout << "grafo Sete pontes de Konigsberg com 4 vertices e 5 arestas" << endl;
            //fonte: https://pt.wikipedia.org/wiki/Sete_pontes_de_K%C3%B6nigsberg
            
            int pontes[matX][matY] = {
            {0, 1, 1, 1}, 
            {1, 0, 1, 0}, 
            {1, 1, 0, 1}, 
            {1, 0, 1, 0}};
            mat = (int**)malloc(matX*sizeof(int*));
            for(int i = 0; i < matX; i++){
                mat[i] = (int*)malloc((matY + 2) * sizeof(int));
            }
            // populando a matriz com numeros 
            for(int i = 0; i < matX; i++){
                for (int j = 0; j < matY; j++)
                {
                    mat[i][j] = pontes[i][j];
                }
                mat[i][matY+1] = 0; // limpar memoria para cor, sendo 0 uma cor n definida
                mat[i][matY+2] = 0; // limpar memoria para booleana; deixando 0 como !colorido
            }
}

void petersen(){
    matX = 10; matY = 10;
            cout << "grafo 3 de Petersen com 10 vertices e 15 arestas" << endl;
            //fonte: https://pt.wikipedia.org/wiki/Grafo_de_Petersen

            int petersen[10][10] = {
            {0, 1, 0, 0, 1, 1, 0, 0, 0, 0}, 
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 0}, 
            {0, 1, 0, 1, 0, 0, 0, 1, 0, 0}, 
            {0, 0, 1, 0, 1, 0, 0, 0, 1, 0}, 
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, 
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0}, 
            {0, 1, 0, 0, 0, 0, 0, 0, 1, 1}, 
            {0, 0, 1, 0, 0, 1, 0, 0, 0, 1}, 
            {0, 0, 0, 1, 0, 1, 1, 0, 0, 0}, 
            {0, 0, 0, 0, 1, 0, 1, 1, 0, 0}};
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

void singleton(){
    matX = 50; matY = 50;
            cout << "grafo  Hoffman-Singleton com 50 vertices e 175 arestas" << endl;
            //fonte: https://www.distanceregular.org/graphs/hoffmansingleton.html

            int singleton[matX][matY] = { { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 1 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 1, 0 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 
      0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 
      1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 
      1, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
      0, 1, 1 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
      1, 1, 0 }, 
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
      0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 
      0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 
      0, 0, 0 }, 
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
      1, 0, 1 }, 
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
      0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 
      0, 0, 0 }, 
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 
      0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
      0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 
      0, 1, 0 }, 
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
      0, 0, 1 }, 
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 
      0, 0, 1 }, 
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
      1, 0, 0 }, 
  { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 
      0, 0, 0 }, 
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
      0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
      1, 0, 0 }, 
  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
      0, 1, 0 }, 
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 
      0, 1, 0 }, 
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 
      0, 0, 1 }, 
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      1, 0, 0 }, 
  { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
      0, 0, 1 }, 
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 
      0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      1, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
      0, 1, 0 }, 
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 
      0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
      1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 
      1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 } };
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
                    mat[i][j] = singleton[i][j];
                }
                mat[i][matY+1] = 0; // limpar memoria para cor, sendo 0 uma cor n definida
                mat[i][matY+2] = 0; // limpar memoria para booleana; deixando 0 como !colorido
            }
    
}

void hadamard(){
    matX = 14; matY = 14;
            cout << "grafo de incidência de Hadamard por Heawood com 14 vertices e 21 arestas" << endl;
            // fonte: https://www.distanceregular.org/graphs/heawood.html

            int Hadamard[14][14] = {
                {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0},
                {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};
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
                    mat[i][j] = Hadamard[i][j];
                }
                mat[i][matY+1] = 0; // limpar memoria para cor, sendo 0 uma cor n definida
                mat[i][matY+2] = 0; // limpar memoria para booleana; deixando 0 como !colorido
            }
}
