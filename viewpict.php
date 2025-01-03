<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="en">
<head>
<title>www.mgy.hu - fotógaléria</title>
<meta http-equiv="Content-Type" content="text/html; charset=windows-1250">
<script src="http://www.google-analytics.com/urchin.js" type="text/javascript">
</script>
<script type="text/javascript">
_uacct = "UA-3157941-1";
urchinTracker();
</script>
<script language="javascript" type="text/javascript">
<!--
var newwindow;
function popitup(url)
{
	newwindow=window.open(url,'name','left=50,top=50,width=800,height=600,resizable=yes,scrollbars=yes,toolbar=yes,status=yes') ;
	if (window.focus) {newwindow.focus()}
	return false;
}
// --></script>
</head>

<body bgcolor='black' text='white' link='white' vlink='white' alink='red'>

<?php

error_reporting(0) ;

include( 'directoryinfo.inc.php' );

$folder = $_GET['id'] ;
$path = './photos/'.$folder.'/' ;
$spath = './photos/'.$folder.'/' ;
$pathtodir = './photos/'.$folder.'/' ;

$dirobj = new directory_info() ;
$myList = $dirobj->get_ext_based_filelist( null, $pathtodir, false ) ;
//print '<pre>filecount is : ' . $dirobj->fileselection_count . '<br /><br /></pre>' ;
$picture_db = ($dirobj->fileselection_count / 2) ;
//print '<pre>pdb: ' . $picture_db . '<br /><br /></pre>' ;
//$picture_db = 14 ;
//break ;

//echo '-' . $path . '-' ;

function tolt($str1)
{
$St = $str1 ;
$hossz = 3 ;
$mivel = '0' ;
while (strlen($St) < $hossz)
 {  
  $St = $mivel . $St ;
 }
return $St ;
}

$filename = $path . '/title.txt' ;
$dataFile = fopen( $filename, "r" ) /*or (echo "Hiba: nincs ilyen fajl!")*/ ;
if ( $dataFile )
  {
   while (!feof($dataFile))
   {
   $cim = fgets($dataFile, 4096) ;
   }
   fclose($dataFile) ;
  }
  else
  {
   $cim = $folder ;
  }
  ;

echo "<div align = 'center' id='header'><h1>".$cim."</h1></div>" ;

  $oszlopdb = 5 ;
  echo "<table cellpadding='0' cellspacing='0' align='center' style='line-height:100%; margin-top:0; margin-bottom:0;' border='0' cellspacing='0' bordercolordark='white' bordercolorlight='black' width='".(($oszlopdb*100)+$oszlopdb)."'>\n" ;
  $i = 1 ;
  $j = 1 ;
  $nev = 1 ;
  while ($i <= $picture_db)
    {
  	if ($j == 1)
   	  { echo "<tr>\n" ; }
      $small = $spath . 'small_image'.tolt($nev).'.jpg' ;
//        print '<pre>i: ' . $nev . '<br /><br /></pre>' ;
      if (file_exists($small))
        {
        $pict = $path . 'image'.tolt($nev).'.jpg' ;
        echo "<td>\n" ;
        echo "<a href='".$pict."' onclick=\"return popitup('".$pict."')\">" ;
        echo "<img src='". $small ."' border='2' vspace='2' hspace='2'>" ;
        echo "</a></td>\n" ;
        $j++ ;
        $i++ ;
        }
    	if ($j > $oszlopdb)
    	  {
    	  $j = 1 ;	
   	  	echo "</tr>\n" ;
   	  	}
      $nev++ ;
//      echo "</tr>\n" ;
    }
  echo "</table>\n" ;
?>

</body>
</html>
