ran(){
	TRandom3 R(0);

	char Ext[4] = ".gif";

	Float_t V;
	Float_t PosProm;
	Float_t PosSig;
	Int_t X;
	Int_t NRW = 600; // <800
	Int_t NStep = 1000; //<2000

	Int_t RanA[2000][800] = {0};
	Int_t DistA[2000][800] = {0};
	Int_t Dist[2000][800] = {0};

	TCanvas *C = new TCanvas();
	C-> cd();

	Out1 = ofstream("Caminatas2D.csv",ios::out);
	Out2 = ofstream("CaminatasDist.csv",ios::out);


	for (Int_t j = 0; j < NStep; j++)
	{
		V = R.Rndm();
		if(V < 0.5){

		}else{

		}
	}

	for (Int_t i = 0; i < NStep; i++)
	{
		Xmin = 0; Xmax = 0;
		/* code */
	}

	for (Int_t j = 0; j < NRW; j++)
	{
		h -> Fill(RanAX[i][j],RanAY[i][j]);
	}
	PosProm = h -> GetMean();
	PosSig = h -> GetRMS();
	cout<<Xmin << " " << Xmax << endl;
	TH1

		sprintf(GifNam, "%s%04d%s",Nam,i+1,Ext);
		C -> SaveAs(GifNam);
		}
		h -> Delete();
		hDist -> Delete();
	}

	Out1.close();
	Out2.close();
}