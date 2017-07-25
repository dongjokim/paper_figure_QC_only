void Comparison_SC32_AMPTmodel(){

	const int NData = 7;
	int gColor = kBlue;
	int gMarker[NData] = { 24, 25, 26, 27, 28, 30, 20 }; 

	TString datainfo[NData][3] = { // rootfile name , gr name, legend 
		"Results/results_AMPT13f3aQC_JFFluc_KineOnly_Eta0408_Pt0250.root", "gr_SC_corr_0"		, "SC(3,2) with SP : AMPT13f3a #Delta#eta>0.8",
		"Results/results_AMPT13f3aQC_JFFluc_KineOnly_Eta0408_Pt0250.root", "gr_SC_with_QC_3223"	, "SC(3,2) with QC : AMPT13f3a #Delta#eta>0.8",
		"Results/results_AMPT13f3bQC_JFFluc_KineOnly_Eta0408_Pt0250.root", "gr_SC_corr_0"		, "SC(3,2) with SP : AMPT13f3b #Delta#eta>0.8",
		"Results/results_AMPT13f3bQC_JFFluc_KineOnly_Eta0408_Pt0250.root", "gr_SC_with_QC_3223"	, "SC(3,2) with QC : AMPT13f3b #Delta#eta>0.8",
		"Results/results_AMPT13f3cQC_JFFluc_KineOnly_Eta0408_Pt0250.root", "gr_SC_corr_0"		, "SC(3,2) with SP : AMPT13f3c #Delta#eta>0.8",
		"Results/results_AMPT13f3cQC_JFFluc_KineOnly_Eta0408_Pt0250.root", "gr_SC_with_QC_3223"	, "SC(3,2) with QC : AMPT13f3c #Delta#eta>0.8",
		"Results/Ante_DataPoint_20160130.root"							 , "gr_Ante_SC32"		, "SC(3,2) with QC (Anthony : AMPT13f3c)" 
	};

	TFile *fin[NData];
	TGraphErrors *grs[NData];
	for(int i=0; i<NData; i++){
		fin[i] = new TFile( datainfo[i][0].Data(), "read"); 
		grs[i] = (TGraphErrors*)fin[i]->Get(datainfo[i][1].Data());
		grs[i]->SetMarkerStyle( gMarker[i] );
		grs[i]->SetMarkerColor( gColor );
		grs[i]->SetLineColor( gColor );
	}

	TH2D *href = new TH2D("href", "", 100, 0, 60, 100, -3.e-6, 3.e-6);
	href->SetStats(0);
	href->GetXaxis()->SetTitle("Centralities");
	href->GetYaxis()->SetTitle("SC(m,n)");
	href->Draw();
	TLegend *leg = new TLegend(0.1, 0.6, 0.5, 0.88, "", "brNDC");
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	for(int i=0; i<NData; i++){
		grs[i]->Draw("same p");
		leg->AddEntry( grs[i], datainfo[i][2].Data(), "p");
	}
	leg->Draw();
	c1->SaveAs("figs/SC32_AMPTmodel.eps");
}
