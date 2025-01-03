<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              Kérdés mgy-hez" . "\n\n ";
	$eleje_text = $eleje_text . "     Email cím: " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     Kérdés: "  . $sz2 . "\n ";
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'mgy - kérdés',$message2,'From: kerdes@mgy.hu');
		mail ($emailcc,'mgy - kérdés',$message2,'From: kerdes@mgy.hu');		
?>