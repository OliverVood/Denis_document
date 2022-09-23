<?php

	namespace Base\DB;

	abstract class DB {
		protected ?string $host;
		protected ?string $username;
		protected ?string $password;
		protected ?string $dbname;
		protected ?string $port;
		protected ?string $socket;

		protected array $tables;
		protected ?bool $state;

		protected function __construct(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null) {
			$this->host				= $host;
			$this->username			= $username;
			$this->password			= $password;
			$this->dbname			= $dbname;
			$this->port				= $port;
			$this->socket			= $socket;
			$this->tables			= [];
		}

		abstract public static function Connect(?string $hostname, ?string $user, ?string $password, ?string $dbname, string|int|null $port, ?string $socket);

		abstract public function Check();
		abstract public function Make();

		abstract public function Query(string $text);
		abstract public function GetQueryList(): array;

		abstract public function Insert(string $tablename, array $data): int;
		abstract public function Update(string $tablename, array $data, ?string $where): bool;
		abstract public function Delete(string $tablename, ?string $where): bool;
		abstract public function Select(string $tablename, ?array $fields, ?string $where, ?string $order, ?string $limit, ?array $calc);

		abstract public function Fetch($result): ?array;
		abstract public function FetchAll($result, ?callable $func = null): ?array;

		abstract protected function ConstructQueryInsert(string $tablename, array $data): string;
		abstract protected function ConstructQueryUpdate(string $tablename, array $data, string $where): string;
		abstract protected function ConstructQueryDelete(string $tablename, ?string $where): string;
		abstract protected function ConstructQuerySelect(string $tablename, ?array $fields, ?string $where, ?string $order, ?string $limit, ?array $calc): string;

		public function PushTables($table, ...$tables) {
			$args = func_get_args();
			foreach ($args as $arg) $this->tables[] = $arg;
		}

	}