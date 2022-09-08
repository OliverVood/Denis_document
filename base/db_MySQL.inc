<?php

	namespace Base\DB;

	class MySQLi extends DB {
		private \mysqli $db;
		private int $errno = 0;

		private function __construct($host = null, $username = null, $password = null, $dbname = null, $port = null, $socket = null) {
			parent::__construct($host, $username, $password, $dbname, $port, $socket);

			@ $this->db = new \mysqli($this->host, $this->username, $this->password, $this->dbname, $this->port, $this->socket);

			if (!$this->db->connect_errno) {
				$this->state = true;
			} else {
				$this->state = false;
				$this->errno = $this->db->connect_errno;
			}
		}

		/**
		 * Соединение с базой данных
		 * @param null $hostname - Хост
		 * @param null $user - Пользователь
		 * @param null $password - Пороль
		 * @param null $dbname - Имя базы данных
		 * @param null $port - Порт
		 * @param null $socket - Сокет
		 * @return MySQLi
		 */
		public static function Connect($hostname = null, $user = null, $password = null, $dbname = null, $port = null, $socket = null) :self {
			return new self($hostname, $user, $password, $dbname);
		}

		/**
		 * Возвращает состояние соединения
		 * @return bool
		 */
		public function State() :bool {
			return $this->state;
		}

		/**
		 * Возвращмет код ошибки
		 * @return int
		 */
		public function GetErrorCode() :int {
			return $this->errno;
		}

		public function Insert(string $tablename, array $data): int {
			return $this->db->query($this->ConstructQueryInsert($tablename, $data)) ? $this->db->insert_id : 0;
		}

		public function Update(string $tablename, array $data, string $where): bool {
			return $this->db->query($this->ConstructQueryUpdate($tablename, $data, $where));
		}

		public function Delete(string $tablename, string $where)
		{
			// TODO: function Delete() method.
		}

		public function Select(string $query)
		{
			// TODO: function Select() method.
		}

		public function ConstructQueryInsert(string $tablename, array $data): string {
			$fields = '`' . implode('`, `', array_keys($data)) . '`';
			$values = '\'' . implode('\', \'', $data) . '\'';

			return "INSERT INTO `{$tablename}` ({$fields}) VALUES ({$values})";
		}

		public function ConstructQueryUpdate(string $tablename, array $data, string $where): string {
			$update = [];
			foreach ($data as $field => $value) $update[] = "`{$field}` = '{$value}'";
			$updateStr = implode(', ', $update);

			return "UPDATE `{$tablename}` SET {$updateStr}" . ($where ? " WHERE {$where}" : '');
		}

		public function ConstructQueryDelete(string $tablename, string $where): string {
			// TODO: Implement СonstructQueryDelete() method.
			return '';
		}

	}