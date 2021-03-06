// configuration
bool Draw_TLatex = kFALSE;
int gFillStyle[2]={1000, 3002};
TString strFileName = "results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root";
enum { kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};

int gDataColor = kBlack;
int gDataFillColor = kGray;

int gOMarker[5] = {kOpenCircle, kOpenSquare, kOpenDiamond, 30, 27};
int gColor[5] = {kBlue, kRed, kGreen+2, kOrange-1, kRed+1};
int gFillColor[3] = { kGreen-3, kCyan+2, kYellow-6};

bool Draw_SC[kNSC] = { 1, 1, 1, 1, 1 };
bool Draw_SC_syst[kNSC] = { 1, 1, 1, 1, 1};
bool Draw_SC_norm[kNSC] = { 1, 1, 1, 1, 1};
bool Draw_SC_norm_syst[kNSC] = {1, 1, 1, 1, 1};


enum {kAMPT13f3a, kAMPT13f3b, kAMPT13f3c, kNAMPT};
bool Draw_SC_AMPT[kNAMPT] = { 0,};
bool Draw_SC_norm_AMPT[kNAMPT] = {0,};
double AMPT_ScaleFactor[kNAMPT] = { 1, 1, 1};

enum {kV_AMPT, kV_KLN, kV_Glb, kNVISH};
enum {kV_smallviso, kV_largevisco, kVNvisco};
bool Draw_VISH[kNVISH][kVNvisco] = { // 0 : for small eta/s  
							//   1: for large eta/s 
//	0,0,0,0,0,0
		1, 1, // VISH2+1 calculation with AMPT initial conditions
		1, 1, // VISH2+1 calculation with KLN initial condigtions
		1, 1 // VISH2+1 calcuation with Glauber initial condistions.
};
TString strVISHconf[kNVISH][kVNvisco] = {
		"VISH2+1 (AMPT, #eta/s=0.08)",
		"VISH2+1 (AMPT, #eta/s=0.16)",
		"VISH2+1 (MC-KLN, #eta/s=0.08)",
		"VISH2+1 (MC-KLN, #eta/s=0.2)",
		"VISH2+1 (MC-Glauber, #eta/s=0.08)",
		"VISH2+1 (MC-Glauber, #eta/s=0.2)",	
};



TString strSCType[kNSC] = { 
 "SC(3,2)","SC(4,2)","SC(5,2)","SC(5,3)","SC(4,3)"}; 
TString strSCnormType[kNSC] = {
	"SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT",
    "SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT",
    "SC(5,2)/#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT",
    "SC(5,3)/#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT",
    "SC(4,3)/#LTv_{4}^{2}#GT#LTv_{3}^{2}#GT"};
TString strAMPTName[kNAMPT] ={
	"AMPT String Melting ON,  Rescatering OFF",
	"AMPT String Melting OFF, Rescatering ON",
	"AMPT String Melting ON,  Rescatering ON"
	};


double x_min =0;
double x_max =51;

//Syst info
double systErr[kNSC] = { 0.098,  0.169, 0.21, 0.29, 0.18};
double systErr_norm[kNSC] = { 0.092, 0.0819,  0.21, 0.29, 0.143};


// Graph List
TGraphErrors *gr_SC[kNSC];
TGraphErrors *gr_SC_syst[kNSC];
TGraphErrors *gr_SC_norm[kNSC];
TGraphErrors *gr_SC_norm_syst[kNSC];
TGraphErrors *gr_SC_AMPT[kNAMPT][kNSC];
TGraphErrors *gr_SC_norm_AMPT[kNAMPT][kNSC];

TGraphErrors *gr_SC_Ante[2];
TGraphErrors *gr_SC_syst_Ante[2];
TGraphErrors *gr_SC_norm_Ante[2];
TGraphErrors *gr_SC_norm_syst_Ante[2];
TH1D *h_Ante_SC_AMPT[2];
TH1D *h_Ante_SC_norm_AMPT[2];

TGraphErrors *gr_SC_YOU[kNSC];
TGraphErrors *gr_SC_norm_YOU[kNSC];
TGraphErrors *gr_SC_YOU_syst[kNSC];
TGraphErrors *gr_SC_norm_YOU_syst[kNSC];

TGraphErrors *gr_SC_VISH[kNSC][kNVISH][kVNvisco];
TGraphErrors *gr_SC_norm_VISH[kNSC][kNVISH][kVNvisco];

double YlabelOffset = 1.21;
double XlabelOffset = 0.88;

void Draw_QConly_Fig3_vish_for_QM(){

	LoadSCResults();
	LoadAMPT();
	LoadVISH();
	cout << "load done. start draw " << endl;

	TLatex latex;
	TLine *line_0_60 = new TLine(0, 0, 60, 0);
//===================================================================================
	// MultiCanvas for SC 32
	TCanvas *c3 = new TCanvas("c3", "c3" , 400, 600);
	c3->Divide(1, 2, 0., 0.);
	c3->Draw();
	c3->cd(1);
	TH2D *href3 = new TH2D( "href3", "", 100, x_min, x_max, 100, -31.e-7, 4.e-7);
	href3->SetStats(0);
	href3->GetYaxis()->SetTitle("SC(3,2) ");
	href3->GetYaxis()->SetTitleOffset(0.85);
	href3->GetYaxis()->SetTitleSize(0.05);
	href3->GetYaxis()->SetLabelSize(0.047);

	TGaxis::SetExponentOffset(0.04, -0.0844, "y");
	href3->Draw();
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC( 0.93, 0.93 , "(a)");
	line_0_60->Draw("same l");
	TLegend *leg3 = new TLegend( 0.15, 0.07, 0.81, 0.74, "#splitline{ALICE}{ Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV}", "brNDC");
	leg3->SetTextSize(0.045);
	leg3->SetBorderSize(0);
	leg3->SetFillStyle(0);
		int isc = 0; 	
		gr_SC_syst[isc]->Draw("same2");
		gr_SC[isc]->Draw("same p");
		leg3->AddEntry( gr_SC[isc], "SC(3,2)", "p");
	
		for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_AMPT[iset]==1){
				gr_SC_AMPT[iset][isc]->Draw("same pl");
				leg3->AddEntry( gr_SC_AMPT[iset][isc], Form("%s", strAMPTName[iset].Data()), "pl");
			};
		}
	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<2; ieta++){
			if(Draw_VISH[iset][ieta]==1){
				gr_SC_VISH[isc][iset][ieta]->Draw("same pl");
				leg3->AddEntry( gr_SC_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
			}
		}
	};




		gStyle->SetErrorX(0);


	leg3->Draw();
	c3->cd(2);
//	TH2D *href3_low = new TH2D( "href3_low", "", 100, x_min, x_max, 100, -0.6, 0.3);
	TH2D *href3_low = new TH2D( "href3_low", "", 100, x_min, x_max, 100, -0.18, 0.06);
	href3_low->SetStats(0);
	href3_low->GetYaxis()->SetTitle("SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT      ");
	href3_low->GetYaxis()->SetTitleOffset(0.94);
	href3_low->GetYaxis()->SetTitleSize(0.048);
	href3_low->GetXaxis()->SetTitleSize(0.047);
	href3_low->GetYaxis()->SetLabelSize(0.042);
	href3_low->GetXaxis()->SetTitleOffset(XlabelOffset);
	href3_low->GetXaxis()->SetTitle("Centrality percentile");
	href3_low->GetXaxis()->SetLabelSize(0.047);
	href3_low->Draw();
	TLegend *leg3_low = new TLegend( 0.45, 0.66, 0.8, 0.9, "", "brNDC");
	leg3_low->SetTextSize(0.044);
	leg3_low->SetBorderSize(0);
	leg3_low->SetFillStyle(0);

	line_0_60->Draw("same l");
	gr_SC_norm_syst[isc]->Draw("same2");
	gr_SC_norm[isc]->Draw("same p");
	leg3_low->AddEntry( gr_SC_norm[0], "SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT", "p");
	leg3_low->AddEntry((TObject*)NULL,"|#eta|<0.8 , 0.2 < p_{T} < 5.0 GeV/c","");
	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_norm_AMPT[iset]==1){
					gr_SC_norm_AMPT[iset][isc]->Draw("same pl");
					leg3_low->AddEntry( gr_SC_norm_AMPT[iset][isc], strAMPTName[iset].Data(), "pl");
			};
	}

	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<2; ieta++){
			if(Draw_VISH[iset][ieta]==1){
				gr_SC_norm_VISH[isc][iset][ieta]->Draw("same pl");
//				leg3_low->AddEntry( gr_SC_norm_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
			}
		}
	};




	leg3_low->Draw();
	c3->SaveAs("figs/fig3_QConly_ModelComparison_SC32_vish.eps");

//===================================================================================
//===================================================================================
	// MultiCanvas for SC 42
	TCanvas *c4 = new TCanvas("c4", "c4" , 400, 600);
	c4->Divide(1, 2, 0., 0.);
	c4->Draw();
	c4->cd(1);
	TH2D *href4 = new TH2D( "href4", "", 100, x_min, x_max, 100, -4.2e-7, 45.6e-7);
	href4->SetStats(0);
	href4->GetYaxis()->SetTitle("SC(4,2) ");
	href4->GetYaxis()->SetTitleOffset(0.85);
	href4->GetYaxis()->SetTitleSize(0.05);
	href4->GetYaxis()->SetLabelSize(0.047);
	href4->Draw();
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC( 0.93, 0.93 , "(b)");
	line_0_60->Draw("same l");
	TLegend *leg4 = new TLegend( 0.2, 0.57, 0.81, 0.94, "ALICE Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
	leg4->SetTextSize(0.0425);
	leg4->SetBorderSize(0);
	leg4->SetFillStyle(0);
	int isc = 1;
	gr_SC_syst[isc]->Draw("same2");
	gr_SC[isc]->Draw("same p");
	leg4->AddEntry( gr_SC[isc], "SC(4,2)", "p");

	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_AMPT[iset]==1){
					gr_SC_AMPT[iset][isc]->Draw("same pl");
					leg4->AddEntry( gr_SC_AMPT[iset][isc], Form("%s", strAMPTName[iset].Data()), "pl");
			};
	}
	gStyle->SetErrorX(0);

	for(int iset=0; iset<kNVISH; iset++){
			for(int ieta=0; ieta<2; ieta++){
					if(Draw_VISH[iset][ieta]==1){
							gr_SC_VISH[isc][iset][ieta]->Draw("same pl");
							leg4->AddEntry( gr_SC_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
					}
			}
	};



	leg4->Draw();
	c4->cd(2);
	TH2D *href4_low = new TH2D( "href4_low", "", 100, x_min, x_max, 100, -0.05, 1.05);
//	TH2D *href4_low = new TH2D( "href4_low", "", 100, x_min, x_max, 100, -0.35, 1.75);
	href4_low->GetXaxis()->SetLabelSize(0.047);
	href4_low->SetStats(0);
	href4_low->GetYaxis()->SetTitle("SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT  ");
	href4_low->GetYaxis()->SetTitleOffset(0.97);
	href4_low->GetYaxis()->SetTitleSize(0.047);
	href4_low->GetXaxis()->SetTitleSize(0.05);
	href4_low->GetYaxis()->SetLabelSize(0.045);
	href4_low->GetXaxis()->SetTitleOffset(XlabelOffset);
	href4_low->GetXaxis()->SetTitle("Centrality percentile");
	href4_low->Draw();
	TLegend *leg4_low = new TLegend( 0.2, 0.62, 0.81, 0.95, "", "brNDC");
	leg4_low->SetTextSize(0.043);
	leg4_low->SetBorderSize(0);
	leg4_low->SetFillStyle(0);

	line_0_60->Draw("same l");
		gr_SC_norm_syst[isc]->Draw("same2");
		gr_SC_norm[isc]->Draw("same p");
	leg4_low->AddEntry( gr_SC_norm[isc], "SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT", "p");
	leg4_low->AddEntry((TObject*)NULL,"|#eta|<0.8 , 0.2 < p_{T} < 5.0 GeV/c","");
		for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_norm_AMPT[iset]==1){
				gr_SC_norm_AMPT[iset][isc]->Draw("same pl");
				leg4_low->AddEntry( gr_SC_norm_AMPT[iset][isc], strAMPTName[iset].Data(), "pl");
			};
		}
	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<2; ieta++){
			if(Draw_VISH[iset][ieta]==1){
				gr_SC_norm_VISH[isc][iset][ieta]->Draw("same pl");
	//			leg4_low->AddEntry( gr_SC_norm_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
			}
		}
	};



	leg4_low->Draw();
	c4->SaveAs("figs/fig3_QConly_ModelComparison_SC42_vish.eps");
//===================================================================================
//===================================================================================

	// MultiCanvas for SC 52
	TCanvas *c5 = new TCanvas("c5", "c5" , 400, 600);
	c5->Divide(1, 2, 0., 0.);
	c5->Draw();
	c5->cd(1);
	TH2D *href5 = new TH2D( "href5", "", 100, x_min, x_max, 100, -0.2e-7, 5.45e-7);
	href5->SetStats(0);
	href5->GetYaxis()->SetTitle("SC(5,2) ");
	href5->GetYaxis()->SetTitleOffset(0.85);
	href5->GetYaxis()->SetLabelSize(0.047);
	href5->GetYaxis()->SetTitleSize(0.05);
	href5->Draw();
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC( 0.93, 0.93 , "(a)");
	line_0_60->Draw("same l");
	TLegend *leg5 = new TLegend( 0.15, 0.53, 0.72, 0.89, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
	leg5->SetTextSize(0.0435);
	leg5->SetBorderSize(0);
	leg5->SetFillStyle(0);
	int isc = 2;

	gr_SC_syst[isc]->Draw("same2");
	gr_SC[isc]->Draw("same p");
	leg5->AddEntry( gr_SC[isc], "SC(5,2)", "p");
	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_AMPT[iset]==1){
					gr_SC_AMPT[iset][isc]->Draw("same pl");
					leg5->AddEntry( gr_SC_AMPT[iset][isc], Form("%s", strAMPTName[iset].Data()), "pl");
			};
	}
	for(int iset=0; iset<kNVISH; iset++){
			for(int ieta=0; ieta<2; ieta++){
					if(Draw_VISH[iset][ieta]==1){
							gr_SC_VISH[isc][iset][ieta]->Draw("same pl");
							leg5->AddEntry( gr_SC_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
					}
			}
	};



	leg5->Draw();
	c5->cd(2);
	TH2D *href5_low = new TH2D( "href5_low", "", 100, x_min, x_max, 100, -0.11, 0.565);
	//TH2D *href5_low = new TH2D( "href5_low", "", 100, x_min, x_max, 100, -0.20, 1.45);
	href5_low->GetXaxis()->SetLabelSize(0.046);
	href5_low->SetStats(0);
	href5_low->GetYaxis()->SetTitle("SC(5,2)/#LTv_{5}^{2}#GT#LTv_{2}^{2}#GT  ");
	href5_low->GetYaxis()->SetTitleOffset(0.99);
	href5_low->GetXaxis()->SetTitleOffset(XlabelOffset);
	href5_low->GetYaxis()->SetTitleSize(0.0465);
	href5_low->GetYaxis()->SetLabelSize(0.044);
	href5_low->GetXaxis()->SetTitleSize(0.05);
	href5_low->GetXaxis()->SetTitle("Centrality percentile");
	href5_low->Draw();
	TLegend *leg5_low = new TLegend( 0.15, 0.65, 0.6, 0.95, "", "brNDC");
	leg5_low->SetTextSize(0.045);
	leg5_low->SetBorderSize(0);
	leg5_low->SetFillStyle(0);

	line_0_60->Draw("same l");
	gr_SC_norm_syst[isc]->Draw("same2");
	gr_SC_norm[isc]->Draw("same p");
	leg5_low->AddEntry( gr_SC_norm[isc], "SC(5,2)/#LTv_{5}^{2}#GT#LTv_{2}^{2}#GT", "p");
	leg5_low->AddEntry((TObject*)NULL,"|#eta|<0.8 , 0.2 < p_{T} < 5.0 GeV/c","");

	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_norm_AMPT[iset]==1){
					gr_SC_norm_AMPT[iset][isc]->Draw("same pl");
			//		leg5_low->AddEntry( gr_SC_norm_AMPT[iset][isc], strAMPTName[iset].Data(), "pl");
			};
	}
	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<2; ieta++){
			if(Draw_VISH[iset][ieta]==1){
				gr_SC_norm_VISH[isc][iset][ieta]->Draw("same pl");
	//			leg5_low->AddEntry( gr_SC_norm_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
			}
		}
	};



	leg5_low->Draw();
	c5->SaveAs("figs/fig3_QConly_ModelComparison_SC52_vish.eps");
//===================================================================================
//===================================================================================

	// MultiCanvas for SC 53
	TCanvas *c6 = new TCanvas("c6", "c6" , 400, 600);
	c6->Divide(1, 2, 0., 0.);
	c6->Draw();
	c6->cd(1);
	TH2D *href6 = new TH2D( "href6", "", 100, x_min, x_max, 100, -0.13e-7, 2.59e-7);
	href6->SetStats(0);
	href6->GetYaxis()->SetTitle("SC(5,3) ");
	href6->GetYaxis()->SetTitleOffset(0.97);
	href6->GetYaxis()->SetLabelSize(0.047);
	href6->GetYaxis()->SetTitleSize(0.05);
	href6->Draw();
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC( 0.93, 0.93 , "(b)");
	line_0_60->Draw("same l");
	TLegend *leg6 = new TLegend( 0.15, 0.55, 0.74, 0.88, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
	leg6->SetTextSize(0.0435);
	leg6->SetBorderSize(0);
	leg6->SetFillStyle(0);
	int isc = 3;


	gr_SC_syst[isc]->Draw("same2");
	gr_SC[isc]->Draw("same p");
	leg6->AddEntry( gr_SC[isc], "SC(5,3)", "p");
	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_AMPT[iset]==1){
					gr_SC_AMPT[iset][isc]->Draw("same pl");
					leg6->AddEntry( gr_SC_AMPT[iset][isc], Form("%s", strAMPTName[iset].Data() ), "pl");
			};
	}
	for(int iset=0; iset<kNVISH; iset++){
			for(int ieta=0; ieta<2; ieta++){
					if(Draw_VISH[iset][ieta]==1){
							gr_SC_VISH[isc][iset][ieta]->Draw("same pl");
							leg6->AddEntry( gr_SC_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
					}
			}
	};



	leg6->Draw();
	c6->cd(2);
	TH2D *href6_low = new TH2D( "href6_low", "", 100, x_min, x_max, 100, -0.08, 1.75);
//	TH2D *href6_low = new TH2D( "href5_low", "", 100, x_min, x_max, 100, -0.08, 3.35);
	href6_low->GetXaxis()->SetLabelSize(0.046);
	href6_low->SetStats(0);
	href6_low->GetYaxis()->SetTitle("SC(5,3)/#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT  ");
	href6_low->GetYaxis()->SetTitleOffset(0.97);
	href6_low->GetXaxis()->SetTitleOffset(XlabelOffset);
	href6_low->GetYaxis()->SetTitleSize(0.047);
	href6_low->GetYaxis()->SetLabelSize(0.045);
	href6_low->GetXaxis()->SetTitleSize(0.05);
	href6_low->GetXaxis()->SetTitle("Centrality percentile");
	href6_low->Draw();
	TLegend *leg6_low = new TLegend( 0.15, 0.68, 0.63, 0.94, "", "brNDC");
	leg6_low->SetTextSize(0.045);
	leg6_low->SetBorderSize(0);
	leg6_low->SetFillStyle(0);

	line_0_60->Draw("same l");
	gr_SC_norm_syst[isc]->Draw("same2");
	gr_SC_norm[isc]->Draw("same p");
	leg6_low->AddEntry( gr_SC_norm[isc], "SC(5,3)/#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT", "p");
	leg6_low->AddEntry((TObject*)NULL,"|#eta|<0.8 , 0.2 < p_{T} < 5.0 GeV/c","");
	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_norm_AMPT[iset]==1){
					gr_SC_norm_AMPT[iset][isc]->Draw("same pl");
	//				leg6_low->AddEntry( gr_SC_norm_AMPT[iset][isc], strAMPTName[iset].Data(), "pl");
			};
	}
	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<2; ieta++){
			if(Draw_VISH[iset][ieta]==1){
				gr_SC_norm_VISH[isc][iset][ieta]->Draw("same pl");
	//		leg6_low->AddEntry( gr_SC_norm_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
			}
		}
	};




	leg6_low->Draw();
	c6->SaveAs("figs/fig3_QConly_ModelComparison_SC53_vish.eps");


//===================================================================================
//===================================================================================

	// MultiCanvas for SC 43
	TCanvas *c7 = new TCanvas("c7", "c7" , 400, 600);
	c7->Divide(1, 2, 0., 0.);
	c7->Draw();
	c7->cd(1);
	//TH2D *href7 = new TH2D( "href7", "", 100, x_min, x_max, 100, -1.35e-7, 0.55e-7);
	TH2D *href7 = new TH2D( "href7", "", 100, x_min, x_max, 100, -1.35e-7, 0.19e-7);
	href7->SetStats(0);
	href7->GetYaxis()->SetTitle("SC(4,3) ");
	href7->GetYaxis()->SetTitleOffset(0.85);
	href7->GetYaxis()->SetLabelSize(0.047);
	href7->GetYaxis()->SetTitleSize(0.05);
	href7->Draw();
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC( 0.93, 0.93 , "(c)");
	line_0_60->Draw("same l");
	TLegend *leg7 = new TLegend( 0.15, 0.07, 0.81, 0.73, "#splitline{ALICE Preliminary}{ Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV}", "brNDC");
	leg7->SetTextSize(0.045);
	leg7->SetBorderSize(0);
	leg7->SetFillStyle(0);
	int isc = 4;


	gr_SC_syst[isc]->Draw("same2");
	gr_SC[isc]->Draw("same p");
	leg7->AddEntry( gr_SC[isc], "SC(4,3)", "p");
	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_AMPT[iset]==1){
					gr_SC_AMPT[iset][isc]->Draw("same pl");
					leg7->AddEntry( gr_SC_AMPT[iset][isc], Form("%s", strAMPTName[iset].Data() ), "pl");
			};
	}
	for(int iset=0; iset<kNVISH; iset++){
			for(int ieta=0; ieta<2; ieta++){
					if(Draw_VISH[iset][ieta]==1){
							gr_SC_VISH[isc][iset][ieta]->Draw("same pl");
							leg7->AddEntry( gr_SC_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
					}
			}
	};



	leg7->Draw();
	c7->cd(2);
	TH2D *href7_low = new TH2D( "href7_low", "", 100, x_min, x_max, 100, -0.23, 0.049);
	//TH2D *href7_low = new TH2D( "href5_low", "", 100, x_min, x_max, 100, -0.65, 0.52);
	href7_low->GetXaxis()->SetLabelSize(0.046);
	href7_low->SetStats(0);
	href7_low->GetYaxis()->SetTitle("SC(4,3)/#LTv_{4}^{2}#GT#LTv_{3}^{2}#GT ");
	href7_low->GetYaxis()->SetTitleOffset(0.9);
	href7_low->GetXaxis()->SetTitleOffset(XlabelOffset);
	href7_low->GetYaxis()->SetTitleSize(0.0429);
	href7_low->GetYaxis()->SetLabelSize(0.045);
	href7_low->GetXaxis()->SetTitleSize(0.05);
	href7_low->GetXaxis()->SetTitle("Centrality percentile");
	href7_low->Draw();
	TLegend *leg7_low = new TLegend( 0.15, 0.12, 0.6, 0.45, "", "brNDC");
	leg7_low->SetTextSize(0.044);
	leg7_low->SetBorderSize(0);
	leg7_low->SetFillStyle(0);

	line_0_60->Draw("same l");


	gr_SC_norm_syst[isc]->Draw("same2");
	gr_SC_norm[isc]->Draw("same p");
	leg7_low->AddEntry( gr_SC_norm[isc], "SC(4,3)/#LTv_{4}^{2}#GT#LTv_{3}^{2}#GT", "p");
	leg7_low->AddEntry((TObject*)NULL,"|#eta|<0.8 , 0.2 < p_{T} < 5.0 GeV/c","");
	for(int iset=0; iset<kNAMPT; iset++){
			if(Draw_SC_norm_AMPT[iset]==1){
					gr_SC_norm_AMPT[iset][isc]->Draw("same pl");
					leg7_low->AddEntry( gr_SC_norm_AMPT[iset][isc], strAMPTName[iset].Data(), "pl");
			};
	}
	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<2; ieta++){
			if(Draw_VISH[iset][ieta]==1){
				gr_SC_norm_VISH[isc][iset][ieta]->Draw("same pl");
			//	leg7_low->AddEntry( gr_SC_norm_VISH[isc][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
			}
		}
	};


	leg7_low->Draw();
	c7->SaveAs("figs/fig3_QConly_ModelComparison_SC43_vish.eps");

}
// 

void LoadSCResults(){
	cout << "start load data" << endl;
	TFile *fin = new TFile( Form("%s", strFileName.Data() ), "read" );
	TString strGrSCName[kNSC] = { 
				"gr_SC_with_QC_3223",
				"gr_SC_with_QC_4224",
				"gr_SC_with_QC_5225",
				"gr_SC_with_QC_5335",
				"gr_SC_with_QC_4334"}
		TString strGrSCnormName[kNSC] = {
				"gr_SC_norm_with_QC_3223",
				"gr_SC_norm_with_QC_4224",
				"gr_SC_norm_with_QC_5225",
				"gr_SC_norm_with_QC_5335",
				"gr_SC_norm_with_QC_4334"}


	for(int isc=0; isc<kNSC; isc++){
		cout << isc << endl;
		gr_SC[isc] = (TGraphErrors*)fin->Get(Form("%s", strGrSCName[isc].Data() ) );
		gr_SC_norm[isc] = (TGraphErrors*) fin->Get(Form("%s", strGrSCnormName[isc].Data() ) );


		gr_SC[isc]->SetMarkerColor( gDataColor );
		gr_SC[isc]->SetMarkerStyle( kFullCircle );
		gr_SC[isc]->SetLineColor( gDataColor );
		gr_SC[isc]->SetMarkerSize(1.1);
		gr_SC_norm[isc]->SetMarkerColor( gDataColor );
		gr_SC_norm[isc]->SetLineColor( gDataColor );
		gr_SC_norm[isc]->SetMarkerStyle( kFullCircle );
		gr_SC_norm[isc]->SetMarkerSize(1.1);
		gr_SC_syst[isc] = (TGraphErrors*)gr_SC[isc]->Clone();
		gr_SC_syst[isc]->SetFillStyle( gFillStyle[0] );
		gr_SC_syst[isc]->SetFillColor( gDataFillColor );
		gr_SC_norm_syst[isc] = (TGraphErrors*)gr_SC_norm[isc]->Clone();
		gr_SC_norm_syst[isc]->SetFillStyle( gFillStyle[0] );
		gr_SC_norm_syst[isc]->SetFillColor( gDataFillColor );

/*
		gr_SC[isc]->SetMarkerColor( gColor[isc] );
		gr_SC[isc]->SetMarkerStyle( kFullCircle );
		gr_SC[isc]->SetLineColor( gColor[isc] );
		gr_SC[isc]->SetMarkerSize(1.1);
		gr_SC_norm[isc]->SetMarkerColor( gColor[isc] );
		gr_SC_norm[isc]->SetLineColor( gColor[isc] );
		gr_SC_norm[isc]->SetMarkerStyle( kFullCircle );
		gr_SC_norm[isc]->SetMarkerSize(1.1);
		gr_SC_syst[isc] = (TGraphErrors*)gr_SC[isc]->Clone();
		gr_SC_syst[isc]->SetFillStyle( gFillStyle[0] );
		gr_SC_syst[isc]->SetFillColor( gColor[isc] );
		gr_SC_norm_syst[isc] = (TGraphErrors*)gr_SC_norm[isc]->Clone();
		gr_SC_norm_syst[isc]->SetFillStyle( gFillStyle[0] );
		gr_SC_norm_syst[isc]->SetFillColor( gColor[isc]);
*/


		for(int ip=0; ip<gr_SC_syst[isc]->GetN(); ip++){
				double sErr = gr_SC_syst[isc]->GetY()[ip] * systErr[isc];
				gr_SC_syst[isc]->SetPointError( ip, 0.8, sErr );	
		};
		for(int ip=0; ip<gr_SC_norm_syst[isc]->GetN(); ip++){
				double sErr = gr_SC_norm_syst[isc]->GetY()[ip] * systErr_norm[isc];
				gr_SC_norm_syst[isc]->SetPointError(ip, 0.8, sErr);
		}

	}

    //(*****************************************************
    //change SC32, SC42 to published data points
    TFile *fin_Ante = new TFile("Ante_SC_results/Ante_DataPoint_20160130.root", "read");
    gr_SC[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32");
    gr_SC[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42");
    gr_SC_syst[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32_Syst");
    gr_SC_syst[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42_Syst");


    gr_SC_norm[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32_norm");
    gr_SC_norm[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42_norm");
    gr_SC_norm_syst[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32_norm_Syst");
    gr_SC_norm_syst[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42_norm_Syst");
    gr_SC_norm[kSC32]->SetMarkerColor( gDataColor );
    gr_SC_norm[kSC32]->SetLineColor( gDataColor );
    gr_SC_norm[kSC32]->SetMarkerStyle( kFullCircle );
    gr_SC_norm[kSC32]->SetMarkerSize( 1.1 );
    gr_SC_norm[kSC42]->SetMarkerColor( gDataColor );
    gr_SC_norm[kSC42]->SetLineColor( gDataColor );
    gr_SC_norm[kSC42]->SetMarkerStyle( kFullCircle );
    gr_SC_norm[kSC42]->SetMarkerSize( 1.1 );
    gr_SC_norm_syst[kSC32]->SetFillStyle(gFillStyle[0]);
    gr_SC_norm_syst[kSC32]->SetFillColor(gDataFillColor);
    gr_SC_norm_syst[kSC42]->SetFillStyle(gFillStyle[0]);
    gr_SC_norm_syst[kSC42]->SetFillColor(gDataFillColor);


    gr_SC[kSC32]->SetMarkerColor( gDataColor );
    gr_SC[kSC32]->SetMarkerStyle( kFullCircle );
    gr_SC[kSC32]->SetMarkerSize(1.1);
    gr_SC[kSC42]->SetMarkerColor( gDataColor );
    gr_SC[kSC42]->SetMarkerStyle( kFullCircle );
    gr_SC[kSC42]->SetMarkerSize(1.1);
    gr_SC_syst[kSC32]->SetFillStyle(gFillStyle[0]);
    gr_SC_syst[kSC32]->SetFillColor(gDataFillColor);
    gr_SC_syst[kSC42]->SetFillStyle(gFillStyle[0]);
    gr_SC_syst[kSC42]->SetFillColor(gDataFillColor);

    //******************************************************

	
	cout << "load done " <<endl;
}




void LoadAMPT(){

		TString strGrSCName[kNSC] = { 
				"gr_SC_with_QC_3223",
				"gr_SC_with_QC_4224",
				"gr_SC_with_QC_5225",
				"gr_SC_with_QC_5335",
				"gr_SC_with_QC_4334"}
		TString strGrSCnormName[kNSC] = {
				"gr_SC_norm_with_QC_3223",
				"gr_SC_norm_with_QC_4224",
				"gr_SC_norm_with_QC_5225",
				"gr_SC_norm_with_QC_5335",
				"gr_SC_norm_with_QC_4334"}

		TFile *fin[kNAMPT];
		TString strAMPTfile[kNAMPT] = {
				"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0250.root",
				"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0250.root",
				"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0250.root"
		};

	for(int iset=0; iset<kNAMPT; iset++){
			for(int isc=0; isc<kNSC; isc++){
					fin[iset] = new TFile( Form("%s", strAMPTfile[iset].Data() ), "read" );
					gr_SC_AMPT[iset][isc] = (TGraphErrors*)fin[iset]->Get(Form("%s", strGrSCName[isc].Data() ) );
					gr_SC_AMPT[iset][isc]->SetMarkerColor( gColor[isc] );
					gr_SC_AMPT[iset][isc]->SetLineColor( gColor[isc] );
					gr_SC_AMPT[iset][isc]->SetMarkerStyle( gOMarker[iset] );
					gr_SC_AMPT[iset][isc]->SetMarkerSize( 1.2);
					gr_SC_AMPT[iset][isc]->SetLineStyle( 2+ iset);
//					gr_SC_AMPT[iset][isc]->SetLineWidth(1.4);

					gr_SC_norm_AMPT[iset][isc] = (TGraphErrors*) fin[iset]->Get(Form("%s", strGrSCnormName[isc].Data() ) );
					gr_SC_norm_AMPT[iset][isc]->SetMarkerColor( gColor[isc] );
					gr_SC_norm_AMPT[iset][isc]->SetLineColor( gColor[isc] );
					gr_SC_norm_AMPT[iset][isc]->SetMarkerStyle( gOMarker[iset] );
					gr_SC_norm_AMPT[iset][isc]->SetMarkerSize( 1.2);
					gr_SC_norm_AMPT[iset][isc]->SetLineStyle( 2+iset );
//					gr_SC_norm_AMPT[iset][isc]->SetLineWidth(1.4);
		
			};

			//Scale graph
			for(int isc=0; isc<kNSC; isc++){
					double Npoint = gr_SC_AMPT[iset][isc]->GetN() ;
					for(int ipoint=0; ipoint < Npoint; ipoint++){
							double x = gr_SC_AMPT[iset][isc]->GetX()[ipoint] ;
							double y = gr_SC_AMPT[iset][isc]->GetY()[ipoint] * AMPT_ScaleFactor[iset] ;
							double ex = gr_SC_AMPT[iset][isc]->GetErrorX(ipoint) ;
							double ey = gr_SC_AMPT[iset][isc]->GetErrorY(ipoint) * AMPT_ScaleFactor[iset] ;
							gr_SC_AMPT[iset][isc]->SetPoint( ipoint, x, y);
							gr_SC_AMPT[iset][isc]->SetPointError( ipoint, ex, ey);
					};
			};

	};

};


void LoadVISH(){
	TString VISH[kNVISH]={
		"VISH_simdata/AMPT/resultSC.root",
		"VISH_simdata/KLN/resultSC.root",
		"VISH_simdata/Glb/resultSC.root"
	}
	TString VISH_norm[kNVISH]={
		"VISH_simdata/AMPT/resultSCR.root",
		"VISH_simdata/KLN/resultSCR.root",
		"VISH_simdata/Glb/resultSCR.root"
	}
	TFile *fin_VISH[kNVISH];
	TFile *fin_VISH_norm[kNVISH];
	for(int ivish=0; ivish<kNVISH; ivish++){
		fin_VISH[ivish] = new TFile( VISH[ivish].Data(), "read");
		fin_VISH_norm[ivish] = new TFile( VISH_norm[ivish].Data(), "read");
	}	

	
	// load files done.
	TString strVISHSCgraph[kNSC] = {
		"SC32", "SC42", "SC52", "SC53", "SC43"
	}
	for(int iset=0; iset<kNVISH; iset++){
		for(int isc=0; isc< kNSC; isc++){
			for(int ieta=0; ieta<kVNvisco; ieta++){
			gr_SC_VISH[isc][iset][ieta] = (TGraphErrors*)fin_VISH[iset]->Get(Form("%s_%d", strVISHSCgraph[isc].Data(), ieta));
			gr_SC_norm_VISH[isc][iset][ieta] = (TGraphErrors*)fin_VISH_norm[iset]->Get(Form("%s_%d",strVISHSCgraph[isc].Data(),ieta));


			//remove datapoint above 50centralities
			gr_SC_VISH[isc][iset][ieta]->RemovePoint(6);
			gr_SC_norm_VISH[isc][iset][ieta]->RemovePoint(6);
			//

			// cosmetics ? //
			int vc[3] = {kRed, kBlue, kGreen+2};
			gr_SC_VISH[isc][iset][ieta]->SetMarkerColor( vc[iset] );
			gr_SC_VISH[isc][iset][ieta]->SetLineColor( vc[iset]  );
			gr_SC_VISH[isc][iset][ieta]->SetMarkerStyle( gOMarker[iset] );
			gr_SC_VISH[isc][iset][ieta]->SetMarkerSize( 1.2);
			gr_SC_VISH[isc][iset][ieta]->SetFillStyle( gFillStyle[ieta] );
			gr_SC_VISH[isc][iset][ieta]->SetFillColor( gFillColor[iset] );

			gr_SC_norm_VISH[isc][iset][ieta]->SetMarkerColor( vc[iset] );
			gr_SC_norm_VISH[isc][iset][ieta]->SetMarkerSize( 1.2 );
			gr_SC_norm_VISH[isc][iset][ieta]->SetLineColor( vc[iset] );
			gr_SC_norm_VISH[isc][iset][ieta]->SetMarkerStyle( gOMarker[iset] );
			gr_SC_norm_VISH[isc][iset][ieta]->SetFillStyle( gFillStyle[ieta] );
			gr_SC_norm_VISH[isc][iset][ieta]->SetFillColor( gFillColor[iset] );
	

			}
		}
	}

}
