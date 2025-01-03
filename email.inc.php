<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              Jelentkezés hírlevélre" . "\n\n ";
	$eleje_text = $eleje_text . "     Név: " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     Email cím: "  . $sz2 . "\n ";
	$eleje_text = $eleje_text . "     Lakcím: "  . $sz3 . "\n ";
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'mgy - hírlevélre jelentkezés',$message2,'From: hirlevel@mgy.hu');
		mail ($emailcc,'mgy - hírlevélre jelentkezés',$message2,'From: hirlevel@mgy.hu');		

?>
