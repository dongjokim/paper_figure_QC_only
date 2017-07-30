// chisqared test results as a function of oberables, fist index 0 SC, 1 NSC
enum { kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};
enum { kEKRT, kVISH, kAMPT, kNmodel};
enum {kAMPT13f3a, kAMPT13f3b, kAMPT13f3c, kNAMPT};
enum {kV_AMPT, kV_KLN, kV_Glb, kNVISH};
enum {kV_smallviso, kV_largevisco, kVNvisco};
int gCMarker[5] = {kFullCircle, kFullSquare, kFullDiamond, 34, 31};
int gOMarker[5] = {kOpenCircle, kOpenSquare, kOpenDiamond, 30, 27};

int gColor[5] = {kBlue, kRed, kGreen+2, kOrange-1, kRed+1};
int gFillColor[3] = { kGreen-3, kCyan+2, kYellow-6};

TGraphErrors *gr_VISH_chisq[2][kNVISH][kVNvisco];
TGraphErrors *gr_EKRT_chisq[2][2];
TGraphErrors *gr_AMPT_chisq[2][kNAMPT];

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

TString strAMPTName[kNAMPT] ={
	"string melting w/o hadronic rescattering",
	"default",
	"string melting"
}

TString strModel[3] = { "EKRT","VISH","AMPT"};

void draw_chiq(){
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

	double sc=1.0, sdx=400, sdy=450;
	double ly=1e0, hy=6e5;
	mc(1,sc,sdx); //===================================
    // scale sc and sdx could be omitted

    mpad->SetLogy(1);
    mpad->SetLeftMargin(0.2);
    gStyle->SetOptStat(0); gStyle->SetOptTitle(0);

    hfr0 = new TH2F("hfr0", " ", 12, -1, kNSC+1, 10, ly, hy);
    hset( *hfr0, "oberables", "#chi^{2}",0.9,1.4, 0.06,0.05, 0.01,0.001, 0.04,0.05, 510,510);

   
    hfr0->Draw();
    
    leg = new TLegend(0.5,0.48,0.8,0.95,NULL,"brNDC");
    leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.04);
     
    for(int iset=0;iset<2;iset++) {
    	gr_EKRT_chisq[0][iset]->SetMarkerStyle(gCMarker[iset]);
		gr_EKRT_chisq[0][iset]->Draw("lp");
		gr_EKRT_chisq[1][iset]->SetMarkerStyle(gOMarker[iset]);
		gr_EKRT_chisq[1][iset]->Draw("lp");
		leg->AddEntry(gr_EKRT_chisq[0][iset],gr_EKRT_chisq[0][iset]->GetTitle(),"lp");
		leg->AddEntry(gr_EKRT_chisq[1][iset],gr_EKRT_chisq[1][iset]->GetTitle(),"lp");
	}

	for(int iset=0; iset<kNVISH; iset++){
        for(int ieta=0; ieta<kVNvisco; ieta++){
        	gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gCMarker[2+iset+ieta]);
			gr_VISH_chisq[0][iset][ieta]->Draw("lp");
			gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gOMarker[2+iset+ieta]);
			gr_VISH_chisq[1][iset][ieta]->Draw("lp");
			leg->AddEntry(gr_VISH_chisq[0][iset][ieta],gr_VISH_chisq[0][iset][ieta]->GetTitle(),"lp");
			leg->AddEntry(gr_VISH_chisq[1][iset][ieta],gr_VISH_chisq[1][iset][ieta]->GetTitle(),"lp");
		}
	}
	for(int iset=0; iset<kNAMPT; iset++){
		//gr_AMPT_chisq[0][iset]->Draw("p");
		//gr_AMPT_chisq[1][iset]->Draw("p");
	}
	leg->Draw();
}