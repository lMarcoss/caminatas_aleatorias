/*
* caminatas aleatorias en tres dimensiones
* Autor: Marcos Santiago Leonardo 
*/

#include <iostream>
#include <string>

#define C 10 // caminatas
#define P 100 // pasos

caminatasD3(){
	Int_t caminatas = C;
	Int_t pasos = P;
 	Float_t matrizX[P][C+2];
 	Float_t matrizY[P][C+2];
	Float_t matrizZ[P][C+2];

	/*
	* Cada fila guarda un paso de la simulación
	* Cada columna guarda una simulacion
	* : Se utiliza la penúltima columna para el promedio de los pasos de todas las caminatas
	* : Se utiliza la última columna para la desviación estándar de los pasos de todas las caminatas
	*/

	//caminatas
	Out1 = ofstream("graficos.txt",ios::out);
	for (Int_t i = 0; i < caminatas; i++)
	{
		//pasos por cada simulación
		pasos(i+1,pasos,matrizX,matrizY,matrizZ);
		//Crea el script para graficar con gnuplot
		if((i+1) == 1){
			Out1<<"splot \"caminata1.csv\" using 1:2:3 w l t \"\""<<endl;
		}else{
			Out1<<"replot \"caminata"<<(i+1)<<".csv\" using 1:2:3 w l t \"\""<<endl;
		}
	}
	//Gráfica de promedios
	Out1<<"replot \"promedio.csv\" using 1:2:3"<<endl;
	//Gráfica de desviaciones
 	Out1<<"replot \"desvEstd.csv\" using 1:2:3"<<endl;

	Out1.close();

	calcula_promedio(matrizX,caminatas,pasos);
	calcula_promedio(matrizY,caminatas,pasos);
	calcula_promedio(matrizZ,caminatas,pasos);
	calcula_desvEst(matrizX,caminatas,pasos);
	calcula_desvEst(matrizY,caminatas,pasos);
	calcula_desvEst(matrizZ,caminatas,pasos);
	crear_archivo(matrizX,matrizY,matrizZ,caminatas,pasos,"promedio.csv");
	crear_archivo(matrizX,matrizY,matrizZ,caminatas+1,pasos,"desvEstd.csv");
	calcula_distancia(matrizX,matrizY,matrizZ,caminatas,pasos);
	// histograma(matrizX,matrizY,matrizZ,caminatas,pasos);
}
// Calcula los pasos de una simulación
void pasos(Int_t simulacion, Int_t pasos, Float_t matrizX[][C+2], Float_t matrizY[][C+2], Float_t matrizZ[][C+2]){
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
	for (Int_t i = 1; i < pasos; i++)
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
			//en matriz
			matrizX[i][simulacion-1] = x;
			matrizY[i][simulacion-1] = y;
			matrizZ[i][simulacion-1] = z;
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
void calcula_distancia(Float_t m_X[][C+2], Float_t m_Y[][C+2], Float_t m_Z[][C+2], Int_t caminatas, Int_t pasos){
	Float_t X = 0;
	Float_t Y = 0;
	Float_t Z = 0;
	Float_t distancia = 0;
	Out3 = ofstream("distancia.csv",ios::out);
	
	for (Int_t i = 0; i < pasos; i++)
	{
		X = pow(m_X[i][caminatas+1],2);
		Y = pow(m_Y[i][caminatas+1],2);
		Z = pow(m_Z[i][caminatas+1],2);
		distancia = sqrt(X + Y + Z);
		Out3<<distancia<<endl;	
	}
	Out3.close();
	printf("distancia.csv\n");
}

// Crear archivos de promedios o desviaciones estándar
void crear_archivo(Float_t m_X[][C+2], Float_t m_Y[][C+2], Float_t m_Z[][C+2], Int_t caminatas, Int_t pasos, string archivo){
	Out3 = ofstream(archivo.c_str(),ios::out);
	for (Int_t i = 0; i < pasos; i++)
	{
		Out3<<m_X[i][caminatas]<<" "<<m_Y[i][caminatas]<<" "<<m_Z[i][caminatas]<<endl;
	}
	Out3.close();
	printf("%s\n",archivo.c_str());
}
/*Genera las histogramas de la simulación*/
void histograma(Float_t m_X[][C+2],Float_t m_Y[][C+2],Float_t m_Z[][C+2], Int_t caminatas, Int_t pasos){
	char nombre_gif[20];
	char Ext[4] = ".gif";
	TCanvas *C = new TCanvas();
	C -> cd();

	for (Int_t i = 0; i < pasos; i++)
	{
		sprintf(nombre_gif, "gif_%d%s",i+1,Ext);	
		TH3F* h2=new TH3F("h2","dimension3",i+1,-caminatas,caminatas,i+1,-caminatas,caminatas,i+1,-caminatas,caminatas);
		for (Int_t j = 0; j < caminatas; j++)
		{
			h2 -> Fill(m_X[i][j],m_Y[i][j],m_Z[i][j]);
		}
	h2-> Draw("box");
	C -> Update();	
	// C -> SaveAs(nombre_gif);
	}
}