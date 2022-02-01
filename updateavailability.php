<!DOCTYPE html>
<html>
<body>
	<?php 
		include 'dbconnection.php';
		
		
      $Pos = isset($_GET["position"]) ? $_GET["position"] : '';

      $Available = isset($_GET["available"]) ? $_GET["available"] : '';

      // $Pos = $_POST["position"];

       // $Available = $_POST["available"];
		$sql = "UPDATE parkinglot SET available = " . $Available . " WHERE position = " . $Pos;
		$result = $conn->query($sql);
     	$conn->close();
      

	?>
</body>
</html>