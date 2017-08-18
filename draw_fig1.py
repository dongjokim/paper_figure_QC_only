import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.ticker as plticker
import ROOT

marker = ["s","o","D","8","*"]; #https://matplotlib.org/api/markers_api.html
color = ["black","blue","red","green","orange","yellow"];
gFillColor = ["blue", "red", "green", "orange"];

# int gOMarker[5] = {kOpenSquare, kOpenCircle, 28, kOpenSquare, kOpenCircle};
# int gCMarker[5] = {kFullSquare, kFullCircle, kFullCircle, kFullSquare, 33};
# int gColor[5] = {kBlue, kRed, kRed+2, kGreen+4, kCyan+2};
# int gFillColor[5] = {kBlue-4, kRed-4, kRed-6, kGreen-10, kCyan-4};

def TGraphErrorsToNumpy(gr):
	n = gr.GetN();
	x = np.empty(n);
	y = np.empty(n);
	xerr = np.empty(n);
	yerr = np.empty(n);

	a = ROOT.Double(0);
	b = ROOT.Double(0);
	for i in range(0,n):
		gr.GetPoint(i,a,b);
		x[i] = float(a);
		y[i] = float(b);
		xerr[i] = gr.GetErrorX(i);
		yerr[i] = gr.GetErrorY(i);

	return x,y,xerr,yerr;

p,ax = plt.subplots(1,2,sharex=False,sharey=False,figsize=(10,5)); #create a 1x2 canvas of aspect 2/1 with shared y-axis
#p.subplots_adjust(wspace=0.0,hspace=0.0); #remove the spacing between the pads

f = ROOT.TFile("PbPb2.76TeV_SCNSC.root");


#draw on the first pad
for i in range(0,5):
	tgraph = f.Get("gr_SC_{iset:02d}".format(iset=i)); #read the TGraphErrors
	if i < 2:
		tgraph = f.Get("gr_SC_{iset:02d}_CombinedSyst".format(iset=i)); #read the TGraphErrors
		title = tgraph.GetTitle(); #read the title and it to latex format
		x,y,xerr,yerr = TGraphErrorsToNumpy(tgraph);
		ax[0].fill_between(x,y-yerr,y+yerr,facecolor=gFillColor[i], alpha=0.1,label=title+" ( x 0.1) PRL 117 (2016) 182301");
	else:
		tgraph = f.Get("gr_SC_{iset:02d}".format(iset=i)); #read the TGraphErrors
		title = tgraph.GetTitle(); #read the title and it to latex format
		x,y,xerr,yerr = TGraphErrorsToNumpy(tgraph);
		ax[0].errorbar(x,y,yerr,linestyle="-",fmt=marker[i],color=color[i],label=title);

		ax[0].text(0.4,0.95,"ALICE Pb-Pb $\sqrt{s_{NN}}$ = 2.76 TeV",horizontalalignment='center',verticalalignment='center',transform=ax[0].transAxes,size=10);

ax[0].legend(frameon=False,prop={'size':9},loc="center",handletextpad=0.1,bbox_to_anchor=(0.4,0.8)); #title="Legend"

#draw on the second pad
for i in range(0,5):
	tgraph = f.Get("gr_NSC_{iset:02d}".format(iset=i)); #read the TGraphErrors
	title = tgraph.GetTitle(); #read the title and it to latex format
	x,y,xerr,yerr = TGraphErrorsToNumpy(tgraph);
	if i < 2:
		ax[1].fill_between(x,y-yerr,y+yerr,facecolor=gFillColor[i], alpha=0.1,label=title+" PRL 117 (2016) 182301");
	else:
		ax[1].errorbar(x,y,yerr,linestyle="-",fmt=marker[i],color=color[i],label=title);

ax[1].legend(frameon=False,prop={'size':9},loc="center",handletextpad=0.1,bbox_to_anchor=(0.4,0.8)); #title="Legend"


#SC
ax[0].set_xlim([0, 57]);
#ax[0].set_yscale("log");
#ax[0].set_ylim([-1.95e-7, 3.1e-7]); #Custom y-limits. Setting to ax[0] is enough, since the sharey=True above
#NSC
#ax[1].set_yscale("");
ax[1].set_xlim([0, 57]);
#ax[1].set_ylim([-0.5, 1.8]); #Custom y-limits. Setting to ax[0] is enough, since the sharey=True above

f.Close();

#set common parameters for both pads
for i,a in enumerate(ax):
	a.tick_params(which="major",direction="in",length=8.0);
	a.tick_params(which="minor",direction="in",length=4.0);

	a.xaxis.set_major_locator(plticker.MultipleLocator(10.0)); #set the x tick interval to mimic root style
	a.xaxis.set_minor_locator(plticker.MultipleLocator(2.0));

	#a.text(0.5,-0.1,["x1","x2"][i],horizontalalignment='center',verticalalignment='center',transform=a.transAxes,size=16);
	a.text(0.93,0.93,["(a)","(b)"][i],horizontalalignment='center',verticalalignment='center',transform=a.transAxes,size=12);
	a.text(-0.15,0.9,["SC(m,n)","NSC(m,n)"][i],rotation="vertical",transform=a.transAxes,size=16);

#Manually place the axis labels for shared axes. There might be a better way..
p.text(0.46,0.02,"Centrality percentile",size=16);

#plt.savefig("figs/chisq_bestfits.eps",bbox_inches="tight");
plt.show();
