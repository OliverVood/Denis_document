<?php

	namespace Base\DB;

	class TableMySQLi extends Table {
		const ACTION_OK				=  1;
		const ACTION_CREATE			= -1;
		const ACTION_UPDATE			= -2;
		const ACTION_DELETE 		= -3;

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

		private function GetFieldListApp(): array {
			$out = [];
			foreach ($this->structure as $name => $field) $out[] = $name;

			return $out;
		}

		private function GetListFieldDB(): array {
			$fieldsData = [];
			$result = $this->db->Query("SELECT `COLUMN_NAME`, `COLUMN_DEFAULT`, `IS_NULLABLE`, `DATA_TYPE`, `CHARACTER_MAXIMUM_LENGTH`, `COLUMN_TYPE`, `COLUMN_KEY`, `EXTRA` FROM information_schema.`COLUMNS` WHERE (TABLE_NAME = '{$this->name}') AND (TABLE_SCHEMA = '{$this->db->GetName()}') ORDER BY `ORDINAL_POSITION`");
			$fieldsList = $this->db->FetchAll($result, function(& $items, $item) use (& $fieldsData) {
				$items[] = $item['COLUMN_NAME'];
				$fieldsData[$item['COLUMN_NAME']] = $item;
			});

			return [$fieldsList, $fieldsData];
		}

		public function Check(): array {
			$out = ['action' => self::ACTION_OK, 'fields' => []];

			$fieldListApp = $this->GetFieldListApp();
			[$fieldListDB, $fieldsData] = $this->GetListFieldDB();
			$fields = $fieldListApp;
			foreach ($fieldListDB as $field) if (!in_array($field, $fields)) $fields[] = $field;

			foreach ($fields as $field) {

				if (!in_array($field, $fieldListDB)) {
					$out['fields'][] = ['action' => FieldMySQLi::ACTION_CREATE, 'name' => $field, 'error' => 'Добавить поле'];
					$out['action'] = self::ACTION_UPDATE;
					continue;
				}
				if (!in_array($field, $fieldListApp)) {
					$out['fields'][] = ['action' => FieldMySQLi::ACTION_DELETE, 'name' => $field, 'error' => 'Удалить поле'];
					$out['action'] = self::ACTION_UPDATE;
					continue;
				}

				$res = $this->structure[$field]->Check($fieldsData[$field]);
				if ($res['action'] < 0) {
					$out['fields'][] = ['action' => $res['action'], 'name' => $field, 'error' => 'Изменить поле', 'details' => $res['details']];
					$out['action'] = self::ACTION_UPDATE;
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
					case FieldMySQLi::ACTION_CREATE: $this->structure[$name]->Create(); break;
					case FieldMySQLi::ACTION_VARIOUS: $this->structure[$name]->Update(); break;
					case FieldMySQLi::ACTION_DELETE: $this->db->Query("ALTER TABLE `{$this->name}` DROP COLUMN `{$name}`"); break;
				}
			}

			return true;
		}

	}