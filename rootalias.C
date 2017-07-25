//cat rootalias.C |awk -F ")" '{if($2=="{") print $0}' | grep -v for >a

/*
TGraph* GetGraphFromTF1(TF1* f)
void scale(TH1 *hid=0, float scale=0, float ped=0)
void scaleErrors(TH1 *hid=0, float scaledError=0.1 )
void scaleNotEquidistantHisto(TH1D *hid, double sc=1)
void myTGraphSmooth(TGraph &grr, double DDcut=1.1, int loops=2)
TH1D*  unitNorm(TH1D &hida)
void colind()
void seed()
void history()
void mc(int ic=1, float sc=1.0, float sdx=450, float sdy=10, int icoff=1, double aspect=1 )
void DividegPad(Int_t nx, Int_t ny, Float_t l=0.07, Float_t r=0.02, Float_t t=0.1, Float_t b=0.45)
void mc12(int ic=1, float sc=1.0, float frac=0.3, TH1& hid1, TH1& hid2)
void showit(TString InFile, TString keySubStr="hDphiAssoc")
void h2()
void d2()
void hsetp()
void hsetRanges(TH1& hid, TString xtit="", TString ytit=""
TGraph* getFillGrr(TGraphErrors* ingrr, int col=7)
TGraph* getFillGrr(TGraph *ingrr1, TGraph *ingrr2, int col=7)
TGraph* getFillGrr(TF1* f, int col=7 )
TGraph* getFillGrr(TF1* f1, TF1* f2, int col=7 )
void h2g(TH1D *hid, int offstart=1, int offend=0)

void printGrr(TGraphErrors *gr, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL)
void printGrr(TGraphAsymmErrors *gr, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL)
void printGrr(TGraph *gr, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL)
void printHist(TH1 *hid, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL, double threshold=1e-12)

void smoothGrr(TGraphErrors *gr, char *fcn)
TGraphErrors* grrDivide( TGraphErrors *gr1, TGraphErrors *gr2)
TGraphErrors* grrScale( TGraphErrors *gr, TF1 *func)
TGraphErrors* grrScale( TGraphErrors *gr, double sc=1)
void scaleThisGrr( TGraphErrors &gr, double sc=1)
TGraphBentErrors* GetTGraphBentErrors(int nc,double *X,double *Y,double *EX, double *EY, double incl= 0.3, double aspect=40)
TGraphErrors *GetGraphFromHisto(TH1 *hid, TF1 *fT, int rebin=1, double scale=1, bool skipZeros=false )
TGraphAsymmErrors *GetAsymmGraphFromHisto(TH1 *hid, TF1 *ffit, int rebin=1, double sc=1, bool skipZeros=false )
TH1D *GetHistoFromGraph(TGraph *gr, TString sname="hid")
TGraphAsymmErrors *GetDataOverTheory(TGraphAsymmErrors *gr, TF1 *ftheory )
TGraphAsymmErrors *GetDataOverTheory(TGraphAsymmErrors *grData, TGraphAsymmErrors *grTheo )

void printArray(int NC, double *x, double *y, double *ex, double *ey,
        char *tnc="NC",char *tx="x",char *ty="y",char *tex="ex",char *tey="ey" )
void pPrint(char *name, char *can="c1")
void ppdf(char *name, TCanvas *can)

double GetTGraphErrorsMax(TGraphErrors *gr)
void GetXBinning(TH1 *hid)
TArrow *GetJTvector(double ax, double ay, double bx, double by, double cx, double cy){

void WriteJCard(TFile *fin, TFile *fout) 
void DrawALICELogo(Float_t x1, Float_t y1, Float_t x2, Float_t y2)

class TnameContent {
*/

//-----------------------------------------------
//try to avoid the problem with canvas repainting
//-----------------------------------------------
TGraph* GetGraphFromTF1(TF1* f){
    const int NGR=100;
    double x[NGR], y[NGR];
    double dx = ( f->GetXmax() - f->GetXmin() ) / NGR;
    for(int i=0;i<NGR;i++){
        x[i] = f->GetXmin() + i*dx;
        y[i] = f->Eval(x[i]);
        //cout<<i<<" "<<dx<<" "<<x[i]<<" "<<y[i]<<endl;
    } 
    TGraph *gr = new TGraph(NGR,x,y); 
    return gr;
}

//-------------------------------
// opens the root files
//-------------------------------
void bf(int update = 0)
{

    int id;
    char *option;
    new option = "r";

    if(update==1) option="update";

    gSystem->Exec("ls -l *.root |awk '{print NR,$9 }'");
    cin>>id;

    gSystem->Exec("ls -l *.root |awk '{print $9 }' >bftmp");
    FILE *inf   = fopen("bftmp","r");
    if(!inf){
        cerr<<"Error: could not open temporary file"<<endl; 
        return();
    }

    char name[255];
    for(int i=1;i<=id;i++) fscanf(inf,"%s",&name);
    cout<<name<<endl;
    TFile *file = new TFile(name,option);
    gSystem->Exec("rm bftmp");
    //delete option;

}

//-------------------------------
// Creates the browser canvas
//-------------------------------
void bb()
{
    TBrowser *brow = new TBrowser("brow");
}

void zone(int xdiv=1, int ydiv=1, int pos=1)
{
    int imax;
    int nopads;
    nopads=xdiv*ydiv;
    TPad *mpad;
    if(xdiv>ydiv) imax=xdiv; else imax=ydiv;
    gStyle->SetLabelSize(0.16*imax,"X");   
    gStyle->SetLabelSize(0.16*imax,"Y");   //has no effect ?!?!?
    c1 = new TCanvas("c1", "c1",506,8,598,598);
    char name[20];
    for(int iy=1;iy<=ydiv;iy++)
        for(int ix=1;ix<=xdiv;ix++){
            int ip = (iy-1)*xdiv+ix;
            double x1=1.0/xdiv*(ix-1);
            double x2=1.0/xdiv*(ix);
            double y1=1.0/ydiv*(ydiv-iy);
            double y2=1.0/ydiv*(ydiv-iy+1);
            sprintf(name,"mpad%d",ip);
            cout<<ip<<" "<<name<<endl;
            //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
            mpad = new TPad(name,"mpad",x1,y1,x2,y2,0,0,0);
            mpad->Draw();
        }
    mpad1->cd();
}

void mysum(const char* a1, const char* a2, double sc1=1, double sc2=1 )
{
    TH1D *a1tmp = (TH1D*)gDirectory->Get(a1);
    TH1D *a2tmp = (TH1D*)gDirectory->Get(a2);
    a1tmp->Clone("sum");
    sum->Add(a1tmp,a2tmp,sc1,sc2);
}


//_______________________________________________________
// normalization
void scale(TH1 *hid=0, float scale=0, float ped=0){
    double sc=0;
    if(scale==0) double sc=1/hid->Integral(); else sc=scale;

    const int nb=hid->GetNbinsX();

    for(int i=1;i<=nb;i++) {
        hid->SetBinContent(i,hid->GetBinContent(i)*sc+ped);
        hid->SetBinError(i,hid->GetBinError(i)*sc);
    }

    // hid->Scale(sc);     //doesn't scale the errors
}

//_______________________________________________________
//replace all errors by percentage of the value
void scaleErrors(TH1 *hid=0, float scaledError=0.1 ){
    const int nb=hid->GetNbinsX();
    for(int i=1;i<=nb;i++) hid->SetBinError(i,hid->GetBinContent(i)*scaledError);
}

void scaleNotEquidistantHisto(TH1D *hid, double sc=1){
    for(int i=1;i<= hid->GetNbinsX();i++){
        hid->SetBinContent(i,hid->GetBinContent(i)*sc/hid->GetBinWidth(i));
        hid->SetBinError(i,hid->GetBinError(i)*sc/hid->GetBinWidth(i));
    }
}
//-------------------------------
// 
//-------------------------------
void mysample(TH1D *fromh, TH1D *toh )
{
    if(fabs(toh->GetBinWidth(1)-fromh->GetBinWidth(1))>1e-5){
        cout<<" Attempt to integrate histograms with non-compatible binning"<<endl;
        printf("%16.14f %16.14f %16.14f \n", fromh->GetBinWidth(1), toh->GetBinWidth(1), fabs(toh->GetBinWidth(1)-fromh->GetBinWidth(1)) );
        return;
    }

    for(int idphi=1; idphi<=toh->GetNbinsX(); idphi++){
        double sum=0,err=0, a,b,e;
        for (int i = 1;i <= fromh->GetNbinsX();i++)
        {
            double phi1 = fromh->GetBinCenter(i);
            double dphi = toh->GetBinCenter(idphi);
            double phi2 = atan2(sin(phi1+dphi),cos(phi1+dphi));
            a=fromh->GetBinContent(i);
            b=fromh->GetBinContent(fromh->FindBin(phi2));
            sum += a*b;
            err += a*b*(a+b);
        }
        if( idphi==1 || idphi== toh->GetNbinsX() ) sum /= 2.0;
        toh->SetBinContent(idphi,toh->GetBinContent(idphi)+sum);
        e=toh->GetBinError(idphi);
        toh->SetBinError(idphi,sqrt(err+e*e));
    }
}

void myTGraphSmooth(TGraph &grr, double DDcut=1.1, int loops=2){
    const int ND=grr.GetN();
    double x[500], y[500];
    for(int i=0; i<ND; i++) grr.GetPoint(i, x[i], y[i]);
    for(int i=1; i<ND-2;i++){
        double D[2], DD, dlt=x[i-1]-x[i];
        D[0]=(y[i+0]-y[i-1])/dlt;
        D[1]=(y[i+1]-y[i+0])/dlt;
        DD=(D[1]-D[0])/dlt;
        if(fabs(DD[i])>DDcut) y[i+1]=0.5*(y[i]+y[i+2]);
    } 
    for(int j=0;j<loops;j++) 
        for(int i=1;i<ND-1;i++) y[i]=0.5*(y[i-1]+y[i+1]);
    for(int i=0; i<ND;  i++) grr.SetPoint(i, x[i], y[i]);
}


TH2D* smooth2(TH2D *hida )
{
    hid = (TH2D*) hida->Clone();
    hid->SetBinContent(0, 0);
    hid->SetBinError(0, 0);


    for (int ix = 2; ix < hid->GetNbinsX();ix++)
        for (int jy = 2; jy < hid->GetNbinsY();jy++)
        {
            double sum=0;
            for (int i = -1; i <= 1;i++)
                for (int j = -1; j <= 1;j++)
                    sum += hida->GetBinContent(ix+i,jy+j);
            hid->SetBinContent(ix, jy, sum/9.0 );
        }
    return hid;
}

TH1D*  unitNorm(TH1D &hida){
    if(hida->GetEntries()<=0 ){
        cout<<"Empty histogram  = "<<hida->GetEntries()<<endl;
        exit(0);    
    }
    double norm = hida->GetEntries()/hida->GetNbinsX();
    hidb = (TH1D*) hida->Clone();
    hidb->SetBinContent(0, 0);
    hidb->SetBinError(0, 0);

    for (int i = 0;i < hida->GetNbinsX();i++){
        if(hida->GetBinContent(i + 1)>0){
            double a = hida->GetBinContent(i + 1)/norm;
            double sa =  a*sqrt( 1/hida->GetBinContent(i + 1) +  1/hida->GetEntries());
        } else {
            a=0; sa=0;
        }
        hidb->SetBinContent(i + 1, a );
        hidb->SetBinError(i + 1, sa );
    }
    return hidb;
}


void colind(){
    TCanvas *c10 = new TCanvas("c10","c10",8,300,600,400);
    char name[4];  

    for(int l=0;l<15;l++){
        for(int i=0;i<=16;i++){
            sprintf(name,"%d",i+l*16);

            TLatex *tex = new TLatex(i/20.+.05,(4-l)*0.05+0.7,name);
            tex->SetTextColor(i+l*16);
            tex->SetTextSize(0.04);
            tex->SetLineWidth(2);
            tex->Draw();
        }
    }
    double x,y;
    int id;
    TCanvas *c12 = new TCanvas("c12","c12",600,300,600,400);
    for(int l=0;l<2;l++){
        for(int i=0;i<=10;i++){
            id=l*20+i+(1-l)*1;
            x=i/20.+0.2;
            y=0.6+0.2*l;
            sprintf(name,"%d",id);
            mark = new TMarker(x,y,id);
            mark->SetMarkerSize(2.2);	mark->Draw();
            TLatex *tex = new TLatex(x-0.01,y-0.1,name);
            tex->Draw();
        }
    }
}

void seed(){
    Int_t seed = (Int_t)(time(NULL)/3);
    cout<<seed<<endl;
}

void history(){
    //gSystem->Exec("tail -100 \"/home/Jan Rak/.root_hist\" ");
    gSystem->Exec("cat \"$HOME/.root_hist\" ");

}
void mc(int ic=1, float sc=1.0, float sdx=300, float sdy=100, int ichop=10, double aspect=1 ){
    float mleft = 0.15, mbott = 0.15, topright = 0.06;
    TString name="c"; name+=ic;
    //cout<<gROOT->GetListOfCanvases()->FindObject(name)<<endl;
    if(gROOT->GetListOfCanvases()->FindObject(name)==NULL){
        int ic0=ic-1;
        int cx = sdx*(ic0%ichop)+10;
        int cy = sdy*(ic0-ic0%ichop)/ichop+10;
        //cout<<ic<<" "<<ichop<<" cx="<<cx<<" cy="<<cy<<" "<<(ic-ic%(ichop+1))/(ichop+1)<<endl;
        c = new TCanvas(name, name, cx, cy, int(400*sc*aspect), int(400*sc) );
        mpad = new TPad("mpad", "mpad", 0.01, 0.01, 0.99, 0.99, 0,0,0);
        mpad->SetLeftMargin(mleft);
        mpad->SetBottomMargin(mbott);
        mpad->SetTopMargin(topright);
        mpad->SetRightMargin(topright);
        mpad->Draw();
        mpad->cd();
    } else {
        TCanvas *tmp = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name);
        tmp->cd();
        //mpad->cd();
    }
    //else cout<<name<<" exists"<<endl;
}

void mco(int ic=1, float sc=1.0, float sdx=450, float sdy=10, int icoff=1, double aspect=1 ){
    float mleft = 0.15, mbott = 0.15;
    TString name="c"; name+=ic;
    //cout<<gROOT->GetListOfCanvases()->FindObject(name)<<endl;
    if(gROOT->GetListOfCanvases()->FindObject(name)==NULL){
        c = new TCanvas(name, name, sdx*(ic-icoff)+10, sdy, int(400*sc*aspect), int(400*sc) );
        mpad = new TPad("mpad", "mpad", 0.01, 0.01, 0.99, 0.99, 0,0,0);
        mpad->SetLeftMargin(mleft);
        mpad->SetBottomMargin(mbott);
        mpad->Draw();
        mpad->cd();
    } else {
        TCanvas *tmp = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name);
        tmp->cd();
        mpad->cd();
    }
    //else cout<<name<<" exists"<<endl;
    //cout<<"mpad->Divide()"<<endl;
}

TGraphBentErrors* GetTGraphBentErrors(int nc,double *X,double *Y,double *EX, double *EY, double incl= 0.3, double aspect=10){
    double *err_incl_upp_y = new double [nc]; 
    double *err_incl_low_y = new double [nc];
    for(int i=0;i<nc;i++){ 
        err_incl_upp_y[i] =-tan(incl)*EY[i]*aspect;// tan(inclh)*EY[i]; 
        err_incl_low_y[i] = tan(incl)*EY[i]*aspect;
        //cout<<EY[i]<<" "<<err_incl_upp_y[i]<<endl;
    }
    return  new TGraphBentErrors(nc, X, Y, NULL, NULL, EY, EY, NULL, NULL, err_incl_low_y, err_incl_upp_y);
}


//------------------------------------------------------------------------------------------
// function dividing canvas into nx * ny same pads, taken from root forum found by Filip
//------------------------------------------------------------------------------------------
// TCanvas* C = new TCanvas("c1", "c1", sdx, sdy, size*aspekt, size);
// C->SetFillStyle(4000); C->SetFillColor(10);
// float ml  = 0.07;  mb =  0.45; mr =  0.02;  mt =  0.1;   //separate pads
// DividegPad(nx,ny,ml,mr,mt,mb);
// C->cd(idx);
// pp = (TPad*) C->GetPad(idx);
// pp->SetFrameFillStyle(4000);
//------------------------------------------------------------------------------------------

void DividegPad(Int_t nx, Int_t ny, Float_t l=0.07, Float_t r=0.02, Float_t t=0.1, Float_t b=0.45){
    Int_t ix, iy, n=0;
    Double_t x1, x2, y1, y2;
    Double_t dx = ((1-r)*(1-l))/((1-r)*(1-l)*(nx-2)-r+2-l);
    Double_t dl = dx/(1-l);
    Double_t dy = ((1-t)*(1-b))/((1-t)*(1-b)*(ny-2)-t+2-b);
    Double_t db = dy/(1-b);
    char *name  = new char [strlen(gPad->GetName())+6]; 

    y1 = 0;
    y2 = db;

    for(iy=0; iy<ny; iy++){
        x1 = 0;
        x2 = dl;
        for(ix=0;ix<nx;ix++){
            if(x1 > x2) continue;
            n++;
            sprintf(name,"%s_%d",gPad->GetName(),n);
            pad = new TPad(name,name,x1,y1,x2,y2,0);
            if(ix==0)     pad->SetLeftMargin(l);
            if(ix==nx-1)  pad->SetRightMargin(r);
            if(iy==ny-1)  pad->SetTopMargin(t);
            if(iy==0)     pad->SetBottomMargin(b);
            x1 = x2;

            if(ix==nx-2) x2 = 1;
            else         x2 = x1+dx;

            pad->SetNumber(n);
            pad->Draw();
        }
        y1 = y2;
        if(iy==ny-2) y2 = 1;
        else         y2 = y1+dy;
    }
} 


void mc12(int ic=1, float sc=1.0, float frac=0.3, TH1& hid1, TH1& hid2){
    //TString xtit="", TString ytit1="", TString ytit2=""){
    float mleft = 0.2, mbott = 0.15;
    TString name="c"; name+=ic;
    //if(gROOT->GetListOfCanvases()->FindObject(name)==NULL){
    c = new TCanvas(name, name, 450*(ic-1)+10, 10, int(400*sc), int(400*sc) );
    c->cd();
    TPad *mpad1 = new TPad("mpad1","mpad1", 0.0, frac, 1.0, 1.0);
    mpad1->SetBottomMargin(0.0);
    mpad1->SetLeftMargin(mleft);
    mpad1->SetFillColor(0);
    mpad1->Draw();
    mpad1->cd();

    double titoffx = 0.9, titoffy = 0.9;
    double titsizex = 0.08, titsizey = 0.08;
    double labeloffx = -0.02, labeloffy = 0.01;
    double labelsizex = 0.06, labelsizey = 0.06;

    hid1.GetYaxis()->SetTitleOffset(titoffy);
    //hid1.GetXaxis()->SetLabelOffset(labeloffx);
    hid1.GetYaxis()->SetLabelOffset(labeloffy);
    hid1.GetXaxis()->SetLabelSize(labelsizex);
    hid1.GetYaxis()->SetLabelSize(labelsizey);
    //hid1.GetXaxis()->SetTitle(" ");
    //hid1.GetYaxis()->SetTitle(ytit1);
    hid1.GetYaxis()->CenterTitle(1);
    hid1.GetYaxis()->SetTitleSize(titsizey);

    hid1.Draw();

    c->cd();
    TPad *mpad2 = new TPad("mpad2","mpad2", 0.0, 0.0, 1.0, frac); 
    mpad2->SetLeftMargin(mleft);
    mpad2->SetBottomMargin(0.4);
    mpad2->SetTopMargin(0.0);
    mpad2->SetFillColor(0);
    mpad2->Draw();
    mpad2->cd();

    double scfrac = 0.7/frac;
    hid2.GetXaxis()->SetTitleOffset(titoffx);
    hid2.GetYaxis()->SetTitleOffset(titoffy/scfrac);
    hid2.GetXaxis()->SetTitleSize(titsizex*scfrac);
    hid2.GetYaxis()->SetTitleSize(titsizey*scfrac*0.8);

    hid2.GetXaxis()->SetLabelOffset(labeloffx);
    hid2.GetYaxis()->SetLabelOffset(labeloffy);
    hid2.GetXaxis()->SetLabelSize(labelsizex*scfrac);
    hid2.GetYaxis()->SetLabelSize(labelsizey*scfrac);
    hid2.GetXaxis()->SetNdivisions(505);
    hid2.GetYaxis()->SetNdivisions(505);
    //hid2.GetXaxis()->SetTitle(xtit);
    //hid2.GetYaxis()->SetTitle(ytit2);
    hid2.GetXaxis()->CenterTitle(1);
    hid2.GetYaxis()->CenterTitle(1);

    hid2.Draw();
}



void showit(TString InFile, TString keySubStr="hDphiAssoc"){

    cout<<"++++++++++++++++++++++++++++"<<endl;
    cout<<"showit(\"histoName.root\",\"substring\"=\"all\")"<<endl;
    cout<<"++++++++++++++++++++++++++++"<<endl;
    c1 = new TCanvas("c1", "c1",50,10,400,400);
    mpad = new TPad("mpad","mpad",0.01,0.01,0.99,0.99,0,0,0);
    mpad->Draw();
    mpad->cd();

    TFile fin(InFile);
    TIter next(fin.GetListOfKeys());
    TKey * key;
    while( (key=(TKey*)next()) ){
        TH1F *hid = (TH1F *)fin.Get(key->GetName());
        TString sname=key->GetName();
        if( sname.SubString(keySubStr).Length()>0 || keySubStr=="all"){
            hid->Draw();
            c1->Update();
            cout<<"+++  "<<key->GetName()<<"  +++"<<endl; 
            cout<<"quit? y"<<endl;
            if(getchar()=='y')   return;
        }
    }
    fin.Close();
}


void h2(){

    long inVal;

    cout << "hex: ";
    cin >> hex >>inVal;

    for(int i=31; i>=0; i--){
        if( ((i+1) % 4 == 0) && i != 31 ) cout<<':';
        cout<< (( inVal & (1 << i )) != 0 );
    }
    cout << "    dec: " << inVal << "  hex: "<<  hex << inVal << dec << endl;
    cout << "rrrr rrrr ssss yyxx xxxx xxxx xxxx xx10"<<endl;
}


void d2(){

    long inVal;

    cout << "dec: ";
    cin >>inVal;

    for(int i=31; i>=0; i--){
        if( ((i+1) % 4 == 0) && i != 31 ) cout<<':';
        cout<< (( inVal & (1 << i )) != 0 );
    }
    cout << "    dec: " << inVal << "  hex: "<<  hex << inVal << dec << endl;
    cout << "rrrr rrrr ssss yyxx xxxx xxxx xxxx xx10"<<endl;

}

void hsetRanges(THStack& hid, TString xtit="", TString ytit="",
        double xmin = 0, double xmax = 1,
        double ymin = 0, double ymax = 1,
        double titoffx = 1.1, double titoffy = 1.1,
        double titsizex = 0.06, double titsizey = 0.06,
        double labeloffx =  0.01, double labeloffy = 0.001,
        double labelsizex = 0.05, double labelsizey = 0.05,
        int divx = 505, int divy=505)
{
    hid.GetXaxis()->SetTitle(xtit);
    hid.GetYaxis()->SetTitle(ytit);

    hid.GetXaxis()->SetRange( hid.GetHistogram()->FindBin(xmin), hid.GetHistogram()->FindBin(xmax) );
    hid.SetMinimum(ymin);
    hid.SetMaximum(ymax);

    hid.GetXaxis()->CenterTitle(1);
    hid.GetYaxis()->CenterTitle(1);

    hid.GetXaxis()->SetTitleOffset(titoffx);
    hid.GetYaxis()->SetTitleOffset(titoffy);

    hid.GetXaxis()->SetTitleSize(titsizex);
    hid.GetYaxis()->SetTitleSize(titsizey);

    hid.GetXaxis()->SetLabelOffset(labeloffx);
    hid.GetYaxis()->SetLabelOffset(labeloffy);

    hid.GetXaxis()->SetLabelSize(labelsizex);
    hid.GetYaxis()->SetLabelSize(labelsizey);

    hid.GetXaxis()->SetNdivisions(divx);
    hid.GetYaxis()->SetNdivisions(divy);

    hid.GetXaxis()->SetTitle(xtit);
    hid.GetYaxis()->SetTitle(ytit);

    hid.GetXaxis()->SetLabelFont(42);
    hid.GetYaxis()->SetLabelFont(42);
    hid.GetXaxis()->SetTitleFont(42);
    hid.GetYaxis()->SetTitleFont(42);
}

void hsetRanges(TH1& hid, TString xtit="", TString ytit="",
        double xmin = 0, double xmax = 1,
        double ymin = 0, double ymax = 1,
        double titoffx = 1.1, double titoffy = 1.1,
        double titsizex = 0.06, double titsizey = 0.06,
        double labeloffx =  0.01, double labeloffy = 0.001,
        double labelsizex = 0.05, double labelsizey = 0.05,
        int divx = 505, int divy=505)
{
    hid.GetXaxis()->SetTitle(xtit);
    hid.GetYaxis()->SetTitle(ytit);

    hid.GetXaxis()->SetRange( hid.FindBin(xmin), hid.FindBin(xmax) );
    hid.SetMinimum(ymin);
    hid.SetMaximum(ymax);

    hid.GetXaxis()->CenterTitle(1);
    hid.GetYaxis()->CenterTitle(1);

    hid.GetXaxis()->SetTitleOffset(titoffx);
    hid.GetYaxis()->SetTitleOffset(titoffy);

    hid.GetXaxis()->SetTitleSize(titsizex);
    hid.GetYaxis()->SetTitleSize(titsizey);

    hid.GetXaxis()->SetLabelOffset(labeloffx);
    hid.GetYaxis()->SetLabelOffset(labeloffy);

    hid.GetXaxis()->SetLabelSize(labelsizex);
    hid.GetYaxis()->SetLabelSize(labelsizey);

    hid.GetXaxis()->SetNdivisions(divx);
    hid.GetYaxis()->SetNdivisions(divy);

    hid.GetXaxis()->SetTitle(xtit);
    hid.GetYaxis()->SetTitle(ytit);

    hid.GetXaxis()->SetLabelFont(42);
    hid.GetYaxis()->SetLabelFont(42);
    hid.GetXaxis()->SetTitleFont(42);
    hid.GetYaxis()->SetTitleFont(42);
}

void hset(TH1& hid, TString xtit="", TString ytit="",
        double titoffx = 1.1, double titoffy = 1.1,
        double titsizex = 0.06, double titsizey = 0.06,
        double labeloffx = 0.01, double labeloffy = 0.01,
        double labelsizex = 0.05, double labelsizey = 0.05,
        int divx = 505, int divy=505)
{
    hid.GetXaxis()->CenterTitle(1);
    hid.GetYaxis()->CenterTitle(1);

    hid.GetXaxis()->SetTitleOffset(titoffx);
    hid.GetYaxis()->SetTitleOffset(titoffy);

    hid.GetXaxis()->SetTitleSize(titsizex);
    hid.GetYaxis()->SetTitleSize(titsizey);

    hid.GetXaxis()->SetLabelOffset(labeloffx);
    hid.GetYaxis()->SetLabelOffset(labeloffy);

    hid.GetXaxis()->SetLabelSize(labelsizex);
    hid.GetYaxis()->SetLabelSize(labelsizey);

    hid.GetXaxis()->SetNdivisions(divx);
    hid.GetYaxis()->SetNdivisions(divy);

    hid.GetXaxis()->SetTitle(xtit);
    hid.GetYaxis()->SetTitle(ytit);

    hid.GetXaxis()->SetLabelFont(42);
    hid.GetYaxis()->SetLabelFont(42);
    hid.GetXaxis()->SetTitleFont(42);
    hid.GetYaxis()->SetTitleFont(42);
}


void hsetp(){
    cout<<"hset(*hfr,\" \",\" \",1.1, 1.1, 0.06, 0.06, 0.01,0.001, 0.05,0.05, 505, 505);"<<endl;
}

TGraph* getFillGrr(TGraphErrors* ingrr, int col=7){
    int ii=2*ingrr->GetN();
    const int N = ii;
    double x[N],y[N];
    for(int i=0; i<N/2; i++){
        ingrr->GetPoint(i, x[i], y[i]);
        y[i] +=ingrr->GetErrorY(i);
    }
    for(int i=N/2; i<N; i++){
        ingrr->GetPoint(N-i-1, x[i], y[i]);
        y[i] -=ingrr->GetErrorY(N-i-1);
    }
    //for(int i=0; i<N; i++) cout<<i<<" "<<x[i]<<" "<<y[i]<<endl;
    local_filled_graph = new TGraph(N,x,y);
    local_filled_graph->SetFillStyle(1001);
    local_filled_graph->SetFillColor(col);
    return local_filled_graph;
}

TGraph* getFillGrr(TGraph *ingrr1, TGraph *ingrr2, int col=7){
    int ii=2*ingrr1->GetN();
    const int N = ii;
    double x[N],y[N];
    for(int i=0; i<N/2; i++)    ingrr1->GetPoint(i, x[i], y[i]);
    for(int i=N/2; i<N; i++)    ingrr2->GetPoint(N-i-1, x[i], y[i]);
    local_filled_graph = new TGraph(N,x,y);
    local_filled_graph->SetFillStyle(1001);
    local_filled_graph->SetFillColor(col);
    return local_filled_graph;
}

TGraph* getFillGrr(TF1* f,  int col=7 ){
    const int N = 300;
    double x[N],y[N], ax;
    double xmin=f1->GetXmin(), xmax=f1->GetXmax(), dx=2*(xmax-xmin)/N;
    for(int i=0; i<N/2; i++){
        x[i] = xmin+i*dx;
        y[i] = f->Eval(x[i]);
    }
    for(int i=N/2; i<N; i++){
        x[i] = xmax+(N/2-i-1)*dx;
        y[i] = 0;
    }
    //for(int i=0; i<N; i++) cout<<i<<" "<<x[i]<<" "<<y[i]<<endl;
    local_filled_graph = new TGraph(N,x,y);
    local_filled_graph->SetFillStyle(1001);
    local_filled_graph->SetFillColor(col);
    return local_filled_graph;
}


TGraph* getFillGrr(TF1* f1, TF1* f2, int col=7 ){
    const int N = 100;
    double x[N],y[N], ax;
    double xmin=f1->GetXmin(), xmax=f1->GetXmax(), dx=2*(xmax-xmin)/N;
    for(int i=0; i<N/2; i++){
        x[i] = xmin+i*dx;
        y[i] = f1->Eval(x[i]);
    }
    for(int i=N/2; i<N; i++){
        x[i] = xmax+(N/2-i-1)*dx;
        y[i] = f2->Eval(x[i]);
    }
    //for(int i=0; i<N; i++) cout<<i<<" "<<x[i]<<" "<<y[i]<<endl;
    local_filled_graph = new TGraph(N,x,y);
    local_filled_graph->SetFillStyle(1001);
    local_filled_graph->SetFillColor(col);
    return local_filled_graph;
}

void h2g(TH1D *hid, int offstart=1, int offend=0){
    int    NC =  hid->GetNbinsX()-offend;
    cout<<"const int NC="<<NC+1-offstart<<";"<<endl;
    cout<<"double binx[NC]={";  for(int i=offstart; i<=NC; i++) cout<<hid->GetBinCenter(i)<<", ";cout<<"\b\b};"<<endl;
    cout<<"double ebinx[NC]={0};"<<endl;
    cout<<"double co[NC]  ={";  for(int i=offstart; i<=NC; i++) cout<<hid->GetBinContent(i)<<", ";cout<<"\b\b};"<<endl;
    cout<<"double eco[NC] ={";  for(int i=offstart; i<=NC; i++) cout<<hid->GetBinError(i)<<", ";cout<<"\b\b};"<<endl;
    cout<<"grr = new TGraphErrors(NC,binx,co,ebinx,eco);"<<endl;
    cout<<"grr->SetMarkerStyle(21);"<<endl;
}

void printGrr(TGraphErrors *gr, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL){
    streambuf* sbuf = cout.rdbuf();
    if(file != NULL)  cout.rdbuf(file->rdbuf());

    double x[300], y[300], ex[300], ey[300];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii,x[ii],y[ii]);
        ex[ii] = gr->GetErrorX(ii);
        ey[ii] = gr->GetErrorY(ii);
    }
    cout<<"  const int NC = "<<NC<<";"<<endl;
    cout<<"  double "<<xn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<x[ii]<<", ";  cout<<x[NC-1]<<" };"<<endl;
    cout<<"  double "<<yn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<y[ii]<<", ";  cout<<y[NC-1]<<" };"<<endl;
    TString exn="e"; exn += xn; 
    cout<<"  double "<<exn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<ex[ii]<<", "; cout<<ex[NC-1]<<" };"<<endl;
    TString eyn="e"; eyn += yn; 
    cout<<"  double "<<eyn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<ey[ii]<<", "; cout<<ey[NC-1]<<" };"<<endl;
    cout<<grn<<" = new TGraphErrors(NC, "<<xn<<", "<<yn<<", "<<exn<<", "<<eyn<<");"<<endl<<endl;

    if(file != NULL) cout.rdbuf(sbuf);
}

void printGrr(TGraphAsymmErrors *gr, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL){
    streambuf* sbuf = cout.rdbuf();
    if(file != NULL)  cout.rdbuf(file->rdbuf());

    double x[300], y[300], exl[300], exh[300], eyl[300], eyh[300];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii,x[ii],y[ii]);
        exl[ii] = gr->GetErrorXlow(ii);
        exh[ii] = gr->GetErrorXhigh(ii);
        eyl[ii] = gr->GetErrorYlow(ii);
        eyh[ii] = gr->GetErrorYhigh(ii);
    }
    cout<<"  const int NC = "<<NC<<";"<<endl;
    cout<<"  double "<<xn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<x[ii]<<", ";  cout<<x[NC-1]<<" };"<<endl;
    cout<<"  double "<<yn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<y[ii]<<", ";  cout<<y[NC-1]<<" };"<<endl;
    TString exnl="e"; exnl += xn; exnl += "l"; 
    cout<<"  double "<<exnl<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<exl[ii]<<", "; cout<<exl[NC-1]<<" };"<<endl;
    TString exnh="e"; exnh += xn; exnh += "h"; 
    cout<<"  double "<<exnh<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<exh[ii]<<", "; cout<<exh[NC-1]<<" };"<<endl;
    TString eynl="e"; eynl += yn; eynl += "l"; 
    cout<<"  double "<<eynl<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<eyl[ii]<<", "; cout<<eyl[NC-1]<<" };"<<endl;
    TString eynh="e"; eynh += yn; eynh += "h"; 
    cout<<"  double "<<eynh<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<eyh[ii]<<", "; cout<<eyh[NC-1]<<" };"<<endl;
    cout<<grn<<" = new TGraphAsymmErrors(NC, "<<xn<<", "<<yn<<", "<<exnl<<", "<<exnh<<", "<<eynl<<", "<<eynh<<");"<<endl<<endl;

    if(file != NULL) cout.rdbuf(sbuf);
}


void printGrr(TGraph *gr, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL){
    streambuf* sbuf = cout.rdbuf();
    if(file != NULL)  cout.rdbuf(file->rdbuf());

    double x[300],y[300];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++)    gr->GetPoint(ii,x[ii],y[ii]);
    cout<<"  const int NC = "<<NC<<";"<<endl;
    cout<<"  double "<<xn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<x[ii]<<", "; cout<<x[NC-1]<<" };"<<endl;
    cout<<"  double "<<yn<<"[NC] = {"; for(int ii=0;ii<NC-1;ii++) cout<<y[ii]<<", "; cout<<y[NC-1]<<" };"<<endl;
    cout<<grn<<" = new TGraph(NC, "<<xn<<", "<<yn<<");"<<endl;

    if(file != NULL) cout.rdbuf(sbuf);
}

/*
   void printGrr(TH1D *hid, TString grn="grr", TString xn="x", TString yn="yn"){
   const int NC = hid->GetNbinsX();
   cout<<"  const int NC = "<<NC<<";"<<endl;
   cout<<"  double "<<xn<<"[NC] = {"; for(int ii=1;ii<NC;ii++) 
   cout<<hid->GetBinCenter(ii)<<", "; cout<<hid->GetBinCenter(NC)<<" };"<<endl;
   cout<<"  double "<<yn<<"[NC] = {"; for(int ii=1;ii<NC;ii++) 
   cout<<hid->GetBinContent(ii)<<", "; cout<<hid->GetBinContent(NC)<<" };"<<endl;
   TString exn="e"; exn += xn; 
   cout<<"  double "<<exn<<"[NC] = {"; for(int ii=1;ii<NC;ii++) 
   cout<<hid->GetBinWidth(ii)/2.<<", "; cout<<hid->GetBinWidth(NC)/2.<<" };"<<endl;
   TString eyn="e"; eyn += yn; 
   cout<<"  double "<<eyn<<"[NC] = {"; for(int ii=1;ii<NC;ii++) 
   cout<<hid->GetBinError(ii)<<", "; cout<<hid->GetBinError(NC)<<" };"<<endl;
   cout<<grn<<" = new TGraphErrors(NC, "<<xn<<", "<<yn<<", "<<exn<<", "<<eyn<<");"<<endl<<endl;;
   }
   */

void printHist(TH1 *hid, TString grn="grr", TString xn="x", TString yn="yn", ofstream *file=NULL, double threshold=1e-12){
    streambuf* sbuf = cout.rdbuf();
    if(file != NULL)  cout.rdbuf(file->rdbuf());

    double x[600], y[600], ex[600], ey[600];
    const int NC = hid->GetNbinsX();
    int counter  = 0;
    for(int ii=1;ii<=NC;ii++){
        if(hid->GetBinContent(ii) > threshold && hid->GetBinError(ii) >1e-12){
            x[counter] = hid->GetBinCenter(ii);
            y[counter] = hid->GetBinContent(ii);
            ex[counter] = hid->GetBinWidth(ii)/2.;
            ey[counter] = hid->GetBinError(ii);
            counter++;
        }
    }
    cout<<"  const int NC = "<<counter<<";"<<endl;
    cout<<"  double "<<xn<<"[NC] = {"; for(int ii=0;ii<counter-1;ii++) 
        cout<<x[ii]<<", "; cout<<x[counter-1]<<" };"<<endl;
    cout<<"  double "<<yn<<"[NC] = {"; for(int ii=0;ii<counter-1;ii++) 
        cout<<y[ii]<<", "; cout<<y[counter-1]<<" };"<<endl;
    TString exn="e"; exn += xn; 
    cout<<"  double "<<exn<<"[NC] = {"; for(int ii=0;ii<counter-1;ii++) 
        cout<<ex[ii]<<", "; cout<<ex[counter-1]<<" };"<<endl;
    TString eyn="e"; eyn += yn; 
    cout<<"  double "<<eyn<<"[NC] = {"; for(int ii=0;ii<counter-1;ii++) 
        cout<<ey[ii]<<", "; cout<<ey[counter-1]<<" };"<<endl;
    cout<<grn<<" = new TGraphErrors(NC, "<<xn<<", "<<yn<<", "<<exn<<", "<<eyn<<");"<<endl<<endl;;

    if(file != NULL) cout.rdbuf(sbuf);
}


void smoothGrr(TGraphErrors *gr, char *fcn){
    gr->Fit(fcn,"","QN");
    double x, y;
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii, x, y);
        y=gr->GetFunction(fcn)->Eval(x);
        gr->SetPoint(ii,x,y);
    }
}

TGraphErrors* grrDivide( TGraphErrors *gr1, TGraphErrors *gr2){
    double xin[2], yin[2], exin[2], eyin[2];
    double x[100], y[100], ex[100]={0}, ey[100];
    int NC =  gr1->GetN();
    for(int ii=0;ii<NC;ii++){
        gr1->GetPoint(ii, xin[0], yin[0]); exin[0] = gr1->GetErrorX(ii); eyin[0] = gr1->GetErrorY(ii);
        gr2->GetPoint(ii, xin[1], yin[1]); exin[0] = gr2->GetErrorX(ii); eyin[1] = gr2->GetErrorY(ii);
        x[ii] = xin[0];
        y[ii] = yin[1]!=0 ? yin[0]/yin[1] : 0 ;
        ex[ii]= exin[0];
        ey[ii]= yin[1]!=0 ? sqrt(pow(eyin[1]/yin[1],2)+pow(yin[0]/yin[1]*eyin[1],2)) : 0 ;
    }
    gr = new TGraphErrors(NC, x, y, ex, ey);
    return gr;
}

TGraphErrors* grrScale( TGraphErrors *gr, TF1 *func){
    double xin, yin, exin, eyin;
    double x[100], y[100], ex[100]={0}, ey[100];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii, xin, yin); exin = gr1->GetErrorX(ii); eyin = gr1->GetErrorY(ii);
        x[ii] = xin;
        y[ii] = yin * func->Eval(xin);
        ex[ii]= exin;
        ey[ii]= eyin * func->Eval(xin);
    }
    gr = new TGraphErrors(NC, x, y, ex, ey);
    return gr;
}

TGraphErrors* grrScale( TGraphErrors *gr, double sc=1){
    double xin, yin, exin, eyin;
    double x[100], y[100], ex[100]={0}, ey[100];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii, xin, yin); exin = gr->GetErrorX(ii); eyin = gr->GetErrorY(ii);
        x[ii] = xin;
        y[ii] = yin * sc;
        ex[ii]= exin;
        ey[ii]= eyin * sc;
    }
    gr = new TGraphErrors(NC, x, y, ex, ey);
    return gr;
}

void scaleThisGrr( TGraphErrors &gr, double sc=1){
    int NC =  gr.GetN();
    double xin, yin, exin, eyin;
    for(int ii=0;ii<NC;ii++){
        gr.GetPoint(ii, xin, yin);    exin = gr.GetErrorX(ii); eyin = gr.GetErrorY(ii);
        gr.SetPoint(ii, xin, yin*sc); gr.SetPointError(ii, exin, eyin*sc);
    }
}

void scaleThisGrr( TGraphAsymmErrors &gr, double sc=1){
    int NC =  gr.GetN();
    double xin, yin, exinl, exinh, eyinl, eyinh;
    for(int ii=0;ii<NC;ii++){
        gr.GetPoint(ii, xin, yin);    
        exinl = gr.GetErrorXlow(ii);  exinh = gr.GetErrorXhigh(ii); 
        eyinl = gr.GetErrorYlow(ii);  eyinh = gr.GetErrorYhigh(ii); 
        gr.SetPoint(ii, xin, yin*sc); gr.SetPointError(ii, exinl, exinh, eyinl*sc, eyinh*sc);
    }
}


//----------------------------------------------------------------------------------------------
//skipZeors = ignore empty bins when you want to compute an average y-value in bins (e.g mean pT)
//for normal counting skipZero should be false.
//----------------------------------------------------------------------------------------------
TGraphErrors *GetGraphFromHisto(TH1 *hid, TF1 *fT, int rebin=1, double scale=1, bool skipZeros=false ){
    const int nb = hid->GetNbinsX();
    const int newNb = nb/rebin + 1;
    double x[newNb], y[newNb], ex[newNb]={0}, ey[newNb];
    double sum  = 0, serror2 = 0; 
    int nonzero = 0, counts = 0;

    for(int ib=1; ib<=nb; ib += rebin){
        sum = 0;
        serror2 = 0;
        nonzero = 0;
        for(int ich=0; ich<rebin; ich++){
            sum     += hid->GetBinContent(ib+ich);
            serror2 += pow(hid->GetBinError(ib+ich),2);
            if( !(skipZeros && hid->GetBinContent(ib+ich)==0) ) nonzero++;
        }
        if(nonzero==0) continue;
        double error = sqrt(serror2)/nonzero;
        //if (error<=0.01) error = 0.5;
        if (error<=0.0) continue;

        double A = hid->GetBinLowEdge(ib);
        double B = hid->GetBinLowEdge(ib+rebin);
        x[counts] = fT->Moment(1, A, B);//  /fT->Moment(0, A, B);; //mean value of x on the interval
        y[counts] = sum/nonzero*scale;
        ey[counts] = error*scale;
        //cout<<ib<<" "<<x[counts]<<" "<<y[counts]<<" "<<ey[counts]<<endl;
        counts++;
    } 

    return new TGraphErrors(counts, x, y, ex, ey);
}

//----------------------------------------------------------------------------------------------
//skipZeors = ignore empty bins when you want to compute an average y-value in bins (e.g mean pT)
//for normal counting skipZero should be false.
//----------------------------------------------------------------------------------------------
TGraphAsymmErrors *GetAsymmGraphFromHisto(TH1 *hid, TF1 *ffit, int rebin=1, double sc=1, bool skipZeros=false ){
    const int nb = hid->GetNbinsX();
    const int newNb = nb/rebin + 1;
    double x[newNb], y[newNb], exl[newNb]={0}, exh[newNb], eyl[newNb]={0}, eyh[newNb];
    double sum  = 0, serror2 = 0; 
    int nonzero = 0, counts = 0;

    for(int ib=1; ib<=nb; ib += rebin){
        sum = 0;
        serror2 = 0;
        nonzero = 0;
        for(int ich=0; ich<rebin; ich++){
            double pout  = hid->GetBinCenter(ib+ich);
            sum     += hid->GetBinContent(ib+ich);
            serror2 += pow(hid->GetBinError(ib+ich),2);
            if( !(skipZeros && hid->GetBinContent(ib+ich)==0) ) nonzero++;
        }
        if(nonzero==0) continue;
        double error = sqrt(serror2)/nonzero;
        //if (error<=0.01) error = 0.5;
        if (error<=0.0) continue;

        double A = hid->GetBinLowEdge(ib);
        double B = hid->GetBinLowEdge(ib+rebin);
        x[counts] = ffit->Moment(1, A, B);  //mean value of x on the interval
        y[counts] = sum/nonzero*sc;
        exl[counts] = x[counts]-A;
        exh[counts] = B-x[counts];
        eyl[counts] = error*sc;
        eyh[counts] = error*sc;
        //cout<<ib<<" "<<x[counts]<<" "<<y[counts]<<" "<<eyl[counts]<<endl;
        counts++;
    } 

    return new TGraphAsymmErrors(counts, x, y, exl, exh, eyl, eyh);
}

TH1D *GetHistoFromGraph(TGraph *gr, TString sname="hid"){
    double x[300], y[300], exb[300];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii,x[ii],y[ii]);
        exb[ii] = x[ii]-gr->GetErrorXlow(ii);
    }
    exb[NC] = x[NC-1]+gr->GetErrorXhigh(NC-1);
    hid = new TH1D(sname,"",NC,exb);
    for(int ii=0;ii<NC;ii++){
        hid->SetBinContent(ii+1,y[ii]);
        //cout<<ii <<" "<< x[ii] <<" "<< exb[ii] << endl;
    }
    //cout<<exb[NC]<<endl;
    return hid; 
}


TGraphAsymmErrors *GetDataOverTheory(TGraphAsymmErrors *gr, TF1 *ftheory ){
    double x[300], y[300], exl[300], exh[300], eyl[300], eyh[300];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii,x[ii],y[ii]);
        exl[ii] = gr->GetErrorXlow(ii);
        exh[ii] = gr->GetErrorXhigh(ii);
        eyl[ii] = gr->GetErrorYlow(ii);
        eyh[ii] = gr->GetErrorYhigh(ii);
    }
    for(int ii=0;ii<NC;ii++){
        //y[ii]   = ( ftheory->Eval(x[ii]) - y[ii] )/y[ii];
        //eyl[ii] = ftheory->Eval(x[ii])*eyl[ii] / y[ii] / y[ii];
        //eyh[ii] = ftheory->Eval(x[ii])*eyh[ii] / y[ii] / y[ii];
        y[ii]   = ( ftheory->Eval(x[ii]) - y[ii] ) / ftheory->Eval(x[ii]);
        eyl[ii] = eyl[ii]/ftheory->Eval(x[ii]);
        eyh[ii] = eyh[ii]/ftheory->Eval(x[ii]);
    }
    return new TGraphAsymmErrors(NC, x, y, exl, exh, eyl, eyh);
}


TGraphAsymmErrors *GetDataOverTheory(TGraphAsymmErrors *grData, TGraphAsymmErrors *grTheo ){
    double x[300], y[300], exl[300], exh[300], eyl[300], eyh[300];
    int NC =  grData->GetN();
    for(int ii=0;ii<NC;ii++){
        grData->GetPoint(ii,x[ii],y[ii]);
        exl[ii] = grData->GetErrorXlow(ii);
        exh[ii] = grData->GetErrorXhigh(ii);
        eyl[ii] = grData->GetErrorYlow(ii);
        eyh[ii] = grData->GetErrorYhigh(ii);
    }
    for(int ii=0;ii<NC;ii++){
        double xTheo[1], yTheo[1];
        grTheo->GetPoint(ii, xTheo[0], yTheo[0]);
        double ydata =  fabs(y[ii])>0 ? y[ii] : 1;
        y[ii]   = ( yTheo[0] - ydata ) / ydata;
        eyl[ii] = eyl[ii]*yTheo[0]/ ydata / ydata;
        eyh[ii] = eyh[ii]*yTheo[0]/ ydata / ydata;
    }
    return new TGraphAsymmErrors(NC, x, y, exl, exh, eyl, eyh);
}



void printArray(int NC, double *x, double *y, double *ex, double *ey,
        char *tnc="NC",char *tx="x",char *ty="y",char *tex="ex",char *tey="ey" ){
    cout<<" const int "<<tnc<<" = "<<NC<<";"<<endl;

    cout<<" double "<<tx<<"["<<tnc<<"] ={";
    if(x!=NULL){for(int i=0;i<NC;i++)cout<<x[i]<<", ";cout<<"\b\b};"<<endl;
    } else cout<<"0};"<<endl;
    cout<<" double "<<ty<<"["<<tnc<<"] ={";
    if(y!=NULL){for(int i=0;i<NC;i++)cout<<y[i]<<", ";cout<<"\b\b};"<<endl;
    } else cout<<"0};"<<endl;
    cout<<" double "<<tex<<"["<<tnc<<"] ={";
    if(ex!=NULL){for(int i=0;i<NC;i++)cout<<ex[i]<<", ";cout<<"\b\b};"<<endl;
    } else cout<<"0};"<<endl;
    cout<<" double "<<tey<<"["<<tnc<<"] ={";
    if(ey!=NULL){for(int i=0;i<NC;i++)cout<<ey[i]<<", ";cout<<"\b\b};"<<endl;
    } else cout<<"0};"<<endl;
}

void pPrint(char *name, char *can="c1"){
    cout<<"  ppdf(\""<<name<<"\", "<<can<<");"<<endl;
}

void ppdf(char *name, TCanvas *can, int png=0){
    char newname[400];
    sprintf(newname,"%s.eps",name);
    //cout<<name <<" "<< newname <<endl;return;
    can->Print(newname);
    if(png==0){
        sprintf(newname,"pstopdf %s.eps; rm %s.eps; echo %s.pdf created",name,name,name);
        cout<<"Performing: "<<newname<<endl;
        gSystem->Exec(newname);
    } else {
        sprintf(newname,"pstopdf %s.eps; echo %s.pdf created",name,name,name);
        gSystem->Exec(newname);
        sprintf(newname,"%s.png",name);
        can->Print(newname);
    }
}

double GetTGraphErrorsMax(TGraphErrors *gr){
    double max = -1e20;
    double x[300], y[300], ex[300], ey[300];
    int NC =  gr->GetN();
    for(int ii=0;ii<NC;ii++){
        gr->GetPoint(ii,x[ii],y[ii]);
        ex[ii] = gr->GetErrorX(ii);
        ey[ii] = gr->GetErrorY(ii);
        if(y[ii]+ey[ii]>max) max = y[ii]+ey[ii];
    }
    return max;
}

void GetXBinning(TH1 *hid){
    int nb = hid->GetNbinsX();
    for(int i=1; i<=nb; i++)cout <<  hid->GetBinLowEdge(i) <<endl; 
    cout<<hid->GetBinLowEdge(nb)+hid->GetBinWidth(nb) <<endl; 
}

TArrow *GetJTvector(double ax, double ay, double bx, double by, double cx, double cy){

    // line a,b and point c

    double dx = bx-ax;
    double dy = by-ay;
    double x0 = 1./(dx*dx+dy*dy)*(dy*dy*ax+dx*dx*cx+dx*dy*(cy-ay));
    double y0 = dy/dx*(x0-ax)+ay;
    return new TArrow(cx, cy, x0, y0);
}

void WriteJCard(TFile *fin, TFile *fout) {
    TDirectory *dir = fin->GetDirectory("JCard");
    if (dir) {
        dir->cd();
        TIter next(gDirectory->GetListOfKeys());
        TKey * key; 
        TString olds;
        while( (key=(TKey*)next()) ){
            TString sname=key->GetName();
            TVector *mv = (TVector*)key->ReadObj();
            if(sname != olds) { // write once once
                fout->cd();
                mv->Write(sname);
                olds = sname;
            }
        }
    } else {
        cout <<"There is no JCard in this file" << endl;
    }
    fout->Close();
}

void PrintJCard(TString infile, TString keySubStr="all") {

    TFile *fin = new TFile(infile.Data(),"read");
    TDirectory *dir = fin->GetDirectory("JCard");
    if (dir) {
        dir->cd();
        TIter next(gDirectory->GetListOfKeys());
        TKey * key;
        TString olds;
        while( (key=(TKey*)next()) ){
            TString sname=key->GetName();
            TVector *mv = (TVector*)key->ReadObj();
            if(sname != olds) { // write once once
                if( sname.SubString(keySubStr).Length()>0 || keySubStr=="all"){
                    printf("%20s\t", sname.Data());
                    int NE    = mv->GetNoElements();
                    for(int i=0;i<NE;i++) cout << mv(i+1)<<" ";
                    cout <<endl;
                    //mv->Print();
                    olds = sname;
                }
            }
        }
    } else {
        cout <<"There is no JCard in this file" << endl;
    }
    fin->Close();
}



template <typename T>
    static inline T
sqr(const T &x)
{
    return x * x;
}


void DrawALICELogo(Float_t x1=.18, Float_t y1=.80, Float_t y2=.93)
{
    // correct for aspect ratio of figure plus aspect ratio of pad (coordinates are NDC!)
    // Printf("%d %f %d %f", gPad->GetCanvas()->GetWindowHeight(), gPad->GetHNDC(), gPad->GetCanvas()->GetWindowWidth(), gPad->GetWNDC());
    Float_t x2 = x1 + (y2 - y1) * 0.891 * gPad->GetCanvas()->GetWindowHeight() * gPad->GetHNDC() / (gPad->GetWNDC() * gPad->GetCanvas()->GetWindowWidth());
    // Printf("%f %f %f %f", x1, x2, y1, y2);

    TPad *myPadLogo = new TPad("myPadLogo", "Pad for ALICE Logo", x1, y1, x2, y2);
    myPadLogo->SetLeftMargin(0);
    myPadLogo->SetTopMargin(0);
    myPadLogo->SetRightMargin(0);
    myPadLogo->SetBottomMargin(0);
    myPadLogo->Draw();
    myPadLogo->cd();
    TASImage *myAliceLogo = new TASImage("~/ajan/ALICE/ALICE_various/2011-ALICE_PRELIMARY_logo_BLACK.png");
    myAliceLogo->Draw();
}

class TnameContent {
    public:
        TnameContent(TString inData){

            if     (inData.Contains("pp"))   collType = "pp";
            else if(inData.Contains("PbPb")) collType = "PbPb";

            TString energyStr="";
            if(inData.Contains("7TeV"))          energy = "7TeV";
            else if( inData.Contains("2.76TeV")) energy = "2.76TeV";

            TString trackCutStr="";
            if     (inData.Contains("TPCPl",TString::kIgnoreCase))   trackCut="TPCPlus";
            else if(inData.Contains("RAA",TString::kIgnoreCase))     trackCut="RAA";
            else if(inData.Contains("TPCOnly",TString::kIgnoreCase)) trackCut="TPCOnly";
            else if(inData.Contains("Hybrid",TString::kIgnoreCase))  trackCut="Hybrid";
            //cout<< collType <<" "<< energy <<" "<< trackCut <<endl; 
        }

        TString legend(double c1=0, double c2=100){
            TString stype = Form("%s #sqrt{s}=%s %s", collType.Data(), energy.Data(), collType != "pp" ? Form("C: %2.0f-%2.0f%%", c1, c2) : "" );
            return stype;
        }
        TString collType, energy, trackCut;
};



//int gOMarker[6] = {24, 25, 26, 27, 28, 30};
//int gCMarker[6] = {20, 21, 22, 33, 34, 29}; 
// msong color style (based on subway color)
int msColor[10] = { kBlue+1, kGreen+2, kOrange+2, kRed+1, kAzure+1, 
					kPink+8, kOrange-6, kYellow+3, kViolet-1, kSpring+5};
int msMarker[11] = {20, 24, 21, 25, 22, 26, 27, 28, 29, 30, 31};

void Shift_graph_X(TGraphErrors *gr, double xoffset){
    int NPoint = gr->GetN();
    for(int ipoint=0; ipoint<NPoint; ipoint++){
        double x = gr->GetX()[ipoint];
        double y = gr->GetY()[ipoint];
		gr->SetPoint( ipoint, x+xoffset, y);
    }
}


