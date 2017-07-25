// pt Dependence 
bool Draw_TLatex= kTRUE;
enum {kQC, kNsets};
enum {kDefault, kpt0850, kpt0950, kpt1050, kpt1250, kpt1550, kNpt};
enum {kSC32, kSC42, kNSC};
bool Draw_canvas[4] = { 1, 1, 1, 1}; // (a), (b), (c), (d)

int x_min = -1;
int x_max = 51;
bool RemoveCent50to60 = 1;
int gColor[kNSC] = {kBlue, kRed};
int gOMarker[6] = { 24, 25, 26, 27, 28, 30 };
int gCMarker[6] = { 20, 21, 22, 33, 34, 29 };
int gFillStyle=3002;//3010;//3002;

double SystErr[kNsets][kNpt][kNSC] = { 
		0.098, 0.169,  // 0.2 ~ 5.0 
		0.0713, 0.1515,  // 0.8 ~ 5.0
		0.0737, 0.1617,  // 0.9 ~ 5.0
		0.0823, 0.1533,  // 10 ~ 5.0
		0.1026, 0.1405,   // 12 ~ 5.0
		0.1591, 0.1631	// 1.5
 }; // fill this
double SystErr_norm[kNsets][kNpt][kNSC] = { 
		0.092,	0.082,			//0.2 
		0.0646,	0.1104,			// 0.3
		0.0668,	0.1183,			// 0.4
		0.0766,	0.1191,			// 0.5
		0.0957,	0.1213,			//0.7
		0.1511, 0.1594
}; // fill this


TString strSCGrName[kNSC] = { "gr_SC_with_QC_3223", "gr_SC_with_QC_4224"};
TString strSCnormGrName[kNSC] = {"gr_SC_norm_with_QC_3223", "gr_SC_norm_with_QC_4224"};


TString strDataType[kNsets] = {
	" SC(m,n) (QC)"
};

TString strResultfiles[kNsets][kNpt] = {
	// data
	"results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0850.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0950.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt1050.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt1250.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt1550.root"
};

TString strPt[kNpt] = {
	"0.2", "0.8", "0.9", "1.0", "1.2", "1.5"
	};
/* 
	"#it{p}_{T,min} = 0.2 GeV/#it{c}",
	"#it{p}_{T,min} = 0.8 GeV/#it{c}",
	"#it{p}_{T,min} = 0.9 GeV/#it{c}",
	"#it{p}_{T,min} = 1.0 GeV/#it{c}",
	"#it{p}_{T,min} = 1.2 GeV/#it{c}",
	"#it{p}_{T,min} = 1.5 GeV/#it{c}"};
	"0.2 < p_{T} < 5.0 GeV/c", 
	"0.8 < p_{T} < 5.0 GeV/c",
	"0.9 < p_{T} < 5.0 GeV/c",
	"1.0 < p_{T} < 5.0 GeV/c",
	"1.2 < p_{T} < 5.0 GeV/c", 
	"1.5 < p_{T} < 5.0 GeV/c" };
*/
// TGraph List
TGraphErrors *gr_SC[kNsets][kNpt][kNSC];
TGraphErrors *gr_SC_norm[kNsets][kNpt][kNSC];
TGraphErrors *gr_SC_syst[kNsets][kNpt][kNSC];
TGraphErrors *gr_SC_norm_syst[kNsets][kNpt][kNSC];
TGraphErrors *gr_SC_norm_ratio[kNpt][kNSC];
TGraphErrors *gr_SystBand[kNSC];

void Draw_QConly_Fig4b(){

	LoadSCdata();
	TLatex latex;
	latex.SetTextSize(0.04);

	for(int ipt=1; ipt<kNpt; ipt++){
		for(int isc=0; isc<kNSC; isc++){
			gr_SC_norm_ratio[ipt][isc] = CalculateRatio( gr_SC_norm[kQC][ipt][isc], gr_SC_norm[kQC][0][isc], isc );
		}
	}

	for(int isc=0; isc<kNSC; isc++){
			gr_SystBand[isc]= new TGraphErrors();
			for(int ip=0; ip<7; ip++){
					gr_SystBand[isc]->SetPoint( ip, ip*10, 1);
					gr_SystBand[isc]->SetPointError( ip, 0, isc==0?0.043:0.11);
					gr_SystBand[isc]->SetFillStyle( 3002 );
					gr_SystBand[isc]->SetFillColor( isc==0?kBlue-9:kRed-9);
			}
	}
	//Draw (a) figure 
	if( Draw_canvas[0] == 1	){
		TCanvas *c1 = new TCanvas( "c1", "c1", 800, 600 );
		c1->Draw();
		TH2D *href = new TH2D("href", "" , 100, x_min, x_max, 100, -13.3e-5 , 13.9e-5 );
		href->SetStats(0);
		href->GetYaxis()->SetTitleSize(0.042);
		href->GetYaxis()->SetTitle("SC(m,n)");
		href->GetXaxis()->SetTitleSize(0.042);
		href->GetXaxis()->SetTitle("Centrality percentile");
		href->Draw();
		if(Draw_TLatex==kTRUE) latex.DrawLatexNDC(0.85, 0.83, "(c)");

		TLine *line0 = new TLine( x_min, 0, x_max, 0);
		line0->Draw("l");

		TLegend *leg1_top = new TLegend(0.15, 0.67, 0.55, 0.85, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
		TLegend *leg1 = new TLegend(0.13, 0.145, 0.59, 0.45, "", "brNDC");
		leg1->SetFillStyle(0);
		leg1->SetBorderSize(0);
		leg1->SetTextSize(0.037);
		leg1_top->SetFillStyle(0);
		leg1_top->SetBorderSize(0);
		leg1_top->SetTextSize(0.045);


		leg1_top->AddEntry( gr_SC[kQC][0][0], "SC(3,2)", "lp");
		leg1_top->AddEntry( gr_SC[kQC][0][1], "SC(4,2)", "lp");
		leg1_top->Draw();
		for(int ipt=0; ipt<kNpt; ipt++){
				for(int isc=0; isc<kNSC; isc++){
						gr_SC_syst[kQC][ipt][isc]->SetFillColor( gColor[isc] - 9 );
						gr_SC_syst[kQC][ipt][isc]->Draw("same 2");

				}
		}
		for(int ipt=0; ipt<kNpt; ipt++){
				for(int isc=0; isc<kNSC; isc++){

						gr_SC[kQC][ipt][isc]->SetLineColor( gColor[isc] );
						gr_SC[kQC][ipt][isc]->SetLineStyle( 1+ipt );
						gr_SC[kQC][ipt][isc]->SetLineWidth(1.5);
						gr_SC[kQC][ipt][isc]->SetMarkerColor( gColor[isc] );
						gr_SC[kQC][ipt][isc]->SetMarkerSize( 1.6 );
						if(isc==0)gr_SC[kQC][ipt][isc]->SetMarkerStyle( gOMarker[ipt] );
						if(isc==1)gr_SC[kQC][ipt][isc]->SetMarkerStyle( gCMarker[ipt] );
						gr_SC[kQC][ipt][isc]->SetLineWidth(1.2);
						gr_SC[kQC][ipt][isc]->Draw("same pl");

				}
				leg1->AddEntry( gr_SC[kQC][ipt][0], Form("%s", strPt[ipt].Data() ) , "pl");
		}
leg1->AddEntry((TObject*)NULL,"#it{p}_{T,min} ( #it{p}_{T,min} < #it{p}_{T} < 5 ) [GeV/#it{c}]", "");
		leg1->Draw();	
		c1->Update();
		c1->SaveAs("figs/fig4b_QConly_SC_ptdep.eps");
	} // (a) figure done..


	if(Draw_canvas[1] == 1){
		TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
		c2->SetGridy(1);
		c2->Draw();
		TH2D *href2 = new TH2D("href2", "", 100, x_min, x_max, 100, -0.23, 0.83);
		href2->SetStats(0);
		href2->GetYaxis()->SetTitleSize(0.042);
		href2->GetYaxis()->SetTitle("SC(m, n)/#LTv_{m}^{2}#GT#LTv_{n}^{2}#GT");
		href2->GetXaxis()->SetTitleSize(0.042);
		href2->GetXaxis()->SetTitle("Centrality percentile");
		href2->Draw();
		if(Draw_TLatex==kTRUE) latex.DrawLatexNDC(0.855, 0.83, "(d)");
		line0->Draw("l");

		
		TLegend *leg2_top = new TLegend(0.15, 0.67, 0.60, 0.85, "ALICE Preliminary Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
		TLegend *leg2 = new TLegend(0.15, 0.12, 0.60, 0.36, "");
		leg2->SetFillStyle(0);
		leg2->SetBorderSize(0);
		leg2->SetTextSize(0.038);
		leg2_top->SetFillStyle(0);
		leg2_top->SetBorderSize(0);
		leg2_top->SetTextSize(0.04);


		leg2_top->AddEntry( gr_SC_norm[kQC][0][0], "SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT", "pl");
		leg2_top->AddEntry( gr_SC_norm[kQC][0][1], "SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT", "pl");
		leg2_top->Draw();


		for(int ipt=0; ipt<kNpt; ipt++){
			for(int isc=0; isc<kNSC; isc++){

				gr_SC_norm_syst[kQC][ipt][isc]->SetFillColor( gColor[isc] - 9);
				Shift_graph_X( gr_SC_norm_syst[kQC][ipt][isc], -2.5+ipt/1.2);
				gr_SC_norm_syst[kQC][ipt][isc]->Draw("same2");
			}
		}
		for(int ipt=0; ipt<kNpt; ipt++){
			for(int isc=0; isc<kNSC; isc++){



				gr_SC_norm[kQC][ipt][isc]->SetLineColor( gColor[isc] );
				gr_SC_norm[kQC][ipt][isc]->SetLineStyle( ipt+1 );
				gr_SC_norm[kQC][ipt][isc]->SetLineWidth( 1.5  );
				gr_SC_norm[kQC][ipt][isc]->SetMarkerColor( gColor[isc] );
				gr_SC_norm[kQC][ipt][isc]->SetMarkerSize(1.6);
				if(isc==0)gr_SC_norm[kQC][ipt][isc]->SetMarkerStyle( gOMarker[ipt] );
				if(isc==1)gr_SC_norm[kQC][ipt][isc]->SetMarkerStyle( gCMarker[ipt] );
				gr_SC_norm[kQC][ipt][isc]->SetLineWidth(1.2);
				Shift_graph_X( gr_SC_norm[kQC][ipt][isc], -2.5 + ipt/1.2);
				gr_SC_norm[kQC][ipt][isc]->Draw("same pl");
			}
			leg2->AddEntry( gr_SC_norm[kQC][ipt][0], Form("%s", strPt[ipt].Data() ), "pl"); 
		}
	//	leg2->Draw();
		c2->Update();
		c2->SaveAs("figs/fig4b_QConly_nSC_ptdep.eps");
	} // (b) figure done

	// (c) ratio to default 
	TCanvas *c3 = new TCanvas("c3","c3", 800, 600);
	c3->Draw();
	TH2D *href3 = new TH2D("href3", "", 100, x_min, x_max, 100, -1, 3);
	href3->SetStats(0);
	href3->GetYaxis()->SetTitle("Ratio to ( 0.2 < p_{T} < 5.0 GeV/c )");
	href3->GetXaxis()->SetTitle("Centrality percentile");
	href3->Draw();
	TLine *line1 = new TLine( x_min, 1, x_max, 1);
	line1->Draw("l");

		gr_SystBand[1]->Draw("same3");
		gr_SystBand[0]->Draw("same3");

	for(int ipt=1; ipt<kNpt; ipt++){
		for(int isc=0; isc<kNSC; isc++){
			gr_SC_norm_ratio[ipt][isc]->SetLineColor( gColor[isc] );
			gr_SC_norm_ratio[ipt][isc]->SetMarkerColor( gColor[isc] );
			gr_SC_norm_ratio[ipt][isc]->SetMarkerStyle( gOMarker[ipt] );
			gr_SC_norm_ratio[ipt][isc]->SetMarkerSize(1.2);
			Shift_graph_X(	gr_SC_norm_ratio[ipt][isc] , -1 + ipt/2. );
			gr_SC_norm_ratio[ipt][isc]->Draw("same p");

		}
	}
		TLegend *leg3 = new TLegend(0.35, 0.57, 0.85, 0.85, "ALIC PreliminaryE Pb-Pb #sqrt{#it{s}}_{NN} = 2.76 TeV", "brNDC");
		leg3->SetFillStyle(0);
		leg3->SetBorderSize(0);
		leg3->SetTextSize(0.03);

		leg3->AddEntry( gr_SC[kQC][0][0], "NSC(3,2)", "l");
		leg3->AddEntry( gr_SC[kQC][0][1], "NSC(4,2)", "l");
		for(int ipt=0; ipt<kNpt; ipt++){
		leg3->AddEntry( gr_SC_norm[kQC][ipt][0], Form("%s", strPt[ipt].Data() ), "pl"); 
		}
		leg3->Draw();

		c3->SaveAs("figs/fig4b_QConly_nSC_ptdep_ratio.eps");


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


void LoadSCdata(){

	cout << "start load results files " << endl;

	TFile *fin[kNsets][kNpt];
	for(int iset=0; iset < kNsets; iset++){
		for(int ipt =0 ; ipt<kNpt; ipt++){
			cout << strResultfiles[iset][ipt].Data() << endl;
			fin[iset][ipt] = new TFile( strResultfiles[iset][ipt].Data() , "read" );
			for(int isc=0; isc<kNSC; isc++){
				gr_SC[iset][ipt][isc] = (TGraphErrors*)fin[iset][ipt]->Get(strSCGrName[isc].Data());
				gr_SC_norm[iset][ipt][isc]=(TGraphErrors*)fin[iset][ipt]->Get(strSCnormGrName[isc].Data());

				if(1){
					gr_SC[iset][ipt][isc]->RemovePoint(6);
					gr_SC_norm[iset][ipt][isc]->RemovePoint(6);
				}	

	
				// make syst gr
				gr_SC_syst[iset][ipt][isc] = (TGraphErrors*)gr_SC[iset][ipt][isc]->Clone();
				for(int ip=0; ip< gr_SC_syst[iset][ipt][isc]->GetN(); ip++){
					double serr =  gr_SC_syst[iset][ipt][isc]->GetY()[ip] * SystErr[iset][ipt][isc];
					gr_SC_syst[iset][ipt][isc]->SetPointError( ip, 0.8, serr );
				};
				gr_SC_norm_syst[iset][ipt][isc]=(TGraphErrors*)gr_SC_norm[iset][ipt][isc]->Clone();
				for(int ip=0; ip< gr_SC_norm_syst[iset][ipt][isc]->GetN(); ip++){
					double serr = gr_SC_norm_syst[iset][ipt][isc]->GetY()[ip] * SystErr_norm[iset][ipt][isc];
					gr_SC_norm_syst[iset][ipt][isc]->SetPointError( ip, 0.8, serr) ;

				}
			}// load Graph done.
		}; // pt loop
	}; // iset loop

	cout << "load... done" << endl;


}
