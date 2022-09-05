<?php

	namespace Base\DB;

	abstract class DB {
		protected ?string $host;
		protected ?string $username;
		protected ?string $password;
		protected ?string $dbname;
		protected ?string $port;
		protected ?string $socket;

		protected ?bool $state;

		protected function __construct($host = null, $username = null, $password = null, $dbname = null, $port = null, $socket = null) {
			$this->host				= $host;
			$this->username			= $username;
			$this->password			= $password;
			$this->dbname			= $dbname;
			$this->port				= $port;
			$this->socket			= $socket;
		}

		abstract public static function Connect($hostname = null, $user = null, $password = null, $dbname = null, $port = null, $socket = null);
		abstract public function Insert(array $data, string $tablename);
		abstract public function Update(array $data, string $where, string $tablename);
		abstract public function Delete();
		abstract public function Select();
	}