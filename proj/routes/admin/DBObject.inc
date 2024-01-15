<?php

	namespace Proj;

	use Base\DB\MySQLi;
	use Base\Debugger;

	class DBObject extends MySQLi\DBObject {

		public function __construct($hostname, $user, $password, $dbname) {
			parent::__construct($hostname, $user, $password, $dbname);
			$this->SetCharset('utf8mb4');
			self::Query("SET GLOBAL time_zone = 'UTC'");
		}

	}

	DBObject::init(DB_HOST, DB_USER, DB_PASS, DB_NAME);

	if (!DBObject::instance()->State()) die('MySQLi database connection error! Code: ' . DBObject::instance()->GetErrorCode());

	Debugger::SetDB(DBObject::instance());