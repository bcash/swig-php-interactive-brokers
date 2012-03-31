<?php

error_reporting(E_ALL);
ini_set('display_errors', '1');

require_once('InteractiveBrokersAPI.php');
require_once("events.php");

$events = new IBEvents();
$events->thisown = 0;

$ib = new InteractiveBrokersAPIClient($events);
$ib->eConnect("127.0.0.1",7496);

while($ib->isConnected()) {
  $ib->processMessages();
  sleep(2);
}
?>
