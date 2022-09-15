<?php

	namespace Base\DB;

	use mysqli_result;

	class DBMySQLi extends DB {
		private \mysqli $db;
		private int $errno = 0;
		private array $history = [];

		private function __construct(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null) {
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
		 * @param string|null $hostname - Хост
		 * @param string|null $user - Пользователь
		 * @param string|null $password - Пороль
		 * @param string|null $dbname - Имя базы данных
		 * @param string|int|null $port - Порт
		 * @param string|null $socket - Сокет
		 * @return self
		 */
		public static function Connect(?string $hostname = null, ?string $user = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null): self {
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

		/**
		 * Запрос к БД
		 * @param string $text - Текст запроса
		 * @return bool|mysqli_result
		 */
		public function Query(string $text): bool|mysqli_result {
			$this->history[] = $text;

			return $this->db->query($text);
		}

		/**
		 * Возвращает историю запросов
		 * @return array
		 */
		public function GetQueryList(): array {
			return $this->history;
		}

		/**
		 * Вставка записи
		 * @param string $tablename - Имя таблицы
		 * @param array $data - Данные
		 * @return int
		 */
		public function Insert(string $tablename, array $data): int {
			return $this->Query($this->ConstructQueryInsert($tablename, $data)) ? $this->db->insert_id : 0;
		}

		/**
		 * Обновление записей
		 * @param string $tablename - Имя таблицы
		 * @param array $data - Данные
		 * @param string|null $where - Условия
		 * @return bool
		 */
		public function Update(string $tablename, array $data, ?string $where): bool {
			return $this->Query($this->ConstructQueryUpdate($tablename, $data, $where));
		}

		/**
		 * Удаление записей
		 * @param string $tablename - Имя таблицы
		 * @param string|null $where - Условия
		 * @return bool
		 */
		public function Delete(string $tablename, ?string $where = null): bool {
			return $this->Query($this->ConstructQueryDelete($tablename, $where));
		}

		/**
		 * @param string $tablename
		 * @param array|null $fields
		 * @param string|null $where
		 * @param string|null $order
		 * @param string|null $limit
		 * @param array|null $calc
		 * @return bool|mysqli_result
		 */
		public function Select(string $tablename, ?array $fields = null, ?string $where = null, ?string $order = null, ?string $limit = null, ?array $calc = null): bool|mysqli_result {
			return $this->Query($this->ConstructQuerySelect($tablename, $fields, $where, $order, $limit, $calc));
		}

		/**
		 * Построение запроса вставки записей
		 * @param string $tablename - Имя таблицы
		 * @param array $data - Данные
		 * @return string
		 */
		public function ConstructQueryInsert(string $tablename, array $data): string {
			$fields = '`' . implode('`, `', array_keys($data)) . '`';
			foreach ($data as & $value) $value = $this->db->real_escape_string($value);
			$values = '\'' . implode('\', \'', $data) . '\'';

			return "INSERT INTO `{$tablename}` ({$fields}) VALUES ({$values})";
		}

		/**
		 * Построение запроса обновления записей
		 * @param string $tablename - Имя таблицы
		 * @param array $data - Данные
		 * @param string|null $where - Условия
		 * @return string
		 */
		public function ConstructQueryUpdate(string $tablename, array $data, ?string $where): string {
			$update = [];
			foreach ($data as $field => $value) $update[] = "`{$field}` = '" . $this->db->real_escape_string($value) . "'";
			$updateStr = implode(', ', $update);
			$whereStr = !is_null($where) ? " WHERE {$where}" : '';

			return "UPDATE `{$tablename}` SET {$updateStr}{$whereStr}";
		}

		/**
		 * Построение запроса удаления записей
		 * @param string $tablename
		 * @param string|null $where
		 * @return string
		 */
		public function ConstructQueryDelete(string $tablename, ?string $where = null): string {
			$whereStr = !is_null($where) ? " WHERE {$where}" : '';
			return "DELETE FROM `{$tablename}`{$whereStr}";
		}

		/**
		 * Ваборка
		 * @param string $tablename - Имя таблицы
		 * @param array|null $fields - Поля
		 * @param string|null $where - Условия
		 * @param string|null $order - Сортировка
		 * @param string|null $limit - Лимит
		 * @param array|null $calc - Вычисляемые поля
		 * @return string
		 */
		public function ConstructQuerySelect(string $tablename, ?array $fields = null, ?string $where = null, ?string $order = null, ?string $limit = null, ?array $calc = null): string {
			$fieldsStr = '*';
			if (!is_null($fields) || !is_null($calc)) {
				$fieldsList = [];
				if (!is_null($fields)) $fieldsList[] = '`' . implode('`, `', $fields) . '`';
				if (!is_null($calc)) $fieldsList[] = implode(', ', $calc);
				$fieldsStr = implode(', ', $fieldsList);
			}
			$whereStr = !is_null($where) ? " WHERE {$where}" : '';
			$orderStr = !is_null($order) ? " ORDER BY {$order}" : '';
			$limitStr = !is_null($limit) ? " LIMIT {$limit}" : '';
			return "SELECT {$fieldsStr} FROM `{$tablename}`{$whereStr}{$orderStr}{$limitStr}";
		}

		/**
		 * Возвращает одну запись резельтата запроса в виде ассоциативного массива
		 * @param $result - Результат запроса
		 * @return array|null
		 */
		public function Fetch($result): array|null {
			if (!$result) return null;
			return $result->fetch_assoc();
		}

		/**
		 * Возвращает записи результата запроса в виде массива
		 * @param $result - Результат запроса
		 * @param callable|null $func - Результат запроса
		 * @return array|null
		 */
		public function FetchAll($result, ?callable $func = null): ?array {
			$out = [];
			while ($fitch = $this->Fetch($result)) {
				$out[] = $fitch;
			}

			return $out;
		}

	}