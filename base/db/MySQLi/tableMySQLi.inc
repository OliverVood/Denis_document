<?php

	namespace Base\DB;

	class TableMySQLi extends Table {
		const ERROR_NULL	=  1;
		const ERROR_CREATE 	= -1;
		const ERROR_UPDATE 	= -2;
		const ERROR_DELETE 	= -3;

		private string	$engine 	= 'InnoDB';
		private string	$encoding 	= 'utf8';
		private array	$primary	= [];

		/** @var DBObjectMySQLi $db */

		public function __construct($name, $db) {
			parent::__construct($name, $db);
		}

		public function id(string $name): void { $this->AddPrimary([$name]); $this->PushField(new FieldIDMySQLi($name, $this)); }
		public function bool(string $name): void { $this->PushField(new FieldBoolMySQLi($name, $this)); }
		public function int8(string $name): void { $this->PushField(new FieldInt8MySQLi($name, $this)); }
		public function int16(string $name): void { $this->PushField(new FieldInt16MySQLi($name, $this)); }
		public function int24(string $name): void { $this->PushField(new FieldInt24MySQLi($name, $this)); }
		public function int32(string $name): void { $this->PushField(new FieldInt32MySQLi($name, $this)); }
		public function int64(string $name): void { $this->PushField(new FieldInt64MySQLi($name, $this)); }
		public function uint8(string $name): void { $this->PushField(new FieldUInt8MySQLi($name, $this)); }
		public function uint16(string $name): void { $this->PushField(new FieldUInt16MySQLi($name, $this)); }
		public function uint24(string $name): void { $this->PushField(new FieldUInt24MySQLi($name, $this)); }
		public function uint32(string $name): void { $this->PushField(new FieldUInt32MySQLi($name, $this)); }
		public function uint64(string $name): void { $this->PushField(new FieldUInt64MySQLi($name, $this)); }
		public function float(string $name): void { $this->PushField(new FieldFloatMySQLi($name, $this)); }
		public function double(string $name): void { $this->PushField(new FieldDoubleMySQLi($name, $this)); }
		public function timestamp(string $name, bool $update = false): void { $this->PushField(new FieldTimestampMySQLi($name, $update, $this)); }
		public function enum(string $name, array $enum): void { $this->PushField(new FieldEnumMySQLi($name, $enum, $this)); }
		public function set(string $name, array $set): void { $this->PushField(new FieldSetMySQLi($name, $set, $this)); }
		public function string(string $name, int $length): void { $this->PushField(new FieldStringMySQLi($name, $length, $this)); }
		public function text(string $name): void { $this->PushField(new FieldTextMySQLi($name, $this)); }
		public function AddPrimary(array $primary): void { $this->primary[] = $primary; }

		public function Check(): array {
			$out = ['action' => 1, 'fields' => []];

			$fields = [];

			/* Get fields struct */
			foreach ($this->structure as $name => $field) {
				$fields[] = $name;
			}

			/* Get fields DB */
			$result = $this->db->Query("SELECT `COLUMN_NAME`, `COLUMN_DEFAULT`, `IS_NULLABLE`, `DATA_TYPE`, `CHARACTER_MAXIMUM_LENGTH`, `COLUMN_TYPE`, `COLUMN_KEY`, `EXTRA` FROM information_schema.`COLUMNS` WHERE (TABLE_NAME = '{$this->name}') AND (TABLE_SCHEMA = '{$this->db->GetName()}') ORDER BY `ORDINAL_POSITION`");
			$fields_db = $this->db->FetchAll($result, function(& $items, $item) use (& $fields) {
				$items[$item['COLUMN_NAME']] = $item;
				if (!in_array($item['COLUMN_NAME'], $fields)) $fields[] = $item['COLUMN_NAME'];
			});

			/* Check fields */
			foreach ($fields as $field) {
				$action = FieldMySQLi::ERROR_NULL;
				$error = null;
				$details = null;
				if (!isset($fields_db[$field])) {
					$action = FieldMySQLi::ERROR_CREATE;
					$error = 'Добавить поле';
				}
				else if (!isset($this->structure[$field])) {
					$action = FieldMySQLi::ERROR_DELETE;
					$error = 'Удалить поле';
				}
				else {
					$res = $this->structure[$field]->Check($fields_db[$field]);
					if ($res['action'] < 0) {
						$action = $res['action'];
						$error = 'Изменить поле';
						$details = $res['details'];
					}
				}

				if ($action < 0) {
					$_out = ['action' => $action, 'name' => $field, 'error' => $error];
					if ($details) $_out['details'] = $details;
					$out['fields'][] = $_out;
					$out['action'] = self::ERROR_UPDATE;
				}
			}

			return $out;
		}

		public function Create(): void {
			$fields = [];
			$primaries = [];
			foreach ($this->structure as $field) $fields[] = $field->CreationFormat();
			foreach ($this->primary as $primary) $primaries[] = ", PRIMARY KEY (`" . implode('`, `', $primary) . "`)";
			$this->db->query("CREATE TABLE `{$this->name}` (" . implode(', ', $fields) . implode('', $primaries) . ") ENGINE = {$this->engine}  DEFAULT CHARSET = {$this->encoding}");
		}

		public function Make(array $fields): bool {
			foreach ($fields as $name => ['action' => $action]) {
				switch ($action) {
					case FieldMySQLi::ERROR_CREATE: $this->structure[$name]->Create(); break;
					case FieldMySQLi::ERROR_VARIOUS: $this->structure[$name]->Update(); break;
					case FieldMySQLi::ERROR_DELETE: $this->db->Query("ALTER TABLE `{$this->name}` DROP COLUMN `{$name}`"); break;
				}
			}

			return true;
		}

	}