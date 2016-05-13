<?php

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "beerfridge01";
$getTemp = $_GET['temp'];
$giveTemp = $_GET['getTemp'];
$changeTemp = $_GET['changeTemp'];


// Send temp to database.
if ($getTemp != '') {
            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $sql = "INSERT INTO temp (temp)
            VALUES ($getTemp)";

            if ($conn->query($sql) === TRUE) {
                echo "New record created successfully";
            } else {
                echo "Error: " . $sql . "<br>" . $conn->error;
            }

            $conn->close();
}


//Get the wanted Temp.
if ($giveTemp === '1') {
            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $sql = "SELECT wantedTemp FROM setTemp";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) {
                // output data of each row
                while($row = $result->fetch_assoc()) {
                    echo $row["wantedTemp"];
                }
            } else {
                echo "0 results";
            }
            $conn->close();

}


if ($changeTemp != '') {
            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $sql = "UPDATE setTemp SET wantedTemp = $changeTemp";

            if ($conn->query($sql) === TRUE) {
                echo "Record updated successfully";
            } else {
                echo "Error updating record: " . $conn->error;
            }
            $conn->close();
}

?>
