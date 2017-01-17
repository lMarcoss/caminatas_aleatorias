/*
* Caminatas aleatorias de dos dimensiones
* Autor: Marcos Santiago Leonardo 
*/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
#define N 200 //2 más para promedio y desviación

caminatasD2(){
	Int_t simulaciones = 50;
	Int_t caminatas = 100;
 	Float_t matrizX[N][N+3];
 	Float_t matrizY[N][N];
	
	/*
	* Cada fila guarda un paso de la simulación
	* Cada columna guarda una simulacion
	* : La utiliza la penúltima columna para el promedio de los pasos de todas las simulaciones
	* : La utiliza la última columna para la desviación estándar de de los pasos de todas las simulaciones
	*/

	//Simulaciones
	Out1 = ofstream("graficos.txt",ios::out);
	for (Int_t i = 0; i < simulaciones; i++)
	{
		//caminatas por cada simulación
		caminatas(i+1,caminatas,matrizX,matrizY);
		//Crea el script para graficar con gnuplot
		if((i+1) == 1){
			Out1<<"plot \"caminata1.csv\" using 1:2 with lines t \"\""<<endl;
		}else{
			Out1<<"replot \"caminata"<<(i+1)<<".csv\" using 1:2 with lines t \"\""<<endl;
		}
	}
	//Gráfica de promedios
	Out1<<"replot \"promedio.csv\" using 1:2 with linespoints linetype 3 linewidth 2"<<endl;
	//Gráfica de desviaciones
	Out1<<"replot \"desvEstd.csv\" using 1:2 with linespoints linetype 2 linewidth 1"<<endl;
	//Gráfica de distancia
	Out1<<"replot \"distancia.csv\""<<endl;
	Out1.close();

	calcula_promedio(matrizX,simulaciones,caminatas);
	calcula_promedio(matrizY,simulaciones,caminatas);
	calcula_desvEst(matrizX,simulaciones,caminatas);
	calcula_desvEst(matrizY,simulaciones,caminatas);
	crear_archivo_prom(matrizX,matrizY,simulaciones,caminatas);
	crear_archivo_desv(matrizX,matrizY,simulaciones,caminatas);
	calcula_distancia(matrizX,matrizY,simulaciones,caminatas);
}
// Calcula los pasos de una simulación
void caminatas(Int_t simulacion, Int_t caminatas, Float_t matrizX[][N], Float_t matrizY[][N]){
	float x = 0;
	float y = 0;
	float vol; // volado
	
	/* Convertir entero a cadena para nombres de archivos*/
	stringstream stream = "";
	string numeroArc_archivo;
	stream << simulacion;
	numeroArc_archivo = stream.str();

	string nombre_archivo ="caminata"+stream.str()+".csv";
	Out2 = ofstream(nombre_archivo.c_str(),ios::out);
	// posición inicial
	Out2<<0<<" "<<0<<endl; 
	matrizX[0][simulacion-1] = x;
	matrizY[0][simulacion-1] = y;
	for (Int_t i = 1; i < caminatas; i++)
		{
			//Arriba o abajo
			vol = 0 + rand() % (1 +1 - 0);
			if(vol == 0 ){
				x--;
			}else{
				x++;
			}
			//izq o derecha
			vol = 0 + rand() % (1 +1 - 0);
			if(vol == 0 ){
				y--;
			}else{
				y++;
			}
			//En archivo
			Out2<<x<<" "<<y<<endl;
			matrizX[i][simulacion-1] = x;
			matrizY[i][simulacion-1] = y;
		}
	Out2.close();
	printf("%s\n",nombre_archivo.c_str());
}
// Calcula el promedio de cada paso de todas las simulaciones
void calcula_promedio(Float_t m_sim[][N], Int_t simulaciones, Int_t caminatas){
	Float_t suma = 0;
	Float_t promedio = 0;
	// Out3 = ofstream("promedio.csv",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		suma = 0;
		for (Int_t j = 0; j < simulaciones; j++)
		{
			suma = suma + m_sim[i][j];
		}
		m_sim[i][simulaciones] = suma / simulaciones;
		// Out3<<m_sim[i][simulaciones]<<endl;
	}
	// Out3.close();
	// printf("promedio.csv\n");
}
/*Calcula la desviación estándar de cada paso*/
void calcula_desvEst(Float_t m_sim[][N], Int_t simulaciones, Int_t caminatas){
	Float_t suma = 0; //Suma de desviaciones
	Float_t varianza = 0;
	for (Int_t i = 0; i < caminatas; i++)
	{
		suma = 0;
		for (Int_t j = 0; j < simulaciones; j++)
		{
			//Suma de desviación de cada xi --> ((xi-prom)^ 2)
			suma = suma + ((m_sim[i][j] - m_sim[i][simulaciones]) * (m_sim[i][j] - m_sim[i][simulaciones]));
		}
		//calcula la varianza
		varianza = suma / simulaciones;
		//calcula la desviación estándar
		m_sim[i][simulaciones+1] = sqrt(varianza);
	}
}
/*Calcula la distancia en cada paso*/
void calcula_distancia(Float_t m_X[][N], Float_t m_Y[][N], Int_t simulaciones, Int_t caminatas){
	Float_t X = 0;
	Float_t Y = 0;
	Float_t distancia = 0;
	Out3 = ofstream("distancia.csv",ios::out);
	
	for (Int_t i = 0; i < caminatas; i++)
	{
		X = pow(m_X[i][simulaciones+1],2);
		Y = pow(m_Y[i][simulaciones+1],2);
		distancia = X + Y;
		Out3<<distancia<<endl;	
	}

	Out3.close();
	printf("distancia.csv\n");
}
void imprime_matriz(Float_t m_sim[][N], Int_t simulaciones, Int_t caminatas){
	for (Int_t i = 0; i < caminatas; i++)
	{
		printf("\n");
		for (Int_t j = 0; j < (simulaciones + 1); j++)
		{
			if(j < simulaciones){
				printf("[%d]", m_sim[i][j]);
			}else{
				printf("[%.2f]", m_sim[i][j]);
			}
		}
	}
}
// Crear archivo con los promedios de cada paso
void crear_archivo_prom(Float_t m_X[][N], Float_t m_Y[][N], Int_t simulaciones, Int_t caminatas){
	Out3 = ofstream("promedio.csv",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		Out3<<m_X[i][simulaciones]<<" "<<m_Y[i][simulaciones]<<endl;
	}
	Out3.close();
	printf("promedio.csv\n");
}
// Crear archivo con las desviaciones estándar de cada paso
void crear_archivo_desv(Float_t m_X[][N], Float_t m_Y[][N], Int_t simulaciones, Int_t caminatas){
	Out3 = ofstream("desvEstd.csv",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		Out3<<m_X[i][simulaciones+1]<<" "<<m_Y[i][simulaciones+1]<<endl;
	}
	Out3.close();
	printf("desvEstd.csv\n");
}