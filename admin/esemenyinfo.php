<?php

// PHPMaker 4 configuration
// Table level constants

define("ewTblVar", "esemeny", true);
define("ewTblRecPerPage", "RecPerPage", true);
define("ewSessionTblRecPerPage", "esemeny_RecPerPage", true);
define("ewTblStartRec", "start", true);
define("ewSessionTblStartRec", "esemeny_start", true);
define("ewTblShowMaster", "showmaster", true);
define("ewSessionTblMasterKey", "esemeny_MasterKey", true);
define("ewSessionTblMasterWhere", "esemeny_MasterWhere", true);
define("ewSessionTblDetailWhere", "esemeny_DetailWhere", true);
define("ewSessionTblAdvSrch", "esemeny_AdvSrch", true);
define("ewTblBasicSrch", "psearch", true);
define("ewSessionTblBasicSrch", "esemeny_psearch", true);
define("ewTblBasicSrchType", "psearchtype", true);
define("ewSessionTblBasicSrchType", "esemeny_psearchtype", true);
define("ewSessionTblSearchWhere", "esemeny_SearchWhere", true);
define("ewSessionTblSort", "esemeny_Sort", true);
define("ewSessionTblOrderBy", "esemeny_OrderBy", true);
define("ewSessionTblKey", "esemeny_Key", true);

// Table level SQL
define("ewSqlSelect", "SELECT * FROM `esemeny`", true);
define("ewSqlWhere", "", true);
define("ewSqlGroupBy", "", true);
define("ewSqlHaving", "", true);
define("ewSqlOrderBy", "", true);
define("ewSqlOrderBySessions", "", true);
define("ewSqlKeyWhere", "`kod` = @kod", true);
define("ewSqlUserIDFilter", "", true);
?>
