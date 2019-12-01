<meta name="viewport" content="width=device-width, initial-scale=0.75, maximum-scale=0.8, minimum-scale=0, user-scalable=no, target-densitydpi=medium-dpi" />
<meta http-equiv="refresh" content="3">

</script>
<?php
$mysql_host = 'localhost';
$mysql_user = 'root';
$mysql_password = '821n2757';
$mysql_db = 'Hospital';

// 접속
$conn = mysql_connect($mysql_host, $mysql_user, $mysql_password);
$dbconn = mysql_select_db($mysql_db, $conn);


// charset 설정, 설정하지 않으면 기본 mysql 설정으로 됨, 대체적으로 euc-kr를 많이 사용
//mysql_query("set names utf8");


$sql="SELECT * FROM Alarm";
//echo $sql;

 

$result = mysql_query($sql) ;


$str_time="";
$str_atemper="";
while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
 //echo($row['time']."--------------".$row['temperature']."<br>");
 $str_time .="'".$row['patient_name']."',";
 $str_alarm .="".$row['state'].",";
	if($row['state']=='3')
		$emergen = $row['patient_name'];
 $str_w_alarm .="".$row['w_alarm'].",";
}
$str_time= substr($str_time,0,-1);
$str_alarm= substr($str_alarm,0,-1);
$str_w_alarm= substr($str_w_alarm,0,-1);
//echo $str_atemper;

?>
<?php
    include_once('./send_notification.php');
    if(strpos($str_alarm, '3') !== false)
{
	    send_notification( 'ccEqI8e0l9M:APA91bHBO-KPB9ezCu7i3d2_OkXj-L1pVSV4ribLsNM0QLeDb8Osp8DDq-8bjYWAp4uSoX1lPgvigqtFYFW8y8ROR3_fthV2Lo_HOBb7cx_cbbezmr7HkIJfrFZ9zwJ_e_s_4Q6NTg_i', 'please',$emergen );
}
?>


<!DOCTYPE HTML>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <title>IV state</title>
<div align="center"><a href='/'><img src="/ringer.png" width:"10px" height:"10px"></a></div>


  <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
  <style type="text/css">
	${highcharts.css}
  </style>
  <link rel="stylesheet" type="text/css" href="./highchart/code/css/highcharts.css" />
  <script type="text/javascript">
$(function () {
    $('#container').highcharts({
        chart: {
            type: 'bar'
//	    backgroundColor: 'black'
        },
        title: {
            text: 'Real-Time'
        },
        subtitle: {
            text: 'IV'
        },
        xAxis: {
            categories: [<?php echo $str_time?>]
        },
        yAxis: {
            title: {
                text: 'IV'
            }
        },
        plotOptions: {
            bar: {
                dataLabels: {
                    enabled: true
                },
                enableMouseTracking: false
            }
        },
        series: [{
            name: 'mount',
	    data: [<?php echo $str_w_alarm?>]
	}]		        
    });
});
  </script>
 </head>
 <body>
<script src="./highchart/code/js/highcharts.js"></script>
<script src="./highchart/code/js/modules/exporting.js"></script>

<div id="container" style="width: 500px; height: 400px; margin: 0 auto"></div>
 </body>
</html>


