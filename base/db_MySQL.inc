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

		public function Insert(array $data, string $tablename): int {
			$fields = '`' . implode('`, `', array_keys($data)) . '`';
			$values = '\'' . implode('\', \'', $data) . '\'';

			$result = $this->db->query("INSERT INTO `{$tablename}` ({$fields}) VALUES ({$values})");

			return $result ? $this->db->insert_id : 0;
		}

		public function Update(array $data, string $where, string $tablename): bool {
			$update = [];
			foreach ($data as $field => $value) $update[] = "`{$field}` = '{$value}'";
			$updateStr = implode(', ', $update);

			return $this->db->query("UPDATE `{$tablename}` SET {$updateStr}" . ($where ? " WHERE {$where}" : ''));
		}

		public function Delete()
		{
			// TODO: function Delete() method.
		}

		public function Select()
		{
			// TODO: function Select() method.
		}

	}