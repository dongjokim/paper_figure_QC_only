// chisqared test results as a function of oberables, fist index 0 SC, 1 NSC
#include "JmxnTPad.h" // for multi canvas

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

TString strAMPTName[kNAMPT] ={
	"string melting w/o hadronic rescattering",
	"default",
	"string melting"
};

TString strModel[3] = { "EKRT","VISH","AMPT"};

void draw_chiq_multi(){
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

	//TGaxis::SetExponentOffset(0.04, -0.1150, "y");

	// Draw in multicanvas for final paper // 
	const int nx = 2;
	const int ny = 2;
	double lrX[nx];
	double urX[nx];
	double lrY[nx][ny];
	double urY[nx][ny];
	for(int ix=0; ix <nx; ix++){
		lrX[ix] = -0.5;
		urX[ix] = kNSC-0.5;
		for(int iy=0; iy<ny; iy++){	
			lrY[ix][iy] = 0.9e-1; // 0.22
			urY[ix][iy] = 1.1e5; // 0.2
		}
	}
	JmxnTPad *pad1 = new JmxnTPad( nx, ny, lrX, urX, lrY[0], urY[0]);
	pad1->SetCanvas(1.2, 800, 10, 10);
	pad1->SetOptionsLabelAxisX(0.008,0.58, 42);
	pad1->SetOptionsLabelAxisY(0.008,0.32, 42);
	pad1->SetSizeOfLabelPadsAxisY(0.05,0.017);
	pad1->SetTitleX("oberables", 1,0.04, 42, 1.4);
	pad1->SetTitleY("#chi^{2}",1,0.04,42,1.2);
	TLegend *leg[nx*ny];
	TLegend *leg_ampt;
	TLatex latex;
	
	leg_ampt = new TLegend( 0.06, 0.13, 0.4, 0.36, "AMPT", "brNDC" );
	leg_ampt->SetFillStyle(0);
	leg_ampt->SetBorderSize(0);
	leg_ampt->SetTextSize(0.048);

	leg_ekrt = new TLegend( 0.15, 0.13, 0.8, 0.37, "EKRT+Viscous Hydrodynamics", "brNDC");
	leg_ekrt->SetFillStyle(0);
	leg_ekrt->SetBorderSize(0);
	leg_ekrt->SetTextSize(0.052);

	leg_vish = new TLegend( 0.06, 0.13, 0.4, 0.36, "VISH2+1", "brNDC" );
	leg_vish->SetFillStyle(0);
	leg_vish->SetBorderSize(0);
	leg_vish->SetTextSize(0.048);
	
	pad1->SetYCaption(8.8 / 10. );
	
	pad1->Draw();	


	for(int ix=0; ix<nx; ix++){
		for(int iy=0; iy<ny; iy++){
			TPad *p = pad1->GetPad(ix, iy);
			p->cd();
			p->SetGridx(0);
			p->SetGridy(1);
			p->SetLogy(1);
			p->ls();

			// EKRT
			if(ix==0&&iy==0){
				for(int iset=0;iset<2;iset++) {
					gr_EKRT_chisq[0][iset]->SetMarkerStyle(gCMarker[iset]);
					gr_EKRT_chisq[0][iset]->Draw("lp");
					gr_EKRT_chisq[1][iset]->SetMarkerStyle(gOMarker[iset]);
					gr_EKRT_chisq[1][iset]->Draw("lp");
					leg_ekrt->AddEntry(gr_EKRT_chisq[0][iset],gr_EKRT_chisq[0][iset]->GetTitle(),"lp");
				}
				leg_ekrt->Draw();
			}
			// VISH2+1
			if(ix==1&&iy==0){
				for(int iset=0; iset<kNVISH; iset++){
					for(int ieta=0; ieta<kVNvisco; ieta++){
						gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gCMarker[iset]);
						gr_VISH_chisq[0][iset][ieta]->SetMarkerColor(gColor[iset]);
						gr_VISH_chisq[0][iset][ieta]->SetLineColor(gColor[iset]);
						gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gCMarker[iset]);
						gr_VISH_chisq[1][iset][ieta]->SetMarkerColor(gColor[iset]);
						gr_VISH_chisq[1][iset][ieta]->SetLineColor(gColor[iset]);
						if(ieta==1) {
							gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gOMarker[iset]);
							gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gOMarker[iset]);
							gr_VISH_chisq[0][iset][ieta]->SetLineStyle(2); 
							gr_VISH_chisq[1][iset][ieta]->SetLineStyle(2);
							leg_vish->AddEntry(gr_VISH_chisq[0][iset][ieta],gr_VISH_chisq[0][iset][ieta]->GetTitle(),"lp");
						} else {
							leg_vish->AddEntry(gr_VISH_chisq[0][iset][ieta],gr_VISH_chisq[0][iset][ieta]->GetTitle(),"lp");
						}
						gr_VISH_chisq[0][iset][ieta]->Draw("lp");
						gr_VISH_chisq[1][iset][ieta]->Draw("lp");
					}
				}
				leg_vish->Draw();
			}
			// AMPT
			if(ix==0&&iy==1){
				TH1F *hr= (TH1F*)p->GetPrimitive("hDummyHist9997_9998");
				p->SetBottomMargin(0);
				hr->SetBins(kNSC, -0.5, kNSC-0.5);
				SetGraphBinLabel(hr,strSCType);
				for(int iset=0; iset<kNAMPT; iset++){
					gr_AMPT_chisq[0][iset]->SetMarkerStyle(gCMarker[iset]);
					gr_AMPT_chisq[0][iset]->SetMarkerColor(gColor[iset]);
					gr_AMPT_chisq[0][iset]->SetLineColor(gColor[iset]);
					gr_AMPT_chisq[0][iset]->Draw("lp");
					gr_AMPT_chisq[1][iset]->SetMarkerStyle(gOMarker[iset]);
					gr_AMPT_chisq[1][iset]->SetMarkerColor(gColor[iset]);
					gr_AMPT_chisq[1][iset]->SetLineColor(gColor[iset]);
					gr_AMPT_chisq[1][iset]->SetLineStyle(2);
					gr_AMPT_chisq[1][iset]->Draw("lp");
					leg_ampt->AddEntry(gr_AMPT_chisq[0][iset],gr_AMPT_chisq[0][iset]->GetTitle(),"lp");
				}
				leg_ampt->Draw();
			}	
			// Best fit
			if(ix==1&&iy==1){
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
					//leg->AddEntry(gr_EKRT_chisq[0][iset],Form("%s",gr_EKRT_chisq[0][iset]->GetTitle()),"lp");
				}

				// AMPT eta/s =0.08
				int iset=0,ieta=0;
				gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gCMarker[2]);
				gr_VISH_chisq[0][iset][ieta]->SetMarkerColor(gColor[2]);
				gr_VISH_chisq[0][iset][ieta]->SetLineColor(gColor[2]);
				gr_VISH_chisq[0][iset][ieta]->Draw("lp");
				//leg->AddEntry(gr_VISH_chisq[0][iset][ieta],Form("VISH2+1, %s",gr_VISH_chisq[0][iset][ieta]->GetTitle()),"lp");

				gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gOMarker[2]);
				gr_VISH_chisq[1][iset][ieta]->SetMarkerColor(gColor[2]);
				gr_VISH_chisq[1][iset][ieta]->SetLineColor(gColor[2]);
				gr_VISH_chisq[1][iset][ieta]->SetLineStyle(2);
				gr_VISH_chisq[1][iset][ieta]->Draw("lp");

				gr_AMPT_chisq[0][1]->SetMarkerStyle(gCMarker[3]);
				gr_AMPT_chisq[0][1]->SetMarkerColor(gColor[3]);
				gr_AMPT_chisq[0][1]->SetLineColor(gColor[3]);
				gr_AMPT_chisq[0][1]->Draw("lp");
				//leg->AddEntry(gr_AMPT_chisq[0][1],Form("AMPT, %s",gr_AMPT_chisq[0][1]->GetTitle()),"lp");
				gr_AMPT_chisq[1][1]->SetMarkerStyle(gOMarker[3]);
				gr_AMPT_chisq[1][1]->SetMarkerColor(gColor[3]);
				gr_AMPT_chisq[1][1]->SetLineColor(gColor[3]);
				gr_AMPT_chisq[1][1]->SetLineStyle(2);
				gr_AMPT_chisq[1][1]->Draw("lp");
				//leg->Draw();
			}

		} 
	}	
}

void SetGraphBinLabel(TH1F *hid, TString *strArr) {
	for(int i=1;i<= hid->GetNbinsX();i++) {
		cout << strArr[i-1] << endl;
		hid->GetXaxis()->SetBinLabel(i, strArr[i-1]);
	}
}
