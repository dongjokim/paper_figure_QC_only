// configuration
bool Draw_TLatex = kFALSE;
int gFillStyle[2]={1000, 3002};
TString strFileName = "results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root";
enum { kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};
enum { kEKRT, kVISH, kAMPT, kNmodel};
TString strModel[3] = { "EKRT","VISH","AMPT"};

bool Draw_old_EKRT=false;
// Hydro calculation
enum {kParm0, kParm1, kParm2, kParm3, kParm4, kNParm};
bool Draw_Harris_Hydro[kNParm] = {1,1,1,1,1};
bool Draw_Harris_norm_Hydro[kNParm] = {1,1,1,1,1};

TGraphErrors *gr_SC_Hydro[kNParm][2];
TGraphErrors *gr_SC_norm_Hydro[kNParm][2];
TString finHydro = "Harris_results/Harris_SC_datapoint.root";

int gDataColor = kBlack;
int gDataFillColor = kGray;

int gOMarker[5] = {kOpenCircle, kOpenSquare, kOpenDiamond, 30, 27};
int gColor[5] = {kBlue, kRed, kGreen+2, kOrange-1, kRed+1};
int gFillColor[3] = { kGreen-3, kCyan+2, kYellow-6};
//int gHarriEtaColor[5] = { kBlue, kBlack, kRed, kGreen+2, kOrange-3};
int gHarriEtaColor[5] = { kBlue+1, kRed+1, kRed, kGreen+2, kOrange-3};
const int Npar=2;

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
	0, 0, // VISH2+1 calculation with AMPT initial conditions
	0, 0, // VISH2+1 calculation with KLN initial condigtions
	0, 0 // VISH2+1 calcuation with Glauber initial condistions.
};
TString strVISHconf[kNVISH][kVNvisco] = {
	"AMPT, #eta/s=0.08",
	"AMPT, #eta/s=0.16",
	"MC-KLN, #eta/s=0.08",
	"MC-KLN, #eta/s=0.2",
	"MC-Glauber, #eta/s=0.08",
	"MC-Glauber, #eta/s=0.2"	
};



int sc_number[5][2] = { 3,2,
	4,2,
	5,2,
	5,3,
	4,3};

TString strSCType[kNSC] = { 
	"SC(3,2)","SC(4,2)","SC(5,2)","SC(5,3)","SC(4,3)"}; 
TString strSCnormType[kNSC] = {
	"SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT",
	"SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT",
	"SC(5,2)/#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT",
	"SC(5,3)/#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT",
	"SC(4,3)/#LTv_{4}^{2}#GT#LTv_{3}^{2}#GT"};
TString strAMPTName[kNAMPT] ={
	"string melting without hadronic rescattering",
	"default",
	"string melting"
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

TGraphErrors *gr_SC_EKRT[2][kNSC];
TGraphErrors *gr_NSC_EKRT[2][kNSC];

// chisqared test results as a function of oberables, fist index 0 SC, 1 NSC
TGraphErrors *gr_VISH_chisq[2][kNVISH][kVNvisco];
TGraphErrors *gr_EKRT_chisq[2][2];
TGraphErrors *gr_AMPT_chisq[2][kNAMPT];

double YlabelOffset = 1.21;

void LoadHydro(){
	TFile *fin_hydro = new TFile( Form("%s", finHydro.Data(), "read"));
	fin_hydro->Print();
	for(int ipar=0; ipar<kNParm; ipar++){
		for(int isc=0; isc<2; isc++){
			cout << ipar <<  " " << isc << endl;
			gr_SC_Hydro[ipar][isc] = (TGraphErrors*)fin_hydro->Get(Form("gr_harri_SC_%d_par%d", isc, ipar) );
			gr_SC_norm_Hydro[ipar][isc] = (TGraphErrors*)fin_hydro->Get(Form("gr_harri_SC_%d_Norm_par%d", isc, ipar) );

			cout << "a" << endl;
			gr_SC_Hydro[ipar][isc]->Print();
			cout << "b" << endl;
			gr_SC_norm_Hydro[ipar][isc]->Print();

			gr_SC_Hydro[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
			gr_SC_Hydro[ipar][isc]->SetLineWidth( 1 );
			gr_SC_Hydro[ipar][isc]->SetLineStyle( 1 + ipar );

			gr_SC_norm_Hydro[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
			gr_SC_norm_Hydro[ipar][isc]->SetLineWidth( 1);
			gr_SC_norm_Hydro[ipar][isc]->SetLineStyle( 1+ ipar);

		}
	}
	cout << "Load Harri's data point... done " << endl;

}

void LoadSCResults(){
	cout << "start load data" << endl;
	TFile *fin = new TFile( Form("%s", strFileName.Data() ), "read" );
	TString strGrSCName[kNSC] = { 
		"gr_SC_with_QC_3223",
		"gr_SC_with_QC_4224",
		"gr_SC_with_QC_5225",
		"gr_SC_with_QC_5335",
		"gr_SC_with_QC_4334"};
	TString strGrSCnormName[kNSC] = {
		"gr_SC_norm_with_QC_3223",
		"gr_SC_norm_with_QC_4224",
		"gr_SC_norm_with_QC_5225",
		"gr_SC_norm_with_QC_5335",
		"gr_SC_norm_with_QC_4334"};


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
		"gr_SC_with_QC_4334"};
	TString strGrSCnormName[kNSC] = {
		"gr_SC_norm_with_QC_3223",
		"gr_SC_norm_with_QC_4224",
		"gr_SC_norm_with_QC_5225",
		"gr_SC_norm_with_QC_5335",
		"gr_SC_norm_with_QC_4334"};

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
			gr_SC_AMPT[iset][isc]->SetMarkerColor( gColor[iset] );
			gr_SC_AMPT[iset][isc]->SetLineColor( gColor[iset] );
			gr_SC_AMPT[iset][isc]->SetMarkerStyle( gOMarker[iset] );
			gr_SC_AMPT[iset][isc]->SetMarkerSize( 1.2);
			//gr_SC_AMPT[iset][isc]->SetLineStyle( 2+ iset);
			gr_SC_AMPT[iset][isc]->SetLineWidth(1.5);

			gr_SC_norm_AMPT[iset][isc] = (TGraphErrors*) fin[iset]->Get(Form("%s", strGrSCnormName[isc].Data() ) );
			gr_SC_norm_AMPT[iset][isc]->SetMarkerColor( gColor[iset] );
			gr_SC_norm_AMPT[iset][isc]->SetLineColor( gColor[iset] );
			gr_SC_norm_AMPT[iset][isc]->SetMarkerStyle( gOMarker[iset] );
			gr_SC_norm_AMPT[iset][isc]->SetMarkerSize( 1.2);
			//gr_SC_norm_AMPT[iset][isc]->SetLineStyle( 2+iset );
			gr_SC_norm_AMPT[iset][isc]->SetLineWidth(1.5);

			//remove datapoint over 50 cent
			gr_SC_norm_AMPT[iset][isc]->RemovePoint(6);
			gr_SC_AMPT[iset][isc]->RemovePoint(6);

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
	};
	TString VISH_norm[kNVISH]={
		"VISH_simdata/AMPT/resultSCR.root",
		"VISH_simdata/KLN/resultSCR.root",
		"VISH_simdata/Glb/resultSCR.root"
	};
	TFile *fin_VISH[kNVISH];
	TFile *fin_VISH_norm[kNVISH];
	for(int ivish=0; ivish<kNVISH; ivish++){
		fin_VISH[ivish] = new TFile( VISH[ivish].Data(), "read");
		fin_VISH_norm[ivish] = new TFile( VISH_norm[ivish].Data(), "read");
	}	


	// load files done.
	TString strVISHSCgraph[kNSC] = {
		"SC32", "SC42", "SC52", "SC53", "SC43"
	};
	for(int iset=0; iset<kNVISH; iset++){
		for(int isc=0; isc< kNSC; isc++){
			for(int ieta=0; ieta<kVNvisco; ieta++){
				gr_SC_VISH[isc][iset][ieta] = (TGraphErrors*)fin_VISH[iset]->Get(Form("%s_%d", strVISHSCgraph[isc].Data(), ieta));
				gr_SC_norm_VISH[isc][iset][ieta] = (TGraphErrors*)fin_VISH_norm[iset]->Get(Form("%s_%d",strVISHSCgraph[isc].Data(),ieta));


				//remove datapoint above 50centralities
				gr_SC_VISH[isc][iset][ieta]->RemovePoint(6);
				gr_SC_norm_VISH[isc][iset][ieta]->RemovePoint(6);
				//
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

// Load Hydro cal

void LoadEKRT(){
	cout << "start" << endl;
	TFile *fin_EKRT[2];
	fin_EKRT[0]  = new TFile("Harris_results/EKRT_eta_020_pt_NSC.root", "read");
	fin_EKRT[1]  = new TFile("Harris_results/EKRT_eta_par1_pt_NSC.root", "read");
	for(int ipar=0; ipar<2; ipar++){
		for(int isc=0; isc<kNSC; isc++){
			gr_SC_EKRT[ipar][isc]=(TGraphErrors*)fin_EKRT[ipar]->Get(Form("gr_harri_SC_%d_pt_1", isc) );
			gr_NSC_EKRT[ipar][isc]=(TGraphErrors*)fin_EKRT[ipar]->Get(Form("gr_harri_NSC_%d_pt_1", isc) );

			gr_SC_EKRT[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
			gr_SC_EKRT[ipar][isc]->SetLineWidth(3);
			gr_SC_EKRT[ipar][isc]->SetLineStyle( 1+ipar);
			gr_NSC_EKRT[ipar][isc]->SetLineColor( gHarriEtaColor[ipar] );
			gr_NSC_EKRT[ipar][isc]->SetLineWidth(3);
			gr_NSC_EKRT[ipar][isc]->SetLineStyle( 1+ipar);

		}
	}
	cout << "load EKRT data points... done" << endl;
}
//TGraphErrors *gr_SC_EKRT[2][kNSC]; // only param0, and par1 at this moment
//TGraphErrors *gr_NSC_EKRT[2][kNSC]; // only param0, and par1 at this moment


double calculate_chisquared( TGraphErrors *gr_data, TGraphErrors *gr_data_syst, TGraphErrors *gr_theory) {
	//gr_data->Print();
	//gr_theory->Print();
	int NPoint = gr_data->GetN();
	TGraph ger( gr_theory->GetN(), gr_theory->GetX(), gr_theory->GetEY() ); // << Err estimation of gr2
	Double_t chisq = 0.;
	for(int i=0; i<NPoint; i++){
		double x = gr_data->GetX()[i];
		if(x>10 && x<50) {
			double data = gr_data->GetY()[i];
			double err_data = gr_data->GetEY()[i]; 
			double err_data_syst = gr_data_syst->GetEY()[i];
			double tho = gr_theory->Eval(x);
			double err_tho = ger.Eval(x);
			err_data = TMath::Sqrt(err_data*err_data + err_data_syst*err_data_syst + err_tho*err_tho);
			// chi square is the quadratic sum of the distance from the point to the function weighted by its error
			double delta  = TMath::Abs(data-tho)/TMath::Abs(err_data);
    		chisq += delta*delta;
			cout << i <<"\t"<< x <<"\t"<< data <<"\t"<< tho << "\t"<< TMath::Power(TMath::Abs(data-tho),2.) <<"\t"<<  chisq<< endl;
		}
	}
	//cout << chisq << endl;
	return chisq/4.;
}

void Draw_QConly_Fig456(int imodel=kEKRT){
	gStyle->SetErrorX(0);
	TGaxis::SetExponentOffset(0.05, -0.144, "y");
	TGaxis::SetMaxDigits(5);

	if(Draw_old_EKRT){LoadHydro();}
	LoadSCResults();
	LoadAMPT();
	LoadVISH();
	LoadEKRT();
	cout << "load done. start draw " << endl;
	//===================================================================================
	// Calculate chisquared
	double ekrt_SC_chisq[2][kNSC];
	double ekrt_NSC_chisq[2][kNSC];
	double vish_SC_chisq[kNVISH][kVNvisco][kNSC];
	double vish_NSC_chisq[kNVISH][kVNvisco][kNSC];
	double ampt_SC_chisq[kNAMPT][kNSC];
	double ampt_NSC_chisq[kNAMPT][kNSC];

	int inc = 1;
	for(int iy=0;iy<kNSC;iy++){
		ekrt_SC_chisq[0][iy] = calculate_chisquared(gr_SC[iy], gr_SC_syst[iy], gr_SC_EKRT[0][iy]);
		ekrt_SC_chisq[1][iy] = calculate_chisquared(gr_SC[iy], gr_SC_syst[iy], gr_SC_EKRT[1][iy]);
		ekrt_NSC_chisq[0][iy] = calculate_chisquared(gr_SC_norm[iy], gr_SC_norm_syst[iy], gr_NSC_EKRT[0][iy]);
		ekrt_NSC_chisq[1][iy] = calculate_chisquared(gr_SC_norm[iy], gr_SC_norm_syst[iy], gr_NSC_EKRT[1][iy]);
	}
	// VISH
    for(int iset=0; iset<kNVISH; iset++){
        for(int ieta=0; ieta<kVNvisco; ieta++){
            for(int isc=0; isc< kNSC; isc++){
				vish_SC_chisq[iset][ieta][isc] = calculate_chisquared(gr_SC[isc], gr_SC_syst[isc], gr_SC_VISH[isc][iset][ieta]);
				vish_NSC_chisq[iset][ieta][isc] = calculate_chisquared(gr_SC_norm[isc], gr_SC_norm_syst[isc], gr_SC_norm_VISH[isc][iset][ieta]);
			}
		}
	}
	//AMPT
	for(int iset=0; iset<kNAMPT; iset++){
		for(int isc=0; isc< kNSC; isc++){
			ampt_SC_chisq[iset][isc] = calculate_chisquared(gr_SC[isc], gr_SC_syst[isc], gr_SC_AMPT[iset][isc]);
			ampt_NSC_chisq[iset][isc] = calculate_chisquared(gr_SC_norm[isc], gr_SC_norm_syst[isc], gr_SC_norm_AMPT[iset][isc]);
		}
	}

	double obsX[kNSC+1]={kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};

	for(int iset=0;iset<2;iset++) {
		gr_EKRT_chisq[0][iset] = new TGraphErrors(kNSC,obsX,ekrt_SC_chisq[iset],0,0);
		gr_EKRT_chisq[1][iset] = new TGraphErrors(kNSC,obsX,ekrt_NSC_chisq[iset],0,0);
	}
	for(int iset=0; iset<kNVISH; iset++){
        for(int ieta=0; ieta<kVNvisco; ieta++){
			gr_VISH_chisq[0][iset][ieta] = new TGraphErrors(kNSC,obsX,vish_SC_chisq[iset][ieta],0,0);
			gr_VISH_chisq[1][iset][ieta] = new TGraphErrors(kNSC,obsX,vish_NSC_chisq[iset][ieta],0,0);
		}
	}
	for(int iset=0; iset<kNAMPT; iset++){
		gr_AMPT_chisq[0][iset] = new TGraphErrors(kNSC,obsX,ampt_SC_chisq[iset],0,0);
		gr_AMPT_chisq[1][iset] = new TGraphErrors(kNSC,obsX,ampt_NSC_chisq[iset],0,0);
	}
	// wrinting the resuts into a rootfile
	TFile *fout = new TFile("chisquaredndf_results.root","recreate");
	fout->cd();
	for(int iset=0;iset<2;iset++) {
		if(iset==0){
			gr_EKRT_chisq[0][iset]->SetTitle("param0 (#eta/s=0.2)");gr_EKRT_chisq[1][iset]->SetTitle("param0 (#eta/s=0.2)");
		}
		if(iset==1){
			gr_EKRT_chisq[0][iset]->SetTitle("param1 (#eta/s(T))");gr_EKRT_chisq[1][iset]->SetTitle("param1 (#eta/s(T))");
		}
		gr_EKRT_chisq[0][iset]->Write(Form("gr_EKRT_SC_parm%02d",iset));
		gr_EKRT_chisq[1][iset]->Write(Form("gr_EKRT_NSC_parm%02d",iset));
	}
	for(int iset=0; iset<kNVISH; iset++){
        for(int ieta=0; ieta<kVNvisco; ieta++){
        	gr_VISH_chisq[0][iset][ieta]->SetTitle(strVISHconf[iset][ieta]);
			gr_VISH_chisq[0][iset][ieta]->Write(Form("gr_VISH_SC_%02d%02d_chisq",iset,ieta));
			gr_VISH_chisq[1][iset][ieta]->SetTitle(strVISHconf[iset][ieta]);
			gr_VISH_chisq[1][iset][ieta]->Write(Form("gr_VISH_NSC_%02d%02d_chisq",iset,ieta));
		}
	}
	for(int iset=0; iset<kNAMPT; iset++){
		gr_AMPT_chisq[0][iset]->SetTitle(strAMPTName[iset]);
		gr_AMPT_chisq[0][iset]->Write(Form("gr_AMPT_SC_%2d_chisq",iset));
		gr_AMPT_chisq[1][iset]->SetTitle(strAMPTName[iset]);
		gr_AMPT_chisq[1][iset]->Write(Form("gr_AMPT_NSC_%2d_chisq",iset));
	}
	fout->Write();fout->Close();

	//*********************************************************************************
	// New 2X5 Figures //
	//*********************************************************************************


	TLegend *legmult = new TLegend( 0.09, 0.07, 0.53, 0.35, NULL, "brNDC");
	legmult->AddEntry((TObject*)NULL,"Pb-Pb #sqrt{#it{s}_{NN}} = 2.76 TeV","");
	legmult->AddEntry((TObject*)NULL,"|#eta| < 0.8, 0.2 < #it{p}_{T} < 5.0 GeV/#it{c}","");
	legmult->SetTextSize(0.12);
	legmult->SetBorderSize(0);
	legmult->SetFillStyle(0);

	TLegend *legData = new TLegend( 0.7, 0.8, 0.9, 0.90, NULL, "brNDC");
	legData->SetTextSize(0.12);
	legData->SetBorderSize(0);
	legData->SetFillStyle(0);
	legData->AddEntry(gr_SC[0],"ALICE","pl");

	TLegend *legModel;
	if(imodel == kEKRT) {
		legModel = new TLegend( 0.18, 0.50, 0.5, 0.89, NULL, "brNDC");
		legModel->SetTextSize(0.12);
		legModel->SetBorderSize(0);
		legModel->SetFillStyle(0);
		legModel->AddEntry((TObject*)NULL,"EKRT+Viscous Hydrodynamics","");
		legModel->AddEntry( gr_SC_EKRT[0][0], "param0 (#eta/s=0.2)", "l");
		legModel->AddEntry( gr_SC_EKRT[1][1], "param1 (#eta/s(T))", "l");
	} 
	if(imodel==kVISH) {
		legModel = new TLegend( 0.18, 0.23, 0.45, 0.850, "VISH2+1", "brNDC");
		legModel->SetTextSize(0.09);
		legModel->SetBorderSize(0);
		legModel->SetFillStyle(0);
	}
	if(imodel == kAMPT) {
		legModel = new TLegend( 0.19, 0.40, 0.5, 0.85, "AMPT", "brNDC");
		legModel->SetTextSize(0.11);
		legModel->SetBorderSize(0);
		legModel->SetFillStyle(0);
	}

	const int cNX = 2; // number of pad along X
	const int cNY = 5; // number of pad along y
	double canvas_width = 1000;
	double canvas_height = 1600;
	double canvas_margin_x = 10;
	double W = 0.46; //(pad width as ratio);
	double Xm = (1- cNX*W)/2; // xmargin
	double H = 0.182; // pad height as ratio;
	double Ym = (1- cNY*H)/2;

	double ypos[cNY+1];
	for(int i=0; i<cNY+1; i++){
		if(i==0) ypos[i] = Ym + 0.02;
		if(i!=0) ypos[i] = Ym + i* H +0.02; // give label size for bottom pa
		//cout << ypos[i] << endl;;
	}

	double *Ref_Histo_SC_y_min;
	double *Ref_Histo_SC_y_max;
	double *Ref_Histo_NSC_y_min;
	double *Ref_Histo_NSC_y_max;
	if(imodel==kEKRT) {
		static double a[cNY] = { -16.1e-7, -4.2e-7, -0.19e-7, -0.06e-7, -0.74e-7 };
		static double b[cNY] = { 2.8e-7, 28.6e-7, 2.1e-7, 0.63e-7, 0.9e-8};
		static double c[cNY] = {-0.19, -0.1, -0.08,-0.08 , -0.39 };
		static double d[cNY] = {0.01,0.999, 0.599, 1.7, 0.016};
		Ref_Histo_SC_y_min = a;
		Ref_Histo_SC_y_max = b;
		Ref_Histo_NSC_y_min = c;
		Ref_Histo_NSC_y_max = d;
	}
	if(imodel==kVISH) {
		static double a[cNY] = { -27.2e-7, -4.2e-7, -0.27e-7, -0.16e-7, -1.39e-7 };
		static double b[cNY] = { 6.9e-7, 47.7e-7, 3.93e-7, 1.69e-7, 2.7e-8};
		static double c[cNY] = {-0.19, -0.1, -0.14,-0.12 , -0.39 };
		static double d[cNY] = {0.07,0.999, 0.599, 1.7, 0.077};
		Ref_Histo_SC_y_min = a;
		Ref_Histo_SC_y_max = b;
		Ref_Histo_NSC_y_min = c;
		Ref_Histo_NSC_y_max = d;
	}
	if(imodel==kAMPT) {
		static double a[cNY] = { -16.1e-7, -4.2e-7, -0.29e-7, -0.16e-7, -0.87e-7 };
		static double b[cNY] = { 9.9e-7, 32.7e-7, 2.35e-7, 0.76e-7, 4.7e-8};
		static double c[cNY] = {-0.33, -0.1, -0.11,-0.11 , -0.39 };
		static double d[cNY] = {0.27,1.45, 1.11, 2.75, 0.47};
		Ref_Histo_SC_y_min = a;
		Ref_Histo_SC_y_max = b;
		Ref_Histo_NSC_y_min = c;
		Ref_Histo_NSC_y_max = d;
	}


	TCanvas *c100 = new TCanvas("c100", "", canvas_width, canvas_height);
	TPad *pads[cNX][cNY];
	for(int ix=0; ix<cNX; ix++){
		for(int iy=0; iy<cNY; iy++){

			pads[ix][iy] = new TPad(Form("p%d%d",ix, iy), "",
					Xm + ix*W,  ypos[iy],
					Xm + (ix+1)*W, ypos[iy+1],
					0, 0, 0 );
			if(ix==0) pads[ix][iy]->SetRightMargin(0);
			if(ix==0) pads[ix][iy]->SetLeftMargin(0.15);
			if(ix==1) pads[ix][iy]->SetLeftMargin(0);
			if(ix==1) pads[ix][iy]->SetRightMargin(0.15);
			pads[ix][iy]->SetBottomMargin(0);
			pads[ix][iy]->SetTopMargin(0);
			pads[ix][iy]->Draw();
		}
	}

	TLatex *latex2 = new TLatex();
	latex2->SetTextSize(0.025);
	latex2->SetTextFont(42);
	c100->cd();
	latex2->DrawLatexNDC( 0.10, 0.046, "0");
	latex2->DrawLatexNDC( 0.173, 0.046, "10");
	latex2->DrawLatexNDC( 0.249, 0.046, "20");
	latex2->DrawLatexNDC( 0.326, 0.046, "30");
	latex2->DrawLatexNDC( 0.404, 0.046, "40");
	latex2->DrawLatexNDC( 0.48, 0.046, "50");

	latex2->DrawLatexNDC( 0.565, 0.046, "10");
	latex2->DrawLatexNDC( 0.644, 0.046, "20");
	latex2->DrawLatexNDC( 0.720, 0.046, "30");
	latex2->DrawLatexNDC( 0.797, 0.046, "40");
	latex2->DrawLatexNDC( 0.873, 0.046, "50");

	latex2->DrawLatexNDC( 0.30, 0.020, "#scale[1.2]{Centrality percentile}");
	latex2->DrawLatexNDC( 0.70, 0.020, "#scale[1.2]{Centrality percentile}");

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
		hSCReference[i]->GetYaxis()->SetTitleOffset(0.52);
		hSCReference[i]->GetYaxis()->SetTitleSize(0.15);
		hSCReference[i]->GetYaxis()->SetLabelSize(0.125);
		hSCReference[i]->GetYaxis()->CenterTitle();
		hSCReference[i]->GetXaxis()->SetLabelSize(0.0);
		hSCReference[i]->GetYaxis()->SetNdivisions(505);


		hNSCReference[i]->SetStats(0);
		hNSCReference[i]->GetYaxis()->SetTitle(Form("NSC(%d,%d) ", m, n) );
		hNSCReference[i]->GetYaxis()->SetTitleOffset(0.56);
		hNSCReference[i]->GetYaxis()->SetTitleSize(0.15);
		hNSCReference[i]->GetYaxis()->SetLabelSize(0.125);
		hNSCReference[i]->GetYaxis()->CenterTitle();
		hNSCReference[i]->GetXaxis()->SetLabelSize(0.0);
		hNSCReference[i]->GetYaxis()->SetNdivisions(505);

		if(i==4){	
			hNSCReference[i]->GetXaxis()->SetTitle("Centrality percentile");
			hNSCReference[i]->GetXaxis()->SetTitleSize(0.077);
			hNSCReference[i]->GetXaxis()->SetTitleOffset(0.81);

		}		

	}	

	for(int ix=0; ix<cNX; ix++){
		for(int iy=0; iy<cNY; iy++){
			pads[ix][4-iy]->cd();

			if(ix==0){ // left pannel SC
				hSCReference[iy]->Draw();

				gr_SC_syst[iy]->Draw("same2");
				gr_SC[iy]->Draw("same p,Z");

				if(imodel==kEKRT) {
					gr_SC_EKRT[0][iy]->Draw("same c");
					gr_SC_EKRT[1][iy]->Draw("same c");
					for(int ipar=0; ipar<kNParm; ipar++){
						if(Draw_old_EKRT  && iy<2) gr_SC_Hydro[ipar][iy]->Draw("same c");
					}
				} 
				if(imodel==kVISH) {
					for(int iset=0; iset<kNVISH; iset++){
						for(int ieta=0; ieta<kVNvisco; ieta++){
							gr_SC_VISH[iy][iset][ieta]->Draw("same pl,Z");
							if(iy==0) legModel->AddEntry( gr_SC_VISH[iy][iset][ieta], Form("%s", strVISHconf[iset][ieta].Data() ), "pl");
						}
					}

				}
				if(imodel==kAMPT) {
					for(int iset=0; iset<kNAMPT; iset++){
						gr_SC_AMPT[iset][iy]->SetLineStyle(2);
						gr_SC_AMPT[iset][iy]->Draw("same pl,Z");
						if(iy==0) legModel->AddEntry( gr_SC_AMPT[iset][iy], Form("%s", strAMPTName[iset].Data()), "pl");
					}
				}
			}

			if(ix==1){ // right pannel NSC
				hNSCReference[iy]->Draw("Y+");

				gr_SC_norm_syst[iy]->Draw("same 2");
				gr_SC_norm[iy]->Draw("same p,Z");

				if(imodel==kEKRT) {
					gr_NSC_EKRT[0][iy]->Draw("same c");
					gr_NSC_EKRT[1][iy]->Draw("same c");
					for(int ipar=0; ipar<kNParm; ipar++){
						if(Draw_old_EKRT  && iy<2) gr_SC_norm_Hydro[ipar][iy]->Draw("same c");
					}
				} 
				if(imodel==kVISH) {
					for(int iset=0; iset<kNVISH; iset++){
						for(int ieta=0; ieta<kVNvisco; ieta++){
							gr_SC_norm_VISH[iy][iset][ieta]->Draw("same pl,Z");
						}
					}

				}
				if(imodel==kAMPT) {
					for(int iset=0; iset<kNAMPT; iset++){
						gr_SC_norm_AMPT[iset][iy]->SetLineStyle(2);
						gr_SC_norm_AMPT[iset][iy]->Draw("same pl,Z");
					}
				}
			}

			if(ix==0&&iy==0) {
				legmult->Draw();
			}
			if(ix==0&&iy==0) {
				legData->Draw();
			}
			if(ix==0&&iy==1) {
				legModel->Draw();
			}
		}
	}
	TString strPadName[10] = {"(a)","(A)","(b)","(B)","(c)","(C)","(d)","(D)","(e)","(E)"};
	TLatex latexPad;
	latexPad.SetTextSize(0.10);
	for(int ix=0; ix<cNX; ix++){
		for(int iy=0; iy<cNY; iy++){
			pads[ix][4-iy]->cd();
			if(ix==0) latexPad.DrawLatexNDC( 0.93, 0.91 , strPadName[ix+2*iy]);
			if(ix==1) latexPad.DrawLatexNDC( 0.78, 0.91 , strPadName[ix+2*iy]);
		}
	}
	c100->SaveAs(Form("figs/Fig%d_ModelComparison_%s.eps",imodel+4,strModel[imodel].Data()));
}





