enum {kAMPTdefault, kAMPTstON, kAMPTstOnHrOff, kNAMPT};
bool draw_ampt[kNAMPT] = {1,1,1};

bool draw_old_ekrt[5] = {1,1,1,1,1};
bool draw_ekrt[2] = {1, 1};

TString strDataFile = "results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root";
TString strAMPTFile[kNAMPT] = {
			"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0250.root",
			"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0250.root",
			"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0250.root"}

TGraphErrors *gr_SC;
TGraphErrors *gr_SC_norm;
TGraphErrors *gr_SC_AMPT[kNAMPT];
TGraphErrors *gr_SC_norm_AMPT[kNAMPT];

// check this we need <v2v2><v3v3> with Eta10 cut!
TGraphErrors *gr_v2v2;
TGraphErrors *gr_v3v3;
TGraphErrors *gr_v2v2_ampt[kNAMPT]; // <v2^2>
TGraphErrors *gr_v3v3_ampt[kNAMPT]; // <v3^2>

TGraphErrors *gr_C_factor;
TGraphErrors *gr_C_factor_ampt[kNAMPT];
TGraphErrors *gr_C_ratio[kNAMPT];

void Draw_vn2vm2(){
	cout << "loading" << endl;
	LoadSCResults();
	LoadAMPT();
	cout << "load done" << endl;
	CalAMPTCorr();
	cout << "correction done" << endl;

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
	for(int i=0; i<kNAMPT; i++){
	gr_C_factor_ampt[i]->Draw("samepl");
	}

	TLegend *leg2 = new TLegend( 0.1, 0.65, 0.8, 0.85, "ALICE Pb-Pb #sqrt{#it{s}}_{NN} = 2.76TeV","brNDC");
	leg2->SetFillStyle(0);
	leg2->SetBorderSize(0);
	leg2->AddEntry( gr_C_factor, "<v_{2}^{2}><v_{3}^{2}> , Data" , "p");
	leg2->AddEntry( gr_C_factor_ampt[0], "<v_{2}^{2}><v_{3}^{2}> , AMPT default", "p");
	leg2->AddEntry( gr_C_factor_ampt[1], "<v_{2}^{2}><v_{3}^{2}> , AMPT String Melting", "p");
	leg2->AddEntry( gr_C_factor_ampt[2], "<v_{2}^{2}><v_{3}^{2}> , AMPT String Melting w/o hadronic rescattering", "p");
	leg2->Draw();

	lowPad2->cd();
	lowPad2->SetTopMargin(0);	

	TH2D *href2_ratio = new TH2D("href2_low", "", 100, 0, 52, 100, 0.2, 2 );
	href2_ratio->SetStats(0);
	href2_ratio->GetYaxis()->SetTitle("Ratio  ");
	href2_ratio->GetYaxis()->SetTitleSize(0.08);
	href2_ratio->GetYaxis()->SetTitleOffset(0.4);
	href2_ratio->Draw();
	TLine *line1 = new TLine( 0, 1, 52, 1);
	line1->Draw();
	for(int i=0; i<kNAMPT; i++){
	gr_C_ratio[i] = CalculateRatio( gr_C_factor_ampt[i], gr_C_factor, i );

	gr_C_ratio[i]->SetMarkerStyle(kOpenSquare);
	gr_C_ratio[i]->SetLineColor(2+i);
	gr_C_ratio[i]->SetMarkerColor(2+i);
	
	gr_C_ratio[i]->Draw("same pl");
	}	
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

	TFile *fin_ampt[kNAMPT];
	TString strGrSCName = "gr_SC_with_QC_3223";
	TString strGrNSCName = "gr_SC_norm_with_QC_3223";

	for(int i=0; i<kNAMPT; i++){
	fin_ampt[i] = new TFile( Form("%s", strAMPTFile[i].Data() ), "read" );

	gr_SC_AMPT[i] = (TGraphErrors*)fin_ampt[i]->Get( Form("%s", strGrSCName.Data() ));
	gr_SC_norm_AMPT[i] = (TGraphErrors*)fin_ampt[i]->Get( Form("%s", strGrNSCName.Data() ));

	gr_v2v2_ampt[i] = (TGraphErrors*)fin_ampt[i]->Get("gr_v2_QCeta10");
	gr_v3v3_ampt[i] = (TGraphErrors*)fin_ampt[i]->Get("gr_v3_QCeta10");
	}

}

void CalAMPTCorr(){

		cout << "data part" << endl;	
		gr_C_factor = new TGraphErrors();
		int Npoint = gr_SC->GetN();
		for(int ipoint =0; ipoint <Npoint; ipoint++){
				double x = gr_SC->GetX()[ipoint] ;
				double v22 = gr_v2v2->GetY()[ipoint] ;
				double v33 = gr_v3v3->GetY()[ipoint] ;
				double eyv2 = gr_v2v2->GetEY()[ipoint] ;
				double eyv3 = gr_v3v3->GetEY()[ipoint] ;

				gr_C_factor->SetPoint( ipoint, x, v22*v22 *v33 *v33 );
		}
		gr_C_factor->SetLineColor(kBlack);
		gr_C_factor->SetMarkerColor(kBlack);
		gr_C_factor->SetMarkerStyle(kFullCircle);

		cout << "calculate AMPT correction" << endl;
		for(int i=0; i<kNAMPT; i++){
				cout << i << endl;
				gr_C_factor_ampt[i] = new TGraphErrors();

				int Npoint = gr_SC->GetN();
				for(int ipoint =0; ipoint <Npoint; ipoint++){
						cout << ipoint << endl;
						double x = gr_SC_AMPT[i]->GetX()[ipoint] ;
						double v22_ampt = gr_v2v2_ampt[i]->GetY()[ipoint] ;
						double v33_ampt = gr_v3v3_ampt[i]->GetY()[ipoint] ;
						gr_C_factor_ampt[i]->SetPoint( ipoint, x, v22_ampt * v22_ampt * v33_ampt *v33_ampt);


				}

				gr_C_factor_ampt[i]->SetLineColor(2+i);
				gr_C_factor_ampt[i]->SetMarkerColor(2+i);
				gr_C_factor_ampt[i]->SetMarkerStyle(kOpenSquare);

		}


		if(draw_old_ekrt[0]==1){
			

		};


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
