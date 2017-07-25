bool Draw_TLatex =kTRUE;
bool Draw_order_by_order = kTRUE;
bool Draw_higher_order_by_order = kTRUE;

int gFillStyle = 3002;
int gOMarker[5] = {kFullCircle, kFullCircle, 28, 30, 32};
int gCMarker[5] = {kFullSquare, kFullCircle, 22, 33, 34};
int gColor[6] = { kBlack, kBlack, 4, 32, 6, 7};

int gHarriEtaColor[5] = { kBlue, kBlack, kRed, kGreen+2, kOrange-3};

double x_min = 0;
double x_max = 51;
double y_min = -2.5 * 10e-7;
double y_max = 3. * 10e-7;
double y_min_ratio = -0.5;
double y_max_ratio = 6.2;

enum {kSC3223, kSC4224, kNSC};
enum {kAMPT13f3a, kAMPT13f3b, kAMPT13f3c, kNAMPT};

//SC 
bool Draw_Ante[kNSC] 			= {1,	 1};
bool Draw_Ante_syst[kNSC] 		= {1,	 1};
bool Draw_Ante_AMPT[kNSC]		= {0,0};
bool Draw_Ante_AMPT_norm[kNSC] = { 0,0};
bool Draw_SC[kNSC] 				= {0,	 0};
bool Draw_SC_syst[kNSC] 		= {0,	 0};
								//13f3a,13f3b,13f3c
bool Draw_AMPT[kNAMPT] 			= {0,	0,	0};
double ScaleFactor[kNAMPT]			= {0,	0,	0};

//normalized SC
bool Draw_Ante_Norm[kNSC] 		= {1,	 1};
bool Draw_Ante_Norm_syst[kNSC]	= {1,	 1};
bool Draw_SC_Norm[kNSC]			= {0,	 0};
bool Draw_SC_Norm_syst[kNSC] 	= {0,	 0};




// Hydro calculation 
enum {kParm0, kParm1, kParm2, kParm3, kParm4, kNParm};
bool Draw_Harris_Hydro[kNParm] = {1,1,1,1,1};
bool Draw_Harris_norm_Hydro[kNParm] = {1,1,1,1,1};

enum {kAnte, kOurs, kNsets};
TString finName[kNsets] = {"Ante_SC_results/Ante_DataPoint_20160130.root",
		"results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root"
};
TString finHydro = "Harris_results/Harris_SC_datapoint.root";


//syst error info
double SystErr[kNsets][kNSC] = {
		0.0980000407047346422, 0.169000376015966208, // ante's syst err
		0.151				, 0.10	};
double SystErr_norm[kNsets][kNSC] = {
		0.0919999878405408505, 0.0819998864547628603, // ante's syst err
		0.226				, 0.111 };


//graph list
TGraphErrors *gr_SC[kNsets][kNSC];
TGraphErrors *gr_SC_syst[kNSC][kNSC];
TGraphErrors *gr_SC_ratio[kNSC]; 
TGraphErrors *gr_SC_norm[kNsets][kNSC];
TGraphErrors *gr_SC_norm_syst[kNsets][kNSC];
TGraphErrors *gr_SC_norm_ratio[kNSC];
TGraphErrors *gr_SC_Hydro[kNParm][kNSC];
TGraphErrors *gr_SC_norm_Hydro[kNParm][kNSC];
TGraphErrors *gr_SC_AMPT[kNAMPT][kNSC];
TGraphErrors *gr_SC_norm_AMPT[kNAMPT][kNSC];
TH1D *h_Ante_SC_AMPT[kNSC];
TH1D *h_Ante_SC_norm_AMPT[kNSC];

TGraphErrors *gr_SC_EKRT[2][kNSC]; // only parm0, and par1 at this moment 
TGraphErrors *gr_NSC_EKRT[2][kNSC]; // only parm0, and par1 at this moment 


//=============== Main Code =========
void Draw_QConly_Fig1(){

		cout << "start " << endl;
		LoadAnteResults();
		LoadSCResults();
		LoadHydro();
		LoadAMPTModels();

		if(Draw_higher_order_by_order){
			LoadEKRT();
		}


		TLatex latex;
		latex.SetTextSize(0.04);

		TCanvas *c1 = new TCanvas("c1","c1", 800, 600);
		c1->Draw();

		TLine *line_0= new TLine( x_min, 0, x_max, 0);
		TLine *line_1= new TLine( x_min, 1, x_max, 1);
		TH2D *href = new TH2D("href", "", 100, x_min, x_max, 100,  -3.69e-6, 3.29e-6);
		href->GetYaxis()->SetTitle("SC(m,n) ");
		href->GetXaxis()->SetTitle("Centrality Percentile");
		href->GetYaxis()->SetTitleSize(0.04);
		href->GetYaxis()->SetTitleOffset(.8);
		href->GetYaxis()->SetLabelSize(0.035);
		//	TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
		href->SetStats(0);
		href->Draw();
		if(Draw_TLatex==kTRUE) latex.DrawLatexNDC( 0.84, 0.84, "(a)");
		line_0->Draw("same l");
		//
		//Fill Graph 
		for(int isc=0; isc<kNSC; isc++){

				if(Draw_Ante_syst[isc]==1) gr_SC_syst[kAnte][isc]->Draw("same2");
				if(Draw_Ante[isc] == 1) gr_SC[kAnte][isc]->Draw("same p");
				if(Draw_SC_syst[isc] == 1) gr_SC_syst[kOurs][isc]->Draw("same2");	
				if(Draw_SC[isc] == 1 ) gr_SC[kOurs][isc]->Draw("same p");
				for(int iampt=0; iampt<kNAMPT; iampt++){
					if(Draw_AMPT[iampt]==1) gr_SC_AMPT[iampt][isc]->Draw("same p");
				}
//				if(Draw_Ante_AMPT[isc]==1){gStyle->SetErrorX(0); h_Ante_SC_AMPT[isc]->Draw("samepl"); };

				for(int ipar=0; ipar<kNParm; ipar++){
						if(Draw_Harris_Hydro[ipar] == 1) gr_SC_Hydro[ipar][isc]->Draw("same c");
				}

		}

		TLegend *leg = new  TLegend(0.15, 0.68, 0.4, 0.85, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
		leg->SetFillStyle(0); 
		leg->SetBorderSize(0);
		leg->SetTextSize(0.03);
		//leg->AddEntry( gr_SC[kOurs][0] , "SC(3,2) : SP method (#Delta#eta>0.8) ", "p");  
		leg->AddEntry( gr_SC[kAnte][0] , "SC(3,2)", "p"); 
		leg->AddEntry( gr_SC[kAnte][1] , "SC(4,2)", "p"); 
		//leg->AddEntry( gr_SC[kOurs][1] , "SC(4,2) : SP method (#Delta#eta>0.8) ", "p");  
		if(Draw_AMPT[kAMPT13f3a]==1)leg->AddEntry( gr_SC_AMPT[kAMPT13f3a][0] , Form("AMPT13f3a String Melting ON,  ReScatering OFF"), "p");  
		if(Draw_AMPT[kAMPT13f3b]==1)leg->AddEntry( gr_SC_AMPT[kAMPT13f3b][0] , Form("AMPT13f3b String Melting OFF, ReScatering ON"), "p");  
		if(Draw_AMPT[kAMPT13f3c]==1)leg->AddEntry( gr_SC_AMPT[kAMPT13f3c][0] , Form("AMPT13f3c String Melting ON,  ReScatering ON"), "p");  
//		leg->AddEntry( h_Ante_SC_AMPT[0], "Ante's AMPT (String Melting ON)", "p"); 

		leg->Draw();

		TLegend *leg_hydro = new  TLegend(0.15, 0.15, 0.55, 0.33, "", "brNDC");
		leg_hydro->SetFillStyle(0); 
		leg_hydro->SetBorderSize(0);
		leg_hydro->SetTextSize(0.03);
//		leg_hydro->AddEntry( gr_SC_Hydro[0][0] , "Hydrodynamics", ""); 
		if(Draw_Harris_Hydro[0]==1)leg_hydro->AddEntry( gr_SC_Hydro[0][0] , "parm0 (#eta/s = 0.2)", "l"); 
		if(Draw_Harris_Hydro[1]==1)	leg_hydro->AddEntry( gr_SC_Hydro[1][0] , "parm1 (#eta/s(T))", "l"); 
		if(Draw_Harris_Hydro[2]==1)	leg_hydro->AddEntry( gr_SC_Hydro[2][0] , "parm2 (#eta/s(T)) ", "l"); 
		if(Draw_Harris_Hydro[3]==1)	leg_hydro->AddEntry( gr_SC_Hydro[3][0] , "parm3 (#eta/s(T))", "l"); 
		if(Draw_Harris_Hydro[4]==1)	leg_hydro->AddEntry( gr_SC_Hydro[4][0] , "parm4 (#eta/s(T))", "l"); 
		leg_hydro->Draw();

		gPad->GetCanvas()->SaveAs("figs/fig1_QConly_hydro.eps");


		// Draw Figure 1-(b)
		TCanvas *c2 = new TCanvas("c2","c2", 800, 600);
		c2->Draw();

		TH2D *href = new TH2D("href", "", 100, x_min, x_max, 100,  -0.6, 1.01);
		href->GetXaxis()->SetTitle("Centrality Percentile");
		href->GetYaxis()->SetTitle("SC(m,n)/#LTv_{m}^{2}#GT#LTv_{n}^{2}#GT");
		href->GetYaxis()->SetTitleSize(0.04);
		href->GetYaxis()->SetTitleOffset(0.8);
		href->GetYaxis()->SetLabelSize(0.025);
		href->SetStats(0);
		href->Draw();
		if(Draw_TLatex==kTRUE) latex.DrawLatexNDC( 0.84, 0.84, "(b)");
		line_0->Draw("same l");

		for(int isc=0; isc<kNSC; isc++){
				if(Draw_Ante_Norm_syst[isc] == 1) gr_SC_norm_syst[kAnte][isc]->Draw("same 2");
				if(Draw_Ante_Norm[isc] == 1) gr_SC_norm[kAnte][isc]->Draw("same p");
				if(Draw_SC_Norm_syst[isc] == 1) gr_SC_norm_syst[kOurs][isc]->Draw("same 2");
				if(Draw_SC_Norm[isc] == 1 ) gr_SC_norm[kOurs][isc]->Draw("same p");
				for(int iampt=0; iampt<kNAMPT; iampt++){
					if(Draw_AMPT[iampt]==1) gr_SC_norm_AMPT[iampt][isc]->Draw("same pl");
				}
//				if(Draw_Ante_AMPT_norm[isc]==1) h_Ante_SC_norm_AMPT[isc]->Draw("samepl");
				for(int ipar=0; ipar<kNParm; ipar++){
						if(Draw_Harris_norm_Hydro[ipar] == 1) gr_SC_norm_Hydro[ipar][isc]->Draw("same c");
				}
		}
		TLegend *leg2 = new  TLegend(0.15, 0.61, 0.55, 0.84, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
		leg2->SetFillStyle(0); 
		leg2->SetBorderSize(0);
		leg2->SetTextSize(0.03);
	//	leg2->AddEntry( gr_SC[kOurs][0] , "SC(3,2)/<v_{n}^{2}><v_{m}^{2}> : SP method (#Delta#eta>0.8) ", "p");  
		leg2->AddEntry( gr_SC[kAnte][0] , "SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT", "p"); 
	//	leg2->AddEntry( gr_SC[kOurs][1] , "SC(4,2)/<v_{n}^{2}><v_{m}^{2}>  : SP method (#Delta#eta>0.8) ", "p");  
		leg2->AddEntry( gr_SC[kAnte][1] , "SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT", "p"); 
		if(Draw_AMPT[kAMPT13f3a]==1)leg2->AddEntry( gr_SC_AMPT[kAMPT13f3a][0] , Form("AMPT13f3a String Melting ON,  ReScatering OFF"), "p");  
		if(Draw_AMPT[kAMPT13f3b]==1)leg2->AddEntry( gr_SC_AMPT[kAMPT13f3b][0] , Form("AMPT13f3b String Melting OFF, ReScatering ON"), "p");  
		if(Draw_AMPT[kAMPT13f3c]==1)leg2->AddEntry( gr_SC_AMPT[kAMPT13f3c][0] , Form("AMPT13f3c String Melting ON,  ReScatering ON") , "p");  
		//leg2->AddEntry( h_Ante_SC_AMPT[0], "Ante's AMPT (String Melting ON)", "p"); 
		leg2->Draw();
		leg_hydro->Draw();
		gPad->GetCanvas()->SaveAs("figs/fig1_QConly_hydro_norm.eps");


		if(Draw_order_by_order){ // order by order figure 

				TLine *line_0_60 = new TLine( 0, 0, 60, 0);
				//sc32 and nsc32
				TCanvas *c3 = new TCanvas("c3", "c3", 400, 600 );
				c3->Divide(1, 2, 0., 0.);
				c3->Draw();
				c3->cd(1);
				TH2D *href3 = new TH2D("href3", "" , 100, x_min, x_max, 100, -18e-7, 2.5e-7);
				href3->SetStats(0);
				href3->GetYaxis()->SetTitle("SC(3,2) ");
				href3->GetYaxis()->SetTitleSize(0.04);
				TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
				href3->Draw();		
				line_0_60->Draw("same l");
				TLegend *leg3 = new TLegend( 0.15, 0.32, 0.81, 0.5, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
				leg3->SetTextSize(0.04);
				leg3->SetBorderSize(0);
				leg3->SetFillStyle(0);	
				//Draw part = upper pad =
				gr_SC_syst[kAnte][kSC3223]->Draw("same 2");
				gr_SC[kAnte][kSC3223]->Draw("same p");
				leg3->AddEntry(gr_SC[kAnte][kSC3223] , "SC(3,2)", "p");
				for(int i=0; i<kNParm; i++){
						gr_SC_Hydro[i][kSC3223]->Draw("same c");
				}
						leg3->Draw();
				c3->cd(2);
				TH2D *href3_low = new TH2D( "href3_low", "", 100, x_min, x_max, 100, -0.19, 0.14);
				href3_low->SetStats(0);
				href3_low->GetXaxis()->SetTitle("Centrality percentile");
				href3_low->GetYaxis()->SetTitle("SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT  ");
				href3_low->GetYaxis()->SetTitleOffset(1.1);
				href3_low->GetYaxis()->SetTitleSize(0.04);
				href3_low->Draw();
				TLegend *leg3_low = new TLegend( 0.45, 0.64, 0.92, 0.94, "EKRT+Viscous Hydrodynamics", "brNDC");
				leg3_low->SetTextSize(0.04);
				leg3_low->SetBorderSize(0);
				leg3_low->SetFillStyle(0);
				if(Draw_Harris_Hydro[0]==1) leg3_low->AddEntry( gr_SC_Hydro[0][0] , "parm0 (#eta/s = 0.2)", "l"); 
				if(Draw_Harris_Hydro[1]==1)	leg3_low->AddEntry( gr_SC_Hydro[1][0] , "parm1 (#eta/s(T))", "l"); 
				if(Draw_Harris_Hydro[2]==1)	leg3_low->AddEntry( gr_SC_Hydro[2][0] , "parm2 (#eta/s(T)) ", "l"); 
				if(Draw_Harris_Hydro[3]==1)	leg3_low->AddEntry( gr_SC_Hydro[3][0] , "parm3 (#eta/s(T))", "l"); 
				if(Draw_Harris_Hydro[4]==1)	leg3_low->AddEntry( gr_SC_Hydro[4][0] , "parm4 (#eta/s(T))", "l"); 
				leg3_low->Draw();

				line_0_60->Draw("same l");
				//Draw part == lower pad ==
				gr_SC_norm_syst[kAnte][kSC3223]->Draw("same 2");
				gr_SC_norm[kAnte][kSC3223]->Draw("same p");
				for(int i=0; i<kNParm; i++){
						gr_SC_norm_Hydro[i][kSC3223]->Draw("same c");
				}

				TCanvas *c4 = new TCanvas("c4", "c4", 400, 600 );
				c4->Divide(1, 2, 0., 0.);
				c4->Draw();
				c4->cd(1);
				TH2D *href4 = new TH2D("href4", "" , 100, x_min, x_max, 100, -1e-7, 22.5e-7);
				href4->SetStats(0);
				href4->GetYaxis()->SetTitle("SC(4,2) ");
				href4->GetYaxis()->SetTitleSize(0.04);
				TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
				href4->Draw();		
				line_0_60->Draw("same l");
				TLegend *leg4 = new TLegend( 0.15, 0.32, 0.81, 0.5, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
				leg4->SetTextSize(0.04);
				leg4->SetBorderSize(0);
				leg4->SetFillStyle(0);	
				//Draw part = upper pad =
				gr_SC_syst[kAnte][kSC4224]->Draw("same 2");
				gr_SC[kAnte][kSC4224]->Draw("same p");
				for(int i=0; i<kNParm; i++){
						gr_SC_Hydro[i][kSC4224]->Draw("same c");
				}
				leg4->AddEntry(gr_SC[kAnte][kSC3223] , "SC(4,2)", "p");
				leg4->Draw();

								c4->cd(2);
				TH2D *href4_low = new TH2D( "href4_low", "", 100, x_min, x_max, 100, -0.1, 0.94);
				href4_low->SetStats(0);
				href4_low->GetXaxis()->SetTitle("Centrality percentile");
				href4_low->GetYaxis()->SetTitle("SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT  ");
				href4_low->GetYaxis()->SetTitleOffset(1.1);
				href4_low->GetYaxis()->SetTitleSize(0.04);
				href4_low->Draw();
				TLegend *leg4_low = new TLegend( 0.15, 0.64, 0.72, 0.94, "EKRT+Viscous Hydrodynamics", "brNDC");
				leg4_low->SetTextSize(0.04);
				leg4_low->SetBorderSize(0);
				leg4_low->SetFillStyle(0);
if(Draw_Harris_Hydro[0]==1)leg4_low->AddEntry( gr_SC_Hydro[0][1] , "parm0 (#eta/s = 0.2)", "l"); 
				if(Draw_Harris_Hydro[1]==1)	leg4_low->AddEntry( gr_SC_Hydro[1][1] , "parm1 (#eta/s(T))", "l"); 
				if(Draw_Harris_Hydro[2]==1)	leg4_low->AddEntry( gr_SC_Hydro[2][1] , "parm2 (#eta/s(T)) ", "l"); 
				if(Draw_Harris_Hydro[3]==1)	leg4_low->AddEntry( gr_SC_Hydro[3][1] , "parm3 (#eta/s(T))", "l"); 
				if(Draw_Harris_Hydro[4]==1)	leg4_low->AddEntry( gr_SC_Hydro[4][1] , "parm4 (#eta/s(T))", "l"); 
				leg4_low->Draw();

				line_0_60->Draw("same l");
				//Draw part == lower pad ==
				gr_SC_norm_syst[kAnte][kSC4224]->Draw("same 2");
				gr_SC_norm[kAnte][kSC4224]->Draw("same p");
				for(int i=0; i<kNParm; i++){
						gr_SC_norm_Hydro[i][kSC4224]->Draw("same c");
				}


		c3->SaveAs("figs/fig_SC_hydro_32.eps");
		c4->SaveAs("figs/fig_SC_hydro_42.eps");
		};

		// This is SC52 and higher order-by-order (only 2 par were calculated by EKRT's)
	

}


// Load Ante Results //
void LoadAnteResults(){

		TString strAnteGraphName[kNSC] = { "SC32", "SC42" };

		TFile *fin_Ante = new TFile( Form("%s", finName[kAnte].Data() ) , "read");
		for(int isc=0; isc<kNSC; isc++){
				gr_SC[kAnte][isc] = (TGraphErrors*)fin_Ante->Get(Form("gr_Ante_%s", strAnteGraphName[isc].Data() ));
				gr_SC[kAnte][isc]->RemovePoint(8);
				gr_SC[kAnte][isc]->RemovePoint(7);
				gr_SC[kAnte][isc]->SetMarkerColor( gColor[isc] );
				gr_SC[kAnte][isc]->SetLineColor ( gColor[isc] );
				gr_SC[kAnte][isc]->SetMarkerStyle( gOMarker[isc] );
				gr_SC[kAnte][isc]->SetMarkerSize( 1.1);
				gr_SC[kAnte][isc]->SetLineWidth(2);

				gr_SC_syst[kAnte][isc] = (TGraphErrors*)fin_Ante->Get(Form("gr_Ante_%s_Syst", strAnteGraphName[isc].Data() ) );
				gr_SC_syst[kAnte][isc]->RemovePoint(8);
				gr_SC_syst[kAnte][isc]->RemovePoint(7);
				gr_SC_syst[kAnte][isc]->SetFillColor( kGray);

				h_Ante_SC_AMPT[isc] = (TH1D*)fin_Ante->Get(Form("h_Ante_AMPT_%s", strAnteGraphName[isc].Data() ) );
				h_Ante_SC_AMPT[isc]->SetMarkerColor( gColor[isc] );
				h_Ante_SC_AMPT[isc]->SetMarkerStyle( 29 );
				h_Ante_SC_AMPT[isc]->SetLineColor( gColor[isc] );
				h_Ante_SC_AMPT[isc]->SetMarkerSize( 2.0);
				


		}
		for(int isc=0; isc<kNSC; isc++){
				gr_SC_norm[kAnte][isc] = (TGraphErrors*)fin_Ante->Get(Form("gr_Ante_%s_norm", strAnteGraphName[isc].Data() ));
				gr_SC_norm[kAnte][isc]->RemovePoint(8);
				gr_SC_norm[kAnte][isc]->RemovePoint(7);
				gr_SC_norm[kAnte][isc]->SetMarkerColor( gColor[isc] );
				gr_SC_norm[kAnte][isc]->SetMarkerSize( 1.1  );
				gr_SC_norm[kAnte][isc]->SetMarkerStyle( gOMarker[isc] );
				gr_SC_norm[kAnte][isc]->SetLineColor( gColor[isc] );
				gr_SC_norm[kAnte][isc]->SetLineWidth( 2 );

				gr_SC_norm_syst[kAnte][isc] = (TGraphErrors*)fin_Ante->Get(Form("gr_Ante_%s_norm_Syst", strAnteGraphName[isc].Data() ) );
				gr_SC_norm_syst[kAnte][isc]->RemovePoint(8);
				gr_SC_norm_syst[kAnte][isc]->RemovePoint(7);
				gr_SC_norm_syst[kAnte][isc]->SetFillColor(kGray );

				h_Ante_SC_norm_AMPT[isc] = (TH1D*)fin_Ante->Get(Form("h_Ante_AMPT_norm_%s", strAnteGraphName[isc].Data()) );
				h_Ante_SC_norm_AMPT[isc]->SetMarkerColor( gColor[isc] );
				h_Ante_SC_norm_AMPT[isc]->SetMarkerStyle( 29 );
				h_Ante_SC_norm_AMPT[isc]->SetLineColor( gColor[isc] );
				h_Ante_SC_norm_AMPT[isc]->SetMarkerSize( 2.0);
				



		}
		cout << "Load Ante's results.... done" << endl;
}
// Load SC results //

void LoadSCResults(){
		TFile *fin = new TFile( Form("%s", finName[kOurs].Data() ), "read");
		for(int isc=0; isc<kNSC; isc++){
				gr_SC[kOurs][isc] = (TGraphErrors*)fin->Get(Form("gr_SC_corr_%d", isc));

				gr_SC[kOurs][isc]->SetMarkerColor( gColor[isc] );
				gr_SC[kOurs][isc]->SetLineColor ( gColor[isc] );
				gr_SC[kOurs][isc]->SetMarkerStyle( gCMarker[isc] );
				gr_SC[kOurs][isc]->SetMarkerSize( 1.1);
				gr_SC[kOurs][isc]->SetLineWidth(2);

				gr_SC_syst[kOurs][isc] = (TGraphErrors*)gr_SC[kOurs][isc]->Clone();
				for(int ip=0; ip< gr_SC_syst[kOurs][isc]->GetN(); ip++){
						double serr = gr_SC_syst[kOurs][isc]->GetY()[ip] * SystErr[kOurs][isc];
						gr_SC_syst[kOurs][isc]->SetPointError( ip, 0.8, serr );
				}
				gr_SC_syst[kOurs][isc]->SetFillColor(kGray );

		}
		for(int isc=0; isc<kNSC; isc++){
				gr_SC_norm[kOurs][isc] = (TGraphErrors*)fin->Get(Form("gr_SC_ratio_%02d", isc));
				gr_SC_norm[kOurs][isc]->SetMarkerColor( gColor[isc] );
				gr_SC_norm[kOurs][isc]->SetLineColor ( gColor[isc] );
				gr_SC_norm[kOurs][isc]->SetMarkerStyle( gCMarker[isc] );
				gr_SC_norm[kOurs][isc]->SetMarkerSize( 1.1);
				gr_SC_norm[kOurs][isc]->SetLineWidth(2);

				gr_SC_norm_syst[kOurs][isc] = (TGraphErrors*)gr_SC_norm[kOurs][isc]->Clone();
				for(int ip=0; ip< gr_SC_norm_syst[kOurs][isc]->GetN(); ip++){
						double serr = gr_SC_norm_syst[kOurs][isc]->GetY()[ip] * SystErr_norm[kOurs][isc];
						gr_SC_norm_syst[kOurs][isc]->SetPointError( ip, 0.8, serr );
				}
				gr_SC_norm_syst[kOurs][isc]->SetFillColor( kGray );

		}
		cout << "Load SC results.... done" << endl;
}
// Load Hydro cal
void LoadHydro(){
		TFile *fin_hydro = new TFile( Form("%s", finHydro.Data(), "read"));
		for(int ipar=0; ipar<kNParm; ipar++){
				for(int isc=0; isc<kNSC; isc++){
						gr_SC_Hydro[ipar][isc] = (TGraphErrors*)fin_hydro->Get(Form("gr_harri_SC_%d_par%d", isc, ipar) );
						gr_SC_norm_Hydro[ipar][isc] = (TGraphErrors*)fin_hydro->Get(Form("gr_harri_SC_%d_Norm_par%d", isc, ipar) );


						gr_SC_Hydro[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
						gr_SC_Hydro[ipar][isc]->SetLineWidth( 2 );
						gr_SC_Hydro[ipar][isc]->SetLineStyle( 2 + ipar );

						gr_SC_norm_Hydro[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
						gr_SC_norm_Hydro[ipar][isc]->SetLineWidth( 2);
						gr_SC_norm_Hydro[ipar][isc]->SetLineStyle( 2+ ipar);

				}
		}
		cout << "Load Harri's data point... done " << endl;

}
// load EKRT with parm 0, parm 1
void LoadEKRT(){
		TFile *fin_EKRT[2];
		fin_EKRT[0]  = new TFile("Harris_results/EKRT_eta_020_pt_NSC.root", "read");
		fin_EKRT[1]  = new TFile("Harris_results/EKRT_eta_par1_pt_NSC.root", "read");

		for(int ipar=0; ipar<2; ipar++){
				for(int isc=0; isc<kNSC; isc++){
						gr_SC_EKRT[ipar][isc]=(TGraphErrors*)fin_EKRT[ipar]->Get(Form("gr_harri_SC_%d_pt_1", isc) );
						gr_NSC_EKRT[ipar][isc]=(TGraphErrors*)fin_EKRT[ipar]->Get(Form("gr_harri_NSC_%d_pt_1", isc) );

						gr_SC_EKRT[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
						gr_SC_EKRT[ipar][isc]->SetLineWidth(2);
						gr_SC_EKRT[ipar][isc]->SetLineStyle( 2+ ipar);
						gr_NSC_EKRT[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
						gr_NSC_EKRT[ipar][isc]->SetLineWidth(2);
						gr_NSC_EKRT[ipar][isc]->SetLineStyle( 2+ ipar);

				}
		}
		cout << "load EKRT data points... done" << endl;
//TGraphErrors *gr_SC_EKRT[2][kNSC]; // only parm0, and par1 at this moment 
//TGraphErrors *gr_NSC_EKRT[2][kNSC]; // only parm0, and par1 at this moment 
}


void LoadAMPTModels(){
		TFile *fin[kNAMPT];
		TString strAMPTsetName[kNAMPT] = {
				"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0250.root",
				"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0250.root",
				"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0250.root"
			};
		for(int iset=0; iset<kNAMPT; iset++){
				fin[iset] = new TFile( strAMPTsetName[iset].Data(), "read");
				for(int isc=0; isc<kNSC; isc++){
						gr_SC_AMPT[iset][isc] = (TGraphErrors*)fin[iset]->Get(Form("gr_SC_corr_%d", isc));
						double Npoint = gr_SC_AMPT[iset][isc]->GetN() ;
						for(int ipoint=0; ipoint < Npoint; ipoint++){
								double x = gr_SC_AMPT[iset][isc]->GetX()[ipoint] ;
								double y = gr_SC_AMPT[iset][isc]->GetY()[ipoint] * ScaleFactor[iset] ;
								double ex = gr_SC_AMPT[iset][isc]->GetErrorX(ipoint) ;
								double ey = gr_SC_AMPT[iset][isc]->GetErrorY(ipoint) * ScaleFactor[iset] ;
								gr_SC_AMPT[iset][isc]->SetPoint( ipoint, x, y);
								gr_SC_AMPT[iset][isc]->SetPointError( ipoint, ex, ey);
						};


						gr_SC_norm_AMPT[iset][isc] = (TGraphErrors*)fin[iset]->Get(Form("gr_SC_ratio_%02d", isc));

						
						gr_SC_AMPT[iset][isc]->SetLineColor( gColor[isc] );
						gr_SC_AMPT[iset][isc]->SetMarkerColor( gColor[isc] );
						gr_SC_AMPT[iset][isc]->SetMarkerSize(1.1);
						gr_SC_AMPT[iset][isc]->SetMarkerStyle( 24+ iset );

						gr_SC_norm_AMPT[iset][isc]->SetLineColor( gColor[isc] );
						gr_SC_norm_AMPT[iset][isc]->SetMarkerColor( gColor[isc] );
						gr_SC_norm_AMPT[iset][isc]->SetMarkerSize(1.1);
						gr_SC_norm_AMPT[iset][isc]->SetMarkerStyle( 24+ iset );


				};
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
















