void Draw_multi_graph(){

	const int NData = 4;
	int gColor[4] = {kBlue, kRed, kBlack, kGreen+2};
	int gMarker[NData] = { 24, 25, 26, 27}; 

	TString datainfo[NData][3] = { // rootfile name , gr name, legend 
		"Harris_SC_datapoint.root", "gr_harri_SC_0_Norm_par0" , "NSC(3,2) EKRT Old Param0 (eta/s=0.20)",
		"Harris_SC_datapoint.root", "gr_harri_SC_0_Norm_par1" , "NSC(3,2) EKRT Old Param1",
		"EKRT_eta_020_pt_NSC.root", "gr_harri_NSC_0_pt_1" , "NSC(3,2) EKRT New Param0 (eta/s=0.20)",
		"EKRT_eta_par1_pt_NSC.root", "gr_harri_NSC_0_pt_1" , "NSC(3,2) EKRT New Param1"
	};

	TFile *fin[NData];
	TGraphErrors *grs[NData];
	for(int i=0; i<NData; i++){
		fin[i] = new TFile( datainfo[i][0].Data(), "read"); 
		grs[i] = (TGraphErrors*)fin[i]->Get(datainfo[i][1].Data());
		grs[i]->SetMarkerStyle( gMarker[i] );
		grs[i]->SetMarkerColor( gColor[i] );
		grs[i]->SetLineColor( gColor[i] );
	}

	TH2D *href = new TH2D("href", "", 100, 0, 60, 100, -0.2, -0.01);
	href->SetStats(0);
	href->GetXaxis()->SetTitle("Centralities");
	href->GetYaxis()->SetTitle("SC(m,n)");
	href->Draw();
	TLegend *leg = new TLegend(0.1, 0.2, 0.5, 0.5, "", "brNDC");
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	for(int i=0; i<NData; i++){
		grs[i]->Draw("same pl");
		leg->AddEntry( grs[i], datainfo[i][2].Data(), "pl");
	}
	leg->Draw();
}
