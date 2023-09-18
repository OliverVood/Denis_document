<?php

	namespace Proj;

	use Base\DB\MySQLi;
	use Base\Debugger;

	class DBQuery extends MySQLi\DBQuery {

		public function __construct($hostname, $user, $password, $dbname) {
			parent::__construct($hostname, $user, $password, $dbname);
			$this->SetCharset('utf8mb4');
			self::Query("SET GLOBAL time_zone = 'UTC'");
		}

	}

	DBQuery::init(DB_HOST, DB_USER, DB_PASS, DB_NAME);

	if (!DBQuery::instance()->State()) die('MySQLi database connection error! Code: ' . DBQuery::instance()->GetErrorCode());

	Debugger::SetDB(DBQuery::instance());