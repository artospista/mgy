<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              Jelentkez�s h�rlev�lre" . "\n\n ";
	$eleje_text = $eleje_text . "     N�v: " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     Email c�m: "  . $sz2 . "\n ";
	$eleje_text = $eleje_text . "     Lakc�m: "  . $sz3 . "\n ";
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'mgy - h�rlev�lre jelentkez�s',$message2,'From: hirlevel@mgy.hu');
		mail ($emailcc,'mgy - h�rlev�lre jelentkez�s',$message2,'From: hirlevel@mgy.hu');		

?>
