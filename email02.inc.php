<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              K�rd�s mgy-hez" . "\n\n ";
	$eleje_text = $eleje_text . "     Email c�m: " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     K�rd�s: "  . $sz2 . "\n ";
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'mgy - k�rd�s',$message2,'From: kerdes@mgy.hu');
		mail ($emailcc,'mgy - k�rd�s',$message2,'From: kerdes@mgy.hu');		
?>