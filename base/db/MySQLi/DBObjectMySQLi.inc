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
				$state = TableMySQLi::ERROR_NULL;
				$error = null;
				$fields = null;
				if (!in_array($table, $tables_db)) {
					$state = TableMySQLi::ERROR_CREATE;
					$error = 'Создать таблицу';
				}
				else if (!in_array($table, $tables_struct)) {
					$state = TableMySQLi::ERROR_DELETE;
					$error = 'Удалить таблицу';
				}
				else {
					$res = $this->GetTable($table)->Check();
					if ($res['state'] < 0) {
						$state = $res['state'];
						$error = 'Изменить таблицу';
						$fields = $res['fields'];
					}
				}

				if ($state < 0) {
					$_out = ['name' => $table, 'state' => $state, 'error' => $error];
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

			$queries = [];
			foreach ($tables as $tablename => $table) {
				$q = match ((int)$table['state']) {
					TableMySQLi::ERROR_CREATE => $this->tables[$tablename]->Create(),
					TableMySQLi::ERROR_UPDATE => $this->tables[$tablename]->Modify($table),
					TableMySQLi::ERROR_DELETE => TableMySQLi::Remove($tablename),
					default => ''
				};
				if (is_array($q)) foreach ($q as $query) $queries[] = $query;
				else $queries[] = $q;
			} //Debug($queries);die();

			$this->MultiQuery(implode('; ', $queries));

			//TODO continue from here

//			Debug($tables);
//			die();

			return true;
		}

	}