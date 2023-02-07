<?php

	namespace Base\DB;

	abstract class DBQueryMySQLi extends DBQuery {
		use DBMySQLi;

		protected function __construct(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null) {
			parent::__construct();

			$this->Link($host, $username, $password, $dbname, $port, $socket);
		}

	}