/*
* caminatas aleatorias en dos dimensiones
* Autor: Marcos Santiago Leonardo 
*/

#include <iostream>
#include <string>

#define C 10 // caminatas
#define P 100 // pasos

caminatasD2(){
	Int_t caminatas = C;
	Int_t pasos = P;
 	Float_t matrizX[P][C+2];
 	Float_t matrizY[P][C+2];
	
	/*
	* Cada columna guarda una simulacion
	* Cada fila guarda un paso de la simulación
	* : Se utiliza la penúltima columna para el promedio de los pasos de todas las caminatas
	* : Se utiliza la última columna para la desviación estándar de los pasos de todas las caminatas
	*/

	//caminatas: Total de archivos a crear
	Out1 = ofstream("graficos.txt",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		//pasos por cada simulación
		pasos(i+1,pasos,matrizX,matrizY);
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
	
	Out1.close();

	calcula_promedio(matrizX,caminatas,pasos);
	calcula_promedio(matrizY,caminatas,pasos);
	calcula_desvEst(matrizX,caminatas,pasos);
	calcula_desvEst(matrizY,caminatas,pasos);
	crear_archivo(matrizX,matrizY,caminatas,pasos,"promedio.csv"); //Archivo de promedios
	crear_archivo(matrizX,matrizY,caminatas+1,pasos,"desvEstd.csv");
	calcula_distancia(matrizX,matrizY,caminatas,pasos);
	// histograma(matrizX,matrizY,caminatas,pasos);
}

// Calcula los pasos de una simulación
void pasos(Int_t simulacion, Int_t pasos, Float_t matrizX[][C+2], Float_t matrizY[][C+2]){
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
	for (Int_t i = 1; i < pasos; i++)
		{
			//Adelante o atrás
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

// Calcula el promedio de cada paso de todas las caminatas
void calcula_promedio(Float_t m_sim[][C+2], Int_t caminatas, Int_t pasos){
	Float_t suma = 0;
	Float_t promedio = 0;
	for (Int_t i = 0; i < pasos; i++)
	{
		suma = 0;
		for (Int_t j = 0; j < caminatas; j++)
		{
			suma = suma + m_sim[i][j];
		}
		m_sim[i][caminatas] = suma / caminatas;
	}
}

/*Calcula la desviación estándar de cada paso*/
void calcula_desvEst(Float_t m_sim[][C+2], Int_t caminatas, Int_t pasos){
	Float_t suma = 0; //Suma de desviaciones
	Float_t varianza = 0;
	for (Int_t i = 0; i < pasos; i++)
	{
		suma = 0;
		for (Int_t j = 0; j < caminatas; j++)
		{
			//Suma de desviación de cada xi --> ((xi-prom)^ 2)
			suma = suma + ((m_sim[i][j] - m_sim[i][caminatas]) * (m_sim[i][j] - m_sim[i][caminatas]));
		}
		varianza = suma / caminatas;
		//calcula la desviación estándar
		m_sim[i][caminatas+1] = sqrt(varianza);
	}
}

/*Calcula la distancia en cada paso*/
void calcula_distancia(Float_t m_X[][C+2], Float_t m_Y[][C+2], Int_t caminatas, Int_t pasos){
	Float_t X = 0;
	Float_t Y = 0;
	Float_t distancia = 0;
	Out3 = ofstream("distancia.csv",ios::out);
	
	for (Int_t i = 0; i < pasos; i++)
	{
		X = pow(m_X[i][caminatas+1],2);
		Y = pow(m_Y[i][caminatas+1],2);
		distancia = sqrt(X + Y);
		Out3<<distancia<<endl;	
	}
	Out3.close();
	printf("distancia.csv\n");
}

// Crear archivos de promedios o desviaciones estándar
void crear_archivo(Float_t m_X[][C+2], Float_t m_Y[][C+2], Int_t caminatas, Int_t pasos, string archivo){
	Out3 = ofstream(archivo.c_str(),ios::out);
	for (Int_t i = 0; i < pasos; i++)
	{
		Out3<<m_X[i][caminatas]<<" "<<m_Y[i][caminatas]<<endl;
	}
	Out3.close();
	printf("%s\n",archivo.c_str());
}

/*Se generan las histogramas*/
void histograma(Float_t m_X[][C+2],Float_t m_Y[][C+2], Int_t caminatas, Int_t pasos){
	char nombre_gif[20];
	char Ext[4] = ".gif";
	TCanvas *C = new TCanvas();
	C -> cd();

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
		
		TH2F* h2=new TH2F("h2","dimension2",i+1,-pasos,pasos,i+1,-pasos,pasos);
		for (Int_t j = 0; j < caminatas; j++)
		{
			h2 -> Fill(m_X[i][j],m_Y[i][j]);
		}
	h2-> Draw("SURF3");
	C -> Update();	
	C -> SaveAs(nombre_gif);
	}
}
