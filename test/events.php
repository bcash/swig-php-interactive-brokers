<?php


class IBEvents extends EWrapper
{

  function tickPrice($tickerId,$field,$price,$canAutoExecute) {

    print "Tick price event received\n";
    print "tickerId: $tickerId, field: $field, price $price, canAutoExecute: $canAutoExecute\n";

  }

  function tickSize($tickerId,$field,$size) {

    print "Tick size event received\n";
    print "tickerId: $tickerId, field: $field, size: $size\n";

  }

  function tickOptionComputation($tickerId,$tickType,$impliedVol,$delta,$optPrice,$pvDividend,$gamma,$vega,$theta,$undPrice) {

    print "Tick option computation event received\n";
    print "tickerId: $tickerId, 
           tickType: $tickType, 
           impliedVol: $impliedVol, 
           delta: $delta, 
           optPrice: $optPrice, 
           pvDividend: $pvDividend, 
           gamma: $gamma, 
           vega: $vega, 
           theta: $theta, 
           undPrice: $undPrice\n";

  }

  function tickGeneric($tickerId,$tickType,$value) {
  
    print "Tick generic event received\n";
    print "tickerId: $tickerId, tickType: $tickType, value: $value\n";

  }

  function tickString($tickerId,$tickType,$value) {

    print "Tick string event received\n";
    print "tickerId: $tickerId, tickType: $tickType, value: $value\n";

  }

  function tickEFP($tickerId,$tickType,$basisPoints,$formattedBasisPoints,$totalDividends,$holdDays,$futureExpiry,$dividendImpact,$dividendsToExpiry) {

    print "Tick EFP event received\n";
    print "tickerId: $tickerId, 
           tickType: $tickType,
           basisPoints: $basisPoints,
           formattedBasisPoints: $formattedBasisPoints,
           totalDividens: $totalDividends,
           holdDays: $holdDays,
           futureExpire: $futureExpiry,
           dividendImpact: $dividendImpact,
           dividendsToExpire: $dividendsToExpiry\n";
  }

  function orderStatus($orderId,$status,$filled,$remaining,$avgFillPrice,$permId,$parentId,$lastFillPrice,$clientId,$whyHeld) {

    print "Order status event received\n";
    print "orderId: $orderId,
           status: $status,
           filled: $filled,
           remaining: $remaining,
           avgFillPrice: $avgFillPrice,
           permId: $permId,
           parentId: $parentId,
           lastFillPrice: $lastFillPrice,
           clientId: $clientId,
           whyHeld: $whyHeld\n";

  }

  function openOrder($orderId,$arg0,$arg1,$arg2) {

    print "Order status event received\n";
    print "orderId: $orderId,
           arg0: $arg0,
           arg1: $arg1,
           arg2: $arg2\n";

  }

  function openOrderEnd() {

    print "Open order end event received\n";

  }

  function winError($str,$lastError) {

    print "Win error event received\n";
    print "str: $str, lastError: $lastError\n";

  }

  function connectionClosed() {

    print "Connection closed event received\n";

  }

  function updateAccountValue($key,$val,$currency,$accountName) {

    print "Update account value event received\n";
    print "key: $key, val: $val, currency: $currency, accountName: $accountName\n";

  }

  function updatePortfolio($contract,$position,$marketPrice,$marketValue,$averageCost,$unrealizedPNL,$realizedPNL,$accountName) {

    print "Update portfolio event received\n";
    print "contract: $contract,
           position: $position,
           marketPrice: $marketPrice,
           marketValue: $marketValue,
           averageCost: $averageCost,
           unrealizedPNL: $unrealizedPNL,
           realizedPNL: $realizedPNL,
           accountName: $accountName\n";

  }

  function updateAccountTime($timeStamp) {

    print "Update account time event received\n";
    print "timestamp: $timeStamp\n";
  }

  function accountDownloadEnd($accountName) {

    print "Account download end event received\n";
    print "accountDownloadEnd: $accountName\n";

  }

  function nextValidId($orderId) {

    print "Next valid id event received\n";
    print "nextValidId: $orderId\n";

  }

  function contractDetails($reqId,$contractDetails) {

    print "Contract details event received\n";
    print "reqId: $reqId, contractDetails: $contractDetails\n";

  }

  function bondContractDetails($reqId,$contractDetails) {

    print "Bond contract details event received\n";
    print "reqId: $reqId, contractDetails: $contractDetails\n";

  }

  function contractDetailsEnd($reqId) {

    print "Contract details end event received\n";
    print "reqId: $reqId\n";

  }

  function execDetails($reqId,$contract,$execution) {

    print "Exec details event received\n";
    print "reqId: $reqId, constract: $contract, execution: $execution\n";

  }

  function execDetailsEnd($reqId) {

    print "Exec details end event received\n";
    print "reqId: $reqId\n";

  }

  function error($id,$errorCode,$errorString) {

    print "Error event received\n";
    print "id: $id, errorCode: $errorCode, errorString: $errorString\n";

  }

  function updateMktDepth($id,$position,$operation,$side,$price,$size) {

    print "Update market depth event received\n";
    print "id: $id, 
           position: $position, 
           operation: $operation, 
           side: $side, 
           price: $price, 
           size: $size\n";

  }

  function updateMktDepthL2($id,$position,$marketMaker,$operation,$side,$price,$size) {

    print "Update market depth level 2 event received\n";
    print "id: $id, 
           position: $position, 
           marketMaker: $marketMaker, 
           operation: $operation, 
           side: $side, 
           price: $price, 
           size: $size\n";

  }

  function updateNewsBulletin($msgId,$msgType,$newsMessage,$originExch) {

    print "Update news bulletin event received\n";
    print "msgId: $msgId, 
           msgType: $msgType, 
           newsMessage: $newsMessage, 
           originExch: $originExch\n";

  }

  function managedAccounts($accountsList) {

    print "Managed accouns event received\n";
    print "accountsList: $accountsList\n";

  }

  function receiveFA($pFaDataType,$cxml) {

    print "Receive FA event received\n";
    print "pFaDataType: $pFaDataType, cxml: $cxml\n";

  }

  function historicalData($reqId,$date,$open,$high,$low,$close,$volume,$barCount,$WAP,$hasGaps) {

    print "Historical data event received\n";
    print "reqId: $reqId, 
           date: $date, 
           open: $open, 
           high: $high, 
           low: $low, 
           close: $close, 
           volume: $volume, 
           barCount: $barCount, 
           WAP: $WAP, 
           hasGaps: $hasGaps\n";

  }

  function scannerParameters($xml) {

    print "Scanner parameters event received\n";
    print "xml: $xml\n";

  }

  function scannerData($reqId,$rank,$contractDetails,$distance,$benchmark,$projection,$legsStr) {

    print "Scanner data event received\n";
    print "reqId: $reqId, 
           rank: $rank, 
           contractDetails: $contractDetails, 
           distance: $distance, 
           benchmark: $benchmark, 
           projection: $projection, 
           legsStr: $legsStr\n";

  }

  function scannerDataEnd($reqId) {

    print "Scanner data end event received\n";
    print "reqId: $reqId\n";

  }

  function realtimeBar($reqId,$time,$open,$high,$low,$close,$volume,$wap,$count) {

    print "Real time bar event received\n";
    print "reqId: $reqId,
           time: $time,
           open: $open,
           high: $high,
           low: $low,
           close: $close,
           volume: $volume,
           wap: $wap,
           count: $count\n";

  }

  function currentTime($time) {

    print "Current time event received\n";
    print "time: $time\n";

  }

  function fundamentalData($reqId,$data) {

    print "Fundamental data event received\n";
    print "reqId: $reqId, data: $data\n";

  }

  function deltaNeutralValidation($reqId,$underComp) {

    print "Delta neutral validation event received\n";
    print "reqId: $reqId, underComp: $underComp\n";

  }

  function tickSnapshotEnd($reqId) {

    print "Tick snapshot end event received\n";
    print "reqId: $reqId\n";

  }

  function marketDataType($reqId,$marketDataType) {

    print "Market data type event received\n";
    print "reqId: $reqId, marketDataType: $marketDataType\n";

  }

};



?>
