// chisqared test results as a function of oberables, fist index 0 SC, 1 NSC
enum { kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};
enum { kEKRT, kVISH, kAMPT, kNmodel};
enum {kAMPT13f3a, kAMPT13f3b, kAMPT13f3c, kNAMPT};
enum {kV_AMPT, kV_KLN, kV_Glb, kNVISH};
enum {kV_smallviso, kV_largevisco, kVNvisco};
int gCMarker[6] = {kFullCircle, kFullSquare, kFullDiamond, kFullStar, 34, 22};
int gOMarker[6] = {kOpenCircle, kOpenSquare, kOpenDiamond, kOpenStar, 28, 26};

int gColor[6] = {kBlack, kBlue, kRed, kGreen+2, kOrange-1,kYellow-6};
int gFillColor[3] = { kGreen-3, kCyan+2, kYellow-6};

TGraphErrors *gr_VISH_chisq[2][kNVISH][kVNvisco];
TGraphErrors *gr_EKRT_chisq[2][2];
TGraphErrors *gr_AMPT_chisq[2][kNAMPT];

// Single vn
TGraphErrors *gr_VISH_vn_chisq[kNVISH][kVNvisco];
TGraphErrors *gr_EKRT_vn_chisq[2];
TGraphErrors *gr_AMPT_vn_chisq[kNAMPT];

TString strVISHconf[kNVISH][kVNvisco] = {
	"AMPT, #eta/s=0.08",
	"AMPT, #eta/s=0.16",
	"MC-KLN, #eta/s=0.08",
	"MC-KLN, #eta/s=0.2",
	"MC-Glauber, #eta/s=0.08",
	"MC-Glauber, #eta/s=0.2"	
};

int sc_number[5][2] = { {3,2},
{4,2},
{5,2},
{5,3},
{4,3}};

TString strSCType[kNSC] = {"(3,2)","(4,2)","(5,2)","(5,3)","(4,3)"}; 
TString strVNType[3] = {"#it{v}_{2}","#it{v}_{3}","#it{v}_{4}"}; 

TString strAMPTName[kNAMPT] = { 
	"string melting w/o hadronic rescattering",
	"default",
	"string melting"
};

TString strModel[3] = { "EKRT","VISH","AMPT"};

void LoadVnChiq() {
	TFile *finvn = TFile::Open("chisquared_vn_results.root");
	for(int iset=0;iset<2;iset++) {
		gr_EKRT_vn_chisq[iset] = (TGraphErrors*)finvn->Get(Form("gr_EKRT_vn_parm%02d_chisq",iset));
	}

	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<kVNvisco; ieta++){
			gr_VISH_vn_chisq[iset][ieta] = (TGraphErrors*)finvn->Get(Form("gr_VISH_vn_%02d%02d_chisq",iset,ieta));
		}
	}
	for(int iset=0; iset<kNAMPT; iset++){
		gr_AMPT_vn_chisq[iset] = (TGraphErrors*)finvn->Get(Form("gr_AMPT_vn_%2d_chisq",iset));
	}

}

void LoadSCChiq(){
// open the resuts 
	TFile *fin = TFile::Open("chisquared_results.root");

	for(int iset=0;iset<2;iset++) {
		gr_EKRT_chisq[0][iset] = (TGraphErrors*)fin->Get(Form("gr_EKRT_SC_parm%02d",iset));
		gr_EKRT_chisq[1][iset] = (TGraphErrors*)fin->Get(Form("gr_EKRT_NSC_parm%02d",iset));
	}

	for(int iset=0; iset<kNVISH; iset++){
		for(int ieta=0; ieta<kVNvisco; ieta++){
			gr_VISH_chisq[0][iset][ieta] = (TGraphErrors*)fin->Get(Form("gr_VISH_SC_%02d%02d_chisq",iset,ieta));
			gr_VISH_chisq[1][iset][ieta] = (TGraphErrors*)fin->Get(Form("gr_VISH_NSC_%02d%02d_chisq",iset,ieta));
		}
	}
	for(int iset=0; iset<kNAMPT; iset++){
		gr_AMPT_chisq[0][iset] = (TGraphErrors*)fin->Get(Form("gr_AMPT_SC_%2d_chisq",iset));
		gr_AMPT_chisq[1][iset] = (TGraphErrors*)fin->Get(Form("gr_AMPT_NSC_%2d_chisq",iset));
	}
}

void draw_chiqbest(){
// open the resuts 
	LoadSCChiq();
	LoadVnChiq();

	double sc=1.0, sdx=400, sdy=400;
	double ly=0.9e-1, hy=1.1e4;
	int logy=1;

	int iCan = 1;
	TLatex latexPad;
	latexPad.SetTextSize(0.035);

	//Best fit
	mc(iCan++,sc,sdx); //===================================
    // scale sc and sdx could be omitted
	mpad->SetLogy(logy);
	mpad->SetLeftMargin(0.2);
	gStyle->SetOptStat(0); gStyle->SetOptTitle(0);

	hfr0 = new TH2F("hfr0", " ", kNSC, -0.5, kNSC-0.5, 10, ly, hy);
	hset( *hfr0, "", "#chi^{2}",0.9,1.4, 0.05,0.07, 0.01,0.001, 0.09,0.06, 510,510);
	SetGraphBinLabel(hfr0, strSCType);
	hfr0->Draw();

	leg = new TLegend(0.25,0.75,0.5,0.93,NULL,"brNDC");
	leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.035);
	//leg->AddEntry((TObject*)NULL,"EKRT+Viscous Hydrodynamics","");
	for(int iset=0;iset<2;iset++) {
		gr_EKRT_chisq[0][iset]->SetMarkerStyle(gCMarker[iset]);
		gr_EKRT_chisq[0][iset]->SetMarkerColor(gColor[iset]);
		gr_EKRT_chisq[0][iset]->SetLineColor(gColor[iset]);
		gr_EKRT_chisq[0][iset]->Draw("lp");
		gr_EKRT_chisq[1][iset]->SetMarkerStyle(gOMarker[iset]);
		gr_EKRT_chisq[1][iset]->SetMarkerColor(gColor[iset]);
		gr_EKRT_chisq[1][iset]->SetLineColor(gColor[iset]);
		gr_EKRT_chisq[1][iset]->SetLineStyle(2);
		gr_EKRT_chisq[1][iset]->Draw("lp");
		leg->AddEntry(gr_EKRT_chisq[0][iset],Form("EKRT+Viscous Hydro, %s",gr_EKRT_chisq[0][iset]->GetTitle()),"lp");
	}
	int count = 0;
    // AMPT eta/s =0.08
	int iset=0,ieta=0;
	gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gCMarker[2]);
	gr_VISH_chisq[0][iset][ieta]->SetMarkerColor(gColor[2]);
	gr_VISH_chisq[0][iset][ieta]->SetLineColor(gColor[2]);
	gr_VISH_chisq[0][iset][ieta]->Draw("lp");
	leg->AddEntry(gr_VISH_chisq[0][iset][ieta],Form("VISH2+1, %s",gr_VISH_chisq[0][iset][ieta]->GetTitle()),"lp");

	gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gOMarker[2]);
	gr_VISH_chisq[1][iset][ieta]->SetMarkerColor(gColor[2]);
	gr_VISH_chisq[1][iset][ieta]->SetLineColor(gColor[2]);
	gr_VISH_chisq[1][iset][ieta]->SetLineStyle(2);
	gr_VISH_chisq[1][iset][ieta]->Draw("lp");

	// ieta=1;
	// gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gCMarker[3]);
	// gr_VISH_chisq[0][iset][ieta]->SetMarkerColor(gColor[3]);
	// gr_VISH_chisq[0][iset][ieta]->SetLineColor(gColor[3]);
	// gr_VISH_chisq[0][iset][ieta]->Draw("lp");
	// leg->AddEntry(gr_VISH_chisq[0][iset][ieta],Form("VISH2+1, %s",gr_VISH_chisq[0][iset][ieta]->GetTitle()),"lp");

	// gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gOMarker[3]);
	// gr_VISH_chisq[1][iset][ieta]->SetMarkerColor(gColor[3]);
	// gr_VISH_chisq[1][iset][ieta]->SetLineColor(gColor[3]);
	// gr_VISH_chisq[1][iset][ieta]->SetLineStyle(2);
	// gr_VISH_chisq[1][iset][ieta]->Draw("lp");
	
	// gr_AMPT_chisq[0][1]->SetMarkerStyle(gCMarker[3]);
	// gr_AMPT_chisq[0][1]->SetMarkerColor(gColor[3]);
	// gr_AMPT_chisq[0][1]->SetLineColor(gColor[3]);
	// gr_AMPT_chisq[0][1]->Draw("lp");
	// leg->AddEntry(gr_AMPT_chisq[0][1],Form("AMPT, %s",gr_AMPT_chisq[0][1]->GetTitle()),"lp");
	// gr_AMPT_chisq[1][1]->SetMarkerStyle(gOMarker[3]);
	// gr_AMPT_chisq[1][1]->SetMarkerColor(gColor[3]);
	// gr_AMPT_chisq[1][1]->SetLineColor(gColor[3]);
	// gr_AMPT_chisq[1][1]->SetLineStyle(2);
	// gr_AMPT_chisq[1][1]->Draw("lp");

	// gr_AMPT_chisq[0][2]->SetMarkerStyle(gCMarker[4]);
	// gr_AMPT_chisq[0][2]->SetMarkerColor(gColor[4]);
	// gr_AMPT_chisq[0][2]->SetLineColor(gColor[4]);
	// gr_AMPT_chisq[0][2]->Draw("lp");
	// leg->AddEntry(gr_AMPT_chisq[0][2],Form("AMPT, %s",gr_AMPT_chisq[0][2]->GetTitle()),"lp");
	// gr_AMPT_chisq[1][2]->SetMarkerStyle(gOMarker[4]);
	// gr_AMPT_chisq[1][2]->SetMarkerColor(gColor[4]);
	// gr_AMPT_chisq[1][2]->SetLineColor(gColor[4]);
	// gr_AMPT_chisq[1][2]->SetLineStyle(2);
	// gr_AMPT_chisq[1][2]->Draw("lp");

	leg->Draw();
	latexPad.DrawLatexNDC( 0.52, 0.66 , "SC(m,n) closed markers");
	latexPad.DrawLatexNDC( 0.52, 0.60 , "NSC(m,n) open markers");
	latexPad.DrawLatexNDC( 0.45, 0.20 , "N = 4, Centrality 10 - 50\%");
	TLatex latexPadID;
	latexPadID.SetTextSize(0.040);
	latexPadID.DrawLatexNDC(0.88, 0.87, "(a)");

	gPad->GetCanvas()->Update();
	gPad->GetCanvas()->SaveAs("figs/chisq_SC_bestfits.eps");
 


			//Best fit vn
	mc(iCan++,sc,sdx); //===================================
    // scale sc and sdx could be omitted
	mpad->SetLogy(logy);
	mpad->SetLeftMargin(0.2);
	gStyle->SetOptStat(0); gStyle->SetOptTitle(0);

	hfr0 = new TH2F("hfr0", " ", 3, -0.5, 3-0.5, 10, ly, hy);
	hset( *hfr0, "", "#chi^{2}",0.9,1.4, 0.05,0.07, 0.01,0.001, 0.09,0.06, 510,510);
	SetGraphBinLabel(hfr0, strVNType);
	hfr0->Draw();

	leg = new TLegend(0.25,0.75,0.5,0.93,NULL,"brNDC");
	leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.035);
	//leg->AddEntry((TObject*)NULL,"EKRT+Viscous Hydrodynamics","");
	for(int iset=0;iset<2;iset++) {
		gr_EKRT_vn_chisq[iset]->SetMarkerStyle(gCMarker[iset]);
		gr_EKRT_vn_chisq[iset]->SetMarkerColor(gColor[iset]);
		gr_EKRT_vn_chisq[iset]->SetLineColor(gColor[iset]);
		gr_EKRT_vn_chisq[iset]->Draw("lp");
		leg->AddEntry(gr_EKRT_vn_chisq[iset],Form("EKRT+Viscous Hydro, %s",gr_EKRT_vn_chisq[iset]->GetTitle()),"lp");
	}
	int count = 0;
    // AMPT eta/s =0.08
	int iset=0,ieta=0;
	gr_VISH_vn_chisq[iset][ieta]->SetMarkerStyle(gCMarker[2]);
	gr_VISH_vn_chisq[iset][ieta]->SetMarkerColor(gColor[2]);
	gr_VISH_vn_chisq[iset][ieta]->SetLineColor(gColor[2]);
	gr_VISH_vn_chisq[iset][ieta]->Draw("lp");
	leg->AddEntry(gr_VISH_vn_chisq[iset][ieta],Form("VISH2+1, %s",gr_VISH_vn_chisq[iset][ieta]->GetTitle()),"lp");

	// ieta=1;
	// gr_VISH_vn_chisq[iset][ieta]->SetMarkerStyle(gCMarker[3]);
	// gr_VISH_vn_chisq[iset][ieta]->SetMarkerColor(gColor[3]);
	// gr_VISH_vn_chisq[iset][ieta]->SetLineColor(gColor[3]);
	// gr_VISH_vn_chisq[iset][ieta]->Draw("lp");
	// leg->AddEntry(gr_VISH_vn_chisq[iset][ieta],Form("VISH2+1, %s",gr_VISH_vn_chisq[iset][ieta]->GetTitle()),"lp");
	
	// gr_AMPT_vn_chisq[1]->SetMarkerStyle(gCMarker[3]);
	// gr_AMPT_vn_chisq[1]->SetMarkerColor(gColor[3]);
	// gr_AMPT_vn_chisq[1]->SetLineColor(gColor[3]);
	// gr_AMPT_vn_chisq[1]->Draw("lp");
	// leg->AddEntry(gr_AMPT_vn_chisq[1],Form("AMPT, %s",gr_AMPT_vn_chisq[1]->GetTitle()),"lp");
	// gr_AMPT_vn_chisq[2]->SetMarkerStyle(gCMarker[4]);
	// gr_AMPT_vn_chisq[2]->SetMarkerColor(gColor[4]);
	// gr_AMPT_vn_chisq[2]->SetLineColor(gColor[4]);
	// gr_AMPT_vn_chisq[2]->Draw("lp");
	// leg->AddEntry(gr_AMPT_vn_chisq[2],Form("AMPT, %s",gr_AMPT_vn_chisq[2]->GetTitle()),"lp");
	
	leg->Draw();
	latexPad.DrawLatexNDC( 0.45, 0.20 , "N = 4, Centrality 10 - 50\%");
	latexPadID.DrawLatexNDC(0.88, 0.87, "(b)");

	gPad->GetCanvas()->Update();
	gPad->GetCanvas()->SaveAs("figs/chisq_vn_bestfits.eps");
}



void SetGraphBinLabel(TH2F *hid, TString *strArr) {
	for(int i=1;i<= hid->GetNbinsX();i++) {
		cout << strArr[i-1] << endl;
		hid->GetXaxis()->SetBinLabel(i, strArr[i-1]);
	}
}
