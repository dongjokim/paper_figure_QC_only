#include "JmxnTPad.h" // for multi canvas

	enum{ k0250, k0350, k0450, k0550, k0750, k0850, k0950, k1050, k1250, k1550, kNpt};
	enum{ kSC32, kSC42, kNSC};
	enum{ k0005, k0510, k1020, k2030, k3040, k4050, k5060, kNCent};
	enum{ kSP, kQC, kNM};


	TGraphErrors *gr_SC[kNM][kNpt][kNSC];
	TGraphErrors *gr_SC_xpt[kNM][kNCent][kNSC];
	TGraphErrors *gr_SC_xpt_err[kNM][kNCent][kNSC];
	TGraphErrors *gr_SC_xpt_ratio[kNM][kNCent][kNSC];


	TFile *fin_ampt[3][kNpt];
	TGraphErrors *gr_SC_AMPT[3][kNM][kNpt][kNSC];
	TGraphErrors *gr_SC_xpt_AMPT[3][kNM][kNCent][kNSC];

	bool Draw_AMPT[3] = {1, 1, 1}; // 13f3a, b, c
	const double CentBins[kNCent+1] = {0, 5, 10, 20, 30, 40, 50, 60};
	const double ptbins[kNpt] = {0.2, 0.3, 0.4, 0.5, 0.7, 0.8, 0.9, 1.0, 1.2, 1.5 };

	int gAMPTColor[3] = { kGreen+2, kRed, kBlue };
	int gAMPTMarker[3] = { kOpenDiamond, kOpenCircle, kOpenSquare};
	TString strAMPT[3] = {
		"AMPT, string melting w/o hadronic rescattering",
		"AMPT, default",
		"AMPT, string melting"
	}

	
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
	}
	TString strGraphName[kNM][kNSC]= {
		"gr_SC_ratio_00", "gr_SC_ratio_01",
		"gr_SC_norm_with_QC_3223", "gr_SC_norm_with_QC_4224"
	};

void Draw_pT_vs_SC(){
	
	LoadAMPTResults();



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



	//load data part//
	cout << "start load data" << endl;
	for(int ipt=0; ipt<kNpt; ipt++){
		fin[ipt] = new TFile( strFilename[ipt].Data(), "read" );
		fin[ipt]->Print();
		//load file here

		for(int im=0; im<kNM; im++){
			for(int isc=0; isc<kNSC; isc++){
				gr_SC[im][ipt][isc] = (TGraphErrors*)fin[ipt]->Get(strGraphName[im][isc].Data());
//				gr_SC[im][ipt][isc]->Print();
			}
		}
	}
	cout << "load datafiles and grpha done.." << endl;
	//load done	

	//init new graph
	for(int im=0; im<kNM; im++){
		for(int icent=0; icent<kNCent; icent++){
			for(int isc=0; isc<kNSC; isc++){
				gr_SC_xpt[im][icent][isc] = new TGraphErrors();
				gr_SC_xpt[im][icent][isc]->SetMarkerStyle( 20 );
				gr_SC_xpt[im][icent][isc]->SetMarkerSize(1.1);
				gr_SC_xpt[im][icent][isc]->SetMarkerColor( kBlack );
				gr_SC_xpt[im][icent][isc]->SetLineColor( kBlack );
				gr_SC_xpt[im][icent][isc]->SetFillColor( kGray );
			}
		}
	};
	//int done

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
							}
					}
			}
	}
	// Add systematics for data
	for(int isc=0; isc<kNSC; isc++){
		for(int icent=0; icent<kNCent; icent++){
			for(im=0; im<kNM; im++){
				gr_SC_xpt_err[im][icent][isc] = (TGraphErrors*)gr_SC_xpt[im][icent][isc]->Clone();
				gr_SC_xpt_err[im][icent][isc]->SetFillColor( kGray );
			}
		}
	}
	for(int isc =0; isc<kNSC; isc++){
			for(int ipt=0; ipt<kNpt; ipt++){
					for(int im=0; im<kNM; im++){
							for(int icent=0; icent<kNCent; icent++){
								double systerr = gr_SC_xpt_err[im][icent][isc]->GetY()[ipt] * systematics[im][ipt][isc];
								gr_SC_xpt_err[im][icent][isc]->SetPointError( ipt, 0.05, systerr );
							}
					}
			}
	}
	// 


	// Calcultae ratio
	for(int im=0; im<kNM; im++){
		for(int ic=0; ic<kNCent; ic++){
			for(int isc=0; isc<kNSC; isc++){
				gr_SC_xpt_ratio[im][ic][isc] = CalculateRatio( gr_SC_xpt[im][ic][isc] , gr_SC_xpt[kQC][ic][isc], 0 );
				gr_SC_xpt_ratio[im][ic][isc]->SetMarkerStyle( 24+im );
				gr_SC_xpt_ratio[im][ic][isc]->SetMarkerSize(1.1);
				gr_SC_xpt_ratio[im][ic][isc]->SetMarkerColor( isc==0?kBlue:kRed );
				gr_SC_xpt_ratio[im][ic][isc]->SetLineColor( isc==0?kBlue:kRed);
			}
		}
	}

	// Draw in multicanvas for final paper // 
	// 3 x 2 ?
	const int nx = 3;
	const int ny = 2;
	const int nbins = 6;
	double lrX[nx];
	double urX[nx];
	double lrY[nx][ny];
	double urY[nx][ny];

	// Draw 3,2 first // 
	int isc=0;

	for(int ix=0; ix <nx; ix++){
		lrX[ix] = 0;
		urX[ix] = 1.8;
		for(int iy=0; iy<ny; iy++){	
			lrY[ix][iy] = -0.27;
			urY[ix][iy] = 0.26;
		}
	}
	JmxnTPad *pad1 = new JmxnTPad( nx, ny, lrX, urX, lrY[0], urY[0]);
	pad1->SetCanvas(1.5, 800, 10, 10);
	pad1->SetOptionsLabelAxisX(0.008,0.58, 42);
	pad1->SetOptionsLabelAxisY(0.008,0.32, 42);
	pad1->SetSizeOfLabelPadsAxisY(0.05,0.017);
	pad1->SetTitleX(" p_{T,min} ( p_{T,min} < p_{T} < 5 GeV/#it{c} )", 1,0.04, 42, 1.4);
	pad1->SetTitleY("SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT",1,0.04,42,1.2);
	TLegend *leg[nx*ny];
	TLegend *leg_ampt;
	TLatex latex;
	for(int ix=0; ix<nx; ix++){
			for(int iy=0; iy<ny; iy++){
					int count = ix + nx* iy;


					if(ix==0 && iy==0){
							cout << count << endl;
							leg[count] = new TLegend( 0.1, 0.7, 0.8, 0.8, Form("ALICE Pb+Pb #sqrt{S_{NN}}=2.76 TeV"), "brNDC" );
							leg_ampt = new TLegend( 0.00, 0.13, 0.5, 0.31, "", "brNDC" );
							leg_ampt->SetFillStyle(0);
							leg_ampt->SetBorderSize(0);
							leg_ampt->SetTextSize(0.045);
					};
					if(count !=0)leg[count] = new TLegend( 0.05, 0.1, 0.88, 0.5, "", "brNDC");
					leg[count]->SetFillStyle(0);
					leg[count]->SetBorderSize(0);
					leg[count]->SetTextSize(0.035);
					//			pad1->SetCaption( ix, iy, Form("Centrality %02.0f ~ %02.0f", CentBins[count], CentBins[1+count] ) );
					//			pad1->SetOptionsCaption( 15, 43, 0.7, 3./5. );
			}
	}
	pad1->SetYCaption(8.8 / 10. );
	pad1->Draw();	

	for(int ix=0; ix<nx; ix++){
		for(int iy=0; iy<ny; iy++){
			TPad *p = pad1->GetPad(ix, iy);
			p->cd();
			p->SetGridx(0);
			p->SetGridy(1);
						
			int count = ix + nx* iy;
			latex.SetTextSize(0.052);
			latex.DrawLatex( 0.3, 0.17, Form("%2.f - %2.f%%", CentBins[count], CentBins[count+1]));	
		
			gr_SC_xpt_err[kQC][count][isc]->Draw("same 2");	
			gr_SC_xpt[kQC][count][isc]->Draw("same p");
			if( count == 0 ) leg[count]->AddEntry( gr_SC_xpt[kQC][count][isc], "SC(3,2)/#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT", "p");

			for(int iampt=0; iampt<3; iampt++){
				if(Draw_AMPT[iampt]==1){
					int kampt = iampt+1;
					if(kampt==3) kampt=0;

					gr_SC_xpt_AMPT[kampt][kQC][count][isc]->Draw("same p");
					if(count==0) leg_ampt->AddEntry( gr_SC_xpt_AMPT[kampt][kQC][count][isc], strAMPT[kampt], "p" );

				}
			}
			if(count==0) leg_ampt->Draw();
			leg[count]->Draw();
		}
	}
	p->GetCanvas()->SaveAs("figs/fig5_QConly_xminpt_nSC32.eps");


	// Draw 4,2 first // 
	int isc=1;

	for(int ix=0; ix <nx; ix++){
		lrX[ix] = 0;
		urX[ix] = 1.8;
		for(int iy=0; iy<ny; iy++){	
				if(iy==0){
						lrY[ix][iy] = -0.05;
						urY[ix][iy] = 0.4;
				}			
				if(iy==1){
						lrY[ix][iy] = 0.11;
						urY[ix][iy] = 1.85;
				}
		}
	}
	JmxnTPad *pad2 = new JmxnTPad( nx, ny, lrX, urX, lrY[0], urY[0]);
	pad2->SetCanvas(1.5, 800, 10, 10);
	pad2->SetOptionsLabelAxisX(0.008,0.58, 42);
	pad2->SetOptionsLabelAxisY(0.008,0.32, 42);
	pad2->SetSizeOfLabelPadsAxisY(0.05,0.017);
	pad2->SetTitleX(" p_{T,min} ( p_{T,min} < p_{T} < 5 GeV/#it{c} )", 1,0.04, 42, 1.4);
	pad2->SetTitleY("SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT",1,0.04,42,1.2);
	TLegend *leg2[nx*ny];
	for(int ix=0; ix<nx; ix++){
			for(int iy=0; iy<ny; iy++){
					int count = ix + nx* iy;
					if( count == 0){
							leg2[count] = new TLegend( 0.05, 0.40, 0.6, 0.74, Form("ALICE Pb+Pb #sqrt{S_{NN}}=2.76 TeV"), "brNDC" );
							leg2[count]->SetTextSize(0.04);
					};
					if( count !=0 ){
							leg2[count] = new TLegend( 0., 0.55, 0.6, 0.75, "", "brNDC");
							leg2[count]->SetTextSize(0.045);
					}

					leg2[count]->SetFillStyle(0);
					leg2[count]->SetBorderSize(0);
			}
	}
	pad2->SetYCaption(8.8 / 10. );
	pad2->Draw();	

	for(int ix=0; ix<nx; ix++){
		for(int iy=0; iy<ny; iy++){
			TPad *p = pad2->GetPad(ix, iy);
			p->cd();
			p->SetGridx(0);
			p->SetGridy(1);
		
			int count = ix + nx* iy;
			if(iy==0){
					latex.DrawLatex( 0.1, 0.32, Form("%.f - %.f%%", CentBins[count], CentBins[count+1]));	
			}
			else{
			latex.DrawLatex( 0.1, 1.55, Form("%.f - %.f%%", CentBins[count], CentBins[count+1]));		
			}

			gr_SC_xpt_err[kQC][count][isc]->Draw("same 2");	
			gr_SC_xpt[kQC][count][isc]->Draw("same p");
			if( count == 0 ) leg2[count]->AddEntry( gr_SC_xpt[kQC][count][isc], "SC(4,2)/#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT", "p");

			for(int iampt=0; iampt<3; iampt++){
				if(Draw_AMPT[iampt]==1){
					int kampt = iampt+1;
					if(kampt==3) kampt=0;
					gr_SC_xpt_AMPT[kampt][kQC][count][isc]->Draw("same p");
					if(count==3 ) leg2[count]->AddEntry( gr_SC_xpt_AMPT[kampt][kQC][count][isc], strAMPT[kampt], "p" );

				}
			}
			leg2[count]->Draw();
		}
	}
	p->GetCanvas()->SaveAs("figs/fig5_QConly_xminpt_nSC42.eps");


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
										gr_SC_AMPT[iampt][im][ipt][isc] = (TGraphErrors*)fin_ampt[iampt][ipt]->Get(strGraphName[im][isc].Data());
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
										gr_SC_xpt_AMPT[iampt][im][icent][isc] = new TGraphErrors();
										gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetMarkerStyle( gAMPTMarker[iampt] );
										gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetMarkerSize(1.1);
										gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetMarkerColor( gAMPTColor[iampt] );
										gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetLineColor( gAMPTColor[iampt] );
										gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetFillStyle(3001);
										gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetFillColor( gAMPTColor[iampt] );
										//gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetLineStyle(2+iampt);
										gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetLineWidth(1.0);
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
 
									gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetPoint( ipt, x, y);
									gr_SC_xpt_AMPT[iampt][im][icent][isc]->SetPointError( ipt, ex, ey );
							}
					}
			}
	}
	};

};





