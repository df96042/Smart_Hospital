<?php
// API access key from Google API's Console
define( 'API_ACCESS_KEY', 'AAAARQlW3Kk:APA91bGWAAd_SgcRAkgt7Rw7zyDotl3D2H4-UWjpOHHhSdnxc2MXD7GosQ1zXM3c2HHZO1R3w7Ub_UYEJMTw9dNTPTUtCT4xpE-KSIjWKA6oub30aQQc5OC1zSjPv4sHUBrbxYHOzaKa' );
$registrationIds = array( $_GET['id'] );
// prep the bundle
$msg = array
(
	"message" => "helloworld",
	"title" => "please"
);
$notification = array 
(
	"body" => "gsdflkj!",
	"title" => "sdflk"
);
$fields = array
(
	'registration_ids' 	=> $registrationIds,
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
echo $result;
?>
