/*
* Caminatas aleatorias de una dimensión
* Autor: Marcos Santiago Leonardo 
*/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
#define N 2002 //2 más para promedio y desviación

caminatasD1(){

	Int_t simulaciones = 10;
	Int_t caminatas = 100;
	Float_t m_sim[N][N];

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
		caminatas(i+1,caminatas,m_sim);
		//Crea el script para graficar con gnuplot
		if((i+1) == 1){
			Out1<<"plot \"caminata1.csv\" with lines t \"\""<<endl;
		}else{
			Out1<<"replot \"caminata"<<(i+1)<<".csv\" with lines t \"\""<<endl;
		}
	}
	//Gráfica de promedios
	Out1<<"replot \"promedio.csv\" with linespoints linetype 3 linewidth 2"<<endl;
	//Gráfica de desviaciones
	Out1<<"replot \"desvEst.csv\" with linespoints linetype 2 linewidth 1"<<endl;
	// x = 0
	Out1<<"replot 0"<<endl;
	Out1.close();

	calcula_promedio(m_sim,simulaciones,caminatas);
	calcula_desvEst(m_sim,simulaciones,caminatas);
	calcula_distancia(m_sim,simulaciones,caminatas);
	// imprime_matriz(m_sim,simulaciones,caminatas);
}

// Calcula los pasos de una simulación
void caminatas(Int_t simulacion, Int_t caminatas, Float_t m_sim[][N]){
	Int_t x = 0;
	Float_t vol; // volado

	/* Convertir entero a cadena para nombres de archivos*/
	stringstream stream;
	string numeroArc_archivo;
	stream << simulacion;
	numeroArc_archivo = stream.str();

	string nombre_archivo ="caminata"+stream.str()+".csv";
	Out2 = ofstream(nombre_archivo.c_str(),ios::out);
	Out2<<0<<endl; // posición inicial
	m_sim[0][simulacion-1] = x;
	for (Int_t y = 1; y < caminatas; y++)
		{
			vol = 0 + rand() % (1 +1 - 0);
			if(vol == 0 ){
				x--;
			}else{
				x++;
			}
			Out2<<x<<endl;
			m_sim[y][simulacion-1] = x;
		}
	Out2.close();
	printf("%s\n",nombre_archivo.c_str());
}

void calcula_promedio(Float_t m_sim[][N], Int_t simulaciones, Int_t caminatas){
	Float_t suma = 0;
	Float_t promedio = 0;
	Out3 = ofstream("promedio.csv",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		suma = 0;
		for (Int_t j = 0; j < simulaciones; j++)
		{
			suma = suma + m_sim[i][j];
		}
		m_sim[i][simulaciones] = suma / simulaciones;
		Out3<<m_sim[i][simulaciones]<<endl;
	}
	Out3.close();
	printf("promedio.csv\n");
}
void calcula_desvEst(Float_t m_sim[][N], Int_t simulaciones, Int_t caminatas){
	Float_t suma = 0; //Suma de desviaciones
	Float_t varianza = 0; //Suma de desviaciones
	Out3 = ofstream("desvEst.csv",ios::out);
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
		//guardar en archivo
		Out3<<m_sim[i][simulaciones+1]<<endl;
	}
	Out3.close();
	printf("desvEst.csv\n");
}
/*Calcula la distancia en cada paso*/
void calcula_distancia(Float_t m_X[][N], Int_t simulaciones, Int_t caminatas){
	Float_t X = 0;
	Float_t distancia = 0;
	Out3 = ofstream("distancia.csv",ios::out);
	
	for (Int_t i = 0; i < caminatas; i++)
	{
		X = pow(m_X[i][simulaciones+1],2);
		distancia = X ;
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