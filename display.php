<!DOCTYPE html>
<html lang="en">
<head>
  <title>Smart Parking</title>
  <br>
  <br>
  <center><h1>SMART PARKING</h1></center>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"></script>

<style>

	.red-icon {
		color:#ff0000;
	}
	.green-icon {
		color:#009933;
	}
	.table-responsive
	{
		width:80%;
    padding-top: 50px;
    padding-bottom: 50px;
    text-align: center;


	}

.body{
  background-color: rgba(67, 255, 66, 0.2);
}


.button1 {
  border: none;
  color: white;
  background-color:green;
  padding: 15px 40px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 20px;
  margin: 4px 2px;
  border-radius: 12px;
}
  .button2 {
  border: none;
  color: white;
  background-color:red;
  padding: 15px 40px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 20px;
  margin: 4px 2px;
  border-radius: 12px;
}

</style>

</head>
<body class="body">

<?php 
include 'dbconnection.php'; 
	$sql = "SELECT position, available FROM parkinglot Order by position";
	$result = $conn->query($sql);
	header("Refresh:1");
?>

<div class="container-fluid">
<center>
	<div class="table-responsive">
		<table class="table table-dark ">
			<thead class="table table-light">
				<tr>
					<th> Basement </th>
					<th> Availability </th>
				</tr>
			</thead>
		 	<?php while($row = $result->fetch_assoc()) { ?> 
				<tbody>
					<tr >
	 					<td class="td"> Position <?php echo $row['position']; ?>  </td>
						<td class="td"> 
							<?php if ( $row['available'] == 1 ) { ?>
								<button type="button" class="button1"><p>Available</p></button>
							<?php }  else { ?>
								<button type="button" class="button2"><p> Not Available</p></button>
							<?php } ?>
						</td>
		 			</tr>
				</tbody>
			<?php } ?>
		</table>
	</div>
</center>
</div>
<?php 	$conn->close(); ?>

</body>
</html>