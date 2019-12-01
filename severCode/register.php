<?php

if(isset($_POST["Token"])){
	$token = $+POST["Token"];
	$mysql_host = 'localhost';
	$mysql_user = 'root';
	$mysql_password = '821n2757';
	$mysql_db = 'Hospital';

	// 접속
	$conn = mysql_connect($mysql_host, $mysql_user, $mysql_password);
	$dbconn = mysql_select_db($mysql_db, $conn);

	$query = "UPDATE user set token='$token' where id=1";
	mysqli_query($conn,$query);

	mysqli_close($conn);
}
?> 



