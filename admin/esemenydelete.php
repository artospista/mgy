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
$arRecKey = NULL;

// Load key parameters
$sKey = "";
$bSingleDelete = true;
$x_kod = @$_GET["kod"];
if (($x_kod == "") || (is_null($x_kod))) {
	$bSingleDelete = false;
} else {
	if ($sKey <> "") $sKey .= ",";
	$sKey .= $x_kod;
	if (!is_numeric($x_kod)) {
		ob_end_clean();
		header("Location: esemenylist.php");
		exit();
	}
}
if (!$bSingleDelete) $sKey = @$_POST["key_d"];
if (!is_array($sKey)) {
 if (strlen($sKey) > 0) $arRecKey = split(",", $sKey);
} else {
 $sKey = implode(",", $sKey);
 $arRecKey = split(",", $sKey);
}
if (count($arRecKey) <= 0) {
	ob_end_clean();
	header("Location: esemenylist.php");
	exit();
}
$sKey = implode(",", $arRecKey);
$i = 0;
$sDbWhere = "";
while ($i < count($arRecKey)) {
	$sDbWhere .= "(";

	// Remove spaces
	$sRecKey = trim($arRecKey[$i+0]);
	$sRecKey = (!get_magic_quotes_gpc()) ? addslashes($sRecKey) : $sRecKey ;

	// Build the SQL
	$sDbWhere .= "`kod`=" . $sRecKey . " AND ";
	if (substr($sDbWhere, -5) == " AND ") { $sDbWhere = substr($sDbWhere, 0, strlen($sDbWhere)-5) . ") OR "; }
	$i += 1;
}
if (substr($sDbWhere, -4) == " OR ") { $sDbWhere = substr($sDbWhere, 0 , strlen($sDbWhere)-4); }

// Get action
$sAction = @$_POST["a_delete"];
if (($sAction == "") || ((is_null($sAction)))) {
	$sAction = "I";	// Display record
}
$conn = phpmkr_db_connect(HOST, USER, PASS, DB, PORT);
switch ($sAction) {
	case "I": // Display
		if (LoadRecordCount($sDbWhere,$conn) <= 0) {
			phpmkr_db_close($conn);
			ob_end_clean();
			header("Location: esemenylist.php");
			exit();
		}
		break;
	case "D": // Delete
		if (DeleteData($sDbWhere,$conn)) {
			$_SESSION[ewSessionMessage] = "Sikeres törlés";
			phpmkr_db_close($conn);
			ob_end_clean();
			header("Location: esemenylist.php");
			exit();
		}
		break;
}
?>
<?php include ("header.php") ?>
<p><span class="phpmaker">Törlés Tábla: esemeny<br><br><a href="esemenylist.php">Vissza a listára</a></span></p>
<form action="esemenydelete.php" method="post">
<p>
<input type="hidden" name="a_delete" value="D">
<?php $sKey = (get_magic_quotes_gpc()) ? stripslashes($sKey) : $sKey; ?>
<input type="hidden" name="key_d" value="<?php echo htmlspecialchars($sKey); ?>">
<table class="ewTable">
	<tr class="ewTableHeader">
		<td valign="top"><span>Dátum</span></td>
		<td valign="top"><span>Hely</span></td>
		<td valign="top"><span>Idopont</span></td>
		<td valign="top"><span>Lejárt</span></td>
		<td valign="top"><span>képek mappa</span></td>
	</tr>
<?php
$nRecCount = 0;
$i = 0;
while ($i < count($arRecKey)) {
	$nRecCount++;

	// Set row color
	$sItemRowClass = " class=\"ewTableRow\"";

	// Display alternate color for rows
	if ($nRecCount % 2 <> 0) {
		$sItemRowClass = " class=\"ewTableAltRow\"";
	}
	$sRecKey = trim($arRecKey[$i+0]);
	$sRecKey = (get_magic_quotes_gpc()) ? stripslashes($sRecKey) : $sRecKey;
	$x_kod = $sRecKey;
	if (!is_numeric($x_kod)) {
		ob_end_clean();
		header("Location: esemenylist.php");
		exit();
	}
	if (LoadData($conn)) {
?>
	<tr<?php echo $sItemRowClass;?>>
		<td><span>
<?php echo FormatDateTime($x_datum,5); ?>
</span></td>
		<td><span>
<?php echo $x_hely; ?>
</span></td>
		<td><span>
<?php echo $x_idopont; ?>
</span></td>
		<td><span>
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
		<td><span>
<?php echo $x_kepek; ?>
</span></td>
	</tr>
<?php
	}
	$i += 1;
}
?>
</table>
<p>
<input type="submit" name="Action" value="Törlés">
</form>
<?php include ("footer.php") ?>
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
<?php

//-------------------------------------------------------------------------------
// Function LoadRecordCount
// - Load Record Count based on input sql criteria sqlKey

function LoadRecordCount($sqlKey, $conn)
{
	global $x_kod;
	$sFilter = $sqlKey;
	$sSql = ewBuildSql(ewSqlSelect, ewSqlWhere, ewSqlGroupBy, ewSqlHaving, ewSqlOrderBy, $sFilter, "");	
	$rs = phpmkr_query($sSql,$conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSql);
	return phpmkr_num_rows($rs);
	phpmkr_free_result($rs);
}

//-------------------------------------------------------------------------------
// Function DeleteData
// - Delete Records based on input sql criteria sqlKey

function DeleteData($sqlKey, $conn)
{
	global $x_kod;
	$sFilter = $sqlKey;

	// Backup the record before delete
	$sSql = ewBuildSql(ewSqlSelect, ewSqlWhere, ewSqlGroupBy, ewSqlHaving, ewSqlOrderBy, $sFilter, "");
	$query = phpmkr_query($sSql,$conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSql);
	while ($temp = phpmkr_fetch_array($query)) {
		$oldrs[] = $temp;
	}

	// Delete
	$sSql = "DELETE FROM `esemeny`";
	$sWhere = "";
	if ($sFilter <> "") {
		if ($sWhere <> "") $sWhere .= " AND ";
		$sWhere .= $sFilter;
	}
	if ($sWhere <> "") {
		$sSql .= " WHERE " . $sWhere;
	}

	// Deleting event
	if (Recordset_Deleting($oldrs)) {
		phpmkr_query($sSql,$conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSql);
		$result = (phpmkr_affected_rows($conn) > 0);

		// Deleted event
		if ($result) Recordset_Deleted($oldrs);
	} else {
		$result = false;
	}
	return $result;
}

// Deleting event
function Recordset_Deleting($oldrs)
{

	// Enter your customized codes here
	return true;
}

// Deleted event
function Recordset_Deleted($oldrs)
{
	$table = "esemeny";
}
?>
