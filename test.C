
void test(){

	
	const int cNX = 2; // number of pad along X
    const int cNY = 5; // number of pad along y
    double canvas_width = 800;
    double canvas_height = 1500;
    double canvas_margin_x = 10;
	double W = 0.47; //(pad width as ratio);
	double Xm = (1- cNX*W)/2 ; // xmargin
	double H = 0.19; // pad height as ratio;
	double Ym = (1- cNY*H)/2 ;


    TCanvas *c100 = new TCanvas("c100", "", canvas_width, canvas_height);
    TPad *pads[cNX][cNY];
    for(int ix=0; ix<cNX; ix++){
		for(int iy=0; iy<cNY; iy++){
			cout << Xm+ix*W << "\t" <<  Ym+iy*H << endl;
			pads[ix][iy] = new TPad(Form("p%d%d",ix, iy), "", 
									Xm + ix*W, 	Ym + iy * H,
									Xm + (ix+1)*W, Ym + (iy+1)*H,
									0, 0, 0 );
			if(ix==0) pads[ix][iy]->SetRightMargin(0);
			if(ix==1) pads[ix][iy]->SetLeftMargin(0);
			if(iy!=4) pads[ix][iy]->SetTopMargin(0);
			if(iy!=0) pads[ix][iy]->SetBottomMargin(0);
			pads[ix][iy]->Draw();
		}
	}


}
