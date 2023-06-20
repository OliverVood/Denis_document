<?php

	namespace Proj;

	use Base\DB\DBObjectMySQLi;

	class DBObject extends DBObjectMySQLi {

		public function __construct($hostname, $user, $password, $dbname) {
			parent::__construct($hostname, $user, $password, $dbname);
			self::Query("SET GLOBAL time_zone = 'UTC'");
		}

	}

	DBObject::init(DB_HOST, DB_USER, DB_PASS, DB_NAME);

	if (!DBObject::instance()->State()) die('MySQLi database connection error! Code: ' . DBObject::instance()->GetErrorCode());