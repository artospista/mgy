<?php
	// UTF-8 encoded
	$strings	= array(
		'en'		=> array( // english (english)
			'is_utf8'	=> false,
			'days'		=> array(
				0			=> 'Monday',
				1			=> 'Tuesday',
				2			=> 'Wednesday',
				3			=> 'Thursday',
				4			=> 'Friday',
				5			=> 'Saturday',
				6			=> 'Sunday',
			),
			'months'	=> array(
				1			=> 'January',
				2			=> 'February',
				3			=> 'March',
				4			=> 'April',
				5			=> 'May',
				6			=> 'June',
				7			=> 'July',
				8			=> 'August',
				9			=> 'September',
				10			=> 'October',
				11			=> 'November',
				12			=> 'December',
			),
			'zodiacs'	=> array(
				'aquarius'		=> 'aquarius',
				'aries'			=> 'aries',
				'cancer'		=> 'cancer',
				'capricornus'	=> 'capricorn',
				'gemini'		=> 'gemini',
				'leo'			=> 'leo',
				'libra'			=> 'libra',
				'pisces'		=> 'pisces',
				'sagittarius'	=> 'sagittarius',
				'scorpius'		=> 'scorpion',
				'taurus'		=> 'taurus',
				'virgo'			=> 'virgo',
			),
		),
	);
	$recognize	= array(
		'en'		=> array(
			'is_utf8' => false,
			'patterns'	=> array(
				'#(\d{1,2})/(\d{1,2})/\d{2,4}#'				=> array('m','d','y',),
				'#(\d{1,2})\.(\d{1,2})h?#'					=> array('H','M'),		//19.42(h)
			),
		),
	);
?>