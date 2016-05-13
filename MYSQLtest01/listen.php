<?php
try {
    if (isset($_POST["t"]) && $_POST["t"] != "") {

        #t is the task we want to do
        $task = $_POST["t"];

        #bd is the database (m for mysql, s for sqlite)
        if (isset($_POST["db"]) && $_POST["db"] != "") {
            $db_type = $_POST["db"];
            if ($type_db === "m") {
                $link = new \PDO('mysql:host=localhost ;port=3306; dbname=beerfridge01', 'root', 'root', array(
                    \PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION,
                    \PDO::ATTR_PERSISTENT => false,ßß
                    \PDO::MYSQL_ATTR_INIT_COMMAND => 'set names utf8mb4'
                ));
            } else {
                $link = new \PDO('sqlite:/mnt/sd/sqlite_file_in_the_yun_sd');
            }

             #Task i_t= insert temperature in the temperature table
            if ($task === "i_t") {
                $temp = $_POST["te"];

                $query = "INSERT INTO  temp (temp)VALUES (?)";
                $handle = $link->prepare($query);
                $handle->bindValue(1, $temp);
                $handle->execute();
                echo 'OK';
            }
            $link = null;
        } else {
            echo "DB type missing";
        }
    } else {
        echo "Task missing";
    }
    exit;
} catch (\PDOException $ex) {
    echo $ex->getMessage();
}
?>
