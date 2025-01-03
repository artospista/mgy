<?php 
session_start();
ob_start();
?>
<?php
define("DEFAULT_LOCALE", "windows-1250");
@setlocale(LC_ALL, DEFAULT_LOCALE);	
?>
<?php
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT"); // Date in the past
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); // Always modified
header("Cache-Control: private, no-store, no-cache, must-revalidate"); // HTTP/1.1 
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache"); // HTTP/1.0
?>
<?php include ("ewconfig.php") ?>
<?php include ("db.php") ?>
<?php include ("esemenyinfo.php") ?>
<?php include ("advsecu.php") ?>
<?php include ("phpmkrfn.php") ?>
<?php include ("ewupload.php") ?>
<?php
	if (!IsLoggedIn()) {
		ob_end_clean();
		header("Location: login.php");
		exit();
	}
?>
<?php

// Initialize common variables
$x_kod = NULL;
$ox_kod = NULL;
$z_kod = NULL;
$ar_x_kod = NULL;
$ari_x_kod = NULL;
$x_kodList = NULL;
$x_kodChk = NULL;
$cbo_x_kod_js = NULL;
$x_datum = NULL;
$ox_datum = NULL;
$z_datum = NULL;
$ar_x_datum = NULL;
$ari_x_datum = NULL;
$x_datumList = NULL;
$x_datumChk = NULL;
$cbo_x_datum_js = NULL;
$x_hely = NULL;
$ox_hely = NULL;
$z_hely = NULL;
$ar_x_hely = NULL;
$ari_x_hely = NULL;
$x_helyList = NULL;
$x_helyChk = NULL;
$cbo_x_hely_js = NULL;
$x_idopont = NULL;
$ox_idopont = NULL;
$z_idopont = NULL;
$ar_x_idopont = NULL;
$ari_x_idopont = NULL;
$x_idopontList = NULL;
$x_idopontChk = NULL;
$cbo_x_idopont_js = NULL;
$x_lejart = NULL;
$ox_lejart = NULL;
$z_lejart = NULL;
$ar_x_lejart = NULL;
$ari_x_lejart = NULL;
$x_lejartList = NULL;
$x_lejartChk = NULL;
$cbo_x_lejart_js = NULL;
$x_kepek = NULL;
$ox_kepek = NULL;
$z_kepek = NULL;
$ar_x_kepek = NULL;
$ari_x_kepek = NULL;
$x_kepekList = NULL;
$x_kepekChk = NULL;
$cbo_x_kepek_js = NULL;
?>
<?php

// Get key
$x_kod = @$_GET["kod"];
if (($x_kod == "") || (is_null($x_kod))) {
	ob_end_clean();
	header("Location: esemenylist.php");
	exit();
}
if (!is_numeric($x_kod)) {
	ob_end_clean();
	header("Location: esemenylist.php");
	exit();
}

// Get action
$sAction = @$_POST["a_view"];
if (($sAction == "") || ((is_null($sAction)))) {
	$sAction = "I";	// Display record
}

// Open connection to the database
$conn = phpmkr_db_connect(HOST, USER, PASS, DB, PORT);
switch ($sAction)
{
	case "I": // Display record
		if (!LoadData($conn)) { // Load record
			$_SESSION[ewSessionMessage] = "Nem találtam rekordokat";
			phpmkr_db_close($conn);
			ob_end_clean();
			header("Location: esemenylist.php");
			exit();
		}
}
?>
<?php include ("header.php") ?>
<script type="text/javascript">
<!--
EW_LookupFn = "ewlookup.php"; // ewlookup file name
EW_AddOptFn = "ewaddopt.php"; // ewaddopt.php file name
EW_MultiPagePage = "Oldal"; // multi-page Page Text
EW_MultiPageOf = "a(z)"; // multi-page Of Text

//-->
</script>
<script type="text/javascript" src="ewp.js"></script>
<p><span class="phpmaker">Megtekint Tábla: esemeny<br><br>
<a href="esemenylist.php">Vissza a listára</a>&nbsp;
<a href="<?php if ($x_kod <> "") {echo "esemenyedit.php?kod=" . urlencode($x_kod); } else { echo "javascript:alert('Hibás rekord! Kulcs nem lehet üres');";} ?>">Szerkesztés</a>&nbsp;
<a href="<?php if ($x_kod <> "") {echo "esemenyadd.php?kod=" . urlencode($x_kod); } else { echo "javascript:alert('Hibás rekord! Kulcs nem lehet üres');";} ?>">Másol</a>&nbsp;
<a href="<?php if ($x_kod <> "") {echo "esemenydelete.php?kod=" . urlencode($x_kod); } else { echo "javascript:alert('Hibás rekord! Kulcs nem lehet üres');";} ?>">Töröl</a>&nbsp;
</span></p>
<p>
<form>
<table class="ewTable">
	<tr>
		<td class="ewTableHeader"><span>Dátum</span></td>
		<td class="ewTableAltRow"><span>
<?php echo FormatDateTime($x_datum,5); ?>
</span></td>
	</tr>
	<tr>
		<td class="ewTableHeader"><span>Hely</span></td>
		<td class="ewTableAltRow"><span>
<?php echo $x_hely; ?>
</span></td>
	</tr>
	<tr>
		<td class="ewTableHeader"><span>Idopont</span></td>
		<td class="ewTableAltRow"><span>
<?php echo $x_idopont; ?>
</span></td>
	</tr>
	<tr>
		<td class="ewTableHeader"><span>Lejárt</span></td>
		<td class="ewTableAltRow"><span>
<?php
switch ($x_lejart) {
	case "i":
		$sTmp = "igen";
		break;
	case "n":
		$sTmp = "nem";
		break;
	default:
		$sTmp = "";
}
$ox_lejart = $x_lejart; // Backup original value
$x_lejart = $sTmp;
?>
<?php echo $x_lejart; ?>
<?php $x_lejart = $ox_lejart; // Restore original value ?>
</span></td>
	</tr>
	<tr>
		<td class="ewTableHeader"><span>képek mappa</span></td>
		<td class="ewTableAltRow"><span>
<?php echo $x_kepek; ?>
</span></td>
	</tr>
</table>
</form>
<p>
<?php include ("footer.php") ?>
<?php
phpmkr_db_close($conn);
?>
<?php

//-------------------------------------------------------------------------------
// Function LoadData
// - Variables setup: field variables

function LoadData($conn)
{
	global $x_kod;
	$sFilter = ewSqlKeyWhere;
	if (!is_numeric($x_kod)) return false;
	$x_kod =  (get_magic_quotes_gpc()) ? stripslashes($x_kod) : $x_kod;
	$sFilter = str_replace("@kod", AdjustSql($x_kod), $sFilter); // Replace key value
	$sSql = ewBuildSql(ewSqlSelect, ewSqlWhere, ewSqlGroupBy, ewSqlHaving, ewSqlOrderBy, $sFilter, "");
	$rs = phpmkr_query($sSql,$conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSql);
	if (phpmkr_num_rows($rs) == 0) {
		$bLoadData = false;
	} else {
		$bLoadData = true;
		$row = phpmkr_fetch_array($rs);

		// Get the field contents
		$GLOBALS["x_kod"] = $row["kod"];
		$GLOBALS["x_datum"] = $row["datum"];
		$GLOBALS["x_hely"] = $row["hely"];
		$GLOBALS["x_idopont"] = $row["idopont"];
		$GLOBALS["x_lejart"] = $row["lejart"];
		$GLOBALS["x_kepek"] = $row["kepek"];
	}
	phpmkr_free_result($rs);
	return $bLoadData;
}
?>
