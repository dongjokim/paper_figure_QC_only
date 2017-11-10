enum{ k0250, k0350, k0450, k0550, k0750, k0850, k0950, k1050, k1250, k1550, kNpt};
enum{ kSC32, kSC42, kNSC};
enum{ k0005, k0510, k1020, k2030, k3040, k4050, k5060, kNCent};
enum{ kSP, kQC, kNM};

int gOMarker[6] = {kOpenCircle, kFullCircle,kOpenSquare, kOpenStar, kFullSquare, kFullStar};
int gColor[6] =     {kBlack, kBlue,    kRed,    kGreen+4, kMagenta, kRed+1};
int gFillColor[6] = {kGray, kBlue-10, kRed-10, kGreen-10, kMagenta-10, kRed-10};

TString strSCType[kNSC] = {
	"SC(3,2)",
	"SC(4,2)"};

TString strSCnormType[kNSC] = {
	"NSC(3,2)",
	"NSC(4,2)"};

double ytitlesize = 0.095;
const int Npar=2;
TGraphErrors *gr_SC[kNM][kNpt][kNSC];
TGraphErrors *gr_NSC[kNM][kNpt][kNSC];

TGraphErrors *gr_SC_xpt[kNM][kNCent][kNSC];
TGraphErrors *gr_SC_xpt_err[kNM][kNCent][kNSC];
TGraphErrors *gr_NSC_xpt[kNM][kNCent][kNSC];
TGraphErrors *gr_NSC_xpt_err[kNM][kNCent][kNSC];
TGraphErrors *gr_NSC_xpt_ratio[kNM][kNCent][kNSC];

TGraphErrors *gr_NSC_xpt_EKRT[Npar][kNCent][kNSC];

double x_min =0.1;
double x_max =1.71;


TFile *fin_ampt[3][kNpt];
TGraphErrors *gr_SC_AMPT[3][kNM][kNpt][kNSC];
TGraphErrors *gr_NSC_xpt_AMPT[3][kNM][kNCent][kNSC];

bool Draw_AMPT[3] = {1,1,1}; // 13f3a, b, c
const double CentBins[kNCent+1] = {0, 5, 10, 20, 30, 40, 50, 60};
const double ptbins[kNpt+1] = {0.2, 0.3, 0.4, 0.5, 0.7, 0.8, 0.9, 1.0, 1.2, 1.5, 5.0 };

int gAMPTColor[3] = { kGreen+2, kRed, kBlue };
int gAMPTMarker[3] = { kOpenDiamond, kOpenCircle, kOpenSquare};
TString strAMPT[3] = {
	"AMPT string melting w/o hadronic rescattering",
	"AMPT default",
	"AMPT string melting"
};

TFile *fin[kNpt];
TString strFilename[kNpt] = {
	"results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0350_NoeffCorr.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0450_NoeffCorr.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0550_NoeffCorr.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0750_NoeffCorr.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0850.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt0950.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt1050.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt1250.root",
	"results_0720/results_LHC10h_JFFlucAODLHC10h_pt1550.root"
};

TString strGraphNameNSC[kNM][kNSC]= {
	"gr_SC_ratio_00", "gr_SC_ratio_01",
	"gr_SC_norm_with_QC_3223", "gr_SC_norm_with_QC_4224"
};

TString strGraphNameSC[kNM][kNSC]= {
	"gr_SC_ratio_00", "gr_SC_ratio_01",
	"gr_SC_with_QC_3223", "gr_SC_with_QC_4224"
};

void LoadAMPTResults(){

	TString AMPTfiles[3][kNpt] = {
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0250.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0350.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0450.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0550.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0750.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0850.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0950.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt1050.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt1250.root",
		"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt1550.root",

		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0250.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0350.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0450.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0550.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0750.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0850.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0950.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt1050.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt1250.root",
		"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt1550.root",

		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0250.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0350.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0450.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0550.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0750.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0850.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0950.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt1050.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt1250.root",
		"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt1550.root"
	};


	//load data part//
	cout << "start load AMPT" << endl;

	for(int iampt=0; iampt<3; iampt++){
		for(int ipt=0; ipt<kNpt; ipt++){
			fin_ampt[iampt][ipt] = new TFile( AMPTfiles[iampt][ipt].Data(), "read" );
			for(int im=0; im<kNM; im++){
				for(int isc=0; isc<kNSC; isc++){
					gr_SC_AMPT[iampt][im][ipt][isc] = (TGraphErrors*)fin_ampt[iampt][ipt]->Get(strGraphNameNSC[im][isc].Data());
				}
			}
		}
	}
	//load done	


	//init new graph
	for(int iampt=0; iampt<3; iampt++){
		for(int im=0; im<kNM; im++){
			for(int icent=0; icent<kNCent; icent++){
				for(int isc=0; isc<kNSC; isc++){
					gr_NSC_xpt_AMPT[iampt][im][icent][isc] = new TGraphErrors();
					gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetMarkerStyle( gAMPTMarker[iampt] );
					gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetMarkerSize(1.1);
					gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetMarkerColor( gAMPTColor[iampt] );
					gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetLineColor( gAMPTColor[iampt] );
					gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetFillStyle(3001);
					gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetFillColor( gAMPTColor[iampt] );
					//gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetLineStyle(2+iampt);
					gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetLineWidth(1.0);
				}
			}
		}
	}

	// convert part //
	for(int iampt=0; iampt<3; iampt++){ 
		for(int isc =0; isc<kNSC; isc++){
			for(int ipt=0; ipt<kNpt; ipt++){
				for(int im=0; im<kNM; im++){
					for(int icent=0; icent<kNCent; icent++){
						double x = ptbins[ipt]; 
						double y = gr_SC_AMPT[iampt][im][ipt][isc]->GetY()[icent];
						double ex = 0;
						double ey = gr_SC_AMPT[iampt][im][ipt][isc]->GetEY()[icent];

						gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetPoint( ipt, x, y);
						gr_NSC_xpt_AMPT[iampt][im][icent][isc]->SetPointError( ipt, ex, ey );
					}
				}
			}
		}
	};

};

void LoadEKRT(){
	TFile *fin_EKRT[2];
	fin_EKRT[0]  = new TFile("Harris_results/EKRT_eta_020_pt_NSC.root", "read");
	fin_EKRT[1]  = new TFile("Harris_results/EKRT_eta_par1_pt_NSC.root", "read");

	TString centbinname[7] = {"0005", "0510", "1020", "2030", "3040", "4050", "5060"};

	for(int ipar=0; ipar<2; ipar++){
		for(int icent=0; icent<kNCent; icent++){
			if(ipar==0 && icent==0) continue; // no 00~05 info for param 0
			if(ipar==1 && icent<=1) continue; // no 00~05, 05~10 info for param1
			for(int isc=0; isc<kNSC; isc++){
				cout << isc << " " << icent << " " << centbinname[icent].Data() <<  endl;
				gr_NSC_xpt_EKRT[ipar][icent][isc] = (TGraphErrors*)fin_EKRT[ipar]->Get(
						Form("gr_harri_SC_%d_x_minpT_Cent%s", isc, centbinname[icent].Data() ) );				
				gr_NSC_xpt_EKRT[ipar][icent][isc]->SetLineColor(ipar==0?kOrange+2:kViolet-1);
				gr_NSC_xpt_EKRT[ipar][icent][isc]->SetLineWidth(3);
				gr_NSC_xpt_EKRT[ipar][icent][isc]->SetLineStyle(1+ipar);
			}
		}
	}
	cout << "load EKRT data points... done" << endl;
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

void printGrrHepData(TGraphErrors *gr, TGraphErrors *gr_syst, const double *ptBins, ofstream *file=NULL){
    streambuf* sbuf = cout.rdbuf();
    if(file != NULL)  cout.rdbuf(file->rdbuf());

    double x[300], y[300], ex[300], ey[300];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii,x[ii],y[ii]);
        ex[ii] = gr->GetErrorX(ii);
        ey[ii] = gr->GetErrorY(ii);
    }
    double x_syst[300], y_syst[300], ex_syst[300], ey_syst[300];
    int NC_syst =  gr_syst->GetN();
    for(int ii=0;ii<NC;ii++){
        gr_syst->GetPoint(ii,x_syst[ii],y_syst[ii]);
        ex_syst[ii] = gr->GetErrorX(ii);
        ey_syst[ii] = gr->GetErrorY(ii);
    }
    for(int ii=0;ii<NC;ii++) {
           TString strData = Form("%.1f TO %.1f;\t%E +- %E (DSYS=%E)",ptBins[ii],ptBins[ii+1],y[ii],ey[ii],ey_syst[ii]);
           cout << strData << endl;
    }

    if(file != NULL) cout.rdbuf(sbuf);
}

void Draw_QConly_Fig2(){

	LoadAMPTResults();
	LoadEKRT();

	//NSC
	double systematics[kNM][kNpt][kNSC] = {
		0.226, 0.111, // sp, 0250, 
		0.128, 0.051, // sp, 0350
		0.124, 0.063, // sp, 0450
		0.131, 0.068, // sp 0550
		0.171, 0.103, // sp 0750
		0.170, 0.105, // 0850
		0.187, 0.133, // 0950
		0.197, 0.369, // 1050
		0.293, 0.480, // 1250
		0.409, 0.499, // 1550

		//QC
		0.092, 0.082, // from Ante's default
		0.0776, 0.1291,
		0.0584, 0.1362,
		0.0615, 0.1270,
		0.0623, 0.1107, // 0750
		0.0646, 0.1104, 
		0.0668, 0.1183,	
		0.0766, 0.1191,
		0.0957, 0.1213,
		0.1511, 0.1594 // 1550
	};
	//SC
	double systematicsSC[kNM][kNpt][kNSC] = {
		0.226, 0.111, // sp, 0250,  for NSC... %%% fix them // DJJ
		0.128, 0.051, // sp, 0350
		0.124, 0.063, // sp, 0450
		0.131, 0.068, // sp 0550
		0.171, 0.103, // sp 0750
		0.170, 0.105, // 0850
		0.187, 0.133, // 0950
		0.197, 0.369, // 1050
		0.293, 0.480, // 1250
		0.409, 0.499, // 1550

		//QC
		0.098, 0.169, // from Ante's default
		0.0525, 0.1808,  // 0.3 ~ 5.0
		0.0466, 0.1898,  // 0.4 ~ 5.0
		0.0544, 0.1794,  // 0.5 ~ 5.0
		0.0697, 0.1558,   // 0.7 ~ 5.0
		0.0713, 0.1515,  // 0.8 ~ 5.0
		0.0737, 0.1617,  // 0.9 ~ 5.0
		0.0823, 0.1533,  // 10 ~ 5.0
		0.1026, 0.1405,   // 12 ~ 5.0
		0.1591, 0.1631  // 1.5
	};

	//load data part//
	cout << "start load data" << endl;
	for(int ipt=0; ipt<kNpt; ipt++){
		fin[ipt] = new TFile( strFilename[ipt].Data(), "read" );
		fin[ipt]->Print();
		//load file here

		for(int im=0; im<kNM; im++){
			for(int isc=0; isc<kNSC; isc++){
				gr_NSC[im][ipt][isc] = (TGraphErrors*)fin[ipt]->Get(strGraphNameNSC[im][isc].Data());
				gr_SC[im][ipt][isc] = (TGraphErrors*)fin[ipt]->Get(strGraphNameSC[im][isc].Data());
			}
		}
	}
	cout << "load datafiles and grpha done.." << endl;
	//load done	

	//init new graph
	for(int im=0; im<kNM; im++){
		for(int icent=0; icent<kNCent; icent++){
			for(int isc=0; isc<kNSC; isc++){
				gr_NSC_xpt[im][icent][isc] = new TGraphErrors();
				gr_NSC_xpt[im][icent][isc]->SetMarkerStyle( gOMarker[icent] );
				gr_NSC_xpt[im][icent][isc]->SetMarkerSize(1.2);
				gr_NSC_xpt[im][icent][isc]->SetMarkerColor( gColor[icent] );
				gr_NSC_xpt[im][icent][isc]->SetLineColor( gColor[icent] );
				gr_NSC_xpt[im][icent][isc]->SetFillColor( gFillColor[icent] );
				//gr_NSC_xpt[im][icent][isc]->SetFillColor( kGray );

				gr_SC_xpt[im][icent][isc] = new TGraphErrors();
				gr_SC_xpt[im][icent][isc]->SetMarkerStyle( gOMarker[icent] );
				gr_SC_xpt[im][icent][isc]->SetMarkerSize(1.2);
				gr_SC_xpt[im][icent][isc]->SetMarkerColor( gColor[icent] );
				gr_SC_xpt[im][icent][isc]->SetLineColor( gColor[icent] );
				gr_SC_xpt[im][icent][isc]->SetFillColor( kGray );
			}
		}
	}
	//int done
	cout <<"converting....."<< endl;

	// convert part // 
	for(int isc =0; isc<kNSC; isc++){
		for(int ipt=0; ipt<kNpt; ipt++){
			for(int im=0; im<kNM; im++){
				for(int icent=0; icent<kNCent; icent++){
					double x = ptbins[ipt]; 

					double y = gr_SC[im][ipt][isc]->GetY()[icent];
					double ex = 0;
					double ey = gr_SC[im][ipt][isc]->GetEY()[icent];
					gr_SC_xpt[im][icent][isc]->SetPoint( ipt, x, y);
					gr_SC_xpt[im][icent][isc]->SetPointError( ipt, ex, ey );

					double yn = gr_NSC[im][ipt][isc]->GetY()[icent];
					double eyn = gr_NSC[im][ipt][isc]->GetEY()[icent];
					gr_NSC_xpt[im][icent][isc]->SetPoint( ipt, x, yn);
					gr_NSC_xpt[im][icent][isc]->SetPointError( ipt, ex, eyn );
				}
			}
		}
	}
	// Add systematics for data
	for(int isc=0; isc<kNSC; isc++){
		for(int icent=0; icent<kNCent; icent++){
			for(int im=0; im<kNM; im++){
				gr_NSC_xpt_err[im][icent][isc] = (TGraphErrors*)gr_NSC_xpt[im][icent][isc]->Clone();
				gr_NSC_xpt_err[im][icent][isc]->SetFillColor( gFillColor[icent]  );
				gr_SC_xpt_err[im][icent][isc] = (TGraphErrors*)gr_SC_xpt[im][icent][isc]->Clone();
				gr_SC_xpt_err[im][icent][isc]->SetFillColor( gFillColor[icent]  );
			}
		}
	}
	for(int isc =0; isc<kNSC; isc++){
		for(int ipt=0; ipt<kNpt; ipt++){
			for(int im=0; im<kNM; im++){
				for(int icent=0; icent<kNCent; icent++){
					double systerr = gr_NSC_xpt_err[im][icent][isc]->GetY()[ipt] * systematics[im][ipt][isc];
					gr_NSC_xpt_err[im][icent][isc]->SetPointError( ipt, 0.03, systerr );

					double systerrSC = gr_SC_xpt_err[im][icent][isc]->GetY()[ipt] * systematicsSC[im][ipt][isc];
					gr_SC_xpt_err[im][icent][isc]->SetPointError( ipt, 0.03, systerrSC );
				}
			}
		}
	}
	// 


	// Calcultae ratio
	for(int im=0; im<kNM; im++){
		for(int ic=0; ic<kNCent; ic++){
			for(int isc=0; isc<kNSC; isc++){
				gr_NSC_xpt_ratio[im][ic][isc] = CalculateRatio( gr_NSC_xpt[im][ic][isc] , gr_NSC_xpt[kQC][ic][isc], 0 );
				gr_NSC_xpt_ratio[im][ic][isc]->SetMarkerStyle( 24+im );
				gr_NSC_xpt_ratio[im][ic][isc]->SetMarkerSize(1.2);
				gr_NSC_xpt_ratio[im][ic][isc]->SetMarkerColor( isc==0?kBlue:kRed );
				gr_NSC_xpt_ratio[im][ic][isc]->SetLineColor( isc==0?kBlue:kRed);
			}
		}
	}


	//*********************************************************************************
	// New 2X5 Figures //
	//*********************************************************************************

	TGaxis::SetExponentOffset(0.04, -0.1150, "y");

	//TLegend *legmult = new TLegend( 0.35, 0.79, 0.80, 0.98, NULL, "brNDC");
	TLegend *legmult = new TLegend( 0.23, 0.10, 0.50, 0.32, NULL, "brNDC");
	legmult->AddEntry((TObject*)NULL,"ALICE Pb-Pb #sqrt{#it{s}_{NN}} = 2.76 TeV","");
	legmult->AddEntry((TObject*)NULL,"|#eta| < 0.8, #it{p}_{T,min} < #it{p}_{T} < 5 GeV/#it{c}","");
	legmult->SetTextSize(0.060);
	legmult->SetBorderSize(0);
	legmult->SetFillStyle(0);

	//TLegend *legCent = new TLegend( 0.27, 0.05, 0.53, 0.45, NULL, "brNDC");
	TLegend *legCent = new TLegend( 0.35, 0.40, 0.60, 0.80, NULL, "brNDC");
	legCent->SetTextSize(0.060);
	legCent->SetBorderSize(0);
	legCent->SetFillStyle(0);

	const int cNX = 2; // number of pad along X
	const int cNY = 2; // number of pad along y
	double canvas_width = 860;
	double canvas_height = 600;
	double W = 0.49; //(pad width as ratio);
	double Xm = (1- cNX*W)/2.; // xmargin
	double H = 0.44; // pad height as ratio;
	double Ym = (1- cNY*H)/2.;

	double ypos[cNY+1];
	for(int i=0; i<cNY+1; i++){
		if(i==0) ypos[i] = Ym + 0.02;
		if(i!=0) ypos[i] = Ym + i* H +0.02; // give label size for bottom pad
		cout << ypos[i] << endl;;
	}

	//double Ref_Histo_SC_y_min[cNY] = { -225.2e-7, -29.2e-7};
	//double Ref_Histo_SC_y_max[cNY] = { 9.2e-6, 290.6e-7};
	double Ref_Histo_SC_y_min[cNY] = { -732.2e-7, -79.2e-7};
	double Ref_Histo_SC_y_max[cNY] = { 12.5e-6, 124.6e-6};
	//double Ref_Histo_SC_y_max[cNY] = { 28.2e-6, 124.6e-6};
	double Ref_Histo_NSC_y_min[cNY] = {-0.22, -0.1};
	double Ref_Histo_NSC_y_max[cNY] = {0.02,0.92};

	int sc_number[2][2] = { 3,2,
		4,2};

	TCanvas *c100 = new TCanvas("c100", "", canvas_width, canvas_height);
	TPad *pads[cNX][cNY];
	for(int ix=0; ix<cNX; ix++){
		for(int iy=0; iy<cNY; iy++){

			pads[ix][iy] = new TPad(Form("p%d%d",ix, iy), "",
					Xm + ix*W,  ypos[iy],
					Xm + (ix+1)*W, ypos[iy+1],
					0, 0, 0 );
			if(ix==0) pads[ix][iy]->SetRightMargin(0);
			if(ix==0) pads[ix][iy]->SetLeftMargin(0.23);
			if(ix==1) pads[ix][iy]->SetLeftMargin(0);
			if(ix==1) pads[ix][iy]->SetRightMargin(0.23);
			if(iy==1) pads[ix][iy]->SetBottomMargin(0);
			pads[ix][iy]->SetTopMargin(0);
			pads[ix][iy]->Draw();
		}
	}

	cout << "pads are ready" << endl;


	TH2D *hSCReference[cNY];
	TH2D *hNSCReference[cNY];
	for(int i=0; i<cNY; i++){
		hSCReference[i] = new TH2D( Form("hrefSC%d",i), "", 100, x_min, x_max, 10, Ref_Histo_SC_y_min[i], Ref_Histo_SC_y_max[i]);
		hNSCReference[i] = new TH2D( Form("hrefNSC%d",i), "", 100, x_min, x_max, 10, Ref_Histo_NSC_y_min[i], Ref_Histo_NSC_y_max[i]);

		int m = sc_number[i][0];
		int n = sc_number[i][1];

		hSCReference[i]->SetStats(0);
		hSCReference[i]->GetYaxis()->SetTitle(Form("SC(%d,%d)   ", m, n) );
		hSCReference[i]->GetYaxis()->SetTitleOffset(0.85);
		hSCReference[i]->GetYaxis()->SetTitleSize(ytitlesize);
		hSCReference[i]->GetYaxis()->SetLabelSize(0.07);

		hNSCReference[i]->SetStats(0);
		hNSCReference[i]->GetYaxis()->SetTitle(Form("NSC(%d,%d) ", m, n) );
		hNSCReference[i]->GetYaxis()->SetTitleOffset(0.83);
		hNSCReference[i]->GetYaxis()->SetTitleSize(ytitlesize);
		hNSCReference[i]->GetYaxis()->SetLabelSize(0.07);

		if(i==1){
			hSCReference[i]->GetXaxis()->SetLabelSize(0.07);
			hNSCReference[i]->GetXaxis()->SetLabelSize(0.07);
		}


	}

	TLatex *latex2 = new TLatex();
	latex2->SetTextSize(0.04);
	latex2->SetTextFont(42);
	c100->cd();
	latex2->DrawLatexNDC( 0.25, 0.05, "#it{p}_{T,min} [GeV/#it{c}]");
	latex2->DrawLatexNDC( 0.65, 0.05, "#it{p}_{T,min} [GeV/#it{c}]");

	TLine *l0 = new TLine(x_min,0,x_max,0);
	l0->SetLineStyle(2);

	for(int ix=0; ix<cNX; ix++){
		for(int iy=0; iy<cNY; iy++){
			pads[ix][1-iy]->cd();

			if(ix==0){ // left pannel SC
				hSCReference[iy]->Draw();
				l0->Draw();
				for(int ic=0;ic<kNCent-1;ic++) {
					gr_SC_xpt_err[kQC][ic][iy]->Draw("same 2");
					gr_SC_xpt[kQC][ic][iy]->Draw("same p,Z");
					cout <<"*dataset:"<<endl;
					cout <<"*location: Figure 2"<<endl;
					cout <<"*dscomment: Centrality dependence of observables "<<strSCType[iy]<<" in Pb-Pb collisions at 2.76 TeV"<<endl;
					cout <<"*reackey: PB PB --> CHARGED X"<<endl;
					cout <<"*obskey: SC"<<endl;
					cout <<"*qual: CENTRALITY : "<<CentBins[ic]<<"-"<<CentBins[ic+1] <<"%"<<endl;
					cout <<"*qual: ETARAP : -0.8 TO 0.8"<<endl;
					cout <<"*qual: RE : PB PB --> CHARGED X"<<endl;
					cout <<"*qual: SQRT(S)/NUCLEON IN GEV : 2760"<<endl;
					cout <<"*xheader: PTMIN IN (GeV/c)"<<endl;
					cout <<"*yheader: "<<strSCType[iy]<<endl;
					cout <<"*data: x : y"<<endl;
					printGrrHepData(gr_SC_xpt[kQC][ic][iy], gr_SC_xpt_err[kQC][ic][iy],ptbins,NULL);
					cout <<"*dataend:"<<endl;
					cout << endl;
					if(iy==0) legCent->AddEntry(gr_NSC_xpt[kQC][ic][iy], Form("%2.f - %2.f%%", CentBins[ic], CentBins[ic+1]));
				}
			}


			if(ix==1){ // right pannel
				hNSCReference[iy]->Draw("Y+");
				l0->Draw();
				for(int ic=0;ic<kNCent-1;ic++) {
					gr_NSC_xpt_err[kQC][ic][iy]->Draw("same 2");
				}
				for(int ic=0;ic<kNCent-1;ic++) {
					gr_NSC_xpt[kQC][ic][iy]->Draw("same p,Z");
					cout <<"*dataset:"<<endl;
					cout <<"*location: Figure 2"<<endl;
					cout <<"*dscomment: Centrality dependence of observables "<<strSCnormType[iy]<<" in Pb-Pb collisions at 2.76 TeV"<<endl;
					cout <<"*reackey: PB PB --> CHARGED X"<<endl;
					cout <<"*obskey: NSC"<<endl;
					cout <<"*qual: CENTRALITY : "<<CentBins[ic]<<"-"<<CentBins[ic+1] <<"%"<<endl;
					cout <<"*qual: ETARAP : -0.8 TO 0.8"<<endl;
					cout <<"*qual: RE : PB PB --> CHARGED X"<<endl;
					cout <<"*qual: SQRT(S)/NUCLEON IN GEV : 2760"<<endl;
					cout <<"*xheader: PTMIN IN (GeV/c)"<<endl;
					cout <<"*yheader: "<<strSCnormType[iy]<<endl;
					cout <<"*data: x : y"<<endl;
					printGrrHepData(gr_NSC_xpt[kQC][ic][iy], gr_NSC_xpt_err[kQC][ic][iy],ptbins,NULL);
					cout <<"*dataend:"<<endl;
					cout << endl;
				}
			}
			if(ix==0&&iy==0) {
				legmult->Draw();
				//legCent->Draw();
			}
			if(ix==0&&iy==1) {
				legCent->Draw();
			}
		}

	}
	TString strPadName[4] = {"(a)","(b)","(c)","(d)"};
	TLatex latexPad;
	latexPad.SetTextSize(0.08);
	for(int ix=0; ix<cNX; ix++){
		for(int iy=0; iy<cNY; iy++){
			pads[ix][1-iy]->cd();
			if(ix==0) latexPad.DrawLatexNDC( 0.92, 0.92 , strPadName[ix+2*iy]);
			if(ix==1) latexPad.DrawLatexNDC( 0.69, 0.92 , strPadName[ix+2*iy]);
		}
	}
	c100->SaveAs("figs/Fig2_pt_SC_NSC.eps");
}


