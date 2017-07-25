
	// Color Settings //
	const int NData = 5;
	int gColor[NData] = {1,2,3,4,kViolet};
	int gMarker[NData] = { 24, 25, 26, 27, 28 }; 
	
	// Scale Settings // 
	double x_min = 0;
	double x_max = 52;
	double y_min = -0.5;
	double y_max = 1.5;


	// Data Settings //
	TString datainfo[NData][3] = { // rootfile name , gr name, legend 
		"../VISH_simdata/AMPT/resultSCR.root", 
			"SC32_1", "SC(3,2)",
		"../VISH_simdata/AMPT/resultSCR.root", 
			"SC42_1", "SC(4,2)",
		"../VISH_simdata/AMPT/resultSCR.root", 
			"SC52_1", "SC(5,2)",
		"../VISH_simdata/AMPT/resultSCR.root", 
			"SC53_1", "SC(5,3)",
		"../VISH_simdata/AMPT/resultSCR.root", 
			"SC43_1", "SC(4,3)"
	};

	// Legend Settings //
	double leg_x_pos = 0.2;
	double leg_y_pos = 0.6;
	double leg_x_end_pos = 0.7;
	double leg_y_end_pos = 0.8;
	TString strLeg = "VISH2+1, AMPT initialcondition, #eta/s=0.16";

	// Line Settings //
	bool Draw_line0 = kTRUE;


// Main Codes //
void NSC_VISH21_icAMPT_etaHigh(){
	TFile *fin[NData];
	TGraphErrors *grs[NData];
	for(int i=0; i<NData; i++){
		fin[i] = new TFile( datainfo[i][0].Data(), "read"); 
		grs[i] = (TGraphErrors*)fin[i]->Get(datainfo[i][1].Data());
		grs[i]->SetMarkerStyle( gMarker[i] );
		grs[i]->SetMarkerColor( gColor[i] );
		grs[i]->SetLineColor( gColor[i] );
	}

	TH2D *href = new TH2D("href", "", 100, x_min, x_max, 100, y_min, y_max);
	href->SetStats(0);
	href->GetXaxis()->SetTitle("Centralities");
	href->GetYaxis()->SetTitle("SC(m,n)");
	href->Draw();
	if(Draw_line0 == kTRUE){
		TLine *line_0 = new TLine( x_min, 0, x_max, 0 );
		line_0->Draw();
	}

	TLegend *leg = new TLegend(leg_x_pos, leg_y_pos, leg_x_end_pos, leg_y_end_pos, strLeg, "brNDC");
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	for(int i=0; i<NData; i++){
		grs[i]->Draw("same p");
		leg->AddEntry( grs[i], datainfo[i][2].Data(), "p");
	}
	leg->Draw();
	c1->SaveAs("NSC_VISH21_icAMPT_HighEta.eps");
}
