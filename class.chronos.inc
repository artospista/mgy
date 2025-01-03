<?php
/*
	INDEXING
		Author:		Stefan Rusterholz
		Contact:	stefan@brightlight.ch
		Version:	0.9.2
		Date:		2005-02-23 [1109171542]
		Tabulator:	4 spaces

	ATTENTION:
		This is a pre 1.0 release, this means:
			-some methods might change in v1.0
			-some methods might become replaced by others in v1.0
			-some methods might disappear in v1.0
			-code is not yet thoroughly tested
		Read more in the documentation (section IMMINENT CHANGES).

		Following functionality is missing:
			-chronos is not aware of all daylight saving time exceptions around the world and time
			-chronos is not (yet) aware of leapseconds
			-chronos assumes all dates are gregorian, it doesn't deal in a special way with dates before introduction of the gregorian calendar

		Following methods are non-functional at the moment:
			-difference::create_fromString()
			-location::get_timezoneName($format=false)
			-location::get_offset()
			-location::get_isDST() [will probably be moved to chronos anyway]
			-timespan::count_weeks()
			-chronos::convert_toDatetime()

		Please notify me if you are using this class.

	DOCUMENTATION
		class.chronos.html	is where you want to take a look at.
		class.chronos.documentation	is better if you prefer text-only documentation
		strings	contains all the localization files

	NOTES
		I don't like it if code is cramed with comments. In my oppinion the code
		itself should be as readable as possible (no short variable names, no
		abbreviated function names).
		Therefore the methods are documented externally and comments are only
		supplied where I think it is needed to understand how the code works.

		Comments after '!!!' indicate a code-part that should be improved/changed
	
	LICENSE
		I haven't yet decided under what license I publicate this class.
		If you want to use this class for a non-profit project you may do that.
		But if you use it for a commercial project, then I ask for a donation for my work.
*/

define("YEAR_AVERAGE", 365.2425);	// Average days per year. In 400 years there are 97 leapyears
define("MONTH_AVERAGE", 30.436875);	// Average days per month. YEAR_AVERAGE/12
define("ISO_8601", 'ISO_8601');		// used for definition of weekstart

if (version_compare(phpversion(), '4.3.0') < 0) {
	trigger_error("chronos needs at least php 4.3.0 to work correctly", E_USER_WARNING);
	return false;
}

class cdatetime extends chronos //Bugfix for PHP5.2, NG
{
	var $version	= '0.9.2';

	function cdatetime($datetime=false, $timezoneID=false, $language=false) //Bugfix for PHP5.2, NG
	{
		$this->chronos($timezoneID, $language); // use parents init function
		if ($datetime == 'current') {
			$this->create_fromCurrent();
		} elseif (is_string($datetime)) {
			$this->create_fromString($datetime);
		} elseif (is_numeric($datetime)) {
			$this->create_fromUnixtime($datetime);
		} elseif (is_array($datetime)) {
			$this->create_fromArray($datetime);
		} elseif ($datetime === false) {
			// nothing to do
		} else {
			trigger_error("Invalid set-from '$from'.", E_USER_ERROR);
		}
	}

	/*
		how it works (at the moment):
		-string becomes lowercased
		-we lock on the first language that has a succesful match
		-matched text becomes removed

		how it is planned work (but does not yet):
		-we first lowercase the string
		-we figure out with which patterns it matches
		-we figure out which combination of the matching pattern is best
		-what is best match?
			-> first perfect match (after removing all matched parts there is only space or empty-string)
			-> match with the least characters left after removing matched parts
			-> earlier patterns have higher priority
	*/
	function create_fromString($string, $croak=true)
	{
		$string		= strtolower($string);
		$translate	= array(
			'd'			=> 'day',
			'm'			=> 'month',
			'y'			=> 'year',
			'H'			=> 'hour',
			'M'			=> 'minute',
			'S'			=> 'second',
			'Z'			=> 'timezone',
		);
		$data		= array();
		$languages	= array_merge(array('independent' => 0), $this->language);
		$did_match	= false;
		$lang_checked	= array();
		foreach ($languages as $lang => $priority) {
			$test	= $string;
			if (!isset($this->recognize[$lang]['patterns'])) { continue; }
			$lang_checked[]	= $lang;
			$recognize	= $this->recognize[$lang];
			$patterns	= $this->recognize[$lang]['patterns'];
			foreach ($patterns as $pattern => $use) {
				if (preg_match($pattern, $test, $matches)) {
					echo "using language $lang\n";
					$did_match	= true;
					$test		= str_replace($matches[0], "", $test);
					foreach ($use as $index => $meaning) {
						if (!isset($matches[$index+1]) || $meaning === 0 || $meaning === false) { continue; }

						$realmeaning		= isset($translate[$meaning]) ? $translate[$meaning] : $meaning;
						$data[$realmeaning]	= $matches[$index+1];
					}
				}
			}
			if ($test != $string) { break; }
		}
		if (!$did_match) {
			if ($croak) {
				trigger_error("String '$string' does not represent date or time in any of the languages: ".join(", ", $lang_checked).".", E_USER_WARNING);
			}
			return false;
		}

		$modify		= array('seconds' => 0, 'minutes' => 0, 'hours' => 0, 'days' => 0, 'weeks' => 0, 'months' => 0, 'years' => 0);
		$testModify	= $modify;
		if (isset($data['today']) || isset($data['tomorrow']) || isset($data['yesterday'])) {
			if (isset($data['tomorrow'])) {
				$modify['days']++;
			} elseif (isset($data['yesterday'])) {
				$modify['days']--;
			}
			unset($data['today'], $data['tomorrow'], $data['yesterday']);
			$data['day']	= strftime("%d");
			$data['month']	= strftime("%m");
			$data['year']	= strftime("%Y");
		}
		if (isset($data['now'])) {
			unset($data['now']);
			$data['day']	= isset($data['day']) ? $data['day'] : strftime("%d");
			$data['month']	= isset($data['month']) ? $data['month'] : strftime("%m");
			$data['year']	= isset($data['year']) ? $data['year'] : strftime("%Y");
			$data['hour']	= strftime("%H");
			$data['minute']	= strftime("%M");
			$data['second']	= strftime("%S");
		}
		if (isset($data['T'])) { // month as name
			$length	= strlen($data['T']);
			foreach ($this->strings[$lang]['months'] as $month => $name1) {
				$names	= array($name1);
				if (isset($this->recognize[$lang]['months'][$month])) {
					$names	= array_merge($names, $this->recognize[$lang]['months'][$month]);
				}
				foreach($names as $name) {
					if (strtolower(substr($name, 0, $length)) == $data['T']) {
						$data['month']	= $month;
						unset($data['T']);
						break(2);
					}
				}
			}
		}
		$return	= $this->create_fromArray($data);
		if ($modify != $testModify) {
			$this->do_add($modify);
		}
		return $return;
	}

	function create_fromUnixtime($unixtime)
	{
		$array['year']		= strftime("%Y", $unixtime);
		$array['month']		= strftime("%m", $unixtime);
		$array['day']		= strftime("%d", $unixtime);
		$array['hour']		= strftime("%H", $unixtime);
		$array['minute']	= strftime("%M", $unixtime);
		$array['second']	= strftime("%S", $unixtime);
		$array['milli']		= 0;
		$array['micro']		= 0;
		$this->create_fromArray($array);
	}

	// accepts both, '200501311215' and '2005-01-31 12:15:00'
	function create_fromMySQL($integer)
	{
		if (preg_match("/^(\d{4})-?(\d{2})-?(\d{2}) ?(\d{2}):?(\d{2}):?(\d{2})$/", $integer, $matches)) {
			$convert	= array(
				1	=> 'year',
				2	=> 'month',
				3	=> 'day',
				4	=> 'hour',
				5	=> 'minute',
				6	=> 'second',
			);
			foreach($convert as $from => $to) {
				$array[$to]	= $matches[$from];
			}
			$this->create_fromArray($array);
			$this->set_is(true, true, false);
			return true;
		}
		return false;
	}

	function create_fromCurrent()
	{
		$this->create_fromUnixtime(time());
	}

	/*
		We make an educated guess what defaults to take. Idea is following:
		-if a datepart is supplied we fill in gaps with current date (e.g. month and day are supplied we complement year with current year)
		-if a timepart is supplied we fill in gaps with 0
		-timezone: argument > creation-supplied > default
	*/
	function create_fromArray($array)
	{
		// clear other data
		$this->unset_dateTimeAndDifference();
		$return		= true;
		$has_date	= false;
		$has_time	= false;

		// has date component
		if (isset($array['year']) || isset($array['month']) || isset($array['day']) || isset($array['dayofyear']) || (isset($array['week']) && isset($array['dayofweek']))) {
			$has_date	= true;
		}
		// has time component
		if (isset($array['hour']) || isset($array['minute']) || isset($array['second']) || isset($array['milli']) || isset($array['micro'])) {
			$has_time	= true;
		}
		// set timezone!!!
		//$array['timezone']	= (isset($array['timezone'])) ? $this->get_utc($array['timezone']) : $this->defaults['timezone'];
		//$this->set_timezone($array['timezone']);

		// defaultize date
		foreach (array('year','month','day') as $index) {
			if (!isset($array[$index])) {
				$array[$index]	= $this->defaults[$index][$has_date ? 0 : 1];
			}
		}
		if ($array['year'] < 100 && $array['year'] !== 0) {
			$array['year']	+= ($array['year'] < 38) ? 2000 : 1900;
		}

		// check date-validity
		if ($has_date && (!$this->allowInvalidDate && !checkdate($array['month'], $array['day'], $array['year']))) {
			trigger_error("Invalid date part", E_USER_WARNING);
			foreach (array('day','year','month') as $index) {
				$array[$index]	= $this->defaults[$index][1];
			}
			$return			= false;
			$has_date		= false;
		}

		// defaultize time
		foreach (array('hour','minute','second','milli','micro') as $index) {
			if (!isset($array[$index])) {
				$array[$index]	= $this->defaults[$index][1];
			}
		}

		// check time-validity
		if ($has_time && ($array['hour'] > 23 || $array['minute'] > 59 || $array['second'] > 59 || $array['milli'] > 999 || $array['micro'] > 999)) {
			trigger_error("Invalid time part ({$array['hour']}, {$array['minute']}, {$array['second']}, {$array['milli']}, {$array['micro']})", E_USER_WARNING);
			foreach (array('hour','minute','second','milli','micro') as $index) {
				$array[$index]	= $this->defaults[$index][1];
			}
			$return			= false;
			$has_time		= false;
		}

		if ($has_date) {
			$this->set_year($array['year']);
			$this->set_month($array['month']);
			$this->set_day($array['day']);
		}
		if ($has_time) {
			$this->set_hour($array['hour']);
			$this->set_minute($array['minute']);
			$this->set_second($array['second']);
			$this->set_milli($array['milli']);
			$this->set_micro($array['micro']);
		}

		$this->set_is($has_date, $has_time, false);
		return $return;
	}

	function set_micro($micro)
	{
		$micro	= intval($micro);
		$return	= true;
		if (0 > $micro || $micro > 999) {
			trigger_error("Invalid micro '$micro', must be within 0-999.", E_USER_WARNING);
			$micro	= 0;
			$return	= false;
		}
		$this->time['micro']	= $micro;
		return $return;
	}
	function set_milli($milli)
	{
		$milli	= intval($milli);
		$return	= true;
		if (0 > $milli || $milli > 999) {
			trigger_error("Invalid milli '$milli', must be within 0-999.", E_USER_WARNING);
			$milli	= 0;
			$return	= false;
		}
		$this->time['milli']	= $milli;
		return $return;
	}
	function set_second($second)
	{
		$second	= intval($second);
		$return	= true;
		if (0 > $second || $second > 59) {
			trigger_error("Invalid second '$second', must be within 0-59.", E_USER_WARNING);
			$second	= 0;
			$return	= false;
		}
		$this->time['second']	= $second;
		return $return;
	}
	function set_minute($minute)
	{
		$minute	= intval($minute);
		$return	= true;
		if (0 > $minute || $minute > 59) {
			trigger_error("Invalid minute '$minute', must be within 0-59.", E_USER_WARNING);
			$minute	= 0;
			$return	= false;
		}
		$this->time['minute']	= $minute;
		return $return;
	}
	function set_hour($hour)
	{
		$hour	= intval($hour);
		$return	= true;
		if (0 > $hour || $hour > 23) {
			trigger_error("Invalid hour '$hour', must be within 0-23.", E_USER_WARNING);
			$hour	= 0;
			$return	= false;
		}
		$this->time['hour']	= $hour;
		return $return;
	}
	function set_day($day, $month=false, $year=false)
	{
		$day	= intval($day);
		$month	= ($month === false) ? $this->get_month() : $month;
		$year	= ($year === false) ? $this->get_year() : $year;
		$max	= ($month === false) ? 31 : $this->get_daysOfMonth($month, $year);
		$return	= true;
		if (1 > $day || $day > $max) {
			trigger_error("Invalid day '$day', must be within 1-$max.", E_USER_WARNING);
			$day	= 1;
			$return	= false;
		}
		$this->date['day']	= $day;
		return $return;
	}
	/*
		BOOL	= set_dayOfYear(INT, INT);

	*/
	function set_dayOfYear($dayOfYear, $year=false)
	{
		$dayOfYear	= intval($dayOfYear);
		$year		= ($year === false) ? $this->get_year() : $year;
		$max		= (chronos::is_leapyear($year)) ? 366 : 365;
		$return		= true;
		if (1 > $dayOfYear || $dayOfYear > $max) {
			trigger_error("Invalid dayOfYear '$dayOfYear', must be within 1-$max.", E_USER_WARNING);
			$dayOfYear	= 1;
			$return	= false;
		}
		$month	= $this->get_monthFromYearday($dayOfYear, $year);
		$day	= $this->get_monthDayFromYearday($dayOfYear, $year);
		$this->set_month($month);
		$this->set_day($day, $month, $year);
		return $return;
	}
	function set_month($month)
	{
		$month	= intval($month);
		$return	= true;
		if (1 > $month || $month > 12) {
			trigger_error("Invalid month '$month', must be within 1-12.", E_USER_WARNING);
			$month	= 1;
			$return	= false;
		}
		$this->date['month']	= $month;
		return $return;
	}
	function set_year($year)
	{
		$year	= intval($year);
		$return	= true;
		if (1 > $year || $year > 9999) {
			trigger_error("Invalid year '$year', must be within 1-9999.", E_USER_WARNING);
			$year	= ($year > 9999) ? 9999 : 1;
			$return	= false;
		}
		if ($year < 1850) {
			trigger_error("Be aware that this class handles dates before 1850 as gregorian too, which is not correct.", E_USER_NOTICE);
		}
		$this->date['year']	= $year;
		return $return;
	}

	function setTo_nthDayOfWeek($n=1) // n=1-7
	{ // date set to nth (like 4th for n=4) day of week, time is preserved, negative numbers ...
		$n	= ($n < 0) ? 8+$n : $n; // adjust negative n
		if (1 > $n || $n > 7) { // check parameter
			trigger_error("Invalid day of week $n (only 1-7 or -1 - -7 accepted).", E_USER_WARNING);
			return false;
		}
		$this->do_addDays($n - $this->get_dayOfWeek());
		return true;
	}
	function setTo_nthDayOfMonth($n=1) //n=1-28,29,30,31 (depending on month)
	{ // date set to nth (like 4th for n=4) day of month, time is preserved
		$max	= $this->get_daysOfMonth();
		$n		= ($n < 0) ? $max+$n+1 : $n; // adjust negative n
		if (1 > $n || $n > $max) { // check parameter
			trigger_error("Invalid day of month $n (only 1-$max or -1 - -$max accepted).", E_USER_WARNING);
			return false;
		}
		$this->do_addDays($n - $this->get_dayOfMonth());
		return true;
	}
	function setTo_nthDayOfYear($n=1) // n=1-365,266 (depending on year)
	{ // date set to nth (like 4th for n=4) day of year, time is preserved
		$max	= $this->is_leapyear() ? 366 : 365;
		$n		= ($n < 0) ? $max+$n+1 : $n; // adjust negative n
		if (1 > $n || $n > $max) { // check parameter
			trigger_error("Invalid day of year $n (only 1-$max or -1 - -$max accepted).", E_USER_WARNING);
			return false;
		}
		$this->do_addDays($n - $this->get_dayOfYear());
		return true;
	}
	function setTo_nthWeekOfYear($n=1, $weekday=false) //n=1-52,53 (depending on year)
	{ // date set to a day of nth (like 4th for n=4) week of year, time is preserved [weekday=false -> weekday preserved, weekday=int -> nth-weekday]
		$max		= $this->get_weeksOfYear();
		$n			= ($n < 0) ? $max+$n+1 : $n; // adjust negative n
		$weekday	= ($weekday !== false && $weekday < 0) ? 8+$weekday : $weekday; // adjust negative weekday
		if (1 > $n || $n > $max) { // check parameter
			trigger_error("Invalid week of year $n (only 1-$max or -1 - -$max accepted).", E_USER_WARNING);
			return false;
		}
		if ($weekday !== false && (1 > $weekday || $weekday > 7)) { // check parameter
			trigger_error("Invalid day of week $n (only 1-7 or -1 - -7 accepted).", E_USER_WARNING);
			return false;
		}

		$addDays	= ($n-$this->get_week())*7; // we have 23th week and want 4th -> (4-23 = -17)*7 = -119days
		$this->do_addDays($addDays);
		if ($weekday !== false) {
			$this->setTo_nthDayOfWeek($weekday);
		}
		return true;
	}


	// $location: either array(latitude, longitude) or string(locationname)
	/*
		BOOL = function setTo_sunrise($location=array(0,0))

    	Synopsis:
    		$sunrise	= $today;
    		$sunrise->SetTo_sunrise("Europe/Zurich");
    		echo "In Zurich, sunrise will bi at ".$sunrise->as_string("%H:%M").".\n";
    	Arguments:
    		$location:	-A location object
    					-An array of array([FLOAT]latitude, [FLOAT]longitude)
    					-A string containing a valid locationID
    					Default: if set_location() was used before, it will use
    					internal location, else an error is triggered.
    	Description:
    		Changes time of cdatetime object to the time of sunrise in location $location //Bugfix for PHP5.2, NG
    */
	function setTo_sunrise($location=false)
	{
		$result	= $this->get_sunCalculation($location, 'sunrise');
		$return	=  ($result === array(0,0,0)) ? false : true;
		$this->set_hour($result[0]);
		$this->set_minute($result[1]);
		$this->set_second($result[2]);
		return $return;
	}
	function setTo_sunset($location=false)
	{
		$result	= $this->get_sunCalculation($location, 'sunset');
		$return	=  ($result === array(0,0,0)) ? false : true;
		$this->set_hour($result[0]);
		$this->set_minute($result[1]);
		$this->set_second($result[2]);
		return $return;
	}
	function setTo_morningTwilight($location=false)
	{
		$result	= $this->get_sunCalculation($location, 'morningtwilight');
		$return	=  ($result === array(0,0,0)) ? false : true;
		$this->set_hour($result[0]);
		$this->set_minute($result[1]);
		$this->set_second($result[2]);
		return $return;
	}
	function setTo_eveningTwilight($location=false)
	{
		$result	= $this->get_sunCalculation($location, 'eveningtwilight');
		$return	=  ($result === array(0,0,0)) ? false : true;
		$this->set_hour($result[0]);
		$this->set_minute($result[1]);
		$this->set_second($result[2]);
		return $return;
	}

	// add a difference-object or an array (form: array([seconds => int], [minutes => int], ...))
	function do_add($differenceOrArray)
	{
		// validate input
		if (!is_array($differenceOrArray) && !$this->is_difference($differenceOrArray)) {
			trigger_error("Argument \$differenceOrArray must be an array or a difference-object.", E_USER_WARNING);
			return false;
		}

		// normalize data
		if ($this->is_difference($differenceOrArray)) {
			$array	= $differenceOrArray->as_array('partial');
		} else {
			$array		= $differenceOrArray;
		}
		$setZero	= array('seconds','minutes','hours','days','months','years');
		foreach ($setZero as $index) {
			if (!isset($array[$index])) {
				$array[$index]	= 0;
			}
		}
		if (isset($array['weeks'])) {
			$array['days']	+= $array['weeks']*7;
			unset($array['weeks']);
		}

		// start adding
		$this->do_addSeconds($array['seconds']);
		$this->do_addMinutes($array['minutes']);
		$this->do_addHours($array['hours']);
		// check for addition of date-parts on non-dates
		if (!$this->is_date(false) && ($array['days'] != 0 || $array['months'] != 0 || $array['years'] != 0)) {
			trigger_error("Can't add date-parts to a time-object.", E_USER_WARNING);
		} else {
			$this->do_addDays($array['days']);
			$this->do_addMonths($array['months']);
			$this->do_addYears($array['years']);
		}
		return true;
	}
	function do_addSeconds($seconds)
	{
		if ($seconds < 0) {	return $this->do_subtractSeconds(abs($seconds));	}
		$seconds	+= $this->get_second();
		$this->set_second($seconds % 60);
		if (0 < ($minutes = floor($seconds/60))) {
			$this->do_addMinutes($minutes);
		}
		return true;
	}
	function do_addMinutes($minutes)
	{
		if ($minutes < 0) {	return $this->do_subtractMinutes(abs($minutes));	}
		$minutes	+= $this->get_minute();
		$this->set_minute($minutes % 60);
		if (0 < ($hours = floor($minutes/60))) {
			$this->do_addHours($hours);
		}
		return true;
	}
	function do_addHours($hours)
	{
		if ($hours < 0) { return $this->do_subtractHours(abs($hours));	}
		$hours	+= $this->get_hour();
		$this->set_hour($hours % 24);
		if (0 < ($days = floor($hours/24)) && $this->is_date(false)) {
			$this->do_addDays($days);
		}
		return true;
	}

	function do_addDays($days)
	{
		if (!$this->is_date(false)) { trigger_error("Can't add days to a time-object.", E_USER_WARNING); return false; }
		if ($days < 0) { return $this->do_subtractDays(abs($days));	}
		$year	= $this->get_year();
		$days	+= $this->get_dayOfYear();
		while ($days > 366 || ($days > 365 && !chronos::is_leapyear($year))) { // !!!can we substitute this while with an algorithm of O(1)?
			if (chronos::is_leapyear($year)) {
				$days	-= 366;
			} else {
				$days -= 365;
			}
			$year++;
		}
		$this->set_dayOfYear($days, $year);
		$this->set_year($year);
		return true;
	}
	/* cutOverflow: if false, 31.3. +1month = 1.5., if true: 31.3. +1month = 30.4. */
	function do_addMonths($months, $cutOverflow=false)
	{
		if (!$this->is_date(false)) { trigger_error("Can't add months to a time-object.", E_USER_WARNING); return false; }
		if ($months < 0) { return $this->do_subtractMonths(abs($months));	}
		$months	   += $this->get_month();
		$year		= $this->get_year() + floor(($months-1)/12); //months = 12 => 12. month, not 0. month +1year...
		$months		= (($months-1)%12)+1; // avoid that months 12x % 12 = 0
		//avoid dates like 31.4.xx
		$day		= $this->get_day();
		$monthsDays	= $this->get_daysOfMonth($months, $year);
		if ($day > $monthsDays) { //can't happen in december, therefore for sure no year-overflow
			if ($cutOverflow) {
				$this->set_day($monthsDays);
			} else {
				$months++;
				$this->set_day($day-$monthsDays);
			}
		}
		//end avoid
		$this->set_month($months);
		$this->set_year($year);
		return true;
	}
	function do_addYears($years)
	{
		if (!$this->is_date(false)) { trigger_error("Can't add years to a time-object.", E_USER_WARNING); return false; }
		if ($years < 0) { return $this->do_subtractYears(abs($years));	}
		$years	+= $this->get_year();
		$this->set_year($years);
		return true;
	}

	function do_subtractDatetime($subtrahend)
	{
		$difference['months']	= 0;
		$difference['seconds']	= 0;

// 2005-06-01 - 2004-06-01 => 1y 00m 00d
// 2005-06-01 - 2004-06-02 => 0y 11m 30d

		// skip date part if one of them doesn't have date
		if ($this->is_datetime() && $subtrahend->is_datetime()) {
//			$compare	= $this;
//			$compare->set_year($subtrahend->get_year());
			$difference['months']	+= ($this->get_year() - $subtrahend->get_year())*12;
			$difference['months']	+= ($this->get_month() - $subtrahend->get_month());
			$difference['seconds']	+= ($this->get_day() - $subtrahend->get_day())*86400;
//			if ($compare->is_bigger($subtrahend)) {
//				if ($
//			}
		}
		$difference['seconds']	+= ($this->get_hour() - $subtrahend->get_hour())*3600;
		$difference['seconds']	+= ($this->get_minute() - $subtrahend->get_minute())*60;
		$difference['seconds']	+= ($this->get_second() - $subtrahend->get_second());
//		$this	= new difference('exact', $difference);
		convert_copyChronos( new difference('exact', $difference), $this ); //Bugfix for PHP5, NG
		return true;
	}
	// subtract a difference-object or an array (form: array([seconds => int], [minutes => int], ...))
	function do_subtract($differenceDatetimeOrArray)
	{
		// validate input
		if (!is_array($differenceDatetimeOrArray) && !$this->is_difference($differenceDatetimeOrArray) && !$this->is_dateOrTime($differenceDatetimeOrArray)) {
			trigger_error("Argument \$differenceDatetimeOrArray must be an array, a cdatetime- or a difference-object.", E_USER_WARNING); //Bugfix for PHP5.2, NG
			return false;
		}

		// special handler for subtraction of datetimes
		if ($this->is_dateOrTime($differenceDatetimeOrArray)) {
			return $this->do_subtractDatetime($differenceDatetimeOrArray);
		}

		// normalize data
		if ($this->is_difference($differenceDatetimeOrArray)) {
			$array	= $differenceDatetimeOrArray->as_array('partial');
		} else {
			$array		= $differenceDatetimeOrArray;
		}
		$setZero	= array('seconds','minutes','hours','days','months','years');
		foreach ($setZero as $index) {
			if (!isset($array[$index])) {
				$array[$index]	= 0;
			}
		}
		if (isset($array['weeks'])) {
			$array['days']	+= $array['weeks']*7;
			unset($array['weeks']);
		}

		// start adding
		// check for subtraction of date-parts on non-dates
		if (!$this->is_date(false) && ($array['days'] != 0 || $array['months'] != 0 || $array['years'] != 0)) {
			trigger_error("Can't subtract date-parts from a time-object.", E_USER_WARNING);
		} else {
			$this->do_subtractYears($array['years']);
			$this->do_subtractMonths($array['months']);
			$this->do_subtractDays($array['days']);
		}
		$this->do_subtractHours($array['hours']);
		$this->do_subtractMinutes($array['minutes']);
		$this->do_subtractSeconds($array['seconds']);
		return true;
	}
	function do_subtractSeconds($seconds)
	{
		if ($seconds < 0) {	return $this->do_addSeconds(abs($seconds));	}
		$seconds	= $this->get_second()-$seconds; // 12:30 -10s = 12:20; 12:30 - 40s = 11:50; 12:30 - 90s = 11:00
		$minutes	= floor(abs(($seconds-59)/60));
		$seconds	= 59+(($seconds-59)%60);
		$this->set_second($seconds);
		if ($minutes > 0) {
			return $this->do_subtractMinutes($minutes);
		}
		return true;
	}
	function do_subtractMinutes($minutes)
	{
		if ($minutes < 0) {	return $this->do_addMinutes(abs($minutes));	}
		$minutes	= $this->get_minute()-$minutes;
		$hours		= floor(abs(($minutes-59)/60));
		$minutes	= 59+(($minutes-59)%60);
		$this->set_minute($minutes);
		if ($hours > 0) {
			return $this->do_subtractHours($hours);
		}
		return true;
	}
	function do_subtractHours($hours)
	{
		if ($hours < 0) { return $this->do_addHours(abs($hours));	}
		$hours	= $this->get_hour()-$hours;
		$days	= floor(abs(($hours-23)/24));
		$hours	= 23+(($hours-23)%24);
		$this->set_hour($hours);
		if ($days > 0 && $this->is_date(false)) {
			return $this->do_subtractDays($days);
		}
		return true;
	}
	function do_subtractDays($days)
	{
		if (!$this->is_date(false)) { trigger_error("Can't subtract days from a time-object.", E_USER_WARNING); return false; }
		if ($days < 0) { return $this->do_addDays(abs($days));	}
		$days		= $this->get_dayOfYear()-$days;
		$year		= $this->get_year();
		while ($days < 1) {
			$year--;
			if (chronos::is_leapyear($year)) {
				$days	+= 366;
			} else {
				$days	+= 365;
			}
		}
		$this->set_year($year);
		$this->set_dayOfYear($days, $year);
	}
	/* cutOverflow: if false, 31.5. -1month = 1.5., if true: 31.5. -1month = 30.4. */
	function do_subtractMonths($months, $cutOverflow=false)
	{
		if (!$this->is_date(false)) { trigger_error("Can't subtract months from a time-object.", E_USER_WARNING); return false; }
		if ($months < 0) { return $this->do_addMonths(abs($months));	}
		$months	= $this->get_month()-$months;
		$year	= $this->get_year();
		if ($months > 0) {
		} else {
			$months	= abs($months);
			$year  -= floor($months/12) + 1;
			$months	= 12-((($months-1)%12)+1); // avoid that months 12x % 12 = 0 !!!should be solvable nicer
			$this->set_year($year);
		}
		//avoid dates like 31.4.xx
		$day		= $this->get_day();
		$monthsDays	= $this->get_daysOfMonth($months, $year);
		if ($day > $monthsDays) { //cannot happen in december, therefore for sure no year-overflow
			if ($cutOverflow) {
				$this->set_day($monthsDays);
			} else {
				$months++;
				$this->set_day($day-$monthsDays);
			}
		}
		//end avoid
		$this->set_month($months);
		return true;
	}
	function do_subtractYears($years)
	{
		if (!$this->is_date(false)) { trigger_error("Can't subtract years from a time-object.", E_USER_WARNING); return false; }
		if ($years < 0) { return $this->do_addYears(abs($years));	}
		$years	= $this->get_year()-$years;
		$this->set_year($years);
		return true;
	}

	function get_nthDayOfWeek($n=1) // n=1-7
	{ // returns a cdatetime-object with date set to nth (like 4th for n=4) day of week, time is preserved, negative numbers ... //Bugfix for PHP5.2, NG
		$result	= $this;
		$result->setTo_nthDayOfWeek($n);
		return $result;
	}
	function get_nthDayOfMonth($n=1)
	{ // returns a cdatetime-object with date set to nth (like 4th for n=4) day of month, time is preserved //Bugfix for PHP5.2, NG
		$result	= $this;
		$result->setTo_nthDayOfMonth($n);
		return $result;
	}
	function get_nthDayOfYear($n=1)
	{ // returns a cdatetime-object with date set to nth (like 4th for n=4) day of year, time is preserved //Bugfix for PHP5.2, NG
		$result	= $this;
		$result->setTo_nthDayOfYear($n);
		return $result;
	}
	function get_nthWeekOfYear($n=1, $weekday=false)
	{ // returns a cdatetime-object with date set to first day of nth (like 4th for n=4) week of year, time is preserved //Bugfix for PHP5.2, NG
		$result	= $this;
		$result->setTo_nthWeekOfYear($n, $weekday);
		return $result;
	}

	function get_dayOfWeek($format='integer')
	{
		$year	= $this->get_year();
		$month	= $this->get_month()-2;
		if ($month < 1) {
			$month += 12;
			$year--;
		}
		$day	= $this->get_day();
		$yearU	= floor($year/100);
		$yearL	= $year % 100;

		$dayOfWeek	= ((floor(((26*$month) - 2)/10)) + $day + $yearL + floor($yearL/4) + floor($yearU/4) - (2 * $yearU));
		// at that moment: ($dayOfWeek % 7)+7)%7 => 0 = sunday, 6 = saturday
		// since $dayOfWeek can still be a big negative number we must %7+7 to bring it into the 0-13 range
		// the %7+1 is there to bring it into the 1-7 range

		switch($format) {
			case 'integer':
				$dayOfWeek	= (($dayOfWeek+7-$this->starts['week'])%7+7)%7+1;// rotate index to fit starting day (default: 1=monday, 7=sunday)
				$dayOfWeek	= intval($dayOfWeek);
				break;

			case 'alldigits':
				$dayOfWeek	= (($dayOfWeek+7-$this->starts['week'])%7+7)%7+1;// rotate index to fit starting day (default: 1=monday, 7=sunday)
				break;

			case 'string':
				$dayOfWeek	= (($dayOfWeek+6)%7+7)%7+1; // rotate index: 1 = monday, 7 = sunday
				$dayOfWeek	= $this->get_string('days', $dayOfWeek);
				break;
		}
		return $dayOfWeek;
	}

	function get_dayOfMonth($format='integer')
	{
		return $this->get_day($format);
	}

	function get_dayOfYear($format='integer')
	{
		$month		= $this->get_month();
		$day		= $this->get_day();
		if ($month == 0 || $day == 0) {
			trigger_error("Can't retrieve dayOfYear of a no-date", E_USER_WARNING);
			return 0;
		}
		$leap		= ($month > 2 && $this->is_leapyear()) ? 1 : 0;
		$dayOfYear	= $this->lookups['dayOfYear'][$month] + $day + $leap;

		switch($format) {
			case 'integer':
				// calculate offset if start is different
				$dayOfYear	= intval($dayOfYear);
				break;

			case 'alldigits':
				$dayOfYear	= str_repeat('0', (3-strlen($dayOfYear)))."$dayOfYear";
				break;
		}
		return $dayOfYear;
	}

	//	FLAGS: procedural
	function get_daysOfMonth($month=false, $year=false)
	{
		if (!isset($this)) {
			$month	= ($month === false) ? strftime("%m") : $month;
			$year	= ($year === false) ? strftime("%Y") : $year;
		} else {
			$month	= ($month === false) ? $this->get_month() : $month;
			$year	= ($year === false) ? $this->get_year() : $year;
		}
		$leap	= ($month == 2 && chronos::is_leapyear($year)) ? 1 : 0;
		$days	= $this->lookups['daysOfMonth'][$month]+$leap;
		return $days;
	}

	//	FLAGS: procedural
	function get_weeksOfYear($year=false)
	{
		if (!isset($this)) {
			$year	= ($year === false) ? strftime("%Y") : $year;
		} else {
			$year	= ($year === false) ? $this->get_year() : $year;
		}
		// get current day
		$currentDay		= $this->get_dayOfYear('integer');
		// get first (4th day of the week, per default thursday) in the year (as day of month):
		$year	= $this->get_year()-1;
		$day	= ((702 + $this->starts['week'] + (2 * floor($year/100)) - ($year % 100) - floor(($year % 100)/4) - floor(floor($year/100)/4) - floor(((26*11) - 2)/10)) % 7)+1;

		$days	= (chronos::is_leapyear($year)) ? 366 : 365;
		// count days in ($year-01-$day -4days until $year-12-31) / 7 == 
		// (($year-12-31 - $year-01-01) - $day + 4days) / 7 ==
		// (days of year $year - $day + 4days)
		// but since the week last week must have at least 4 days in this year we have to subtract 4 days again, therefore
		// (days of year $year - $day)
		$weeks	= ceil(($days-$day)/7);
		return $weeks;
	}

	function get_monthFromYearday($day, $year=false)
	{
		if ($year === false) {
			$year	= $this->get_year();
		}
		$lookup		= chronos::is_leapyear($year) ? $this->lookups['dayOfLeapyear'] : $this->lookups['dayOfYear'];
		foreach ($lookup as $month => $days) {
			if ($days >= $day) {
				$month--;
				break;
			}
		}
		return $month;
	}

	function get_monthDayFromYearday($day, $year=false)
	{
		if ($year === false) {
			$year	= $this->get_year();
		}
		$lookup		= chronos::is_leapyear($year) ? $this->lookups['dayOfLeapyear'] : $this->lookups['dayOfYear'];
		$month		= $this->get_monthFromYearday($day, $year);
		$day		-= $lookup[$month];
		return $day;
	}

	function get_date()
	{
		return $this->date;
	}

	function get_time()
	{
		return $this->time;
	}

	function get_datetime()
	{
		$datetime	= array();
		foreach ($this->time as $index => $value) {
			$datetime[$index]	= $value;
		}
		foreach ($this->date as $index => $value) {
			$datetime[$index]	= $value;
		}
		return $datetime;
	}

	function get_year($digits=true, $asInt=false)
	{
		$year	= $this->date['year'];
		if ($year === false) {
			$year = 0;
		} elseif ($year === true) {
			$year = strftime("%Y");
		}
		if (is_numeric($digits)) {
			$year	= substr($year, -$digits);
		}
		if ($asInt) {
			$year	= intval($year);
		}
		return $year;
	}

	function get_month($format='integer')
	{
		$month	= $this->date['month'];
		if ($month === false) {
			if (is_numeric($this->date['week'])) { // use week to calculate month
			} else {
				$month = 1;
			}
		} elseif ($month === true) {
			$month = strftime("%m");
		}
		$month	= intval($month);

		switch($format) {
			case 'integer':
				$month	= intval($month);
				break;

			case 'alldigits':
				$month	= (strlen($month) < 2) ? "0$month" : $month;
				break;

			case 'string':
				$month	= $this->get_string('months',$month);
				break;
		}
		return $month;
	}

	function get_day($format='integer')
	{ // formats: integer, alldigits, string
		$day	= $this->date['day'];
		if ($day === false) {
			$day = 1;
		} elseif ($day === true) {
			$day = strftime("%d");
		}
		switch($format) {
			case 'integer':
				$day	= intval($day);
				break;

			case 'alldigits':
				$day	= (strlen($day) < 2) ? "0$day" : $day;
				break;
		}
		return $day;
	}

	function get_hour($format='integer', $mode=24)
	{ // formats: integer, alldigits, string
		$hour	= $this->time['hour'];
		if ($hour === false) {
			$hour = 1;
		} elseif ($hour === true) {
			$hour = strftime("%H");
		}
		$hour	= intval($hour);
		if ($mode == 12) {
			if ($hour < 12) {
				$hour++;
			} else {
				$hour-=12;
			}
		}
		switch($format) {
			case 'integer':
				$hour	= intval($hour);
				break;

			case 'alldigits':
				$hour	= (strlen($hour) < 2) ? "0$hour" : $hour;
				break;
		}
		return $hour;
	}

	function get_minute($format='integer')
	{ // formats: integer, alldigits, string
		$minute	= $this->time['minute'];
		if ($minute === false) {
			$minute = 1;
		} elseif ($minute === true) {
			$minute = strftime("%M");
		}
		switch($format) {
			case 'integer':
				$minute	= intval($minute);
				break;

			case 'alldigits':
				$minute	= (strlen($minute) < 2) ? "0$minute" : $minute;
				break;
		}
		return $minute;
	}

	function get_second($format='integer')
	{ // formats: integer, alldigits, string
		$second	= $this->time['second'];
		if ($second === false) {
			$second = 1;
		} elseif ($second === true) {
			$second = strftime("%S");
		}
		switch($format) {
			case 'integer':
				$second	= intval($second);
				break;

			case 'alldigits':
				$second	= (strlen($second) < 2) ? "0$second" : $second;
				break;
		}
		return $second;
	}

	function get_milli($format='integer')
	{ // formats: integer, alldigits, string
		$milli	= $this->time['milli'];
		if ($milli === false) {
			$milli = 0;
		} elseif ($milli === true) {
			$milli = 0;
		}
		switch($format) {
			case 'integer':
				$milli	= intval($milli);
				break;

			case 'alldigits':
				$second	= sprintf("%03d", $milli);
				break;
		}
		return $milli;
	}
	function get_micro($format='integer')
	{ // formats: integer, alldigits, string
		$micro	= $this->time['micro'];
		if ($micro === false) {
			$micro = 0;
		} elseif ($micro === true) {
			$micro = 0;
		}
		switch($format) {
			case 'integer':
				$micro	= intval($micro);
				break;

			case 'alldigits':
				$micro	= sprintf("%03d", $micro);
				break;
		}
		return $micro;
	}

	function get_week($format='integer', $method=ISO_8601)
	{
		// get current day
		$currentDay		= $this->get_dayOfYear('integer');
		// get first (4th day of the week, per default thursday) in the year (as day of month):
		$year	= $this->get_year()-1;
		$day	= ((702 + $this->starts['week'] + (2 * floor($year/100)) - ($year % 100) - floor(($year % 100)/4) - floor(floor($year/100)/4) - floor(((26*11) - 2)/10)) % 7)+1;

		if ($currentDay >= $day-3) {
			$week	= floor(($currentDay - $day+3)/7)+1;
		} else {
			$year--;
			$day	= ((702 + $this->starts['week'] + (2 * floor($year/100)) - ($year % 100) - floor(($year % 100)/4) - floor(floor($year/100)/4) - floor(((26*11) - 2)/10)) % 7)+1;
			$yeardays	= chronos::is_leapyear($year+1) ? 366 : 365;
			if ($day == 0) { $day = 7; }
			$week	= floor(($yeardays + $currentDay - $day+3)/7)+1;
		}
		switch($format) {
			case 'integer':
				$week	= intval($week);
				break;

			case 'alldigits':
				$week	= (strlen($week) < 2) ? "0$week" : $week;
				break;
		}
		return $week;
	}

	function get_zodiac()
	{
		$month		= $this->get_month();
		$day		= $this->get_day();
		if (!$month || !$day) {
			return 'error';
		}
		$zodiac	= ($this->zodiacs['by_date'][$month][0] < $day) ? $this->zodiacs['by_date'][$month][1] : $this->zodiacs['by_date'][$month][2];
		return $this->get_string('zodiacs', $zodiac);
	}

	function get_age()
	{
		$compare	= new cdatetime('current', $this->get_timezoneID(), $this->get_language()); //Bugfix for PHP5.2, NG
		$years		= $compare->get_year() - $this->get_year();
		$compare->set_year($this->get_year());
		if ($this->is_bigger($compare)) {
			$years--;
		}
		return $years;
	}

	function as_array()
	{
		$array	= array(
			'micro'		=> $this->time['micro'],
			'milli'		=> $this->time['milli'],
			'second'	=> $this->time['second'],
			'minute'	=> $this->time['minute'],
			'hour'		=> $this->time['hour'],
			'day'		=> $this->date['day'],
			'month'		=> $this->date['month'],
			'year'		=> $this->date['year'],
//			'timezone'	=> $this->
		);
		return $array;
	}

	function as_unixtime()
	{
		if ($this->unixtime === false) {
			$this->unixtime	= mktime($this->get_hour(), $this->get_minute(), $this->get_second(), $this->get_month(), $this->get_day(), $this->get_year());
		}
		return $this->unixtime;
	}

	function as_mysqlDate($asInteger=false)
	{
		if ($asInteger) {
			return intval($this->get_year(4).$this->get_month('alldigits').$this->get_day('alldigits'));
		} else {
			return $this->get_year(4)."-".$this->get_month('alldigits')."-".$this->get_day('alldigits');
		}
	}
	function as_mysqlTime($asInteger=false)
	{
		if ($asInteger) {
			return intval($this->get_hour('alldigits').$this->get_minute('alldigits').$this->get_second('alldigits'));
		} else {
			return $this->get_hour('alldigits').":".$this->get_minute('alldigits').":".$this->get_second('alldigits');
		}
	}
	function as_mysqlDatetime($asInteger=false)
	{
		if ($asInteger) {
			return intval($this->get_year(4).$this->get_month('alldigits').$this->get_day('alldigits').$this->get_hour('alldigits').$this->get_minute('alldigits').$this->get_second('alldigits'));
		} else {
			return $this->get_year(4)."-".$this->get_month('alldigits')."-".$this->get_day('alldigits')." ".$this->get_hour('alldigits').":".$this->get_minute('alldigits').":".$this->get_second('alldigits');
		}
	}

/*
	STRING	= as_string(STRING);
		RETURN:		The string containing the values as given in $pattern
		$pattern:	How the string should be formatted, allowed are the two formats
					%<char>, %{string|modifier|...}. See @chronos::get_stringPart()
					and @chronos:: for more informations about the formatting

		SYNOPSIS:	echo $datetime->as_string("%m/%d/%Y %H.%M");
					--> 11/21/2005 13.45

	Get a formatted string of the datetime, comparable to strftime for unix-timestamps.
	Be aware the the advanced syntax (%{part|modifier|...}) is quite powerful.
*/
	function as_string($pattern=false)
	{
		$replacements	= array();

		preg_match_all("/%{([\w|]+)}/", $pattern, $matches);
		foreach ($matches[1] as $match) {
			$cmd		= split("\|", $match);
			$current	= $this->get_stringPart($cmd[0]);
			if (count($cmd) > 1) {
				array_shift($cmd);
				$current	= $this->get_appliedModificators($current, $cmd);
			}
			$replacements["%\{$match}"]	= $current;
		}
		unset($matches);
		preg_match_all("/%([aAbBcCdDegGhHIjmMnprRStTuUVwWxXyYzZ%])/", $pattern, $matches);
		foreach ($matches[1] as $match) {
			$current	= $this->get_stringPart($match);
			$replacements["%$match"]	= $current;
		}
		foreach ($replacements as $placeholder => $replacement) {
			$pattern	= str_replace($placeholder, $replacement, $pattern);
		}
		return $pattern;
	}
}

/* this class extension only replaces the constructor */
class difference extends chronos
{
	var $version	= '0.9.2';

	function difference($from='nothing', $difference=false, $timezone=false, $language='en')
	{
		$this->chronos($timezone, $language);
		switch($from) {
			case 'string':
				$this->create_fromString($difference);
				break;

			case 'array':
				$this->create_fromArray($difference);
				break;

			case 'exact':
				if (isset($difference['seconds']) && isset($difference['months'])) {
					$seconds	= $difference['seconds'];
					$months		= $difference['months'];
				} elseif (isset($difference[0]) && isset($difference[1])) {
					$seconds	= $difference[0];
					$months		= $difference[1];
				} elseif (is_int($difference)) {
					$seconds	= $difference;
					$months		= 0;
				} else {
					trigger_error("Invalid \$difference argument for creation". E_USER_WARNING);
					break;
				}
				$this->create_fromExact($seconds, $months);
				break;

			case 'nothing':
				//don't do anything

			default:
				if (in_array($from, array('seconds','minutes','hours','days','weeks','months','years'))) {
					$this->create_fromPart($difference, $from);
				} else {
					trigger_error("Invalid \$from '$from'", E_USER_WARNING);
				}
		}
	}

	function create_fromString($string)
	{
		trigger_error("This creation method is currently non-functional.", E_USER_WARNING);

		$string		= strtolower($string);
		$data		= array();
		$languages	= array_merge(array('independent' => 0), $this->language);
		foreach ($languages as $lang => $priority) {
			$test	= $string;
			if (!isset($this->recognize[$lang]['patterns'])) { continue; }
			$recognize	= $this->recognize[$lang];
			$patterns	= $this->recognize[$lang]['patterns'];
			foreach ($patterns as $pattern => $use) {
				if (preg_match($pattern, $test, $matches)) {
					$test	= str_replace($matches[0], "", $test);
					foreach ($use as $index => $meaning) {
						if (!isset($matches[$index+1]) || $meaning === 0 || $meaning === false) { continue; }

						$realmeaning		= isset($translate[$meaning]) ? $translate[$meaning] : $meaning;
						$data[$realmeaning]	= $matches[$index+1];
					}
				}
			}
			if ($test != $string) { break; }
		}
		$return	= $this->create_fromArray($data);
		return $return;
	}
	function create_fromPart($amount, $part='seconds')
	{
		$this->create_fromArray(array($part => $amount));
	}
	function create_fromDatetimes($datetime1, $datetime2)
	{
		if ($datetime1->do_subtractDatetime($datetime2)) {
//			$this	= $datetime1;
			convert_copyChronos( $datetime1, $this ); //Bugfix for PHP5, NG
		} else {
			trigger_error("Creation of difference failed.", E_USER_NOTICE);
		}
	}
	function create_fromArray($array)
	{
		$this->unset_dateTimeAndDifference();
		$this->set_is(false, false, true);

		// handle overflows
		$array	= $this->get_withoutOverflow($array);

		// ...
		foreach ($array as $key => $value) {
			$this->difference['partial'][$key]	= $value;
			foreach ($this->multipliers as $addTo => $multiply) {
				$this->difference['absolute'][$addTo]	+= $value*$multiply[$key];
			}
		}
		$d	= $this->difference['partial'];
		$this->difference['exact']['seconds']	= $d['seconds']+($d['minutes']*60)+($d['hours']*3600)+($d['days']*86400)+($d['weeks']*604800);
		$this->difference['exact']['months']	= $d['months']+($d['years']*12);
	}

	function create_fromExact($seconds=0, $months=0)
	{
		$this->unset_dateTimeAndDifference();
		$this->set_is(false, false, true);

		$this->difference['exact']['seconds']	= $seconds;
		$this->difference['exact']['months']	= $months;

		// handle overflows
		$array	= array('seconds' => $seconds, 'months' => $months);
		$array	= $this->get_withoutOverflow($array);

		foreach ($array as $key => $value) {
			if (isset($this->overflow[$key]) && $value > $this->overflow[$key][0]) {
				if (!isset($array[$this->overflow[$key][1]])) {
					$array[$this->overflow[$key][1]]	= 0;
				}
				$preserve	= floor($value/$this->overflow[$key][0]);
				$value		= $value % $this->overflow[$key][0];
				$array[$this->overflow[$key][1]]   += $preserve;
				$array[$key]						= $value;
			}
		}
		foreach ($array as $key => $value) {
			$this->difference['partial'][$key]	= $value;
			foreach ($this->multipliers as $addTo => $multiply) {
				$this->difference['absolute'][$addTo]	+= $value*$multiply[$key];
			}
		}
	}

	function do_add($differenceDatetimeOrArray)
	{
		// validate input
		if (!is_array($differenceDatetimeOrArray) && !$this->is_difference($differenceDatetimeOrArray) && !$this->is_dateOrTime($differenceDatetimeOrArray)) {
			trigger_error("Argument \$differenceDatetimeOrArray must be an array, a cdatetime- or a difference-object.", E_USER_WARNING); //Bugfix for PHP5.2, NG
			return false;
		}

		// special handler for addition of datetimes
		if ($this->is_dateOrTime($differenceDatetimeOrArray)) {
			$add	= $this;
//			$this	= $differenceDatetimeOrArray;
			convert_copyChronos( $differenceDatetimeOrArray, $this ); //Bugfix for PHP5, NG
			unset($differenceDatetimeOrArray);
			return $this->do_add($add);
		}

		// normalize data
		if ($this->is_difference($differenceDatetimeOrArray)) {
			$array	= $differenceDatetimeOrArray->as_array('exact');
		} else {
			$array	= $differenceDatetimeOrArray;
		}
		$setZero	= array('seconds','months');
		foreach ($setZero as $index) {
			if (!isset($array[$index])) {
				$array[$index]	= 0;
			}
		}

		// add data
		$array['seconds']  += $this->difference['exact']['seconds'];
		$array['months']   += $this->difference['exact']['months'];
		$this->create_fromExact($array['seconds'], $array['months']);
		return true;
	}

	function do_subtract($differenceOrArray)
	{
		// validate input
		if (!is_array($differenceOrArray) && !$this->is_difference($differenceOrArray)) {
			trigger_error("Argument \$differenceOrArray must be an array or a difference-object.", E_USER_WARNING);
			return false;
		}

		// normalize data
		if ($this->is_difference($differenceOrArray)) {
			$array	= $differenceOrArray->as_array('exact');
		} else {
			$array		= $differenceOrArray;
		}
		$setZero	= array('seconds','months');
		foreach ($setZero as $index) {
			if (!isset($array[$index])) {
				$array[$index]	= 0;
			}
		}

		//start adding
		$array['seconds']  -= $this->difference['exact']['seconds'];
		$array['months']   -= $this->difference['exact']['months'];
		$this->create_fromExact($array['seconds'], $array['months']);
		return true;
	}

	function get_seconds($part='partial')
	{
		if (!in_array($part, array('absolute','partial','exact'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		return $this->difference[$part]['seconds'];
	}

	function get_minutes($part='partial')
	{
		if (!in_array($part, array('absolute','partial'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		return $this->difference[$part]['minutes'];
	}

	function get_hours($part='partial')
	{
		if (!in_array($part, array('absolute','partial'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		return $this->difference[$part]['hours'];
	}

	function get_days($part='partial')
	{
		if (!in_array($part, array('absolute','partial'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		return $this->difference[$part]['days'];
	}

	function get_weeks($part='partial')
	{
		if (!in_array($part, array('absolute','partial'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		if ($part == 'absolute') {
			return $this->difference['absolute']['days']/7;
		} else {
			return floor($this->difference['partial']['days']/7);
		}
	}

	function get_months($part='partial')
	{
		if (!in_array($part, array('absolute','partial','exact'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		return $this->difference[$part]['months'];
	}

	function get_years($part='partial')
	{
		if (!in_array($part, array('absolute','partial'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		return $this->difference[$part]['years'];
	}

	function as_array($part)
	{
		if (!in_array($part, array('absolute','partial','exact'))) {
			trigger_error("Invalid \$part '$part'.", E_USER_WARNING);
			return 0;
		}
		return $this->difference[$part];
	}

	function as_string($pattern=false)
	{
		$replacements	= array();

		preg_match_all("/%{([\w|]+)}/", $pattern, $matches);
		foreach ($matches[1] as $match) {
			$cmd		= split("\|", $match);
			$current	= $this->get_stringPart($cmd[0]);
			if (count($cmd) > 1) {
				array_shift($cmd);
				$current	= $this->get_appliedModificators($current, $cmd);
			}
			$replacements["%\{$match}"]	= $current;
		}
		unset($matches);
		preg_match_all("/%([aAbBcCdDegGhHIjmMnprRStTuUVwWxXyYzZ%])/", $pattern, $matches);
		foreach ($matches[1] as $match) {
			$current	= $this->get_stringPart($match);
			$replacements["%$match"]	= $current;
		}
		foreach ($replacements as $placeholder => $replacement) {
			$pattern	= str_replace($placeholder, $replacement, $pattern);
		}
		return $pattern;
	}
}


/*
	Timespan can handle all kinds of timespans:
	- start-dateAndOrtime to end-dateAndOrtime
	- difference to end-dateAndOrtime (start-dateAndOrtime becomes calculated - start+diff=end)
	- start-dateAndOrtime to difference (end-dateAndOrtime becomes calculated - start+diff=end)
*/
class timespan
{
	var $version	= '0.9.2';

	var $start		= false;
	var $end		= false;
	var $difference	= false;
	
	// PRIVATE!
	var $compare	= array( // we use this to check if one of the objects has changed, which would mean we need to adapt the others to it
		'start'			=> false,
		'end'			=> false,
		'difference'	=> false,
	);

	function timespan($start=false, $end=false, $timezoneID=false, $language=false)
	{
		foreach (array('start','end') as $varname) {
			if ($$varname === false) {
				$$varname	= new cdatetime('current', $timezoneID, $language); //Bugfix for PHP5.2, NG
			} elseif (is_string($$varname)) {
				$$varname	= new cdatetime($$varname, $timezoneID, $language); //Bugfix for PHP5.2, NG
			} elseif (is_array($$varname)) {
				$$varname	= new cdatetime($$varname, $timezoneID, $language); //Bugfix for PHP5.2, NG
			} elseif (is_object($$varname)) {
				// verify object type
			}
		}
		if ($start->is_difference() && $end->is_dateOrTime()) {
			$difference	= $start;
			$start		= $end;
			if ($end->is_time()) {
				$difference->unset_differenceDate();
			}
			$start->do_subtract($difference);
		} elseif ($start->is_dateOrTime() && $end->is_difference()) {
			$difference	= $end;
			$end		= $start;
			if ($start->is_time()) {
				$difference->unset_differenceDate();
			}
			$end->do_add($difference);
		} elseif ($start->is_dateOrTime() && $end->is_dateOrTime()) {
			if (($start->is_date() && $end->is_date()) || ($start->is_time() && $end->is_time()) || ($start->is_datetime() && $end->is_datetime())) {
				if ($start->is_bigger($end)) {
					list($start, $end) = array($end, $start);
				}
				$difference	= $end;
				$end->do_subtractDatetime($start);
			} else {
				trigger_error("Cannot create a timespan", E_USER_WARNING);
			}
		}
		$this->start		= $start;
		$this->end			= $end;
		$this->difference	= $difference;
		$this->compare		= array(
			'start'				=> $start,
			'end'				=> $end,
			'difference'		=> $difference,
		);
	}
	
	// checks if an object has changed and adapts the others to those changes
	function do_synchronize()
	{
		$changes['start']		= ($this->start !== $this->compare['start']);
		$changes['end']			= ($this->end !== $this->compare['end']);
		$changes['difference']	= ($this->difference !== $this->compare['difference']);
		
		// check for irreparable asynchronity (more then one changed object)
		if (($changes['start'] && $changes['end']) || ($changes['end'] && $changes['difference']) || ($changes['start'] && $changes['difference'])) {
			trigger_error("Irreparable asynchronity, you need to synchronize after every change of one", E_USER_ERROR);
		}
		// check for irrelevance of synchronization
		if (!$changes['start'] && !$changes['end'] && !$changes['difference']) {
			return true;
		}
		if ($changes['difference']) {
			$this->do_synchronizeDifference();
		} elseif ($changes['start']) {
			$this->do_synchronizeStart();
		} elseif ($changes['end']) {
			$this->do_synchronizeEnd();
		}
	}
	function do_synchronizeDifference()
	{
		if ($start->is_bigger($end)) {
			list($start, $end) = array($end, $start);
		}
		$difference	= $end;
		$end->do_subtractDatetime($start);
	}
	function do_synchronizeStart()
	{
		$this->start		= $this->end;
		if ($this->end->is_time()) {
			$this->difference->unset_differenceDate();
		}
		$this->start->do_subtract($this->difference);
	}
	function do_synchronizeEnd()
	{
		$this->end		= $this->start;
		if ($this->start->is_time()) {
			$this->difference->unset_differenceDate();
		}
		$this->end->do_add($this->difference);
	}

	// how many times is $day (1-7 or localized name) in timespan?
	function count_weekdayOccurrences($day)
	{
		
		$day	= is_numeric($day) ? intval($day) : $start->get_dayFromName($day);
		if (1 > $day || $day > 7) {
			trigger_error("Invalid day '$day'", E_USER_WARNING);
			return 0;
		}
		$this->do_synchronize();

		$days		= $this->difference->get_days('partial');
		$startDay	= $this->start->get_dayOfWeek();
		$endDay		= $this->end->get_dayOfWeek();
		
		// [(deltaDays - daysToNext $day from start - daysToLast $day from end)/7+1]
		$effective	= ($days - (($startDay-7-$day)%7) - (($day-7-$endDay)%7));
		if ($effective % 7 != 0) {
			trigger_error("Error while calculating weekdayOccurrences, please report this error!", E_USER_WARNING);
			return 0;
		}
		return (($effective/7)+1);
	}

	// how many times is $month (1-12 or localized name) in timespan?
	function count_monthOccurrences($month)
	{
		$day	= is_numeric($day) ? intval($day) : $start->get_MonthFromName($day);
		if (0 > $day || $day > 6) {
			trigger_error("Invalid day '$day'", E_USER_WARNING);
			return 0;
		}
		$this->do_synchronize();

		$months		= $this->difference->get_months('partial');
		$startMonth	= $this->start->get_month();
		$endMonth	= $this->end->get_month();
		
		// [(deltaMonths - monthsToNext $month from start - monthsToLast $month from end)/12+1]
		$effective	= ($months - (($startMonth-12-$month)%12) - (($month-12-$endMonth)%12));
		if ($effective % 12 != 0) {
			trigger_error("Error while calculating monthOccurrences, please report this error!", E_USER_WARNING);
			return 0;
		}
		return (($effective/12)+1);
	}

	// modes: 0 = at least 4 days of a week, 1 = how many complete weeks, 2 = how many weeks even if only 1 day of the week, 3 = a simple floor(days/7), 4 a simple ceil(days/7)
	function count_weeks($mode=0)
	{
		$mode	= intval($mode);
		if (0 > $mode || $mode > 4) {
			trigger_error("Invalid mode '$mode'", E_USER_WARNING);
			return 0;
		}
		$this->do_synchronize();
	}
}


class location
{
	var $version	= '0.9.2';

	var $location	= array(
		"timezone_id"	=> 'custom',
		"language"		=> 'en',
		"utc"			=> 'UTC',
		"DST_rule"		=> 'NONE',
		"numeric"		=> '000',
		"alpha2"		=> '--',
		"alpha3"		=> '---',
		"country"		=> 'custom',
		"latitude"		=> '0',
		"longitude"		=> '0',
		"latitude_iso"	=> '+00000',
		"longitude_iso"	=> '+00000',
	);
	var $locations	= array();
	var $zonemap	= array( // map old timezone names to UTC
	//  timezone=> array(corresponding utc, isDST[BOOL]),
		'YANKEE'	=> array('UTC-12',	false),
		'XRAY'		=> array('UTC-11',	false),
		'XRAY'		=> array('UTC-11',	false),
		'HST'		=> array('UTC-10',	false),
		'WHISKY'	=> array('UTC-10',	false),
		'AKST'		=> array('UTC-9',	false),
		'AKDT'		=> array('UTC-9',	true),
		'YDT'		=> array('UTC-9',	true),
		'VICTOR'	=> array('UTC-9',	false),
		'PST'		=> array('UTC-8',	false),
		'PDT'		=> array('UTC-8',	true),
		'UNIFORM'	=> array('UTC-8',	false),
		'MST'		=> array('UTC-7',	false),
		'MDT'		=> array('UTC-7',	true),
		'TANGO'		=> array('UTC-7',	false),
		'CST'		=> array('UTC-6',	false),
		'CDT'		=> array('UTC-6',	true),
		'SIERRA'	=> array('UTC-6',	false),
		'EST'		=> array('UTC-5',	false),
		'EDT'		=> array('UTC-5',	true),
		'ROMEO'		=> array('UTC-5',	false),
		'AST'		=> array('UTC-4',	false),
		'ADT'		=> array('UTC-4',	true),
		'QUEBEC'	=> array('UTC-4',	false),
		'NST'		=> array('UTC-3:30',false),
		'NDT'		=> array('UTC-3:30',true),
		'PAPA'		=> array('UTC-3',	false),
		'OSCAR'		=> array('UTC-2',	false),
		'NOVEMBER'	=> array('UTC-1',	false),
		'GMT'		=> array('UTC',		false),
		'WET'		=> array('UTC',		false),
		'ZULU'		=> array('UTC',		false),
		'CET'		=> array('UTC+1',	false),
		'CEST'		=> array('UTC+1',	true),
		'ALPHA'		=> array('UTC+1',	false),
		'BRAVO'		=> array('UTC+2',	false),
		'MSK'		=> array('UTC+3',	false),
		'CHARLIE'	=> array('UTC+3',	false),
		'DELTA'		=> array('UTC+4',	false),
		'ECHO'		=> array('UTC+5',	false),
		'IST'		=> array('UTC+5:30',false),
		'FOXTROT'	=> array('UTC+6',	false),
		'GOLF'		=> array('UTC+7',	false),
		'AWST'		=> array('UTC+8',	false),
		'HOTEL'		=> array('UTC+8',	false),
		'INDIA'		=> array('UTC+9',	false),
		'ACST'		=> array('UTC+9:30',false),
		'AEST'		=> array('UTC+10',	false),
		'KILO'		=> array('UTC+10',	false),
		'LIMA'		=> array('UTC+11',	false),
		'MIKE'		=> array('UTC+12',	false),
	);
	var $timezones	= array( // all the UTC timezones, offset in seconds
		'UTC-12'	=> -43200,
		'UTC-11'	=> -39600,
		'UTC-10'	=> -36000,
		'UTC-9:30'	=> -34200,
		'UTC-9'		=> -32400,
		'UTC-8'		=> -28800,
		'UTC-7'		=> -25200,
		'UTC-6'		=> -21600,
		'UTC-5'		=> -18000,
		'UTC-4'		=> -14400,
		'UTC-3:30'	=> -12600,
		'UTC-3'		=> -10800,
		'UTC-2'		=>  -7200,
		'UTC-1'		=>  -3600,
		'UTC'		=>      0,
		'UTC+1'		=>   3600,
		'UTC+2'		=>   7200,
		'UTC+3'		=>  10800,
		'UTC+3:07'	=>  11224,
		'UTC+3:30'	=>  12600,
		'UTC+4'		=>  14400,
		'UTC+4:30'	=>  16200,
		'UTC+5'		=>  18000,
		'UTC+5:30'	=>  19800,
		'UTC+5:45'	=>  20700,
		'UTC+6'		=>  21600,
		'UTC+6:30'	=>  23400,
		'UTC+7'		=>  25200,
		'UTC+8'		=>  28800,
		'UTC+8:45'	=>  31500,
		'UTC+9'		=>  32400,
		'UTC+9:30'	=>  34200,
		'UTC+10'	=>  36000,
		'UTC+10:30'	=>  37800,
		'UTC+11'	=>  39600,
		'UTC+11:30'	=>  41400,
		'UTC+12'	=>  43200,
		'UTC+12:45'	=>  45900,
		'UTC+13'	=>  46800,
		'UTC+14'	=>  50400,
	);

	function location($location=false)
	{
		$this->do_readData();
		if (is_array($location)) {
			$this->set_pseudoLocation($location);
		} elseif ($location !== false) {
			$this->set_location($location);
		}
	}

	function set_location($location)
	{
		if (isset($this->zonemap[$location])) {
			$location	= $this->zonemap[$location];
		}
		if (!isset($this->locations[$location])) {
			trigger_error("Unknown location '$location'", E_USER_WARNING);
			return false;
		}
		$this->location	= $this->locations[$location];
		return true;
	}
	function set_pseudoLocation($data)
	{
		$defaults	= array(
			"timezone_id"	=> 'custom',
			"language"		=> 'en',
			"utc"			=> 'UTC',
			"DST_rule"		=> 'NONE',
			"numeric"		=> '000',
			"alpha2"		=> '--',
			"alpha3"		=> '---',
			"country"		=> 'custom',
			"latitude"		=> '0',
			"longitude"		=> '0',
			"latitude_iso"	=> '+00000',
			"longitude_iso"	=> '+00000',
		);
		foreach ($defaults as $key => $default) {
			if (isset($data[$key])) {
				$this->defaults[$key]	= $data[$key];
			}
		}
		$this->location	= $defaults;
	}
	function set_language($lang)
	{
		$this->location['language']	= $lang;
	}

	function do_readData($file=false)
	{
		$file	= file("strings/data.locations.tab", true); //Bugfix for finding file, NG
		unset($file[0]);
		$keys	= array("timezone_id", "language", "utc", "DST_rule", "numeric", "alpha2", "alpha3", "country",	"latitude", "longitude", "latitude_iso", "longitude_iso");
		$ckeys	= count($keys);
		foreach ($file as $ln => $line) {
			$data	= split("\t", $line);
			$hash	= array();
			if ($ckeys != count($data)) {
				trigger_error("Erroneous line $ln: $line", E_USER_WARNING);
				continue;
			}
			foreach ($keys as $index => $key) {
				$hash[$key]	= $data[$index];
			}
			$this->locations[$data[0]]	= $hash;
		}
	}

	function is_validID($timezoneID)
	{
		return (isset($this->locations[$timezoneID]));
	}

	function get_language()
	{
		return $this->location['language'];
	}

	function get_utc()
	{
		return $this->location['utc'];
	}

	// !!! not fully implemented
	function get_timezoneName($format=false)
	{
	}

	function get_countryAlpha2()
	{
		return $this->location['alpha2'];
	}

	function get_countryAlpha3()
	{
		return $this->location['alpha3'];
	}

	function get_numeric()
	{
		return $this->location['numeric'];
	}

	function get_timezoneID()
	{
		return $this->location['timezone_id'];
	}

	function get_rawOffset()
	{
		return $this->timezones[$this->location['utc']];
	}

	// !!! not fully implemented
	function get_offset($atDatetime=null)
	{
		if ($atDatetime === null) {
			return $this->get_rawOffset();
		} elseif ($atDatetime === false) {
			//$atDatetime	= new cdatetime('current', $this->get_timezoneID(), $this->get_language()); //Bugfix for PHP5.2, NG
		}
	}

	function get_latitude($format='float')
	{
		if ($format == 'float') {
			return $this->location['latitude'];
		} else {
			return $this->location['latitude_iso'];
		}
	}

	function get_longitude($format='float')
	{
		if ($format == 'float') {
			return $this->location['longitude'];
		} else {
			return $this->location['longitude_iso'];
		}
	}

	// !!! not fully implemented
	function get_isDST($atDatetime)
	{
	}

	function get_DSTrule()
	{
		return $this->location['DST_rule'];
	}


}

class chronos
{
	var $version	= '0.9.2';

	var $useDST				= true;		// if useDST a time in a timezone within a date where DST is active will become alterated on output by 1h
	var $autoDST			= false;	// as long as we can't get DST automatically correctly we disable autoDST
	var $allowInvalidDate	= false;
	var $stringsDirectory	= 'strings';
	var $current			= array();
	var $language	= array(
		'en' => 1,
		'de' => 2,
		'fr' => 3,
		'it' => 4,
		'es' => 5,
		'pt' => 6,
	);
	var $is	= array(
		'date'			=> false,
		'time'			=> false,
		'difference'	=> false,
	);
	var $starts	= array(
		'year'		=> array(
			'month'		=> 1, // months normally start with day 1...
			'week'		=> 1, // days: 1-7 while 1 == monday
			'day'		=> 1,
		),
		'week'		=> 1, // week starts with this day, days: 1-7 while 1 == monday
	);
	var $defaults	= array(
		'year'			=> true,	// true: insert current, false: insert 0, integer: use value
		'month'			=> 1,		// true: insert current, false: insert 1, integer: use value
		'day'			=> 1,		// true: insert current, false: insert 1, integer: use value
		'week'			=> 1,		// true: insert current, false: insert 1, integer: use value
		'weekday'		=> 0,		// true: insert current, false: insert 0, integer: use value
		'timezone'		=> true,	// true: insert current, false: insert UTC, string: use value
		'hour'			=> 0,		// true: insert current, false: insert 0, integer: use value
		'minute'		=> 0,		// true: insert current, false: insert 0, integer: use value
		'second'		=> 0,		// true: insert current, false: insert 0, integer: use value
		'milli'			=> 0,		// true: insert current, false: insert 0, integer: use value
		'micro'			=> 0,		// true: insert current, false: insert 0, integer: use value
	);
	var $difference = array(
		'absolute'		=> array( // each value represents the complete difference
			'seconds'	=> 0,
			'minutes'	=> 0,
			'hours'		=> 0,
			'days'		=> 0,
			'weeks'		=> 0,
			'months'	=> 0, // 1month = MONTH_AVERAGE
			'years'		=> 0, // 1year = YEAR_AVERAGE
		),
		'partial'	=> array( // each value represents a part of the difference
			'seconds'	=> 0,
			'minutes'	=> 0,
			'hours'		=> 0,
			'days'		=> 0,
			'weeks'		=> 0,
			'months'	=> 0,
			'years'		=> 0,
		),
		'exact'		=> array( // the exact amount
			'seconds'	=> 0,
			'months'	=> 0,
		),
	);
	// true: current, false: start-date/time, integer/string: use value
	var $date		= array(
		'year'			=> 0,
		'month'			=> 0,
		'day'			=> 0,
		'week'			=> 0,
		'weekday'		=> 0,
	);
	var $time		= array(
		'hour'			=> 0,
		'minute'		=> 0,
		'second'		=> 0,
		'milli'			=> 0,
		'micro'			=> 0,
	);
	var $strings	= array();
	var	$recognize	= array(
		'independent'	=> array(
			// y = year, m = month, d = day, H = Hour, M = Minute, S = Second, O = timezone-offset, Z = Timezone
			'patterns'		=> array(
				// ISO
				// RFC
				'#(\d{4})-(\d{2})-(\d{2})T(\d{2}):(\d{2}):(\d{2})([+-]\d{2}:\d{2})#'	=> array('y','m','d','H','M','S','O'),	//2004-02-12T15:19:21+00:00
//				'#(\d{2}|\d{4})-(\d{1,2})-(\d{1,2})#'									=> array('y','m','d'),	//(19)82-5-23 MySQL
//				'#(\d{1,2}):(\d{1,2}):?(\d{1,2})?#'										=> array('H','M','S'),	//19:42(:59) Standard Time
				'#^(\d{14})$#'															=> array('mysqlstamp'),	//A mysql timestamp
				'#^(\+?\-?\d{1,10})$#'													=> array('unixtime'),	//A unix timestamp
			),
		),
	);
	var $timezones	= array( // all the UTC timezones, offset in seconds
		'UTC-12'	=> -43200,
		'UTC-11'	=> -39600,
		'UTC-10'	=> -36000,
		'UTC-9:30'	=> -34200,
		'UTC-9'		=> -32400,
		'UTC-8'		=> -28800,
		'UTC-7'		=> -25200,
		'UTC-6'		=> -21600,
		'UTC-5'		=> -18000,
		'UTC-4'		=> -14400,
		'UTC-3:30'	=> -12600,
		'UTC-3'		=> -10800,
		'UTC-2'		=>  -7200,
		'UTC-1'		=>  -3600,
		'UTC'		=>      0,
		'UTC+1'		=>   3600,
		'UTC+2'		=>   7200,
		'UTC+3'		=>  10800,
		'UTC+3:07'	=>  11224,
		'UTC+3:30'	=>  12600,
		'UTC+4'		=>  14400,
		'UTC+4:30'	=>  16200,
		'UTC+5'		=>  18000,
		'UTC+5:30'	=>  19800,
		'UTC+5:45'	=>  20700,
		'UTC+6'		=>  21600,
		'UTC+6:30'	=>  23400,
		'UTC+7'		=>  25200,
		'UTC+8'		=>  28800,
		'UTC+8:45'	=>  31500,
		'UTC+9'		=>  32400,
		'UTC+9:30'	=>  34200,
		'UTC+10'	=>  36000,
		'UTC+10:30'	=>  37800,
		'UTC+11'	=>  39600,
		'UTC+11:30'	=>  41400,
		'UTC+12'	=>  43200,
		'UTC+12:45'	=>  45900,
		'UTC+13'	=>  46800,
		'UTC+14'	=>  50400,
	);
	var $lookups	= array(
		'dayOfYear'		=> array(
			1	=>   0,
			2	=>  31, //+31
			3	=>  59, //+28 (is_leapyear() => +1)
			4	=>  90, //+31
			5	=> 120, //+30
			6	=> 151, //+31
			7	=> 181, //+30
			8	=> 212, //+31
			9	=> 243, //+31
			10	=> 273, //+30
			11	=> 304, //+31
			12	=> 334, //+30
		),
		'dayOfLeapyear'		=> array(
			1	=>   0,
			2	=>  31, //+31
			3	=>  60, //+28 (is_leapyear() => +1)
			4	=>  91, //+31
			5	=> 121, //+30
			6	=> 152, //+31
			7	=> 182, //+30
			8	=> 213, //+31
			9	=> 244, //+31
			10	=> 274, //+30
			11	=> 305, //+31
			12	=> 335, //+30
		),
		'daysOfMonth'	=> array(
			1	=> 31,
			2	=> 28, // is_leapyear() => +1
			3	=> 31,
			4	=> 30,
			5	=> 31,
			6	=> 30,
			7	=> 31,
			8	=> 31,
			9	=> 30,
			10	=> 31,
			11	=> 30,
			12	=> 31,
		),
	);
	var $zodiacs	= array(
		'by_zodiac'		=> array(
			// sign			=> array(from-day, from-month, until-day, until-month),
			'aquarius'		=> array(21,1,19,02),
			'aries'			=> array(21,3,20,04),
			'cancer'		=> array(22,6,22,07),
			'capricornus'	=> array(22,12,20,01),
			'gemini'		=> array(22,05,21,06),
			'leo'			=> array(23,07,23,08),
			'libra'			=> array(23,09,22,10),
			'pisces'		=> array(20,02,20,03),
			'sagittarius'	=> array(23,11,21,12),
			'scorpius'		=> array(24,10,22,11),
			'taurus'		=> array(21,04,21,05),
			'virgo'			=> array(24,08,23,09),
		),
		'by_date'	=> array( // bigger-equal date is (month -> array(day, before, at&after))
			1		=> array(21, 'capricornus',	'aquarius'),
			2		=> array(20, 'aquarius',	'pisces'),
			3		=> array(21, 'pisces',		'aries'),
			4		=> array(21, 'aries',		'taurus'),
			5		=> array(22, 'taurus',		'gemini'),
			6		=> array(22, 'gemini',		'cancer'),
			7		=> array(23, 'cancer',		'leo'),
			8		=> array(24, 'leo',			'virgo'),
			9		=> array(23, 'virgo',		'libra'),
			10		=> array(24, 'libra',		'scorpius'),
			11		=> array(23, 'scorpius',	'sagittarius'),
			12		=> array(22, 'sagittarius', 'capricornus'),
		),
	);

	var $overflow	= array(
		'seconds'		=> array(60, 'minutes'),
		'minutes'		=> array(60, 'hours'),
		'hours'			=> array(24, 'days'),
		'months'		=> array(12, 'years'),
	);
	var $errors		= array();

	function chronos($timezoneID=false, $language=false)
	{
		if (get_class($this) == __CLASS__) {
			trigger_error(__CLASS__." is an abstract class, you must not instanciate it directly, use cdatetime, difference or timespan instead.", E_USER_ERROR); //Bugfix for PHP5.2, NG
		}
		$this->localtime			= localtime();
		$this->timeofday			= gettimeofday();
		$this->set_defaults($timezoneID);
		$this->unset['time']		= $this->time;
		$this->unset['date']		= $this->date;
		$this->unset['difference']	= $this->difference;
		$this->set_timezone($timezoneID);
		if ($language !== false) {
			$this->set_language($language);
		}
		$this->multipliers	= array( // used for calculating differences
			'seconds'		=> array(
				'seconds'		=> 1,
				'minutes'		=> 60,
				'hours'			=> 3600,
				'days'			=> 86400,
				'weeks'			=> 604800,
				'months'		=> 2629746,
				'years'			=> 86400*YEAR_AVERAGE,
			),
			'minutes'		=> array(
				'seconds'		=> 1/60,
				'minutes'		=> 1,
				'hours'			=> 60,
				'days'			=> 1440,
				'weeks'			=> 10080,
				'months'		=> 43829.1,
				'years'			=> 1440*YEAR_AVERAGE,
			),
			'hours'			=> array(
				'seconds'		=> 1/3600,
				'minutes'		=> 1/60,
				'hours'			=> 1,
				'days'			=> 24,
				'weeks'			=> 168,
				'months'		=> 730.485,
				'years'			=> 24*YEAR_AVERAGE,
			),
			'days'			=> array(
				'seconds'		=> 1/86400,
				'minutes'		=> 1/1440,
				'hours'			=> 1/24,
				'days'			=> 1,
				'weeks'			=> 7,
				'months'		=> MONTH_AVERAGE,
				'years'			=> YEAR_AVERAGE,
			),
			'weeks'			=> array(
				'seconds'		=> 1/604800,
				'minutes'		=> 1/10080,
				'hours'			=> 1/168,
				'days'			=> 1/7,
				'weeks'			=> 1,
				'months'		=> 4.348125,
				'years'			=> YEAR_AVERAGE/7,
			),
			'months'		=> array(
				'seconds'		=> 1/(MONTH_AVERAGE*86400),
				'minutes'		=> 1/(MONTH_AVERAGE*1440),
				'hours'			=> 1/(MONTH_AVERAGE*24),
				'days'			=> 1/MONTH_AVERAGE,
				'weeks'			=> 7/MONTH_AVERAGE,
				'months'		=> 1,
				'years'			=> 12,
			),
			'years'		=> array(
				'seconds'		=> 1/(YEAR_AVERAGE*86400),
				'minutes'		=> 1/(YEAR_AVERAGE*1440),
				'hours'			=> 1/(YEAR_AVERAGE*24),
				'days'			=> 1/YEAR_AVERAGE,
				'weeks'			=> 7/YEAR_AVERAGE,
				'months'		=> 1/12,
				'years'			=> 1,
			),
		);
	}

	function load_stringsFile($lang)
	{
		$file	= "{$this->stringsDirectory}/strings.datetime.{$lang}.inc";
		if ($this->include_exists($file)) {
			include($file);

			// import strings (default is utf8-encoded)
			$utf8	= (isset($strings[$lang]['is_utf8']) && !$strings[$lang]['is_utf8']) ? false : true;
			foreach (array('days','months','zodiacs','outputs') as $field) {
				if (isset($strings[$lang][$field])) {
					foreach ($strings[$lang][$field] as $index => $import) {
						if ($utf8) {
							$this->strings[$lang][$field][$index]	= utf8_decode($import);
						} else {
							$this->strings[$lang][$field][$index]	= $import;
						}
					}
				}
			}
			if (isset($strings[$lang]['timezones']['normal'])) {
				foreach ($strings[$lang]['timezones']['normal'] as $index => $import) {
					if ($utf8) {
						//$this->zonemap[$index]	= array(utf8_decode($import[0]), false);
						$this->strings[$lang]['timezones_abbr'][$index]	= utf8_decode($import[0]);
						$this->strings[$lang]['timezones'][$index]		= utf8_decode($import[1]);
					} else {
						//$this->zonemap[$index]	= array($import[0], false);
						$this->strings[$lang]['timezones_abbr'][$index]	= $import[0];
						$this->strings[$lang]['timezones'][$index]		= $import[1];
					}
				}
			}
			if (isset($strings[$lang]['timezones']['dst'])) {
				foreach ($strings[$lang]['timezones']['dst'] as $index => $import) {
					if ($utf8) {
						//$this->zonemap[$index]				= array(utf8_decode($import[0]), true);
						$this->strings[$lang]['timezonesDST_abbr'][$index]	= utf8_decode($import[0]);
						$this->strings[$lang]['timezonesDST'][$index]		= utf8_decode($import[1]);
					} else {
						//$this->zonemap[$index]	= array($import[0], true);
						$this->strings[$lang]['timezonesDST_abbr'][$index]	= $import[0];
						$this->strings[$lang]['timezonesDST'][$index]		= $import[1];
					}
				}
			}

			// import recognize (default is utf8-encoded)
			$utf8	= (isset($recognize[$lang]['is_utf8']) && !$recognize[$lang]['is_utf8']) ? false : true;
			foreach (array('days','months','patterns') as $field) {
				if (isset($recognize[$lang][$field])) {
					foreach ($recognize[$lang][$field] as $index => $import) {
						if ($utf8) {
							$this->recognize[$lang][$field][$index]	= utf8_decode($import);
						} else {
							$this->recognize[$lang][$field][$index]	= $import;
						}
					}
				}
			}
		} else {
			trigger_error("Language file for '$lang' not found ($file)", E_USER_WARNING);
		}
	}

	function unset_dateTimeAndDifference()
	{
		$this->unset_time();
		$this->unset_date();
		$this->unset_difference();
	}

	function unset_time()
	{
		$this->is['time']	= false;
		$this->time	= $this->unset['time'];
	}

	function unset_date()
	{
		$this->is['date']	= false;
		$this->date	= $this->unset['date'];
	}

	function unset_difference()
	{
		$this->is['difference']	= false;
		$this->difference	= $this->unset['difference'];
	}
	function unset_differenceDate()
	{
		$this->difference['months']	= 0;
		$this->difference	= $this->unset['difference'];
	}

	function set_defaults($timezone=false)
	{
		if (!isset($this->timezones[$timezone])) {
			$timezone	= 'UTC';
		}
		$this->defaults	= array(
		//	'item'			=> array(true-default, false-default)
			'year'			=> array($this->localtime[5]+1900, 0),
			'month'			=> array($this->localtime[4]+1, 1),
			'day'			=> array($this->localtime[3], 1),
			'week'			=> array(strftime("%V"), 1),
			'weekday'		=> array($this->localtime[6], 0),
			'yearday'		=> array($this->localtime[7], 1),
			'timezone'		=> $timezone,
			'hour'			=> array($this->localtime[2], 0),
			'minute'		=> array($this->localtime[1], 0),
			'second'		=> array($this->localtime[0], 0),
			'milli'			=> array(floor($this->timeofday['usec']/1000), 0),
			'micro'			=> array($this->timeofday['usec']%1000, 0),
		);
		return true;
	}

	function set_is($date, $time, $difference)
	{
		$this->is['date']		= $date;
		$this->is['time']		= $time;
		$this->is['difference']	= $difference;
	}

	function set_timezone($timezoneID=false)
	{
		$this->location	= new location($timezoneID);
		$this->set_language($this->location->get_language());
	}

	function set_language($language)
	{
		if ($this->language[$language] > 1) {
			foreach ($this->language as $lang => $pri) {
				$this->language[$lang] = $pri+1;
			}
			$this->language[$language]	= 1;
		}
		$this->load_stringsFile($language);
		asort($this->language);
		$this->location->set_language($language);
	}


	function do_convertTimezone($newTimezoneID)
	{
		// convert current zone to UTC
		$seconds	= $this->location->get_rawOffset();
		$this->do_subtractSeconds($seconds);

		// convert UTC to new zone
		$location	= new location($newTimezoneID);
		$seconds	= $location->get_rawOffset();
		$this->do_addSeconds($seconds);

		// set the new location
		$this->location	= $location;
	}

	function is_chronos($object, $class=__CLASS__)
	{
		return (is_object($object) && is_a($object, $class));
	}

	function is_time($exclusive=true, $object=false)
	{
		if ($object === false) {
			$object	= $this;
		} elseif (!$this->is_chronos($object, 'cdatetime')) { //Bugfix for PHP5.2, NG
			return false;
		}
		return ((!$object->is['date'] || !$exclusive) && $object->is['time']);
	}
	function is_date($exclusive=true, $object=false)
	{
		if ($object === false) {
			$object	= $this;
		} elseif (!$this->is_chronos($object, 'cdatetime')) { //Bugfix for PHP5.2, NG
			return false;
		}
		return ($object->is['date'] && (!$object->is['time'] || !$exclusive));
	}
	function is_datetime($object=false)
	{
		if ($object === false) {
			$object	= $this;
		} elseif (!$this->is_chronos($object, 'cdatetime')) { //Bugfix for PHP5.2, NG
			return false;
		}
		return ($object->is['date'] && $object->is['time']);
	}
	function is_dateOrTime($object=false)
	{
		if ($object === false) {
			$object	= $this;
		} elseif (!$this->is_chronos($object, 'cdatetime')) { //Bugfix for PHP5.2, NG
			return false;
		}
		return ($object->is['date'] || $object->is['time']);
	}
	function is_difference($object=false)
	{
		if ($object === false) {
			$object	= $this;
		} elseif (!$this->is_chronos($object, 'difference')) {
			return false;
		}
		return ($object->is['difference']);
	}

	//	FLAGS: procedural
	function is_leapyear($year=false)
	{
		if ($year === false) {
			if (!isset($this)) {
				$year	= strftime("%Y");
			} else {
				$year = $this->get_year();
			}
		}
		return (($year % 4 == 0) && (($year % 100 != 0) || ($year % 400 == 0)));
	}

	function is_dst()
	{

	}

/* for comparisons we miss options to
	compare times converted to UTC before comparing (automatically)
	compare datetimes ignoring date
	compare datetimes ignoring time
*/
	function is_equal($to)
	{
		if (get_class($this) !== get_class($to)) {
			return false;
		}
		return ($this->get_cmp($to) === 0);
	}

	// returns NULL on invalid comparison, else BOOL
	function is_biggerOrEqual($than)
	{
		return ($this->is_bigger($than) || $this->is_equal($than));
	}
	function is_bigger($than)
	{
		return ($this->get_cmp($than) > 0);
	}
	function is_smallerOrEqual($than)
	{
		return ($this->is_smaller($than) || $this->is_equal($than));
	}
	function is_smaller($than)
	{
		return ($this->get_cmp($than) < 0);
	}

	function get_utc($timezone)
	{
		if (isset($this->zonemap[$timezone][0])) {
			$timezone	= $this->zonemap[$timezone][0];
		}
		return $timezone;
	}

	function get_timezone($format='utc')
	{
		$timezone	= $this->location->get_utc();

		switch($format) {
			case 'seconds':
				$timezone	= $this->timezones[$timezone];
				break;
			case 'minutes':
				$timezone	= $this->timezones[$timezone]/60;
				break;
			case 'hours':
				$timezone	= $this->timezones[$timezone]/3600;
				break;

			case 'utc':
				break;

			case 'short':
				if ($this->is_dst()) {
					$timezoneB	= $timezone;
					$timezone	= $this->get_string('timezonesDST_abbr', $timezone);
					if ($timezoneB == $timezone) {
						$timezone	= $this->get_string('timezones_abbr', $timezone);
					}
				} else {
					$timezone	= $this->get_string('timezones_abbr', $timezone);
				}
				break;

			case 'string':
				if ($this->is_dst()) {
					$timezoneB	= $timezone;
					$timezone	= $this->get_string('timezonesDST', $timezone);
					if ($timezoneB == $timezone) {
						$timezone	= $this->get_string('timezones', $timezone);
					}
				} else {
					$timezone	= $this->get_string('timezones', $timezone);
				}
				break;
		}
		return $timezone;
	}
	
	function get_timezoneID()
	{
		return $this->location->get_timezoneID();
	}

	function get_language()
	{
		reset($this->language);
		$lang	= key($this->language);
		return $lang;
	}
	
	function get_string($block, $string)
	{
		foreach ($this->language as $lang => $priority) {
			if (isset($this->strings[$lang][$block][$string])) {
				return $this->strings[$lang][$block][$string];
			}
		}
		return $string;
	}
	function get_comparison($with)
	{
		return $this->get_cmp($with);
	}

	/* return values:
		false:	impossible comparison
		-1:		$this is smaller (-1 < 0),
		0:		$this is equal (0 == 0)
		1:		$this is bigger (1 > 0) */
	function get_cmp($with)
	{
		// check possibility of comparison
		if (get_class($this) !== get_class($with)) {
			return false;
		} elseif ($this->is_dateOrTime()) {
			if (($this->is_time() && !$with->is_time()) || ($this->is_date() && !$with->is_date()) || ($this->is_datetime() && !$with->is_datetime())) {
				return false;
			}
		}


		// compare differences
		if ($this->is_difference()) {
			if ($this->difference['absolute']['days'] < $with->difference['absolute']['days']) {
				return -1;
			} elseif ($this->difference['absolute']['days'] > $with->difference['absolute']['days']) {
				return 1;
			} else {
				return 0;
			}
		} elseif ($this->is_dateOrTime()) {
			// compare date
			if ($this->is_date(false)) {
				$compare	= array(
					'year'	=> array($this->get_year(), $with->get_year()),
					'day'	=> array($this->get_dayOfYear(), $with->get_dayOfYear()),
				);
				foreach ($compare as $index => $current) {
					if ($current[0] < $current[1]) {
						return -1;
					} elseif ($current[0] > $current[1]) {
						return 1;
					}
				}
			}
			// compare time
			if ($this->is_time(false)) {
				$compare	= array(
					'hour'		=> array($this->get_hour(), $with->get_hour()),
					'minute'	=> array($this->get_minute(), $with->get_minute()),
					'second'	=> array($this->get_second(), $with->get_second()),
					'milli'		=> array($this->get_milli(), $with->get_milli()),
					'micro'		=> array($this->get_micro(), $with->get_micro()),
				);
				foreach ($compare as $index => $current) {
					if ($current[0] < $current[1]) {
						return -1;
					} elseif ($current[0] > $current[1]) {
						return 1;
					}
				}
			}
			// it's equal
			return 0;
		}
	}

	function get_withoutOverflow($array)
	{
		foreach (array('seconds', 'minutes', 'hours', 'days', 'weeks', 'months', 'years') as $key) {
			$value	= (isset($array[$key])) ? $array[$key] : 0;
			if (!is_numeric($value)) {
				trigger_error("Value for key '$key' is not a number but ".gettype($value)."\n");
				$value	= 0;
			}

			if (isset($this->overflow[$key]) && abs($value) > $this->overflow[$key][0]) {
				if (!isset($array[$this->overflow[$key][1]])) {
					$array[$this->overflow[$key][1]]	= 0;
				}
				$preserve	= floor($value/$this->overflow[$key][0]);
				$value		= $value % $this->overflow[$key][0];
				$array[$this->overflow[$key][1]]   += $preserve;
				$array[$key]						= $value;
			}
		}
		return $array;
	}
	function get_differenceTo($to, $absolute=false)
	{
		$datetime	= new cdatetime(); //Bugfix for PHP5.2, NG
		if (!is_object($to) || !is_a($to, "cdatetime")) { //Bugfix for PHP5.2, NG
			trigger_error("Argument \$to must be a cdatetime-object.", E_USER_WARNING); //Bugfix for PHP5.2, NG
			return $datetime;
		}
		$datetime->create_fromUnixtime($this->get_unixtime() - $to->get_unixtime(), $absolute);
		return $datetime;
	}

	function get_stringPart($part)
	{
/*
	%g - wie %G, aber ohne Jahrhundert.
	%G - Das vierstellige Jahr entsprechend der ISO Wochennummer (siehe %V).  Das gleiche Format und der gleiche Wert wie bei %Y. Besonderheit:  entspricht die ISO Wochennummer dem vorhergehenden oder folgenden  Jahr, wird dieses Jahr verwendet.
	%% - ein %-Zeichen
*/
		if (strlen($part) > 1) {
			$part	= strtolower($part);
		}
		if ($this->is_dateOrTime()) {
			switch($part) {
				case "a": // name of day abbreviated (mon - sun)
				case "snday":
				case "shortdayname":
					return substr($this->get_dayOfWeek('string'), 0, 3);

				case "A": // name of day (monday - sunday)
				case "nday":
				case "dayname":
					return $this->get_dayOfWeek('string');

				case "b": // name of month abbreviated (jan - dec)
				case "snmonth":
				case "shortmonthname":
					return substr($this->get_month('string'), 0, 3);

				case "B": // name of month (january - december)
				case "nmonth":
				case "monthname":
					return $this->get_month('string');

				case "C": // get first two digits of year (eg. 20 of 2005)
				case "century":
					return substr($this->get_year('alldigits'), 0, 2);

				case "d":
				case "day":
				case "dayofmonth":
					return $this->get_day('alldigits');

				case "H":
				case "hour":
				case "hour24":
					return $this->get_hour('alldigits', 24);

				case "I":
				case "hour12":
					return $this->get_hour('alldigits', 12);

				case "j":
				case "dayofyear":
					return $this->get_dayOfYear('alldigits');

				case "m":
				case "month":
					return $this->get_month('alldigits');

				case "M":
				case "min":
				case "minute":
					return $this->get_minute('alldigits');

				case "S":
				case "sec":
				case "second":
					return $this->get_second('alldigits');

				case "u":
				case "w":
				case "dayofweek":
					return $this->get_dayOfWeek('alldigits');

				case "U":
				case "timezone":
				case "timezoneutc":
					return $this->get_timezone('utc');

				case "V":
				case "isoweek":
					return $this->get_week('alldigits');

				case "W":
				case "week":
					return $this->get_week('alldigits');

				case "y":
				case "year2":
					return $this->get_year(2);

				case "Y":
				case "year":
				case "year4":
					return $this->get_year(4);

				case "z":
				case "ntimezone":
				case "timezonename":
					return $this->get_timezone('string');

				case "Z":
				case "sntimezone":
				case "shorttimezonename":
					return $this->get_timezone('short');

				case "zodiac":
					return $this->get_zodiac();

				case "%":
					return '%';

				default:
					// lookup in localisation if there is something...

			}
		} elseif ($this->is_difference()) {
			switch($part) {
				case "d":
				case "days":
					return $this->get_days();

				case "H":
				case "hours":
					return $this->get_hours();

				case "m":
				case "months":
					return $this->get_months();

				case "M":
				case "mins":
				case "minutes":
					return $this->get_minutes();

				case "S":
				case "secs":
				case "seconds":
					return $this->get_seconds();

				case "W":
				case "weeks":
					return $this->get_weeks();

				case "y":
				case "years":
					return $this->get_years();

				case "%":
					return '%';

				default:
					// lookup in localisation if there is something...
			}
		}
		return '';
	}

	// algorithm taken from lgpl-library 'class.kronos.php' (rajasi@ziobudda.net, info@holosoft.it)
	function get_timeserverStamp($server='time-a.nist.gov', $port=37) //
	{
	    if ($fp = @fsockopen($server, $port, $errno, $errstr, 25)) {
	        fputs($fp, "\n");
	        $timevalue = fread($fp, 49);
	        fclose($fp);
	    	$ts = (abs(hexdec('7fffffff') - hexdec(bin2hex($timevalue)) - hexdec('7fffffff')) - 2208988800);
	    } else {
	    	trigger_error("Could not connect to '$server:$port' - server is not responding or no internet connection.", E_USER_NOTICE);
	    	$ts	= time();
		}
	    return $ts;
	}

	function get_appliedModificators($value, $modifiers)
	{
		foreach ($modifiers as $modifier) {
			if (is_numeric($modifier)) {
				$value	= substr($value, 0, $modifier);
			} else {
				switch($modifier) {
					case 'uc':
					case 'uppercase':
						$value	= strtoupper($value);
						break;
					case 'ucf':
					case 'uppercasefirst':
						$value	= ucfirst($value);
						break;
					case 'lc':
					case 'lowercase':
						$value	= strtolower($value);
						break;
					case 'html':
					case 'htmlentities':
						$value	= htmlentities($value);
						break;
					default:
						if (function_exists($modifier)) {
							$value	= $modifier($value);
						} else {
							trigger_error("Invalid modifier '$modifier'", E_USER_WARNING);
						}
				}
			}
		}
		return $value;
	}

	/*
		algorithm taken from lgpl-library 'class.kronos.php' (rajasi@ziobudda.net, info@holosoft.it) and slightly changed
		The algorithm is still the same, I just removed unecessary while-loops and replaced them with straight calculations
		additionally I replaced the numeric constants with built-in php constants (the stuff with M_PI)
		And I'm still searching for a good functionname :-/
		Calculates sunrise, sunset, morning-twilight, evening-twilight - used by function of that name in class datetime
	*/
	function get_sunCalculation($location=false, $what='sunrise', $timezone=false)
	{
		// normalizing location
		if (is_string($location)) {
			$location	= $this->get_location($location);
			list($latitude, $longitude) = array($location['latitude'], $location['longitude']);
		} elseif (isset($location['latitude']) && isset($location['longitude'])) {
			list($latitude, $longitude) = array($location['latitude'], $location['longitude']);
		} elseif (isset($location[0]) && isset($location[1])) {
			list($latitude, $longitude) = array($location[0], $location[1]);
		} elseif ($location === false) {
			$latitude	= $this->location->get_latitude();
			$longitude	= $this->location->get_longitude();
		} else {
			trigger_error("Invalid location format.", E_USER_WARNING);
			return array(0,0,0);
		}

		// normalizing timezone
		if ($timezone === false) {
			$timezone	= $this->get_timezone("hours") + ($this->is_dst() ? 1 : 0);
		}
		if($timezone == "13") {
			$timezone = "-11";
		}

		// calculating constants
		$E		= (M_PI/180) * $latitude;
		$F		= (M_PI/180) * $longitude;
		$G		= (M_PI/12)  * $timezone;

		# For astronomical twilight, use R = -.309017
		# For     nautical twilight, use R = -.207912
		# For        civil twilight, use R = -.104528
		# For     sunrise or sunset, use R = -.0145439
		if ($what == 'morningtwilight' || $what == 'eveningtwilight') {
			$R = -.104528; //<- twilight
		} elseif ($what == 'sunrise' || $what == 'sunset') {
			$R = -.0145439; //<- sunrise/sunset
		}

		if ($what == 'sunrise' || $what == 'morningtwilight') {
			$J =  M_PI_2;
		} else { # calculate sunrise
			$J =  (1.5*M_PI);
		} # calculate sunset

		$K = $this->get_dayOfYear() - 1 + (($J - $F) / (2*M_PI));
		$L = ($K * .017202) - .0574039;				# Solar Mean Anomaly
		$M = $L + .0334405 * sin($L);				# Solar True Longitude
		$M += 4.93289 + (3.49066E-04) * sin(2 * $L);

		# Quadrant Determination
		if ($M < 0) {	$M += (2*M_PI)*ceil((0-$M)/(2*M_PI)); }
		if ($M >= (2*M_PI)) {	$M -= (2*M_PI)*ceil(($M-(2*M_PI))/(2*M_PI)); }

		if (($M / M_PI_2) - intval($M / M_PI_2) == 0) {
			$M += 4.84814E-06;
		}

		$P = sin($M) / cos($M);		# Solar Right Ascension
		$P = atan2(.91746 * $P, 1);

		# Quadrant Adjustment
		if ($M > (1.5*M_PI)) {
			$P += (2*M_PI);
		} elseif ($M > M_PI_2) {
			$P += M_PI;
		}

		$Q = .39782 * sin($M);            # Solar Declination
		$Q = $Q / sqrt(-$Q * $Q + 1);     # This is how the original author wrote it!
		$Q = atan2($Q, 1);

		$S = $R - (sin($Q) * sin($E));
		$S = $S / (cos($Q) * cos($E));

		if (abs($S) > 1) {
			return array(0,0,0);
		} # Null phenomenon

		$S = $S / sqrt(-$S * $S + 1);
		$S = M_PI_2 - atan2($S, 1);

		if ($what == 'sunrise' || $what == 'morningtwilight') {
			$S = (2*M_PI) - $S;
		}

		$T = $S + $P - 0.0172028 * $K - 1.73364; # Local apparent time
		$U = $T - $F;                            # Universal timer
		$V = $U + $G;                            # Wall clock time

		# Quadrant Determination
		if ($V < 0) {	$V += (2*M_PI)*ceil((0-$V)/(2*M_PI)); }
		if ($V >= (2*M_PI)) {	$V -= (2*M_PI)*ceil(($V-(2*M_PI))/(2*M_PI)); }
		$V = $V * 3.81972;

		$hour = intval($V);
		$min  = intval((($V - $hour) * 60) + 0.5);
		$sec  = intval((((($V - $hour) * 60) - $min + 0.5) * 60) + 0.5);
		if ($sec > 59) {
			$min++;
			$sec-=60;
		}
		if ($min > 59) {
			$hour++;
			$min-=60;
		}
		return array($hour, $min, $sec);
	}

	function include_exists($filename)
	{ // returns full path of an include where only filename is given or false if no include file of this name in any include path exists
		if (substr($filename,0,1) == '/') { //absolute filepath
			if (file_exists($filename)) {
				return $filename;
			} else {
				return false;
			}
		}
		$include_dirs = split(":",ini_get('include_path')); //!!!suboptimal, on some platforms it's not ":"!
		foreach ($include_dirs as $dir) {
			if (substr($dir, -1) != '/') { $dir .= '/'; } // append a trailing slash if not already present !!!suboptimal, on some platforms it's not "/"!
			if (file_exists($dir.$filename)) {
				return $dir.$filename;
			}
		}
		return false;
	}

	// copies all chronos
	function convert_copyChronos($chronos=null, $copyTo=null)
	{
		// list all chronos attributes
		$copy_properties	= get_class_vars('chronos');
		foreach (array('version','difference','date','time') as $unset) {
			unset($copy_properties[$unset]);
		}
		// defaultize variables
		if (is_null($chronos)) {
			$chronos	= &$this;
		}
		if (is_null($copyTo)) {
			$copyTo		= &$this;
		}
		// copy properties
		foreach ($copy_properties as $property => $unused) {
			$copyTo->$property	= $chronos->$property;
		}
		return true;
	}

	// if ignoreDate is false then the difference will include years, months and days. If ignoreDate is set to 'year'
	function convert_toDifference($ignoreDate=true)
	{
		// convert a time/date to difference
		if ($this->is_dateOrtime()) {
			$array['seconds']	= $this->get_second();
			$array['minutes']	= $this->get_minute();
			$array['hours']		= $this->get_hour();
			if ($ignoreDate !== true) {
				$array['seconds']	= $this->get_day();
				$array['months']	= $this->get_month();
			}
			if ($ignoreDate !== 'year') {
				$array['years']		= $this->get_year();
			}
			$difference	= new difference();
			$this->convert_copyChronos(null, $difference);
			$difference->create_fromArray($array);

		// convert a difference to difference
		} elseif ($this->is_difference()) {
			return true; // nothing to do
		}
	}

	function convert_toTime()
	{
		// convert a time to time
		if ($this->is_time()) {
			return true; // nothing to do

		// converting a date to time doesn't make sense, but we do it anyway
		} elseif ($this->is_date()) {
			$this->create_fromArray(array('hour' => 0));

		// convert a datetime to time
		} elseif ($this->is_datetime()) {
			$this->unset_date(); // just drop the date part

		// convert a difference to time
		} elseif ($this->is_difference()) {
			$array	= array(
				'second'	=> $this->get_seconds('partial'),
				'minute'	=> $this->get_minutes('partial'),
				'hour'		=> $this->get_hours('partial'),
			);
//			$this	= new cdatetime('array',$array); //Bugfix for PHP5.2, NG
			convert_copyChronos( new cdatetime('array',$array), $this ); //Bugfix for PHP5, PHP5.2, NG
			return true;
		}
	}

	// $missingDate should contain the missing date part in a form as the cdatetime-constructor accepts it //Bugfix for PHP5.2, NG
	function convert_toDate($missingDate='current')
	{
		// convert a time to date doesn't make sense, but we do it anyway
		if ($this->is_time()) {
//			$this	= new cdatetime($missingDate); //Bugfix for PHP5.2, NG
			convert_copyChronos( new cdatetime($missingDate), $this ); //Bugfix for PHP5, PHP5.2, NG
			$this->unset_time();
			return true;

		// converting a date to date
		} elseif ($this->is_date()) {
			return true; // nothing to do :)

		// convert a datetime to time
		} elseif ($this->is_datetime()) {
			$this->unset_time(); // just drop the time part

		// convert a difference to date
		} elseif ($this->is_difference()) {
			// there are just too many odds
			trigger_error("Can not convert a difference to date");
			return false;
		}
	}

	// $missing should contain either the missing time or date part in a form datetime-
	function convert_toDatetime($missing='current')
	{
	}
}
?>