/*
* Caminatas aleatorias de tres dimensiones
* Autor: Marcos Santiago Leonardo 
*/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
#define N 202 //2 más para promedio y desviación

caminatasD3(){
	Int_t simulaciones = 50;
	Int_t caminatas = 100;

	//Matriz de datos:
	//Penúltima columna = promedio
	//última columna = desviación estandar
 	Float_t matrizX[N][N];
 	Float_t matrizY[N][N];
	Float_t matrizZ[N][N];

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
		caminatas(i+1,caminatas,matrizX,matrizY,matrizZ);
		//Crea el script para graficar con gnuplot
		if((i+1) == 1){
			Out1<<"splot \"caminata1.csv\" using 1:2:3 t \"\""<<endl;
		}else{
			Out1<<"replot \"caminata"<<(i+1)<<".csv\" using 1:2:3 t \"\""<<endl;
		}
	}
	//Gráfica de promedios
	Out1<<"replot \"promedio.csv\" using 1:2:3"<<endl;
	//Gráfica de desviaciones
 	Out1<<"replot \"desvEstd.csv\" using 1:2:3"<<endl;
	// x = 0
	// Out1<<"replot 0"<<endl;
	Out1.close();

	calcula_promedio(matrizX,simulaciones,caminatas);
	calcula_promedio(matrizY,simulaciones,caminatas);
	calcula_promedio(matrizZ,simulaciones,caminatas);
	calcula_desvEst(matrizX,simulaciones,caminatas);
	calcula_desvEst(matrizY,simulaciones,caminatas);
	calcula_desvEst(matrizZ,simulaciones,caminatas);
	crear_archivo_prom(matrizX,matrizY,matrizZ,simulaciones,caminatas);
	crear_archivo_desv(matrizX,matrizY,matrizZ,simulaciones,caminatas);
}
// Calcula los pasos de una simulación
void caminatas(Int_t simulacion, Int_t caminatas, Float_t matrizX[][N], Float_t matrizY[][N], Float_t matrizZ[][N]){
	float x = 0;
	float y = 0;
	float z = 0;
	float vol; // volado
	
	/* Convertir entero a cadena para nombres de archivos*/
	stringstream stream = "";
	string numeroArc_archivo;
	stream << simulacion;
	numeroArc_archivo = stream.str();

	string nombre_archivo ="caminata"+stream.str()+".csv";
	Out2 = ofstream(nombre_archivo.c_str(),ios::out);
	// posición inicial
	Out2<<0<<" "<<0<<" "<<0<<endl; 
	matrizX[0][simulacion-1] = x;
	matrizY[0][simulacion-1] = y;
	matrizZ[0][simulacion-1] = z;
	for (Int_t i = 1; i < caminatas; i++)
		{
			//x
			vol = 0 + rand() % (1 +1 - 0);
			if(vol == 0 ){
				x--;
			}else{
				x++;
			}
			//y
			vol = 0 + rand() % (1 +1 - 0);
			if(vol == 0 ){
				y--;
			}else{
				y++;
			}
			//z
			vol = 0 + rand() % (1 +1 - 0);
			if(vol == 0 ){
				z--;
			}else{
				z++;
			}
			//En archivo
			Out2<<x<<" "<<y<<" "<<z<<endl;
			matrizX[i][simulacion-1] = x;
			matrizY[i][simulacion-1] = y;
			matrizZ[i][simulacion-1] = z;
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
	}
}
/*Calcula la desviación estándar de cada paso*/
void calcula_desvEst(Float_t m_sim[][N], Int_t simulaciones, Int_t caminatas){
	Float_t suma = 0; //Suma de desviaciones
	Float_t varianza = 0;
	// Out3 = ofstream("desvEst.csv",ios::out);
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
void crear_archivo_prom(Float_t m_X[][N], Float_t m_Y[][N], Float_t m_Z[][N], Int_t simulaciones, Int_t caminatas){
	Out3 = ofstream("promedio.csv",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		Out3<<m_X[i][simulaciones]<<" "<<m_Y[i][simulaciones]<<" "<<m_Z[i][simulaciones]<<endl;
	}
	Out3.close();
	printf("promedio.csv\n");
}
// Crear archivo con las desviaciones estándar de cada paso
void crear_archivo_desv(Float_t m_X[][N], Float_t m_Y[][N], Float_t m_Z[][N], Int_t simulaciones, Int_t caminatas){
	Out3 = ofstream("desvEstd.csv",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		Out3<<m_X[i][simulaciones+1]<<" "<<m_Y[i][simulaciones+1]<<" "<<m_Z[i][simulaciones+1]<<endl;
	}
	Out3.close();
	printf("desvEstd.csv\n");
}