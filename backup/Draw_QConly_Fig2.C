bool Draw_TLatex = kTRUE;

//int fsty=1000;
int fsty=3002;

TString strFileName = "results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root";
enum { kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};
enum{ k0005, k0510, k1020, k2030, k3040, k4050, k5060, kNCent};
const double CentBins[kNCent+1] = {0, 5, 10, 20, 30, 40, 50, 60};

int gFillStyle = 1000;
int gOMarker[5] = {kOpenSquare, kOpenCircle, 28, kOpenSquare, kOpenCircle};
int gCMarker[5] = {kFullSquare, kFullCircle, kFullCircle, kFullSquare, 33};
int gColor[5] = {kBlue, kRed, kRed+2, kGreen+4, kCyan+2};
int gFillColor[5] = {kBlue-4, kRed-4, kRed-6, kGreen-10, kCyan-4};  

bool Draw_SC[kNSC] = { 1, 1, 1,1,1 };
bool Draw_SC_syst[kNSC] = { 1, 1, 1, 1, 1};
bool Draw_SC_norm[kNSC] = { 1, 1, 1, 1, 1};
bool Draw_SC_norm_syst[kNSC] = {0, 0, 1, 1, 1};
bool Draw_SC_HIJING[kNSC] = { 0, 0, 0, 0, 0};
double ScaleFactor[kNSC] = { 0.1, 0.1, 1,1 , 1}; // x1. scale

TString strSCType[kNSC] = { 
	"SC(3,2)",
	"SC(4,2)",
	"SC(5,2)",
	"SC(5,3)",
	"SC(4,3)"};

TString strSCnormType[kNSC] = {
	"NSC(3,2)",
	"NSC(4,2)",
	"NSC(5,2)",
	"NSC(5,3)",
	"NSC(4,3)"};

//	"<v_{3}^{2}v_{2}^{2}> - <v_{3}^{2}><v_{2}^{2}>",
//	"<v_{4}^{2}v_{2}^{2}> - <v_{4}^{2}><v_{2}^{2}>",
//	"<v_{5}^{2}v_{2}^{2}> - <v_{5}^{2}><v_{2}^{2}>",
//	"<v_{5}^{2}v_{3}^{2}> - <v_{5}^{2}><v_{3}^{2}>",
//	"<v_{4}^{2}v_{3}^{2}> - <v_{4}^{2}><v_{3}^{2}>"	};
//"SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT",
//"SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT",
//"SC(5,2)/#LTv_{5}^{2}#GT#LTv_{2}^{2}#GT",
//"SC(5,3)/#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT",
//"SC(4,3)/#LTv_{4}^{2}#GT#LTv_{3}^{2}#GT"};
//	"<v_{3}^{2}v_{2}^{2}>/<v_{3}^{2}><v_{2}^{2}> - 1",
//	"<v_{4}^{2}v_{2}^{2}>/<v_{4}^{2}><v_{2}^{2}> - 1",
//	"<v_{5}^{2}v_{2}^{2}>/<v_{5}^{2}><v_{2}^{2}> - 1",
//	"<v_{5}^{2}v_{3}^{2}>/<v_{5}^{2}><v_{3}^{2}> - 1",
//	"<v_{4}^{2}v_{3}^{2}>/<v_{4}^{2}><v_{3}^{2}> - 1"};

double x_min =0;
double x_max =57;

//Syst info
double systErr[kNSC] = { 0.098, 0.169, 0.21, 0.29, 0.103};
double systErr_norm[kNSC] = {0.092, 0.082, 0.21, 0.29, 0.10 };


// Graph List
TGraphErrors *gr_SC[kNSC];
TGraphErrors *gr_SC_syst[kNSC];
TGraphErrors *gr_SC_norm[kNSC];
TGraphErrors *gr_SC_norm_syst[kNSC];

TGraphErrors *gr_SC_Band[kNSC];
TGraphErrors *gr_SC_norm_Band[kNSC];
TGraphErrors *gr_SC_pub[kNSC];
TGraphErrors *gr_SC_norm_pub[kNSC];
TGraphErrors *gr_SC_pub_syst[kNSC];
TGraphErrors *gr_SC_norm_pub_syst[kNSC];

TGraphErrors *gr_SC_Hijing[kNSC];



void Draw_QConly_Fig2(){

	LoadSCResults();
	TLatex latex;
	latex.SetTextSize(0.04);

	Merge_Syst_Stat_Errors(); // quadratic merged syst and stats, save into SC Band style graph.

	cout << "loaded files" << endl;

	TCanvas *c1 = new TCanvas("c1", "c1", 800, 600 );
	c1->Draw();
	TH2D *href = new TH2D("href", "", 100, x_min, x_max, 100, -1.95e-7, 3.1e-7);
	href->GetYaxis()->SetTitle("SC(m,n)");
	href->GetYaxis()->SetTitleSize(0.041);
	href->GetYaxis()->SetTitleOffset(0.8);
	href->GetYaxis()->SetLabelSize(0.035);
	href->GetXaxis()->SetTitleSize(0.05);
	href->GetXaxis()->SetTitleOffset(0.9);
	href->GetXaxis()->SetTitle("Centrality percentile");
	href->SetStats(0);
	href->Draw();
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC(0.83, 0.83, "(a)");

	TLine *line_0 = new TLine(x_min, 0, x_max, 0);
	line_0->Draw("same l");
	TLegend *leg = new TLegend( 0.13, 0.58, 0.55, 0.87, "ALICE Pb-Pb #sqrt{#it{s}_{NN}} = 2.76 TeV", "brNDC");
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	leg->SetTextSize(0.038);

	for(int isc=0; isc<kNSC; isc++){
		gr_SC[isc]->SetMarkerColor( gColor[isc] );
		gr_SC[isc]->SetFillColor( gFillColor[isc] );
		gr_SC[isc]->SetLineColor( gColor[isc] );
		gr_SC[isc]->SetMarkerStyle( gCMarker[isc] );
		gr_SC[isc]->SetMarkerSize( 1.8 );
		if(isc==kSC43) gr_SC[isc]->SetMarkerSize( 2.2 );
		gr_SC[isc]->SetLineWidth(2);
		gr_SC_syst[isc]->SetFillStyle( gFillStyle);
		gr_SC_syst[isc]->SetFillColor( gFillColor[isc] );
		cout <<"*dataset:"<<endl;
		cout <<"*location: Figure 1"<<endl;
		cout <<"*dscomment: Centrality dependence of observables "<<strSCType[isc]<<" in Pb-Pb collisions at 2.76 TeV"<<endl;
		cout <<"*reackey: PB PB --> CHARGED X"<<endl;
		cout <<"*obskey: SC"<<endl;
		cout <<"*qual: ETARAP : -0.8 TO 0.8"<<endl;
		cout <<"*qual: PT IN GEV/C : 0.2 TO 5.0"<<endl;
		cout <<"*qual: RE : PB PB --> CHARGED X"<<endl;
		cout <<"*qual: SQRT(S)/NUCLEON IN GEV : 2760"<<endl;
		cout <<"*xheader: CENTRALITY IN PCT"<<endl;
		cout <<"*yheader: "<<strSCType[isc]<<endl; 	
		cout <<"*data: x : y"<<endl;
		printGrrHepData(gr_SC[isc], gr_SC_syst[isc],CentBins,NULL);
		cout <<"*dataend:"<<endl;
		cout << endl;

		if(Draw_SC[isc] == 1) {
			if(ScaleFactor[isc]==1){
				gr_SC_syst[isc]->Draw("same2");
				gr_SC[isc]->Draw("samep");	
				leg->AddEntry( gr_SC[isc] , Form("%s ", strSCType[isc].Data() ), "pl");
			}
			if(ScaleFactor[isc]!=1){
				RemovePoints( gr_SC_Band[isc],60);
				gr_SC_Band[isc]->Draw("same3");
				leg->AddEntry( gr_SC_Band[isc] , Form("%s ( #times %1.1f) PRL. 117 (2016) 182301", strSCType[isc].Data(), ScaleFactor[isc]  ), "f");
			}
		};
		if(Draw_SC_HIJING[isc] ==1)gr_SC_Hijing[isc]->Draw("same p");
	}
	//leg->AddEntry((TObject*)NULL,"|#eta| < 0.8, 0.2 < p_{T} < 5.0 GeV/#it{c}","");
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC(0.15, 0.15, "|#eta| < 0.8, 0.2 < p_{T} < 5.0 GeV/#it{c}");
	leg->Draw();
	if(Draw_SC_HIJING[0]==1){
		TLegend *leg_hijing = new TLegend( 0.15, 0.25, 0.55, 0.45, "", "brNDC");
		leg_hijing->SetBorderSize(0);
		leg_hijing->SetFillStyle(0);
		leg_hijing->SetTextSize(0.043);
		leg_hijing->AddEntry( gr_SC_Hijing[0], "HIJING", "p");
		leg_hijing->Draw();
	}	

	gPad->GetCanvas()->SaveAs("figs/fig2_QConly_higherSC.eps");

	//cout <<"Pubished SC32"<< endl;
	//printGrrHepData (gr_SC_pub[kSC32], gr_SC_pub_syst[kSC32], NULL);

	TCanvas *c2 = new TCanvas("c2", "c2" , 800, 600);
	c2->Draw();
	TH2D *href2 = new TH2D("href", "", 100, x_min, x_max, 100, -0.5, 1.8);
	href2->GetYaxis()->SetTitle("SC(m,n)/#LTv_{m}^{2}#GT#LTv_{n}^{2}#GT");
	href2->GetYaxis()->SetTitleSize(0.041);
	href2->GetYaxis()->SetTitleOffset(0.85);
	href2->GetYaxis()->SetLabelSize(0.035);
	href2->GetXaxis()->SetTitleSize(0.05);
	href2->GetXaxis()->SetTitleOffset(0.9);
	href2->GetXaxis()->SetTitle("Centrality percentile");
	href2->SetStats(0);
	href2->Draw();
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC(0.83, 0.83, "(b)");

	line_0->Draw("same l");
	TLegend *leg2 = new TLegend( 0.13, 0.58, 0.55, 0.87, "ALICE Pb-Pb #sqrt{#it{s}_{NN}} = 2.76 TeV" , "brNDC");
	leg2->SetBorderSize(0);
	leg2->SetFillStyle(0);
	leg2->SetTextSize(0.038);

	for(int isc=0; isc<kNSC; isc++){
		gr_SC_norm[isc]->SetMarkerColor( gColor[isc] );
		gr_SC_norm[isc]->SetMarkerStyle( gCMarker[isc] );
		gr_SC_norm[isc]->SetMarkerSize( 1.5 );
		if(isc==kSC43) gr_SC_norm[isc]->SetMarkerSize( 2.2 );
		gr_SC_norm[isc]->SetFillColor( gFillColor[isc]);
		gr_SC_norm[isc]->SetLineColor( gColor[isc] );
		gr_SC_norm[isc]->SetLineWidth( 2);
		gr_SC_norm_syst[isc]->SetFillStyle( gFillStyle);
		gr_SC_norm_syst[isc]->SetFillColor( gFillColor[isc]);
		cout <<"*dataset:"<<endl;
		cout <<"*location: Figure 1"<<endl;
		cout <<"*dscomment: Centrality dependence of observables "<<strSCnormType[isc]<<" in Pb-Pb collisions at 2.76 TeV"<<endl;
		cout <<"*reackey: PB PB --> CHARGED X"<<endl;
		cout <<"*obskey: SC"<<endl;
		cout <<"*qual: ETARAP : -0.8 TO 0.8"<<endl;
		cout <<"*qual: PT IN GEV/C : 0.2 TO 5.0"<<endl;
		cout <<"*qual: RE : PB PB --> CHARGED X"<<endl;
		cout <<"*qual: SQRT(S)/NUCLEON IN GEV : 2760"<<endl;
		cout <<"*xheader: CENTRALITY IN PCT"<<endl;
		cout <<"*yheader: "<<strSCnormType[isc]<<endl; 	
		cout <<"*data: x : y"<<endl;
		printGrrHepData(gr_SC_norm[isc], gr_SC_norm_syst[isc],CentBins,NULL);
		cout <<"*dataend:"<<endl;
		cout << endl;
		if(Draw_SC_norm[isc] == 1){	
			if(ScaleFactor[isc]==1){
				gr_SC_norm_syst[isc]->Draw("same2");	
				gr_SC_norm[isc]->Draw("same p");
				leg2->AddEntry( gr_SC_norm[isc], strSCnormType[isc].Data(), "pl");
			}
			if(ScaleFactor[isc]!=1){
				RemovePoints( gr_SC_norm_Band[isc],60);
				gr_SC_norm_Band[isc]->Draw("same3");
				leg2->AddEntry( gr_SC_norm_Band[isc], Form("%s PRL. 117 (2016) 182301",strSCnormType[isc].Data()), "f");
			}
		};
	}
	if(Draw_TLatex==kTRUE) latex.DrawLatexNDC(0.15, 0.15, "|#eta| < 0.8, 0.2 < p_{T} < 5.0 GeV/#it{c}");
	//leg2->AddEntry((TObject*)NULL,"|#eta| < 0.8, 0.2 < p_{T} < 5.0 GeV/#it{c}","");
	leg2->Draw();
	gPad->GetCanvas()->SaveAs("figs/fig2_QConly_higherNSC.eps");

}
// 
void LoadSCResults(){
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
		gr_SC[isc] = (TGraphErrors*)fin->Get(Form("%s", strGrSCName[isc].Data() ) );
		//Shift_graph_X( gr_SC[isc], -2+isc );


		gr_SC_norm[isc] = (TGraphErrors*) fin->Get(Form("%s", strGrSCnormName[isc].Data() ) );
		//Shift_graph_X( gr_SC_norm[isc], -2+isc);

		gr_SC_syst[isc] = (TGraphErrors*)gr_SC[isc]->Clone();
		for(int ip=0; ip<gr_SC_syst[isc]->GetN(); ip++){
			double sErr = gr_SC_syst[isc]->GetY()[ip] * systErr[isc];
			gr_SC_syst[isc]->SetPointError( ip, 0.8, sErr );	
		};
		gr_SC_norm_syst[isc] = (TGraphErrors*)gr_SC_norm[isc]->Clone();
		for(int ip=0; ip<gr_SC_norm_syst[isc]->GetN(); ip++){
			double sErr = gr_SC_norm_syst[isc]->GetY()[ip] * systErr_norm[isc];
			gr_SC_norm_syst[isc]->SetPointError(ip, 0.8, sErr);
		}
		RemovePoints(gr_SC[isc],50);
		RemovePoints(gr_SC_norm[isc],50);
		RemovePoints(gr_SC_syst[isc],50);
		RemovePoints(gr_SC_norm_syst[isc],50);



	}

	//Scale graph  : SC
	for(int isc=0; isc<kNSC; isc++){
		double Npoint = gr_SC[isc]->GetN() ;
		for(int ipoint=0; ipoint < Npoint; ipoint++){
			double x = gr_SC[isc]->GetX()[ipoint] ;
			double y = gr_SC[isc]->GetY()[ipoint] * ScaleFactor[isc] ;
			double ex = gr_SC[isc]->GetErrorX(ipoint) ;
			double ey = gr_SC[isc]->GetErrorY(ipoint) * ScaleFactor[isc] ;
			gr_SC[isc]->SetPoint( ipoint, x, y);
			gr_SC[isc]->SetPointError( ipoint, ex, ey);
		};
	};
	//Scale graph : SC_syst
	for(int isc=0; isc<kNSC; isc++){
		double Npoint = gr_SC_syst[isc]->GetN() ;
		for(int ipoint=0; ipoint < Npoint; ipoint++){
			double x = gr_SC_syst[isc]->GetX()[ipoint] ;
			double y = gr_SC_syst[isc]->GetY()[ipoint] * ScaleFactor[isc] ;
			double ex = gr_SC_syst[isc]->GetErrorX(ipoint) ;
			double ey = gr_SC_syst[isc]->GetErrorY(ipoint) * ScaleFactor[isc] ;
			gr_SC_syst[isc]->SetPoint( ipoint, x, y);
			gr_SC_syst[isc]->SetPointError(ipoint, ex, ey);
		};
	};




}

void Merge_Syst_Stat_Errors(){

	//(*****************************************************
	//change SC32, SC42 to published data points
	TFile *fin_Ante = new TFile("Ante_SC_results/Ante_DataPoint_20160130.root", "read");
	gr_SC_pub[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32");
	gr_SC_pub[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42");
	gr_SC_pub_syst[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32_Syst");
	gr_SC_pub_syst[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42_Syst");

	gr_SC_norm_pub[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32_norm");
	gr_SC_norm_pub[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42_norm");
	gr_SC_norm_pub_syst[kSC32] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC32_norm_Syst");
	gr_SC_norm_pub_syst[kSC42] = (TGraphErrors*)fin_Ante->Get("gr_Ante_SC42_norm_Syst");

	for(int isc=0; isc<2; isc++){ // only for sc32, and sc42
		gr_SC_Band[isc] = (TGraphErrors*)gr_SC_pub[isc]->Clone();
		int NP = gr_SC_pub[isc]->GetN();
		for(int ip=0; ip<NP; ip++){
			double staterr = gr_SC_pub[isc]->GetEY()[ip];  
			double systerr = gr_SC_pub_syst[isc]->GetEY()[ip];
			double error_sum = TMath::Sqrt( staterr * staterr + systerr * systerr 	);
			gr_SC_Band[isc]->SetPointError( ip, 0.01, error_sum);
		}

		gr_SC_norm_Band[isc] = (TGraphErrors*)gr_SC_norm_pub[isc]->Clone();
		int NP = gr_SC_norm_pub[isc]->GetN();
		for(int ip=0; ip<NP; ip++){
			double staterr = gr_SC_norm_pub[isc]->GetEY()[ip];  
			double systerr = gr_SC_norm_pub_syst[isc]->GetEY()[ip]; 
			double error_sum = TMath::Sqrt( staterr * staterr + systerr * systerr 	);
			gr_SC_norm_Band[isc]->SetPointError( ip, 0, error_sum);
		}
	}
	//scaling
	for(int isc=0; isc<2; isc++){
		double Npoint = gr_SC_Band[isc]->GetN() ;
		for(int ipoint=0; ipoint < Npoint; ipoint++){
			double x = gr_SC_Band[isc]->GetX()[ipoint] ;
			double y = gr_SC_Band[isc]->GetY()[ipoint] * ScaleFactor[isc] ;
			double ex = gr_SC_Band[isc]->GetErrorX(ipoint) ;
			double ey = gr_SC_Band[isc]->GetErrorY(ipoint) * ScaleFactor[isc] ;
			gr_SC_Band[isc]->SetPoint( ipoint, x, y);
			gr_SC_Band[isc]->SetPointError( ipoint, ex, ey);
		}
	}

	gr_SC_Band[0]->SetFillStyle(fsty);
	gr_SC_Band[0]->SetMarkerColor(kBlue+1);
	gr_SC_Band[0]->SetLineColor(kBlue+1);
	gr_SC_Band[0]->SetFillColor(kBlue+1);
	gr_SC_Band[1]->SetFillStyle(fsty);
	gr_SC_Band[1]->SetMarkerColor(kRed);
	gr_SC_Band[1]->SetLineColor(kRed);
	gr_SC_Band[1]->SetFillColor(kRed);

	gr_SC_norm_Band[0]->SetFillStyle(fsty);
	gr_SC_norm_Band[0]->SetMarkerColor(kBlue+1);
	gr_SC_norm_Band[0]->SetLineColor(kBlue+1);
	gr_SC_norm_Band[0]->SetFillColor(kBlue+1);
	gr_SC_norm_Band[1]->SetFillStyle(fsty);
	gr_SC_norm_Band[1]->SetMarkerColor(kRed);
	gr_SC_norm_Band[1]->SetLineColor(kRed);
	gr_SC_norm_Band[1]->SetFillColor(kRed);
}

void RemovePoints(TGraphErrors *ge, double lcent)
{
	// Remove zero points from TGraphErrors.

	if(!ge){return;}

	Int_t nPoints = ge->GetN();
	Double_t x = 0.; 
	Double_t y = 0.; 
	int p =0; 
	while(p<nPoints) {
		ge->GetPoint(p,x,y);
		//if( x < 0.21 || x>8.  )
		if( x > lcent  )
		{   
			ge->RemovePoint(p);
			//			cout<<Form(" WARNING (%s): point %d is < 1.e-10 and it was removed from the plot !!!!",ge->GetName(),p+1)<<endl;
			nPoints = ge->GetN();
		} else {
			p++;
		}   
	} // end of for(Int_t p=0;p<nPoints;p++)

	//cout<<endl;
	return;

} // end of void RemoveZeroPoints(TGraphErrors *ge)
