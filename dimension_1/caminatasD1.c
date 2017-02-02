/*
* caminatas aleatorias en una dimensión
* Autor: Marcos Santiago Leonardo 
*/

#include <iostream>
#include <string>

#define C 10// caminatas
#define P 100 // pasos

caminatasD1(){
	Int_t caminatas = C;
	Int_t pasos = P;
 	Float_t m_sim[P][C+2]; 	

	/*
	* Cada fila guarda un paso de la simulación
	* Cada columna guarda una simulacion
	* : La utiliza la penúltima columna para el promedio de los pasos de todas las caminatas
	* : La utiliza la última columna para la desviación estándar de los pasos de todas las caminatas
	*/

	//caminatas
	Out1 = ofstream("graficos.txt",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		//pasos por cada simulación
		pasos(i+1,pasos,m_sim);
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

	calcula_promedio(m_sim,caminatas,pasos);
	calcula_desvEst(m_sim,caminatas,pasos);
	calcula_distancia(m_sim,caminatas,pasos);
	// imprime_matriz(m_sim,caminatas,pasos);
	// histograma(m_sim,caminatas,pasos);
}
// Calcula los pasos de una simulación
void pasos(Int_t simulacion, Int_t pasos, Float_t m_sim[][C+2]){
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
	for (Int_t y = 1; y < pasos; y++)
		{
			vol = 0 + rand() % (1 +1 - 0);
			if(vol == 0 ){
				x--; //izquierda
			}else{
				x++; //Derecha
			}
			Out2<<x<<endl;
			m_sim[y][simulacion-1] = x;
		}
	Out2.close();
	printf("%s\n",nombre_archivo.c_str());
}
void calcula_promedio(Float_t m_sim[][C+2], Int_t caminatas, Int_t pasos){
	Float_t suma = 0;
	Float_t promedio = 0;
	Out3 = ofstream("promedio.csv",ios::out);
	for (Int_t i = 0; i < pasos; i++)
	{
		suma = 0;
		for (Int_t j = 0; j < caminatas; j++)
		{
			suma = suma + m_sim[i][j];
		}
		m_sim[i][caminatas] = suma / caminatas;
		Out3<<m_sim[i][caminatas]<<endl;
	}
	Out3.close();
	printf("promedio.csv\n");
}
void calcula_desvEst(Float_t m_sim[][C+2], Int_t caminatas, Int_t pasos){
	Float_t suma = 0; //Suma de desviaciones
	Float_t varianza = 0; //Suma de desviaciones
	Out3 = ofstream("desvEst.csv",ios::out);
	for (Int_t i = 0; i < pasos; i++)
	{
		suma = 0;
		for (Int_t j = 0; j < caminatas; j++)
		{
			//Suma de desviación de cada xi --> ((xi-prom)^ 2)
			suma = suma + ((m_sim[i][j] - m_sim[i][caminatas]) * (m_sim[i][j] - m_sim[i][caminatas]));
		}
		//calcula la varianza
		varianza = suma / caminatas;
		//calcula la desviación estándar
		m_sim[i][caminatas+1] = sqrt(varianza);
		//guardar en archivo
		Out3<<m_sim[i][caminatas+1]<<endl;
	}
	Out3.close();
	printf("desvEst.csv\n");
}
/*Calcula la distancia en cada paso*/
void calcula_distancia(Float_t m_X[][C+2], Int_t caminatas, Int_t pasos){
	Float_t X = 0;
	Float_t distancia = 0;
	Out3 = ofstream("distancia.csv",ios::out);
	
	for (Int_t i = 0; i < pasos; i++)
	{
		X = pow(m_X[i][caminatas+1],2);
		distancia = sqrt(X) ;
		Out3<<distancia<<endl;	
	}

	Out3.close();
	printf("distancia.csv\n");
}
void histograma(Float_t m_X[][C+2], Int_t caminatas, Int_t pasos){
	char nombre_gif[20];
	char Ext[4] = ".gif";
	TCanvas *C= new TCanvas();
	C->cd();
	for (Int_t i = 0; i < pasos; i++)
	{
		if(i<10-1){
			sprintf(nombre_gif, "gif_000%d%s",i+1,Ext);	
		}else if(i < 100-1){
			sprintf(nombre_gif, "gif_00%d%s",i+1,Ext);	
		}else if(i < 1000-1){
			sprintf(nombre_gif, "gif_0%d%s",i+1,Ext);	
		}else{
			sprintf(nombre_gif, "gif_%d%s",i+1,Ext);	
		}

		TH1F* h1=new TH1F("h1","dimension1",i+1,-pasos,pasos);
		for (Int_t j = 0; j < caminatas; j++)
		{
			h1 -> Fill(m_X[i][j]);
		}
	h1->Draw();
	C->Update();	
	C -> SaveAs(nombre_gif);
	}
}
