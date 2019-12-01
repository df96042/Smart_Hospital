
<?php

define( 'API_ACCESS_KEY', 'AAAARQlW3Kk:APA91bGWAAd_SgcRAkgt7Rw7zyDotl3D2H4-UWjpOHHhSdnxc2MXD7GosQ1zXM3c2HHZO1R3w7Ub_UYEJMTw9dNTPTUtCT4xpE-KSIjWKA6oub30aQQc5OC1zSjPv4sHUBrbxYHOzaKa' );
function send_notification( $token, $message,$patient ) {
//	$emer = sprinf("patient%d EMERGENGY!!!!",$patient); 
	$emer = sprintf("%s EMERGENCY!!!!!",$patient);
	$msg = array
		(
		 "message" => $message,
		 "title" => "please"
		);
	$notification = array 
		(
		 "body" => $emer, //"EMERGENCY!!!",
		 "title" => $patient
		);
	$fields = array
		(
		 'to' 	=> $token,
		 'data'			=> $msg,
		 'notification' => $notification
		);

	$headers = array
		(
		 'Authorization: key=' . API_ACCESS_KEY,
		 'Content-Type: application/json'
		);
	$ch = curl_init();
	curl_setopt( $ch,CURLOPT_URL, 'https://android.googleapis.com/gcm/send' );
	curl_setopt( $ch,CURLOPT_POST, true );
	curl_setopt( $ch,CURLOPT_HTTPHEADER, $headers );
	curl_setopt( $ch,CURLOPT_RETURNTRANSFER, true );
	curl_setopt( $ch,CURLOPT_SSL_VERIFYPEER, false );
	curl_setopt( $ch,CURLOPT_POSTFIELDS, json_encode( $fields ) );
	$result = curl_exec($ch );

	curl_close( $ch );
	return $result;
}

?>
