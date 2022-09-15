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

		public function Check() {
			$result = $this->Query("SELECT `table_name`, `engine` FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = '{$this->dbname}'");
			$tables = $this->FetchAll($result);
			Debug($tables);
			foreach ($this->tables as $table) $table->Check();
//SHOW DATABASES; - список баз данных
//SHOW TABLES [FROM db_name]; -  список таблиц в базе
//SELECT table_name, table_rows FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'your_database_name';
//SHOW COLUMNS FROM таблица [FROM db_name]; - список столбцов в таблице
//SHOW CREATE TABLE table_name; - показать структуру таблицы в формате "CREATE TABLE"
//SHOW INDEX FROM tbl_name; - список индексов
//SHOW GRANTS FOR user [FROM db_name]; - привилегии для пользователя.
//
//
//SHOW VARIABLES; - значения системных переменных
//SHOW [FULL] PROCESSLIST; - статистика по mysqld процессам
//SHOW STATUS; - общая статистика
//SHOW TABLE STATUS [FROM db_name]; - статистика по всем таблицам в базе
		}

		public function Make() {
			foreach ($this->tables as $table) $table->Make();
		}

	}