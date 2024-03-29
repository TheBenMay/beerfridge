<?php

$dbname = 'beerfridge01'; // Enter DB Here
$username = 'root'; // Enter Username Here
$password = 'root'; // Enter Password Here

$conn = new PDO("mysql:host=localhost;dbname=$dbname", $username, $password);
  $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    try {
      $result = $conn->query('SELECT * FROM temp WHERE datetime > DATE_SUB(CURDATE(), INTERVAL 7 DAY);');

  $rows = array();
  $table = array();
  $table['cols'] = array(array('label' => 'Datetime', 'type' => 'string'),array('label' => 'Temp', 'type' => 'number'));

  foreach($result as $r) {

  $data = array();
  $time = $r['datetime'];
  $data[] = array('v' => (string) date("F jS, g:ia",strtotime($time)));
  $data[] = array('v' => (int) $r['temp']);

  $rows[] = array('c' => $data);

  }

$table['rows'] = $rows;

} catch(PDOException $e) {
    echo 'ERROR: ' . $e->getMessage();
}

try {
  $result2 = $conn->prepare("SELECT * FROM temp WHERE datetime >= CURDATE();");

  $result2->execute();

} catch(PDOException $e) {
    echo 'ERROR: ' . $e->getMessage();
}

?>
