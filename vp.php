<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="en">
<head>
<title>www.mgy.hu</title>
<meta http-equiv="Content-Type" content="text/html; charset=windows-1250">
</head>

<body bgcolor='white' text='black'>

<?php

$pct = $_GET['pict'] ;
$filename = $pct . '.txt' ;
//echo dirname($pct) . "-" . basename($pct) ;
$cim = '' ;

if (file_exists($filename))
  {
  $dataFile = fopen( $filename, "r" ) /*or (echo "Hiba: nincs ilyen fajl!")*/ ;
  if ( $dataFile )
    {
    while (!feof($dataFile))
      {
      $cim = $cim . fgets($dataFile, 4096) ;
      }
    fclose($dataFile) ;
    }
    else
    {
     $cim = $filename ;
    } ;
  } ;  

echo "<div align='left'>".$cim."</div>" ;
echo '<img src="'.$pct.'">' ;

?>

</body>
</html>
