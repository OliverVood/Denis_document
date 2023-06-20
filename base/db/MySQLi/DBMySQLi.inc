<?php

	namespace Base\DB;

	use mysqli_result;

	trait DBMySQLi {
		protected static ?self $instance = null;

		private \mysqli $db;
		private int $errno = 0;
		private array $history = [];

		public static function instance(): ?self { return self::$instance; }
		public static function init(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null): void { if (!self::$instance) self::$instance = self::Connect($host, $username, $password, $dbname, $port, $socket); }

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
			return new static($hostname, $user, $password, $dbname, $port, $socket);
		}

		private function Link($hostname, $username, $password, $dbname, $port, $socket): void {
			$this->dbname			= $dbname;

			@ $this->db = new \mysqli($hostname, $username, $password, $this->dbname, $port, $socket);
			mysqli_set_charset($this->db, 'utf8mb4');

			if (!$this->db->connect_errno) {
				$this->state = true;
			} else {
				$this->state = false;
				$this->errno = $this->db->connect_errno;
			}
		}

		/**
		 * Возвращает код ошибки
		 * @return int
		 */
		public function GetErrorCode() :int {
			return $this->errno;
		}

		/**
		 * Запрос к БД
		 * @param string $query - Текст запроса
		 * @return bool|mysqli_result
		 */
		public function Query(string $query): bool|mysqli_result {
			$this->history[] = $query;

			return $this->db->query($query);
		}

		/**
		 * Мультизапрос к БД
		 * @param string $query - Текст запросов
		 * @return array
		 */
		public function MultiQuery(string $query): array {
			$this->history[] = $query;

			$this->db->multi_query($query);
			$result = [];
			do {
				$result[] = $this->db->store_result();
			} while ($this->db->next_result());

			return $result;
		}

		/**
		 * Возвращает историю запросов
		 * @return array
		 */
		public function GetQueryList(): array {
			return $this->history;
		}

		/**
		 * Возвращает текст последнего запроса
		 * @return string
		 */
		public function GetLastQuery(): string {
			return end($this->history);
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
		 * @param string $tablename
		 * @param array|null $fields
		 * @param string|null $where
		 * @param string|null $order
		 * @param string|null $limit
		 * @param array|null $calc
		 * @return null|array
		 */
		public function SelectOne(string $tablename, ?array $fields = null, ?string $where = null, ?string $order = null, ?string $limit = null, ?array $calc = null): null | array {
			$result = $this->Select($tablename, $fields, $where, $order, $limit, $calc);
			return $this->Fetch($result);
		}

		/**
		 * @param string $tablename
		 * @param string $field
		 * @param string|null $where
		 * @param string|null $order
		 * @param string|null $limit
		 * @return null|string
		 */
		public function SelectOneField(string $tablename, string $field, ?string $where = null, ?string $order = null, ?string $limit = '1'): null | string {
			$row = $this->SelectOne($tablename, [$field], $where, $order, $limit);
			return $row[$field] ?? null;
		}

		/**
		 * @param string $tablename
		 * @param string $field_calc
		 * @param string $field_name
		 * @param string|null $where
		 * @param string|null $order
		 * @param string|null $limit
		 * @return null|string
		 */
		public function SelectOneFieldCalc(string $tablename, string $field_calc, string $field_name, ?string $where = null, ?string $order = null, ?string $limit = '1'): null | string {
			$row = $this->SelectOne($tablename, null, $where, $order, $limit, [$field_calc]);
			return $row[$field_name] ?? null;
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

			if ($func) { while ($fitch = $this->Fetch($result)) $func($out, $fitch); }
			else { while ($fitch = $this->Fetch($result)) $out[] = $fitch; }

			return $out;
		}

		public function Escaping(string $str): string {
			return $this->db->real_escape_string($str);
		}

	}