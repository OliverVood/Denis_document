<?php

	namespace Base\DB;

	abstract class DBObjectMySQLi extends DBObject {
		use DBMySQLi;

		protected function __construct(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null) {
			parent::__construct();

			$this->Link($host, $username, $password, $dbname, $port, $socket);
		}

		/**
		 * Проверка базы данных
		 * @return array
		 */
		public function Check(): array {
			$out = [];
			$tables = [];

			/* Get tables structure */
			$tables_struct = [];
			foreach ($this->tables as $table) {
				$name = $table->GetName();
				$tables_struct[] = $name;
				$tables[] = $name;
			}

			/* Get tables DB */
			$result = $this->Query("SELECT `table_name` AS `name` FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = '{$this->dbname}'");
			$tables_db = $this->FetchAll($result, function(& $items, $item) use (& $tables) {
				$items[] = $item['name'];
				if (!in_array($item['name'], $tables)) $tables[] = $item['name'];
			});

			/* Check tables */
			foreach ($tables as $table) {
				$action = TableMySQLi::ERROR_NULL;
				$error = null;
				$fields = null;
				if (!in_array($table, $tables_db)) {
					$action = TableMySQLi::ERROR_CREATE;
					$error = 'Создать таблицу';
				}
				else if (!in_array($table, $tables_struct)) {
					$action = TableMySQLi::ERROR_DELETE;
					$error = 'Удалить таблицу';
				}
				else {
					$res = $this->GetTable($table)->Check();
					if ($res['action'] < 0) {
						$action = $res['action'];
						$error = 'Изменить таблицу';
						$fields = $res['fields'];
					}
				}

				if ($action < 0) {
					$_out = ['name' => $table, 'action' => $action, 'error' => $error];
					if ($fields) $_out['fields'] = $fields;
					$out[] = $_out;
				}
			}

			return $out;
		}

		/**
		 * Исправление базы данных
		 * @return bool
		 */
		public function Make(): bool {
			if (!$tables = GetParam('tables')) return false;

			foreach ($tables as $name => $table) {
				$action = (int)$table['action'];
				switch ($action) {
					case TableMySQLi::ERROR_CREATE: $this->tables[$name]->Create(); break;
					case TableMySQLi::ERROR_UPDATE: $this->tables[$name]->Make($table['fields']); break;
					case TableMySQLi::ERROR_DELETE: $this->db->Query("DROP TABLE `{$name}`"); break;
				}
			}

			return true;
		}

	}