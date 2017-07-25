
TString strDataFile = "results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root";
TString strAMPTFile = "results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0250.root";

TGraphErrors *gr_SC;
TGraphErrors *gr_SC_norm;
TGraphErrors *gr_SC_AMPT;
TGraphErrors *gr_SC_norm_AMPT;

// check this we need <v2v2><v3v3> with Eta10 cut!
TGraphErrors *gr_v2v2;
TGraphErrors *gr_v3v3;
TGraphErrors *gr_v2v2_ampt; // <v2^2>
TGraphErrors *gr_v3v3_ampt; // <v3^2>

TGraphErrors *gr_SC_AMPT_Corr;
TGraphErrors *gr_C_factor;
TGraphErrors *gr_C_factor_ampt;

TGraphErrors *gr_ratio_before;
TGraphErrors *gr_ratio_after;
TGraphErrors *gr_C_ratio;

void Draw_QConly_DataAMPT(){
	cout << "loading" << endl;
	LoadSCResults();
	LoadAMPT();
	cout << "load done" << endl;
	CalAMPTCorr();
	cout << "correction done" << endl;
	gr_ratio_before = CalculateRatio( gr_SC_AMPT, gr_SC , 0);
	gr_ratio_after = CalculateRatio( gr_SC_AMPT_Corr, gr_SC, 0.7);
	gr_C_ratio = CalculateRatio( gr_C_factor_ampt, gr_C_factor, 0);
	

	// multi canvas
	TCanvas *c1 = new TCanvas("c1","c1", 500, 700);
	c1->Draw();

	TPad *upPad = new TPad("up","upper pad", 0, 0.3, 1, 1);
    TPad *lowPad = new TPad("low","lower pad", 0, 0, 1, 0.3);
	upPad->Draw();
	lowPad->Draw();

	upPad->cd();
	upPad->SetBottomMargin(0);

	TH2D *href = new TH2D("href", "", 100, 0, 52, 100,  -2.19e-6, 0.29e-6);
	href->GetYaxis()->SetTitle("SC(m,n) ");
	href->GetXaxis()->SetTitle("Centrality Percentile");
	href->GetYaxis()->SetTitleSize(0.04);
	href->GetYaxis()->SetTitleOffset(.8);
	href->GetYaxis()->SetLabelSize(0.035);
	href->SetStats(0);
	href->Draw();

	gr_SC->SetMarkerColor(kBlack);
	gr_SC->SetLineColor(kBlack);
	gr_SC->SetMarkerStyle(kOpenCircle);
	gr_SC_AMPT->SetMarkerColor(kRed);
	gr_SC_AMPT->SetLineColor(kRed);
	gr_SC_AMPT->SetMarkerStyle(kOpenSquare);

	gr_SC->Draw("same p");
	gr_SC_AMPT->Draw("same p");
	gr_SC_AMPT_Corr->Draw("same p");
	gr_SC_AMPT_Corr->Print();

	TLegend *leg = new TLegend( 0.15, 0.15, 0.5, 0.4, "ALICE Pb-Pb #sqrt{#it{s}}_{NN} = 2.76TeV","brNDC");
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->AddEntry( gr_SC, "SC(3,2)" , "p");
	leg->AddEntry( gr_SC_AMPT, "AMPT, default", "p");
	leg->AddEntry( gr_SC_AMPT_Corr, "AMPT x (<v_{2}^{2}><v_{3}^{2}>)_{Data} /  (<v_{2}^{2}><v_{3}^{2}>)_{AMPT} )", "p");
	leg->Draw();

	lowPad->cd();
	lowPad->SetTopMargin(0);	
	TH2D *href_low = new TH2D("href_low", "",100,  0, 52, 100, 0.2, 1.33);
	href_low->SetStats(0);
	href_low->GetYaxis()->SetTitle("Ratio  ");
	href_low->GetYaxis()->SetTitleSize(0.08);
	href_low->GetYaxis()->SetTitleOffset(0.4);
	href_low->Draw();

	TLine *line1 = new TLine( 0, 1, 52, 1);
	line1->Draw();	

	gr_ratio_before->SetMarkerColor(kRed);
	gr_ratio_before->SetLineColor(kRed);
	gr_ratio_before->SetMarkerStyle( kOpenSquare);	
	gr_ratio_before->Draw("same p");

	gr_ratio_after->SetMarkerColor(kBlue);
	gr_ratio_after->SetLineColor(kBlue);
	gr_ratio_after->SetMarkerStyle( kOpenDiamond);
	gr_ratio_after->Draw("same p");




	c1->SaveAs("SC32_Data_vs_AMPT_correction.eps");

	TCanvas *c2 = new TCanvas("c2","", 500, 700);
	c2->Draw();

	TPad *upPad2 = new TPad("up2","upper pad", 0, 0.3, 1, 1);
    TPad *lowPad2 = new TPad("low2","lower pad", 0, 0, 1, 0.3);
	upPad2->Draw();
	lowPad2->Draw();



	upPad2->cd();
	upPad2->SetBottomMargin(0);

	TH2D *href2 = new TH2D("href2", "", 100, 0, 52, 100, -1e-6, 10e-6);
	href2->GetXaxis()->SetTitle("Centrality Percentile");
	href2->GetYaxis()->SetTitleSize(0.04);
	href2->GetYaxis()->SetTitleOffset(.8);
	href2->GetYaxis()->SetLabelSize(0.035);
	href2->SetStats(0);
	href2->Draw();

	gr_C_factor->Draw("samepl");
	gr_C_factor_ampt->Draw("samepl");

	TLegend *leg2 = new TLegend( 0.15, 0.55, 0.5, 0.8, "ALICE Pb-Pb #sqrt{#it{s}}_{NN} = 2.76TeV","brNDC");
	leg2->SetFillStyle(0);
	leg2->SetBorderSize(0);
	leg2->AddEntry( gr_C_factor, "<v_{2}^{2}><v_{3}^{2}> , Data" , "p");
	leg2->AddEntry( gr_C_factor_ampt, "<v_{2}^{2}><v_{3}^{2}> , AMPT default", "p");
	leg2->Draw();

	lowPad2->cd();
	lowPad2->SetTopMargin(0);	

	TH2D *href2_ratio = new TH2D("href2_low", "", 100, 0, 52, 100, 0.2, 1.23 );
	href2_ratio->SetStats(0);
	href2_ratio->GetYaxis()->SetTitle("Ratio  ");
	href2_ratio->GetYaxis()->SetTitleSize(0.08);
	href2_ratio->GetYaxis()->SetTitleOffset(0.4);
	href2_ratio->Draw();
	line1->Draw();
	gr_C_ratio->SetMarkerStyle(kOpenCircle);
	gr_C_ratio->SetMarkerColor(kBlue);
	gr_C_ratio->Draw("same p");
		
	c2->SaveAs("SC32_C_factor.eps");
} 


void LoadSCResults(){
	cout << "start load data" << endl;
	TFile *fin_data = new TFile( Form("%s", strDataFile.Data()), "read");
	TString strGrSCName = "gr_SC_with_QC_3223";
	TString strGrNSCName = "gr_SC_norm_with_QC_3223";

	gr_SC = (TGraphErrors*)fin_data->Get( Form("%s", strGrSCName.Data() ) );
	gr_SC_norm = (TGraphErrors*)fin_data->Get( Form("%s", strGrNSCName.Data() ) );


	gr_v2v2 = (TGraphErrors*)fin_data->Get("gr_v2_QCeta10");
	gr_v3v3 = (TGraphErrors*)fin_data->Get("gr_v3_QCeta10");

}

void LoadAMPT(){
	cout << "start load ampt" << endl;
	cout << "use only ampt default , 13f3b " << endl;
	TFile *fin_ampt = new TFile( Form("%s", strAMPTFile.Data() ), "read" );
	TString strGrSCName = "gr_SC_with_QC_3223";
	TString strGrNSCName = "gr_SC_norm_with_QC_3223";

	gr_SC_AMPT = (TGraphErrors*)fin_ampt->Get( Form("%s", strGrSCName.Data() ));
	gr_SC_norm_AMPT = (TGraphErrors*)fin_ampt->Get( Form("%s", strGrNSCName.Data() ));

	gr_v2v2_ampt = (TGraphErrors*)fin_ampt->Get("gr_v2_QCeta10");
	gr_v3v3_ampt = (TGraphErrors*)fin_ampt->Get("gr_v3_QCeta10");

}

void CalAMPTCorr(){
	cout << "calculate AMPT correction" << endl;
	gr_SC_AMPT_Corr = new TGraphErrors();
	gr_C_factor = new TGraphErrors();
	gr_C_factor_ampt = new TGraphErrors();

	int Npoint = gr_SC->GetN();
	for(int ipoint =0; ipoint <Npoint; ipoint++){
		double x = gr_SC_AMPT->GetX()[ipoint] ;
		double ex = gr_SC_AMPT->GetEX()[ipoint] ;
		double y = gr_SC_AMPT->GetY()[ipoint] ;
		double ey = gr_SC_AMPT->GetEY()[ipoint] ;
//		double y = gr_SC_norm_AMPT->GetY()[ipoint];

		double v22 = gr_v2v2->GetY()[ipoint] ;
		double v33 = gr_v3v3->GetY()[ipoint] ;
		double v22_ampt = gr_v2v2_ampt->GetY()[ipoint] ;
		double v33_ampt = gr_v3v3_ampt->GetY()[ipoint] ;
		double eyv2 = gr_v2v2->GetEY()[ipoint] ;
		double eyv3 = gr_v3v3->GetEY()[ipoint] ;

		gr_C_factor->SetPoint( ipoint, x, v22*v22 *v33 *v33 );
		gr_C_factor_ampt->SetPoint( ipoint, x, v22_ampt * v22_ampt * v33_ampt *v33_ampt);

		double corr_y = y * v22 * v33 *v22 * v33 / (v22_ampt*v22_ampt*v33_ampt*v33_ampt) ;
//		double corr_y = y * v22 * v33 *v22 * v33 ;
		double corr_ey = TMath::Sqrt( ey*ey );
	
		gr_SC_AMPT_Corr->SetPoint( ipoint, x, corr_y );
		gr_SC_AMPT_Corr->SetPointError( ipoint, ex, corr_ey);			

		

	}
	gr_SC_AMPT_Corr->SetLineColor(kBlue);
	gr_SC_AMPT_Corr->SetMarkerColor(kBlue);
	gr_SC_AMPT_Corr->SetMarkerStyle(kOpenDiamond);

	gr_C_factor->SetLineColor(kBlue);
	gr_C_factor->SetMarkerColor(kBlue);
	gr_C_factor->SetMarkerStyle(kOpenCircle);
	gr_C_factor_ampt->SetLineColor(kRed);
	gr_C_factor_ampt->SetMarkerColor(kRed);
	gr_C_factor_ampt->SetMarkerStyle(kOpenSquare);



}

// CalculateRatio
TGraphErrors *CalculateRatio( TGraphErrors* gr1, TGraphErrors* gr2, double xshift){
        int NPoint = gr1->GetN();
        TGraphErrors *gr_ratio = new TGraphErrors( NPoint);
        TGraph ger( gr2->GetN(), gr2->GetX(), gr2->GetEY() ); // << Err estimation of gr2
        for(int i=0; i<NPoint; i++){
                double x = gr1->GetX()[i];
                double y1 = gr1->GetY()[i];
                double ey1 = gr1->GetEY()[i];  // << estimation of gr2's y value for x1
                double y2 = gr2->Eval(x);
                double ey2 = ger.Eval(x);
                double ratio = TMath::Abs( y1 / y2 );
                gr_ratio->SetPoint( i, x+xshift, ratio);
                gr_ratio->SetPointError( i, 0, ratio * TMath::Sqrt( ey1*ey1/y1/y1 + ey2*ey2/y2/y2 ));

        }
        return gr_ratio;
}
