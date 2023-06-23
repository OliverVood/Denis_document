<?php

	namespace Base\DB\MySQLi;

	abstract class DBQuery extends \Base\DB\DBQuery {
		use DB;

		protected function __construct(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null) {
			parent::__construct();

			$this->Link($host, $username, $password, $dbname, $port, $socket);
		}

	}