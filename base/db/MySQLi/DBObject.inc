<?php

	namespace Base\DB\MySQLi;

	abstract class DBObject extends \Base\DB\DBObject {
		use DB;

		protected function __construct(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null) {
			parent::__construct();

			$this->Link($host, $username, $password, $dbname, $port, $socket);
		}

		private function GetTableListApp(): array {
			$out = [];
			foreach ($this->tables as $table) $out[] = $table->GetName();

			return $out;
		}

		private function GetTableListDB(): array {
			$result = $this->Query("SELECT `table_name` AS `name` FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = '{$this->dbname}'");
			return $this->FetchAll($result, function(& $items, $item) {
				$items[] = $item['name'];
			});
		}

		/**
		 * Проверка базы данных
		 * @return array
		 */
		public function Check(): array {
			$tableListApp = $this->GetTableListApp();
			$tablesListDB = $this->GetTableListDB();
			$tables = $tableListApp;
			foreach ($tablesListDB as $table) if (!in_array($table, $tables)) $tables[] = $table;

			$out = [];

			foreach ($tables as $table) {

				if (!in_array($table, $tablesListDB)) {
					$out[] = ['name' => $table, 'action' => Table::ACTION_CREATE, 'error' => 'Создать таблицу'];
					continue;
				}

				if (!in_array($table, $tableListApp)) {
					$out[] = ['name' => $table, 'action' => Table::ACTION_DELETE, 'error' => 'Удалить таблицу'];
					continue;
				}

				$res = $this->GetTable($table)->Check();
				if ($res['action'] < 0) {
					$out[] = ['name' => $table, 'action' => $res['action'], 'error' => 'Изменить таблицу', 'fields' => $res['fields']];
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
					case Table::ACTION_CREATE: $this->tables[$name]->Create(); break;
					case Table::ACTION_UPDATE: $this->tables[$name]->Make($table['fields']); break;
					case Table::ACTION_DELETE: $this->db->Query("DROP TABLE `{$name}`"); break;
				}
			}

			return true;
		}

	}